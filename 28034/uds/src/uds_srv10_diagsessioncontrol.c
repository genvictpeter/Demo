/****************************************************************************
 	@Module       
 	@Filename      uds_srv10_diagsessioncontrol.c
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
#include "uds_pub.h"





#ifdef UDS_ENABLE_DIAGNOSTICSESSIONCONTROL

/* Sun-Function parameter for DiagnosticSessionControl(ISO15765-3 limited)
 * 	diagnosticSessionType
 * 	0x01	UDS_DEFAULT_SESSION
 * 	0x02	UDS_PROGRAMMING_SESSION
 * 	0x03	UDS_EXTENDED_DIAGNOSTIC_SESSION
 */

/* NRC for DiagnosticSessionControl
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 */
 
/* sessionParameterRecord for DiagnosticSessionControl(ISO15765-3 defined)
 *	4bytes
 *	parameter1 - P2CanServerMax high byte
 *	parameter2 - P2CanServerMax low byte
 *	parameter3 - P2StarCanServerMax high byte
 *	parameter4 - P2StarCanServerMax low byte
 */

Std_UdsReturnType UDS_FN_TYPE  UdsApp_DiagSessionControl(Uds_APduData_t* pAPduInd, 
                                                      Uds_APduData_t* pAPduResp )
{
   uint8_t lub_error;
   uint8_t lub_uds_returncode;
   uint8_t lub_CurrActiveSession;
   uint8_t lub_IsAllowDiagSessionToggle = (uint8_t)FALSE;

   lub_error = UDS_POSITIVE_RESPONSE;
   //lub_uds_returncode= (uint8_t)FALSE;

   if (pAPduInd->msgLength != 0x02u )
   {
       /*incorrect size of 0x10 request */
       lub_error = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
   else
   {
       lub_CurrActiveSession = UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION();
         
       switch (((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7))
       {
           default:
           {
               lub_error = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
           }
           break;
             
           case UDS_PROGRAMMING_SESSION:
         	 {
         	    lub_IsAllowDiagSessionToggle = UDS_APP_ITF_IMP_CHK_SESN_CHNG_PRE_CND(lub_CurrActiveSession, 
         	                                                                            UDS_PROGRAMMING_SESSION);
				if(lub_IsAllowDiagSessionToggle == (uint8_t)TRUE) 
				{
					lub_uds_returncode = UDS_APP_ITF_IMP_SET_CHANGE_SESSION(UDS_PROGRAMMING_SESSION);
					if (lub_uds_returncode != TRUE)
					{
						lub_error = UDS_NRC_CONDITIONSNOTCORRECT;
					}
					else
					{
						lub_error = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
					}
				}
				else
				{
					lub_error = UDS_NRC_CONDITIONSNOTCORRECT; 
				}
           }  /* end of case UDS_PROGRAMMING_SESSION: */
           break;
           case UDS_EXTENDED_DIAGNOSTIC_SESSION:
           {
                if (UDS_DEFAULT_SESSION != lub_CurrActiveSession)
                {   
                    /* to execute all of the needed actions when 
                       entering a new session. 
                     */  
                    UdsApp_10Dsc_TriggerStartNewSessionActions(); 
                } 
                else 
                {
                }
                
                /* notify session manager to toggle to extended diag session */
                lub_uds_returncode = UDS_APP_ITF_IMP_SET_CHANGE_SESSION(UDS_EXTENDED_DIAGNOSTIC_SESSION);
                if (lub_uds_returncode != TRUE)
                {
                    lub_error = UDS_NRC_CONDITIONSNOTCORRECT;
                } 
                else 
                {
                          
                }

				UDS_APP_ITF_IMP_SET_PRVNT_ECU_2_SLEEP();
                UDS_APP_ITF_IMP_SET_PRVNT_CAN_2_SLEEP();
           } /* end of case UDS_EXTENDED_DIAGNOSTIC_SESSION: */
           break;

           case UDS_DEFAULT_SESSION:
           {
                /* switch back to default session can always be allowed.
                   to execute all of the needed actions when 
                   entering a new session. 
                 */
                UdsApp_10Dsc_TriggerStartNewSessionActions(); 

                /* notify session manager to toggle to extended diag session */
                lub_uds_returncode = UDS_APP_ITF_IMP_SET_CHANGE_SESSION(UDS_DEFAULT_SESSION);
                if (lub_uds_returncode != TRUE)
                {
                    lub_error = UDS_NRC_CONDITIONSNOTCORRECT;
                } 
                else 
                {
                          
                }
           } /* end of  case DP_APPL_DEFAULT_SESSION_ID: */
           break;

	       case UDS_ECU_SUPPLIER_SPEC_SESSION:
	        {
                if (UDS_DEFAULT_SESSION != lub_CurrActiveSession)
				{
                    /* switch back to default session can always be allowed.
                       to execute all of the needed actions when 
                       entering a new session. 
                     */
                    UdsApp_10Dsc_TriggerStartNewSessionActions(); 
                }
                else
                {
                }
				/* notify session manager to toggle to supplier specific diag session */
				lub_uds_returncode = UDS_APP_ITF_IMP_SET_CHANGE_SESSION(UDS_ECU_SUPPLIER_SPEC_SESSION);
				if (lub_uds_returncode != TRUE)
				{
					lub_error = UDS_NRC_CONDITIONSNOTCORRECT;
				} 
				else 
				{
				  
				}
				UDS_APP_ITF_IMP_SET_PRVNT_ECU_2_SLEEP();
				UDS_APP_ITF_IMP_SET_PRVNT_CAN_2_SLEEP();
           }
           break;
       }/* end of switch (((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7)) */
   } /* end of else of if (pAPduInd->msgLength != 0x02u ) */

   if (lub_error == UDS_POSITIVE_RESPONSE)
   {
       /* the optional positive response content the P2_Server and P2*_Server timer value */
       /* P2Can_server_max unit should be 1ms , P2StarCan_Server_max unite should be 10ms 
           the returned value from interface are absolute value , unit are always 1ms , so  P2StarCan_Server_max
           will be divided by 10u 
         */
       pAPduResp->pduData[0x02u] =  ((0xFF00u) & (uint16_t)(UDS_APP_ITF_IMP_GET_TP_P2SVR_TMR_VALUE() )) >> 0x08u;
       pAPduResp->pduData[0x03u] =   (0x00FFu) & (uint16_t)(UDS_APP_ITF_IMP_GET_TP_P2SVR_TMR_VALUE());
       pAPduResp->pduData[0x04u] =  ((0xFF00u) & (uint16_t)(UDS_APP_ITF_IMP_GET_TP_P2START_SVR_TMR_VALUE()/10u)) >> 0x08u;
       pAPduResp->pduData[0x05u] =   (0x00FFu) & (uint16_t)(UDS_APP_ITF_IMP_GET_TP_P2START_SVR_TMR_VALUE()/10u);
       /* the length of whole of positive response message  */
       pAPduResp->msgLength = 0x06u; 
   }
   else
   {

   }

   return lub_error;
}

void UDS_FN_TYPE UdsApp_10Dsc_TriggerStartNewSessionActions(void) 
{
	/* in this function , to trigger all of necessary 
	  actions when starting a new session
	  if the more actions are needed , can also 
	  put into this function to handle. 
	*/
	#ifdef UDS_ENABLE_ECURESET
	    UDS_APP_ITF_INT_CMD_STRT_NEW_SESN_ACTION;
	#endif
	
	#ifdef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION
	    UDS_APP_ITF_INT_DTC_STRT_NEW_SESN_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER
	    UDS_APP_ITF_INT_DID_STRT_NEW_SESN_ACTION;
	#endif
	
	#ifdef UDS_ENABLE_SECURITYACCESS
	    UDS_APP_ITF_INT_SECU_STRT_NEW_SESN_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_COMMUNICATIONCONTROL   
	    UDS_APP_ITF_INT_COMCTRL_STRT_NEW_SESN_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER   
	    UDS_APP_ITF_INT_E2BLK_STRT_NEW_SESN_ACTION;
       #endif

	#ifdef UDS_ENABLE_ROUTINECONTROL   
	    UDS_APP_ITF_INT_RTN_STRT_NEW_SESN_ACTION;
       #endif

	#ifdef UDS_ENABLE_LINKCONTROL   
	    UDS_APP_ITF_INT_LNKCTRL_STRT_NEW_SESN_ACTION;
	#endif

	#ifdef UDS_ENABLE_CONTROLDTCSETTING
		UdsApp_85CtrlDtcSet_Init();
	#endif /* end of #ifdef UDS_ENABLE_CONTROLDTCSETTING */ 	
}

void UDS_FN_TYPE UdsApp_10Dsc_generic_S3SeverTmrTimeoutEvtHandler(void)
{
	/* inform all of the other needed services that 
	  S3 Sever Timer Timout event ocurred
	*/

	#ifdef UDS_ENABLE_ECURESET
	    UDS_APP_ITF_INT_CMD_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
	#endif
	
	#ifdef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION
	    UDS_APP_ITF_INT_DTC_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER
	    UDS_APP_ITF_INT_DID_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
	#endif
	
	#ifdef UDS_ENABLE_SECURITYACCESS
	    UDS_APP_ITF_INT_SECU_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_COMMUNICATIONCONTROL   
	    UDS_APP_ITF_INT_COMCTRL_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
       #endif
	   
	#ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER   
	    UDS_APP_ITF_INT_E2BLK_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
       #endif

	#ifdef UDS_ENABLE_ROUTINECONTROL   
	    UDS_APP_ITF_INT_RTN_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
       #endif

	#ifdef UDS_ENABLE_LINKCONTROL   
	    UDS_APP_ITF_INT_LNKCTRL_HANDLE_S3_SVR_TMR_TO_EVT_ACTION;
	#endif

	#ifdef UDS_ENABLE_CONTROLDTCSETTING
		UdsApp_85CtrlDtcSet_Init();
	#endif /* end of #ifdef UDS_ENABLE_CONTROLDTCSETTING */ 	
}

#endif /* UDS_ENABLE_DIAGNOSTICSESSIONCONTROL */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
