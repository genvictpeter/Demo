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
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Type of network transport layer timer variables are modified from  *
*         unsigned 16bit to unsigned 32bit.                                  *
*         Modify definition of ISO15765_MAX_STMIN to 127000u in unit of us.  *
*         Remove definition of ¡°flagSTmin_MicroSec¡± from UdsTp_Session_t.    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.2 Rev1 | Nov/07/2013    |                         | Yongqiang Deng   *
* Delivery_005                                                               *
*    to use the unified basic type : uint8_t , uint16_t, uint32_t, uint64_t  *
*    to remove the similar coexisitn basic type for UINT8  uint8 and so on   *
*    and remove some MISRA warning                                           *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSTP_PRIV_H
#define _UDSTP_PRIV_H



#include "uds_target.h"
#include "udstp_confdefs.h"
#include "udscan_conf.h"



/*lint -e749*//*lint -e750*//*lint -e751*//*lint -e752*//*lint -e754*//*lint -e963*/

/* Turn off lint test Info 793: ANSI/ISO limit of 6 'significant characters in an external identifier' */
/*lint -"esym(793,significant characters in an external identifier)"*/

/* [MISRA 2004 Required Rule 18.4] unions shall not be used */
/*lint -esym(960,18.4) */

/* [MISRA 2004 Required Rule 19.4] Disallowed definition for macro 'xxx' */
/*lint -esym(960,19.4) */

/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

/* Preprocessor for Network timing
 *
 * FALSE - only used during debugging.
 * TRUE  - This shall be used after debugging.
 */
#define UDSTP_TIMING_ENABLE 		TRUE

/* Define of masks
 *
 */
#define ISO15765_NPDU_LENGTH_MASK	  0x0FFFu	/* ISO15765-2 defined max length of message data is 12bit. */
#define ISO15765_TPCI_MASK      	  0xF0u	    /* N_PCItype mask */
#define ISO15765_TPCI_SF        	  0x00  	/* Single Frame */
#define ISO15765_TPCI_FF        	  0x10u  	/* First Frame */
#define ISO15765_TPCI_CF        	  0x20u  	/* Consecutive Frame */
#define ISO15765_TPCI_FC        	  0x30u  	/* Flow Control frame */
#define ISO15765_TPCI_SF_DL_MASK	  0x0Fu  	/* SF SF_DL mask */
#define ISO15765_TPCI_FF_DL_MASK	  0x0FFF	/* FF FF_DL mask */
#define ISO15765_TPCI_CF_SN_MASK	  0x0Fu	    /* CF Sequence number mask */
#define ISO15765_TPCI_FC_FS_MASK   	  0x0Fu  	/* Flowcontrol FlowStatus mask */

/* Define ISO15765-2 data link layer interface required addressing format.
 *
 */
#define ADDRESSING_NORMAL_RANGE	  	0x01u			/* addressingType smaller than this value means normal addressing. */
#define ADDRESSING_NORMAL           0x00u
#define ADDRESSING_NORMAL_FIXED     0x01u
#define ADDRESSING_EXTENDED         0x02u
#define ADDRESSING_MIXED11BIT       0x03u
#define ADDRESSING_MIXED29BIT       0x04u

/* Defines for padding CAN frames concerning the length of the data field in a CAN frame
 * less than 8 bytes
 * 
 */
#define CAN_FRAME_DATA_PADDING_ON   0x00u
#define CAN_FRAME_DATA_PADDING_OFF  0x01u


/* Define Maxium value for STmin defined by ISO15765-2 specification.
 *
 * Unit: ms
 * It is used to assign to STmin of one session who received a FC frame with a Sprc reserved STmin value.
 *
 */
#define ISO15765_MAX_STMIN	    	  127000u		/** UdsTp_req 68 */

/* Define FlowControl Frame Flow Status
 *
 */
#define ISO15765_FLOW_CTRL_STATUS_CTS        0x00u
#define ISO15765_FLOW_CTRL_STATUS_WAIT       0x01u
#define ISO15765_FLOW_CTRL_STATUS_OVFLW      0x02u

/* Define values of Std_UdsTpReturnType which are used for function returns
 * of UdsTp module.
 */ 
#ifndef E_OK
  #define E_OK 					((Std_UdsTpReturnType)0x00u)
#endif
#ifndef E_NOT_OK
   #define E_NOT_OK             ((Std_UdsTpReturnType)0x01u)
#endif

#define E_PENDING				((Std_UdsTpReturnType)0x02u)	/* service request can not be performed at the time return from service call. */
#define E_PROTOCOL_NOT_ALLOWED	((Std_UdsTpReturnType)0x03u)	/* Due to an protocol format error detected. */
#define E_FLOWCONTROL_SN_ERR	((Std_UdsTpReturnType)0x04u)
#define E_FLOWCONTROL_CONTINUE	((Std_UdsTpReturnType)0x05u)
#define E_FLOWCONTROL_WAIT		((Std_UdsTpReturnType)0x06u)
#define E_FLOWCONTROL_FS_ERR	((Std_UdsTpReturnType)0x07u)
#define E_FLOWCONTROL_ERR		((Std_UdsTpReturnType)0x08u)

/******************************************************************************
*
* Type definitions
*
******************************************************************************/

typedef uint16_t	UdsTp_NPduLength_t;
typedef uint8_t     UdsTp_NPduSTmin_t;
typedef uint32_t    UdsTp_NPduTxSTmin_t;
typedef uint8_t	    UdsTp_NPduBs_t;
typedef uint8_t 	Std_UdsTpReturnType;

typedef enum
{
	RX_TX_IDLE = 0x00u,		    /* Transport processor Idle. */
	RX_IN_PROGRESS,			  	/* Single frame reception in process. */
	SEG_RX_IN_PROGRESS,			/* Segmented data reception in process. */
	TX_IN_PROGRESS,			 	/* Single frame transmission in process. */
	SEG_TX_IN_PROGRESS			/* Segmented data transmission in process. */
} ISO15765_TpState_t;

typedef enum
{
	SEG_RX_WAIT_SENT_FC_CTS_CON = 0x00u,
	SEG_RX_WAIT_SENT_FC_WAIT_CON,
	SEG_RX_WAIT_SENT_FC_OVFLW_CON,
	SEG_RX_WAIT_CF
} UdsTp_SegReceiveCtrl_t;

typedef enum
{
	SEG_TX_WAIT_SENT_FF_CON = 0x00u,
	SEG_TX_FLOWCONTROL_RECEIVED,
	SEG_TX_SEND_CF_WITH_STMIN,
	SEG_TX_WAIT_SENT_CF_CON,
	SEG_TX_WAIT_FLOWCONTROL
} UdsTp_SegTransmitCtrl_t;

typedef enum 
{
	SINGLE_FRAME = 0x00u,
	FIRST_FRAME,
	CONSECUTIVE_FRAME,
	FLOW_CONTROL_FRAME,
	INVALID_FRAME,
	NO_FRAME
} UdsTp_FrameType_t;

typedef enum
{
	N_OK = 0x00u,			    /* (both sender and receiver side) service execution successfully completed. */
	N_TIMEOUT_A,		  /* (both sender and receiver side) N_Ar/N_As timeout occured */
	N_TIMEOUT_BS,		  /* (only sender side) N_Bs timeout occured */
	N_TIMEOUT_CR,		  /* (only receiver side) N_Cr timeout occured */
	N_WRONG_SN,			  /* (only receiver side) reception of an unexpected sequence number(CF.PCI.SN) */
	N_INVALID_FS,		  /* (only sender side)   reception of an invalid/unknown FlowStatus(FC.PCI.FS) */
	N_UNEXP_PDU,	  	/* (only receiver side) reception of an unexpected PDU */
	N_WFT_OVRN,			  /* (only sender side)   reception of FC.PCI.FS=WAIT > N_WFTmax */
	N_BUFFER_OVFLW,		/* (only sender side)   reception of FC.PCI.FS=OVFLW */
	N_ERROR				    /* (both sender and receiver side) general error detected by network transport layer */
} UdsTp_NResult_t;		/** UdsTp_req 19 */

typedef enum
{
	N_ParamOK = 0x00u,	  	/* (both sender and receiver side) service execution successfully completed. */
	N_RX_ON,			      /* (only receiver side) service didn't executed since a reception of the message identified by <AI> was taking place. */
	N_WRONG_PARAMETER,	/* (both sender and receiver side) service didn't executed due to an undefined <Parameter>. */
	N_WRONG_VALUE	    	/* (both sender and receiver side) service didn't executed due to an out-of-range <Parameter_Value>. */
} UdsTp_NResult_ChangeParam_t;

typedef struct
{
	uint16_t		msgLen;										/* Number of bytes in msgData[]. */
	uint8_t			msgData[ISO15765_NSDU_MSGDATA_LENGTH];		/** UdsTp_req 18 */
} UdsTp_NPduMsgData_t;

typedef enum
{
	DIAGNOSTIC = 0x00u,
	REMOTEDIAGNOSTIC
} UdsTp_NPduMtype_t;

typedef enum
{
	CANTP_PHYSICAL = 0x00u,
	CANTP_FUNCTIONAL
} UdsTp_NTaType_t;

typedef UDS_CONFIG_TYPE struct
{
	UdsTp_Addr_t		addrServer;			  /* uint8_t type server address */
	UdsTp_Addr_t		addrClient;		  	/* uint8_t type client address */
	UdsTp_Addr_t		addrExtenServer;	/* uint8_t type server address extention */
	UdsTp_Addr_t		addrExtenClient;	/* uint8_t type client address extention */
} UdsTp_NPduAI_t;

/* ISO15765-2 data link layer interface required addressing format for send/receive N_PDUs which will
 * be used for encapsulating CAN ID values. */
typedef enum
{
	NORMAL = 0x00u,
	NORMAL_FIXED,
	EXTENDED,
	MIXED11BIT,
	MIXED29BIT
} UdsTp_AddressingFormat_t;			/** UdsTp_req 1 */

/* Optional configuration for padding CAN frames concerning the length of the data field in a CAN frame
 * less than 8 bytes. */
typedef enum
{
	PADDING_ON = 0x00u,
	PADDING_OFF
} UdsTp_PaddingCfg_t;

typedef struct
{
	uint32_t        nAr;				/* Timeout for transmission of a CAN frame on receiver side (ms). */
	uint32_t        nBr;				/* N/A, Timeout until transmission of the next FlowControl N_PDU (ms). */
	uint32_t        nCr;				/* Timeout until reception of the next consecutive frames (ms). */
} UdsTp_RxNTiming_t;

typedef struct
{
	uint32_t        nAs;				/* Timeout for transmission of a CAN frame on sender side (ms). */
	uint32_t        nBs;				/* Timeout until reception of the next FlowControl N_PDU (ms). */
	uint32_t        nCs;				/* N/A, Timeout until transmission of the next consecutive frames (ms). */
} UdsTp_TxNTiming_t;

typedef UDS_CONFIG_TYPE struct
{
	UdsTp_NPduMsgData_t*	pNPdu_MsgData;	/* referencing to the data to be exchanged with higher layer. */
	union
	{
		UdsTp_RxNTiming_t 	rxNTiming;	  	/* Notwork layer timing parameters for sender. */
		UdsTp_TxNTiming_t	txNTiming;		/* Notwork layer timing parameters for receiver. */
	} timingData;
} UdsTp_NSduCfg_t;

typedef UDS_CONFIG_TYPE struct
{
	const void*             	pTransportCfg;	/* The configuration of the transport layer associated with this session */
  /* The following point to functions within the Data Link Layer Interface associated with the session. */
  UdsCan_QueueBufPtr 	UDS_FN_TYPE (*pGetTxBuf)      ( uint8_t sessionId );
  UdsCan_QueueBufPtr 	UDS_FN_TYPE (*pGetRxBuf)      ( uint8_t sessionId );
  void				        UDS_FN_TYPE (*pTxNext)        ( uint8_t sessionId );
  void          		  UDS_FN_TYPE (*pRxNext)        ( uint8_t sessionId );
  void          	  	UDS_FN_TYPE (*pTxAbortRequest)( uint8_t sessionId );
	UdsTp_NPduMtype_t		    	nPdu_Mtype;		  /* diagnostic or remote diagnostic. */
	UdsTp_NPduAI_t*				    pNPdu_AI;		    /* Network layer address information. */
	UdsTp_NPduSTmin_t			    nPdu_STmin; 	  /* As CF receiver, minimum time the sender shall wait between transmissions of two CF N-PDUs. */
	UdsTp_NPduBs_t			  	  nPdu_Bs;		    /* As CF receiver, maximum number of CF N-PDUs msgs in one block allowed from sender before sent flow control. */
#ifdef UDSTP0_NPDU_WFTMAX
	uint8_t 						        nPdu_WFTmax;	    /* Max number FC wait that can be transmitted consecutively. *//** UdsTp_req 69-72 */
#endif /* UDSTP0_NPDU_WFTMAX */
	UdsTp_AddressingFormat_t	addressingFormat;	/* CAN ID format for send/receive N_PDUs. */
	UdsTp_PaddingCfg_t 			  paddingCfg;		  	/* Enable use of padding. */
	UdsTp_NSduCfg_t*			    pNSduCfg;
} UdsTp_SessionCfg_t;

typedef UDS_STATE_TYPE struct
{
	ISO15765_TpState_t			  	tpState;		/* state machine of the network transport layer. */
	UdsTp_SegReceiveCtrl_t			segRxCtrl;
	UdsTp_SegTransmitCtrl_t			segTxCtrl;
	UdsTp_NTaType_t		    		nTaType;		/* Functional or physical addressing. */
	/* For transmit direction of FC frames(CF PDUs receiver), this is the minimum time the sender shall wait
	 * between transmissions of two CF N-PDUs. */
	UdsTp_NPduSTmin_t			    nPdu_STmin;
	/* For transmit direction of FC frames(CF PDUs receiver), this is the maximum number of CF N-PDUs msgs in one block
	 * which is allowed from sender before sent flow control. */
	UdsTp_NPduBs_t			    	nPdu_Bs;
	/* For receive direction of FC frames(CF PDUs sender), this represent the received minimum time it shall wait
	 * between transmissions of two CF N-PDU. */
	UdsTp_NPduTxSTmin_t				nPdu_TxSTmin;
	/* For receive direction of FC frames(CF PDUs sender), this represent the received maximum number of messages of CF N-PDUs
	 * in one block that it can transmissions before receive next flow control from receiver. */
	UdsTp_NPduBs_t					nPdu_TxBs;
	UdsTp_FrameType_t				pendingFrameType;		/* Type of frame that pending to dispatch to upper layer which kept in local buffer. */
	uint8_t					        nUSDataTransReq;		/* Flag of new N_USData transmit request from upper layer. */
	uint8_t						    flagZeroFlowCtrlReq;	/* Flag to Indicate that received BlockSize is ZERO. */
	UdsTp_NPduTxSTmin_t			    timeoutCounterST;		/* counter for seperation time between send of two CF frames, init value is received STmin. */
	UdsTp_NPduLength_t		  		nPdu_Length;			/* length of data to be received/transmited. */
	uint16_t					    numBlockBytes;			/* Number of bytes that can be received in one block. */
	uint8_t						    nPdu_SeqNum;		  	/* CF_PDU SN */
	uint8_t					        numBytesLstFrame;		/* Number of data bytes in the last consecutive frame of current block. */
	uint16_t					    remainBlocks;			/* Current remaining blocks for the segment data. */
	uint16_t						remainConseFrame;		/* Current remaining consecutive frames expected (downward counting). */
	uint16_t						currentBufPos;			/* Current buffer position in UdsTp0_NPdu_MsgData for block data. */
#ifdef UDSTP0_NPDU_WFTMAX
	uint8_t						    counterWFT;			  	/* counter for WFT frames to be send only when as a segment data receiver. */
#endif /* UDSTP0_NPDU_WFTMAX */
	uint8_t					        sentConfirmed;			/* Confirmation flag from udscan module indicating last transmit request finished. */
	uint8_t                     	flagTimeoutCounter;		/* state of timeout counter. */
	uint32_t 						timeoutCounter;			/* Counter for timeout. count down */
} UdsTp_Session_t;

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
/* [MISRA 2004 Required Rule 8.9] undefined symbol: 'xxx' */
/*lint -esym(960,8.9) */

extern UdsTp_NTaType_t	 UDS_FN_TYPE UdsTp_GetTaType( const uint8_t sessionId, const UdsCan_QueueBuf_t* pRxPacket );
extern UdsTp_FrameType_t UDS_FN_TYPE UdsTp_SetFrameType( uint16_t msgLen );
extern void UDS_FN_TYPE UdsTp_PackCanId( UdsCan_QueueBufPtr pTxPacket );

extern Std_UdsTpReturnType UDS_FN_TYPE UdsTp_GetSingleFrame( const uint8_t sessionId, const UdsCan_QueueBufPtr pRxPacket );
extern Std_UdsTpReturnType UDS_FN_TYPE UdsTp_GetFirstFrame( const uint8_t sessionId, const UdsCan_QueueBufPtr pRxPacket, UdsCan_QueueBufPtr pTxPacket );
extern Std_UdsTpReturnType UDS_FN_TYPE UdsTp_GetFlowCtrlFrame( const uint8_t sessionId, const UdsCan_QueueBufPtr pRxPacket );
extern Std_UdsTpReturnType UDS_FN_TYPE UdsTp_GetConsecutiveFrame( const uint8_t sessionId, const UdsCan_QueueBufPtr pRxPacket, UdsCan_QueueBufPtr pTxPacket );

extern void UDS_FN_TYPE UdsTp_SegRxProc( UdsTp_SessionCfg_t* pTpSessionCfg, UdsTp_Session_t* pTpSession, const uint8_t sessionId, const UdsTp_FrameType_t frameType, const UdsCan_QueueBufPtr pRxPacket, UdsCan_QueueBufPtr pTxPacket );
extern void UDS_FN_TYPE UdsTp_SegTxProc( UdsTp_SessionCfg_t* pTpSessionCfg, UdsTp_Session_t* pTpSession, const uint8_t sessionId, const UdsTp_FrameType_t frameType, const UdsCan_QueueBufPtr pRxPacket, UdsCan_QueueBufPtr pTxPacket );

extern void UDS_FN_TYPE UdsTp_TransmitProc( const uint8_t sessionId, UdsCan_QueueBufPtr pTxPacket );
extern void UDS_FN_TYPE UdsTp_SendSingleFrame( const uint8_t sessionId, UdsCan_QueueBufPtr pTxPacket );
extern void UDS_FN_TYPE UdsTp_SendFlowCtrlFrame( const uint8_t sessionId, UdsCan_QueueBufPtr pTxPacket, uint8_t flowStatus, uint8_t blockSize, uint8_t stMin );
extern void UDS_FN_TYPE UdsTp_SendConsecutiveFrame( const uint8_t sessionId, UdsCan_QueueBufPtr pTxPacket );
extern Std_UdsTpReturnType UDS_FN_TYPE UdsTp_SendFirstFrame( const uint8_t sessionId, UdsCan_QueueBufPtr pTxPacket );

extern void UDS_FN_TYPE UdsTp_NUSData_indication( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t nResult, uint16_t msgLen, uint8_t* pMsgData );
extern void UDS_FN_TYPE UdsTp_NUSData_FFindication( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint16_t msgLen );
extern void UDS_FN_TYPE UdsTp_NUSData_Confirmation( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t nResult );
extern void UDS_FN_TYPE UdsTp_NChangeParam_Request( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t param, uint8_t paramValue );
extern void UDS_FN_TYPE	UdsTp_NChangeParam_Confirmation( uint8_t mType, uint8_t nSa, uint8_t nTa, uint8_t nTaType, uint8_t nAe, uint8_t param, uint8_t result );

#endif /* _UDSTP_PRIV_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
