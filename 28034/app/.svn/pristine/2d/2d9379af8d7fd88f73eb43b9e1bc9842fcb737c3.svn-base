/**
*
* \file
*
* \brief Preprocessor definitions derived from the UDS Application Layer configuration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 0 2012-07-05 Tan Yang $
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
*         update the code after 1st round integration with Customer running  *
*         sw project, change detail please refer to                          *
*         UDSonCAN Protocol Stack Release Note_v1_0r5.doc                    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Add one definition UDS_SESSION_TIMING_TICK_PERIOD which is used    *
*         as granularity of ticking session layer timer and application      *
*         timers in user application.                                        *
*         Resolution of timer values is changed from millisecond to          *
*         microsecond.                                                       *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*    to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t  *
*    to remove the similar coexisitn basic type for UINT8  uint8 and so on   *
*    to add the example DID interfaces                                       *
*    to add the data and configure for the respective services               *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_CONFDEFS_H
#define _UDS_CONFDEFS_H



#include "FlashDrv_ExtItf.h"
//#include "eed_data.h"
#include "Error.h"
#include "EepromManage.h"


#ifndef TC17XX_FBL_USING_POLLING_TO_DRIVE
#define  TC17XX_FBL_USING_POLLING_TO_DRIVE
#endif



/*lint -e750*/

/* [MISRA 2004 Rules 1.2, 1.4 and 5.1] - Identifier clash */
/*lint -e621*/

/******************************************************************************
*
* Uds Services preprocessor definitions
*
******************************************************************************/

/* Define Number of Uds Services that supported by the Uds Application
 *
 * This number will be used when looking up UDSservice handlers in Uds_ServiceTable[].
 */
//#define UDS_NUM_OF_SERVICES							25u
// if support ISO 15031-5
#define UDS_NUM_OF_SERVICES							29u


/* Define Uds Services that supported by the Uds Application
 *
 * "Define" means define the string here for the service that will be supported by the UDS application.
 * [Note]
 * These definitions are only for preprocessor processing in uds_priv.h, and all service functions will
 * need to be implemented in corresponding files.
 */
/* If we do not apply this diagnostic service, we assign the function call to it to a predefined handler. */
/* Diagnostic and Communication Management functional unit Services - UDS_DCM */
#define UDS_ENABLE_DIAGNOSTICSESSIONCONTROL			/* 0x10 - Uds_DiagSessionControl */
#define UDS_ENABLE_ECURESET							/* 0x11 - Uds_EcuReset */
#define UDS_ENABLE_SECURITYACCESS					/* 0x27 - Uds_SecurityAccess */
#define UDS_ENABLE_COMMUNICATIONCONTROL				/* 0x28 - Uds_CommunicationControl */
#define UDS_ENABLE_TESTERPRESENT					/* 0x3E - Uds_TesterPresent */
// #define UDS_ENABLE_ACCESSTIMINGPARAMETER			/* 0x83 - Uds_AccessTimingParameter */
// #define UDS_ENABLE_SECUREDDATATRANSMISSION			/* 0x84 - Uds_SecuredDataTransmission */
#define UDS_ENABLE_CONTROLDTCSETTING				       /* 0x85 - Uds_ControlDTCSetting */
// #define UDS_ENABLE_RESPONSEONEVENT					/* 0x86 - Uds_ResponseOnEvent */
// #define UDS_ENABLE_LINKCONTROL						/* 0x87 - Uds_LinkControl */
/* Data Transmission functional unit Services - UDS_DTC */
#define UDS_ENABLE_READDATABYIDENTIFIER				/* 0x22 - Uds_ReadDataByIdentifier */
// #define UDS_ENABLE_READMEMORYBYADDRESS				/* 0x23 - Uds_ReadMemoryByAddress */
// #define UDS_ENABLE_READSCALINGDATABYIDENTIFIER		  /* 0x24 - Uds_ReadScalingDataByIdentifier */
// #define UDS_ENABLE_READDATABYPERIODICIDENTIFIER	  	/* 0x2A - Uds_ReadDataByPeriodicIdentifier */
// #define UDS_ENABLE_DYNAMICALLYDEFINEDATAIDENTIFIER	/* 0x2C - Uds_DynamicallyDefineDataIdentifier */
#define UDS_ENABLE_WRITEDATABYIDENTIFIER			/* 0x2E - Uds_WriteDataByIdentifier */
//#define UDS_ENABLE_WRITEMEMORYBYADDRESS				/* 0x3D - Uds_WriteMemoryByAddress */
/* Stored Data Transmission functional unit Services */
#define UDS_ENABLE_CLEARDIAGNOSTICINFORMATION		/* 0x14 - Uds_ClearDiagnosticInformation */
#define UDS_ENABLE_READDTCINFORMATION				        /* 0x19 - Uds_ReadDTCInformation */
/* InputOutput Control functional unit Services */
#define UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER	  /* 0x2F - Uds_InputOutputControlByIdentifier */
/* Remote Activation of Routine functional unit Services */
#define UDS_ENABLE_ROUTINECONTROL					/* 0x31 - Uds_RoutineControl */
/* Upload and Download functional unit Services */
//#define UDS_ENABLE_REQUESTDOWNLOAD					/* 0x34 - Uds_RequestDownload */
//#define UDS_ENABLE_REQUESTUPLOAD					/* 0x35 - Uds_RequestUpload */
//#define UDS_ENABLE_TRANSFERDATA						/* 0x36 - Uds_TransferData */
//#define UDS_ENABLE_REQUESTTRANSFEREXIT				/* 0x37 - Uds_RequestTransferExit */

/******************************************************************************
*
* Uds Session preprocessor definitions
*
******************************************************************************/

/* Define Number of non-default sessions
 *
 * UDS_NUM_NON_DEFAULT_SESSION: number of non-default sessions.
 * UDS_NUM_SESSIONS: number of all sessions, inc. default-session.
 */
#define UDS_NUM_NON_DEFAULT_SESSION					3u/* TODO */
#define UDS_NUM_SESSIONS                                                     4u/* TODO */

/* Define Uds server type
 *
 * Unit: enum
	LOCAL_SERVER	=0,
	REMOTE_SERVER	=1
 */
#define UDS_SERVER_TYPE								LOCAL_SERVER/* TODO */

/* Define Address Information for Server and Client
 *
	uint8_t type of address informaiton.
 */
#define UDS_CLIENT_ADDR								(uint8_t)(22)/* TODO */
#define UDS_SERVER_ADDR								(uint8_t)(11)/* TODO */
#define UDS_REMOTE_ADDR								(uint8_t)(44)/* TODO */

/* Define schedule period for Uds session manager
 * - Uds diagnostic data interpretation rate
 * Unit: ms
 *
 * This value shall be smaller than P2CAN_SRV_MAX_xxx_VAL, but this definition is only
 * used for configuration check and not used in code.
 * - UDS_DIAGDATA_INTERP_RATE < P2CAN_SRV_MAX_xxx_VAL
 */
#ifdef TC17XX_FBL_USING_INTERRUPT_TO_DRIVE
#define UDS_DIAGFAST_TASK_RATE					(400u)   /* TODO */	/**   unit : us  200 us , UDSonCAN_req 70 */
#define UDS_DIAGDATA_INTERP_RATE					(400u)    /* TODO */	/**   unit : us  400us , UDSonCAN_req 70 */
#endif

#ifdef TC17XX_FBL_USING_POLLING_TO_DRIVE
#define UDS_DIAGFAST_TASK_RATE					(1000u)   /* TODO */	/**   unit : us  4 us , UDSonCAN_req 70 */
#define UDS_DIAGDATA_INTERP_RATE					(1000u)    /* TODO */	/**   unit : us  4s , UDSonCAN_req 70 */


#endif
/* Define APdu Max Length of data to be received/transmited
 *
 * uint16_t type
 * maxium available length is 12bit(1~4095) as defined in ISO15765-2.
 */
 /* duplicate definition for this macro constant , so remove 
  */
//#define ISO15765_APDU_MSGDATA_LENGTH		  		300u /* TODO */

/* Define whether enable change STmin and BlockSize of transport layer.
 *
 * Not ISO standard required.
 */
#define UDS_ENABLE_CHANGEPARAMETER

/* Define max number of service request/indication can be buffered by session.
 *
 * Not ISO standard required.
 */
#define UDS_SESSIONBUF_RX_NUM						1u/* TODO */

/* Define max number of service response can be buffered by session.
 *
 * Not ISO standard required.
 */
#define UDS_SESSIONBUF_TX_NUM						1u/* TODO */

/******************************************************************************
*
* Uds Application Layer and Session Layer Timing definitions
*
******************************************************************************/

/* Define tick period for application layer and session Layer timing.
 *
 * Unit: us
 * This value shall be configured to period of function that is used to tick these timings.
 */
 #ifdef TC17XX_FBL_USING_INTERRUPT_TO_DRIVE

#define UDS_SESSION_TIMING_TICK_PERIOD			    500u /* TODO */
#define FBLUDS_C_TASK_CYCLE_ZOOM       (0x01u)

#endif

 #ifdef TC17XX_FBL_USING_POLLING_TO_DRIVE

#define UDS_SESSION_TIMING_TICK_PERIOD			    500u /* TODO */
#define FBLUDS_C_TASK_CYCLE_ZOOM                    (0x01u)

#endif



/* Configured limiter of session Manager to continuously waiting for application to finish service processing
 * and give back final response to avoid session manager protentially hooked up during (enhanced)78hex processing
 * window by not receiving final service processing result.
 */

/* Define UDS Application Layer and Session Layer Timing Parameters
 * ( Compliant to ISO15765-3 )
 *
 * in Unit of 1ms (Configured value)
 * in Unit of 1us (Real value used by appliation)
 * The configured Uds App layer timing and session timing timeout value will be further aligned with
 * the schedule period of session manager(diagnostic data interpretation rate).
 *
 */
#define P2CAN_SERVER_MAX_ALLOWED_TO_NUM                    (uint8_t)(10u) 

#define P2CAN_SERVER_MAX_DEFAULT_VAL				       (uint32_t)(50000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 50000us = 50ms */
#define P2STAR_CAN_SERVER_MAX_DEFAULT_VAL			(uint32_t)(2000000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 2000000us = 2000ms = 2s */
#define P2STAR_CAN_SERVER_CONSNEGRESP_DEFAULT_VAL	(uint32_t)(P2STAR_CAN_SERVER_MAX_DEFAULT_VAL>>1u)
#define SESSION_TIMING_S3SERVER_VAL					(uint32_t)(5000000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 5000000us = 5000ms = 5s */
#define PROG_SESSION_RESET_DELAY_VAL				       (uint32_t)(20000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 20000us = 20ms */

#define P2CAN_SERVER_MAX_DEFAULT                                    (uint32_t)(P2CAN_SERVER_MAX_DEFAULT_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_MAX_DEFAULT                          (uint32_t)(P2STAR_CAN_SERVER_MAX_DEFAULT_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_CONSNEGRESP_DEFAULT          (uint32_t)(P2STAR_CAN_SERVER_CONSNEGRESP_DEFAULT_VAL / UDS_DIAGDATA_INTERP_RATE)
#define SESSION_TIMING_S3SERVER                                        (uint32_t)(SESSION_TIMING_S3SERVER_VAL / UDS_DIAGFAST_TASK_RATE)

#define PROG_SESN_RESET_DELAY_TIMING                             (uint32_t)(PROG_SESSION_RESET_DELAY_VAL / UDS_DIAGFAST_TASK_RATE)

/* Define UDS Application Layer Timing Parameters for non-default session.
 *
 * in Unit of 1ms (Configured value)
 * in Unit of 1us (Real value used by appliation)
 * The configured Uds App layer timing and session timing timeout value will be further aligned with
 * the schedule period of session manager(diagnostic data interpretation rate).
 *
 * [Note]: Each defined non-default session shall have it's own specific application layer
 * timing parameters.
 */
#define P2CAN_SERVER_MAX_PGM_VAL				       (uint32_t)(500000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 500000us = 500ms */
#define P2STAR_CAN_SERVER_MAX_PGM_VAL			(uint32_t)(5000000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 5000000us = 5000ms = 5s */
#define P2STAR_CAN_SERVER_CONSNEGRESP_PGM_VAL	(uint32_t)(P2STAR_CAN_SERVER_MAX_PGM_VAL >> 1u)

#define P2CAN_SERVER_MAX_PGM                                     (uint32_t)(P2CAN_SERVER_MAX_PGM_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_MAX_PGM                           (uint32_t)(P2STAR_CAN_SERVER_MAX_PGM_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_CONSNEGRESP_PGM           (uint32_t)(P2STAR_CAN_SERVER_CONSNEGRESP_PGM_VAL / UDS_DIAGDATA_INTERP_RATE)

/* Define UDS Application Layer Timing Parameters for non-default session.
 *
 * in Unit of 1ms (Configured value)
 * in Unit of 1us (Real value used by application)
 * The configured Uds App layer timing and session timing timeout value will be further aligned with
 * the schedule period of session manager(diagnostic data interpretation rate).
 *
 * [Note]: Each defined non-default session shall have it's own specific application layer
 * timing parameters.
 */
#define P2CAN_SERVER_MAX_EXTENDED_VAL                                 (uint32_t)(500000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 500000us = 500ms */
#define P2STAR_CAN_SERVER_MAX_EXTENDED_VAL                       (uint32_t)(5000000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 5000000us = 5000ms = 5s */
#define P2STAR_CAN_SERVER_CONSNEGRESP_EXTENDED_VAL       (uint32_t)(P2STAR_CAN_SERVER_MAX_EXTENDED_VAL >> 1)

#define P2CAN_SERVER_MAX_EXTENDED                                          (uint32_t)(P2CAN_SERVER_MAX_EXTENDED_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_MAX_EXTENDED                                (uint32_t)(P2STAR_CAN_SERVER_MAX_EXTENDED_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_CONSNEGRESP_EXTENDED                (uint32_t)(P2STAR_CAN_SERVER_CONSNEGRESP_EXTENDED_VAL / UDS_DIAGDATA_INTERP_RATE)

/* Define UDS Application Layer Timing Parameters for non-default session.
 *
 * in Unit of 1ms (Configured value)
 * in Unit of 1us (Real value used by application)
 * The configured Uds App layer timing and session timing timeout value will be further aligned with
 * the schedule period of session manager(diagnostic data interpretation rate).
 *
 * [Note]: Each defined non-default session shall have it's own specific application layer
 * timing parameters.
 */
#define P2CAN_SERVER_MAX_ECUSPL_VAL                                     (uint32_t)(500000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 500000us = 500ms */
#define P2STAR_CAN_SERVER_MAX_ECUSPL_VAL                           (uint32_t)(5000000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* 5000000us = 5000ms = 5s */
#define P2STAR_CAN_SERVER_CONSNEGRESP_ECUSPL_VAL           (uint32_t)(P2STAR_CAN_SERVER_MAX_ECUSPL_VAL >> 1u)

#define P2CAN_SERVER_MAX_ECUSPL                                             (uint32_t)(P2CAN_SERVER_MAX_ECUSPL_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_MAX_ECUSPL                                   (uint32_t)(P2STAR_CAN_SERVER_MAX_ECUSPL_VAL / UDS_DIAGDATA_INTERP_RATE)
#define P2STAR_CAN_SERVER_CONSNEGRESP_ECUSPL                   (uint32_t)(P2STAR_CAN_SERVER_CONSNEGRESP_ECUSPL_VAL / UDS_DIAGDATA_INTERP_RATE)

/******************************************************************************
*
* UDS Services Application Specific preprocessor definitions
*
******************************************************************************/

/*****************************************************************************
 *	Diagnostic Services Configuration Parameters , listed as alphanumeric    *
 *****************************************************************************/

/************************************************************
 *	1. DiagnosticSessionControl(0x10)						*
 ***********************************************************/
/*
 * If the server only allow a client with a certain identifier(client diagnostic address) to start
 * a specific new diagnostic session, we define "UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK".
 *
   [Note]: for which client(client diagnostic address) is allowed for which session is seperatly defined
   and will be filled in configuration of the corresponding session data bodies in uds_conf.c
   Default session has no requirement on this.
 */
#define UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK
#ifdef  UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK
	#define PROGRAMMING_SESSION_REQ_CLIENTADDR			(uint8_t)(22u)/* TODO */
	#define EXTENDED_SESSION_REQ_CLIENTADDR				(uint8_t)(22u)/* TODO */
	#define ECU_SUPPLIER_SESSION_REQ_CLIENTADDR			(uint8_t)(22u)/* TODO */
#endif /* UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK */


/************************************************************
 *	2. ECUReset(0x11)										*
 ***********************************************************/
/*
 * This parameter indicates to the client the minimum time of the stand-by sequence the server
 * will remain in the power-down sequence when required sub-function is enableRapidPowerShutDown.
 *
 * The resolution of this parameter is one (1) second per count.
 * The following values are valid:
	00 ¨C FE hex: 	0 ¨C 254s powerDownTime
	FF hex: 		indicates a failure or time not available
 */
 
/* legend : ABS: absolute;  REL : relative (unitless) */
 
#define UDS_C_ECURESET_POWER_DOWN_ABS_TIME				(80000u*FBLUDS_C_TASK_CYCLE_ZOOM)	/* unit : us, 80000us  = 80ms */ /* TODO */

/* uds 0x11 EcuReset Service cyclic task period value  */
#define UDS_C_11ECURESET_CYC_TASK_PERIOD      			               UDS_DIAGDATA_INTERP_RATE   /* 0x11EcuReset process is put into 100us task */ 
/*
* uds  0x11 EcuReset Service reset delay timer timeout absolute value 80000us
* uds0x11 EcuReset Service reset delay timer timeout relative value (80000us/200us == 400u )
*  Note : to set the relative timeout value directly , to avoid use divide operation
*  UDS_C_ECURESET_POWER_DOWN_ABS_TIME/UDS_C_11ECURESET_CYC_TASK_PERIOD == 80000us/200us 
*/
#define UDS_C_ECURESET_POWER_DOWN_REL_TIME   			(uint32_t)(UDS_C_ECURESET_POWER_DOWN_ABS_TIME/UDS_C_11ECURESET_CYC_TASK_PERIOD) 


/*
 * Number of sub-functions supported by this service
 */
#define UDS_ECURESET_NUM_SUBFUNC						       3u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define UDS_C_ECURESET_SUBFUNC_POWERONRESET				0x01u
#define UDS_C_ECURESET_SUBFUNC_KEYONOFFRESET		  	0x02u
#define UDS_C_ECURESET_SUBFUNC_SOFTRESET				0x03u
/* legend : ENA : enable ; RPD : rapid ; PDN : Power Down */
#define UDS_C_ECURESET_SUBFUNC_ENA_RPD_PDN_RESET		0x04u
#define UDS_C_ECURESET_SUBFUNC_DIS_RPD_PDN_RESET		0x05u


/************************************************************
 *	3. ClearDiagnosticInformation(0x14)						*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_CLEARDTC_NUM_SUBFUNC						0u/* TODO*/

/* legend : CLR : clear , TYP : type, SPEC : specified
 * 			GRP : group */
#define UDS_C_CLRDTC_CLRTYP_ALL_DTCS        			       0x01u
#define UDS_C_CLRDTC_CLRTYP_SPEC_GRP_DTCS   			0x02u
#define UDS_C_CLRDTC_CLRTYP_SPEC_ONE_DTC    			0x03u

/************************************************************
 *	4. ReadDTCInformation(0x19)								*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_READDTC_INFO_SUBFUNC						 3u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define READDTC_REPORT_NUMDTC_BYSTATUSMSK				0x01u
#define READDTC_REPORT_DTC_BYSTATUSMSK					0x02u
#define READDTC_REPORT_DTC_SNAPSHOT_ID					0x03u
#define READDTC_REPORT_DTCSNAPSHOT_BYDTCNUM			    0x04u
#define READDTC_REPORT_DTC_EXTDAT_RCD_BYDTCNUM          0x06u
#define READDTC_REPORT_SUPPORTED_DTC                    0x0Au

#define UDS_C_SUPPORTED_DTC_ST_MASK                                    (0xFFu)
#define UDS_C_DTC_CODE_FORMAT_ISO15031_6_FMT                 (0x00u)
#define UDS_C_DTC_CODE_FORMAT_ISO14229_1_FMT                 (0x01u)
#define UDS_C_DTC_CODE_FORMAT_SAEJ1939_73_FMT               (0x02u)
#define UDS_C_DTC_CODE_FORMAT_ISO11992_4_FMT                 (0x03u)


/************************************************************
 *	5. ReadDataByIdentifier(0x22)							*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_READDATBYDID_NUM_SUBFUNC					0x00u /* TODO*/

#define UDS_C_RD_DAT_BY_DID_MAX_REQ_LEN       			0x0Bu /* 11 bytes, including sid , 5 DIDs */


#define UDS_C_DID_ASW_FNGR_PRNT_F184       ((uint16_t)0xF184u)
#define UDS_C_DID_LEN_F184                 9u // E2_ITF_I_LEN_APP_SW_FNGR_PRINT
#define UDS_C_DID_ATTR_F184                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0|UDS_C_DID_ATR_WT_SAL11|UDS_C_DID_ATR_WT_SESN_EXTD)/*App only read & Boot Write*/
#define UDS_ITF_IMP_DAT_PTR_F184           (&SW_Finger[0x00u]) // E2_ITF_I_DP_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_RD_FNCPTR_F184         NULL   /* need the interface to read data  */
#define UDS_ITF_IMP_E2_BLKIDX_F184         0x00u //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_F184         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_F184        NULL   /* need the interface to check data prior write data */



#define UDS_C_DID_ASW_FNGR_PRNT_F183       ((uint16_t)0xF183u)
#define UDS_C_DID_LEN_F183                 10u // E2_ITF_I_LEN_APP_SW_FNGR_PRINT
#define UDS_C_DID_ATTR_F183                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)
#define UDS_ITF_IMP_DAT_PTR_F183           (uint8_t *)(&ECUBootDataVersion[0x00u]) // E2_ITF_I_DP_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_RD_FNCPTR_F183         NULL   /* need the interface to read data  */
#define UDS_ITF_IMP_E2_BLKIDX_F183         0x00u //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_F183         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_F183        NULL   /* need the interface to check data prior write data */



#define UDS_C_DID_VIN_F190       			((uint16_t)0xF190u)
#define UDS_C_DID_LEN_F190                 17u // E2_ITF_I_LEN_APP_SW_FNGR_PRINT
#define UDS_C_DID_ATTR_F190                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0|UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL11|UDS_C_DID_ATR_WT_SESN_EXTD)
#define UDS_ITF_IMP_DAT_PTR_F190          (&VIN[0x00u]) // E2_ITF_I_DP_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_RD_FNCPTR_F190         NULL   /* need the interface to read data  */
#define UDS_ITF_IMP_E2_BLKIDX_F190         0x10u //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_F190         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_F190        NULL   /* need the interface to check data prior write data */

#define UDS_C_DID_MOT_CODE_02FE       	   ((uint16_t)0x02FEu)
#define UDS_C_DID_LEN_02FE                 2u // E2_ITF_I_LEN_APP_SW_FNGR_PRINT
#define UDS_C_DID_ATTR_02FE                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0|UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL11|UDS_C_DID_ATR_WT_SESN_EXTD)
#define UDS_ITF_IMP_DAT_PTR_02FE           (&Mcu_Configuration[0]) // E2_ITF_I_DP_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_RD_FNCPTR_02FE         NULL   /* need the interface to read data  */
#define UDS_ITF_IMP_E2_BLKIDX_02FE         0x3Eu //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_02FE         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_02FE        check_DID   /* need the interface to check data prior write data */

#define UDS_C_DID_MOT_CODE_02FF       	   ((uint16_t)0x02FFu)
#define UDS_C_DID_LEN_02FF                 30u // E2_ITF_I_LEN_APP_SW_FNGR_PRINT
#define UDS_C_DID_ATTR_02FF                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0|UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL11|UDS_C_DID_ATR_WT_SESN_EXTD)
#define UDS_ITF_IMP_DAT_PTR_02FF          (&MotCode[0x00u]) // E2_ITF_I_DP_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_RD_FNCPTR_02FF         NULL   /* need the interface to read data  */
#define UDS_ITF_IMP_E2_BLKIDX_02FF         0x20u //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_02FF         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_02FF        NULL   /* need the interface to check data prior write data */

#define UDS_C_DID_SYS_PART_NUMBER_F187          ((uint16_t)0xF187u)
#define UDS_C_DID_LEN_F187                 9u // E2_ITF_I_LEN_SYS_SUPLR_ID
#define UDS_C_DID_ATTR_F187                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)
#define UDS_ITF_IMP_DAT_PTR_F187            (uint8_t *)(&PartNumber[0x00u])// E2_ITF_I_DP_SYS_SUPLR_ID
#define UDS_ITF_IMP_RD_FNCPTR_F187         NULL   /* need the interface to read data  */


#define UDS_C_DID_SYS_SUP_ID_F18A          ((uint16_t)0xF18Au)
#define UDS_C_DID_LEN_F18A                 10u // E2_ITF_I_LEN_SYS_SUPLR_ID
#define UDS_C_DID_ATTR_F18A                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)
#define UDS_ITF_IMP_DAT_PTR_F18A           (uint8_t *)(&SuppID[0x00u]) // E2_ITF_I_DP_SYS_SUPLR_ID
#define UDS_ITF_IMP_RD_FNCPTR_F18A          NULL  /* need the interface to read data  */


#define UDS_C_DID_APP_HW_VER_F191         ((uint16_t)0xF191u)
#define UDS_C_DID_LEN_F191                 9u // E2_ITF_I_LEN_BOOT_SW_VER
#define UDS_C_DID_ATTR_F191                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)
#define UDS_ITF_IMP_DAT_PTR_F191           (uint8_t *)(&HW_VER[0x00u]) // E2_ITF_I_DP_BOOT_SW_VER
#define UDS_ITF_IMP_RD_FNCPTR_F191         NULL

#define UDS_C_DID_APP_SW_VER_F195         ((uint16_t)0xF195u)
#define UDS_C_DID_LEN_F195                 9u // E2_ITF_I_LEN_BOOT_SW_VER
#define UDS_C_DID_ATTR_F195                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)
#define UDS_ITF_IMP_DAT_PTR_F195           (uint8_t *)(&SW_VER[0x00u]) // E2_ITF_I_DP_BOOT_SW_VER
#define UDS_ITF_IMP_RD_FNCPTR_F195         NULL

#define UDS_C_DID_PROGRAM_DATE_F199        ((uint16_t)0xF199u)
#define UDS_C_DID_LEN_F199                 3u // E2_ITF_I_LEN_REPROG_DATE
#define UDS_C_DID_ATTR_F199                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0|UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL11|UDS_C_DID_ATR_WT_SESN_EXTD)
#define UDS_ITF_IMP_DAT_PTR_F199           (uint8_t *)(&PRO_DATA[0x00u]) // E2_ITF_I_DP_REPROG_DATE
#define UDS_ITF_IMP_RD_FNCPTR_F199         NULL
#define UDS_ITF_IMP_E2_BLKIDX_F199         0x20u //E2_C_IDX_APP_SW_FNGR_PRINT
#define UDS_ITF_IMP_WT_FNCPTR_F199         NULL   /* need the interface to write data */
#define UDS_ITF_IMP_CHK_FNCPTR_F199        NULL   /* need the interface to check data prior write data */


#define UDS_C_DID_ATTR_SREC                (UDS_C_DID_ATR_ENA_RD|UDS_C_DID_ATR_RD_SAL0)

#define UDS_ITF_IMP_DAT_PTR_0200           (uint8_t *)( & ErrSubmit.ErrLog.ErrDCVoltage)
#define UDS_ITF_IMP_DAT_PTR_0201           (uint8_t *)( & ErrSubmit.ErrLog.DC_Cur)
#define UDS_ITF_IMP_DAT_PTR_0202           (uint8_t *)( & ErrSubmit.ErrLog.ErrMotorModeCmd)
#define UDS_ITF_IMP_DAT_PTR_0203           (uint8_t *)( & ErrSubmit.ErrLog.ErrMCUState)
#define UDS_ITF_IMP_DAT_PTR_0204           (uint8_t *)( & ErrSubmit.ErrLog.ErrTorqueCmd)
#define UDS_ITF_IMP_DAT_PTR_0205           (uint8_t *)( & ErrSubmit.ErrLog.ErrTorqueFed)
#define UDS_ITF_IMP_DAT_PTR_0206           (uint8_t *)( & ErrSubmit.ErrLog.ErrSpeedSet)
#define UDS_ITF_IMP_DAT_PTR_0207           (uint8_t *)( & ErrSubmit.ErrLog.ErrSpeed)
#define UDS_ITF_IMP_DAT_PTR_0208           (uint8_t *)( & ErrSubmit.ErrLog.ErrMCUTemp)
#define UDS_ITF_IMP_DAT_PTR_0209           (uint8_t *)( & ErrSubmit.ErrLog.ErrMotorTemp)
#define UDS_ITF_IMP_DAT_PTR_020A           (uint8_t *)( & ErrSubmit.ErrLog.ErrUd)
#define UDS_ITF_IMP_DAT_PTR_020B           (uint8_t *)( & ErrSubmit.ErrLog.ErrUq)
#define UDS_ITF_IMP_DAT_PTR_020C           (uint8_t *)( & ErrSubmit.ErrLog.ErrIdRef)
#define UDS_ITF_IMP_DAT_PTR_020D           (uint8_t *)( & ErrSubmit.ErrLog.ErrIqRef)
#define UDS_ITF_IMP_DAT_PTR_020E           (uint8_t *)( & ErrSubmit.ErrLog.ErrIdFed)
#define UDS_ITF_IMP_DAT_PTR_020F           (uint8_t *)( & ErrSubmit.ErrLog.ErrIqFed)
#define UDS_ITF_IMP_DAT_PTR_0210           (uint8_t *)( & ErrSubmit.ErrLog.Err12V)

//#define UDS_ITF_IMP_DAT_PTR_0211

#define UDS_ITF_IMP_DAT_PTR_0212           (uint8_t *)( & ErrSubmit.ErrLog.ErrDriveState)
#define UDS_ITF_IMP_DAT_PTR_0213           (uint8_t *)( & ErrSubmit.ErrLog.ErrState)
#define UDS_ITF_IMP_DAT_PTR_0214           (uint8_t *)( & ErrSubmit.ErrLog.ErrIGBTTemp)
#define UDS_ITF_IMP_DAT_PTR_0215           (uint8_t *)( & ErrSubmit.ErrLog.ErrIGBTTemp)
#define UDS_ITF_IMP_DAT_PTR_0216           (uint8_t *)( & ErrSubmit.ErrLog.ErrIGBTTemp)
#define UDS_ITF_IMP_DAT_PTR_0217           (uint8_t *)( & ErrSubmit.ErrLog.Angle)
#define UDS_ITF_IMP_DAT_PTR_0218           (uint8_t *)( & ErrSubmit.ErrLog.AngleInit)


/************************************************************
 *	7. ReadScalingDataByIdentifier(0x24)	             	*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_READSCALEDATBYID_NUM_SUBFUNC				0x00u /* TODO*/


/************************************************************
 *	8. SecurityAccess(0x27)									*
 ***********************************************************/
/* Note: Definitions for below SecurityAccess related parameters are defined identially for all sessions,
 * If user application required unic parameter values shall be defined and configured, then user shall
 * define each set of parameters for each specific session.
 *
 * Time units defined here are 1ms
 */
#define UDS_SECURITYACCESS_DELAYTIMEONBOOT			 	(10000u) /* unit : ms, 10000 ms  = 10s , TODO */
#define UDS_SECURITYACCESS_DELAYTIME				 	(10000u) /* TODO */
#define UDS_SECURITYACCESS_NUM_ATTDELAY					(5u) /* TODO */
#define UDS_SECURITYACCESS_NUM_ATTLOCK					(5u) /* TODO */
#define UDS_SECURITYACCESS_SEEDKEY_SIZE					(4u) /* TODO */
/* legend : ABS: absolute;  REL : relative (unitless) */
#define UDS_C_SECUACC_RETRY_DELAY_ABS_TIME				(10000000u*FBLUDS_C_TASK_CYCLE_ZOOM) /* 10s = 10000ms  */

/* uds 0x27SecurityAccess Service cyclic task period value  */
#define UDS_C_27SECUACC_CYC_TASK_PERIOD          		UDS_DIAGDATA_INTERP_RATE   /* 0x27SecurityAccess process is put into cyclic task */
/* uds 0x27SecurityAccess Service retry failure delay timer timeout absolute value 10000ms */
/* uds 0x27SecurityAccess Service retry failure delay timer timeout relative value (10000ms/40ms == 250 ) */
/* Note : to set the relative timeout value directly , to avoid use divide operation */
/* UDS_C_SECUACC_RETRY_DELAY_ABS_TIME/UDS_C_27SECUACC_CYC_TASK_PERIOD == 10000000ms/200ms = 50000u */
#define UDS_C_SECUACC_RETRY_DELAY_REL_TIME   			(uint32_t)(UDS_C_SECUACC_RETRY_DELAY_ABS_TIME/UDS_C_27SECUACC_CYC_TASK_PERIOD) 

/*
 * This definition indicates whether only specific client can be able to acquire uolock of resources.
 *
	securityAccessDataRecord (ISO14229 9.4.2.3)
   [Note]: for which client(client diagnostic identification) is allowed for the security access is user
   optional and not defined in nether ISO14229 nor ISO15765-3.
 */
#define UDS_SECURITYACCESS_ENABLE_QUALIFYCHECK
#ifdef  UDS_SECURITYACCESS_ENABLE_QUALIFYCHECK
	#define SECURITYACCESS_REQ_CLIENTADDR				(uint8_t)(22u)/* TODO */
#endif /* UDS_SECURITYACCESS_ENABLE_QUALIFYCHECK */

/*
 * Number of sub-functions supported by this service
 */
#define UDS_SECURITYACCESS_NUM_SUBFUNC					2u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define SECURITYACCESS_REQUESTSEED						0x01u
#define SECURITYACCESS_SENDKEY							0x02u

/*
 * legend : 
 * SECU : Security; ACC: Access, REQ, Request
 * SAL1 : Security Access Level 1
 * SUB  : Submit
 */
#define UDS_C_SECU_ACC_SECU_LEVEL11            			(0x09u)
#define UDS_C_SECU_ACC_SECU_LEVEL1                      (0x01u)	
	
#define UDS_C_SECU_ACC_REQ_SEED_SAL11          			(0x11u)
#define UDS_C_SECU_ACC_REQ_SEED_SAL1          			(0x01u)	
	
#define UDS_C_SECU_ACC_SUB_KEY_SAL11           			(0x12u)
#define UDS_C_SECU_ACC_SUB_KEY_SAL1           			(0x02u)

#define UDS_C_SECU_ACC_NO_SEED_VALUE          			0x00u

#define UDS_C_SECU_ACC_KEY_MAX_NUM            			0x04u
#define UDS_C_SECU_ACC_SUBMIT_KEY_LEN         			0x06u // 0x05u

#define UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE   			0x00u
/* #define UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE2  		0x00u */
/* #define UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE3  		0x00u */
/* #define UDS_C_SECU_ACC_ALRDY_ULCKD_SED_BYTE4  		0x00u */
#define UDS_C_SECU_ACC_MAX_ALLOW_FAIL_ATMPT_NUM  		(0x03u)

#define UDS_C_SECU_ACC_SECU_LEVEL11_LOCKED   			(0x00u)
#define UDS_C_SECU_ACC_SECU_LEVEL2_LOCKED   			(0x00u)
#define UDS_C_SECU_ACC_SECU_LEVEL3_LOCKED   			(0x00u)

/************************************************************
 *	9. CommunicationControl(0x28)							*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_COMMCONTROL_NUM_SUBFUNC						2u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define UDS_C_COMMCONTROL_ENABLE_RX_ENABLE_TX			   0x00u
#define UDS_C_COMMCONTROL_ENABLE_RX_DISABLE_TX			   0x01u
#define UDS_C_COMMCONTROL_DISABLE_RX_ENABLE_TX			   0x02u
#define UDS_C_COMMCONTROL_DISABLE_RX_DISABLE_TX			   0x03u

#define UDS_C_COMCTRL_COM_TYP_TRAFFIC_MASK            	   0x03u
#define UDS_C_COMCTRL_COM_TYP_SUBNET_MASK             	   0xF0u

#define UDS_C_COMCTRL_COM_TYP_TRFC_NORM_COMM_MSG      	   0x01u
#define UDS_C_COMCTRL_COM_TYP_TRFC_NM_COMM_MSG        	   0x02u
#define UDS_C_COMCTRL_COM_TYP_TRFC_NORM_AND_NM_MSG    	   0x03u
 
#define UDS_C_COMCTRL_SUBNET_RCV_NODE_AND_ALL_CONNECT_NET  0x00u
#define UDS_C_COMCTRL_SUBNET_SPEC_NET_BY_NET_NUM_MIN       0x01u
#define UDS_C_COMCTRL_SUBNET_SPEC_NET_BY_NET_NUM_MAX       0x0Eu
#define UDS_C_COMCTRL_SUBNET_NET_REQ_RCVD_ON               0x0Fu

/************************************************************
 *	10. ReadDataByPeriodicIdentifier(0x2A)	             	*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_READDATBYPERIODICID_NUM_SUBFUNC				0x00u /* TODO*/

/*
 * Definition of maximum number of periodic dataidentifier can be simultaneously requested.
 *
 * [Note]: This definitions according to ISO14229 spec is vehicle manufacturer specific.
 *         and based on the ram resource available
 */
#define UDS_C_PERIODIC_DID_MAX_NUM						0x08u /* TODO: depends on rame available */
#define UDS_C_PERIODIC_DID_MAX_REQ_LEN                  10u

/*
 * Definition of periodic transmission rate
 *
 * Define values for interpretion of slowRate, mediumRate and fastRate for transmissionMode.
 * [Note]: This definitions according to ISO14229 spec is vehicle manufacturer specific.
 */
#define UDS_C_PERIODIC_DID_RATE_TYP_STOP         		0xFFu	/* TODO */
#define UDS_C_PERIODIC_DID_RATE_TYP_FIX          		0x01u	/* TODO */
#define UDS_C_PERIODIC_DID_RATE_TYP_SPEC 				0x02u	/* TODO */

#define UDS_C_PERIODIC_DID_RATE_UNIT     				10u		/* TODO: min rate unit is 10ms */

#define UDS_C_PERIODIC_DID_TXMOD_SENDATSLOWRATE         0x01u
#define UDS_C_PERIODIC_DID_TXMOD_SENDATMEDRATE          0x02u
#define UDS_C_PERIODIC_DID_TXMOD_SENDATFSTRATE          0x03u
#define UDS_C_PERIODIC_DID_TXMOD_STOPSENDING            0x04u

 
#define UDS_C_PERIODIC_DID_REL_SLOW_RATE                400u 	/* TODO: unitless 4000ms slow   fixed rate = 400 * 10 */
#define UDS_C_PERIODIC_DID_REL_MEDIUM_RATE              100u  	/* TODO: unitless 1000ms medium fixed rate = 100  * 10 */
#define UDS_C_PERIODIC_DID_REL_FAST_RATE                20u   	/* TODO: unitless 200ms  fast   fixed rate = 20   * 10 */

#define UDS_C_PERIODIC_DID_SPEC_RATE_MIN                5u		/* TODO: unitless 50ms  fastest   specified rate = 5   * 10 */
#define UDS_C_PERIODIC_DID_SPEC_RATE_MAX                65534u	/* TODO: unitless 655340ms = 655.34 s slowest specifed rate = 65534   * 40 */

/************************************************************
 *	11. DynamicallyDefineDataIdentifier(0x2C)            	*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_DYNDEFDATID_NUM_SUBFUNC						0x00u	/* TODO*/

/*
 * Definition of maximum number of dynamiclly define dataidentifier can be simultaneously requested.
 */
#define UDS_C_DYNA_DEF_DID_MAX_NUM						0x10u	/* TODO: depends on the ram resource available */


/************************************************************
 *	12. WriteDataByIdentifier(0x2E)							*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_WRITEBYDID_NUM_SUBFUNC						0x00u/* TODO*/

/*
 * Definition of maximum number of dataidentifier can be simultaneously requested
 * by ether ReadDataByIdentifier or WriteDataByIdentifier.
 *
 * [Note]: This definitions according to ISO14229 spec is vehicle manufacturer specific.
 */
#define UDS_DID_MAXNUM									0x01u/* TODO */
 
/*
 * Dataidentifier definition
 *
 * dataIdentifier (DID) is intended to identify a server-specific local data record.
 * The dataIdentifier value shall either exist in fixed memory or be temporarily stored in RAM if defined
 * dynamically by the service dynamicallyDefineDataIdentifier.
 *
 * [Note]: DataIdentifier definitions according to ISO14229 AnnexC.1 are vehicle manufacturer specific.
 */
/* TODO */


/************************************************************
 *	13. InputOutputControlByIdentifier(0x2F)				*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_IO_CTL_BY_ID_NUM_SUBFUNC					0x00u /* TODO*/
#define UDS_2FIOCTRL_MNGT_RCD_MAX_NUM                   0x10u /* TODO*/

#define UDS_C_DID_ECU_OUT_ST_3042                       ((uint16_t)0x3042u)
#define UDS_C_DID_LEN_3042                              ((uint8_t)0x02u)
#define UDS_C_DID_ATTR_3042                             (UDS_C_DID_ATR_ENA_IOCTL|UDS_C_DID_ATR_WT_SAL0|UDS_C_DID_ATR_WT_SESN_EXTD)
#define UDS_ITF_IMP_DAT_PTR_3042                        NULL

/************************************************************
 *	14. RoutineControl(0x31)								*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_ROUTINECTRL_NUM_SUBFUNC					0x03u /* TODO*/

/*
 * List all supported sub-function for this service
 */
#define ROUTINECTRL_START_ROUTINE					0x01u
#define ROUTINECTRL_STOP_ROUTINE					0x02u
#define ROUTINECTRL_REQ_ROUTINERESULT				0x03u

/* below will define the routine ID and the related routine interfaces. */

#define UDS_C_31RTNCTRL_VALID_RAM_START_ADD        (0xD4000000u) // (0xD0000000u)
#define UDS_C_31RTNCTRL_VALID_RAM_END_ADD            (0xD4009FFFu) // (0XD001BFFFu)

// #define UDS_C_31RTNCTRL_VALID_FLASH_START_ADD        (0xA0020000u)
#define UDS_C_31RTNCTRL_VALID_FLASH_START_ADD        (0xA0000000u) // (0xA001C000u)
#define UDS_C_31RTNCTRL_VALID_FLASH_END_ADD            (0xA027FFFFu) // (0xA03FFFFFu)

#define UDS_C_31RTNCTRL_ERS_MEM_TYP_IS_RAM              (0x01u) 
#define UDS_C_31RTNCTRL_ERS_MEM_TYP_IS_FLASH          (0x02u) 

#define UDS_C_34REQDNLD_VALID_RAM_START_ADD          (0xD4000000u)
#define UDS_C_34REQDNLD_VALID_RAM_END_ADD              (0XD4009FFFu)

#define UDS_C_34REQDNLD_VALID_FLASH_START_ADD        (0xA0010000u)
#define UDS_C_34REQDNLD_VALID_FLASH_END_ADD          (0xA027FFFFu)



#define UDS_C_RID_ERS_MEM_RTN_FD00                  ((uint16_t)0x0203u)
#define UDS_C_RID_ATTR_FD00                         (UDS_C_RID_ATR_ENA_RUN|UDS_C_RID_ATR_SECU_LVL_0|UDS_C_RID_ATR_SESN_DEFLT) //UDS_C_RID_ATR_SESN_EXTD)

#define UDS_C_RID_VLD_ARGU_NUM_FD00                0x04u // 
#define UDS_C_RID_RUN_TIM_LIMIT_FD00       ((uint32_t)((10000000u*FBLUDS_C_TASK_CYCLE_ZOOM)/UDS_DIAGDATA_INTERP_RATE))   /* unit us : 10000000us = 10000ms = 10s   */
#define UDS_C_RID_RUN_TIM_MIN                    ((uint32_t)(((100000u*FBLUDS_C_TASK_CYCLE_ZOOM)/UDS_DIAGDATA_INTERP_RATE))   /* unit us : 100ms   */

#define UDS_C_RID_EXP_POS_RSLT_FD00                 0x01u
#define UDS_C_RID_FP_START_RTN_FD00                 NULL
// E2DRV_ITF_EXP_EREASE_START_RTN   /* need the interface to start routine */
#define UDS_C_RID_FP_STOP_RTN_FD00                  NULL   /* need the interface to stop routine , if supporting stop routine operation */
#define UDS_C_RID_FP_RESULT_RTN_FD00                NULL // E2DRV_ITF_EXP_EREASE_GET_RESULT   /* need the interface to get the result of routine */
#define UDS_C_RID_FP_CHECK_RTN_FD00                 NULL   /* need the interface to check the input optional arguments of routine, if needed  */
#define UDS_C_RID_FP_FINISH_RTN_FD00                NULL // E2DRV_ITF_EXP_EREASE_IS_FINISHED   /* need the interface to get the finished state after routine running, if needed  */




/************************************************************
 *	15. RequestDownload (0x34)								*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_REQ_DNLD_NUM_SUBFUNC					0x00u /* TODO*/
#define UDS_C_34REQDNLD_VALID_REQ_LEN               0x0Bu /* 11 bytes currently */
/* valid data format identifier is : 0x00: 
   bit0~3: encryptingMethod : 00 : no encryupting ; 
   bit 4~7: compressMethod: 00 : no compress 
 */
#define UDS_C_34REQDNLD_VALID_DAT_FMT_ID            0x00u 

 /* valid address and length format identifier is : 0x44: 
   bit0~3: Len of MemoryAddress : 0x04: means must be 4 bytes , 32 bit address ; 
   bit4~7: Len of MemorySize : 0x40: means must also be 4 bytes, 32 bit unsigned integer; 
 */
#define UDS_C_34REQDNLD_VALID_ADD_LEN_FMT_ID        0x44u 

#define UDS_C_34REQDNLD_VALID_RSP_LEN_FMT_ID        0x20u
#define UDS_C_34REQDNLD_VALID_RSP_MSG_LEN           0x04u
/* max nuber block length is 256 bytes: TODO based on RAM resource */
#define UDS_C_34REQDNLD_VALID_MAX_NUM_BLK_LEN       UDS_C_REQ_DN_OR_UP_LD_BUF_SIZE  
#define UDS_C_34REQDNLD_USING_NUM_BLK_LEN           UDS_C_REQ_DN_OR_UP_LD_BUF_SIZE


#define UDS_C_REQ_DN_ADD_00030000                   ((uint32_t)0x00030000u)
#define UDS_C_REQ_DN_LEN_00030000                   ((uint32_t)0x000E0000u)
#define UDS_C_REQ_DN_ATTR_00030000                  (UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL0|UDS_C_DID_ATR_WT_SESN_PRGM)
#define UDS_ITF_IMP_DPTR_REQ_DN_00030000            (&rub_ReqDnUpldDataBuf[0x00u])
 
#define UDS_C_REQ_DN_ADD_D0000000                   ((uint32_t)0xD4000000u)
#define UDS_C_REQ_DN_LEN_D0000000                   ((uint32_t)0x0000A000u)
#define UDS_C_REQ_DN_ATTR_D0000000                  (UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL0|UDS_C_DID_ATR_WT_SESN_PRGM)
#define UDS_ITF_IMP_DPTR_REQ_DN_D0000000            (&rub_ReqDnUpldDataBuf[0x00u])

#define UDS_C_REQ_DN_ADD_A0020000                   ((uint32_t)0xA0020000u)
#define UDS_C_REQ_DN_LEN_A0020000                   ((uint32_t)0x003E0000u)
#define UDS_C_REQ_DN_ATTR_A0020000                  (UDS_C_DID_ATR_ENA_WT|UDS_C_DID_ATR_WT_SAL0|UDS_C_DID_ATR_WT_SESN_PRGM)
#define UDS_ITF_IMP_DPTR_REQ_DN_A0020000            (&rub_ReqDnUpldDataBuf[0x00u])






#define UDS_ITF_IMP_DPTR_REQ_DN_ANY_ADDR            (&rub_ReqDnUpldDataBuf[0x00u])


/************************************************************
 *	16. RequestUpload (0x35)								*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_REQ_UPLD_NUM_SUBFUNC					0x00u /* TODO*/


/************************************************************
 *	17. TransferData (0x36)									*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_TRANSFR_DAT_NUM_SUBFUNC					0x00u /* TODO*/

#define UDS_C_36TRNSFRDAT_VALID_RAM_START_ADD        (0xD4000000u)
#define UDS_C_36TRNSFRDAT_VALID_RAM_END_ADD            (0XD4009FFFu)

#define UDS_C_36TRNSFRDAT_VALID_FLASH_START_ADD      (0xA0010000u)
#define UDS_C_36TRNSFRDAT_VALID_FLASH_END_ADD        (0xA027FFFFu)

#define UDS_C_36TRNSFRDAT_ERS_MEM_TYP_IS_RAM         (0x01u)
#define UDS_C_36TRNSFRDAT_ERS_MEM_TYP_IS_FLASH       (0x02u)


/************************************************************
 *	18.   RequestTransferExit (0x37)						*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_REQ_TRANSFR_EXIT_NUM_SUBFUNC			0x00u /* TODO*/


/************************************************************
 *	19. WriteMemoryByAddress(0x3D)							*
 ***********************************************************/
 /*
 * Number of sub-functions supported by this service
 */
#define UDS_WR_MEM_BY_ADD_NUM_SUBFUNC				0x00u /* TODO*/
#define UDS_C_3DWTMEMBYADD_MIN_REQ_LEN      0x09u


/************************************************************
 *	20. TesterPresent(0x3E)									*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_TESTERPRESENT_NUM_SUBFUNC				0x01u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define TESTERPRESENT_ZERO_SUBFUNC				 	0x00u

/************************************************************
 *	21. AccessTimingParameter(0x83)							*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_C_ACC_TIM_PARAM_NUM_SUBFUNC			 	0x04u /* TODO*/

/*
 * List all supported sub-function for this service
 */

/* lengend : ACC: Access ; TIM: Timing; PARAM : Parameter
 *           SF : SubFunction; DFLT : Default ; 2: to.
 *           CURR : Current ; ACT : Active; GIVN: Given value
 */ 
#define UDS_C_ACCTIMPARAM_SF_RD_EXT_TIM_PARAM_SET   0x01u
#define UDS_C_ACCTIMPARAM_SF_SET_TIM_PARAM_2_DFLT   0x02u
#define UDS_C_ACCTIMPARAM_SF_RD_CURR_ACT_TIM_PARAM  0x03u
#define UDS_C_ACCTIMPARAM_SF_SET_TIM_PARAM_2_GIVN   0x04u

#define UDS_C_ACCTIMPARAM_SET_GIVEN_TIME_PARAM_LEN  0x06u

/************************************************************
 *	22. SecuredDataTransmission(0x84) 						*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_SECU_DAT_TX_NUM_SUBFUNC 			 	0x00u /* TODO*/

/*
 * List all supported sub-function for this service
 */


/************************************************************
 *	23. ControlDTCSetting(0x85)								*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_C_CONTROLDTCSETTION_NUM_SUBFUNC			0x02u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define UDS_C_CTRLDTCSET_DTC_STORE_ON   			0x01u
#define UDS_C_CTRLDTCSET_DTC_STORE_OFF  			0x02u
#define UDS_C_CTRLDTCSET_DTC_NO_RESPONSE			0x07u


/************************************************************
 *	24. ResponseOnEvent(0x86)								*
 ***********************************************************/
/*
 * This definition indicates whether the vehicle manufacturer specific minimum seperation time shall be
 * used as part of the eventTypeRecord.
 *
 * This min seperation shall be used by server between multiple serviceToResponseTo-response.
 */
#define UDS_ENABLE_MIN_RESP_SEPTIME
#define UDS_RSP_ON_EVT_SUBFUNC 						0x00u/* TODO */
 
/*
 * List all supported sub-function for this service
 */
 

/************************************************************
 *	25. LinkControl(0x87)									*
 ***********************************************************/
/*
 * Number of sub-functions supported by this service
 */
#define UDS_LINKCNTRL_NUM_SUBFUNC					0x03u/* TODO*/

/*
 * List all supported sub-function for this service
 */
#define UDS_C_LNKCTRL_VERIFY_FIXED_BAUDRATE			0x01u
#define UDS_C_LNKCTRL_VERIFY_SPEC_BAUDRATE			0x02u
#define UDS_C_LNKCTRL_TRANSITION_BAUDRATE			0x03u

#define UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_125K      	0x10u
#define UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_250K      	0x11u
#define UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_500K      	0x12u
#define UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_1M        	0x13u

#define UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_DEFAULT     UDS_C_LNKCTRL_FIXED_BAUDRATE_ID_500K
 
#endif /* _UDS_CONFDEFS_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
