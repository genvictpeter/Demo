/********************************************************************************
*
* \file:    FlashDrv_Mgr.h 
*
* \brief:   This file will include all of the data structure and 
*           managing functions used in the flash driver module
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
*  RTA_BSW_1.0      | Aug/18/2012   |                         | Yongqiang Deng   *
* Creation of this file                                                          *
*--------------------------------------------------------------------------------*
**********************************************************************************/

#ifndef _FLASHDRV_MGR_H_
#define _FLASHDRV_MGR_H_




#ifdef  __cplusplus
extern "C" {
#endif

/*
  #define FLASHDRV_C_FBL_FLASH_DRV_RUNNING_IN_ASYNC_MODE
 */

#define FLASHDRV_C_FBL_PEND_REQ_FLG_ASW_VLD_FLG_ADDR   (0xA001C000u)


#define TC17XX_PAGE_SIZE        	256   // program FLASH page size
#define TC17XX_DFLASH_PAGE_SIZE	128	  // data FLASH page size

#define PAGE_START_MASK			0x0FF
#define SECTOR_START_MASK		0x0FFF
#define PFLASH_BASE_MASK		(~0x1FFFFF)

#define DFLASH_PAGE_START_MASK		0x07F
#define DFLASH_SECTOR_START_MASK	0x0FFFF
#define DFLASH_BASE_MASK         	(~0x0FFFF)

#define FLASHPBUSY       0x00000001      /* Program Flash Busy */
#define FLASHD0BUSY      0x00000004      /* Data Flash Bank 0 Busy */
#define FLASHD1BUSY      0x00000008      /* Data Flash Bank 1 Busy */

#define FLASH_MASK_BUSY (FLASHPBUSY | FLASHD0BUSY | FLASHD1BUSY)

#define TC17XX_FLASHPFOPER      0x00000100      /* Program Flash Operation Error */
#define TC17XX_FLASHDFOPER      0x00000200      /* Data Flash Operation Error */
#define TC17XX_FLASHSQER        0x00000400      /* Command Sequence Error */
#define TC17XX_FLASH_MASK_ERROR (FLASHPFOPER | FLASHDFOPER | FLASHSQER)

#define TC17XX_FLASH_PROTECTION_ERROR_MASK 0x00000800 /* Protection Error */

#define PFLASH0_FSR 0xF8002010
#define PFLASH1_FSR 0xF8004010
#define DFLASH_FSR  0xF8002010

//Masks used in Erase procedure
#define PFLASH_MASK1 0x3FFF
#define TC17XX_PFLASH_MASK2 0x1FFFF
#define TC17XX_PFLASH_MASK3 0x3FFFF
#define DFLASH_MASK  0x7FFF

//BSL CONSTANTS

#define HEADER_BLOCK_SIZE  	   16
#define DATA_BLOCK_SIZE  	   PAGE_SIZE+8

#define HEADER_BLOCK 		   0x00
#define DATA_BLOCK 	 		   0x01
#define EOT_BLOCK			   0x02

#define BSL_PROGRAM_FLASH      0x00
#define BSL_RUN_FROM_FLASH     0x01
#define BSL_PROGRAM_SPRAM      0x02
#define BSL_RUN_FROM_SPRAM     0x03
#define BSL_ERASE_FLASH        0x04
#define BSL_PROTECT_FLASH      0x06

#define BSL_BLOCK_TYPE_ERROR   0xFF
#define BSL_MODE_ERROR 		   0xFE 
#define BSL_CHKSUM_ERROR 	   0xFD
#define BSL_ADDRESS_ERROR 	   0xFC
#define BSL_ERASE_ERROR		   0xFB
#define BSL_PROGRAM_ERROR	   0xFA
#define BSL_VERIFICATION_ERROR 0xF9
#define BSL_PROTECTION_ERROR   0xF8
#define BSL_SUCCESS 		   0x55



#ifdef __cplusplus
}
#endif



#endif // end of #ifndef _FLASHDRV_MGR_H_


