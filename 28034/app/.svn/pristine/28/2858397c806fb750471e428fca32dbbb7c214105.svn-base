//****************************************************************************
// @Module       
// @Filename      CAN.c
// @Project       BQApp
//----------------------------------------------------------------------------
// @Controller    TI 28034
//
// @Compiler      V5.211
//
// @Codegenerator CCS 3.3
//
// @Description   
//
//----------------------------------------------------------------------------
// @Date          12/19/2014
//
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****
//
//****************************************************************************

// USER CODE BEGIN (CAN_General,1)
#include "main.h"
#include "typedefs.h"
#include "CAN.h"
#include "Const.h"
#include "FunctionCode.h"
// USER CODE END

#include "CANProtocal.h"
#include "GlobalVariables.h"
//****************************************************************************
// @Project Includes
//****************************************************************************



// USER CODE BEGIN (CAN_General,2)
#include "FblMgr.h"
#include "FblTpExtItf.h"
#include "Uds_priv.h"
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

#define SetListCommand(Value) CAN_PANCTR = Value; while (CAN_PANCTR & CAN_PANCTR_BUSY);

// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// Structure for a single MultiCAN object
// A total of 128 such object structures exists

struct stCanObj 
{
  uword  uwMOFCR;    // Function Control Register
  uword  uwMOFGPR;   // FIFO/Gateway Pointer Register
  uword  uwMOIPR;    // Interrupt Pointer Register
  uword  uwMOAMR;    // Acceptance Mask Register
  ubyte  ubData[8];  // Message Data 0..7
  uword  uwMOAR;     // Arbitration Register
  uword  uwMOCTR;    // Control Register
};

#define CAN_HWOBJ ((struct stCanObj volatile *) 0xF0005000)

// USER CODE BEGIN (CAN_General,4)

// USER CODE END
uint8_t DebugData[8];

extern uint32  BusOffTime,BusOffResetTime;	

//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

//static ubyte aubFIFOWritePtr[128];
//static ubyte aubFIFOReadPtr[128];

// USER CODE BEGIN (CAN_General,7)


CAN_SWObj rul_PhyAddrRxCanSwObj;
static uint32_t  rub_PhyAddrRxID;                 /* Received message ID */
static uint8_t   rub_PhyAddrRxLENGTH;             /* Recieved message number of data bytes */

static CAN_SWObj rul_FuncAddrRxCanSwObj;
static uint32_t  rub_FuncAddrRxID;                 /* Received message ID */
static uint8_t   rub_FuncAddrRxLENGTH;             /* Recieved message number of data bytes */


static uint8_t   TxPhyAddrSemophore;				/*Have message to be Send*/ 
static uint8_t   rub_ATxMsgIsConfirmed;

static uint32_t  rull_TpReqSendRspCounter; 
static uint32_t  rull_CanDrvSendCnfirmCounter; 

//static T_CANDRV_BUF_QUEUE_MNGT_TBL  rul_CanDrvRxBufQueueMngtTbl;
//static T_CANDRV_BUF_QUEUE_MNGT_TBL  rul_CanDrvTxBufQueueMngtTbl;
T_CANDRV_BUF_QUEUE_MNGT_TBL  rul_CanDrvRxBufQueueMngtTbl;
T_CANDRV_BUF_QUEUE_MNGT_TBL  rul_CanDrvTxBufQueueMngtTbl;
T_CANDRV_BUF_QUEUE_MNGT_TBL* pul_CanDrvRxBufQueueMngtTblPtr; 	//CAN 报文接收buffer
T_CANDRV_BUF_QUEUE_MNGT_TBL* pul_CanDrvTxBufQueueMngtTblPtr;

uint16 RecData[8];
uint16 Recindex;

uint16 RecData2[8];
uint16 Recindex2;

extern int isUpdateMe;
// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)
#if SDO_EN
uint16 TotalNumFunc[30];
const uint16 GroupList[]={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,					//0
									 10,11,12,13,14,15,16, 0, 0, 0,					//10
									  0, 0, 0, 0, 0,17,18,19,20, 0,					//20
									 21,22,23,24,25, 0, 0, 0, 0, 0,					//30
									 26, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//40									 									  
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//50
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//60
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//70
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//80
									  0, 0, 0, 0, 0, 0, 0,27,28,29};					//90 
									  
CAN_SWObj rul_SDOCanSwObj;

void   InitDici();
//void Sdo_PollingMode();
#endif
// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)
//static void CanDrv_Loopback_Test_TransmitMsg (void);
static uint8_t CanDrv_GetAReadySendMsgFromBufQueue2Send(void);
static void CanDrv_Init_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL * i_pCanDrvBufQueTblPtr);
static void CanDrv_Init_CanRxTxBufQueMngtTbl(void);
static uint8_t CanDrv_GetAFreeFrmTail_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL * i_pCanDrvBufQueTblPtr,
                                                       uint32_t i_RxCanId,
                                                       uint8_t  i_CanMsgRxLen,
                                                       uint8_t *ip_CanMsgBufPtr);

static uint8_t CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL * i_pCanDrvBufQueTblPtr,
                                                       uint8_t* pub_Channel,
	                                                   uint8_t* pubCanBufIdx,
                                                       uint8_t* o_pCanMsgBufPtr,
                                                       uint8_t* pubCount );

static void CanDrv_PutARxCanMsgFromCanDriverIntoQueue(uint32_t i_RxCanId,
                                                      uint8_t  i_CanMsgRxLen,
                                                      uint8_t* ip_CanMsgBufPtr);

void EcanIntHdl(void);

void InitCAN(void);
void CAN_CfgUDSMail();
uint CosSDOReadFunc(uint func_group, uint addr_in_group,uint * data);
uint FuncOffset(uint func_group, uint addr_in_group);
uint16 ReadAttribute1(uint16 func_addr_offset);
uint16 ValueLessZero1(uint16 para_attr,uint16 func_addr_offset);
uint32 ReadUpForm1(uint16 func_group,uint16 addr_in_group,uint16 func_addr_offset);
uint16 CosSDOWriteFunc(uint16 func_group, uint16 addr_in_group,uint16 ubDataTypeV,uint16 * data);


// USER CODE END


void CanDrv_RxTxMsgPollingMode(void)
{
	CanDrv_RxPhyAddrChlByPollingMode();
	CanDrv_RxFuncAddrChlByPollingMode();
	CanDrv_TxPhyAddrChlConfirmByPollingMode();

#if SDO_EN
	//Sdo_PollingMode();
#endif
}

//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************
void CAN_vInit(void)
{
//	int i;
	asm("  EALLOW");
	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = 1;	//Enable can clock
	
	InitCAN();     // Initialize the eCAN module
	
	CpCoreBaudrate(CP_BAUD_500K);

	CAN_CfgUDSMail();
	CAN_Cfg1939Mail();
	BusOffTime = 0;
	BusOffResetTime = 0;

  	// USER CODE BEGIN (Init,3)
  	CanDrv_Init_CanRxTxBufQueMngtTbl();
  	// USER CODE END
#ifdef SDO_EN 
	InitDici();
#endif
	asm("  EDIS");

	Recindex = 0;
	Recindex2 = 0;			
} //  End of function CAN_vInit

// USER CODE BEGIN (Init,1)
void InitCAN(void)
{

	/* Create a shadow register structure for the CAN control registers. This is
	needed, since only 32-bit access is allowed to these registers. 16-bit access
	to these registers could potentially corrupt the register contents or return
	false data. This is especially true while writing to/reading from a bit
	(or group of bits) among bits 16 - 31 */
	volatile struct ECAN_REGS ECanaShadow;
	
	asm("  EALLOW");
		
	
	// eCAN control registers require 32-bit access. 
	 // If you want to write to a single bit, the compiler may break this
	 // access into a 16-bit access.  One solution, that is presented here,
	 // is to use a shadow register to force the 32-bit access. 
	  
	 // Read the entire register into a shadow register.  This access
	 // will be 32-bits.  Change the desired bit and copy the value back
	 // to the eCAN register with a 32-bit write. 
	
	/* Configure eCAN RX and TX pins for CAN operation using eCAN regs*/
	
	ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
	ECanaShadow.CANTIOC.bit.TXFUNC = 1;
	ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;
	
	ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
	ECanaShadow.CANRIOC.bit.RXFUNC = 1;
	ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;
	
	/* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
	// HECC mode also enables time-stamping feature	
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.SCB = 1;		//ecan mode
	
	//allow auto bus on
	ECanaShadow.CANMC.bit.ABO = 0;
	
	// least significant byte first
	ECanaShadow.CANMC.bit.DBO = 1;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	
	/* Initialize all bits of 'Master Control Field' to zero */
	// Some bits of MSGCTRL register may come up in an unknown state. For proper operation,
	// all bits (including reserved bits) of MSGCTRL must be initialized to zero
	
	ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX31.MSGCTRL.all = 0x00000000;

	
	ECanaMboxes.MBOX0.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX1.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX2.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX3.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX4.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX5.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX6.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX7.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX8.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX9.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX10.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX11.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX12.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX13.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX14.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX15.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX16.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX17.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX18.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX19.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX20.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX21.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX22.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX23.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX24.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX25.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX26.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX27.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX28.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX29.MSGID.all = 0x00000000;	
	ECanaMboxes.MBOX30.MSGID.all = 0x00000000;
	ECanaMboxes.MBOX31.MSGID.all = 0x00000000;
	
		
	// TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
	// as a matter of precaution.
	
	/* Clear all TAn (Transmission-Acknowledge) bits */	
	ECanaRegs.CANTA.all	= 0xFFFFFFFF;
	
	/* Clear all RMPn (Received-Message-Pending) bits */	
	ECanaRegs.CANRMP.all = 0xFFFFFFFF;
	
	/* Clear all interrupt flag bits */	
	ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF1.all = 0xFFFFFFFF;
	
	/*disable mailbox 0~32  overwritten*/
	ECanaRegs.CANOPC.all=0xFFFFFFFF;
	
}

int CpCoreBaudrate(int ubBaudSelV)
{
	
	volatile struct ECAN_REGS ECanaShadow;
		
	//---------------------------------------------------------------#
	// insert hardware dependent code here
	//
    //Disable all can mailbox
	ECanaRegs.CANME.all = 0x00;					 
	
	// Set CCR(Change-configuration request) = 1 
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 1 ;            		
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    // Wait for CCE bit to be  set
	do
	{
		ECanaShadow.CANES.all = ECanaRegs.CANES.all;
	} while(ECanaShadow.CANES.bit.CCE != 1 );
	ECanaShadow.CANES.all = ECanaRegs.CANES.all; 
	
	/* Configure bit timing parameters */
	ECanaShadow.CANBTC.all = 0;
	
	{		
	//60Mhz SYSCLKOUT Sampling Point = 80%
	//TQ = SYSCLKOUT/2/(BRP+1)
	//CANBaud = TQ*(TSEG1REG+TSEG2REG+1+1+1)
		ECanaShadow.CANBTC.bit.BRPREG = 3;				// 500kbps
		ECanaShadow.CANBTC.bit.TSEG2REG = 2;
		ECanaShadow.CANBTC.bit.TSEG1REG = 10;	
	}
	
	ECanaShadow.CANBTC.bit.SJWREG = 2;
	ECanaShadow.CANBTC.bit.SAM = 1;
	ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;
	
    // Set CCR = 0
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 0 ;            		
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
		
	ECanaShadow.CANES.all = ECanaRegs.CANES.all;

	// Wait until the CPU no longer has permission to change the configuration registers
	do
	{
		ECanaShadow.CANES.all = ECanaRegs.CANES.all;
	} while(ECanaShadow.CANES.bit.CCE != 0 ); 		// Wait for CCE bit to be  cleared..

	return 0;
}

// USER CODE END

void CAN_CfgUDSMail()
{	
	uint32 CANMDSET,CANMESET;
	
	CANMDSET = ECanaRegs.CANMD.all;
	CANMESET = ECanaRegs.CANME.all;
	ECanaRegs.CANME.all = 0;
	/* Disable all Mailboxes */
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.

	//RX
	
	ECanaMboxes.MBOX7.MSGID.all  = 0;
	ECanaMboxes.MBOX7.MSGID.bit.STDMSGID = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
	
	ECanaMboxes.MBOX8.MSGID.all  = 0;		
	ECanaMboxes.MBOX8.MSGID.bit.STDMSGID = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
	
	ECanaMboxes.MBOX9.MSGID.all  = 0;		
	ECanaMboxes.MBOX9.MSGID.bit.STDMSGID = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
	
	
	ECanaMboxes.MBOX10.MSGID.all  = 0;		
	ECanaMboxes.MBOX10.MSGID.bit.STDMSGID = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
	
	ECanaMboxes.MBOX11.MSGID.all  = 0;		
	ECanaMboxes.MBOX11.MSGID.bit.STDMSGID = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;

	ECanaMboxes.MBOX15.MSGID.all = 0;	
	ECanaMboxes.MBOX15.MSGID.bit.STDMSGID = SDO_CMD;
	
	
	//TX
	
	ECanaMboxes.MBOX21.MSGID.all  = 0;		
	ECanaMboxes.MBOX21.MSGID.bit.STDMSGID = CANDRV_C_TX_PHY_ADDR_STD_CANMSGID;

	//Only For Bootloader 
	ECanaMboxes.MBOX22.MSGID.all  = 0;		
	ECanaMboxes.MBOX22.MSGID.bit.STDMSGID = CANDRV_C_TX_PHY_ADDR_STD_CANMSGID;



	ECanaMboxes.MBOX24.MSGID.all  = 0;
	ECanaMboxes.MBOX24.MSGID.bit.STDMSGID = 0x200;

	/*ECanaMboxes.MBOX25.MSGID.all  = 0;
	ECanaMboxes.MBOX25.MSGID.bit.STDMSGID = 0x201;*/

	//ECanaMboxes.MBOX26.MSGID.all  = 0;
	//ECanaMboxes.MBOX26.MSGID.bit.STDMSGID = 0x202;
	
	/*ECanaMboxes.MBOX27.MSGID.all  = 0;
	ECanaMboxes.MBOX27.MSGID.bit.STDMSGID = 0x203;*/

	ECanaMboxes.MBOX28.MSGID.all = 0;	
	ECanaMboxes.MBOX28.MSGID.bit.STDMSGID = SDO_RSP; 
	
	
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	
	CANMDSET |=  0x00008F80;
	ECanaRegs.CANMD.all = CANMDSET;

	CANMESET |= 0x1F608F80;
	ECanaRegs.CANME.all = CANMESET;	
}


//****************************************************************************
// @Function      void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function fills the forwarded SW message object with 
//                the content of the chosen HW message object.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see CAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be read (0-127)
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

// USER CODE BEGIN (GetMsgObj,1)

// USER CODE END

void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj)
{
	struct MBOX  *RegPtr=((struct MBOX *)&ECanaMboxes);//Get CAN mailbox beginning address
	volatile Uint32 ShadowReg;
	union CANMSGID_REG     MSGIDData;
	union CANMSGCTRL_REG   MSGCTRLData;
	union CANMDL_REG       MDLData;
	union CANMDH_REG       MDHData;

	
	//if(ubObjNr>=16) return;
	
	ShadowReg=ECanaRegs.CANRMP.all;

	if(ShadowReg&(0x0001L<<ubObjNr))	//have new data
	{
		ECanaRegs.CANRMP.all=(0x0001L<<ubObjNr);
		ShadowReg=ECanaRegs.CANRMP.all;


		//Round to the specific maibox
		RegPtr=RegPtr + ubObjNr;


   		MSGCTRLData.all = RegPtr->MSGCTRL.all;
		if(MSGCTRLData.all == 0)    	MSGCTRLData.all = RegPtr->MSGCTRL.all;

   		MSGIDData.all = RegPtr->MSGID.all;
		if(MSGIDData.all == 0)    	MSGIDData.all = RegPtr->MSGID.all;

   		MDLData.all = RegPtr->MDL.all;
		if(MDLData.all == 0)    	MDLData.all = RegPtr->MDL.all;
	
   		MDHData.all = RegPtr->MDH.all;
		if(MDHData.all == 0)    	MDHData.all = RegPtr->MDH.all;
	

   		//--- set RTR bit if requested------------------------------------
		//if(MSGCTRLData.bit.RTR) CpMacSetRemote(ptsCanMsgT);
   
  		// get DLC
  		pstObj->usMOCfg  =  MSGCTRLData.bit.DLC;
  
		pstObj->ubData[0] = MDLData.byte.BYTE3;
		pstObj->ubData[1] = MDLData.byte.BYTE2;
		pstObj->ubData[2] = MDLData.byte.BYTE1;
		pstObj->ubData[3] = MDLData.byte.BYTE0;
		pstObj->ubData[4] = MDHData.byte.BYTE7;
		pstObj->ubData[5] = MDHData.byte.BYTE6;
		pstObj->ubData[6] = MDHData.byte.BYTE5;
		pstObj->ubData[7] = MDHData.byte.BYTE4;

  		pstObj->usMOCfg  = (pstObj->usMOCfg << 4);    // shift DLC

  		if(MSGIDData.bit.IDE)    // extended identifier
  		{
    		pstObj->uwID     = CpMacGetExtId(MSGIDData.all);
    		pstObj->usMOCfg  = pstObj->usMOCfg | 0x04;  // set IDE
  		}
  		else                                          // standard identifier 
  		{
    		pstObj->uwID    =  MSGIDData.bit.STDMSGID;
  		}
  
	}
}


union CANTRS_REG CANTRS;
//==========================================================
// Function Uint16 CAN_vBusy(Uint16 ubObjNr)
//==========================================================
/*
Uint16 CAN_vBusy(Uint16 ubObjNr)
{
	#if 1


	CANTRS.all = ECanaRegs.CANTRS.all;
	if(CANTRS.all & (0x01L<<ubObjNr)) {		 
		return TRUE;
	}
	else {
		return FALSE;
	}
	#endif
}
*/
//****************************************************************************
// @Function      Uint16 CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          6/18/2014
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

Uint16 CAN_vTransmit(ubyte ubObjNr,uint8_t *data)
{
	union CANTRS_REG CANTRS;
	//union CANTA_REG CANTA;
	struct MBOX  *RegPtr=((struct MBOX *)&ECanaMboxes);
	 RegPtr += ubObjNr;	
	 
	 CANTRS.all=ECanaRegs.CANTRS.all;
	 if(CANTRS.all&(0x01L<<ubObjNr))
	 {		 
		 return FALSE;
	 }
	 else
	 {
	 	RegPtr->MSGCTRL.bit.DLC = 8;
		RegPtr->MDL.byte.BYTE0 = data[3];
		RegPtr->MDL.byte.BYTE1 = data[2];
		RegPtr->MDL.byte.BYTE2 = data[1];
		RegPtr->MDL.byte.BYTE3 = data[0];
		RegPtr->MDH.byte.BYTE4 = data[7];
		RegPtr->MDH.byte.BYTE5 = data[6];	
		RegPtr->MDH.byte.BYTE6 = data[5];
		RegPtr->MDH.byte.BYTE7 = data[4];
		
		//CANTA.all=ECanaRegs.CANTA.all;
		
		//clear transimit acknowledge
		//CANTA.all = ((Uint32)1 << ubObjNr);
		
		//start transmit
		CANTRS.all |= ((Uint32)1 << ubObjNr); 
		
		//ECanaRegs.CANTA.all = CANTA.all;
		ECanaRegs.CANTRS.all=CANTRS.all;

		//
		return TRUE;
	 }
}



// USER CODE BEGIN (CAN_General,10)
uint8_t CanDrv_GetTxMsgFinishedFlag(void)
{
   uint8_t lub_IsConfirmed = rub_ATxMsgIsConfirmed;

   CANDRV_DISABLE_ALL_INTERRUPTS();
       rub_ATxMsgIsConfirmed = FALSE;
   CANDRV_ENABLE_ALL_INTERRUPTS();

   return lub_IsConfirmed;

}



uint8_t CanDrv_TransmitMessageRequest(uint32_t msgId,
                                       uint8_t* pBytes,
                                       uint8_t  numBytes)

{

   uint8_t lub_ReturnCode = FALSE;

   lub_ReturnCode = CanDrv_GetAFreeFrmTail_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr,
                                                            msgId,
                                                            numBytes,
                                                            pBytes);

	CanDrv_GetAReadySendMsgFromBufQueue2Send();
    return lub_ReturnCode;
} /* end of CanDrv_TransmitMessageRequest() */

uint8_t  CanDrv_SendDebugMsg1(uint8_t *i_lup_DatBufToSend)
{
   CAN_vTransmit(25u,i_lup_DatBufToSend); 

   return TRUE;
} /* end of CanDrv_SendDebugMsg1() */

uint8_t  CanDrv_SendDebugMsg2(uint8_t *i_lup_DatBufToSend)
{
  // uint8_t i;
   
   CAN_vTransmit(26u,i_lup_DatBufToSend); 

   return TRUE;



}

uint8_t  CanDrv_SendDebugMsg3(uint8_t *i_lup_DatBufToSend)
{
  // uint8_t i;
   
   CAN_vTransmit(27u,i_lup_DatBufToSend); 

   return TRUE;



}

const uint8_t BootData[] = {0x03,0x7F,0x28,0x78,0xFF,0xFF,0xFF,0xFF};

const uint8_t TimeOutBootData[] = {0x03,0x7F,0x28,0x22,0xFF,0xFF,0xFF,0xFF};

uint8_t  CanDrv_BootLoaderMsg(uint16 x)
{
   
   if(x==0)	
   	{
   		CAN_vTransmit(22u,(uint8_t *)BootData); 
   	}
   	else if(x==1)
   	{
   		CAN_vTransmit(22u,(uint8_t *)TimeOutBootData); 
   	}
    
   return TRUE;
} /* end of CanDrv_SendDebugMsg1() */


static uint8_t CanDrv_GetAReadySendMsgFromBufQueue2Send(void)
{
 //  uint8_t i;
   uint8_t lub_ReturnCode = FALSE;
   // uint8_t lub_CurrUsedIndexFromHead = 0xFFu;
   uint8_t lub_Channel;
   uint8_t lubCanBufIdx;
   uint8_t lubCount;
   uint8_t lub_CanData[0x08u];

   if (TxPhyAddrSemophore != 0x00u)
   {
       //CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr,
       //                                        &lub_Channel,
	   //                                        &lubCanBufIdx,
       //                                        &(lub_CanData[0x00u]),
       //                                        &lubCount );

       return lub_ReturnCode;
   }
   else
   {
   }

   if (rull_CanDrvSendCnfirmCounter >= rull_TpReqSendRspCounter)
   {
       //CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr,
       //                                        &lub_Channel,
	   //                                        &lubCanBufIdx,
       //                                        &(lub_CanData[0x00u]),
       //                                       &lubCount );

       return lub_ReturnCode;
   }
   else
   {
   }
/*
   if (CAN_vBusy(21) == TRUE) 
   {
       lub_ReturnCode = CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr,
                                               &lub_Channel,
	                                           &lubCanBufIdx,
                                               &(lub_CanData[0x00u]),
                                               &lubCount );

		if(lub_ReturnCode == TRUE)
		{
			 CAN_vTransmit(25u,lub_CanData); 
		}
		

       return lub_ReturnCode;
   }
   else
   {
   }*/

   lub_ReturnCode =  CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr,
                                                             &lub_Channel,
	                                                         &lubCanBufIdx,
                                                             &(lub_CanData[0x00u]),
                                                             &lubCount );

   if (lub_ReturnCode == TRUE )
   {
       CANDRV_DISABLE_ALL_INTERRUPTS();
       	
       	
        /*    		   
           for (i = 0x00u; i < 0x08u; i++)
           {
                 CAN_HWOBJ[12u].ubData[i] =  lub_CanData[i];
           }
        */
	   CAN_vTransmit(21u,lub_CanData); 
		
           TxPhyAddrSemophore =0x01u;
		   UDS_APP_ITF_IMP_SET_RELOAD_S3SVR_TMR();
		   
       CANDRV_ENABLE_ALL_INTERRUPTS();
   }
   else
   {

   }

   return lub_ReturnCode;
}


static void CanDrv_Init_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL * i_pCanDrvBufQueTblPtr)
{
   uint8_t i, j;

   CANDRV_DISABLE_ALL_INTERRUPTS();

   i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum   = 0x00u;
   i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex = 0xFFu;
   i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex = 0xFFu;

   for (i = 0x00u; i < CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE; i++)
   {
       i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_IsUsingFlag = FALSE;
       i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_CanId       = 0x00000000u;
       i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_CanDLC      = 0x00u;
       for (j = 0x00u; j < 0x08u; j++)
       {
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_DataBuffer[j] = 0x00u;
       }
   }

   CANDRV_ENABLE_ALL_INTERRUPTS();

}  /* end of CanDrv_Init_CanBufQueMngtTbl() */


static void CanDrv_Init_CanRxTxBufQueMngtTbl(void)
{
    /* to init all of these varaibles */
    rub_PhyAddrRxID = 0x00000000u;                 /* Received message ID */
    rub_PhyAddrRxLENGTH = 0x00u;             /* Recieved message number of data bytes */
    rub_FuncAddrRxID = 0x00000000u;                 /* Received message ID */
    rub_FuncAddrRxLENGTH = 0x00u;             /* Recieved message number of data bytes */
    TxPhyAddrSemophore = 0x00u; // 0xFFu;
    rub_ATxMsgIsConfirmed = FALSE;
    rull_TpReqSendRspCounter = 0u;
    rull_CanDrvSendCnfirmCounter = 0u;
    pul_CanDrvRxBufQueueMngtTblPtr = &rul_CanDrvRxBufQueueMngtTbl;
    pul_CanDrvTxBufQueueMngtTblPtr = &rul_CanDrvTxBufQueueMngtTbl;
    
    CanDrv_Init_CanBufQueMngtTbl(pul_CanDrvRxBufQueueMngtTblPtr);
    CanDrv_Init_CanBufQueMngtTbl(pul_CanDrvTxBufQueueMngtTblPtr);
}


static uint8_t CanDrv_GetAFreeFrmTail_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL  *i_pCanDrvBufQueTblPtr,
                                                       uint32_t                      i_RxCanId,
                                                       uint8_t                       i_CanMsgRxLen,
                                                       uint8_t                      *ip_CanMsgBufPtr)
{
   uint8_t i;
   uint8_t lub_NextFreeIndex = 0xFFu;
   uint8_t lub_ReturnCode = FALSE;

   if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum == CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE)
   {

   }
   else // if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum != CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE)
   {
       if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum == 0x00u )
       {
           CANDRV_DISABLE_ALL_INTERRUPTS();
               i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex = 0x00u;
               i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex = 0x00u;
           CANDRV_ENABLE_ALL_INTERRUPTS();

       }
       else
       {
       }
	   lub_ReturnCode = TRUE;

       CANDRV_DISABLE_ALL_INTERRUPTS();
           rull_TpReqSendRspCounter++;
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex)].m_CanId = i_RxCanId;
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex)].m_CanDLC = i_CanMsgRxLen;
	       for (i = 0x00u; i < 0x08u; i++)
	       {
	           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex)].m_DataBuffer[i] = ip_CanMsgBufPtr[i];
	       }

	       (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum)++;
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex)].m_IsUsingFlag = TRUE;
       CANDRV_ENABLE_ALL_INTERRUPTS();

    // serch a free queue
	if ((i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex + 0x01u) < CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE)
	{
	     for (i = (i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex + 0x01u); i < CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE; i++)
	     {
	         if (i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_IsUsingFlag == FALSE)
		     {
			     lub_NextFreeIndex = i;
		 	     break;
		     }
		     else
		     {
		     }
         }
	 }
	 else
	 {
	 }

	 if (lub_NextFreeIndex == 0xFFu)
	 {
	     for (i = 0x00u; i < i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex; i++)
	     {
	  	    if (i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_IsUsingFlag == FALSE)
		    {
	     	    lub_NextFreeIndex = i;
			    break;
		    }
		    else
	        {
	        }
	     }
     }
	 else
	 {
	 }

	 CANDRV_DISABLE_ALL_INTERRUPTS();
	     (i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex) = lub_NextFreeIndex;
	 CANDRV_ENABLE_ALL_INTERRUPTS();
   }/* end of else if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum != CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE) */

   return lub_ReturnCode;


} /* end of CanDrv_GetAFreeFrmTail_CanBufQueMngtTbl() */


static uint8_t CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(T_CANDRV_BUF_QUEUE_MNGT_TBL * i_pCanDrvBufQueTblPtr,
                                                       uint8_t*                      pub_Channel,
	                                                   uint8_t*                      pubCanBufIdx,
                                                       uint8_t*                      o_pCanMsgBufPtr,
                                                       uint8_t*                      pubCount )
{
   uint8_t i;
   uint8_t lub_NextUsedIndex = 0xFFu;
   uint8_t lub_ReturnCode = FALSE;

   if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum == 0x00u)
   {
   }
   else  // if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum != 0x00u)
   {

	   if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum == 0x01u )
	   {
	       i_pCanDrvBufQueTblPtr->m_CurrQueueTailIndex = 0xFFu;
	   }
       else // if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum != 0x01u )
       {

       }

	   lub_ReturnCode = TRUE;

       CANDRV_DISABLE_ALL_INTERRUPTS();
	       (*pubCanBufIdx)  = (i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex);

           if (i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_CanId == CANDRV_C_RX_PHY_ADDR_STD_CANMSGID)
           {
               (*pub_Channel) = CANDRV_C_RX_PHYSICAL_ADDRESSING;
           }
	       else
	       {
               (*pub_Channel) = CANDRV_C_RX_FUNCTIONAL_ADDRESSING;
	       }
           (*pubCount) = i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_CanDLC;

           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_CanId = 0x00000000u;
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_CanDLC = 0x00u;
           for (i = 0x00u; i < 0x08u; i++)
	       {
	           o_pCanMsgBufPtr[i] =  i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_DataBuffer[i];
	           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_DataBuffer[i] = 0x00u;
	       }

	       (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum)--;
           i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[(i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex)].m_IsUsingFlag = FALSE;
       CANDRV_ENABLE_ALL_INTERRUPTS();

	   if ((i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex + 0x01u) < CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE)
	   {

           for (i = (i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex + 0x01u);
                i < CANDRV_C_MAX_CAN_BUF_RCD_TBL_SIZE;
                i++)
		   {
			    if (i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_IsUsingFlag == TRUE)
			    {
			 	   lub_NextUsedIndex = i;
			 	   break;
			    }
			    else
			    {
			    }
		   }
	    }
	    else
	    {
	    }

		if (lub_NextUsedIndex == 0xFFu)
		{
		   for (i = 0x00u; i < i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex; i++)
		   {
			    if (i_pCanDrvBufQueTblPtr->m_CanBufQueueRcdTbl[i].m_IsUsingFlag == TRUE)
			    {
			 	    lub_NextUsedIndex = i;
			 	    break;
			    }
			    else
			    {
			    }
		   }
		}
		else
		{
		}

		CANDRV_DISABLE_ALL_INTERRUPTS();
		    (i_pCanDrvBufQueTblPtr->m_CurrQueueHeadIndex) = lub_NextUsedIndex;
		CANDRV_ENABLE_ALL_INTERRUPTS();

   } // end of else  // if (i_pCanDrvBufQueTblPtr->m_CurrUsedQueueNum != 0x00u)

   return lub_ReturnCode;


} /* end of CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl() */


static void CanDrv_PutARxCanMsgFromCanDriverIntoQueue(uint32_t i_RxCanId,
                                                      uint8_t  i_CanMsgRxLen,
                                                      uint8_t* ip_CanMsgBufPtr)
{

   CanDrv_GetAFreeFrmTail_CanBufQueMngtTbl(pul_CanDrvRxBufQueueMngtTblPtr,
                                           i_RxCanId,
   	                                       i_CanMsgRxLen,
   	                                       ip_CanMsgBufPtr);


}  /* end of CanDrv_PutARxCanMsgFromCanDriverIntoQueue() */


uint8_t CanDrv_ReadRxCanMsg(uint8_t* pub_Channel,
	                        uint8_t* pubCanBufIdx,
                            uint8_t* pubBuffer,
                            uint8_t* pubCount )
{
   uint8_t lub_ReturnCode = FALSE;
   lub_ReturnCode =  CanDrv_GetAUsedFrmHead_CanBufQueMngtTbl(pul_CanDrvRxBufQueueMngtTblPtr,
                                                             pub_Channel,
	                                                         pubCanBufIdx,
                                                             pubBuffer,
                                                             pubCount);


   return lub_ReturnCode;
} /* end of CanDrv_ReadRxCanMsg() */





void CanDrv_RxPhyAddrChlByPollingMode(void)	//0x7E0
{
        uint8_t lub_IsASpecificDiagReqMsg = FALSE;
		volatile Uint32 ShadowReg;
		uint8_t CanCh;
	
	for(CanCh = 8;CanCh<=11;CanCh++)		//Mail8 - Maill 11
	{
		ShadowReg=ECanaRegs.CANRMP.all;
		if(ShadowReg&(0x0001<<CanCh))	//check is new msg 0x7E0
		{
		//Get new msg from can buffer
          CANDRV_DISABLE_ALL_INTERRUPTS();                
                 CAN_vGetMsgObj(CanCh, &rul_PhyAddrRxCanSwObj);                
                 rub_PhyAddrRxID     = rul_PhyAddrRxCanSwObj.uwID; 
                 rub_PhyAddrRxLENGTH = ((rul_PhyAddrRxCanSwObj.usMOCfg & 0xFFF3u) >> 0x04u);                  
          CANDRV_ENABLE_ALL_INTERRUPTS();
          //check Msg first bye is belong boot sepc msg

		  	if(Recindex>7)	Recindex = 0;
	
			RecData[Recindex++] = rul_PhyAddrRxCanSwObj.ubData[0x00u];	
	
          lub_IsASpecificDiagReqMsg = FblMgr_CheckFblStayInBootSpecificMsg(&(rul_PhyAddrRxCanSwObj.ubData[0x00u]));
          
          if (lub_IsASpecificDiagReqMsg == TRUE)
          {
          }
          else
          {	//put msg to Queue

		  	if(Recindex2>7)	Recindex2 = 0;
	
			RecData2[Recindex++] = rul_PhyAddrRxCanSwObj.ubData[0x00u];
			
               CanDrv_PutARxCanMsgFromCanDriverIntoQueue(rub_PhyAddrRxID, 
                                                rub_PhyAddrRxLENGTH,
                                               &(rul_PhyAddrRxCanSwObj.ubData[0x00u]));
          }	

		  
		  BusOffResetTime = 0;
		  BusOffTime = 0;
		  isUpdateMe = 1;
        }/* end of  if()*/
        else
        {

		}
	}
		
} /* end of CanDrv_RxPhyAddrChlByPollingMode  */

const uint8_t Data3EPos[] = {0x02,0x7E,0x00,0xAA,0xAA,0xAA,0xAA,0xAA};
const uint8_t Data3EErr[] = {0x03,0x7F,0x3E,0x12,0xAA,0xAA,0xAA,0xAA};

void CanDrv_RxFuncAddrChlByPollingMode(void)	//0x7DF
{
	//		uint8_t lub_IsASpecificDiagReqMsg = FALSE;
		  volatile Uint32 ShadowReg;
				  
		  ShadowReg=ECanaRegs.CANRMP.all;
		  if(ShadowReg&(0x0001<<7))   //check is new msg 0x7DF
		  {
		   // Get One Frame CAN data from canbus to rul_FuncAddrRxCanSwObj	  
			CANDRV_DISABLE_ALL_INTERRUPTS();
				  CAN_vGetMsgObj(7u, &rul_FuncAddrRxCanSwObj);
				  rub_FuncAddrRxID	   = rul_FuncAddrRxCanSwObj.uwID;
				  rub_FuncAddrRxLENGTH = ((rul_FuncAddrRxCanSwObj.usMOCfg & 0xFFF3u) >> 0x04u); 		 
			CANDRV_ENABLE_ALL_INTERRUPTS();
			//Save CAN data from rul_FuncAddrRxCanSwObj to rul_CanDrvRxBufQueueMngtTbl(16 frame)
			//(pr is pul_CanDrvRxBufQueueMngtTblPtr)  
			//Next step is TASK(400us)-->FblTp_CyclicTaskEntryPoint()-->FblTp_CheckForRxReq()--->CanDrv_ReadRxCanMsg();
			/*Deal 0x3E */	  
			if((rul_FuncAddrRxCanSwObj.ubData[0x00u] == 0x02) 
				  &&(rul_FuncAddrRxCanSwObj.ubData[0x01u] == 0x3E))   
	
			{
				  if((rul_FuncAddrRxCanSwObj.ubData[0x02u]& 0x7F) == 0u)
				  {
				  
					  FblUds_SimpleSesnMgr_Reload_S3_SeverTimer();
					  if (rul_FuncAddrRxCanSwObj.ubData[0x02u] & 0x80) {
						  //
					  }
					  else {
						  CAN_vTransmit(22u,(uint8_t *)Data3EPos);
					  }
				  }
				  else
				  {
					  //CAN_vTransmit(22u,(uint8_t *)Data3EErr);
				  }
			}
	
			else
			{
			  CanDrv_PutARxCanMsgFromCanDriverIntoQueue(rub_FuncAddrRxID,
																	  rub_FuncAddrRxLENGTH,
																	  &(rul_FuncAddrRxCanSwObj.ubData[0x00u]));
			}
			
			BusOffResetTime = 0;
			BusOffTime = 0;
	
	
		  }/* end of  if(CAN_HWOBJ[8].uwMOCTR & CAN_MOSTAT8_NEWDAT) */
		  else
		  {
		  } /* end of else of  if(CAN_HWOBJ[8].uwMOCTR & CAN_MOSTAT8_NEWDAT) */
		
} /* end of CanDrv_RxFuncAddrChlByPollingMode  */



void CanDrv_TxPhyAddrChlConfirmByPollingMode(void)
{

      uint32_t lul_CanNSR1;

      // USER CODE BEGIN (SRN1,2)

      // USER CODE END


      //   -----------------------------------------------------------------------
      //   Interrupts of CAN node 1
      //   -----------------------------------------------------------------------

      lul_CanNSR1 = ECanaRegs.CANTA.all;

      if (lul_CanNSR1 & 0x00200000u)  // if TXOK
      {
          // Indicates that a message has been transmitted successfully
          // (error free and acknowledged by at least another node).

        	ECanaRegs.CANTA.all |= 0x00200000u;    // reset TXOK

          // USER CODE BEGIN (SRN1_NODE1,7)
   	      CANDRV_DISABLE_ALL_INTERRUPTS();
   	         TxPhyAddrSemophore    = 0x00u; //0xFFu;
   	         rub_ATxMsgIsConfirmed = TRUE;
   	         rull_CanDrvSendCnfirmCounter++;
   	      CANDRV_ENABLE_ALL_INTERRUPTS();

   	      FblTp_NotifyCBForEndOfTxRsp();

   	      CanDrv_GetAReadySendMsgFromBufQueue2Send();

          // USER CODE END
      }

}
