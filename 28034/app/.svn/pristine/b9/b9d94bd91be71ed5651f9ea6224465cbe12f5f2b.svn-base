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
* \version $Id: Version 1.0 Revision 6 2013-02-04 Tan Yang $
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
*----------------------------------------------------------------------------*
* UDS_1.0 Rev6  | Feb/04/2013   |                         | Yang TAN         *
* Delivery_003                                                               *
*         Modify return type of "Uds_ServiceResponse()" from "void" to       *
*         "Std_UdsReturnType" and add one declaration                        *
*         "Uds_SesnMgr_ResetSessionState()", change detail please refer to   *
*         UDSonCAN Protocol Stack Release Note_v1_0r6.doc                    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Type of session layer timer and application timer variables are    *
*         modified from unsigned 16bit to unsigned 32bit.                    *
*         Remove definition of ¡°P2CanServerMaxAbsoluteValue¡± and             *
*         ¡°P2StarCanServerMaxAbsoluteValue¡±.                                 *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*  to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t    *
*  to remove the similar coexisitn basic type for UINT8  uint8 and so on     *
*  and to remove the MISAR warning                                           *
*  add the writing checking interface and                                    *
*  and IO control function pointer type                                      *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDS_PRIV_H
#define _UDS_PRIV_H


#include "main.h"
#include "uds_target.h"
#include "uds_confdefs.h"
#include "udstp_priv.h"
#include "FblUdsExtItf.h"



/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

/* Define APdu Max Length of data to be received/transmited
 *
 * uint16_t type
 * maxium available length is 12bit(1~4095) as defined in ISO15765-2.
 */
#define ISO15765_APDU_MSGDATA_LENGTH		  		150u /* original 300u, TODO */


/* Definition of UDS Diagnostic Session Levels
 *
 * Uds_SessionLevel_t
 *
   [Note]: Only the ISO14229 spec defined sessions are defined here.
   Furhter ISOSAEReserved, vehicleManufacturerSpecific and systemSupplierSpecific
   ranges are not defined here.
   [Note]: ISO15765-3(UDSonCAN) only defined the first three sessions(default, programming, extended).
 */
#define UDS_DEFAULT_SESSION						0x01u		/* ISO15765-3(UDSonCAN) defined. */
#define UDS_PROGRAMMING_SESSION					0x02u		/* ISO15765-3(UDSonCAN) defined. */
#define UDS_EXTENDED_DIAGNOSTIC_SESSION			0x03u		/* ISO15765-3(UDSonCAN) defined. */
#define UDS_SAFTEY_SYSTEM_DIAGNOSTIC_SESSION	0x04u
#define UDS_OEM_VEHCLE_MANU_SPEC_SESSION        0x40u
#define UDS_ECU_SUPPLIER_SPEC_SESSION           0x60u
#define UDS_ALL_SESSION_LEVEL					0xFFu

/* Definition of ECU Reset request types
 *
   [Note]: Only the ISO14229 spec defined sessions are defined here.
   Furhter ISOSAEReserved, vehicleManufacturerSpecific and systemSupplierSpecific
   ranges are not defined here.
 */
#define HARD_RESET								0x01u
#define	KEYOFFON_RESET							0x02u
#define SOFT_RESET								0x03u
#define ENABLE_RAPIDPOWERDOWN_RESET				0x04u
#define DISABLE_RAPIDPOWERDOWN_RESET			0x05u

/* Definition of UDS SecurityAccess Levels
 *
 * Uds_SecurityLevel_t
 *
   [Note]: ISO14229 spec requires these values to be defined and implemented by OEM, system supplier
   or further standard reserved, e.g. airbag development implementation.
   [Note]: ISO15765-3(UDSonCAN) only defined range from 0x01 to 0x60.
 */
#define UDS_SECURITY_LEVEL_L0					0x00u	/* No securty level. */
#define UDS_SECURITY_LEVEL_L11					0x11u

/* Definition of UDS SecurityAccess State
 *
 */
#define UDS_SECURITY_LEVEL_UNLOCKED				0x00u
#define UDS_SECURITY_LEVEL_LOCKED				0xFFu

/* Definition of UDS Communication Control Types
 *
   [Note]: Only the ISO15765-3(UDSonCAN) defined value from ISO14229 spec definitions are defined here.
 */
#define ENABLE_RX_AND_TX						0x00u
#define ENABLE_RX_DISABLE_TX					0x01u
#define DISABLE_RX_ENABLE_TX					0x02u
#define DISABLE_RX_AND_TX						0x03u

/* Definition of UDS Communication Types
 *
   [Note]: This is defined in ISO15765-3(UDSonCAN).
 */
#define COMTYPE_APPLICATION_MSG					0x01u	/* NCM	 */
#define COMTYPE_NETWORKMANAGE_MSG				0x02u	/* NWMCM */

/* Definition of UDS Control DTC Setting Type
 *
   [Note]: Only the ISO14229 spec defined values are defined here.
   Furhter ISOSAEReserved, vehicleManufacturerSpecific and systemSupplierSpecific
   ranges are not defined here.
   [Note]: ISO15765-3(UDSonCAN) only defines this two value range(on and off).
 */
#define UDS_DTC_SETTING_START					0x01u
#define UDS_DTC_SETTING_STOP					0x02u

/* Definition of UDS Response On Event StorageState
 *
 * eventStorageState
 *
   [Note]:	Only bit0 represent bit6 of eventType in received service.
 */
#define UDS_EVENTSTORESTATE_NOTSTORE			0x00u
#define UDS_EVENTSTORESTATE_STORE				0x01u

/* Definition of UDS Response On Event Type
 *
 * eventType
 *
   [Note]:	Only ISO15765(UDSonCAN) defined value ranges are listed.
 */
#define UDS_EVENTTYPE_STOP_RESPONEVENT			0x00u
#define UDS_EVENTTYPE_ONDTCSTATUSCHANGE			0x01u
#define UDS_EVENTTYPE_ONTIMERINTERRUPT			0x02u
#define UDS_EVENTTYPE_ONDIDCHANGE				0x03u
#define UDS_EVENTTYPE_REPORT_ACTIVEEVENT		0x04u
#define UDS_EVENTTYPE_START_RESPONEVENT			0x05u
#define UDS_EVENTTYPE_CLEAR_RESPONEVENT			0x06u
#define UDS_EVENTTYPE_ONCMPOFVALUES				0x07u

/* Definition of UDS Response On Event eventWindowTime
 *
 * eventWindowTimeValue
 *
   [Note]: Only the ISO14229 spec(AnnexB.2) defined values are defined here.
   Furhter ISOSAEReserved, vehicleManufacturerSpecific(0x03-0x7F) ranges are not defined here.
   [Note]: If further vehicleManufacturerSpecific values are to be used, then the resolution
   of the eventWindowTime parameter is left vehicle-manufacturer discretionary.
 */
/* 0x02 - event window shall stay active for an infinite time (e.g. open window until power off). */
#define UDS_EVENTWINDOWTIME_INFINITE			0x02u

/* Definition of UDS Link Control Types
 *
   [Note]: Only the ISO14229 spec(AnnexB.3) fixed baudrate values are defined here.
   Furhter ISOSAEReserved, vehicleManufacturerSpecific and systemSupplierSpecific
   ranges are not defined here.
 */
#define UDS_LINKCONTROL_VERIFYFiXED				0x01u
#define UDS_LINKCONTROL_VERIFYSPECIFIC			0x02u
#define UDS_LINKCONTROL_TRANSITION				0x03u

/* Definition of UDS Link Control baudrateIdentifier
 * Fixed Baudrate defined in ISO14229 spec-AnnexB.3
 *
   [Note]: Only the ISO14229 spec(AnnexB.3) fixed baudrate values for CAN-Bus are defined here.
   Furhter ISOSAEReserved and PC Baudrate ranges are not defined here.
 */
#define UDS_LINKCONTROL_FIXED_125K				0x10u
#define UDS_LINKCONTROL_FIXED_250K				0x11u
#define UDS_LINKCONTROL_FIXED_500K				0x12u
#define UDS_LINKCONTROL_FIXED_1M				0x13u

/* Definition TransmissionMode of UDS Read Data By Periodic Identifier
 * (defined in ISO14229 spec-AnnexC.4)
 *
 * periodicTransmitMode
   [Note]: Only the ISO14229 spec(AnnexC.4) defined values are defined here.
   Furhter ISOSAEReserved are not defined here.
 */
#define UDS_DID_PERIODICTRANSMIT_SLOWRATE		0x01u	/* SASR */
#define UDS_DID_PERIODICTRANSMIT_MEDIUMRATE		0x02u	/* SAMR */
#define UDS_DID_PERIODICTRANSMIT_FASTRATE		0x03u	/* SAFR */
#define UDS_DID_PERIODICTRANSMIT_STOPSEND		0x04u	/* SS   */

/* Definition of UDS Confirmation Status
 *
 * Uds_ConfirmationStatus_t
 */
#define UDS_RESP_POS_OK							0x00u
#define UDS_RESP_POS_NOT_OK						0x01u
#define UDS_RESP_NEG_OK							0x02u
#define UDS_RESP_NEG_NOT_OK						0x03u

/* Definition of UDS Negative Response Code
 * (according to ISO14229 Annex A)
 * Uds_NegRespCode_t
 *
 * ISOSAEReserved value ranges are not listed
 * ISO15764 Extended data link scurity value range are not listed.(0x38-0x4F)
 */
#define UDS_POSITIVE_RESPONSE							0x00u	/* PR */
#define UDS_NO_RESPONSE									0x01u	/* ISOSAEReserved - identify no response needed case. */
#define UDS_NRC_GENERALREJECT							0x10u	/* GR */
#define UDS_NRC_SERVICENOTSUPPORTED						0x11u	/* SNS */
#define UDS_NRC_SUBFUNCTIONNOTSUPPORTED					0x12u	/* SFNS */
#define UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT	0x13u	/* IMLOIF */
#define UDS_NRC_RESPONSETOOLONG							0x14u	/* RTL */
#define UDS_NRC_BUSYREPEATREQUEST						0x21u	/* BRR */
#define UDS_NRC_CONDITIONSNOTCORRECT					0x22u	/* CNC */
#define UDS_NRC_REQUESTSEQUENCEERROR					0x24u	/* RSE */
#define UDS_NRC_NORESPONSEFROMSUBNETCOMPONENT			0x25u	/* NRFSC */
#define UDS_NRC_FAILUREPREVENTEXECUTIONOFREQUESTACTION	0x26u	/* FPEORA */
#define UDS_NRC_REQUESTOUTOFRANGE						0x31u	/* ROOR */
#define UDS_NRC_SECUTITYACCESSDENIED					0x33u	/* SAD */
#define UDS_NRC_INVALIDKEY								0x35u	/* IK */
#define UDS_NRC_EXCEEDNUMBEROFATTEMPTS					0x36u	/* ENOA */
#define UDS_NRC_REQUIREDTIMEDELAYNOTEXPIRED				0x37u	/* RTDNE */
#define UDS_NRC_UPLOADDOWNLOADNOTACCEPTED				0x70u	/* UDNA */
#define UDS_NRC_TRANSFERDATASUSPENDED					0x71u	/* TDS */
#define UDS_NRC_GENERALPROGRAMMINGFAILURE				0x72u	/* GPF */
#define UDS_NRC_WRONGBLOCKSEQUENCECOUNTER				0x73u	/* WBSC */
#define UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING	0x78u	/* RCRRP */
#define UDS_NRC_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION	0x7Eu	/* SFNSIAS */
#define UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION		0x7Fu	/* SNSIAS */
#define UDS_NRC_RPMTOOHIGH								0x81u	/* RPMTH */
#define UDS_NRC_RPMTOLOW								0x82u	/* RPMTL */
#define UDS_NRC_ENGINEISRUNNING							0x83u	/* EIR */
#define UDS_NRC_ENGINEISNOTRUNNING						0x84u	/* EINR */
#define UDS_NRC_ENGINERUNTIMETOOLOW						0x85u	/* ERTTL */
#define UDS_NRC_TEMPERATURETOOHIGH						0x86u	/* TEMPTH */
#define UDS_NRC_TEMPERATURETOOLOW						0x87u	/* TEMPTL */
#define UDS_NRC_VEHICLESPEEDTOOHIGH						0x88u	/* VSTH */
#define UDS_NRC_VEHICLESPEEDTOOLOW						0x89u	/* VSTL */
#define UDS_NRC_THROTTLE_PEDALTOOHIGH					0x8Au	/* TPTH */
#define UDS_NRC_THROTTLE_PEDALTOOLOW					0x8Bu	/* TPTL */
#define UDS_NRC_TRANSMISSIONRANGENOTINNEUTRAL			0x8Cu	/* TRNIN */
#define UDS_NRC_TRANSMISSIONRANGENOTINGEAR				0x8Du	/* TRNIG */
#define UDS_NRC_BRAKESWITCH_NOTCLOSED					0x8Fu	/* BSNC */
#define UDS_NRC_SHIFTERLEVERNOTINPARK					0x90u	/* SLNIP */
#define UDS_NRC_TORQUECONVERTERCLUTCHLOCKED				0x91u	/* TCCL */
#define UDS_NRC_VOLTAGETOOHIGH							0x92u	/* VTH */
#define UDS_NRC_VOLTAGETOOLOW							0x93u	/* VTL */

/* UDS constants definition */

/* TP channel identifer definition */
#define UDS_C_TP_CHANNEL_PHY_ADDRESSING                 (0x00u)
#define UDS_C_TP_CHANNEL_FUNC_ADDRESSING                (0x01u)

/* UDS subfunction bit 7th : SuppressPostiveResponseMsgIndicationBit */ 
#define UDS_C_SUB_FUNC_MASK_YES_SPRB7                   (0x80u)
#define UDS_C_SUB_FUNC_MASK_NO_SPRB7                    (0x7Fu)
#define UDS_C_SVC_POS_RSP_SID_OFFSET                    (0x40u)

#define UDS_C_SVC_NEG_RSP_SID                           (0x7Fu)

/* Define values of Std_UdsReturnType which are used for function returns
 * of Uds module.
 */
#define UDS_E_OK 					(Std_UdsReturnType)0x00u
#define UDS_E_NOT_OK 				(Std_UdsReturnType)0x01u
#define UDS_E_PENDING				(Std_UdsReturnType)0x02u

/******************************************************************************
*
* Type definitions
*
******************************************************************************/
							
typedef uint8_t	Uds_SessionMask_t;
typedef uint8_t	Uds_SecurityLevel_t;
typedef uint8_t	Uds_SessionLevel_t;			/** UDS_req 73 *//** UDSonCAN_req 90 */
typedef uint8_t	Uds_NegRespCode_t;			/** UDS_req 16 */
typedef uint8_t	Uds_ConfirmationStatus_t;
typedef uint8_t Std_UdsReturnType;
/* Statemachine of status of ResponseOnEvent service. */
typedef enum
{
	RESPONEVENT_IDLE,			/* The ResponseOnEvent is idle, ether not setted up yet or events not occurs. */
	RESPONEVENT_SETUP,			/* The ResponseOnEvent handling now setted up but not started yet. */
	RESPONEVENT_START,			/* The ResponseOnEvent handling now started(serviceToResponseTo may start when events occur). */
	RESPONEVENT_STOP,			/* The ResponseOnEvent handling now stopped but not cleared(serviceToResponseTo shall not start when events occur). */
	RESPONEVENT_EVENT_PENDING,	/* The configured events occurs but not able to process now, in pending state. */
	RESPONEVENT_EVENT_INPROCESS	/* The occured events are not under processing. */
} Uds_RespOnEventState_t;

typedef enum
{
    UDS_TXRXFREE = 0x00u,           	/* The buffer is available to store TX or RX data. */
    UDS_TX_RESPONSE_ALLOC,			/* The buffer has been allocated to store TX response data, but it is not yet ready to be transmitted. */	
    UDS_TX_RESPONSE_NOTSENT,        /* The buffer containing TX response is ready to be transmitted to Network transport layer. */	
    UDS_TX_RESPONSE_INPROGRESS,     /* The buffer is being transmitted to Network transport layer. */	
    UDS_RX_DATA                  	/* The buffer is contains RX data, ether indication or response-confirmation. */
} Uds_SessionBufState_t;

typedef UDS_STATE_TYPE struct
{
    /* For a TX queue this represents the tail of the queue. The Uds App writes messages into the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the head of the queue. The Uds App reads messages from the queue
     * at this position in the session's buffer array. */
    uint8_t                  ctUdsPos;

    /* For a TX queue this represents the head of the queue. The Uds Tp reads messages from the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the tail of the queue. The Uds Tp writes messages into the queue
     * at this position in the session's buffer array. */
    uint8_t                  ctUdsTpPos;
} Uds_SessionQueueBufPos_t;

typedef enum
{
	TARGETADDR_PHYSICAL = 0x00u,
	TARGETADDR_FUNCTIONAL
} Uds_TAType_t;

typedef enum
{
	SUPPRESS_POSITIVE_RESPMSG_NO = 0x00u,
	SUPPRESS_POSITIVE_RESPMSG_YES
} Uds_SuppressPosRspMsg_t;

typedef enum
{
	NO_SERVICE = 0x00u,				/* No service indication to process. */
	SERVICE_INDICATION,			/* Reception */
	SERVICE_FF_INDICATION,		/* Reception */
	SERVICE_RESPONSE_CONF,		/* Reception */
#ifdef UDS_ENABLE_CHANGEPARAMETER
	SERVICE_CHANGEPARAM_CONF,	/* Reception */
	SERVICE_CHANGEPARAM_REQ,	/* Transmission */
#endif /* UDS_ENABLE_CHANGEPARAMETER */
	SERVICE_RESPONSE			/* Transmission */
} Uds_ServiceType_t;

/* StateMachine of Uds Session Manager. */
typedef enum
{
	SESSION_IDLE = 0x00u,			/* SessionManager is idle. */
	SESSION_WAIT_TXBUF,			/* Waiting for session transmit buffer available, then process received service indication. */
	SESSION_WAIT_RESPONSE,		/* Waiting for response from service processing(both response required and not required). */
	SESSION_WAIT_RESPCON,		/* Response required and sent, response confirmation not got from transport layer. */
	SESSION_WAIT_78HEX_NEG_RESPCON,	 /* Negative Response(78hex) sent, response confirmation not got from transport layer. */
	SESSION_WAIT_RESPONSE_AFTER78HEX /* Waiting for response from service processing after Negative Response(78hex) transmitted. */
} Uds_SessionState_t;

/* StateMachine of service processing
 * - interface between session and service processor.
 */
typedef enum
{
	UDS_SERVICE_IDLE = 0x00u,				/* (Session write)Service processor idle. */
	UDS_SERVICE_ACCEPTED,				/* (Session write)New service accepted, not start to process or not finished processing. */
	UDS_SERVICE_NO_RESPONSE,			/* (ServiceProcessor write, session read)Finished processing of service, no response required. */
	UDS_SERVICE_RESP_AVAILABLE,			/* (ServiceProcessor write, session read)Finished processing of service, response ready(response buffer available now). */
	/* When service processing returns a 78hex result by setting serviceState to "UDS_SERVICE_78HEX_NEG_RESP", it
	 * shall not modify the serviceState to UDS_SERVICE_RESP_AVAILABLE until it gives response data in A_PDU buffer. */
	UDS_SERVICE_78HEX_NEG_RESP			/* (ServiceProcessor write, session read)Negative response pending(78hex),response ready(response buffer available now). */
} Uds_ServiceState_t;

typedef UDS_STATE_TYPE struct
{
	Uds_PduLength_t		  msgLength;	/* byte length of A_Data including A_PCI. */
	uint8_t                           CurrSvcHavSubFunc; 
	uint8_t                           CurrSvcIsSupPosRspBitSet; 
	uint8_t                           CurrInTempDiagReqSid;
	uint8_t                           CurrIncomDiagReqSid;
	uint8_t                           CurrProcessingDiagReqSid;
	Uds_PduData_t		  pduData[ISO15765_APDU_MSGDATA_LENGTH];	/* UDS A_PDU_Data general type */
} Uds_APduData_t;

/* Identifiers for the configured server location. */
typedef enum
{
	LOCAL_SERVER = 0x00u,
	REMOTE_SERVER
} Uds_ServerType_t;

typedef UDS_CONFIG_TYPE struct
{
	Uds_ServerType_t	serverType;	/** UDS_req 1 *//* Local server or remote server. */
	Uds_Addr_t			sA;			/* uint8_t type source address */
	Uds_Addr_t			tA;			/* uint8_t type target address */
	Uds_Addr_t			rA;			/* uint8_t type address extention */
} Uds_ASduAICfg_t;

/* UDS session Rx buffer for 
 * <service>.indication
 * <service>.FF_indication
 * <service>.Resp-confirmation
 * <service>.ChangeParameter-confirmation
 */
typedef UDS_STATE_TYPE struct
{
	Uds_ServiceType_t			serviceType;		/* Type of service received from below network transport layer. */
	Uds_ServerType_t			serverType;			/** UDS_req 1 *//* Local server or remote server(enum). */
	Uds_TAType_t				tAType;				/* Fnc or Phy type of target address type(enum). */
	Uds_Addr_t					sA;					/* uint8_t type source address */
	Uds_Addr_t					tA;					/* uint8_t type target address */
	Uds_Addr_t					rA;					/* uint8_t type address extention */
	UdsTp_NResult_t				result;				/* service result type(enum). */
	uint8_t						parameter;			/* Parameter type of STmin or Bs(enum). */
	UdsTp_NResult_ChangeParam_t	paramChangeResult;
	Uds_APduData_t*				pAPduData;
} Uds_SessionRxBuf_t;

/* UDS session Tx buffer for 
 * <service>.response
 * <service>.changeParameter-request
 */
typedef UDS_STATE_TYPE struct
{
	Uds_ServerType_t			serverType;		/** UDS_req 1 *//* Local server or remote server(enum). */
	Uds_TAType_t				tAType;			/* Fnc or Phy type of target address type(enum). */
	Uds_Addr_t					sA;				/* uint8_t type source address */
	Uds_Addr_t					tA;				/* uint8_t type target address */
	Uds_Addr_t					rA;				/* uint8_t type address extention */
	uint8_t						parameter;		/* Parameter type of STmin or Bs(enum). */
	uint8_t						parameterValue;
	Uds_APduData_t*				pAPduData;
} Uds_SessionTxBuf_t;

/* The configuration of application layer and session layer timing parameters compliant to ISO15765-3. */
/* Type of timer variables are using unsigned 32bit.
 * Resolutions are 1us.
*/
typedef UDS_CONFIG_TYPE struct
{
	/* application layer timing values for default session and non-default session(when no adapt applied). */
	/* Max value till start with the response after reception of a request msg. */
	uint32_t			P2CanServerMax;	/** UDSonCAN_req 8-1 *//** UDSonCAN_req 68 *//** UDSonCAN_req 69 *//** UDSonCAN_req 92 *//** UDSonCAN_req 94 */
	/* Max value till start with the response after transmition of negative response(78hex) msg. */
	uint32_t			P2StarCanServerMax;			/** UDSonCAN_req 8-2 *//** UDSonCAN_req 93 *//** UDSonCAN_req 95 */
	/* min value between transmission of two consecutive negative(78hex) msg. */
	uint32_t			P2StarCanServerConsNegResp;	/** UDSonCAN_req 8-3 */
	/* session layer timing values for non-default session. */
	/* Time to keep active of an non-default session while not receiving any request msg. */
	uint32_t 			S3Server;					/** UDSonCAN_req 9 */ /** UDSonCAN_req 10 */
} Uds_TimingCfg_t;

/* The configuration of security levels for uds services. */
typedef UDS_CONFIG_TYPE struct
{
	uint32_t			delayTimeOnBoot;
	uint32_t			delayTime;			/* Reload value of "delay timer" for delay time counting of "SecurityAccess" service received from client. */	
	uint8_t				numAttDelay;		/* Number of failed attempts the server allowed for "SecurityAccess" before start "delay timer". */
	uint8_t				numAttLock;			/* Number of failed attempts the server allowed for unlock by key value received in "SendKey" message from client. */
	uint8_t				seedSize;			/* Number of bytes for seed. */
	uint8_t				keySize;			/* Number of bytes for Key. */
	
#ifdef UDS_SECURITYACCESS_ENABLE_QUALIFYCHECK
	Uds_Addr_t			clientAddr;			/* This client address is used when only a certain client is allowed to unlock a security server session. */	
#endif /* UDS_SECURITYACCESS_ENABLE_QUALIFYCHECK */
} Uds_SecurityAccessCfg_t;

/* The configuration of non-default session levels for uds services. */
/* Type of timer variables are using unsigned 32bit.
 * Resolutions are 1us.
*/
typedef UDS_CONFIG_TYPE struct
{
	Uds_SessionLevel_t	sessionLevel;
#ifdef UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK
	Uds_Addr_t			clientAddr;						  /** UDS_req 67 *//* This client address is used when only a certain client is allowed to start this session. */
#endif /* UDS_ENABLE_SWITCHSESSION_QUALIFYCHECK */
	/* Max value till start with the response after reception of a request msg. */
	uint32_t				sessionP2CanServerMax;			  /** UDSonCAN_req 8-1 *//** UDSonCAN_req 68 *//** UDSonCAN_req 69 */
	/* Max value till start with the response after transmition of negative response(78hex) msg. */
	uint32_t				sessionP2StarCanServerMax;		  /** UDSonCAN_req 8-2 */
	/* Min value between transmission of two consecutive negative(78hex) msg. */
	uint32_t				sessionP2StarCanServerConsNegResp;/** UDSonCAN_req 8-3 */
} Uds_SessionLevelCfg_t;

/* The UDS Severice Handler Function Pointer type definition */
typedef  Std_UdsReturnType UDS_FN_TYPE (*T_FUNC_PTR_UDS_SVC_HANDLER) ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* The configuration of uds services table. */
typedef UDS_CONFIG_TYPE struct
{
	/* serviceId(SID) shall alway appear for each service(each table element) regardless whether this service
	 * is supported by current application or not.
	 * If one service is not supported by application, then other elements for this service can be ZERO. */
	uint8_t				serviceId;
	T_FUNC_PTR_UDS_SVC_HANDLER pFnc_UdsSvcHdlr;  	/* service handler function pointer */
	/* supportedSession is a Bit field combinition value:
	 * bit1 - default session, bit2 - programming session, bit3 - extended diagnostic session. */
	Uds_SessionMask_t	supportedSession;			/* In which session this service is support. */
	uint8_t				addrPhySupported;			/* Whether physical addressing type is supported by this service. */
	uint8_t				addrFunSupported;			/* Whether functional addressing type is supported by this service. */
	Uds_SecurityLevel_t	securityLevel;				/* Security access level to be achieved required for this service. */
} Uds_ServiceTable_t;

/* The configuration of uds session compliant to ISO15765-3. */
typedef UDS_CONFIG_TYPE struct
{
	Uds_ASduAICfg_t*			pASdu_AI;
	Uds_TimingCfg_t*			pUdsTimingCfg;			/* Uds Application and session timing configuration. */
	Uds_SecurityAccessCfg_t*	pSecurityAccessCfg;		/* Array of security configuration for each non-default session. */
	Uds_SessionLevelCfg_t*		pSessionLevelCfg;		/* Array of sessions configuration supported by the server. */
	Uds_SessionQueueBufPos_t*	pSessionRxQueuePos;
	Uds_SessionQueueBufPos_t*	pSessionTxQueuePos;
	Uds_SessionBufState_t*		pSessionRxQueueBufState;
	Uds_SessionBufState_t*		pSessionTxQueueBufState;
	Uds_SessionRxBuf_t*			pSessionRxBuffer;		/* Service Rx buffer array used inside session itself. */
	Uds_SessionTxBuf_t*			pSessionTxBuffer;		/* Service Tx buffer array used inside session itself. */
} Uds_SessionCfg_t;

/* The Runtime State of uds session. */
/* Type of timer variables are using unsigned 32bit.
 * Resolutions are 1us.
*/
typedef UDS_STATE_TYPE struct
{
	Uds_SessionState_t			sessionState;			/* state machine for session */
	Uds_SessionLevel_t			sessionLevel;			/* Current Diagnostic Session Level of the Server. */
	Uds_ServiceState_t			serviceState;			/* Current state of processing of Uds service. */
	UdsTp_NResult_t				indOrRespConResult;		/* Result of <service>.indication or <service>.resp-confirm. */
#ifdef UDS_ENABLE_CHANGEPARAMETER
	UdsTp_NResult_ChangeParam_t	changeParameterResult;
	uint8_t						flagChangeParamConfirm;
#endif /* UDS_ENABLE_CHANGEPARAMETER */
	uint8_t						flagFirstFrameReceived; /* First frame received, waitting for <service>.indication. */
	uint8_t						flagResponseConfirm;
	uint8_t						flagP2TimeoutCounter;
	uint8_t						flagS3TimeoutCounter;
	uint8_t						flagConsecutiveNegResp; /* Flag indicate whether this is a consecutive negative response window. */
	uint32_t                    P2CanSrvrTmrTONum;                         /* the logical counter to record the number of the p2canserver timer timeout event */
	uint32_t					timeoutCounter; 		/* Decrease timer for diagnostic app timeout. */
	uint32_t					timeoutCounterS3Server;	/** UDSonCAN_req 15 *//** UDSonCAN_req 26 *//* Decrease timer for diagnostic session timeout. */
	uint32_t					P2CanServerMax;			/* Reload value of P2CAN_Server for current session. */
	uint32_t					P2StarCanServerMax;		/* Reload value of P2StarCAN_Server for current session. */
	uint32_t					P2StarCanServerConsNegResp;/* Reload value of P2StarCAN_Server for consecutive negative response(78hex) for current session. */
	uint32_t					S3Server;				/* Reload value of S3Server for current non-default session. */
	
#ifdef UDS_ENABLE_SECURITYACCESS
	Uds_SecurityLevel_t			securityLevel;			/* Current Security Level for current Diagnostic Session. */
	uint8_t						stateUnLock;			/* Current security unlock state for current session. */
	uint32_t					delayTimerSecurity;		/* Delay timer for security access delay. */
    uint8_t               		seedRemainBytes;        /* Number of bytes at pRemainSeed.                      */
    union{                                      		/* This union is used to reduce storage space.       */
        Uds_Key_t*      		pKey;                   /* Location for UNLOCK to store next portion of key. */
        Uds_Seed_t*     		pRemainSeed;            /* The remaining seed to be sent.					 */
    } seedOrKey;
#endif /* UDS_ENABLE_SECURITYACCESS */
} Uds_SessionRuntime_t;

/* InputOutputControlParameter definitions as ISO14229 Annex.E*/
typedef enum
{
	UDS_C_2FIOCTRL_PARAM_RETN_CTRL_2ECU = 0x00u,
    UDS_C_2FIOCTRL_PARAM_RESET_TO_DFLT  , 
    UDS_C_2FIOCTRL_PARAM_FREEZE_CURR_ST ,
	UDS_C_2FIOCTRL_PARAM_SHORT_TERM_ADJ 
} UdsApp_IODidCtrlState_t;

/* the 2F InputOutputControlParameter Command definition */

typedef enum
{
  UDS_C_2FIOCTRL_CMD_NO         = 0x00u,
  UDS_C_2FIOCTRL_CMD_OFF        = 0x01u,
  UDS_C_2FIOCTRL_CMD_ON         = 0x02u,
  UDS_C_2FIOCTRL_CMD_RST_2_DFLT = 0x04u,
  UDS_C_2FIOCTRL_CMD_FREZ_ST    = 0x08u,
  UDS_C_2FIOCTRL_CMD_REL_2_ECU  = 0x10u
} UdsApp_IODidCtrlCommand_t;

/* Routine Control Type as define in RoutineControl service in ISO14229 */
typedef enum
{
	NO_ROUTINE_REQ = 0,
	START_ROUTINE,
	STOP_ROUTINE,
	REQUEST_ROUTINE_RESULT
} UdsApp_RoutineCtrlType_t;

/* The struct of UDS Data Identifier. */
typedef UDS_STATE_TYPE struct
{
	uint16_t				dataIdentifier;		/** UDS_req 155 *//** UDS_req 198 *//* MSB on high nibble, LSB on low nibble. */
	uint16_t				sizeDid;
} UdsApp_DidType_t;

/* The struct of UDS Read periodic Data Identifier. */
typedef UDS_STATE_TYPE struct
{
	/* This periodDid is the low byte of a dataIdentifier define within ISO14229AnnexC.1,
	whose high byte value equal to 0xF2(period data identifier range). */
	uint16_t				periodicDid;		/** UDS_req 176 */
	uint16_t				sizePeriodicDid;
} UdsApp_PeriodicDidType_t;

typedef UDS_STATE_TYPE struct
{
	uint16_t				dynDid;
	uint16_t				srcRefDid;
	uint8_t				positionRef;
	uint8_t				sizeDid;
} UdsApp_DynDidType_t;

/* The enum of current accessing type of Did. */
typedef enum
{
	DID_READ = 0,			/* Read access to data identifier(s). */
	DID_WRITE,				/* Write access to data identifier(s). */
	DID_CONTROL				/* Input/Output Control to data identifier(s).  */
} UdsApp_DidAccessType_t;

/*lint -save  -e46 */
typedef struct
{
   uint16_t  m_FAA_Flag;
   uint16_t m_FAA_Cntr;
}T_UDS_27SECUACC_E2_DAT_BITMAP;
/*lint -restore */

typedef union
{
	T_UDS_27SECUACC_E2_DAT_BITMAP m_bitmap;
	uint32_t   uw;
}T_UDS_27SECUACC_E2_DAT_TYPE;

typedef void (*T_UDS_27SECUACC_COMPUTEKEY_LVL)( const uint8_t *lpub_seed, uint8_t *lpub_key, uint8_t lpub_accessLevel);

#define UDS_27SECUACC_SUBFUNC_IS_ODD_NUMBER(lub_InSubFunc)        ( 0x01u == (lub_InSubFunc & 0x01u) )

/*
 * Data Structure Definition for DID Reading/Writing/IoCtrl
 */

/* The UDS Pre-ReadingMemoryByAddress Data checking Function Pointer type definition*/
typedef uint8_t (*T_FUNC_PTR_UDS_PRE_RD_MEM_CHK_ITF)(uint32_t i_InMemAdd2Read, 
                                                     uint16_t i_InMemSize2Read);

/* The UDS Reading Data Interface Function Pointer type definition */
typedef  void (*T_FUNC_PTR_UDS_READ_DATA_ITF) (uint8_t * i_pDataBufPtr);
                                               
typedef  uint8_t (*T_FUNC_PTR_UDS_RD_MEMBYADD_ITF) (uint32_t i_InMemAdd2Read, 
                                                 uint16_t i_InMemSize2Read, 
                                                 uint8_t * i_pDataBufPtr);

/* The UDS Pre-Writing Data checking Function Pointer type definition*/
typedef uint8_t (*T_FUNC_PTR_UDS_PRE_WT_CHK_ITF)( uint8_t * i_pDataBufPtr);

/* The UDS Pre-Writing Data by MemAdd checking Function Pointer type definition*/
typedef uint8_t (*T_FUNC_PTR_UDS_PRE_WT_MEM_CHK_ITF)(uint32_t i_InMemAdd2Write, 
                                                   uint16_t i_InMemSize2Write, 
                                                   uint8_t * i_pDataBufPtr);

/* The UDS Writing Data Interface Function Pointer type definition */
typedef  void (*T_FUNC_PTR_UDS_WRITE_DATA_ITF) ( uint8_t * i_pDataBufPtr);

/* The UDS Pre-Writing Data by MemAdd checking Function Pointer type definition*/
typedef uint8_t (*T_FUNC_PTR_UDS_WT_MEMBYADD_ITF)(uint32_t * i_InMemAdd2Write, 
                                                  uint32_t i_InMemSize2Write, 
                                                  uint32_t * i_pDataBufPtr);

/* The UDS Function Pointer type definition : 0x2F IoCtrlByDid IoCtrlInterface Function */
typedef void (* T_FUNC_PTR_UDS_IOCTRL_ITF)(uint8_t i_IoCtrlOption, uint8_t *iP_IoCtrlParam);


/* The UDS Pre-Reqest Download checking Function Pointer type definition*/
typedef uint8_t (*T_FUNC_PTR_UDS_PRE_DNLD_CHK_ITF)(uint32_t  i_InMemAdd2Write, 
                                                   uint32_t  i_InMemSize2Dnld,
                                                   uint16_t *o_pMaxNumOfBlkLen);

/* The UDS ReqeustDownload Writing Data Interface Function Pointer type definition */
typedef uint8_t (*T_FUNC_PTR_UDS_DNLD_WT_DAT_ITF) (uint32_t * i_pInMemAdd2Write, 
                                                   uint32_t       i_InMemSize2Write, 
                                                   uint32_t  *i_pDataBufPtr); /* each block size for writing */


/* 0x22 ReadDataByIdentifier 
   service data Managing Record Type 
 */
typedef UDS_STATE_TYPE struct
{
	uint16_t			dataIdentifier;		
	uint16_t			DataSize;
	uint16_t			AccessAttribute; 
	uint8_t*			pDataBuf;
	T_FUNC_PTR_UDS_READ_DATA_ITF  pFuncPtrToReadData;    
} UDS_DidDatMngRecd_t;



/* 0x23 ReadMemoryByAddress and 
   0x3D WriteMemoryByAddress 
   service data Managing Record Type 
 */

typedef UDS_STATE_TYPE struct
{
	 uint32_t	                        RdWtByAddStartAdd;		
	 uint16_t  				            DataSize;
	 uint16_t                           AccessAttribute; 
	 uint8_t*                           pDataBuf;
	 T_FUNC_PTR_UDS_PRE_RD_MEM_CHK_ITF  pFuncPtrPreRdChk;
	 T_FUNC_PTR_UDS_RD_MEMBYADD_ITF     pFuncPtrToReadData;
	 T_FUNC_PTR_UDS_PRE_WT_MEM_CHK_ITF  pFuncPtrPreWtChk;
	 T_FUNC_PTR_UDS_WT_MEMBYADD_ITF     pFuncPtrToWriteData;	     
} UDS_RdWtMemByAddDatMngRecd_t;




/* 0x2A ReadDataByPeriodicalId
   service data Managing Record Type 
 */
typedef UDS_STATE_TYPE struct
{
	uint8_t     PeriodDid;     /*Periodical Data Identifier LSB (low 8 bits) */
	uint8_t     PeriodDidTblRcdIndex; 		/* refer to static or dynamical did table */
	uint8_t     IsDynaDef;    				/* this period did record is static or dynamicall */
	uint8_t     PeriodRateType; 
	uint8_t     StartingOffset; 
	uint32_t    RunningPeriodTimer;  
} UDS_RdDatByPeriodDidMngRecd_t;

/* 0x2C DynamicallyDefineDataIdentifier 
   service data Managing Record Type 
 */
typedef UDS_STATE_TYPE struct
{
	uint16_t		  DynaDefDid;		      	/* DynaDefined Did : 1st record have meaning, others in the list should keep 0xFFFFu */
	uint8_t           ReferedIsDynaDef; 		/* to indicate reference did is dynamically defined or not */
	uint8_t           ReferedDidIdx;        /* referenced Did Table Index , statically defined or dynamically defined */
	uint8_t			  PriorDynaTblIdx;   	  /* bi-directional prior index pointer of this table */
	uint8_t			  NextDynaTblIdx;   	  /* bi-directional next index pointer of this table  */
	uint16_t		  AccessAttribute;   		/* access attributes for DynaDefDid , if need to define different attr */
} UDS_DynaDefDidMngRecd_t;

/* 0x2E WriteDataByIdentifier 
   service data Managing Record Type 
 */
typedef UDS_STATE_TYPE struct
{
	uint16_t				        dataIdentifier;		
	uint16_t  				        DataSize;
	uint16_t        		        AccessAttribute;
	uint8_t                         EepromBlkIdx; 
	uint8_t*        		        pDataBuf;
	T_FUNC_PTR_UDS_PRE_WT_CHK_ITF	pFuncPtrCheckData;
	T_FUNC_PTR_UDS_WRITE_DATA_ITF	pFuncPtrToWriteData;	    
} UDS_DidEepromDatMngRecd_t;

/* 0x2F InputOutputControlByIdentifier 
   service data Managing Index Table Record Type 
 */

typedef UDS_STATE_TYPE struct
{
	uint16_t		  dataIdentifier;		
	uint16_t  		  DataSize;
	uint16_t          AccessAttribute;	
	uint8_t           StartIndex; 
	uint8_t           NumOfEntry;

}UDS_IoCtrlIdxTblRcd_t;

/* 0x2F InputOutputControlByIdentifier 
   service data Managing Table Record Type 
 */

typedef UDS_STATE_TYPE struct
{
	uint8_t*                     pDataBuf;	       /* the addres of the data buffer */
	uint16_t                     IoCtrlBitmapMask; /* the bitmap mask for IO Control */
	T_FUNC_PTR_UDS_IOCTRL_ITF  pFuncPtrToIoCtrl; /* IO control interface function pointer */
}UDS_IoCtrlMngtDatTblRcd_t;



/* 0x31 RoutineControl 
   service data Managing Table Record Type 
 */
typedef enum {
   UDS_C_RTNCTRL_FSMST_CMPLT_PASSED  = 0x00u, 
   UDS_C_RTNCTRL_FSMST_CMPLT_FAILED  = 0x01u, 
   UDS_C_RTNCTRL_FSMST_ABORTED       = 0x02u, 
   UDS_C_RTNCTRL_FSMST_RUNNING       = 0x0Fu, 
   UDS_C_RTNCTRL_FSMST_NO_REQUEST    = 0xFFu  	
}UDS_RtnCtrlFsmSt_t; 

typedef enum{
   UDS_C_RTNCTRL_EV_idle    = 0x00u,	
   UDS_C_RTNCTRL_EV_init    = 0x01u,
   UDS_C_RTNCTRL_EV_start,    
   UDS_C_RTNCTRL_EV_stop,    
   UDS_C_RTNCTRL_EV_finish,  
   UDS_C_RTNCTRL_EV_results, 
   UDS_C_RTNCTRL_EV_status  
}UDS_RtnCtrlActEvt_t; 

typedef UDS_STATE_TYPE struct
{
   uint16_t   routineIdentifier;

   uint16_t   AccessAttribute;
   uint8_t    ValidArgumentNum;
   uint32_t   RtnRunLimitTime;
   uint8_t    ExpectedPosResult;

   /* start routine sub-function */
   uint8_t    (* const  pFuncPtrStart)( uint8_t * const p_RtnCtrlOpt);
   /* stop routine sub-function */
   void       (* const  pFuncPtrStop)( void );

   uint8_t    (* const  pFuncPtrGetResult)(void);
   uint8_t    (* const  pFuncPtrRtnCheck)(uint8_t * const p_RtnCtrlOpt);
   uint8_t    (* const  pFuncPtrIsRtnFinished)(void);

} UDS_RtnCtrlMngtDatTblRcd_t;


/* 0x34 RequestDownload 
   service data Managing Table Record Type 
 */

typedef UDS_STATE_TYPE struct
{
	 uint32_t	                          ReqDnldStartMemAdd; /* configured starting memory Address allowing to download */		
	 uint32_t  				              MemorySize;         /* configured memory sie for downloading */
	 uint16_t                             AccessAttribute;    /* to controlling the access authentication */
	 uint8_t*                             pDataBuf;           /* to pointer for the data buffer to save the downloaded data */
	 T_FUNC_PTR_UDS_PRE_DNLD_CHK_ITF      pFuncPtrPreDnldChk;
	 T_FUNC_PTR_UDS_DNLD_WT_DAT_ITF       pFuncPtrDnldWrtData;
     uint8_t                    (* const  pFuncPtrIsProgFinished)(void);
	 
} UDS_ReqDnldMngRecd_t;

typedef enum{
   KeyTypeIsUINT8  = 0x00u, 
   KeyTypeIsUINT16 = 0x01u  
} UDS_DidDatMngSearchKeyType_t;

typedef enum{
   UDS_APP_FSM_REGULAR_ST = 0x00u,          /*normal state (nonpending), should give back the response immediately */
   UDS_APP_FSM_PENDING_ST = 0x01u           /*pending state*/	
}UDS_FSM_PENDING_ST_t;

/* legend : ASB : absolute ; REL : relative (unitless) depends on the period of cyclic task */
#define UDS_APP_FSM_TMR_PENDING_ABS_TIME                     (1000000u*FBLUDS_C_TASK_CYCLE_ZOOM)  /*the time after which ECU send new pending msg (in ms)  = 2,000ms = 2s */
#define UDS_APP_FSM_TMR_MAX_PENDING_ABS_TIME            (11000000u*FBLUDS_C_TASK_CYCLE_ZOOM)  /*maximum time to respond with pending msg (unit is us ) 10000000us  = 10,000ms = 10s */
#define UDS_APP_FSM_TMR_INCREMENT                       UDS_DIAGDATA_INTERP_RATE  /*timer increment = task in which the timers are incremented (in ms)*/

#define UDS_APP_FSM_TMR_PENDING_REL_TIME                     (uint32_t)(UDS_APP_FSM_TMR_PENDING_ABS_TIME/UDS_APP_FSM_TMR_INCREMENT)  /* relative time after which ECU send new pending msg (in us)  = 2,000,000us /25,600 us = 78.125 ~ 78 (unitless) */
#define UDS_APP_FSM_TMR_MAX_PENDING_REL_TIME            (uint32_t)(UDS_APP_FSM_TMR_MAX_PENDING_ABS_TIME/UDS_APP_FSM_TMR_INCREMENT)   /*relative maximum time to respond with pending msg (in us) = 10,000,000us / 25,600us = 390.625 ~ 390 (unitless)  */

/* the legend : FP: Function Pointer */
typedef  uint8_t  (* T_FBLUDS_FP_PERIODIC_PARAMVOID)(void);

/* Data Managing constant definition */
/* DID and its attributes definition*/
#define UDS_C_DID_DATA_OPERATE_BUF_SIZE    ((uint16_t)320u) // 0x20u)
#define UDS_C_REQ_DN_OR_UP_LD_BUF_SIZE     ((uint16_t)256u)    /* must be 64bits , 8 bytes aligned  */

/* define the constants for DID data attribute */
#define UDS_C_DID_ATR_DIS_RD               ((uint16_t)0x0000u)  /* reading operation is disabled (disallowed) */
#define UDS_C_DID_ATR_ENA_RD               ((uint16_t)0x0001u)  /* reading operation is enabled (allowed) */

#define UDS_C_DID_ATR_DIS_WT               ((uint16_t)0x0000u)  /* writing operation is disabled (disallowed) */
#define UDS_C_DID_ATR_ENA_WT               ((uint16_t)0x0002u)  /* writing operation is enabled (allowed) */

#define UDS_C_DID_ATR_DIS_IOCTL            ((uint16_t)0x0000u)  /* IoControlling operation is disabled (disallowed) */
#define UDS_C_DID_ATR_ENA_IOCTL            ((uint16_t)0x0004u)  /* IoControlling operation is enabled (allowed) */

#define UDS_C_DID_ATR_RD_NO_SAL            ((uint16_t)0x0000u)  /* reading operation need pass no SAL */
#define UDS_C_DID_ATR_RD_SAL0              ((uint16_t)0x0000u)  /* writing/IoControlling operation need pass SAL0 = no SAL */
#define UDS_C_DID_ATR_RD_SAL11              ((uint16_t)0x0008u)  /* writing/IoControlling operation need pass SAL1 */


#define UDS_C_DID_ATR_WT_NO_SAL            ((uint16_t)0x0000u)  /* writing/IoControlling operation need pass no SAL */
#define UDS_C_DID_ATR_WT_SAL0              ((uint16_t)0x0000u)  /* writing/IoControlling operation need pass SAL0 = no SAL */
#define UDS_C_DID_ATR_WT_SAL11              ((uint16_t)0x0040u)  /* writing/IoControlling operation need pass SAL1 */


#define UDS_C_DID_ATR_RD_SESN_DFLT         ((uint16_t)0x0000u)  /* reading operation can be allowed in diagnostic default session mode */
#define UDS_C_DID_ATR_RD_SESN_EXTD         ((uint16_t)0x0200u)  /* reading operation can be allowed in diagnostic extended session mode */
#define UDS_C_DID_ATR_RD_SESN_SSS          ((uint16_t)0x0400u)  /* reading operation can be allowed in diagnostic supplier specific session mode */
#define UDS_C_DID_ATR_RD_SESN_PRGM         ((uint16_t)0x0800u)  /* reading operation can be allowed in diagnostic programming session mode */

#define UDS_C_DID_ATR_WT_SESN_DFLT         ((uint16_t)0x0000u)  /* writing/IoControlling operation can be allowed in diagnostic default session mode */
#define UDS_C_DID_ATR_WT_SESN_EXTD         ((uint16_t)0x1000u)  /* writing/IoControlling can be allowed in diagnostic extended session mode */
#define UDS_C_DID_ATR_WT_SESN_SSS          ((uint16_t)0x2000u)  /* writing/IoControlling can be allowed in diagnostic supplier specific session mode */
#define UDS_C_DID_ATR_WT_SESN_PRGM         ((uint16_t)0x4000u)  /* writing/IoControlling can be allowed in diagnostic programming session mode */

#define UDS_C_IDX_NOT_IN_TBL               (uint8_t)(0xFFu)

#define UDS_C_DID_END_OF_TBL_FFFF          ((uint16_t)0xFFFFu)  /* special DID to indicate the end of table record */

// define the constants for routine control attribute
/* legend :  RID : Routine Identifier ; ATR : Attribute 
 */
#define UDS_C_RID_ATR_DIS_RUN              ((uint16_t)0x0000u)
#define UDS_C_RID_ATR_ENA_RUN              ((uint16_t)0x0001u)
#define UDS_C_RID_ATR_NO_SECU_LVL          ((uint16_t)0x0000u)
#define UDS_C_RID_ATR_SECU_LVL_0           ((uint16_t)0x0000u)
#define UDS_C_RID_ATR_SECU_LVL_11           ((uint16_t)0x0010u)
#define UDS_C_RID_ATR_SESN_DEFLT           ((uint16_t)0x0000u)
#define UDS_C_RID_ATR_SESN_EXTD            ((uint16_t)0x0100u)
#define UDS_C_RID_ATR_SESN_SSS             ((uint16_t)0x0200u)
#define UDS_C_RID_ATR_SESN_PRGM            ((uint16_t)0x0400u)

#define UDS_C_IDX_NOT_IN_TBL               (uint8_t)(0xFFu)

#define UDS_C_DID_END_OF_TBL_FFFF          ((uint16_t)0xFFFFu)  /* special DID to indicate the end of table record */






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

/* Diagnostic and Communication Management functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_DiagSessionControl		( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_EcuReset				    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_SecurityAccess			( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ComControl				( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_TesterPresent			( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
/* Uds Service AccessTimingParameter is not supported by ISO15765-3. */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_AccessTimingParameter	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_SecuredDataTransmission	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ControlDTCSetting		( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern void UdsApp_85CtrlDtcSet_Init(void);

extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ResponseOnEvent		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_LinkControl              ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* Data Transmission functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ReadDataByIdentifier		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ReadMemoryByAddress			( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ReadScalingDataByIdentifier	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ReadDataByPeriodicIdentifier ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_DynamicDefineDataIdentifier	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_WriteDataByIdentifier		( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_WriteMemoryByAddress		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
// if support ISO 15031-5
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ISO_15031_5_Read01		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ISO_15031_5_Read03		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ISO_15031_5_Read07		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ISO_15031_5_Read09		    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );


/* Stored Data Transmission functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ClearDiagnosticInformation	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ReadDTCInformation			( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* InputOutput Control functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_IOControlByIdentifier        ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* Remote Activation of Routine functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_RoutineControl			    ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );


/* Upload and Download functional unit Services */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_RequestDownload		( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_RequestUpload		( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_TransferData         ( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_RequestTransferExit	( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* Services not implemented */
extern Std_UdsReturnType UDS_FN_TYPE UdsApp_ServiceUnknown( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp );

/* Service response functions. */
extern Std_UdsReturnType    UDS_FN_TYPE Uds_ServiceResponse( Uds_SessionTxBuf_t* pSessionTxBuf );
#ifdef UDS_ENABLE_CHANGEPARAMETER
extern void  UDS_FN_TYPE    Uds_ChangeParamRequest( Uds_SessionTxBuf_t* pSessionTxBuf );
#endif /* UDS_ENABLE_CHANGEPARAMETER */

/* UDS session buffers Read&Write functions. */
extern void  UDS_FN_TYPE 	Uds_RxNext( void );
extern void  UDS_FN_TYPE 	Uds_TxNext( const Uds_ServiceType_t txType );
extern Uds_SessionRxBuf_t* 	UDS_FN_TYPE Uds_GetRxBuf( void );
extern Uds_SessionTxBuf_t* 	UDS_FN_TYPE Uds_GetTxBuf( void );

/* UDS session management related functions. */
extern void   UDS_FN_TYPE 	Uds_SesnMgr_SessionInitialize( void );
extern void   UDS_FN_TYPE   Uds_SesnMgr_ResetSessionState( void );
extern void   UDS_FN_TYPE 	Uds_SesnMgr_SessionManager( void );
extern void   UDS_FN_TYPE	Uds_SesnMgr_UpdateServiceRespState( Uds_ServiceState_t serviceState );
extern uint32_t UDS_FN_TYPE 	Uds_SesnMgr_GetP2CanServerValue( void );
extern uint32_t UDS_FN_TYPE	    Uds_SesnMgr_GetP2StarCanServerValue( void );
extern uint8_t  UDS_FN_TYPE 	Uds_SesnMgr_SetActiveSession( const Uds_SessionLevel_t sessionLevel );
extern uint8_t  UDS_FN_TYPE	    Uds_SesnMgr_IsFirstFrameReceived( void );
extern uint8_t  UDS_FN_TYPE 	Uds_SesnMgr_IsRespConReceived( void );
extern uint8_t  UDS_FN_TYPE	    Uds_SesnMgr_GetRespConResult( void );
extern uint8_t  UDS_FN_TYPE 	Uds_SesnMgr_IsChangeParamConReceived( void );
extern uint8_t  UDS_FN_TYPE	    Uds_SesnMgr_GetChangeParamResult( void );
extern uint8_t  UDS_FN_TYPE	    Uds_SesnMgr_ChkSesnChangePreCndIsAllow( uint8_t i_CurrSession, uint8_t i_DestSession );
extern Uds_SessionLevel_t  	    UDS_FN_TYPE Uds_SesnMgr_GetActiveSession( void );
extern Uds_TAType_t			    UDS_FN_TYPE Uds_SesnMgr_GetReceivedTaType( void );

/* UDS Service processing related general functions. */
extern void  UDS_FN_TYPE	Uds_ServiceProc( const Uds_SessionRxBuf_t* pRxPacket, const Uds_SessionTxBuf_t* pTxPacket );
extern void  UDS_FN_TYPE	UdsApp_10Dsc_TriggerStartNewSessionActions(void);
extern void  UDS_FN_TYPE	UdsApp_10Dsc_generic_S3SeverTmrTimeoutEvtHandler(void);
extern void  UDS_FN_TYPE	Uds_generic_SendResp( Uds_APduData_t* pAPduResp, uint8_t lub_error );
extern uint8_t UDS_FN_TYPE Uds_generic_IsAPrevReqAlreadyRunning(uint8_t i_lub_CurrIncomeReqSid);
extern uint8_t UDS_FN_TYPE	Uds_generic_Get_CurrSvcProcFSMState(void);
extern uint8_t UDS_FN_TYPE	UdsApp_31RtnCtrl_Get_IsRoutineAlreadyRunning(void);
// extern void  UDS_FN_TYPE	Uds_Service_Pending_StateManager( uint8_t lub_SevericNRC );
//extern void  UDS_FN_TYPE	Uds_generic_ServiceCommonProcess( Uds_APduData_t* pAPduInd,
// 															  Uds_APduData_t* pAPduResp,
// 															  T_FUNC_PTR_UDS_SVC_HANDLER pFnc_UdsSvcSpecProc );
// extern Std_UdsReturnType UDS_FN_TYPE	Uds_generic_RcvAndSaveDiagReqMsg( Uds_APduData_t* pAPduInd, Uds_APduData_t* pAPduResp);
extern void UDS_FN_TYPE Uds_generic_max78pendingTONumReachedEventProc(void);

/* search function decleration by key */
extern void Uds_Generic_DatMgr_Init(void);

extern uint8_t  Uds_Generic_DatMgr_SearchTblByKey (uint16_t                         i_luwKey2Search,    /* searched ID */
                                                 UDS_DidDatMngSearchKeyType_t   i_lubSearchKeyType, /* uword(16bits) or ubyte(8bits) */             
                                                 uint8_t const *                  lpub_lookUp, 		/* address of first ID in table */
                                                 uint8_t                          lub_entrySize );	/* size of a table entry */

/* UDS Service specific functions. */
#ifdef UDS_ENABLE_LINKCONTROL
   extern void UDS_FN_TYPE		UdsApp_87LnkCtrl_Init(void);
#endif /* end of #ifdef UDS_ENABLE_LINKCONTROL */

#ifdef UDS_ENABLE_COMMUNICATIONCONTROL
extern void UDS_FN_TYPE		UdsApp_28ComCtrl_Init(void);
extern void UDS_FN_TYPE		UdsApp_28ComCtrl_ExecuteCommControlAction( uint8_t i_CntrlType, uint8_t i_CommSubnetType );
#endif /* end of #ifdef UDS_ENABLE_COMMUNICATIONCONTROL */

extern void Uds_Get_2ndIndRespBufPtrSet(Uds_APduData_t* o_Ind2ndPtr, 
                                           Uds_APduData_t* o_Resp2ndPtr);


/******************************************************************************
 *
 * Internal interfaces, which is provided by other modules within UDS Stack.
 *
 *****************************************************************************/

/**
 * UDS_APP_ITF_IMP_CB_FUNC_NUSDAT_IND : 
 * legend: 
 * UDS_APP: Unified Diagnostic Service Application 
 * ITF    : Interface
 * IMP    : Imported (interface type)       		
 */
/*
 * DiagnosticSessionControl required callbacks(internal provided).
 */
// #ifdef UDS_ENABLE_LINKCONTROL
//#define UDS_APP_ITF_INT_LNKCTRL_STRT_NEW_SESN_ACTION    			UdsApp_87LnkCtrl_Init() /* TODO: 0x87 LinkControl related new session action */
// #define UDS_APP_ITF_INT_LNKCTRL_HANDLE_S3_SVR_TMR_TO_EVT_ACTION   	UdsApp_87LnkCtrl_Init() /* TODO: 0x87 LinkControl related s3_severTmr TO action */
// #endif
// #ifdef UDS_ENABLE_COMMUNICATIONCONTROL
// #define UDS_APP_ITF_INT_COMCTRL_STRT_NEW_SESN_ACTION    			Uds_28ComCtrl_Init() /* TODO: 0x28 CommunicationControl related new session action */
// #define UDS_APP_ITF_INT_COMCTRL_HANDLE_S3_SVR_TMR_TO_EVT_ACTION   	Uds_28ComCtrl_Init() /* TODO: 0x28 CommunicationControl related s3_severTmr TO action */
// #endif

/*
 * UDS Diagnostic Application and Session Layer Macros
 */
#define UDS_APP_ITF_IMP_GET_TP_CHNL()						FBLUDS_ITF_EXP_GET_RX_TA_TYPE() // Uds_SesnMgr_GetReceivedTaType()    
#define UDS_APP_ITF_IMP_SET_RELOAD_S3SVR_TMR()				FBLUDS_ITF_EXP_RELOAD_S3_SVR_TMR()  // UDS_S3TIMER_START( Uds_SessionRuntime.S3Server )
#define UDS_APP_ITF_IMP_CHK_SESN_CHNG_PRE_CND(CurrSession, DestSession)   FBLUDS_ITF_EXP_CHK_SESN_CHNG_PRE_CND_IS_ALLOW(CurrSession, DestSession)
#define UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION()		    FBLUDS_ITF_EXP_GET_ACTIVE_SESSION()	 // Uds_SesnMgr_GetActiveSession()
#define UDS_APP_ITF_IMP_SET_CHANGE_SESSION(DestSession)		FBLUDS_ITF_EXP_CHANGE_SESSION(DestSession)  // FBLUDS_ITF_EXP_SET_ACTIVE_SESSION(DestSession) // Uds_SesnMgr_SetActiveSession(DestSession)
#define UDS_APP_ITF_IMP_GET_TP_P2SVR_TMR_VALUE()        	(P2CAN_SERVER_MAX_DEFAULT_VAL/1000u)  // Uds_SesnMgr_GetP2CanServerValue()
#define UDS_APP_ITF_IMP_GET_TP_P2START_SVR_TMR_VALUE()  	(P2STAR_CAN_SERVER_MAX_DEFAULT_VAL/1000u) // Uds_SesnMgr_GetP2StarCanServerValue()
#define UDS_SESN_MGR_ITF_IMP_CB_FUNC_S3_SVR_TMR_TO_NOTIFY()	UdsApp_10Dsc_generic_S3SeverTmrTimeoutEvtHandler()
#define UDS_SESN_MGR_ITF_IMP_CB_FUNC_P2S_MAX_TO_NOTIFY()	      Uds_generic_max78pendingTONumReachedEventProc()

/*
 * CommunicationControl required callbacks(internal provided).
 */
#ifdef UDS_ENABLE_COMMUNICATIONCONTROL
#define UDS_APP_ITF_IMP_SET_COMM_CTRL_ACTION(ComCtrlType, ComCtrlSubnetType)  UdsApp_28ComCtrl_ExecuteCommControlAction(ComCtrlType, ComCtrlSubnetType)
#endif

/*
 * AccessTimingParameter required callbacks(internal provided).
 */
#define UDS_APP_ITF_IMP_GET_EXT_ACC_TIM_PARAM(pAccTimParamBuffer)    (UDS_POSITIVE_RESPONSE)
#define UDS_APP_ITF_IMP_SET_TIM_PARAM_TO_DEFAULT()   				 (UDS_POSITIVE_RESPONSE)
#define UDS_APP_ITF_IMP_GET_CURR_ACT_TIM_PARAM(pAccTimParamBuffer)   (UDS_POSITIVE_RESPONSE)
#define UDS_APP_ITF_IMP_SET_TIM_PARAM_TO_GIVEN(pAccTimParamBuffer)   (UDS_POSITIVE_RESPONSE)

/******************************************************************************
*
* UDS Service handler post-processing.
*
******************************************************************************/
/* If we do not apply this diagnostic service, we assign the function call to it to a predefined handler. */
#ifndef UDS_ENABLE_DIAGNOSTICSESSIONCONTROL
    #define UdsApp_DiagSessionControl			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_DIAGNOSTICSESSIONCONTROL */

#ifndef UDS_ENABLE_ECURESET
    #define UdsApp_EcuReset					UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_ECURESET */

#ifndef UDS_ENABLE_SECURITYACCESS
    #define UdsApp_SecurityAccess				UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_SECURITYACCESS */

#ifndef UDS_ENABLE_COMMUNICATIONCONTROL
    #define UdsApp_ComControl					UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_COMMUNICATIONCONTROL */

#ifndef UDS_ENABLE_TESTERPRESENT
    #define UdsApp_TesterPresent				UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_TESTERPRESENT */

#ifndef UDS_ENABLE_ACCESSTIMINGPARAMETER
    #define UdsApp_AccessTimingParameter		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_ACCESSTIMINGPARAMETER */

#ifndef UDS_ENABLE_SECUREDDATATRANSMISSION
    #define UdsApp_SecuredDataTransmission		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_SECUREDDATATRANSMISSION */

#ifndef UDS_ENABLE_CONTROLDTCSETTING
    #define UdsApp_ControlDTCSetting		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_CONTROLDTCSETTING */

#ifndef UDS_ENABLE_RESPONSEONEVENT
    #define UdsApp_ResponseOnEvent			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_RESPONSEONEVENT */

#ifndef UDS_ENABLE_LINKCONTROL
    #define UdsApp_LinkControl				UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_LINKCONTROL */

#ifndef UDS_ENABLE_READDATABYIDENTIFIER
    #define UdsApp_ReadDataByIdentifier	UdsApp_ReadDataByIdentifier
#endif /* !UDS_ENABLE_READDATABYIDENTIFIER */
//if support ISO 15031-5
#define UdsApp_ISO_15031_5_Read01 UdsApp_ISO_15031_5_Read01
#define UdsApp_ISO_15031_5_Read03 UdsApp_ISO_15031_5_Read03
#define UdsApp_ISO_15031_5_Read07 UdsApp_ISO_15031_5_Read07
#define UdsApp_ISO_15031_5_Read09 UdsApp_ISO_15031_5_Read09

#ifndef UDS_ENABLE_READMEMORYBYADDRESS
    #define UdsApp_ReadMemoryByAddress		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_READMEMORYBYADDRESS */

#ifndef UDS_ENABLE_READSCALINGDATABYIDENTIFIER
    #define UdsApp_ReadScalingDataByIdentifier			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_READSCALINGDATABYIDENTIFIER */

#ifndef UDS_ENABLE_READDATABYPERIODICIDENTIFIER
    #define UdsApp_ReadDataByPeriodicIdentifier		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_READDATABYPERIODICIDENTIFIER */

#ifndef UDS_ENABLE_DYNAMICALLYDEFINEDATAIDENTIFIER
    #define UdsApp_DynamicDefineDataIdentifier		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_DYNAMICALLYDEFINEDATAIDENTIFIER */

#ifndef UDS_ENABLE_WRITEDATABYIDENTIFIER
    #define UdsApp_WriteDataByIdentifier			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_WRITEDATABYIDENTIFIER */

#ifndef UDS_ENABLE_WRITEMEMORYBYADDRESS
    #define UdsApp_WriteMemoryByAddress			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_WRITEMEMORYBYADDRESS */

#ifndef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION
    #define UdsApp_ClearDiagnosticInformation		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_CLEARDIAGNOSTICINFORMATION */

#ifndef UDS_ENABLE_READDTCINFORMATION
    #define UdsApp_ReadDTCInformation				UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_READDTCINFORMATION */

#ifndef UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER
    #define UdsApp_IOControlByIdentifier	UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER */

#ifndef UDS_ENABLE_ROUTINECONTROL
    #define UdsApp_RoutineControl			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_ROUTINECONTROL */

#ifndef UDS_ENABLE_REQUESTDOWNLOAD
    #define UdsApp_RequestDownload			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_REQUESTDOWNLOAD */

#ifndef UDS_ENABLE_REQUESTUPLOAD
    #define UdsApp_RequestUpload			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_REQUESTUPLOAD */

#ifndef UDS_ENABLE_TRANSFERDATA
    #define UdsApp_TransferData			UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_TRANSFERDATA */

#ifndef UDS_ENABLE_REQUESTTRANSFEREXIT
    #define UdsApp_RequestTransferExit		UdsApp_ServiceUnknown
#endif /* !UDS_ENABLE_REQUESTTRANSFEREXIT */

#endif /* _UDS_PRIV_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
