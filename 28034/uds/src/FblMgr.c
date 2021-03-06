//****************************************************************************/
// @Module       
// @Filename      FblMgr.c
// @Project       BQApp
//----------------------------------------------------------------------------
// @Controller    TI 28034
//
// @Compiler      V5.211
//
// @Codegenerator CCS 3.3
//
// @Description   
//
//----------------------------------------------------------------------------
// @Date          12/19/2014
//
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

/****************************************************************************/

#include "FblMgr.h"
#include "CAN.h"
#include "uds_target.h"
#include "FlashDrv_ExtItf.h"




#ifdef __cplusplus
    extern "C" {
#endif

    
/* default value setting after each POR for FblMgrSwImgState struct 
                                                                    	
 */
static T_FBL_MGR_SW_IMG_STATE rul_FblMgr_SwImgState; // = {FBL_SW_INIT_RUNNING_STATE, /* m_FblSwImgRunningState  */
                                                     //  TRUE,                     /* m_BootSwInFlashValidFlg */
                                                     //  FALSE,                    /* m_BootSwInRamValidFlg   */
                                                     //  FALSE,                    /* m_AppSwInFlashValidFlg  */
                                                     //  FALSE};                   /* m_AppDatInFlashValidFlg */

const  uint8_t  caub_PendProgFlag[0x08u] = {'F','B','L','d','n','r','e','q'};
const  uint8_t  caub_AswVldOkFlag[0x08u] = {'A','s','w','d','a','t','o','k'};
const  uint8_t  caub_AswInvalidFlag[0x08u] = {'A','s','w','i','n','v','l','d'};

const uint32_t  caul_PendProgFlag[0x02u] = { 0x644C4246u, 0x7165726Eu };
const uint32_t  caul_AswVldOkFlag[0x02u] = { 0x64777341u, 0x6B6F7461u };
const uint32_t  caul_AswInvalidFlag[0x02u] = { 0x69777341u, 0x646C766Eu };

static uint32_t  rul_PendRePrgFlgAswVldFlag[0x10u];

static uint8_t   rub_FblMgr_State; // = FBLMGR_C_ST_IDLE;
static uint32_t *rup_PendProgFlgStartAddr; // = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR);
/* static uint32_t *rup_AswInvldFlgStartAddr; // = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR + 0x20u); */

//static const uint32_t *cup_PendProgFlgStartAddr = (uint32_t *)(FBLMGR_C_CACHED_PENDING_PROG_FLG_ADDR);




static T_FP_ASW_JUMP_ENTRYPOINT  rup_AppSwStartAddr; // = NULL;
static uint32_t   rul_AppSwStartAddrValue; // = 0x00000000u;

static uint32_t  lul_RdProgFlgWord1Value; 
static uint32_t  lul_RdProgFlgWord2Value; 
static uint32_t  lul_RdAswVldFlgWord1Value; 
static uint32_t  lul_RdAswVldFlgWord2Value; 
static uint32_t  lul_RdAswInVldFlgWd1Value; 
static uint32_t  lul_RdAswInVldFlgWd2Value; 

static uint32_t  lul_RdCheckSumWordValue; 
static uint64_t  lull_CalcuCheckSumWordValue; // = 0x0000000000000000u;


uint8_t rub_E2RamImg_BootAswModeMngt[0x08u]; 
const   uint8_t rub_E2RomImg_BootAswModeMngt[0x08u] = {'F','B','L','d','n','n','o','n'};

const  uint8_t  rub_FblMgr_StayInBootSpecificMsg[0x08u] = {'J','S','M','S','B','O','O','T'};
const  uint8_t  rub_FblMgr_StayInBootSpecificMsgDcm[0x08u] = {74,83,77,83,66,79,79,84};

uint32_t rul_FblMgr_ResetStayInBootWindowTimer; // = FBLMGR_C_RESET_STAY_IN_BOOT_WIN_TMR_ABS_VALUE/FBLMGR_C_CYCLIC_TASK_PERIOD;

uint8_t  rub_FblMgr_StayInBootMsgIsReceived; // = FALSE;








// static void FblMgr_RdChkPendProgFlgAswVldFlg(void);
//static uint8_t FblMgr_ChkRamBootSwPendProgFlgAndAswVldFlg(void);

static uint8_t FblMgr_ChkPendProgFlgAndAswVldFlg(void);

void FblMgr_Init(void)
{
	//uint8_t i;
	//rul_FblMgr_SwImgState.m_FblSwImgRunningState = FBL_SW_INIT_RUNNING_STATE; /* m_FblSwImgRunningState  */
	rul_FblMgr_SwImgState.m_BootSwInFlashValidFlg = TRUE;                     /* m_BootSwInFlashValidFlg */
	rul_FblMgr_SwImgState.m_BootSwInRamValidFlg = FALSE;                    /* m_BootSwInRamValidFlg   */
	rul_FblMgr_SwImgState.m_AppSwInFlashValidFlg = FALSE;                    /* m_AppSwInFlashValidFlg  */
	rul_FblMgr_SwImgState.m_AppDatInFlashValidFlg = FALSE;                   /* m_AppDatInFlashValidFlg */


	rub_FblMgr_State = FBLMGR_C_ST_IDLE;
	rup_PendProgFlgStartAddr = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR);
	/* rup_AswInvldFlgStartAddr = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR + 0x20u); */



	rup_AppSwStartAddr = NULL;
	rul_AppSwStartAddrValue = 0x00000000u;

	lull_CalcuCheckSumWordValue = 0x0000000000000000u;



	rul_FblMgr_ResetStayInBootWindowTimer = FBLMGR_C_RESET_STAY_IN_BOOT_WIN_TMR_ABS_VALUE/FBLMGR_C_CYCLIC_TASK_PERIOD;

	rub_FblMgr_StayInBootMsgIsReceived = FALSE;


}

uint8_t  FblMgr_CheckFblStayInBootSpecificMsg(uint8_t *i_lup_CanMsgDatPtr)
{
    uint8_t i; 
    uint8_t lub_FblMgrStayInBootSpecMsgIsReceived = TRUE;
	uint8_t * lup_DestCanMsgDatPtr = i_lup_CanMsgDatPtr; 
	const uint8_t * lup_SrcCanMsgDatPtr = &rub_FblMgr_StayInBootSpecificMsg[0x00u]; 

    if (rul_FblMgr_ResetStayInBootWindowTimer == 0x00u)
    {
        lub_FblMgrStayInBootSpecMsgIsReceived = FALSE;
     	return lub_FblMgrStayInBootSpecMsgIsReceived;		   
    }
	else
	{
	}
	
	for (i = 0x00; i < 0x08u; i++)
	{
	      if ((*lup_DestCanMsgDatPtr)  != (*lup_SrcCanMsgDatPtr))
	      {
	             lub_FblMgrStayInBootSpecMsgIsReceived = FALSE;
	             break;
	      }
	      else
	      {
	      }
	}

       if (lub_FblMgrStayInBootSpecMsgIsReceived == TRUE)
       {
	     rub_FblMgr_StayInBootMsgIsReceived = TRUE;
       }
	else
	{
	     rub_FblMgr_StayInBootMsgIsReceived = FALSE;	
	}
       return lub_FblMgrStayInBootSpecMsgIsReceived;
	   
}




T_FBL_SW_IMG_RUNNING_STATE FblMgr_GetCurrSwImgRunningState(void)
{
	return (rul_FblMgr_SwImgState.m_FblSwImgRunningState);
	
}

void FblMgr_SetCurrSwImgRunningState(T_FBL_SW_IMG_RUNNING_STATE i_SwImgToSet)
{
	
   FBLMGR_DISABLE_ALL_INTERRUPTS();
       rul_FblMgr_SwImgState.m_FblSwImgRunningState = i_SwImgToSet;
   FBLMGR_ENABLE_ALL_INTERRUPTS();
	
}

uint8_t FblMgr_CurrRunningSwImgCompare(T_FBL_SW_IMG_RUNNING_STATE i_SwImgToCompared)
{
	 if ((rul_FblMgr_SwImgState.m_FblSwImgRunningState) == 
	        i_SwImgToCompared)
	 {
	 	 return TRUE;
	 }
	 else
	 {
	 	 return FALSE;
	 }
	 
}

void FblMgr_ChkBootSwInRam(void)
{

       if (rul_FblMgr_SwImgState.m_FblSwImgRunningState == BOOT_SW_IN_RAM_DN_FINISHED)       
       {
          // rup_PendProgFlgStartAddr =  (uint32_t *)(FBLMGR_ITF_IMP_GET_RAM_BOOT_SW_START_ADDR);
           
	       rub_FblMgr_StayInBootMsgIsReceived = FALSE;
		
	       // FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v2();
	       FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v3();
       }
       else
       {
       }

}

void FblMgr_ChkAppSwInFlash(void)
{

       if (rul_FblMgr_SwImgState.m_FblSwImgRunningState == BOOT_SW_IN_FLASH_RUNNING)       
       {
           rup_PendProgFlgStartAddr =  (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR);
           
	       rub_FblMgr_StayInBootMsgIsReceived = FALSE;
 		
	       FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v2(); 	   
       }
       else
       {
       }

}

void FBLMgr_MainCyclicTaskEntryPoint(void)
{
       if (rul_FblMgr_ResetStayInBootWindowTimer > 0x00u)
       {
           rul_FblMgr_ResetStayInBootWindowTimer--;
           FblMgr_InitMainEntrypoint();
		   
       }
	else
	{
	}
}

void FblMgr_InitStartStayInBootTimer(void)
{
      rul_FblMgr_ResetStayInBootWindowTimer = FBLMGR_C_RESET_STAY_IN_BOOT_WIN_TMR_ABS_VALUE/FBLMGR_C_CYCLIC_TASK_PERIOD; 

}

void FblMgr_InitMainEntrypoint(void)
{      
     	 
     #ifdef SFBL_BOOT_SW_BUILD  
    uint8_t   lub_ReturnCode1 = FALSE;

     /*  to start the stayinBootSw 
	*/
     lub_ReturnCode1 = FblMgr_ChkPendProgFlgAndAswVldFlg();

     switch(lub_ReturnCode1)
     {
         default:    	
         case FBLMGR_C_ST_IDLE:                               /* (uint8_t)0x00u */
         case FBLMGR_C_ST_PENDING_PROG_REQ:     /*  (uint8_t)0x01u */
         case FBLMGR_C_ST_ASW_DATA_VLD_OK:      /*  (uint8_t)0x03u */
         case FBLMGR_C_ST_ASW_DATA_INVLD:         /*  (uint8_t)0x04u */
         case FBLMGR_C_ST_ASW_DATA_CS_FAIL:      /*  (uint8_t)0x05u */
		 	
		    break;  	
         case FBLMGR_C_ST_BOOT_MODE_UPDATE:     /* (uint8_t)0x02u */
                  // lub_ReturnCode2 = FblMgr_SetPendProgFlgOnAndAswVldFlgOff();
		    break;	
         case FBLMGR_C_ST_ASW_DATA_CS_OK:       /*  (uint8_t)0x06u  */
	       break;   
     } /* end of switch(lub_ReturnCode) */
     #endif /* end of      #ifdef SFBL_BOOT_SW_BUILD */	
}


uint8_t FblMgr_ChkIfProgFlgUpdateIsNeeded(void)
{
     uint8_t   lub_ReturnCode = FALSE;
     lub_ReturnCode = FblMgr_ChkPendProgFlgAndAswVldFlg();
     if (lub_ReturnCode != FBLMGR_C_ST_PENDING_PROG_REQ)
     {
          lub_ReturnCode = TRUE;
     }
     else
     {
     }
     return lub_ReturnCode;	 
}


void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_ForFlash(void)
{
     uint8_t   lub_StartAddrByte[24u]; 
	   
     /* state in the boot mode */
	 rub_FblMgr_State = FBLMGR_C_ST_IDLE; //FBLMGR_C_ST_PENDING_PROG_REQ;


        rup_PendProgFlgStartAddr = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR - 0x10u); 
	 lul_RdAswInVldFlgWd1Value = *rup_PendProgFlgStartAddr;
	 rup_PendProgFlgStartAddr++; 
        lul_RdAswInVldFlgWd2Value = *rup_PendProgFlgStartAddr; 

        if (lul_RdAswInVldFlgWd1Value  != 0xFFFFFFFFu ||
	     lul_RdAswInVldFlgWd2Value  != 0xFFFFFFFFu )
        {
             rub_FblMgr_State = FBLMGR_C_ST_ASW_DATA_INVLD;
	         return ;
        }
        else
        {
        }
		
        rup_PendProgFlgStartAddr = (uint32_t *)(FBLMGR_C_PENDING_PROG_FLG_ADDR); 
	  
	 lul_RdProgFlgWord1Value =  *rup_PendProgFlgStartAddr;	 
	 rup_PendProgFlgStartAddr++; 
	 
	 lul_RdProgFlgWord2Value =  *rup_PendProgFlgStartAddr; 
	 rup_PendProgFlgStartAddr++; 

	 lul_RdAswVldFlgWord1Value =  *rup_PendProgFlgStartAddr;	 
	 rup_PendProgFlgStartAddr++; 
	 
	 lul_RdAswVldFlgWord2Value =  *rup_PendProgFlgStartAddr; 
	 rup_PendProgFlgStartAddr++;

	 rup_AppSwStartAddr = (T_FP_ASW_JUMP_ENTRYPOINT)(*rup_PendProgFlgStartAddr);
	 rul_AppSwStartAddrValue = (uint32_t)(*rup_PendProgFlgStartAddr);
	 rup_PendProgFlgStartAddr++;
	 	     
	 lul_RdCheckSumWordValue = *rup_PendProgFlgStartAddr;
     				                      
	 if (lul_RdProgFlgWord1Value == caul_PendProgFlag[0x00u] &&
	     lul_RdProgFlgWord2Value == caul_PendProgFlag[0x01u]    )
	 {
		 rub_FblMgr_State = FBLMGR_C_ST_PENDING_PROG_REQ;
		 
         /* to send a debug messge to show the start address value 
         */ 			                       		 
	     if (lul_RdAswVldFlgWord1Value == caul_AswVldOkFlag[0x00u] &&
	         lul_RdAswVldFlgWord2Value == caul_AswVldOkFlag[0x01u]    )
	     {
	 	     rub_FblMgr_State = FBLMGR_C_ST_ASW_DATA_VLD_OK;
	 	     
	 	     lull_CalcuCheckSumWordValue = 0x0000000000000000u;
	 	     
	 	     lull_CalcuCheckSumWordValue += lul_RdProgFlgWord1Value; 
	 	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	 	     lull_CalcuCheckSumWordValue += lul_RdProgFlgWord2Value; 
	 	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	 	     lull_CalcuCheckSumWordValue += lul_RdAswVldFlgWord1Value; 
	 	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	 	     lull_CalcuCheckSumWordValue += lul_RdAswVldFlgWord2Value; 
	 	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	 	     lull_CalcuCheckSumWordValue += rul_AppSwStartAddrValue;
	 	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	 	 
	 	     if (lull_CalcuCheckSumWordValue == lul_RdCheckSumWordValue)
	 	     {
	 	         rub_FblMgr_State = FBLMGR_C_ST_ASW_DATA_CS_OK; 
                 
                     
                 if (rul_FblMgr_SwImgState.m_FblSwImgRunningState == BOOT_SW_IN_RAM_DN_FINISHED)
                 {
                     FblMgr_SetCurrSwImgRunningState(BOOT_SW_IN_RAM_RUNNING); 
                 }
			     else if (rul_FblMgr_SwImgState.m_FblSwImgRunningState == APP_SW_IN_FLASH_DN_FINISHED)
			     {
                     FblMgr_SetCurrSwImgRunningState(APP_SW_IN_FLASH_RUNNING);  		     
			     }
                 else
                 {
                     /* all other situation should not allow to switching sw 
                      */
                 } /* end of else of if (rul_FblMgr_SwImgState.m_FblSwImgRunningState == BOOT_SW_IN_RAM_DN_FINISHED) */

                 lub_StartAddrByte[0x10u] = (uint8_t)((uint8_t)(rul_AppSwStartAddrValue >> 24u) & 0xFFu); 
	             lub_StartAddrByte[0x11u] = (uint8_t)((uint8_t)(rul_AppSwStartAddrValue >> 16u) & 0xFFu); 
	             lub_StartAddrByte[0x12u] = (uint8_t)((uint8_t)(rul_AppSwStartAddrValue >>  8u) & 0xFFu); 
	             lub_StartAddrByte[0x13u] = (uint8_t)((uint8_t)(rul_AppSwStartAddrValue       ) & 0xFFu); 
                 lub_StartAddrByte[0x14u] = (uint8_t)((uint8_t)(rul_FblMgr_SwImgState.m_FblSwImgRunningState ) & 0xFFu); 
	             lub_StartAddrByte[0x15u] = 0x00u; 
	             lub_StartAddrByte[0x16u] = 0x00u; 
	             lub_StartAddrByte[0x17u] = 0x00u; 
			        
	             CanDrv_SendDebugMsg1(&lub_StartAddrByte[0x10u]);
												
				 /* to perform the sw switching action 
				  */

	 	     } /* end of if (lul_CalcuCheckSumWordValue == lul_RdCheckSumWordValue)*/
             else
             {
             	/* checksum is invalid , do nothing 
             	 */
             }
         
         	
         } /* end of if (lul_RdAswVldFlgWord1Value == caul_AswVldOkFlag[0x00u] &&
	                     lul_RdAswVldFlgWord2Value == caul_AswVldOkFlag[0x01u]    )
            */
         else
         {
         	  /* application valid flag is not correct , so do nothing 
         	   */
         }              		 
	 }
	 else if (lul_RdProgFlgWord1Value == 0xFFFFFFFFu &&
	             lul_RdProgFlgWord2Value == 0xFFFFFFFFu    )
	 {
	     /* without a valid prog flag until now 
	        so , still running in boot sw in flash/ram  mode 
	      */
	      
	 }
	 else
	 {
	 	/* all other value are valid , means still running 
	 	   in boot sw in flash /ram mode 
 	 	 */
	 }
	 
	 
} /* end of FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_ForFlash()  */



void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v2(void)
{
}/* end of FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v2()  */


void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v3(void)
{

}/* end of FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v3()  */


static uint8_t FblMgr_ChkPendProgFlgAndAswVldFlg(void)
{
    return 0;
}/* end of FblMgr_ChkPendProgFlgAndAswVldFlg()  */

uint8_t FblMgr_SetBootModeAswModeToggleFlg(void)
{

        #ifdef SFBL_APP_SW_BUILD
	     	
            /* set pending prog flag to 'F','B','L','d','n','r','e','q'
	       */
          		  
         
			
	#endif /* end of        #ifdef SFBL_APP_SW_BUILD */		
            return TRUE;
}

uint8_t FblMgr_SetPendReProgFlag(void)
{
   uint8_t lub_returnCode = FALSE; 
   #ifdef SFBL_APP_SW_BUILD
   #endif /* end of #ifdef SFBL_APP_SW_BUILD */
   
   return lub_returnCode; 
   
}/* end of FblMgr_SetPendReProgFlag */




void FblMgr_ToggleFromAppSwModeToBootSwMode(void)
{
	   
       #ifdef SFBL_APP_SW_BUILD 

	MCU_GENERIC_TRIG_MCU_SW_RESET; 
	
       #endif /* end of         #ifdef SFBL_APP_SW_BUILD  */

}

uint8_t FblMgr_SetPendProgFlgOnAndAswVldFlgOff(void)
{
         uint8_t   lub_ReturnCode = FALSE;

            /* set pending prog flag to 'F','B','L','d','n','r','e','q'
	       */
            rul_PendRePrgFlgAswVldFlag[0x00u] =  caul_PendProgFlag[0x00u];
            rul_PendRePrgFlgAswVldFlag[0x01u] =  caul_PendProgFlag[0x01u];
            /*
                set asw valid flag to all of 0xFFFFFFFFu
	       */			
            rul_PendRePrgFlgAswVldFlag[0x02u] =  0xFFFFFFFFu;
            rul_PendRePrgFlgAswVldFlag[0x03u] =  0xFFFFFFFFu;
	     /* set asw starting address to all of 0xFFFFFFFFu*/		
            rul_PendRePrgFlgAswVldFlag[0x04u] =  0xFFFFFFFFu;
			
	     lull_CalcuCheckSumWordValue = 0x0000000000000000u;
	      	 
	     lull_CalcuCheckSumWordValue +=  rul_PendRePrgFlgAswVldFlag[0x00u]; 
            lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
            lull_CalcuCheckSumWordValue +=  rul_PendRePrgFlgAswVldFlag[0x01u]; 
            lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
            lull_CalcuCheckSumWordValue +=  rul_PendRePrgFlgAswVldFlag[0x02u]; 
            lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
            lull_CalcuCheckSumWordValue +=  rul_PendRePrgFlgAswVldFlag[0x03u]; 
            lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu; 
	     lull_CalcuCheckSumWordValue +=  rul_PendRePrgFlgAswVldFlag[0x04u];
	     lull_CalcuCheckSumWordValue &= 0x00000000FFFFFFFFu;
		 
            rul_PendRePrgFlgAswVldFlag[0x05u] =  (uint32_t)lull_CalcuCheckSumWordValue;


   //        lub_ReturnCode =  FLASHDRV_ITF_EXP_PROGRAM_FLASH( (uint32_t )(FBLMGR_C_PENDING_PROG_FLG_ADDR) ,  /*  uint32_t i_p32bitDest, */ 
   //                                                                                       (uint32_t) 0x20u,  /* uint32_t  i_8bitPrgSize, */
   //                                                                                       FLASHDRV_C_WRITE_FLASH_MODE_ONE_PAGE, /* uint8_t   i_lub_FlashWriteMode,*/
   //                                                                                       (uint8_t *)(&(rul_PendRePrgFlgAswVldFlag[0x00u])));   /* uint8_t *i_p8bitSrc) */



        return lub_ReturnCode;




}/* end of FblMgr_SetPendProgFlgOnAndAswVldFlgOff()  */




#ifdef __cplusplus
}
#endif



/********************************************************************************
*								end of file										*
********************************************************************************/


