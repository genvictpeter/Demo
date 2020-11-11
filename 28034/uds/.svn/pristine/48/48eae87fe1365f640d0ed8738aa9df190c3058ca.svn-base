/****************************************************************************
 	@Module       
 	@Filename      uds_srv27_securityaccess.c
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
#include "uds_pub.h"

#ifdef UDS_ENABLE_SECURITYACCESS  /* feature inclusion compilation option */

static uint8_t  rub_27SecuAcc_SeedLvl_11 ; /* store seed level 1 for previous request seed service*/
static uint8_t  rub_27SecuAcc_Prev_SavedSeedLvl1;

static uint8_t  rub_27SecuAcc_SecurityLvl_11 ;

static uint8_t  rub_27SecuAcc_Prev_SavedSecurityLvl ;

static uint8_t  rub_27SecuAcc_FailAccessAttemptCntr;

static uint32_t rul_27SecuAcc_FailAccessAttemptDlyTmr;

static T_UDS_27SECUACC_E2_DAT_TYPE rub_E2_RamImg_27SecuAcc_State;

static T_UDS_27SECUACC_E2_DAT_TYPE rub_Using_E2_RamImg_27SecuAcc_State;

static uint8_t rub_27SecuAcc_ConsecuReqSeedFlg;


static uint8_t raub_27SecuAcc_FrozenSeed[UDS_C_SECU_ACC_KEY_MAX_NUM] ;
static uint8_t raub_27SecuAcc_LocalComputeKey[UDS_C_SECU_ACC_KEY_MAX_NUM] ;

static uint32_t rul_SA_RandomGenerator_1msCounter; // = 0x00000000u;

/* the random integer generator constants definitions */

/* private functions declerations. */

static uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_secLvlSeedKeyHandle(Uds_APduData_t* pAPduInd, 
                                        Uds_APduData_t* pAPduResp,
                                        uint8_t        *i_pRub_secuLvl,
                                        uint8_t        *i_pRub_seedLvl,
                                        uint8_t         i_lub_accessMode,
                                        uint8_t         i_lub_accessLevel,
                                        uint8_t        *i_praub_27SecuAcc_FrozenSeed,
                                        uint8_t        *i_praub_27SecuAcc_LocalComputeKey,
                                        T_UDS_27SECUACC_COMPUTEKEY_LVL i_pComputeKeyLvlProc);
static void UDS_FN_TYPE UdsApp_27SecuAcc_EncryptFrmSeed2Key_SAL1( const uint8_t *lpub_seed, uint8_t *lpub_key, uint8_t lpub_accessLevel);
static uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_RandomGenerateSeed(uint8_t i_BytePosition); 

uint32_t saGetKey(const uint8_t *lpub_seed, uint8_t *lpub_key, uint32_t wConst);
uint32_t saGetKeyL1(const uint8_t *lpub_seed, uint8_t *lpub_key);

/* Sun-Function parameter for SecurityAccess(ISO15765-3 limited)
 * 	securityAccessType
 * 	0x01	requestSeed of security level 1
 *	0x02	sendKey of security level 1
 *	0x03	requestSeed of security level 3
 * 	0x04	sendKey of security level 3
 *	...
 *	0x5F	       requestSeed of security level 95
 *	0x60	sendKey of security level 95
 */

/* NRC for SecurityAccess
 * 	0x12	UDS_NRC_SUBFUNCTIONNOTSUPPORTED
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 * 	0x24	UDS_NRC_REQUESTSEQUENCEERROR
 * 	0x31	UDS_NRC_REQUESTOUTOFRANGE
 * 	0x35	UDS_NRC_INVALIDKEY
 * 	0x36	UDS_NRC_EXCEEDNUMBEROFATTEMPTS
 * 	0x37	UDS_NRC_REQUIREDTIMEDELAYNOTEXPIRED
 */
 
/* securityAccessDataRecord for SecurityAccess
 *	user Optional(ISO14229 9.4.2.3)
 */

/******************************************************************************
 * Name: Uds_SecurityAccess
 * Description: to process the 0x27 Security Access Request and give response 
 * Parameter:   pAPduInd  : input parameters.
                pAPduResp : output parameters.
 * Return: 		error code 
 * Critical:    Yes.
 * Explanation: This is the main function that manages the tester requests
 *              concerning the security access services.
 ******************************************************************************/
Std_UdsReturnType UDS_FN_TYPE UdsApp_SecurityAccess(Uds_APduData_t* pAPduInd, 
                                                    Uds_APduData_t* pAPduResp )
{
    uint8_t lub_accessMode;
    uint8_t lub_accessLevel;
    uint8_t lub_response;
    uint8_t lub_tmp_Req_IsFuncAddr;

    lub_response = UDS_POSITIVE_RESPONSE;
    lub_accessMode = ((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_NO_SPRB7);

	
    lub_accessLevel	= ((uint8_t)(lub_accessMode + 0x01u) >> 0x01u) ;
   
   
   lub_tmp_Req_IsFuncAddr = UDS_APP_ITF_IMP_GET_TP_CHNL();
       
   if (lub_tmp_Req_IsFuncAddr == TARGETADDR_FUNCTIONAL) /* Functional addressing */
   {
       lub_response = UDS_NRC_SERVICENOTSUPPORTED;
   }
   else if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION)
   {
       lub_response = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
   }
   else if ((pAPduInd->msgLength) < 0x02u)
   {
       /* min length of request must not be less than 2 */
       lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
   else if ((lub_accessMode != UDS_C_SECU_ACC_REQ_SEED_SAL1) && (lub_accessMode != UDS_C_SECU_ACC_SUB_KEY_SAL1))
   {
       /* request seeds must be odd sub-function , 
          sub-function must be in supported range
        */
       //lub_response = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
       lub_response = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
   }
   else if (((lub_accessMode == UDS_C_SECU_ACC_REQ_SEED_SAL11) || (lub_accessMode == UDS_C_SECU_ACC_REQ_SEED_SAL1))  &&
            (pAPduInd->msgLength != 0x02u) )
   {
       /* request seeds must be odd sub-function , length must be 2 for ALL SAL */
       lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
   else if (((lub_accessMode  == UDS_C_SECU_ACC_SUB_KEY_SAL11) || (lub_accessMode  == UDS_C_SECU_ACC_SUB_KEY_SAL1))  &&
            (pAPduInd->msgLength != 0x06u) )
   {
       /* submit key must be even sub-function , length must be 6 for all SAL */
       lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
   else
   {
   }
     
   if	(lub_response != UDS_POSITIVE_RESPONSE) 
   {      
     	 return lub_response	;
   } 
   else 
   {
   }
        
   switch (lub_accessLevel)
   {
       default:
            break;
       case UDS_C_SECU_ACC_SECU_LEVEL11:
	   case UDS_C_SECU_ACC_SECU_LEVEL1:
            lub_response =  UdsApp_27SecuAcc_secLvlSeedKeyHandle(pAPduInd,
                                                              pAPduResp,
                                                              &rub_27SecuAcc_SecurityLvl_11,
                                                              &rub_27SecuAcc_SeedLvl_11,
                                                              lub_accessMode,
                                                              lub_accessLevel,
                                                              raub_27SecuAcc_FrozenSeed,
                                                              raub_27SecuAcc_LocalComputeKey,
                                                              UdsApp_27SecuAcc_EncryptFrmSeed2Key_SAL1);
            break;
            

   } /* end of switch (lub_accessLevel) */


   if ((rub_27SecuAcc_FailAccessAttemptCntr >= UDS_C_SECU_ACC_MAX_ALLOW_FAIL_ATMPT_NUM) &&
       (rub_Using_E2_RamImg_27SecuAcc_State.m_bitmap.m_FAA_Flag == (uint8_t)FALSE) &&
       (rul_27SecuAcc_FailAccessAttemptDlyTmr == 0xFFFFFFFFu ||
        rul_27SecuAcc_FailAccessAttemptDlyTmr == 0x00000000u))
   {
       UDS_DISABLE_ALL_INTERRUPTS();  
         rub_Using_E2_RamImg_27SecuAcc_State.m_bitmap.m_FAA_Flag = (uint8_t)TRUE;
         rul_27SecuAcc_FailAccessAttemptDlyTmr = UDS_C_SECUACC_RETRY_DELAY_REL_TIME ; /*  40 * 250 = 10000ms */
       UDS_ENABLE_ALL_INTERRUPTS();
   }
   else
   {
   }

	 if (UDS_POSITIVE_RESPONSE                         != lub_response &&
	     UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT != lub_response)
	 {
	     rub_27SecuAcc_SeedLvl_11 = UDS_C_SECU_ACC_NO_SEED_VALUE ;
	 }
   else
   {

   }
	 return lub_response;
	 
}  /* end of Uds_SecurityAccess() */


/******************************************************************************
 * Name: Uds_27SecuAcc_secLvlSeedKeyHandle
 * Description: common process for handling seed and key
 * Parameter:   None
 * Return: 		Nothing
 * Critical:    No.
 * Explanation: No.
 ******************************************************************************/
static uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_secLvlSeedKeyHandle(Uds_APduData_t* pAPduInd, 
                                               Uds_APduData_t* pAPduResp,
                                               uint8_t        *i_pRub_secuLvl,
                                               uint8_t        *i_pRub_seedLvl,
                                               uint8_t         i_lub_accessMode,
                                               uint8_t         i_lub_accessLevel,
                                               uint8_t        *i_praub_27SecuAcc_FrozenSeed,
                                               uint8_t        *i_praub_27SecuAcc_LocalComputeKey,
                                               T_UDS_27SECUACC_COMPUTEKEY_LVL i_pComputeKeyLvlProc)

{
   uint8_t laub_keyR[UDS_C_SECU_ACC_KEY_MAX_NUM];
   uint8_t lub_response;

   lub_response = UDS_POSITIVE_RESPONSE;

   /* test if is request seed or submit key 
      if sub-function is odd number , it is request seeds. 
      otherwise, it is an even number, it is submit key
    */
   if (UDS_27SECUACC_SUBFUNC_IS_ODD_NUMBER(i_lub_accessMode) )
   {
       /* odd number = request seed */
       if(rul_27SecuAcc_FailAccessAttemptDlyTmr && 
          rul_27SecuAcc_FailAccessAttemptDlyTmr != 0xFFFFFFFFu)
       {
          /* if the delay timer of the 0x27 security Retry restriction is running */
          lub_response = UDS_NRC_REQUIREDTIMEDELAYNOTEXPIRED;
          /* reset the potential consecutive req seed flag to false */
          UDS_DISABLE_ALL_INTERRUPTS();
		        rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
	        UDS_ENABLE_ALL_INTERRUPTS();		  
          return lub_response;
       }
       else
       {
       }

	     /* store the length of response */
	     (pAPduResp->msgLength) = UDS_C_SECU_ACC_SUBMIT_KEY_LEN;
	       
	     /* first byte is the same like in request : sub function */
	     pAPduResp->pduData[0x01u] = pAPduInd->pduData[0x01u];
	       
	     /* prepare response */
	     if (i_lub_accessLevel == *i_pRub_secuLvl) //rub_27SecuAcc_SecurityLvl_11)
	     {   
	         /* the ECU was already unlocked */
	         pAPduResp->pduData[0x02u] = UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE ;
	         pAPduResp->pduData[0x03u] = UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE ;
	         pAPduResp->pduData[0x04u] = UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE ;
             pAPduResp->pduData[0x05u] = UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE ;
	     }
	     else /* if (i_lub_accessLevel != *i_pRub_secuLvl) */
	     {
           if (rub_27SecuAcc_Prev_SavedSeedLvl1 == UDS_C_SECU_ACC_NO_SEED_VALUE)
           {
	             /* freeze the current seed */
	           raub_27SecuAcc_FrozenSeed[0x00u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x00u); 
               raub_27SecuAcc_FrozenSeed[0x01u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x01u); 
               raub_27SecuAcc_FrozenSeed[0x02u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x02u); 
               raub_27SecuAcc_FrozenSeed[0x03u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x03u); 

           }
           else /* if (rub_27SecuAcc_Prev_SavedSeedLvl1 != UDS_C_SECU_ACC_NO_SEED_VALUE) */ //其他级别的访问，暂时不会用到
           {
               if (rub_27SecuAcc_ConsecuReqSeedFlg == (uint8_t)TRUE)
               {   
                   UDS_DISABLE_ALL_INTERRUPTS();
                     rub_27SecuAcc_FailAccessAttemptCntr++;
                   UDS_ENABLE_ALL_INTERRUPTS();
				   
               }
               else
               {
               }

               if (rub_27SecuAcc_Prev_SavedSeedLvl1 == i_lub_accessLevel &&
                   rub_27SecuAcc_ConsecuReqSeedFlg == (uint8_t)TRUE)
               {
               }
               else /* if (rub_27SecuAcc_Prev_SavedSeedLvl1 != i_lub_accessLevel) */
               {
	               /* freeze the current seed */
	               raub_27SecuAcc_FrozenSeed[0x00u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x00u); 
                   raub_27SecuAcc_FrozenSeed[0x01u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x01u); 
                   raub_27SecuAcc_FrozenSeed[0x02u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x02u); 
                   raub_27SecuAcc_FrozenSeed[0x03u]= UdsApp_27SecuAcc_RandomGenerateSeed(0x03u); 

               } /* end of else if (rub_27SecuAcc_Prev_SavedSeedLvl1 != i_lub_accessLevel) */

           }  /* end of else if (rub_27SecuAcc_Prev_SavedSeedLvl1 != UDS_C_SECU_ACC_NO_SEED_VALUE) */


	       /* store the seed level*/
	       *i_pRub_seedLvl = i_lub_accessLevel ;
           rub_27SecuAcc_Prev_SavedSeedLvl1 = i_lub_accessLevel ;

           pAPduResp->pduData[0x02u] = i_praub_27SecuAcc_FrozenSeed[0x00u];
           pAPduResp->pduData[0x03u] = i_praub_27SecuAcc_FrozenSeed[0x01u];
           pAPduResp->pduData[0x04u] = i_praub_27SecuAcc_FrozenSeed[0x02u];
           pAPduResp->pduData[0x05u] = i_praub_27SecuAcc_FrozenSeed[0x03u];

           /* set the potential consecutive req seed flag to true */
           UDS_DISABLE_ALL_INTERRUPTS();
		       rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)TRUE;
	       UDS_ENABLE_ALL_INTERRUPTS();		  
		   
	     } /* end of else if (i_lub_accessLevel != *i_pRub_secuLvl) */

   } /* end of if (UDS_27SECUACC_SUBFUNC_IS_ODD_NUMBER(i_lub_accessMode) ) */
   else	/* if (!UDS_27SECUACC_SUBFUNC_IS_ODD_NUMBER(i_lub_accessMode) ) */
   {
       /* even number = submit key */
       if (rub_27SecuAcc_FailAccessAttemptCntr >= UDS_C_SECU_ACC_MAX_ALLOW_FAIL_ATMPT_NUM)
       {
           lub_response = UDS_NRC_EXCEEDNUMBEROFATTEMPTS;
           /* reset the potential consecutive req seed flag to false */
           UDS_DISABLE_ALL_INTERRUPTS();
		         rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
	         UDS_ENABLE_ALL_INTERRUPTS();		  

           return lub_response;
       }
       else
       {
       }

       /* reset the potential consecutive req seed flag to false */
       UDS_DISABLE_ALL_INTERRUPTS();
	       rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
	     UDS_ENABLE_ALL_INTERRUPTS();		  

       /* if the access level of this submit key is matching the previous 
          request seed access level .
	      */
	     if (*i_pRub_seedLvl == i_lub_accessLevel &&
           rub_27SecuAcc_Prev_SavedSeedLvl1 == i_lub_accessLevel &&
           *i_pRub_secuLvl != i_lub_accessLevel &&
           rub_27SecuAcc_Prev_SavedSecurityLvl != i_lub_accessLevel)
	     {
	         /* a request for a seed with same level was done in the past */
	         laub_keyR[0x00u] = pAPduInd->pduData[0x02u] ;
	         laub_keyR[0x01u] = pAPduInd->pduData[0x03u] ;
	         laub_keyR[0x02u] = pAPduInd->pduData[0x04u] ;
             laub_keyR[0x03u] = pAPduInd->pduData[0x05u] ;

	         /* compute key by calling the encryption function pointer */
	         (i_pComputeKeyLvlProc)  ( i_praub_27SecuAcc_FrozenSeed, i_praub_27SecuAcc_LocalComputeKey, i_lub_accessLevel) ;

	         /* compare results is matching with every bytes */
	         if ((laub_keyR[0x00u] == i_praub_27SecuAcc_LocalComputeKey[0x00u]) &&
		         (laub_keyR[0x01u] == i_praub_27SecuAcc_LocalComputeKey[0x01u]) &&
		         (laub_keyR[0x02u] == i_praub_27SecuAcc_LocalComputeKey[0x02u]) &&
                 (laub_keyR[0x03u] == i_praub_27SecuAcc_LocalComputeKey[0x03u])
		          )
	         {
		           /* store the length of response */
		           (pAPduResp->msgLength) = 0x02u ;
		               
		           /* first byte is the same like in request : sub function */
	             pAPduResp->pduData[0x01u] = pAPduInd->pduData[0x01u];
		               
		           /* set the security level */
		           *i_pRub_secuLvl = i_lub_accessLevel ;
               if (rub_27SecuAcc_Prev_SavedSecurityLvl != i_lub_accessLevel)
               {
                   switch (rub_27SecuAcc_Prev_SavedSecurityLvl)
                   {
                       default:
                            break;
                       case 0x11:
                            rub_27SecuAcc_SecurityLvl_11 = UDS_C_SECU_ACC_SECU_LEVEL11_LOCKED;
                            break;

                   }

               }
               else
               {

               }
               rub_27SecuAcc_Prev_SavedSecurityLvl = i_lub_accessLevel ;

		           /* reset seed */
               rub_27SecuAcc_SeedLvl_11 = UDS_C_SECU_ACC_NO_SEED_VALUE ;

	         }
	         else /* if ((laub_keyR[0u] != i_praub_27SecuAcc_LocalComputeKey[0u]) || ... */
	         {
                   UDS_DISABLE_ALL_INTERRUPTS();
                     rub_27SecuAcc_FailAccessAttemptCntr++;
                   UDS_ENABLE_ALL_INTERRUPTS();
			   
               *i_pRub_seedLvl = UDS_C_SECU_ACC_NO_SEED_VALUE ;

		           /* prepare negative response */
               if (rub_27SecuAcc_FailAccessAttemptCntr >= UDS_C_SECU_ACC_MAX_ALLOW_FAIL_ATMPT_NUM)
               {
                   lub_response = UDS_NRC_EXCEEDNUMBEROFATTEMPTS;
               }
               else
               {
                   lub_response = UDS_NRC_INVALIDKEY ;
               }
	         } /* end of else // if ((laub_keyR[0u] != raub_27SecuAcc_LocalComputeKey[0u]) || ... */
	     } /* end of if (*i_pRub_seedLvl == i_lub_accessLevel ) */
	     else /* if (*i_pRub_seedLvl != i_lub_accessLevel ) */
	     {   
	         /* invalid security level ( doesn't concurr with seed request ) 
              the failure retry counter will only be increased a complete
              request seed + send key sequence , if sequence is not correct
              only return 0x24 requestSequenceError , no counter increasing will be done.
              prepare negative response 
            */
	         lub_response = UDS_NRC_REQUESTSEQUENCEERROR ;
	     } /* end of else if (*i_pRub_seedLvl != i_lub_accessLevel ) */
   } /* end of else	//if (!SECU_IS_ODD_NUMBER(i_lub_accessMode) ) */

   return lub_response;

} /* end of FAR_FCT T_UBYTE disecu_secLvlSeedKeyHandle() */


/******************************************************************************
 * Name: Uds_27SecuAcc_init
 * Description: Initialize the security access values
 * Parameter:   None
 * Return: 		Nothing
 * Critical:    No.
 * Explanation: No.
 ******************************************************************************/
void UDS_FN_TYPE UdsApp_27SecuAcc_Init(void)
{
   rul_SA_RandomGenerator_1msCounter = 0x00000000u;

   UdsApp_27SecuAcc_SwitchDiagSessionInit();
   
   UDS_DISABLE_ALL_INTERRUPTS();
	   /* init counter */
	   rub_27SecuAcc_FailAccessAttemptCntr = 0x00u;
		  
     /* init the potential consecutive req seed flag to false		  */
	 	 rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
	 UDS_ENABLE_ALL_INTERRUPTS();		  

   /* this should check the FAA_Flag */
   /* before the eeprom driver is used, this is initialized manually
    */
   rub_E2_RamImg_27SecuAcc_State.m_bitmap.m_FAA_Flag = (uint16_t)FALSE;
   rub_E2_RamImg_27SecuAcc_State.m_bitmap.m_FAA_Cntr = (uint16_t)0x0000u;
   rub_Using_E2_RamImg_27SecuAcc_State = rub_E2_RamImg_27SecuAcc_State;

   /* stop timer */
   rul_27SecuAcc_FailAccessAttemptDlyTmr = 0xFFFFFFFFu ;

}


void  UDS_FN_TYPE UdsApp_27SecuAcc_SwitchDiagSessionInit(void)
{
	/* no seed request before */
	rub_27SecuAcc_SeedLvl_11      = UDS_C_SECU_ACC_NO_SEED_VALUE ;

    rub_27SecuAcc_Prev_SavedSeedLvl1 = UDS_C_SECU_ACC_NO_SEED_VALUE ;
    
	/* after init the ECU is locked */
	rub_27SecuAcc_SecurityLvl_11      = UDS_C_SECU_ACC_SECU_LEVEL11_LOCKED ;

    rub_27SecuAcc_Prev_SavedSecurityLvl = UDS_C_SECU_ACC_SECU_LEVEL11_LOCKED;

    raub_27SecuAcc_FrozenSeed[0x00u]   = 0x00u;
    raub_27SecuAcc_FrozenSeed[0x01u]   = 0x00u;
    raub_27SecuAcc_FrozenSeed[0x02u]   = 0x00u;
    raub_27SecuAcc_FrozenSeed[0x03u]   = 0x00u;


	raub_27SecuAcc_LocalComputeKey[0x00]  = 0x00;
	raub_27SecuAcc_LocalComputeKey[0x01]  = 0x00;
	raub_27SecuAcc_LocalComputeKey[0x02]  = 0x00;
	raub_27SecuAcc_LocalComputeKey[0x03]  = 0x00;
	
}


/******************************************************************************
 * Name: Uds_27SecuAcc_timer
 * Description: timer manager for the security
 * Parameter:   None
 * Return: 		Nothing
 * Critical:    No.
 * Explanation: No.
 ******************************************************************************/
void UDS_FN_TYPE UdsApp_27SecuAcc_CyclicTskEntryPoint(void)
{
   
   if (rul_SA_RandomGenerator_1msCounter < 0xFFFFFFFFu) 
   {
       rul_SA_RandomGenerator_1msCounter++;
   } 
   else 
   {
       rul_SA_RandomGenerator_1msCounter = 0x00000000u;
   }
    
   if(rul_27SecuAcc_FailAccessAttemptDlyTmr &&
      rul_27SecuAcc_FailAccessAttemptDlyTmr != 0xFFFFFFFFu)
   {
      UDS_DISABLE_ALL_INTERRUPTS();
        rul_27SecuAcc_FailAccessAttemptDlyTmr --; 
        /* reset the potential consecutive req seed flag to false */
        rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
      UDS_ENABLE_ALL_INTERRUPTS();	  

   }
   else
   {
   }

   if (rul_27SecuAcc_FailAccessAttemptDlyTmr == 0x00000000u)
   {
     if (rub_27SecuAcc_FailAccessAttemptCntr > 0x00u)
     {      
          UDS_DISABLE_ALL_INTERRUPTS();
            rub_27SecuAcc_FailAccessAttemptCntr--;
          UDS_ENABLE_ALL_INTERRUPTS();

     }
     else
     {
     }

     /* init the potential consecutive req seed flag to false
        after security delay 10s timer is expired.
      */
     UDS_DISABLE_ALL_INTERRUPTS();     
	     rub_27SecuAcc_ConsecuReqSeedFlg = (uint8_t)FALSE;
       rul_27SecuAcc_FailAccessAttemptDlyTmr = 0xFFFFFFFFu ; 
     UDS_ENABLE_ALL_INTERRUPTS();	  
	 
   }
   else
   {
   }

   if (rub_27SecuAcc_FailAccessAttemptCntr < UDS_C_SECU_ACC_MAX_ALLOW_FAIL_ATMPT_NUM &&
       (rul_27SecuAcc_FailAccessAttemptDlyTmr == (uint32_t)0x00000000u ||
        rul_27SecuAcc_FailAccessAttemptDlyTmr == (uint32_t)0xFFFFFFFFu))
   {
        UDS_DISABLE_ALL_INTERRUPTS();   
          rub_Using_E2_RamImg_27SecuAcc_State.m_bitmap.m_FAA_Flag = (uint8_t)FALSE;
	      UDS_ENABLE_ALL_INTERRUPTS();   
   }
   else
   {

   }

   if ((rub_E2_RamImg_27SecuAcc_State.uw != rub_Using_E2_RamImg_27SecuAcc_State.uw) )

   {
       rub_Using_E2_RamImg_27SecuAcc_State.uw = rub_E2_RamImg_27SecuAcc_State.uw;
       /*  this condition can not be applicable temporarily
       if ((!UDS_APP_ITF_IMP_GET_OVER_VOLTAGE_FAIL() ) &&
           (!UDS_APP_ITF_IMP_GET_UNDER_VOLTAGE_FAIL())) 
        */
       {
        
           UDS_APP_ITF_IMP_SET_E2_WRITE_FLAG(UDS_APP_ITF_IMP_GET_E2_IDX_27SECUACC_ST);
       } 
       /* else  */
       {
       
            
       }
   }
   else
   {


   }

}

void UDS_FN_TYPE UdsApp_27SecuAcc_Pending(void)
{
  /* dummy function , reserved for future */

}

void UDS_FN_TYPE UdsApp_27SecuAcc_Pend_Overtime(void)
{
   /* dummy function , reserved for future. */
}


static uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_RandomGenerateSeed(uint8_t i_BytePosition) 
{
   uint8_t lub_tmpRandom = 0x00u;
    
   lub_tmpRandom = (uint8_t)((rul_SA_RandomGenerator_1msCounter >> 
                           (i_BytePosition * 0x08u)) & 0xFFu); 
   if (lub_tmpRandom == 0x00u ||
       lub_tmpRandom == 0xFFu) 
   {
       switch(i_BytePosition) 
       {
         default: 
                lub_tmpRandom = 0x36u;
                break;
         case 0: 
                lub_tmpRandom = 0x78u;
                break;
         case 1: 
                lub_tmpRandom = 0x15u;
		  break;		
         case 2: 
                lub_tmpRandom = 0x64u;
                break;
         case 3: 
                lub_tmpRandom = 0x29u;
                break;            
       }
   }
   else 
   {
              
   }
      
   return lub_tmpRandom;   
} /* end of UdsApp_27SecuAcc_RandomGenerateSeed() */

static void UDS_FN_TYPE UdsApp_27SecuAcc_EncryptFrmSeed2Key_SAL1( const uint8_t *lpub_seed, uint8_t *lpub_key, uint8_t lpub_accessLevel)
{	
  /* simplest example encrypt algorithm, should be updated according to customer's requirement 
      in the future. 
   */
    if (lpub_accessLevel == UDS_C_SECU_ACC_SECU_LEVEL1) {
        saGetKeyL1(lpub_seed,lpub_key);
    }
    else {
        saGetKey(lpub_seed,lpub_key,0xBBE);
    }  
}



uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_GetCurrSecurityLevelStatus(uint8_t i_lub_SAL2Read) 
{
   uint8_t lub_CurrSecurityLevel = UDS_C_SECU_ACC_SECU_LEVEL11_LOCKED;
   switch(i_lub_SAL2Read) 
   {
       default: 
            break;
       case UDS_C_SECU_ACC_SECU_LEVEL11: 
            lub_CurrSecurityLevel  =  rub_27SecuAcc_SecurityLvl_11; 
            break;
              
   }
   return lub_CurrSecurityLevel;  
}

uint32_t saGetKey(const uint8_t *lpub_seed, uint8_t *lpub_key, uint32_t wConst)
{
         uint8_t Const[4];
         uint8_t Seed2[4];
         uint8_t Key1[4];
         uint8_t Key2[4];
         uint8_t Key[4];
         uint8_t i;
         uint8_t j = 3;
         //uint32_t wKey;


         Const[3] = (uint8_t)((wConst & 0xff000000) >> 24);
         Const[2] = (uint8_t)((wConst & 0x00ff0000) >> 16);
         Const[1] = (uint8_t)((wConst & 0x0000ff00) >> 8);
         Const[0] = (uint8_t)(wConst & 0x000000ff);


         
         for (i = 0; i < 4; i++)
         {
             Key1[i] = lpub_seed [i] ^ Const[i];
             Seed2[i] = lpub_seed [j];
             Key2[i] = Seed2[i] ^ Const[i];
             Key[i] = (uint8_t)(Key1[i] + Key2[i]+0x05);
             j--;
         }


		lpub_key[0] = Key[0]&0xFF;
		lpub_key[1] = Key[1]&0xFF;
		lpub_key[2] = Key[2]&0xFF;
		lpub_key[3] = Key[3]&0xFF;
		
   return 0;
}

uint32_t saGetKeyL1(const uint8_t *lpub_seed, uint8_t *lpub_key)
{
        Uint32 seed,key;

        seed = ((Uint32)lpub_seed[0] << 24) 
             + ((Uint32)lpub_seed[1] << 16)
             + ((Uint32)lpub_seed[2] << 8)
             +  (Uint32)lpub_seed[3];

        key = (((seed>>4) ^ seed) <<3) ^ seed;

		lpub_key[0] = (key >> 24) & (Uint32)0xFF;
		lpub_key[1] = (key >> 16) & (Uint32)0xFF;
		lpub_key[2] = (key >> 8)  & (Uint32)0xFF;
		lpub_key[3] =  key        & (Uint32)0xFF;
		
   return 0;
}

#endif /* UDS_ENABLE_SECURITYACCESS */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
