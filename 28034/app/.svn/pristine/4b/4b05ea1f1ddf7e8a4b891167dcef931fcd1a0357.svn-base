/********************************************************************************
*
* \file:    FblMgr.h 
*
* \brief:   This file will include all of the data structure and 
*           managing functions used in the Flash Boot Loader Management module
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which 
* is attached in the Flash Boot Loader software package.
*
*
*================================================================================*
*                               REVERSION HISTORY                                *
*================================================================================*
*  REVISION         |   DATE        |                         |      AUTHOR      *
*--------------------------------------------------------------------------------*
*  RTA_BSW_1.0      | Sep/12/2012   |                         | Yongqiang Deng   *
* Creation of this file                                                          *
*--------------------------------------------------------------------------------*
*  RTA_BSW_2.0      | Jan/12/2014   |                         | Yongqiang Deng   *
* Update this file for eAAM FBL project                                          *
*--------------------------------------------------------------------------------*
**********************************************************************************/

#ifndef _FBL_MGR_H_
#define _FBL_MGR_H_


#include "MAIN.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define FBLMGR_C_PEND_REPROG_FLG_32BIT_DAT_LEN               (8u)
#define FBLMGR_C_ASW_VLD_FLG_32BIT_DAT_LEN                   (8u)

#define FBLMGR_C_PEND_REPROG_AND_ASW_VLD_FLG_32BIT_DAT_LEN   (72u) // (16u)
#define FBLMGR_C_FBL_BOOTHEADER_32BIT_DEFAULT_VALUE_AFTER_ERASE (0x00000000u)




typedef enum 
{
   BOOT_SW_IN_FLASH_RUNNING    = 0x00u,
   BOOT_SW_IN_RAM_DOWNLOADING  = 0x01u, 
   BOOT_SW_IN_RAM_DN_FINISHED    = 0x02u,
   BOOT_SW_IN_RAM_RUNNING      = 0x03u,
   APP_SW_IN_FLASH_DOWNLOADING = 0x04u,
   APP_SW_IN_FLASH_DN_FINISHED   = 0x05u,
   APP_SW_IN_FLASH_RUNNING     = 0x06u   	
}T_FBL_SW_IMG_RUNNING_STATE;

#ifdef ROM_VERSION
    #define FBL_SW_INIT_RUNNING_STATE   BOOT_SW_IN_FLASH_RUNNING
#endif
#ifdef RAM_VERSION
    #define FBL_SW_INIT_RUNNING_STATE   BOOT_SW_IN_RAM_RUNNING
#endif

typedef struct
{
    T_FBL_SW_IMG_RUNNING_STATE m_FblSwImgRunningState; 
    uint8_t                    m_BootSwInFlashValidFlg; 
    uint8_t                    m_BootSwInRamValidFlg; 
    uint8_t                    m_AppSwInFlashValidFlg; 
    uint8_t                    m_AppDatInFlashValidFlg; 	
	
}T_FBL_MGR_SW_IMG_STATE;


#define FBLMGR_C_VALID_BOOTSW_RCHW_VALUE  (0x015A0000u)

#define FBLMGR_C_BOOT_SW_RCHW_ADDR           (uint32_t)0x00000000u
#define FBLMGR_C_APP_SW_RCHW_ADDR             (uint32_t)0x00030004u

#define FBLMGR_C_PENDING_PROG_FLG_ADDR        (uint32_t)(0xA000C000u)  // (0xA001C000u)
#define FBLMGR_C_ASW_TO_BOOT_SW_FLSH_ADDR     (uint32_t)(0xA000C100u) // (0xA000C020u) //(0xA001C020u)

#define FBLMGR_C_CACHED_PENDING_PROG_FLG_ADDR        (uint32_t)(0x8000C000u) // (0x8001C000u)
#define FBLMGR_C_CACHED_ASW_TO_BOOT_SW_FLSH_ADDR     (uint32_t)(0x8000C100u) // (0x8000C020u) // (0x8001C020u)

#define FBLMGR_C_BOOTSW_RAM_START_ADD         (uint32_t)(0xD0000020u)
#define FBLMGR_C_PENDING_PROG_FLG_LEN         256u // 0x20u


#define FBLMGR_DISABLE_ALL_INTERRUPTS()    SuspendAllInterrupts()
#define FBLMGR_ENABLE_ALL_INTERRUPTS()     ResumeAllInterrupts()


#define FBLMGR_C_ST_IDLE                                (uint8_t)0x00u
#define FBLMGR_C_ST_PENDING_PROG_REQ      (uint8_t)0x01u
#define FBLMGR_C_ST_BOOT_MODE_UPDATE     (uint8_t)0x02u
#define FBLMGR_C_ST_ASW_DATA_VLD_OK       (uint8_t)0x03u
#define FBLMGR_C_ST_ASW_DATA_INVLD         (uint8_t)0x04u
#define FBLMGR_C_ST_ASW_DATA_CS_FAIL     (uint8_t)0x05u 
#define FBLMGR_C_ST_ASW_DATA_CS_OK         (uint8_t)0x06u 

#define FBLMGR_C_RESET_STAY_IN_BOOT_WIN_TMR_ABS_VALUE    30000000u /* 30000000us = 30000ms = 30s */
#define FBLMGR_C_CYCLIC_TASK_PERIOD                      12800u    /* 12800us */

#define FBLMGR_C_APP_SW_START_ADDR_IN_FLASH_LOW_BOUND   0x00080000u
#define FBLMGR_C_APP_SW_START_ADDR_IN_FLASH_HIGH_BOUND  0x00180000u

#define FBLMGR_C_BOOT_SW_START_ADDR_IN_RAM_LOW_BOUND 0x40000000u
#define FBLMGR_C_BOOT_SW_START_ADDR_IN_RAM_HIGH_BOUND 0x40017800u


typedef void (*T_FP_ASW_JUMP_ENTRYPOINT)(void);




extern void FblMgr_Init(void);
extern void FblMgr_InitMainEntrypoint(void);
extern void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v2(void);
extern void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_v3(void);
extern void FblMgr_ChkDnldSwPendProgFlgAndAswVldFlg_ForFlash(void); 
 
extern uint8_t FblMgr_SetPendProgFlgOnAndAswVldFlgOff(void); 
extern uint8_t FblMgr_ChkIfProgFlgUpdateIsNeeded(void);
extern uint8_t FblMgr_SetBootModeAswModeToggleFlg(void);
extern void FblMgr_ToggleFromAppSwModeToBootSwMode(void);
extern T_FBL_SW_IMG_RUNNING_STATE FblMgr_GetCurrSwImgRunningState(void);
extern void FblMgr_SetCurrSwImgRunningState(T_FBL_SW_IMG_RUNNING_STATE i_SwImgToSet);

extern uint8_t FblMgr_CurrRunningSwImgCompare(T_FBL_SW_IMG_RUNNING_STATE i_SwImgToCompared);

extern void FblMgr_ChkBootSwInRam(void);
extern void FblMgr_ChkAppSwInFlash(void); 

extern uint8_t  FblMgr_CheckFblStayInBootSpecificMsg(uint8_t *i_lup_CanMsgDatPtr); 
extern void FBLMgr_MainCyclicTaskEntryPoint(void);
extern void FblMgr_InitStartStayInBootTimer(void);
extern uint8_t FblMgr_SetPendReProgFlag(void); 
extern uint8_t FblMgr_SetPendReProgFlag_FrmAsw(void); 





#define FBLMGR_ITF_EXP_INIT_CHECK_ACTION        FblMgr_InitMainEntrypoint
#define FBLMGR_ITF_EXP_CHK_BSW_IN_RAM()         FblMgr_ChkBootSwInRam()
#define FBLMGR_ITF_EXP_CHK_ASW_IN_FLASH         FblMgr_ChkAppSwInFlash

#define FBLMGR_ITF_EXP_SET_REPROGFLG_FRM_ASW    FblMgr_SetPendReProgFlag_FrmAsw

#define FBLMGR_ITF_EXP_SET_REPROGON_ASWVLDOFF    (TRUE)

#define FBLMGR_ITF_EXP_CHK_IF_REPROG_UPDT_NEEDED      FblMgr_ChkIfProgFlgUpdateIsNeeded

#define FBLMGR_ITF_EXP_GET_CURR_RUN_SW_IMG_STATE()    FblMgr_GetCurrSwImgRunningState()
#define FBLMGR_ITF_EXP_SET_CURR_RUN_SW_IMG_STATE(SwImgToSet)    FblMgr_SetCurrSwImgRunningState(SwImgToSet)

#define FBLMGR_ITF_EXP_CURR_RUN_SW_IMG_IS_BSW_IN_FLASH()   FblMgr_CurrRunningSwImgCompare(BOOT_SW_IN_FLASH_RUNNING)  
#define FBLMGR_ITF_EXP_CURR_RUN_SW_IMG_IS_BSW_IN_RAM()     FblMgr_CurrRunningSwImgCompare(BOOT_SW_IN_RAM_RUNNING)
#define FBLMGR_ITF_EXP_CURR_RUN_SW_IMG_IS_ASW_IN_FLASH()   FblMgr_CurrRunningSwImgCompare(APP_SW_IN_FLASH_RUNNING)  

#define FBLMGR_ITF_EXP_CHK_STAY_IN_BOOT_SPEC_MSG(CanMsgDataPtr)  FblMgr_CheckFblStayInBootSpecificMsg(CanMsgDataPtr)




#ifdef __cplusplus
}
#endif



#endif // end of #ifndef _FBL_MGR_H_
