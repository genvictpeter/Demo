/****************************************************************************
 	@Module       
 	@Filename      uds_srv14_cleardiaginformation.c
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



#include "main.h"
#include "uds_target.h"
#include "uds_confpriv.h"
#include "uds_confdefs.h"
#include "uds_priv.h"
#include "uds_inf.h"
#include "Error.h"
#include "EepromManage.h"




#ifdef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION
static uint8_t rub_didtc_pending;
static uint8_t rub_WhichTypeDtc2Clear;
static uint8_t rub_DtcHighByte2Clear;
static uint8_t rub_DtcMiddleByte2Clear;
static uint8_t rub_DtcLowByte2Clear;

static Uds_APduData_t* pSavedAPduResp;

/* private functions declerations */
static uint8_t UDS_FN_TYPE UdsApp_14ClrDiagInfor_ClearDtcAction(void); 



/* Sun-Function parameter for ClearDiagnosticInformation(ISO15765-3 limited)

 */

/* NRC for EcuReset
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 *	0x33	UDS_NRC_SECUTITYACCESSDENIED
 */

Std_UdsReturnType UDS_FN_TYPE UdsApp_ClearDiagnosticInformation(Uds_APduData_t* pAPduInd, 
                                                             Uds_APduData_t* pAPduResp )
{ 
	 uint8_t lub_response = UDS_POSITIVE_RESPONSE;
	 
     if (0x04u != (pAPduInd->msgLength))
	 {
	     /* 0x14 ClearDiagnosticInformation have the fixed length: 4 bytes 
	      */
		   lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
	 } 
	 else /* if (0x04u == (pAPduInd->msgLength)) */
	 {
	  
       /* to read in 3 bytes DTC identifiers , which will be cleared. 
        */
       rub_DtcHighByte2Clear   = (pAPduInd->pduData[0x01u]);
       rub_DtcMiddleByte2Clear = (pAPduInd->pduData[0x02u]);
       rub_DtcLowByte2Clear    = (pAPduInd->pduData[0x03u]);
  
       /* to decide which kind of dtc type will be cleared. 
          according to value range : 
          1. DTCHighByte   == 0xFFu &&
             DTCMiddleByte == 0xFFu &&
             DTCLowByte    == 0xFFu 
             i.e. 3 bytes 0xFFu, means to clear all items in all of groups of DTCs
          2. 0x00u < DTCHighByte   < 0xFFu &&
             DTCMiddleByte == 0xFFu &&
             DTCLowByte    == 0xFFu 
             i.e. 1st byte is not 0xFFu , rest 2 bytes 0xFFu, 
                means to clear all items in the specified group of DTCs, 
                which is indicated by 1st byte value 
          3. 0x00u < DTCHighByte   < 0xFFu &&
             0x00u < DTCMiddleByte < 0xFFu &&
             0x00u < DTCLowByte    < 0xFFu 
             i.e. 3 bytes are not 0x00u nore 0xFFu, 
                means to clear a single specified DTC, 
                which is indicated by these 3 bytes value, 
                given it is supported by ECU currently 
        */
       if (rub_DtcHighByte2Clear   == 0xFFu &&
           rub_DtcMiddleByte2Clear == 0xFFu &&
           rub_DtcLowByte2Clear    == 0xFFu ) 
       {
           rub_WhichTypeDtc2Clear = UDS_C_CLRDTC_CLRTYP_ALL_DTCS;	//Only Suport Clear All Group
        
       } 
	   else
	   {
           rub_WhichTypeDtc2Clear = 0x00u;
	   	   lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       }   

	     if (lub_response == UDS_POSITIVE_RESPONSE)
	     {
	     	 rub_didtc_pending = (uint8_t)FALSE;

	         lub_response = UdsApp_14ClrDiagInfor_ClearDtcAction();

	         if (lub_response == UDS_POSITIVE_RESPONSE)
	         {
	             pSavedAPduResp = pAPduResp;
	             lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING ;
	             rub_didtc_pending = (uint8_t)TRUE ;
               /* positive rsp will only have one byte : 0x54 = 0x14 + 0x40 
                */
                 //(pAPduResp->msgLength) = 0x01u; 
             }
	         else
	         {
	         }
	     }
	     else
	     {
	     } /* end of else if (lub_response != UDS_POSITIVE_RESPONSE) */ 
	 } /* end of else // if (0x04u == (pAPduInd->msgLength)) */
	 
	 return lub_response ;
	  
} /* end of UdsApp_14ClrDiagInfor_ReqSpecialProcess() */


static uint8_t UDS_FN_TYPE UdsApp_14ClrDiagInfor_ClearDtcAction(void) 
{
	 uint8_t lub_response = UDS_POSITIVE_RESPONSE;
      
   switch (rub_WhichTypeDtc2Clear) 
   {
       default: 
            /* some mistake happened in this case */
            lub_response = UDS_NRC_REQUESTOUTOFRANGE; 
            break;
       /* after dtc manager is added , the below case 
          can be finished.   
        */
       case UDS_C_CLRDTC_CLRTYP_ALL_DTCS:
            UDS_ITF_IMP_CLR_ALL_DTCS();
            break;
           
    
   } /* end of  switch (rub_WhichTypeDtc2Clear) */
   
   return lub_response;
} /* end of UdsApp_14ClrDiagInfor_ClearDtcAction() */


void UDS_FN_TYPE UdsApp_14ClrDiagInfor_CyclicTskEntryPoint(void) 
{
   uint8_t lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING; //UDS_POSITIVE_RESPONSE;
   
   /* the pending flag must be check first, so to make sure the pSavedAPduResp will not be null pointer 
    */

   if (rub_didtc_pending == (uint8_t)TRUE) 
   {     
      if (UDS_ITF_IMP_GET_CLR_DTC_ACT_FINISHED() == TRUE) 
      {
          rub_didtc_pending = FALSE;
          /* positive rsp will only have one byte : 0x54 = 0x14 + 0x40 
           */
          lub_response = UDS_POSITIVE_RESPONSE; 
          (pSavedAPduResp->msgLength) = 0x01u; 
          pSavedAPduResp->pduData[0x00u] = 0x14u; /*SID should be response now */ 
    	  Uds_generic_SendResp(pSavedAPduResp, lub_response);    
      }   
      else 
      {
    		/* rub_didtc_pending = TRUE; */ 
      }
   }
   else
   {
   	   	
   }
}

void UDS_FN_TYPE UdsApp_14ClrDiagInfor_Pend_Overtime(void) 
{
   uint8_t lub_response = UDS_NRC_NORESPONSEFROMSUBNETCOMPONENT; 

       rub_didtc_pending = FALSE;
	/* (pSavedAPduResp->msgLength) = 0x01u; */ 
      pSavedAPduResp->pduData[0x00u] = 0x14u; /*SID should be response now */ 
    	Uds_generic_SendResp(pSavedAPduResp, lub_response);    
   
 }

void UDS_FN_TYPE UdsApp_14ClrDiagInfor_Init(void) 
{
   rub_didtc_pending = (uint8_t)FALSE;
}

uint8_t UDS_FN_TYPE UdsApp_14ClrDiagInf_Pending(void)
{
    uint8_t lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;

    if (rub_didtc_pending == TRUE) {     
        // Check if clear diag information has already finished
        if (FlagClrErr == FALSE) {
            //
            rub_didtc_pending = FALSE;
            
            //
            lub_response = UDS_POSITIVE_RESPONSE;
            (pSavedAPduResp->msgLength) = 1;
            pSavedAPduResp->pduData[0] = 0x14;
        }
        else {
            lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
        }
    }

    return lub_response;
}

#endif /* UDS_ENABLE_CLEARDIAGNOSTICINFORMATION */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
