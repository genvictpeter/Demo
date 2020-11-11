

#ifndef _RTW_HEADER_SPEEDFUNC_h_
#define _RTW_HEADER_SPEEDFUNC_h_

#ifdef  _SPEEDFUNC_DEF_H_
#define  _SPEEDFUNC_DEF             
#else
#define  _SPEEDFUNC_DEF 	extern  		 
#endif

//===========================================================================
/* 加减速标志 */
typedef struct 
{
	unsigned int   SetFreqShiftR:2; 	// 0~1	设定频率定标
	unsigned int   FreqSetChg:1; 		// 2	设定频率更改
	unsigned int   AccTimeChg:1;		// 3	加速时间更改
	unsigned int   DecTimeChg:1;		// 4	减速时间更改
	unsigned int   FWD2REVSwitchIsOn:1;	// 5	zheng反转切换中
	unsigned int   rsvd:10; 		// 6~15	Reserved
}S_AccDecFlag;
	
/* all & bit access */
typedef union  
{
	unsigned short     all;
	S_AccDecFlag bit;
}U_AccDecFlag;


typedef struct 
{
	int32	InitOutput;
	int32	CurrentOutput;
	int32	SetTarget;
	int32	SetTargetBak;
	int32	AccFreq1;
	int32	AccFreq2;
    int32	JerkOutStart;
    int32	JerkOutEnd;
	int32	CurrentJerk;
	int16	AccMax;
	int16	CurrentAccMax;
	int16	JerkStart;
	int16	JerkEnd;
	int16	CurrentAcc;
	int16	InitAcc;
	int16	Acc3Tar;
	uint16	is_SCurve; 
	uint16  STimer;	
	uint16	is_AccStep;	
}S_SCurve;


_SPEEDFUNC_DEF   Uint32	FreqRef;	// 设定频率，不含方向		[0 ~ 3000.00]


_SPEEDFUNC_DEF  void FuncManage_L1ms_Init_Speed(void);
_SPEEDFUNC_DEF  void FuncManage_MakeSetFreq();
_SPEEDFUNC_DEF  int16 FuncManage_SPEED(void );
_SPEEDFUNC_DEF  void FuncManage_exit_internal_SPEED(void );
_SPEEDFUNC_DEF  void FuncManage_enter_internal_SPEED(Uint16 FromTorq);
_SPEEDFUNC_DEF  void FuncManage_GetCurrFreq(void);
_SPEEDFUNC_DEF  void FuncManage_MakeFreq(void);

#endif  

