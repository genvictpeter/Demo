/**
*
* \file
*
* \brief Internal definitions and declarations
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 6 2013-02-04 Tan Yang $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev4  | Dec/12/2012   |                         | Yang TAN         *
* Delivery_001                                                               *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev5  | No Change     |                         |                  *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev6 | Feb/04/2013    |                         | Yang TAN         *
* Delivery_003                                                               *
*    Add one macro UDS_NULL to be used by the protocol stack,change detail   *
*    please refer to UDSonCAN Protocol Stack Release Note_v1_0r6.doc         *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*  to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t    *
*  to remove the similar coexisitn basic type for UINT8  uint8 and so on     *
*  to use the generic TRUE and FALSE and NULL, remove the specific type for  *
*  UDS                                                                       *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_TARGET_H
#define _UDS_TARGET_H



#include "MAIN.h"


/* [MISRA 2004 Rule 19.15] Repeated include file */
/*lint -e537 */

/* #define UDS_ENV_RTAOSEK5 */

#if defined( UDS_ENV_RTAOSEK5 )
    /* We are using RTA-OSEK. */
#ifndef OS_OSEKCOMN_H
    /* We have not yet included an RTA-OSEK header, so do so now. */
   // #include "osek.h"
#endif
#else

#endif

/*lint -e750*//*lint -e751*//*lint -e752*/

/* [MISRA 2004 Advisory Rule 19.7] Function-like macro defined */
/*lint -esym(961,19.7) */
#define UDS_VERSION		0x5A19

/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

/* This is the optimum number of bytes for writes to an address aligned on a natural boundary.
 * Often this is 2 for a 16-bit target and 4 for a 32-bit target. */
#define UDS_MEM_BLOCK_SIZE   0x04u

/* This macro prefixes every definition of a type which contains configuration (i.e. ROM data) for the UDS software. */
#define UDS_CONFIG_TYPE const

/* This macro prefixes every definition of a type which contains state (i.e. RAM data) for the UDS software. */
#define UDS_STATE_TYPE

/* This macro prefixes every definition of a function for the UDS software. */
#define UDS_FN_TYPE

#define MCU_GENERIC_TRIG_MCU_SW_RESET 	// SYSTEM_Reset()	/* the interface to reset MCU */


/* These macros enable or disable all interrupts and must be able to be nested.
 *
 * If we are using RTA-OSEK (either standalone or via ASCET) we can just delegate to the appropriate RTA-OSEK API.
 * Otherwise the user must supply his own implementation.
 */
#ifndef GLOBAL_DISABLE_INTERRUPTS
   #define GLOBAL_DISABLE_INTERRUPTS    DINT // asm ("wrteei 0x00u"); /* global disable interrputs(DEC,external,fixed-interval) */
   #define GLOBAL_ENABLE_INTERRUPTS     EINT // asm ("wrteei 0x01u");	/* global enable interrputs(DEC,external,fixed-interval) */
 
   #define SuspendAllInterrupts()     GLOBAL_DISABLE_INTERRUPTS
   #define ResumeAllInterrupts()      GLOBAL_ENABLE_INTERRUPTS 

#endif /* end of #ifndef GLOBAL_DISABLE_INTERRUPTS */

    #define UDS_DISABLE_ALL_INTERRUPTS()    SuspendAllInterrupts()
    #define UDS_ENABLE_ALL_INTERRUPTS()     ResumeAllInterrupts()


/******************************************************************************
*
* Type definitions
*
******************************************************************************/
#if 0  /* remove the local defined basic type , using the unified basic type */
#ifndef uint8_t
typedef unsigned char   uint8_t;              /* An unsigned 8-bit integer. */
typedef unsigned short  uint16_t;             /* An unsigned 16-bit integer. */
typedef unsigned long   uint32_t;             /* An unsigned 32-bit integer. */
typedef signed char     sint8_t;              /* A signed 8-bit integer. */
typedef short     		sint16_t;             /* A signed 16-bit integer. */
typedef long      		sint32_t;             /* A signed 32-bit integer. */
#endif
#endif

typedef uint16_t			Uds_PduId_t;		/* the type used for all layers during define/reference to a PDU instance. */
typedef uint16_t 			Uds_PduLength_t;
typedef uint8_t 			Uds_PduData_t;
typedef uint8_t			    UdsTp_Addr_t;		/* the type used for network layer SA, TA, AE for NSDU and NPDU. */
typedef uint8_t			    Uds_Addr_t;			/* the type used for UDS application layer SA, TA, RA for A_SDU and A_PDU. */

typedef uint8_t      		Uds_Seed_t;         /* The seed is an array of this type. "uint8_t"-seed is caculated at runtime,"const uint8_t"-seed is stored as predefined */
typedef uint8_t             Uds_Key_t;          /* The key buffer is an array of this type. */

typedef UDS_CONFIG_TYPE uint8_t*          Uds_CfgPtr8;        /* Instances of this type refer to a location of type UDS_CONFIG_TYPE. */
typedef UDS_CONFIG_TYPE uint16_t*         Uds_CfgPtr16;       /* Instances of this type refer to a location of type UDS_CONFIG_TYPE. */
typedef UDS_CONFIG_TYPE uint32_t*		  Uds_CfgPtr32;       /* Instances of this type refer to a location of type UDS_CONFIG_TYPE. */
typedef UDS_STATE_TYPE  uint8_t*          Uds_StatePtr8;      /* Instances of this type refer to a location of type UDS_STATE_TYPE. */
typedef UDS_STATE_TYPE  uint16_t*         Uds_StatePtr16;     /* Instances of this type refer to a location of type UDS_STATE_TYPE. */
typedef UDS_STATE_TYPE  uint32_t*         Uds_StatePtr32;     /* Instances of this type refer to a location of type UDS_STATE_TYPE. */

/*
typedef uint8_t 			Std_UdsReturnType;
 */


#ifndef TRUE
   #define TRUE			    (0x01u)
#endif

#ifndef FALSE
   #define FALSE			(0x00u)
#endif
#ifndef STD_HIGH
   #define STD_HIGH		(0x01u)
#endif

#ifndef STD_LOW
   #define STD_LOW			(0x00u)
#endif

#ifndef STD_ACTIVE
   #define STD_ACTIVE		(0x01u)
#endif

#ifndef STD_IDLE
   #define STD_IDLE	              (0x00u)
#endif

#ifndef STD_ON
   #define STD_ON			(0x01u)
#endif

#ifndef STD_OFF
   #define STD_OFF			(0x00u)
#endif

//#ifndef NULL
//    #define NULL        ((void *)0x00000000ul)
//#endif

/******************************************************************************
*
* Function definitions
*
******************************************************************************/

void UDS_FN_TYPE Uds_MemCopy( uint8_t* pDest, const uint8_t* pSrc, uint32_t numBytes );	/*lint !e963*/



void UDS_FN_TYPE Uds_MemClear( uint8_t* pDest, uint32_t numBytes);

void UDS_FN_TYPE Uds_MemCopyDataFlow(uint8_t * pDest,
                                const uint8_t * pSrc,
                                uint32_t numBytes);


#endif /* _UDS_TARGET_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
