/**
*
* \file
*
* \brief Publically available declarations derived from UDS network transport layer configuration.
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
*         Add macros TICK_UDSTP_SESSION1_TIMER() and                         *
*         TICK_UDSTP_SESSION1_SEPTIME() to tick timrs for network transport  *
*         layer timing.                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSTP_CONF_H
#define _UDSTP_CONF_H

#include "udstp_confpriv.h"

/*lint -e750*//*lint -e766*/

/******************************************************************************
*
* Macro definitions
*
******************************************************************************/

/* This is helper macros to access the transport-layer-specific state and configuration of a session.
 * The transport-layer-specific state and configuration is stored in this manner to allow uniform access,
 * irrespective of the definition of the structures which contain the state and configuation. */
#define UDSCAN_SESSIONCFG( sessionId )  ( (UdsCan_SessionCfg_t*)(UdsTp_SessionCfgs[ (sessionId) ].pTransportCfg ) )

#define UDSCAN_SET_TRANSMITCONF( sessionId )	( UdsTp_Sessions[ (sessionId) ].sentConfirmed = TRUE )

/* Macros to drive Network Transport layer NTiming timer and seperation time(STmin).
 *
 * [Note]: 
 * The period of ECU resource, e.g. a periodic timer, which is used to tick the network transport layer
 * NTiming timer and STmin timer shall be defined in microsecond using "UDSTP_TIMING_TICK_PERIOD"
 * which is configured in "udstp_confdefs.h".
 */
#define TICK_UDSTP_SESSION1_TIMER()        UDSTP_TIMER_DECREMENT(UdsTp_Sessions[0x00u].timeoutCounter)
#define TICK_UDSTP_SESSION1_SEPTIME()      UDSTP_TIMER_DECREMENT(UdsTp_Sessions[0x00u].timeoutCounterST)

#endif /* _UDSTP_CONF_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
