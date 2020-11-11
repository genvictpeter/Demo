
#ifndef CAN_PROTOCAL_H
#define CAN_PROTOCAL_H

#ifdef  CAN_PROTOCAL_DEF_SET
	#define  _CAN_PROTOCAL_DEF_
#else
	#define  _CAN_PROTOCAL_DEF_		extern 
#endif

#define  CANV15			1



#define VCU_0			0x210
#define VCU_2			0x212
#define VCU_4			0x618
#define VCU_7			0x214
#define VCU_8			0x617
#define BMS_0 			0x450
#define MCU_0			0x430
#define MCU_1			0x431
#define MCU_2			0x432
#define MCU_3			0x433
#define MCU_4			0x434
#define MCU_5			0x435
#define MCU_6			0x63F

#define MCU_7			0x6B6
#define MCU_8			0x6B7
#define MCU_9			0x6B8
#define MCU_10			0x6B9
#define MCU_11			0x6BA
#define MCU_12			0x6BB
#define MCU_13			0x6BC
#define MCU_14			0x6BD
#define MCU_15			0x340

#define SDO_CMD			0x105
#define SDO_RSP		    0x115

#define SPORT			0x07
#define ECONOMY			0x06
#define DRIVE			0x04
#define REVERSE			0x03
#define NEUTRAL 		0x02
#define PARK			0x01

#define J1939_MSG_LENGTH	4
#define J1939_DATA_LENGTH	4

union J1939_MESSAGE_UNION {
	struct {
		unsigned int      EXTMSGID_L:16;  // 0:15
		unsigned int      EXTMSGID_H:2;   // 16:17
		unsigned int      STDMSGID:11;    // 18:28  
   		unsigned int      AAM:1;          // 29   
   		unsigned int      AME:1;          // 30
   		unsigned int      IDE:1;          // 31   
		unsigned int 	DataLength:4;
		unsigned int 	RTR:1;
		unsigned int	Res2:3;
		unsigned int	TransmitPriority:5;
		unsigned int	Res3:3;
		unsigned int	Reserved:16;
	 	unsigned int 	Data[J1939_DATA_LENGTH];
	}FormatMsg;
	unsigned long Array[J1939_MSG_LENGTH];
};
typedef union J1939_MESSAGE_UNION J1939_MESSAGE;

struct ERROR1_BITS {   // bits   description               
//----Byte 0---------------------------//
    Uint16 RAM:1;	
    Uint16 ROM:1;	
    Uint16 EEPROM:1;	
    Uint16 RSV3:1;	
	Uint16 VMSLost:1;			
	Uint16 VMSTorqLimit:1;		
    Uint16 RSV6:1;	
	Uint16 VMSTorqErr:1;	

//----Byte 1---------------------------//
    Uint16 SOFT_OC:1;       // 0 
	Uint16 DRVU:1;
	Uint16 Hard_OC:1;
	Uint16 Mul_Soft_OC:1;
    Uint16 Rsv13:1;
	Uint16 Rsv7:1;			//DRV Phase V
	Uint16 Rsv8:1;			//DRV Phase U
    Uint16 ErUCUR:1;	

//----Byte 2---------------------------//
	Uint16 ErVCUR:1;
    Uint16 ErWCUR:1;
    Uint16 Rsv17:5;
	Uint16 CurCheck:1;
	
//----Byte 3---------------------------//
    Uint16 LU:1; 			
	Uint16 OU:1;
    Uint16 RESOLVE:1;       
	Uint16 UdcCheckErr:1;
    Uint16 OverSpeed:1;        
    Uint16 IGBTU_OT:1;	
    Uint16 IGBTV_OT:1;	
    Uint16 IGBTW_OT:1;	
//----Byte 4---------------------------//	
	Uint16 IGBTU_Err:1;		//U phase IGBT Temp Sesor Err
	Uint16 IGBTV_Err:1;		//U phase IGBT Temp Sesor Err
	Uint16 IGBTW_Err:1;		//U phase IGBT Temp Sesor Err
    Uint16 MotorOT:1; 		
    Uint16 PTSensor:1; 		//Motor Pt1000 Sensor Error	
	Uint16 Rsv56:2;			//MCU OT , use IGBT U OT
    Uint16 LU_12V:1;   	

//----Byte 5---------------------------//	
	Uint16 OU_12V:1;
	Uint16 Err_12V:1;
	Uint16 OutVolCheck:1;
	Uint16 Rsv27:5;
	
   
			//4
};

union ERROR1_REG {
    Uint16               all[3];
    struct ERROR1_BITS   bit;
};


_CAN_PROTOCAL_DEF_ union ERROR1_REG	CANError1;
_CAN_PROTOCAL_DEF_ uint16  MCUEnable,CtrlMode,CANDirect,VCUCommand;

#define R_POWER_OFF		1
#define R_DISABLE		2
#define R_ZERO_TORQUE	4
#define R_REDUCE_POWER  5

#ifdef CAN_PROTOCAL_DEF_SET
#define J1939_RX_QUEUE_SIZE	5

unsigned char 					RXHead;
unsigned char 					RXTail;
unsigned char 					RXQueueCount;
J1939_MESSAGE 					RXQueue[J1939_RX_QUEUE_SIZE];


//uint16 WHeatBeat; 
int32 MaxTorqueFilt;
int16 MaxTorque;

#define RC_SUCCESS	1
#define RC_FAIL		0

int16 SendCount0,SendCount1,SendCount2,SendCount3,SendCount4,SendCount5,SendCount6;

int16 Torque;

uint16 TorqLimitCount1,TorqLimitCount2;

#define LIFE_SIGNAL_MAX_VAL                       16
Uint16 LifeSignalClick;




	
int	PumbCustomId;
int CANControlMode;	//1: Torque 2:Speed

int16 SlipQuit_flag;
int16 SlipCut_counter;
int16 SlipQuit_Clear_Counter,SlipCut_timer;

int32   DriveTorqLimit,GenTorqLimit;

uint32  BusOffTime,BusOffResetTime;	
J1939_MESSAGE 					OneMessage;

int Swap(int inputdata);

uint16 Dgns_ID,DgnsR_ID1,DgnsR_ID2,DgnsR_ID3;
uint16 Speed;

uint16 VmsLostDelay;


#endif

union MCU_STATE_UNION {
	struct {
		unsigned int	InitState:1; 			//bit 0 
		unsigned int	State:2;  				//bit 1 -2 
		unsigned int	McuMode:2;				//bit 3 - 4    
   		unsigned int	McuDir:2;          		//bit 5 -6
   		unsigned int	HighVolOK:1;         	//bit 7 
   		unsigned int	Rsv1:2;					//bit 8 -9
   		unsigned int	RequestPowerOff12V:1;	//bit 10
   		unsigned int	Rsv2:1;         		//bit 11
		unsigned int	RequestVCU:4;			//bit 12 -15
	}bit;
	unsigned int  data;
};

typedef union MCU_STATE_UNION MCU_STATE_U;

union Un_CANMotorCmd
{
    struct
    {
        Uint16 MCUEnable:1;				
		Uint16 CtrlMode:3;			
		Uint16 CANDirect:2;		
		Uint16 Rsv1:2;
		Uint16 Rsv2:8;				
    }Bit;
	Uint16 Word;
};

union Un_DriveState
{
    struct
    {
        Uint16 Rsv1:2;				
		Uint16 VcuGearGet:3;			
		Uint16 isBrake:1;		
		Uint16 Rsv2:1;
		Uint16 NoSlide:1;
		Uint16 Rsv3:8;				
    }Bit;
	Uint16 Word;
};


union Un_McuState2
{
	struct {
		//
		Uint16 HighVolOK:1;
   		Uint16 EpWtOk:1;
   		Uint16 PowerOffOk:1;
   		Uint16 RequestPowerOff12V:1;
		Uint16 RequestReducePower:1;
		Uint16 RequestDisable:1;
		Uint16 Rsv1:2;
		//
		Uint16 InitState:1;
		Uint16 State:2;
		Uint16 McuMode:3;
   		Uint16 McuDir:2;
	}Bit;
	Uint16 Word;
};


_CAN_PROTOCAL_DEF_ int32   CANTorq,CANSpeed,CANTorqReal,CANTorqErr;
_CAN_PROTOCAL_DEF_ int16 InvStatus;
_CAN_PROTOCAL_DEF_ int16 BUS_CMD;
_CAN_PROTOCAL_DEF_ int16 CANCtrlMode,CANCtrlModeBak;
_CAN_PROTOCAL_DEF_ uint16 VcuGearGet,Gear,NoSlide,GeraErr,VmsState,isBrake;
_CAN_PROTOCAL_DEF_ uint16 CANProtocol,LostCount,CANErrorUpdate;
	
_CAN_PROTOCAL_DEF_ int CANRequestFreq,CANRequestTorque,CANRequestTorque1;
_CAN_PROTOCAL_DEF_ MCU_STATE_U  McuState;

_CAN_PROTOCAL_DEF_ union Un_CANMotorCmd CANMotorCmd;
_CAN_PROTOCAL_DEF_ union Un_DriveState DriveState;

/*-------------------------------------------------------------------*/
/*!
** \def  CP_MASK_EXT_FRAME
**
** Mask for extended frame (29 bits)
*/
#define  	CP_MASK_EXT_FRAME 0x1FFFFFFF

#define  	CpMacGetExtId(MSG_PTR)           (MSG_PTR)&CP_MASK_EXT_FRAME

#define		COM_OVERTIME		Funcode.CANOverTime.value


#define 	INV_NULL		0
#define		INV_12V_ON		1
#define     SEFT_TEST_OK	2
#define     DCBUS_TEST_OK	3
#define 	INV_12V_OFF		4

#define 	NEW_PROTOCOL	0
#define		OLD_PROTOCOL	1

_CAN_PROTOCAL_DEF_ void J1939_Initialization();
_CAN_PROTOCAL_DEF_ void J1939_Poll(unsigned int ElapsedTime);
_CAN_PROTOCAL_DEF_ void EcanIntHdl(void);
_CAN_PROTOCAL_DEF_ void  EnNormComTx();
_CAN_PROTOCAL_DEF_ void  DisNormComTx();
_CAN_PROTOCAL_DEF_ void Diagnosis_poll( unsigned int ElapsedTime );
_CAN_PROTOCAL_DEF_ uint8_t CheckProgramCondition();
_CAN_PROTOCAL_DEF_ void Anti_Slip( unsigned int ElapsedTime1 ) ; 


#endif  

