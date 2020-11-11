/**
*
* \file
*
* \brief Publically available declarations derived from UDS Application Layer configuration.
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
*         Add macros TICK_UDS_SESSION_TIMER() and TICK_UDS_APP_TIMER() to    *
*         tick session layer timing timer S3Server and application timer     *
*         P2Can_Server.                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_CONF_H
#define _UDS_CONF_H

#include "uds_confpriv.h"

/*lint -e750*//*lint -e752*/

/******************************************************************************
*
* Macro definitions
*
******************************************************************************/

/* Macros to drive UDS Session layer and Application layer timing.
 *
 * [Note]: 
 * The period of ECU resource, e.g. a periodic timer, which is used to tick the session layer and
 * application layer timers shall be defined in microsecond using "UDS_SESSION_TIMING_TICK_PERIOD"
 * which is configured in "uds_confdefs.h".
 */
#define TICK_UDS_SESSION_TIMER()        UDS_TIMER_DECREMENT(Uds_SessionRuntime.timeoutCounterS3Server)
#define TICK_UDS_APP_TIMER()            UDS_TIMER_DECREMENT(Uds_SessionRuntime.timeoutCounter)

#endif /* _UDS_CONF_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/