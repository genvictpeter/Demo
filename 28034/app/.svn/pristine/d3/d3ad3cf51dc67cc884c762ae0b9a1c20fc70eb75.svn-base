/**
*
* \file
*
* \brief Public definitions and declarations of functions intended to be called by
* the UDS network transport layer.
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
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*    to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t  *
*    to remove the similar coexisitn basic type for UINT8  uint8 and so on   *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSCAN_PUB_H
#define _UDSCAN_PUB_H

#include "udscan_conf.h"

/*lint -e750*//*lint -e752*/

void 		  		UDS_FN_TYPE UdsCan_Initialize		( void );
UdsCan_QueueBufPtr 	UDS_FN_TYPE UdsCan_GetTxBuf       	( uint8_t sessionId );
UdsCan_QueueBufPtr 	UDS_FN_TYPE UdsCan_GetRxBuf      	( uint8_t sessionId );
void          		UDS_FN_TYPE UdsCan_TxNext        	( uint8_t sessionId );
void          		UDS_FN_TYPE UdsCan_RxNext        	( uint8_t sessionId );
void          		UDS_FN_TYPE UdsCan_AbortTxRequest	( uint8_t sessionId );

#endif /* _UDSCAN_PUB_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
