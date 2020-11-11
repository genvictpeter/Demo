#ifndef _KEYBOARDEX_H_
#define _KEYBOARDEX_H_

/*******************************************************************************************/
#ifdef  _KEYBOARDEX_
#define  _KEYBOARDEX_DEF_
#else
#define  _KEYBOARDEX_DEF_		extern 
#endif

	/*typedef		unsigned int 	uint;
	typedef		short 		int16;
	typedef		unsigned short  uint16;
	typedef		long		int32;
	typedef		unsigned long  	uint32;*/

/*******************************************************************************************/
/*私有变量*/

#ifdef  _KEYBOARDEX_
#endif

/*******************************************************************************************/

/*共享变量*/
	
	/*Para显示属性*/	
	typedef struct{
		uint ignore:1;		//=0可见 =1不可见
		uint modify:1;		//=0不可改写 =1可改写
		uint scal:3;		//小shu点位置   =0无  =1 =2 =3/1,2,3位
		uint unit:3;		//单位 H=1 A=2 V=3 R=4 M=5
		uint sign:1;		//=1 负
		uint flicker:1;		//=1 闪烁
		uint bhex:1;		//=1 16进制
		uint rsv:5;		//保留
		uint32 value;		//功能码值
	}DataDisplayBits;


	_KEYBOARDEX_DEF_	DataDisplayBits *SDfirstip;		//停机data初始指针
	_KEYBOARDEX_DEF_	DataDisplayBits *SDfuncip;		//停机data当前指针
	_KEYBOARDEX_DEF_	DataDisplayBits *RDfirstip;		//运行data初始指针
	_KEYBOARDEX_DEF_	DataDisplayBits *RDfuncip;		//运行data当前指针
	_KEYBOARDEX_DEF_	DataDisplayBits *RSfuncip;		//临时指针

	typedef struct	{
		DataDisplayBits SDFreqRef;		//SD00
		DataDisplayBits SDOutSpd;		//SD01
		DataDisplayBits SDSpdRef;		//SD02
		DataDisplayBits SDDCVolt;		//SD03
		DataDisplayBits SDOutLSpd;		//SD04
		DataDisplayBits SDLSpdRef;		//SD05
		DataDisplayBits SDPIDFB;		//SD06
		DataDisplayBits SDPIDRef;		//SD07
		DataDisplayBits SDAI1Volt;		//SD08
		DataDisplayBits SDAI2Volt;		//SD09
		DataDisplayBits SDAI3Volt;		//SD10
		DataDisplayBits SDDITermSts;		//SD11
	}sStopData;
	_KEYBOARDEX_DEF_	sStopData StopData;

	typedef struct	{
		DataDisplayBits RDOutFreq;		//RD00
		DataDisplayBits RDFreqRef;              //RD01
		DataDisplayBits RDOutCurr;              //RD02
		DataDisplayBits RDOutSpd;               //RD03
		DataDisplayBits RDSpdRef;               //RD04
		DataDisplayBits RDOutLSpd;              //RD05
		DataDisplayBits RDLSpdRef;              //RD06
		DataDisplayBits RDOutPower;             //RD07
		DataDisplayBits RDOutTorq;              //RD08
		DataDisplayBits RDOutVolt;              //RD09
		DataDisplayBits RDAI1Volt;              //RD10
		DataDisplayBits RDAI2Volt;              //RD11
		DataDisplayBits RDAI3Volt;		//RD12
		DataDisplayBits RDPIDFB;                //RD13
		DataDisplayBits RDPIDRef;               //RD14
		DataDisplayBits RDDITermSts;            //RD15
		DataDisplayBits RDDCVolt;               //RD16
	}sRunData;
	_KEYBOARDEX_DEF_	sRunData RunData;
/*******************************************************************************************/

	_KEYBOARDEX_DEF_	uint16 KeyValue;	//键盘下发键值
							//Bit0	ENTER
							//Bit1	PANEL
							//Bit2	SHIFT
							//Bit3	UP
							//Bit4	JOG
							//Bit5	RUN
							//Bit6	DOWN
							//Bit7	STOP
							//Bit8	MENU/ESC
							
	_KEYBOARDEX_DEF_	uint16 curRunData;	//当前显示运行Para
	_KEYBOARDEX_DEF_	uint16 curStopData;	//当前显示停机Para
	_KEYBOARDEX_DEF_	uint16 LEDSeg[5];	//LED笔段码
	_KEYBOARDEX_DEF_	uint16 LCDSeg[4][21];
	_KEYBOARDEX_DEF_ 	uint16 M1Polars,M2Polars;
	/* 键盘Para*/
	typedef struct
	{
		uint bUserLock:1;			//=1 设定了用户密码
		uint bFactoryLock:1;			//=1 厂家密码锁定生效
		uint bKeyLock:1;			//=1 键盘锁定中
		uint bErr:1;				//=1 有故障
		uint bErrFlag:1;			//=1 故障已触发 
		uint bParaInit:1;			//=1 恢复出厂para
		uint bLongTimeUp:1;			//=1 长时间Up
		uint bLongTimeDn:1;			//=1 长时间Down
		uint bParaUpload:1;			//=1 Para上载中
		uint bParaDnload:1;			//=1 Para下载中
		uint bPartDnload:1;			//=1 Para 下载，except电机para
		uint bParaDnOK:1;			//=1 Para 下载结束
		uint bParaCopyEnd:1;		//=1 Para 拷贝结束
		uint bTestMode:1;			//=1 in test mode 
		uint bAlarm:1;
		uint bMotorSwitch:1;			//=1 term func 88 select  2007.4.5 add
	}sKeyBoardPara;
	_KEYBOARDEX_DEF_	sKeyBoardPara uKeyPara;
	
	typedef struct
	{
		uint bFuncDebugLock:1;//调试功能码密码标志
		uint resv:15;
	}sKeyBoardPara1;
	_KEYBOARDEX_DEF_	sKeyBoardPara1 uKeyPara1;
	/* LED灯*/
	typedef struct
	{
		uint bUnitH:1;			
		uint bUnitA:1;
		uint bUnitV:1;
		uint bUnitR:1;
		uint bUnitM:1;
		uint Rsv0507:3;
		uint bDirFWD:1;
		uint bDirREV:1;
		uint bMenuQuick:1;
		uint bMenuBasic:1;
		uint bAlarm:1;
		uint bRun:1;
		uint bPanel:1;
		uint btest:1;
	}sLEDLight;				//0亮1灭
	
	typedef union  
	{
		uint16     all;
		sLEDLight bit;
	}LEDLight;
	_KEYBOARDEX_DEF_	LEDLight unnLEDLight;
/*******************************************************************************************/
/*Function声明*/
	_KEYBOARDEX_DEF_	void KBMange_step(void);
/*******************************************************************************************/
#endif	                         
