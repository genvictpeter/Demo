/****************************************************************************
 	@Module       
 	@Filename      uds_srv11_ecureset.c
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





#ifdef UDS_ENABLE_ECURESET
/* static uint8_t rub_0x11EcuReset_Sid; */
static uint8_t rub_0x11EcuReset_SubFunc; 
static uint32_t rul_0x11EcuReset_Dly_Tmr;
Uint16 StEcuReset=FALSE; 


/* Sun-Function parameter for EcuReset(ISO15765-3 limited)
 *	resetType
 * 	0x01	POWER_ON_RESET(WachDogReset)
 * 	0x02	KEYOFFON_RESET
 * 	0x03	SOFT_RESET
 *	0x04	ENABLE_RAPIDPOWERDOWN_RESET
 *	0x05	DISABLE_RAPIDPOWERDOWN_RESET
 */

/* NRC for EcuReset
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 *	0x33	UDS_NRC_SECUTITYACCESSDENIED
 */

Std_UdsReturnType UDS_FN_TYPE UdsApp_EcuReset(Uds_APduData_t* pAPduInd, 
                                           Uds_APduData_t* pAPduResp )
{
	 uint8_t lub_response ;
	 lub_response = UDS_POSITIVE_RESPONSE;

	 /* check message length */
	 if (0x02u != (pAPduInd->msgLength))
   {
	     lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT ;
	 }
   else /* if (0x02u == (pAPduInd->msgLength)) */
   {
       UDS_DISABLE_ALL_INTERRUPTS();
         rub_0x11EcuReset_SubFunc = ((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7); 
       UDS_ENABLE_ALL_INTERRUPTS();
  
       /* here to check all of the supported sub functions.   */
       if ((rub_0x11EcuReset_SubFunc != UDS_C_ECURESET_SUBFUNC_POWERONRESET) 
          && (rub_0x11EcuReset_SubFunc != UDS_C_ECURESET_SUBFUNC_SOFTRESET))
       {
	   	     lub_response = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
       }
       else
       {
           UDS_DISABLE_ALL_INTERRUPTS();
             rul_0x11EcuReset_Dly_Tmr = UDS_C_ECURESET_POWER_DOWN_REL_TIME;		//80ms
           UDS_ENABLE_ALL_INTERRUPTS();
			(pAPduResp->msgLength) = 0x02u; /* whole of positive response length */
       }
   }  /* end of else if (0x02u == (pAPduInd->msgLength)) */
	 return lub_response;
}


void UDS_FN_TYPE UdsApp_11EcuRst_CyclicTskEntryPoint( void ) 
{

  uint8_t lub_EcuResetType = 0x00u; 
  
  if (rul_0x11EcuReset_Dly_Tmr > 0x00000001u) 
  {
      UDS_DISABLE_ALL_INTERRUPTS();
      rul_0x11EcuReset_Dly_Tmr--;
      UDS_ENABLE_ALL_INTERRUPTS();
  }  
  else if (rul_0x11EcuReset_Dly_Tmr == 0x00000001u) 
  {
      /* save the previous saved sub function into local variable
         then to clear it 
       */ 
      lub_EcuResetType = rub_0x11EcuReset_SubFunc;
      
      UDS_DISABLE_ALL_INTERRUPTS();
        rul_0x11EcuReset_Dly_Tmr--;
        rub_0x11EcuReset_SubFunc = 0x00u;
      UDS_ENABLE_ALL_INTERRUPTS();

      switch (lub_EcuResetType)
      {
        default :
              break;
        case UDS_C_ECURESET_SUBFUNC_POWERONRESET:
		case UDS_C_ECURESET_SUBFUNC_SOFTRESET:
            StEcuReset = TRUE;
              break;                   
      }  /* end of switch (lub_EcuResetType) */
    
  } /* end of else if (rul_0x11EcuReset_Dly_Tmr == 0x00000001u) */
  else 
  {
    
  }
       
}


#endif /* UDS_ENABLE_ECURESET */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
