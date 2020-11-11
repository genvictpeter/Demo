#ifndef DSP2802x_MV180CTRL_H
#define DSP2802x_MV180CTRL_H

/*******************************************************************************************/
#ifdef  _MV180CTRL_H_
#define  _MV180CTRL_DEF_               
#else
#define  _MV180CTRL_DEF_		extern 
#endif


#ifdef _MV180CTRL_H_

#define CurAD_ZERO		2110
typedef struct{
	long l;		//=0可见 =1不可见
	long h;
} DOUBLELONG;

extern long DV32_16(long,long);
extern int DV32_32(unsigned long,unsigned long);
extern long DV48_32(long,unsigned long);
extern unsigned long  UDV48_32(unsigned long,unsigned long);
extern long MP32_32(long,long);
extern long DV3232_32(long,unsigned long,unsigned long);
extern void DV64_32(DOUBLELONG *,long,unsigned long,unsigned long);
extern void KeyBoard_Init(void);

void RunInitial(void);


void CalCurrentAdResult(void);
void CalVolAdResult(void);
void FaultReset(void);
void PowerStep();

void HardwareFault(void);

void CurrentZeroDrift(void);
int CalSin(int);
int CalSin2(int);

unsigned long MotorFn;

unsigned int ItRefLim;

unsigned int SpeedFedTorque;
long IwErrorAcc,IvErrorAcc,IuErrorAcc;

int Udc,Udc1;    //    母线电压
int ConVdc15v,ConVdc;
int RE_ATEXC;    //实测旋变励磁幅值


long ItFedFltAcc,ImFedFltAcc;
int Isa,Isb,Iu2;
int	Iv1,Iw1,Iu1;
unsigned int IvErrorK,IwErrorK,IuErrorK;


int	Thta;
int	Sina,Cosa;
int	ImFed,ItFed,ItRef;
long ImFedFlt,ItFedFlt;
int	ItError,ImError;
int	UmRef,UtRef,UtOut;
long IfedAcc;

unsigned int MotorVoltage,InverterVoltage;
int Umag,Imag,ImagRms;


unsigned int MotorCurrent;
  
   

long SpeedLedAcc;
unsigned int Ubase,Ibase,Zb,Lb,Ulbase;

unsigned int InverterCurrent;

unsigned int ImReal;
unsigned long MotorRatedSpeed;
long Fn,Fb;


int IwError,IvError,IuError;
long IuErrorAcc,IvErrorAcc,IwErrorAcc;






int IuSample;
int IvSample;
int IwSample;

int UdcSample;

int AbsSpeedFed;


int SpeedRef,SpeedRef1,SpeedFed,SpeedError;

int AbsSpeedRef;

unsigned int CurrentZeroCount;



#else


#endif

typedef struct{

	int AI1;
	int AI2;
	int NTCU;
	int NTCV;
	int NTCW;	
	int KTY;
}AI_Sam_t;

_MV180CTRL_DEF_ interrupt void SinCosSamplePoint(void);
_MV180CTRL_DEF_ interrupt void CurrentSamplePoint(void);

_MV180CTRL_DEF_ interrupt void OverCurrent(void);
//_MV180CTRL_DEF_ interrupt void ADC_INT1_ISR(void);  // AdPoint, test only
//_MV180CTRL_DEF_ interrupt void ADC_INT2_ISR(void);  // AdPoint, test only
_MV180CTRL_DEF_ interrupt void Epwm7Int_isr(void);

_MV180CTRL_DEF_  void CtrlInit();
_MV180CTRL_DEF_ void InitMem(void);


_MV180CTRL_DEF_ void CalFuncPara(void);
_MV180CTRL_DEF_ void SoftFaultReset(void);
_MV180CTRL_DEF_ void CalMotorParameter(void);
_MV180CTRL_DEF_ void CalParameter(void);
_MV180CTRL_DEF_  void SetSwitchFreq(void); 
_MV180CTRL_DEF_ void ForceTZ(void);

_MV180CTRL_DEF_ void VcoRad(long *pAgl, long f);

_MV180CTRL_DEF_ long Fb;

_MV180CTRL_DEF_ int Iw,Iv,Iu;
_MV180CTRL_DEF_ long SumI;


_MV180CTRL_DEF_ unsigned int  RunStep;        
_MV180CTRL_DEF_ unsigned int  RunStepOld;   
                 
_MV180CTRL_DEF_ int	CurrentFedFlt,CvdFlt,IFedOc;
_MV180CTRL_DEF_ int UdcFlt,ConVdcFlt,Udc1Flt;
_MV180CTRL_DEF_ unsigned long MotorRatedFreq,MotorRatedRotorFreq,MotorRatedTorque;

_MV180CTRL_DEF_ int ImRef,ImRefn,MotorNp,MotorNps;

_MV180CTRL_DEF_ long rlSpeedFed;
_MV180CTRL_DEF_ long rlSvcSpeedFed;


_MV180CTRL_DEF_  AI_Sam_t AI_Sample;
_MV180CTRL_DEF_  long lSpeedRef,lSpeedFed;
_MV180CTRL_DEF_  int DisPr4,DisPr3,EnableDischarge,ChargeClock,Sliding;

#endif

