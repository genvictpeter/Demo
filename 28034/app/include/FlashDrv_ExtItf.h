/********************************************************************************
*
* \file:    FlashDrv_ExtItf.h 
*
* \brief:   This file will include all of the external interfaces 
*           used in the flash driver module
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the Flash Boot Loader software package.
*
*
*================================================================================*
*                               REVERSION HISTORY                                *
*================================================================================*
*  REVISION         |   DATE        |                         |      AUTHOR      *
*--------------------------------------------------------------------------------*
*  RTA_BSW_1.0      | Aug/18/2012   |                         | Yongqiang Deng   *
* Creation of this file                                                          *
*--------------------------------------------------------------------------------*
*  RTA_BSW_2.0      | Jan/12/2014   |                         | Yongqiang Deng   *
* Update this file for eAAM FBL project                                          *
*--------------------------------------------------------------------------------*
**********************************************************************************/


#ifndef _FLASHDRV_EXTITF_H_
#define _FLASHDRV_EXTITF_H_


#include "MAIN.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum {
	FLASHDRV_C_RC_NON_USED         = 0x00u,
	FLASHDRV_C_RC_SUCCESS          = 0x01u,
	FLASHDRV_C_RC_FLASH_MODULE_ERR = 0x02u,
	FLASHDRV_C_RC_FLASH_TYPE_ERR   = 0x03u,
	FLASHDRV_C_RC_FLASH_ADDR_ERR   = 0x04u,

	FLASHDRV_C_RC_LOGED_THIS_REQ   = 0x05u,
	FLASHDRV_C_RC_REJECT_THIS_REQ          = 0x06u,
	FLASHDRV_C_RC_BUSY_FLG_IS_STILL_ON     = 0x07u,
	FLASHDRV_C_RC_ERASING_PROGING_ON_GOING = 0x08u,
	FLASHDRV_C_RC_BUSY_FLG_IS_OFF_NOW      = 0x09u,
	FLASHDRV_C_RC_ERASING_PROGING_FINISHED = 0x0Au,

	FLASHDRV_C_RC_ERASE_ERR       = 0x0Bu,
	FLASHDRV_C_RC_PROTECTION_ERR  = 0x0Cu,
    FLASHDRV_C_RC_PROGRAM_ERR     = 0x0Du,
    FLASHDRV_C_RC_WRITE_MODE_ERR  = 0x0Eu,
    FLASHDRV_C_RC_VERIFY_ERR      = 0x0Fu,
    FLASHDRV_C_RC_PROG_BUFFER_ERR = 0x10u

}T_FlashDrv_Return_Code;




extern void FlashDrv_Init(void);
extern void FlashDrv_MainCyclicTaskEntryPoint(void);

extern uint8_t FlashDrv_Get_IsFinish_EraseAnySectors_V2(void);
extern uint8_t FlashDrv_Get_Result_EraseAnySectors_V2(void);

extern void FlashDrv_EraseMultiLogicalSector_SyncMode_v4(void);
extern T_FlashDrv_Return_Code FlashDrv_EraseMultiLogicalSector_SyncMode_v5(uint32_t  i_lul_LogicalSectorStartAddrToErase,
		                                 uint8_t   i_lub_NumOfLogicSectorToErase,
		                                 uint32_t  i_lul_LogicalSectorSizeToErase);

extern uint8_t FlashDrv_EraseAddressValid(uint32_t  i_lul_SectorStartAddrToErase,
		                                                  uint32_t  i_lul_SectorSizeToErase);


#define FLASHDRV_DISABLE_ALL_INTERRUPTS()  DINT
#define FLASHDRV_ENABLE_ALL_INTERRUPTS()   EINT


extern uint8_t FlashDrv_Get_IsFinish_EraseAnySectors_V2(void);
extern uint8_t FlashDrv_Get_Result_EraseAnySectors_V2(void);


 
#define FLASHDRV_ITF_EXP_PROGRAM_IS_FINISHED()                               (TRUE)


#ifdef __cplusplus
}
#endif





#endif // end of #ifndef _FLASHDRV_EXTITF_H_



