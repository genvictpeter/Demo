/**
*
* \file
*
* \brief This file declares all the APIs (i.e. interfaces) which the Data Link Layer Interface
* requires from other components of the system.
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

#ifndef _UDSCAN_INF_H
#define _UDSCAN_INF_H



#include "uds_target.h"
#include "udscan_confdefs.h"


/*lint -e750*//*lint -e752*/


/******************************************************************************
*
* APIs required from the CAN driver.
*
******************************************************************************/

/**
 * This function should transmit (or queue for transmission) the specified CAN message.
 * The CAN driver can decide by itself which CAN message object(e.g. Hardware message objects) to be used.
 *
 * The UdsCan module assumes that:
 *  - The UdsCan module can discard the contents of the buffer pBytes after this API call has returned.
 *
 * \param [in] msgId        The CAN message ID to be used for the message.
 * \param [in] numBytes		The DLC of the CAN message.
 * \param [in] pBytes       The payload of the CAN message.
 */
void UdsCan_LData_TxRequest( uint32_t msgId, uint8_t numBytes, uint8_t* pBytes );

#if (UDS0_CAN_HW_TX_ABORT == 0x01u)
/**
 * This function abort the ongoing transmission of the CAN message which is pending at the CAN
 * driver and not transmitted yet.
 *
 * Note that:
 *  - This function is suppose to never fail on cancling of the pending transmit request.
 *
 * \param [in] msgId        The CAN message ID which is used for the message.
 */
void UdsCanApp_AbortTransmit( uint32_t msgId );
#endif /* (UDS0_CAN_HW_TX_ABORT == 0x01u) */

#endif /* _UDSCAN_INF_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
