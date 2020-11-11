/**
*
* \file
*
* \brief Private declarations derived from the UDS network transport layer configuration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 4 2012-12-12 Tan Yang $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev4  | Dec/12/2012   |                         | Yang TAN         *
* Delivery_001                                                               *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Modify macros of network transport layer timing timers.            *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSTP_CONFPRIV_H
#define _UDSTP_CONFPRIV_H



#include "uds_target.h"
#include "udstp_priv.h"


/*lint -esym(752, UdsTp_SessionCfgs) */
/*lint -esym(752, UdsTp_Sessions) */
/*lint -esym(750, _UDSTP_CONFPRIV_H) */
/*lint -esym(750, UDSTP_TIMER_START) */
/*lint -esym(750, UDSTP_TIMER_STOP) */
/*lint -esym(750, UDSTP_TIMER_ISPENDING) */
/*lint -esym(750, UDSTP_TIMER_ISTIMEOUT) */
/*lint -esym(750, UDSTP_TIMER_DECREMENT) */

/* [MISRA 2004 Advisory Rule 19.7] Function-like macro defined */
/*lint -esym(961,19.7) */

/* [MISRA 2004 Required Rule 14.3] null statement not in line by itself */
/*lint -esym(960,14.3) */

/******************************************************************************
*
* Preprocessor declarations
*
******************************************************************************/

/******************************************************************************
*
* Variables declarations
*
******************************************************************************/

extern UdsTp_SessionCfg_t	UdsTp_SessionCfgs[];
extern UdsTp_Session_t		UdsTp_Sessions[];

/******************************************************************************
*
* Macro definitions
*
******************************************************************************/

/* Define Network Transport layer NTiming timer
 *
 */
#define UDSTP_TIMER_START(sessionId, timer)							\
		UdsTp_Sessions[ (sessionId) ].timeoutCounter = (timer);		\
		UdsTp_Sessions[ (sessionId) ].flagTimeoutCounter = TRUE;

#define UDSTP_TIMER_STOP(sessionId)									\
		UdsTp_Sessions[ (sessionId) ].flagTimeoutCounter = FALSE;

#define UDSTP_TIMER_ISPENDING(sessionId)							\
		UdsTp_Sessions[ (sessionId) ].flagTimeoutCounter

#define UDSTP_TIMER_ISTIMEOUT(sessionId)							\
		(UdsTp_Sessions[ (sessionId) ].timeoutCounter == 0x00u)

#define UDSTP_TIMER_ST_START(sessionId, timer)						\
		(UdsTp_Sessions[ (sessionId) ].timeoutCounterST = (timer))

#define UDSTP_TIMER_ST_ISTIMEOUT(sessionId)							\
		(UdsTp_Sessions[ (sessionId) ].timeoutCounterST == 0x00u)

#define UDSTP_TIMER_DECREMENT(timer) 				\
		if ((timer) >= UDSTP_TIMING_TICK_PERIOD) 	\
		{ 											\
			(timer) -= UDSTP_TIMING_TICK_PERIOD;	\
		}else										\
		{											\
			(timer) = 0x00u;							\
		}

#endif /* _UDSTP_CONFPRIV_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
