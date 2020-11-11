#ifndef ERROR_H
#define ERROR_H

#include "main.h"

/*******************************************************************************************/
#ifdef  _ERROR_DEF_H_
#define  _ERROR_DEF             
#else
#define  _ERROR_DEF 	extern  		 
#endif

#define	I2T_MOTOR_TEMP_ACTIVE	1
#define HIWORD(x)	(x>>16) 
#define	MOTOR_MODE_COOLINGTYPE 			0x01
#define	MOTOR_MODE_TEMP_EVALUATION_ON	0x010

#define MAX_LOG			0x06

#define RESOLVER		0

#define MAX_SOFT_OC		5

#define SumIMaxErr      1000


//**********	IGBT ???			**********
#define IXT_100		0x2000   			//  i*t???100%, in Q13
#define IXT_95		0x1E66  			//  i*t?95%, in Q13



typedef enum {
	ErrNONE	 	 = 0x00,	
	ErDrv	 	 = 0x01,			
	EroSoftOC	 = 0x02,		
	EroHardOC	 = 0x03,		
	Er12V		 = 0x04,		
	Er12H		 = 0x05,		
	Er12L		 = 0x06,        
	ErCurU		 = 0x07,
	ErCurV       = 0x08,	
	ErCurW		 = 0x09,		
	ErEEPROM	 = 0x0A,	
	EroOU1		 = 0x0B,		
	ErLU		 = 0x0C,		
	ErMCUOH		 = 0x0D,	
	ErPG1		 = 0x0E,
	ErCurCheck	 = 0x0F, 	
	ErEFT		 = 0x10,		
	ErTune		 = 0x11,     
	ErParaSET	 = 0x12,
	ErVdcCheck   = 0x13,
    ErMulOC		 = 0x14,
    ErOutVolCheck= 0x15,
	ErCurU1		 = 0x16,
	ErCurV1      = 0x17,	
	ErCurW1		 = 0x18, 	
	AlU_OT		 = 0x0101,
	AlV_OT		 = 0x0102,
	AlW_OT		 = 0x0103,
	AlVMSLost	 =	0x0104,
	AlVMSTorqLimit =0x0105,
	AlOvSpeed	   = 0x0106,
	AlMotorOT	   = 0x0107,
	WlIGBTSensor  = 0x0201,
	WlIGBTVSensor  = 0x0202,
	WlIGBTWSensor  = 0x0203,
	WlPTSensor    = 0x0204,
	WlVMSTorqErr  = 0x205		  
  } ErrorStates;

typedef struct  {Uint16 ErrorListBit;ErrorStates KeyCode;int16 EpAdr;Uint32 UDSNumber;} ErrorInfo_s;

#define ErrorInfo_Size	25

#ifdef _ERROR_DEF_H_

// 注意修改如下表格后，一定要修改 SupportedDtcTbl
const ErrorInfo_s ErrorInfo[]={
								0,			ErrNONE,	 	  0,		0x00000000,					
								1,			ErDrv,			  1, 		0x00116016,			 
								2,			EroSoftOC,		  2, 		0x00113519,
								3,			EroHardOC,		  3,	    0x00116116,
								4,			ErrNONE,		  0,		0x00000000,
								5,			Er12H,		   	  4,		0x00F00317,
								6,			Er12L,      	  5,		0x00F00316,
								7,			ErCurU,			  6,		0x00118A28,	
								8,			ErCurV, 		  7,		0x00118B28, 																
								9,			ErCurW,			  8,		0x00118C28,								
								10,			ErEEPROM,		  9,		0x00062F46,
								11,			EroOU1,			 10,		0x00114017,								
								12,			ErLU,			 11, 		0x00114016,								
								13,			ErMCUOH,		  0, 		0x00000000,			//MCU-OH not save in uds.														
								14,			ErPG1,			 12, 		0x000A3F00,
								15,			ErCurCheck,		 13,		0x00112164,	
								16,			ErEFT,		   	  0,		0x00000000,
								17,			ErTune,     	  0,		0x00000000,
								18,			ErParaSET,		  0,		0x00000000,
								19,		    ErVdcCheck,		 14,		0x0011841C,
								20,         ErMulOC,         15,        0x00116216,
								21,         ErOutVolCheck,   16,        0x000A0A94,
								22,         ErCurU1,         17,        0x00118A12,		
	                            23,         ErCurV1,         18,        0x00118B12,
	                            24,         ErCurW1,		 19,        0x00118C12,	                            
								};

const ErrorInfo_s AlarmInfo[]={
								0,			ErrNONE,		  0,			0x00000000,		
								1,			AlU_OT,			  20,			0x00117098,	
								2,			AlV_OT,			  21,			0x00117198,
								3,			AlW_OT,			  22,			0x00117298,
								4,			AlVMSLost,		  23,	 		0x00C10087,			
								5,			AlVMSTorqLimit,	  24,	 		0x00C40186,			
								6,			AlOvSpeed,        25,			0x000A4400,
								7,			AlMotorOT,		  26,			0x000A2F98,
								8,			ErrNONE,		  0,			0x00000000,								
								9,			ErrNONE,		  0,			0x00000000,
								10,			ErrNONE,		  0,			0x00000000,
								11,			ErrNONE,		  0,			0x00000000,								
								12,			ErrNONE,		  0,	 		0x00000000,								
								13,			ErrNONE,		  0,	 		0x00000000,															
								14,			ErrNONE,		  0,	 		0x00000000,								
								15,			ErrNONE,		  0,	 		0x00000000,																																		
								};

const ErrorInfo_s WarnInfo[]={
								0,			ErrNONE,	  	  0,			0x00000000,			//IGBTTempSensor			
								1,			WlIGBTSensor,	  27,	 		0x0011801C,	
								2,			WlIGBTVSensor,	  28,	 		0x0011811C,	
								3,			WlIGBTWSensor,	  29,	 		0x0011821C,	
								4,			WlPTSensor,		  30,	 		0x000A001C,			
								5,			WlVMSTorqErr,  	  31,	 		0x00113064,			
								6,			ErrNONE,	  	  0,	 		0x00000000,			//Waring EEP not save in EEPROM		
								7,			ErrNONE,	      0,			0x00000000,
								8,			ErrNONE,          0,			0x00000000,
								9,			ErrNONE,	      0,			0x00000000,		
								10,			ErrNONE,	      0,			0x00000000,								
								11,			ErrNONE,	      0,			0x00000000,
								12,			ErrNONE,	      0,			0x00000000,								
								13,			ErrNONE,		  0,	 		0x00000000,								
								14,			ErrNONE,		  0,	 		0x00000000,															
								15,			ErrNONE,		  0,	 		0x00000000,																																			
								};	
#endif

struct ERROR_BITS {   		// bits   description               
	Uint16 RsvNone:1;		//0 
    Uint16 DRV:1; 			//   1        
    Uint16 Soft_OC:1; 		//   2
    Uint16 Hard_OC:1;		//   3
	Uint16 Rsv2:1;			//   4
    Uint16 Over12V:1; 		//   5	
	Uint16 Low12V:1;		//  6		
	Uint16 CurU:1;			//  7
	Uint16 CurV:1;			//  8	
	Uint16 CurW:1;			//  9 
	Uint16 EEP:1;			//  10
    Uint16 OU:1;       		// 11
    Uint16 LU:1;       		// 12    
    Uint16 MCUOH:1;       	// 13     
    Uint16 PGSignal:1;      // 14
    Uint16 CurCheck:1;		// 15
    Uint16 EFT:1;       	// 16   
    Uint16 Tune:1;       	// 17
    Uint16 ParaSet:1;		// 18
    Uint16 VdcCheck:1;		// 19
    Uint16 Mul_Soft_OC:1;	// 20
    Uint16 OutVolCheck:1;	//  21 
	Uint16 CurU1:1;			//  22
	Uint16 CurV1:1;			//  23	
	Uint16 CurW1:1;			//  24 	
	Uint16 Rsv18:7;		   //  25 - 31
};

union ERROR_REG {
    Uint32              all;
    struct ERROR_BITS   bit;
};





struct ALARM1_BITS {   		// bits   description               
	Uint16 RsvNone:1;			//1----  Resever
    Uint16 U_OT:1;      		//2----- IGBT Over 90 degree
    Uint16 V_OT:1;      		//2----- IGBT Over 90 degree
    Uint16 W_OT:1;      		//2----- IGBT Over 90 degree
	Uint16 VMSLost:1;			//3--No Clear  .Power Reset
    Uint16 VMSTorqLimit:1; 		//4--No Clear  .Power Reset				
	Uint16 OvSpeed:1;			//5	Auto Clear
	Uint16 MotorOT:1;			//6--  Auto Clear		
	Uint16 Rsv7:8;				//9 --- 15
};

union ALARM1_REG {
    Uint16                      all;
    struct ALARM1_BITS   bit;
};



struct WARNING_BITS {   		// bits   description               

    Uint16 Rsv1:1;    				//0   		//  3 channel all error   
	Uint16 IGBTTempSensor:1;			//1
    Uint16 IGBTVTempSensor:1;
	Uint16 IGBTWTempSensor:1;
	Uint16 PTSensor:1;			//2
	Uint16 VMSTorqErr:1;			// No Clear , Power Reset	//3	
    Uint16 EEp:1;
	Uint16 Rsv11:9;//4
};

union WARNING_REG {
    Uint16                      all;
    struct WARNING_BITS   bit;
};



struct TEST_WARNING_BITS {   		// bits   description               

    Uint16 Rsv1:1;    //0   		//  3 channel all error   
	Uint16 Rsv2:1;			//1
	Uint16 Rsv3:1;			//2
	Uint16 Rsv4:1;		//3	
    Uint16 Rsv5:1;       		//4
    Uint16 IGBTUShort:1;        //5
    Uint16 IGBTVShort:1; 		//6 
	Uint16 IGBTWShort:1;		//7
	Uint16 IGBTUOPEN:1;			//8
    Uint16 IGBTVOPEN:1; 		//9
	Uint16 IGBTWOPEN:1;			//10
    Uint16 RSV11:1;       		//11
    Uint16 RSV12:1;          	//12
    Uint16 RSV13:1;      		//13
    Uint16 PTOPEN:1;       		//14
    Uint16 PTShort:1;       		//15
};

union TEST_WARNING_REG {
    Uint16                      all;
    struct TEST_WARNING_BITS   bit;
};




typedef struct
{
	Uint16  ErrorCode;          
	Uint16	ErrDCVoltage;	//-5
	Uint16  ErrMCUState;	//--3/
	Uint8 	ErrMotorModeCmd;      //-1
	Uint8 	ErrDriveState; 	// 2    
	Uint16	ErrTorqueCmd;   //--7 
	Uint16	ErrTorqueFed;   //---9 
	Uint16	ErrSpeedSet;		//8      
	Uint16	ErrSpeed;       //10 
	Uint8 	ErrIGBTTemp;     //11 - 13 
	Uint8 	ErrMotorTemp;    // 15
	Uint16	ErrUd; 			//20          
	Uint16	ErrUq;			//21            
	Uint16	ErrIdRef;       //16  
	Uint16	ErrIqRef;       //17  
	Uint16	ErrIdFed;       //18  
	Uint16	ErrIqFed;       //19  
	Uint16	ErrState;		////--4
	Uint8 	Err12V;  		//24
	Uint8   Angle;			//22
	Uint8   AngleInit;		//23
	Uint8	ErrMCUTemp;			
	Uint16  DC_Cur;
	//Uint32	ErrState;
}t_ErrorLog;


typedef union  {
   Uint16       U16Data[sizeof(t_ErrorLog)];
   t_ErrorLog	ErrLog;
}ErrorLog_t;



_ERROR_DEF	uint16 		FlagSaveErr,SoftOCCount;
_ERROR_DEF  ErrorLog_t	ErrLog[MAX_LOG];
_ERROR_DEF  int16 		SpeedRpm;
_ERROR_DEF  void Init_Error(void);
_ERROR_DEF ErrorLog_t	ErrSubmit;

_ERROR_DEF union ERROR_REG	ErrorList;
_ERROR_DEF union ALARM1_REG	AlarmCode,AlarmCodeBak;
_ERROR_DEF union WARNING_REG	WarningCode,WarningCodeBak;

_ERROR_DEF union  TEST_WARNING_REG	TestWarn;

_ERROR_DEF	uint16 PowerIsOK,ConPowerIsOK;


_ERROR_DEF  void FuncManage_Error(void);
_ERROR_DEF  void FuncManage_ResetErr(void );
_ERROR_DEF  void FuncManage_RecordErr(void);

_ERROR_DEF  Uint16 GetErrorCode();
_ERROR_DEF  Uint16 isAlarmWarn();


_ERROR_DEF  void SetError(ErrorStates Code);

//_ERROR_DEF void FuncManage_JdgOCTimes(void );


_ERROR_DEF  void Calc_LpIxtIGBT ( void );
_ERROR_DEF  void LT_It_handlePt1(void);
_ERROR_DEF uint16  GetErrInfo();
_ERROR_DEF void ResolverSignalCheck();
_ERROR_DEF void ResolverSignal();

_ERROR_DEF void Detect_Alaram(void);

_ERROR_DEF void GetDataFlowInfo(void);
_ERROR_DEF uint16 Get_Error_Adr(uint16 ErrNo);

_ERROR_DEF void Asert_Alarm_Warn();

_ERROR_DEF void CopyLogToFuncode(ErrorLog_t *Err);
_ERROR_DEF void TorqErrCheck(void);
_ERROR_DEF void VdcSensorCheck(void);
_ERROR_DEF void HighVolOutCheck(void);

_ERROR_DEF uint16	PG1Count,PG2Count,PG2ErrCount;

#ifdef _ERROR_DEF_H_


//int16 OCTimes;	//??????
//Uint16 OcTimer;


//Uint16 FORstTimer;
//Uint32 OCRstTimer;

Uint16 UTempLinetime,VTempLinetime,WTempLinetime,MotorTempLineTime,MotorTempLineOKTime;
unsigned short MotorTempFilterLo;

uint16 OvSpeedTime;
uint16 DelayLow12V,DelayOv12V,LuDetectCount,TorqErrCount;
int16  SpeedRpm,RevLimit;


uint16 LogWrite,LogRead;
ErrorStates ErrorCode1,ErrorCode,ErrorCodeBak;  

extern long CANTorqRealDis;

uint16 ErrorListIndex;

void HardwareFault(void);
void FuncManage_AssertErr(void );
void FuncManage_DetectErr(void );
void FuncManage_ExFaultDetect(void);
static void FuncManage_PowerDetect(void );
static void FuncManage_OtDetect(void);

static void TempLineOpenDetect(void);
static void AutoOverSpeedDetect();
static void ResolverCheck();
static void FuncManage_TuneDetect();
static void PushErrInfo(uint16  Code);

void Detect_Warn(void);
void Asert_Alarm_Warn(void);

void Error_ErrClass();
uint16 GetErrBuffer();


extern unsigned long divu64d32 (unsigned long factor1, unsigned long factor2, unsigned long divisor);
extern Uint16 divu16 (Uint32 dividend32, Uint16 divisor16); 
extern Uint32 mulu32 (Uint16 factor1, Uint16 factor2); // ???16??16?,??32????

#endif

#endif

