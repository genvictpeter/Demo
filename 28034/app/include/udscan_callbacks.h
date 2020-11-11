/**
*
* \file
*
* \brief Declaration of callbacks implemented by the Data Link Layer Interface.
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
*    to remove the similar coexisitn basic type for uint16  uint8 and so on   *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSCAN_CALLBACKS_H
#define _UDSCAN_CALLBACKS_H


#include "uds_target.h"


/*lint -e750*//*lint -e752*/

/**
 * This function is called by the CAN driver whenever a CAN message is successfully transmitted on a message object.
 *
 * Note that this function is called from within the CAN driver's TX confirmation interrupt handler and therefore
 * it cannot be re-entered or interrupted by transmission from the UDS software package.
 * It *can* be interrupted by UdsCan_LData_RxIndication().
 *
 * This function changes the buffer state which latestly sent message from UDSCAN_TXINPROGRESS to UDSCAN_TXRXFREE and
 * thereby freeing the buffer if the "transferStatus" equals to ZERO which means last transmit successfully finished.
 *
 * Note that:
 *  - This function will discard the CAN message buffer which sent last message and reset buffer state only if
 *    transferStatus equals to ZERO which means transmit successfully finished. 
 *
 * \param [in] msgId     		  The CAN message ID which has successfully transmitted a message.
 * \param [in] transferStatus	The result of transfer request
 */
void UdsCan_LData_TxConfirmation( uint32_t msgId, uint8_t transferStatus );

/**
 * This function is called by the CAN driver whenever a CAN message is received which is associated
 * with the UDS software package.
 *
 * The function tries to assign the received message to the buffers maintained by the Uds CAN Data Link Layer Interface.
 * If this is not possible, the function silently discards the message.
 *
 * This function is called from the CAN driver's RX interrupt, so we do not need to worry about re-entrancy.
 *
 * \param [in] msgId        The CAN message ID of the received CAN message.
 * \param [in] msgLen       The length of the received CAN message.
 * \param [in] pMsgData     The received CAN message. The caller can discard this after the function returns.
 */
void UdsCan_LData_RxIndication	( uint32_t msgId, uint8_t msgLen, uint8_t* pMsgData );

#endif /* _UDSCAN_CALLBACKS_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
