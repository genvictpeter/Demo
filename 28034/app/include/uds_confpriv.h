/**
*
* \file
*
* \brief Private declarations derived from the UDS Application Layer configuration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 3 2012-08-28 Tan Yang $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev4  | Dec/12/2012   |                         | Yang TAN         *
* Delivery_001                                                               *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev5  | Jan/18/2013   |                         | Yongqiang Deng   *
* Delivery_002                                                               *
*         update the code after 1st round integration with Customer running  *
*         sw project, change detail please refer to                          *
*         UDSonCAN Protocol Stack Release Note_v1_0r5.doc                    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Modify macros of session layer timer and application timers.       *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*    to add the data table decleration for services usage                    *
*    to use the generic TRUE and FALSE                                       *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_CONFPRIV_H
#define _UDS_CONFPRIV_H



#include "main.h"
#include "uds_priv.h"



/*MISRA 2004 Required Rule 14.3 - null statement not in line by itself */
/*lint -esym(960,14.3)*/

/******************************************************************************
*
* Preprocessor declarations
*
******************************************************************************/

/******************************************************************************
*
* Type declarations
*
******************************************************************************/

typedef Uds_SessionRxBuf_t* Uds_SessionRxBufPtr;
typedef Uds_SessionTxBuf_t* Uds_SessionTxBufPtr;

/******************************************************************************
*
* Variables declarations
*
******************************************************************************/

extern Uds_SessionCfg_t		Uds_SessionCfg;
extern Uds_SessionRuntime_t Uds_SessionRuntime;
extern Uds_ServiceTable_t	Uds_ServiceTable[];
extern Uds_APduData_t		Uds_APduDataInd[ UDS_SESSIONBUF_RX_NUM ];
extern Uds_APduData_t		Uds_APduDataResp[ UDS_SESSIONBUF_TX_NUM ];

extern UDS_CONFIG_TYPE UDS_DidDatMngRecd_t       Uds_g_DidDataTable[];
extern UDS_CONFIG_TYPE UDS_DidEepromDatMngRecd_t Uds_g_DidEepromDataTable[];
extern UDS_CONFIG_TYPE UDS_IoCtrlIdxTblRcd_t        Uds_g_IoCtrlByDidIdxTable[];
extern UDS_CONFIG_TYPE UDS_IoCtrlMngtDatTblRcd_t    Uds_g_IoCtrlByDidMngtTable[];
extern UDS_CONFIG_TYPE UDS_RdWtMemByAddDatMngRecd_t Uds_g_RdWtMemoryByAddrMngTbl[];
extern UDS_RdDatByPeriodDidMngRecd_t                Uds_g_RdDatByPeriodDidMngTbl[UDS_C_PERIODIC_DID_MAX_NUM]; 
extern UDS_DynaDefDidMngRecd_t                      Uds_g_DynaDefDidMngTbl[UDS_C_DYNA_DEF_DID_MAX_NUM];
extern UDS_CONFIG_TYPE UDS_ReqDnldMngRecd_t         Uds_g_ReqDnldMngTbl[];
extern UDS_CONFIG_TYPE UDS_RtnCtrlMngtDatTblRcd_t Uds_g_RtnCtrlMngtDataTable[];

/******************************************************************************
*
* Macro definitions
*
******************************************************************************/

/* Define UDS Diagnostic Application ans Session Layer Timing timer
 *
 */
#define UDS_P2TIMER_START(timer)							\
		Uds_SessionRuntime.timeoutCounter = (timer);		\
		Uds_SessionRuntime.flagP2TimeoutCounter = TRUE;

#define UDS_P2TIMER_STOP()									\
		(Uds_SessionRuntime.flagP2TimeoutCounter = FALSE)

#define UDS_P2TIMER_ISPENDING()								\
		Uds_SessionRuntime.flagP2TimeoutCounter

#define UDS_P2TIMER_ISTIMEOUT()								\
		( Uds_SessionRuntime.timeoutCounter == 0x00u )

#define UDS_P2STAR_CONSENEG_TIMER_ISTIMEOUT()				\
		(( Uds_SessionRuntime.timeoutCounter < Uds_SessionRuntime.P2StarCanServerConsNegResp))

#define UDS_S3TIMER_START(timer)							\
		Uds_SessionRuntime.timeoutCounterS3Server = (timer);\
		Uds_SessionRuntime.flagS3TimeoutCounter = TRUE;

#define UDS_S3TIMER_STOP()									\
		(Uds_SessionRuntime.flagS3TimeoutCounter = FALSE)

#define UDS_S3TIMER_ISPENDING()								\
		Uds_SessionRuntime.flagS3TimeoutCounter

#define UDS_S3TIMER_ISTIMEOUT()								\
		( Uds_SessionRuntime.timeoutCounterS3Server == 0x00u )

#define UDS_TIMER_DECREMENT(timer) 							\
		if ((timer) >= UDS_SESSION_TIMING_TICK_PERIOD) 		\
		{ 													\
			(timer) -= UDS_SESSION_TIMING_TICK_PERIOD;		\
		}else												\
		{													\
			(timer) = 0x00u;								\
		}

#endif /* _UDS_CONFPRIV_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
