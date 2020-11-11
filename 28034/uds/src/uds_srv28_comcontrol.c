/****************************************************************************
 	@Module       
 	@Filename      uds_srv28_comcontrol.c
 	@Project       BQApp
----------------------------------------------------------------------------
 	@Controller    TI 28034

 	@Compiler      V5.211

 	@Codegenerator CCS 3.3

 	@Description   

----------------------------------------------------------------------------
	 @Date          12/19/2014

******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

****************************************************************************/


#include "uds_target.h"
#include "uds_confpriv.h"
#include "uds_confdefs.h"
#include "uds_priv.h"
#include "uds_inf.h"
#include "CANProtocal.h"




#ifdef UDS_ENABLE_COMMUNICATIONCONTROL
static Uds_APduData_t* pSavedAPduResp;
static uint8_t UdsApp_28ComCtrl_PendingFlg;
static Uint16 Delay28Count;
Uint16 CurRxUdsMsgBuf=0u;
Uint16 PreRxUdsMsgBuf0[10];
Uint16 PreRxUdsMsgBuf1[10];
Uint16 PreRxUdsMsgBuf2[10];
Uint16 PreRxUdsMsgBuf3[10];
static const Uint16 Srv28Key0[4] = {0x7DF,0x02,0x10,0x03};
static const Uint16 Srv28Key1[6] = {0x7E0,0x04,0x31,0x01,0x02,0x03};
static const Uint16 Srv28Key2[4] = {0x7DF,0x02,0x85,0x02};
static const Uint16 Srv28Key3[5] = {0x7DF,0x03,0x28,0x03,0x01};

static Uint16 CheckSrv28Key(void);

/* Sun-Function parameter for CommunicationControl(ISO15765-3 limited)
 * 	controlType
	0x00	ENABLE_RX_AND_TX
	0x01	ENABLE_RX_DISABLE_TX
	0x02	DISABLE_RX_ENABLE_TX
	0x03	DISABLE_RX_AND_TX
 */

/* NRC for CommunicationControl
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 *	0x31	UDS_NRC_REQUESTOUTOFRANGE
 */
 
/* communicationType for CommunicationControl(ISO15765-3 defined)
 *	bit-code value for each type
 *	01b - application: (all application-related communication, e.g. inter-application
						signal exchange between multiple in-vehicle servers.)
 *	10b - network management: (all network-management-related communication).
 */

Std_UdsReturnType UDS_FN_TYPE UdsApp_ComControl(Uds_APduData_t* pAPduInd, 
                                                Uds_APduData_t* pAPduResp )
{
	uint8_t lub_error;
	uint8_t lub_CommTypeByte; 
	uint8_t lub_CommTypeTrafficBits; 
	uint8_t lub_CommTypeSubnetBits; 
	uint8_t lub_0x28CommCtrl_SubFunc;
	uint8_t lub_tmp_Req_IsFuncAddr;
	lub_error = UDS_POSITIVE_RESPONSE;

	lub_tmp_Req_IsFuncAddr = UDS_APP_ITF_IMP_GET_TP_CHNL();
          
	pSavedAPduResp = pAPduResp; /* just to remove the compiliation warning */

	if ((pAPduInd->msgLength) != 0x03u)
	{
	   /* the valid request length for 0x28 svc is 0x03 bytes. 
		  otherwise , to return NRC: 0x13 : IncorrectMessageLengthOrInvalidFormat
		*/
	   lub_error = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
	} 
	else if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION)
	{   
        if (TARGETADDR_FUNCTIONAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
            lub_error = UDS_POSITIVE_RESPONSE;
            pAPduResp->CurrSvcIsSupPosRspBitSet = 1u;
            pAPduResp->msgLength = 0x02u;
        }
        else {
            /* 0x28 CommunicationControl will only be allowed in the non-default session 
            otherwise , to return NRC: 0x7F, SevericeNotSupportedInCurrActiveSession 
		    */
	        lub_error = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
        }
	}   
	else
	{
	   /* to handle the byte_1 control_type , 
		  except bit7 SuppressPositiveResponseMessgeIndicationBit        
		*/
	   lub_0x28CommCtrl_SubFunc = ((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7); 
		
	   switch(lub_0x28CommCtrl_SubFunc)
	   {
		   default:
				lub_error= UDS_NRC_SUBFUNCTIONNOTSUPPORTED; 
				break;
		   case UDS_C_COMMCONTROL_ENABLE_RX_ENABLE_TX   :
				 case UDS_C_COMMCONTROL_ENABLE_RX_DISABLE_TX  :
				 case UDS_C_COMMCONTROL_DISABLE_RX_ENABLE_TX  :
				 case UDS_C_COMMCONTROL_DISABLE_RX_DISABLE_TX :           
				lub_CommTypeByte        = (pAPduInd->pduData[0x02u]); 
				lub_CommTypeTrafficBits = (lub_CommTypeByte & UDS_C_COMCTRL_COM_TYP_TRAFFIC_MASK); 
				lub_CommTypeSubnetBits  =  ((lub_CommTypeByte  & UDS_C_COMCTRL_COM_TYP_SUBNET_MASK) >> 0x04u); 
				
				if (lub_CommTypeTrafficBits != UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG  &&
					lub_CommTypeTrafficBits != UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG    &&
					lub_CommTypeTrafficBits != UDS_C_COMCTRL_COM_TYP_TRFC_NORM_AND_NM_MSG )
				{
					lub_error = UDS_NRC_REQUESTOUTOFRANGE;
				}
				else if(lub_CommTypeSubnetBits != UDS_C_COMCTRL_SUBNET_RCV_NODE_AND_ALL_CONNECT_NET &&
						/*(lub_CommTypeSubnetBits < UDS_C_COMCTRL_SUBNET_SPEC_NET_BY_NET_NUM_MIN ||
						   lub_CommTypeSubnetBits > UDS_C_COMCTRL_SUBNET_SPEC_NET_BY_NET_NUM_MIN   )  &&
						 */ 
						lub_CommTypeSubnetBits != UDS_C_COMCTRL_SUBNET_NET_REQ_RCVD_ON                )  
						  
				{
					lub_error = UDS_NRC_REQUESTOUTOFRANGE;
				}				
				else if((VmsState == 255)&&(lub_0x28CommCtrl_SubFunc == UDS_C_COMMCONTROL_DISABLE_RX_ENABLE_TX))
				{
					lub_error = UDS_NRC_REQUESTOUTOFRANGE;
				}
				else if(lub_0x28CommCtrl_SubFunc == UDS_C_COMMCONTROL_DISABLE_RX_DISABLE_TX)
				{
					if(TARGETADDR_PHYSICAL == lub_tmp_Req_IsFuncAddr)
					{
							UdsApp_28ComCtrl_ExecuteCommControlAction(lub_0x28CommCtrl_SubFunc, 
															lub_CommTypeByte);
							(pAPduResp->msgLength) = 0x02u;						
					}
					else
					{
                        if (CheckSrv28Key()) 
                        {
							lub_error = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;	
							UdsApp_28ComCtrl_PendingFlg = TRUE;
							Delay28Count = 10000u;
                        }
						else
						{
							UdsApp_28ComCtrl_ExecuteCommControlAction(lub_0x28CommCtrl_SubFunc, 
															lub_CommTypeByte);
							(pAPduResp->msgLength) = 0x02u;
						}	
					}
				}
				else
				{
					{
						UDS_APP_ITF_IMP_SET_COMM_CTRL_ACTION(lub_0x28CommCtrl_SubFunc, 
															lub_CommTypeByte);
						/* the valid positive reponse will be 2 bytes totally 
					 	*/
						(pAPduResp->msgLength) = 0x02u;
					}
				}           
				break;

	   }  /* end of switch(lub_0x28CommCtrl_SubFunc)  */
	} /* end of else if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION) */

   return lub_error;
} /* end of Uds_28ComCtrl_ReqSpecialProcess() */

//Bootloader only support 00(Enable RXAndTX) 03(DisableRXAndTX)
void UDS_FN_TYPE UdsApp_28ComCtrl_ExecuteCommControlAction(
      uint8_t i_CntrlType, 
      uint8_t i_CommSubnetType ) 
{
    uint8_t lub_CommTypeTrafficBits; 
    uint8_t lub_CommTypeSubnetBits; 

    lub_CommTypeTrafficBits =   (i_CommSubnetType & UDS_C_COMCTRL_COM_TYP_TRAFFIC_MASK); 
    lub_CommTypeSubnetBits  =  ((i_CommSubnetType  & UDS_C_COMCTRL_COM_TYP_SUBNET_MASK) >> 0x04u); 

    if( lub_CommTypeSubnetBits == UDS_C_COMCTRL_SUBNET_RCV_NODE_AND_ALL_CONNECT_NET ||
        lub_CommTypeSubnetBits == UDS_C_COMCTRL_SUBNET_NET_REQ_RCVD_ON                ) 
    {
        switch(i_CntrlType) 
        {
          
            case UDS_C_COMMCONTROL_ENABLE_RX_ENABLE_TX   :
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_TX_TRAFFIC(); 
                } 
                else 
                {
                  
                }
                
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_TX_TRAFFIC();                  
                } 
                else 
                {
                  
                }
                break;
                
			case UDS_C_COMMCONTROL_ENABLE_RX_DISABLE_TX  :
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NORM_TX_TRAFFIC(); 
                } 
                else 
                {
                  
                }
                
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NM_TX_TRAFFIC();                  
                } 
                else 
                {
                  
                }
			    break;
			          
			case UDS_C_COMMCONTROL_DISABLE_RX_ENABLE_TX  :
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NORM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_TX_TRAFFIC(); 
                } 
                else 
                {
                  
                }
                
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_TX_TRAFFIC();                  
                } 
                else 
                {
                  
                }
			    break;
			          
			case UDS_C_COMMCONTROL_DISABLE_RX_DISABLE_TX :
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NORM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NORM_TX_TRAFFIC(); 
                } 
                else 
                {
                  
                }
                
                if( lub_CommTypeTrafficBits & UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG)
                {
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NM_RX_TRAFFIC(); 
                    UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NM_TX_TRAFFIC();                  
                } 
                else 
                {
                  
                }			     
			    break;
			     
        } /* end of switch(i_CntrlType)  */
    } /* end of if( lub_CommTypeSubnetBits == UDS_C_COMCTRL_SUBNET_RCV_NODE_AND_ALL_CONNECT_NET */
}

void UDS_FN_TYPE UdsApp_28ComCtrl_Init(void)
{
	UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_RX_TRAFFIC();    /* TODO: need the itf from IL   */
	UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NORM_TX_TRAFFIC();    /* TODO: need the itf from IL   */

	UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_RX_TRAFFIC();      /* TODO: need the itf from NM */
	UDS_APP_ITF_IMP_SET_COM_CTRL_ENA_NM_TX_TRAFFIC();      /* TODO: need the itf from NM */  
}





uint8_t UDS_FN_TYPE UdsApp_28ComCtrl_Pending(void)
{
	uint8_t lub_response  = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING  ;

    if (UdsApp_28ComCtrl_PendingFlg == TRUE)
    {
		if (Delay28Count) {
			Delay28Count--;
		}
		
		//if ((VmsState == 255)||(ErrorList.bit.Low12V==1)||(AlarmCode.bit.VMSLost == 1))
		if ((VmsState == 255) || (Delay28Count == 0u))
		{
            UdsApp_28ComCtrl_PendingFlg = FALSE;
			UDS_APP_ITF_IMP_SET_COM_CTRL_DIS_NORM_TX_TRAFFIC();
			lub_response                   = UDS_POSITIVE_RESPONSE ;
            (pSavedAPduResp->msgLength)    = 0x02u; 
            pSavedAPduResp->pduData[0x00u] = 0x68u; 
            pSavedAPduResp->pduData[0x01u] = 0x03u;
		}
		else
		{
		}

    }
    else
    {

    }

	return lub_response;
}  /* end of Uds_2eWtDatByDid_Pending() */

static Uint16 CheckSrv28Key(void)
{
	Uint16 IsOk;
	Uint16 i;

	IsOk = 0u;
	for (i = 0u; i < 4u; ) {
		if (PreRxUdsMsgBuf0[i] != Srv28Key0[i]) {
			break;
		}

		i++;
		
		if (i == 4u) {
			IsOk = 1u;
		}
	}

	if (IsOk == 1u) {
		IsOk = 0u;
		for (i = 0u; i < 6u; ) {
			if (PreRxUdsMsgBuf1[i] != Srv28Key1[i]) {
				break;
			}
		
			i++;
			
			if (i == 6u) {
				IsOk = 1u;
			}
		}
	}

	if (IsOk == 1u) {
		IsOk = 0u;
		for (i = 0u; i < 4u; ) {
			if (PreRxUdsMsgBuf2[i] != Srv28Key2[i]) {
				break;
			}
		
			i++;
			
			if (i == 4u) {
				IsOk = 1u;
			}
		}
	}

	if (IsOk == 1u) {
		IsOk = 0u;
		for (i = 0u; i < 5u; ) {
			if (PreRxUdsMsgBuf3[i] != Srv28Key3[i]) {
				break;
			}
		
			i++;
			
			if (i == 5u) {
				IsOk = 1u;
			}
		}
	}

	return IsOk;
}


#endif /* UDS_ENABLE_COMMUNICATIONCONTROL */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
