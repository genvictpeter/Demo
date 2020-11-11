/**
*
* \file
*
* \brief This file defines a body for each of the callback functions which the UDS Application Layer
* expects the user to implement.
*
* By their nature these callbacks depend on the user's Diagnostic application and cannot be implemented generically;
* so many of the supplied function bodies simply return an error. Others contain a sample implementation which
* may be suitable in certain limited circumstances.
*
* Areas which require further implementation or review are marked with "TODO" comments.
*
* Some callbacks are needed only if certain UDS services are enabled and implemented. Preprocessor symbols of the
* form UDS_ENABLE_XXX indicate which callbacks are required in which circumstances.
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

#ifndef _UDS_CALLBACKS_H
#define _UDS_CALLBACKS_H


#include "uds_target.h"


/*lint -e750*//*lint -e752*/

/******************************************************************************
 *
 * General functions and types
 *
 *****************************************************************************/

extern uint8_t UDS_FN_TYPE UdsApp_87LnkCtrl_ChkFixedBaudrateIsAllowed(uint8_t i_FixedBaudRateId2Chk);
extern uint8_t UDS_FN_TYPE UdsApp_87LnkCtrl_Transit2FixedBaudrate(uint8_t i_FixedBaudRateId2Transit);
extern uint8_t UDS_FN_TYPE UdsApp_87LnkCtrl_ChkSpecifiedBaudrateIsAllowed(uint8_t i_SpecBaudRateHByte,
																		uint8_t i_SpecBaudRateMByte,
																		uint8_t i_SpecBaudRateLByte);
extern uint8_t UDS_FN_TYPE UdsApp_87LnkCtrl_TransitSpecifiedBaudrate( uint8_t i_SpecBaudRateHByte,
																	uint8_t i_SpecBaudRateMByte,
																	uint8_t i_SpecBaudRateLByte);
extern uint8_t UDS_FN_TYPE UdsApp_27SecuAcc_IsSpecifiedSALHasUnlocked(uint8_t i_lub_Sal2Checked);

#endif /* _UDS_CALLBACKS_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/


