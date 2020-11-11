/**
*
* \file
*
* \brief Public definitions and declarations
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
******************************************************************************/

#ifndef _UDSTP_PUB_H
#define _UDSTP_PUB_H



#include "uds_target.h"
#include "udstp_priv.h"



/*lint -e750*//*lint -e752*/

/******************************************************************************
 *
 * General functions and types
 *
 *****************************************************************************/

void				UDS_FN_TYPE	UdsTp_Initialize   				( void );
void				UDS_FN_TYPE	UdsTp_ServiceProc				( void );
uint8_t             UDS_FN_TYPE	UdsTp_NUSData_Request			( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint16_t msgLen, uint8_t* pMsgData );
void				UDS_FN_TYPE	UdsTp_NUSData_Confirmation		( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t nResult );
void				UDS_FN_TYPE	UdsTp_NUSData_indication		( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t nResult, uint16_t msgLen, uint8_t* pMsgData );
void				UDS_FN_TYPE	UdsTp_NUSData_FFindication		( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint16_t msgLen );
void				UDS_FN_TYPE	UdsTp_NChangeParam_Request		( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t param, uint8_t paramValue );
void				UDS_FN_TYPE	UdsTp_NChangeParam_Confirmation	( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t param, uint8_t result );

#endif /* _UDSTP_PUB_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
