//****************************************************************************
// @Module        MultiCAN Controller 
// @Filename      CAN.h
// @Project       TC1782_CAN2_BAIC_ECU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1782
//
// @Compiler      Tasking 3.5r1
//
// @Codegenerator 1.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CAN module.
//
//----------------------------------------------------------------------------
// @Date          6/18/2014 14:19:39
//
//****************************************************************************

// USER CODE BEGIN (CAN_Header,1)

// USER CODE END



#ifndef _CAN_H_
#define _CAN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CAN_Header,2)
#include "Typedefs.h"
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_Header,3)

#define  UDS_ENABLE		1

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_Header,4)


// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

///  -------------------------------------------------------------------------
///  @Definition of a structure for the CAN data
///  -------------------------------------------------------------------------

// The following data type serves as a software message object. Each access to
// a hardware message object has to be made by forward a pointer to a software
// message object (CAN_SWObj). The data type has the following fields:
//
// usMOCfg:
// this byte contains the "Data Lenght Code" (DLC), the 
// "Extended Identifier" (IDE) and the "Message Direction" (DIR).
//
//
//         7     6     5      4    3     2     1     0
//      |------------------------------------------------|
//      |        DLC            | DIR | IDE |      |     |
//      |------------------------------------------------|
//
// uwID: 
// this field is four bytes long and contains either the 11-bit identifier 
// or the 29-bit identifier
//
// uwMask: 
// this field is four bytes long and contains either the 11-bit mask 
// or the 29-bit mask
//
// ubData[8]:
// 8 bytes containing the data of a frame
//
// usCounter:
// this field is two bytes long and contains the counter value 
//

typedef struct
  {
     ushort usMOCfg;    // message object configuration register
     uword  uwID;       // standard (11-bit)/extended (29-bit) identifier
     uword  uwMask;     // standard (11-bit)/extended (29-bit) mask
     ubyte  ubData[8];  // 8-bit data bytes
     ushort usCounter;  // frame counter
  }CAN_SWObj;

// USER CODE BEGIN (CAN_Header,5)
#define CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE       ((uint8_t)8u)

#define CANDRV_C_RX_PHY_ADDR_STD_CANMSGID       (uint32_t)(0x7E0u)//(uint32_t)(0x766u)  // (uint32_t)(0x7E0u)
#define CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID      (uint32_t)(0x7DFu)
#define CANDRV_C_TX_PHY_ADDR_STD_CANMSGID       (uint32_t)(0x7E8u)//(uint32_t)(0x7A6u)  //  (uint32_t)(0x7E8u)

enum CP_BAUD {
   /*!
   ** Baudrate 125 kBit/sec
   */
   CP_BAUD_125K = 0,

   /*!
   ** Baudrate 250 kBit/sec
   */
   CP_BAUD_250K = 1,

   /*!
   ** Baudrate 500 kBit/sec
   */
   CP_BAUD_500K = 2,

   /*!
   ** Baudrate 1 MBit/sec
   */
   CP_BAUD_1M = 3,

   /*!
   ** Use values for Btr0 and Btr1
   */
   CP_BAUD_BTR = 0x80
};
typedef enum
{
	CANDRV_C_RX_PHYSICAL_ADDRESSING = 0,
	CANDRV_C_RX_FUNCTIONAL_ADDRESSING
} Diag_ReqAddrTAType_t;


typedef struct
{
   uint8_t   m_IsUsingFlag;  /* the using States : TRUE is in using , FALSE is : free  */

   uint32_t  m_CanId;        /* to record the Rx/Tx CAN Msg Canid , can support upto 29 bit CAN2.0B extended id */
   uint8_t   m_CanDLC;       /* to record the Rx/Tx CAN Msg Len, currently, we always using 8 bytes DLC */
   uint8_t   m_DataBuffer[0x08u]; /* the payload data buffer of CAN Frame */
}T_CANDRV_BUF_QUEUE_RCD;

typedef struct
{
   uint8_t               m_CurrUsedQueueNum;
   uint8_t               m_CurrQueueHeadIndex;
   uint8_t               m_CurrQueueTailIndex;

   T_CANDRV_BUF_QUEUE_RCD m_CanBufQueueRcdTbl[CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE];
}T_CANDRV_BUF_QUEUE_MNGT_TBL;




/* Imported interfaces . */
#define CANDRV_DISABLE_ALL_INTERRUPTS()    	//DINT// SuspendAllInterrupts()
#define CANDRV_ENABLE_ALL_INTERRUPTS()      //EINT// ResumeAllInterrupts()


#define  	CP_MASK_EXT_FRAME 0x1FFFFFFF

#define  	CpMacGetExtId(MSG_PTR)           (MSG_PTR)&CP_MASK_EXT_FRAME

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CAN_vInit(void);
void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj);
//Uint16 CAN_vBusy(Uint16 ubObjNr);
Uint16 CAN_vTransmit(ubyte ubObjNr,uint8_t *data);
void CAN_vConfigMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj);

int CpCoreBaudrate(int ubBaudSelV);


// USER CODE BEGIN (CAN_Header,8)
extern uint8_t CanDrv_TransmitMessageRequest(uint32_t msgId,
                                              uint8_t* pBytes,
                                              uint8_t  numBytes);

extern void UdsCanApp_AbortTransmit( uint32_t msgId );


extern uint8_t CanDrv_ReadRxCanMsg(uint8_t*  pub_Channel,
      	                           uint8_t*  pubCanBufIdx,
                                    uint8_t* pubBuffer,
                                    uint8_t* pubCount );


extern uint8_t CanDrv_GetTxMsgFinishedFlag(void);

extern uint8_t  CanDrv_SendDebugMsg1(uint8_t *i_lup_DatBufToSend);
extern uint8_t  CanDrv_SendDebugMsg2(uint8_t *i_lup_DatBufToSend);
extern uint8_t  CanDrv_SendDebugMsg3(uint8_t *i_lup_DatBufToSend);

extern void CanDrv_RxTxMsgPollingMode(void);
extern void CanDrv_RxPhyAddrChlByPollingMode(void);
extern void CanDrv_RxFuncAddrChlByPollingMode(void);
extern void CanDrv_TxPhyAddrChlConfirmByPollingMode(void);

extern uint8_t  CanDrv_BootLoaderMsg(uint16 x);

// USER CODE END


//****************************************************************************
// @Macro         CAN_ubGetTxErrorCounter(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the transmit error 
//                counter of the selected node. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the transmit error counter
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

#define CAN_ubGetTxErrorCounter(NODE_NAME) _GetTxErrorCounter##NODE_NAME()
#define _GetTxErrorCounterCAN_NODE0()  (ubyte)((CAN_NECNT0 & 0x0000FF00) >> 8)
#define _GetTxErrorCounterCAN_NODE1()  (ubyte)((CAN_NECNT1 & 0x0000FF00) >> 8)
#define _GetTxErrorCounterCAN_NODE2()  (ubyte)((CAN_NECNT2 & 0x0000FF00) >> 8)


//****************************************************************************
// @Macro         CAN_ubGetRxErrorCounter(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the receive error 
//                counter of the selected node. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the receive error counter
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

#define CAN_ubGetRxErrorCounter(NODE_NAME) _GetRxErrorCounter##NODE_NAME()
#define _GetRxErrorCounterCAN_NODE0()  (ubyte)(CAN_NECNT0 & 0x000000FF)
#define _GetRxErrorCounterCAN_NODE1()  (ubyte)(CAN_NECNT1 & 0x000000FF)
#define _GetRxErrorCounterCAN_NODE2()  (ubyte)(CAN_NECNT2 & 0x000000FF)


//****************************************************************************
// @Macro         CAN_ubGetErrorTransferDirection(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the Last Error 
//                Transfer Direction flag. 0 indicates that the last error 
//                occurred while the selected CAN node was receiving a 
//                message. The receive error counter has been incremented. 1 
//                indicates that the last error occurred while the selected 
//                CAN node was transmitting a message. The transmit error 
//                counter has been incremented. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   0 receive error, else transmit error
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

#define CAN_ubGetErrorTransferDirection(NODE_NAME) _GetErrorTransferDirection##NODE_NAME()
#define _GetErrorTransferDirectionCAN_NODE0()  (ubyte)((CAN_NECNT0 & CAN_NECNT0_LETD) >> 24)
#define _GetErrorTransferDirectionCAN_NODE1()  (ubyte)((CAN_NECNT1 & CAN_NECNT1_LETD) >> 24)
#define _GetErrorTransferDirectionCAN_NODE2()  (ubyte)((CAN_NECNT2 & CAN_NECNT2_LETD) >> 24)


//****************************************************************************
// @Macro         CAN_ubGetErrorIncrement(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the Last Error 
//                Increment flag. If the Bit Stream Processor itself detects 
//                an error while a transmit operation is running, the 
//                Transmit Error Counter is incremented by 8. An increment of 
//                1 is used, when the error condition was reported by an 
//                external CAN node via an error frame generation. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   0 counter is incrementd by 1, counter is incremented by 8
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

#define CAN_ubGetErrorIncrement(NODE_NAME) _GetErrorIncrement##NODE_NAME()
#define _GetErrorIncrementCAN_NODE0()  (ubyte)((CAN_NECNT0 & CAN_NECNT0_LEINC) >> 25)
#define _GetErrorIncrementCAN_NODE1()  (ubyte)((CAN_NECNT1 & CAN_NECNT1_LEINC) >> 25)
#define _GetErrorIncrementCAN_NODE2()  (ubyte)((CAN_NECNT2 & CAN_NECNT2_LEINC) >> 25)


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (CAN_Header,9)
enum SdoCmd_e {

   eSDO_WRITE_REQ_SEG   = 0x21,  /*! segmented write request               */
   eSDO_WRITE_REQ_0     = 0x22,  /*! write request, unspecified length     */
   eSDO_WRITE_REQ_4     = 0x23,  /*! write request, 4 bytes data           */
   eSDO_WRITE_REQ_3     = 0x27,  /*! write request, 3 bytes data           */
   eSDO_WRITE_REQ_2     = 0x2B,  /*! write request, 2 bytes data           */
   eSDO_WRITE_REQ_1     = 0x2F,  /*! write request, 1 byte data            */
   eSDO_WRITE_RESP      = 0x60,  /*! response to write request             */

   eSDO_READ_REQ        = 0x40,  /*! read request                          */
   eSDO_READ_RESP_SEG   = 0x41,  /*! read response, segmented data         */
   eSDO_READ_RESP_0     = 0x42,  /*! read response, unspecified length     */
   eSDO_READ_RESP_4     = 0x43,  /*! read response, 4 bytes data           */
   eSDO_READ_RESP_3     = 0x47,  /*! read response, 3 bytes data           */
   eSDO_READ_RESP_2     = 0x4B,  /*! read response, 2 bytes data           */
   eSDO_READ_RESP_1     = 0x4F,  /*! read response, 1 byte data            */

	eSDO_READ_POINTER_2		= 0x52,	/*! read UINT16 pointer */
	eSDO_READ_POINTER_4		= 0x54,	/*! read UINT32 pointer */

   eSDO_READ_REQ_SEG_0  = 0x60,  /*! read request, segmented data          */
   eSDO_READ_REQ_SEG_1  = 0x70,  /*! read request, segmented data          */

   eSDO_ABORT           = 0x80   /*! abort transmission                    */
};


enum CoDT {
   /*!
   ** data type:  boolean value
   */
   CoDT_BOOLEAN = 1,

   /*!
   ** data type:  Signed Integer, 1 byte
   */
   CoDT_INTEGER8,

   /*!
   ** data type:  Signed Integer, 2 bytes
   */
   CoDT_INTEGER16,
   
   /*!
   ** data type:  Signed Integer, 4 bytes
   */
   CoDT_INTEGER32,

   /*!
   ** data type:  Unsigned Integer, 1 byte
   */
   CoDT_UNSIGNED8,

   /*!
   ** data type:  Unsigned Integer, 2 bytes
   */
   CoDT_UNSIGNED16,

   /*!
   ** data type:  Unsigned Integer, 4 bytes
   */
   CoDT_UNSIGNED32,

   /*!
   ** data type:  Float, 32 bit according to IEEE
   */
   CoDT_REAL32,

   /*!
   ** data type:  character string
   */
   CoDT_VISIBLE_STRING,
   
   /*!
   ** data type:  octet string
   */
   CoDT_OCTET_STRING,
   
   /*!
   ** data type:  unicode string
   */
   CoDT_UNICODE_STRING,

   /*!
   ** data type:  time of day value
   */
   CoDT_TIME_OF_DAY,
   
   /*!
   ** data type:  time difference value
   */
   CoDT_TIME_DIFFERENCE
};


// USER CODE END
//#define SDO_EN

#endif  // ifndef _CAN_H_
