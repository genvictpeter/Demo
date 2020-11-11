/****************************************************************************
 	@Module       
 	@Filename      uds_srv85_controldtcsetting.c
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



#ifdef UDS_ENABLE_CONTROLDTCSETTING
uint8_t rub_0x85CtrlDtcSetting_SubFunc;


/* Sun-Function parameter for ControlDTCSetting(ISO15765-3 limited)
 * 	DTCSettingType
	0x01	UDS_DTC_SETTING_START
	0x02	UDS_DTC_SETTING_STOP
 */

/* NRC for ControlDTCSetting
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 *	0x31	UDS_NRC_REQUESTOUTOFRANGE
 */

/* DTCSettingControlOptionRecord for ControlDTCSetting
 *	user Optional(ISO14229 9.9.2.3)
 */

Std_UdsReturnType UDS_FN_TYPE UdsApp_ControlDTCSetting(Uds_APduData_t* pAPduInd, 
                                                    Uds_APduData_t* pAPduResp )
{

   uint8_t lub_error = UDS_POSITIVE_RESPONSE;

     
   /* to handle the byte_1 sub function , except bit7 
      SuppressPositiveResponseMessgeIndicationBit 
    */
   UDS_DISABLE_ALL_INTERRUPTS();       
     rub_0x85CtrlDtcSetting_SubFunc = ((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7); 
   UDS_ENABLE_ALL_INTERRUPTS();  

   if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION)
   {
        if (TARGETADDR_FUNCTIONAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
            lub_error = UDS_POSITIVE_RESPONSE;
            pAPduResp->CurrSvcIsSupPosRspBitSet = 1u;
            pAPduResp->msgLength = 0x02u;
        }
        else {
            /* 0x85 ControlDtcSetting shall be only working 
            under non default diagnostic session mode 
            */
	        lub_error = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
        }
   }
	 else if ( (pAPduInd->msgLength) != 0x02u )
	 {
	     /* currently , optional DTCSettingControlOptionRecord 
	        is not supported temporarily 
	      */
	 	   lub_error = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT ;
	 }
	 else if(UDS_C_CTRLDTCSET_DTC_NO_RESPONSE == rub_0x85CtrlDtcSetting_SubFunc)
	 {
	 		lub_error = UDS_NO_RESPONSE;
	 }
	 else if ( UDS_C_CTRLDTCSET_DTC_STORE_ON  != rub_0x85CtrlDtcSetting_SubFunc &&
	           UDS_C_CTRLDTCSET_DTC_STORE_OFF != rub_0x85CtrlDtcSetting_SubFunc )		 	 
	 {
			 /* the DTC Setting parameter is not supported by the ECU */
			 lub_error = UDS_NRC_SUBFUNCTIONNOTSUPPORTED ;
	 }
   else
   {
       /* ok, all of the checking is passed, 
          prepare the positive response related data 
          the length of reponse is 2 bytes , currently , still not include sid byte
        */
       (pAPduResp->msgLength) = 0x02u;
         
   }
   
   return lub_error;

} /* end of Uds_ControlDTCSetting() */


/******************************************************************************
 * Name: Uds_85CtrlDtcSet_Init
 * Description: init function for DCT setting
 * Parameter:   None
 * Return: 		Nothing
 * Critical:    No.
 * Explanation: -.
 ******************************************************************************/
void UdsApp_85CtrlDtcSet_Init(void)
{
	/* after start-up DTC Manager has to set DTCs 
	   so the Control Dtc Setting Flag should be set to initial value ON 
	 */
	 UDS_DISABLE_ALL_INTERRUPTS();
	    rub_0x85CtrlDtcSetting_SubFunc = UDS_C_CTRLDTCSET_DTC_STORE_ON ;
   UDS_ENABLE_ALL_INTERRUPTS();
	 
}


uint8_t UdsApp_85CtrlDtcSet_Get_CurrDtcSettingFlg(void)
{
	 return rub_0x85CtrlDtcSetting_SubFunc ;
}





#endif /* UDS_ENABLE_CONTROLDTCSETTING */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
