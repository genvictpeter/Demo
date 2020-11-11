/**
*
* \file
*
* \brief Preprocessor definitions derived from the CAN Data Link Layer Interface's configuration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 5 2013-01-18 Yongqiang Deng $
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
*         update the code after 1st round integration with customer running  *
*         sw project, change detail please refer to                          *
*         UDSonCAN Protocol Stack Release Note_v1_0r5.doc                    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*    to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t  *
*    to remove the similar coexisitn basic type for UINT8  uint8 and so on   *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSCAN_CONFDEFS_H
#define _UDSCAN_CONFDEFS_H

/*lint -e750*/

/******************************************************************************
*
* General definitions
*
******************************************************************************/

/* Enable aborting the ongoing transmission of a CAN message which is pending at the CAN
 * hardware module and not transmitted yet.
 *
 * [Note]:
 * This preprocessor definition is used when user application requires/can abort the ongoing
 * can message transmission in CAN hardware module.
 * If this functionality is not used, just undefine it.
 *
 * 0x01 - Enabling this functionality
 * 0x00 - This functionality disabled
 */
#define UDS0_CAN_HW_TX_ABORT		0x00u

/******************************************************************************
*
* CAN channel queue definitions
*
******************************************************************************/

/* Define number of channels for each UdsCan session
 *
 * one channel for receive, the other one for transmit
 */
#define UDS0_CAN_NUM_CHANNELS 		0x02u

/* Allocate buffers for Rx direction
 *
 * UDS0_CAN_RX_NUMBUF: number of buffers to store received messages from outside
 * UDS0_CAN_RX_START:  start position in buffers for Rx
 * UDS0_CAN_RX_END:	end position in buffers for Rx
 */
#define UDS0_CAN_RX_NUMBUF			0x03u
#define UDS0_CAN_RX_START			0x00u
#define UDS0_CAN_RX_END				(UDS0_CAN_RX_START + UDS0_CAN_RX_NUMBUF - 0x01u)

/* Allocate buffers for Tx direction
 *
 * UDS0_CAN_TX_NUMBUF: number of buffers to store transmit messages to outside
 * UDS0_CAN_TX_START:  start position in buffers for Tx
 * UDS0_CAN_TX_END:	end position in buffers for Tx
 */
#define UDS0_CAN_TX_NUMBUF			0x03u
#define UDS0_CAN_TX_START			(UDS0_CAN_RX_END   + 0x01u)
#define UDS0_CAN_TX_END				(UDS0_CAN_TX_START + UDS0_CAN_TX_NUMBUF - 0x01u)

#define UDS0_CAN_QUEUEALL_NUMBUF 	(UDS0_CAN_RX_NUMBUF + UDS0_CAN_TX_NUMBUF)

/* Define of CAN message IDs for Rx/Tx direction for each UdsTp session
 *
 * UDS0_CAN_RX_MSGID_PHY: message ID for Rx direction for UdsTp0 session using physical TA type.
 * UDS0_CAN_RX_MSGID_FNC: message ID for Rx direction for UdsTp0 session using functional TA type.
 * UDS0_CAN_TX_MSGID_PHY: message ID for Tx direction for UdsTp0 session using physical TA type.
 * UDS0_CAN_TX_MSGID_FNC: message ID for Tx direction for UdsTp0 session using functional TA type.
 *
 * For both a 11bit ID and a 29bit ID: bit0 of ID will be placed in bit0 of below defined values.
 * 
 * [Note]:
 *	  The determination of these IDs are from N_AI information. We use staticly defined ID values
 *	  rather than dynamiclly calculated is because on one hand for an implementation of vehicle network,
 *    the N_AI information always predefined/fixed. Also using staticlly defined values saves CPU execution time.
 * 1. The Rx MSGIDs are used for checking received CAN messages by UdsCan module, and to allocate received messages
 *    to the dedicated buffers in case multi-session configured and used.
 * 2. The Tx MSGIDs are used to be copied into canID of Tx buffer of UdsCan_QueueBufPtr type by UdsTp module.
 */
 /* currently , will use request 0x7E4 and response 0x7EC */

#define UDS0_CAN_RX_MSGID_PHY			CANDRV_C_UDS_FBL_PHY_ADD_RX_CAN_ID //CANDRV_C_RX_PHY_ADDR_CANMSGID /* TODO */ /* CANID_REQ_PHYS */
#define UDS0_CAN_RX_MSGID_FNC			CANDRV_C_UDS_FBL_FUNC_ADD_RX_CAN_ID //CANDRV_C_RX_FUNC_ADDR_CANMSGID /* TODO */  /* CANID_REQ_FUNC */
#define UDS0_CAN_TX_MSGID_PHY			CANDRV_C_UDS_FBL_PHY_ADD_TX_CAN_ID // CANDRV_C_TX_PHY_ADDR_CANMSGID  /* TODO */ /* CANID_RES_PHYS */
#define UDS0_CAN_TX_MSGID_FNC			(uint32_t)0x04u /* TODO */ /* for a server this will never be used */

#endif /* _UDSCAN_CONFDEFS_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
