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

#ifndef _UDSCAN_PRIV_H
#define _UDSCAN_PRIV_H


#include "uds_target.h"



/*lint -e749*//*lint -e750*//*lint -e751*//*lint -e754*/

/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

/******************************************************************************
*
* Type definitions
*
******************************************************************************/

/* This holds the state of an instance of UdsCan_QueueBuf_t. 
 * The lower 4 bits contain a value from UdsCan_QueueBufStates_t. */
typedef UDS_STATE_TYPE uint8_t UdsCan_QueueBufProps_t;

typedef enum
{
    UDSCAN_TXRXFREE = 0x00u,        /* The buffer is available to store TX or RX data. */
									/* For a TX buffer this means a tx confirmation has been received. */
    UDSCAN_TXALLOC,                	/* The buffer has been allocated to store TX data, but it is not yet ready to be transmitted. */
    UDSCAN_TXNOTSENT,              	/* The buffer is ready to be transmitted. */
    UDSCAN_TXINPROGRESS,           	/* The buffer is being transmitted. */
    UDSCAN_RXDATA                  	/* The buffer is contains RX data. */
} UdsCan_QueueBufStates_t;

typedef struct
{
	uint32_t					canID;
	uint8_t					    dlc;
    uint8_t                  	msgBuffer[0x08u];   /* We need 8 bytes of storage aligned on a natural boundary, and this is a convenient way to allocate it. */
} UdsCan_QueueBuf_t;

typedef UDS_STATE_TYPE struct
{
    /* For a TX queue this represents the tail of the queue. The Uds Tp writes CAN messages into the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the head of the queue. The Uds Tp reads CAN messages from the queue
     * at this position in the session's buffer array. */
    uint8_t                  ctUdsPos;

    /* For a TX queue this represents the head of the queue. The CAN driver reads CAN messages from the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the tail of the queue. The CAN driver writes CAN messages into the queue
     * at this position in the session's buffer array. */
    uint8_t                  ctCanPos;
} UdsCan_QueuePos_t;

typedef UDS_CONFIG_TYPE struct	/*lint !e963*/
{
    uint8_t			idxStart;   /* The first element of this channel's queue space in the array pointed to by UdsCan_SessionCfg_t::pQueueBuffers */
    uint8_t			idxEnd;     /* The last element of this channel's queue space in the array pointed to by UdsCan_SessionCfg_t::pQueueBuffers */
    uint32_t		msgIdPhy;   /* The CAN message ID used for sending or receiving messages on this channel(physical addressing type). */
	uint32_t		msgIdFnc;	/* The CAN message ID used for sending or receiving messages on this channel(functional addressing type). */
} UdsCan_ChannelCfg_t;

typedef UDS_CONFIG_TYPE struct	/*lint !e963*/
{
    UdsCan_ChannelCfg_t*        pChannelCfgs;       /* Points to an array with one entry each of Tx and Rx channel. */
    UdsCan_QueuePos_t*          pQueuePositions;    /* Points to an array with one entry per channel. */
    UdsCan_QueueBuf_t*          pQueueBuffers;      /* Points to an array with one entry per queue element. */
    UdsCan_QueueBufProps_t*     pQueueBufferStates; /* Points to an array with one entry per queue element. */
	uint8_t						numChannels;
} UdsCan_SessionCfg_t;

/******************************************************************************
*
* Variables
*
******************************************************************************/


/******************************************************************************
*
* Prototypes
*
******************************************************************************/


#endif /* _UDSCAN_PRIV_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
