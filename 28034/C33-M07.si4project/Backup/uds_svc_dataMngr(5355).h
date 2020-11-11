/**
*
* \file
*
* \ Data Structure Definition for UDS Diagnostic Data Manager for Reading, 
*   Writing and IOControl operation.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id:Version 1.0 Revision 0 2012-07-08 Deng Yongqiang $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
*  UDS_1.0      | July/08/2012  |                         | Yongqiang Deng   *
* Creation of this file                                                      *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_SVC_DATA_MNGR_H
#define _UDS_SVC_DATA_MNGR_H



#include "main.h"
#include "uds_target.h"

extern void Uds_Generic_DatMgr_Init(void);
extern uint8_t  Uds_Generic_DatMgr_SearchTblByKey (uint16_t                         i_luwKey2Search,    /* searched ID */
                                                 UDS_DidDatMngSearchKeyType_t   i_lubSearchKeyType, /* uword(16bits) or ubyte(8bits) */
                                                 uint8_t const *                  lpub_lookUp, 		/* address of first ID in table */
                                                 uint8_t                          lub_entrySize );	/* size of a table entry */


#endif /* _UDS_SVC_DATA_MNGR_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
