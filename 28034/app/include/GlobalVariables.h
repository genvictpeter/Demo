/***************************************************************************
  Name:         GlobalVariables.h
****************************************************************************/

#ifndef _GLOBAL_VARIABLES_H_
#define _GLOBAL_VARIABLES_H_

/*******************************************************************************************/
#ifdef  _FunctionManage_H_
#define  _VARIABLESEX_DEF_               
#else
#define  _VARIABLESEX_DEF_		extern 
#endif

/* 运行命令1－－bit fields  */
typedef struct
{
// 键盘RUN/JOG命令为电平触发，由键盘程序将相应的位置位/复位，进行起停控制。
// 其他键盘命令为上XX沿触发，由键盘程序将相应的位置位，但由功能程序在响应命令后复位。    
	unsigned int   KBRun:1; 		// 0	键盘运行：1－运行；0－停机       
	unsigned int   KBJog:1;   	        // 1	键盘JOG：1－JOG运行；0－JOG停机  
				        	//	键盘RUN/JOG运行时方向取自F05.01
				        	
	unsigned int   KBFreeStop:1; 	        // 2	键盘自由停机：1－自由停机；0－无效
						//	Stop键双击 
	unsigned int   KBForceStop:1; 		// 3	键盘强制停机
	unsigned int   KBEmergStop:1; 		// 4	键盘紧急停机
	unsigned int   KBPanel:1; 		// 5	键盘通道切换
	unsigned int   KBReset:1;		// 6	键盘复位
	unsigned int   RefChFCSet:1;		// 7	频率给定通道功能码设定
						//	键盘确认了F02.00
	unsigned int   CmdBindRefFCSet:1;	// 8	命令绑定给定功能码设定
						//	键盘确认了F05.02
	unsigned int   CmdChFCSet:1;		// 9	命令给定通道功能码设定
						//	键盘确认了F05.00
	unsigned int   MtrSltFCSet:1;		// 10	电机与控制功能码设定
						//	键盘确认了F00.07
	unsigned int   Torq2SpdFCSet:1;		// 11	转矩和速度控制功能码设定
						//	键盘确认了F07.00
	unsigned int   Torq2TorqCurrFCSet:1;	// 12	转矩和转矩电流选择功能码设定
						//	键盘确认了F07.01
	unsigned int   LocalPosFCSet:1;		// 13	本地位置指令功能码设定
						//	键盘确认了F13.04
										                                                                                          
       	unsigned int   KBUP:1;			// 14	键盘∧键，1->按键闭合   																				
	unsigned int   KBDN:1;			// 15	键盘∨键，1->按键闭合   																				
}S_RunStopCmd1;
/* 运行命令1－－all & bit access */
typedef union 
{
	unsigned short  all;
	S_RunStopCmd1 bit;
}U_RunStopCmd1;

/* 运行命令2－－bit fields  */ 
typedef struct
{
	unsigned int   TermFWD:1;		// 0	端子zheng转运行 
	unsigned int   TermREV:1;		// 1	端子反转运行
	unsigned int   TermJogFWD:1;		// 2	端子JOG zheng转运行
	unsigned int   TermJogREV:1;		// 3	端子JOG反转运行
	unsigned int   TermFreeStop:1; 		// 4	端子自由停机 
	unsigned int   KeyON:1;      // 5	预留
	//unsigned int   TermEmergStop:1;	// 5	端子紧急停机 
						//  060808 拆分为两个端子变量
	unsigned int   TermResetError:1;	// 6	端子故障复位
	unsigned int   TermForbitRun:1; 	// 7	端子禁止运行
	unsigned int   TermDCBrake:1; 		// 8	端子直流制动
	unsigned int   TermCMDValid:1; 		// 9	切换至端子命令
	unsigned int   TermForceStop:1; 	// 10	端子强制停机
						// 对所有的控制方式有效，按功能码设置的停机方式停机
	//unsigned int   rsvd2:1;          	// 11	reserved
	//unsigned int   TermDisablePWM:1;	// 11	端子中断输入，封PWM
						// 0频运行，中断解XX后转速跟踪恢复运行
						//  060808 拆分为两个端子变量
	unsigned int   TermForbidAccDec:1;	// 11	端子禁止加减速
	unsigned int   TriTermOprInput:1; 	// 12	san线式运转控制
	unsigned int   TermOLCLSwitch:1; 	// 13	端子开闭环切换
//	unsigned int   KBPanel:2;          	// 14~15	reserved
	unsigned int   rsvd2:2;
}S_RunStopCmd2;	
/* 运行命令2－－all & bit access */
typedef union 
{
	unsigned short   all;
	S_RunStopCmd2 bit;
}U_RunStopCmd2;


/* 运行命令4－－bit fields  */ 
typedef struct
{
	unsigned int   DEVStop:1;		// 0	DEV停机
	unsigned int   OSStop:1;		// 1	OS停机
	unsigned int   PIDirect:1;		// 2	PID给定方向		
	unsigned int   PIDEnter:1;		// 3	PID首次进入
	unsigned int   JogBugRun:1;    	// 4	runcmd sean2006.8.23
	unsigned int   PILimitReached:2;// 5~6	PI Limit is reached//2006.Xmas
	unsigned int   PoffToReady:1;	// 7    poff to ready 20070131
	unsigned int   ReRunFromPoff:1;	// 8   rerun when F5.13=1 20070131 no use 070301
	unsigned int   OLTFreeStop1:1;	// 9
	unsigned int   OLTFreeStop2:1;	// 10	
	unsigned int   KeyFWDToREV:1;	// 11   lxy100407 多功能键作为正反转切换时
	unsigned int   KeyRun:1;		// 12	Run键
	unsigned int   KeyStop:1;		// 13	Stop键	
	unsigned int   KBPanel:2;          	// 14~15	reserved
}S_RunStopCmd4;
/* 运行命令4－－all & bit access */
typedef union 
{
	unsigned short   all;
	S_RunStopCmd4 bit;
}U_RunStopCmd4;


/* 运行命令5－－bit fields  */ //
typedef struct
{
	unsigned int   CommCardCmd:2;    		// 0~1	comm card运行命令
						//	00 -- 停机
						//	01 -- zheng转
						//	10 -- 反转
						//	11 -- 运行，方向取自功能码  
	unsigned int   CommCardFWD:1;    		// 2	comm cardXX转运行 0715 no use
	unsigned int   CommCardREV:1;    		// 3	comm card反转运行 0715 no use
	unsigned int   CommCardJogFWD:1;    		// 4	comm card-JOGXX转运行，电平维持，0时停机 	
	unsigned int   CommCardJogREV:1;         	// 5	comm card-JOG反转运行，电平维持 
						//	CommCardJogFWD!=CommCardJogREV 命令有效，程序处理上同端子点动zheng反转       

	unsigned int   CommCardFreeStop:1;    	// 	6	comm card自由停机，上XX沿触发，一次性有效，响应后清零     	
	unsigned int   CommCardEmergStop:1;		// 7	comm card紧急停机，上XX沿触发     	
	unsigned int   CommCardResetError:1;    	// 8	comm card故障停机，上XX沿触发
	unsigned int   CommCardErrStop:1;    	// 9	comm card故障停机，电平维持，仅对SCI控制有效
	unsigned int   CommCardForbitRun:1;    	// 10	comm card禁止运行，电平维持
	unsigned int   CommCardFreqChg:1;    	// 11	 
	unsigned int   rsvd:4;          	// 12~15	reserved	 	
}S_RunStopCmd5;
/* 运行命令5－－all & bit access */ //
typedef union 
{
	unsigned short   all;
	S_RunStopCmd5 bit;
}U_RunStopCmd5;


typedef struct
{
	unsigned int   RefChannel:4;   		// 0~2 上次的给定通道
	unsigned int   AuxRefChannel:3;   	// 3~5 上次的辅助给定通道
	unsigned int   TorqToSpdTerm:1; 	// 6	转矩控制和速度控制切换端子
	unsigned int   Torq2TorqCurrTerm:1;	// 7   端子转矩和转矩电流切换
	unsigned int   HoldAITBiasTerm:1;	// 8	AI转矩偏置保持
	//以下标志的备份用于位置点动，键盘和通信在赋值点动命令时要备份该标志
	//unsigned int   KBJog:1;   	        // 9	键盘JOG
	unsigned int   TermJogFWD:1;		// 10	端子JOG zheng转运行																				
	unsigned int   TermJogREV:1;		// 11	端子JOG反转运行
	unsigned int   SciJogFWD:1;    		// 12	SCI-JOGXX转运行
	unsigned int   SciJogREV:1;         	// 13	SCI-JOG反转运行
	unsigned int   KBUP:1;			// 14	键盘∧键，1->按键闭合   																				
	unsigned int   KBDN:1;			// 15	键盘∨键，1->按键闭合 
	

}S_RunStopCmdBK2;
typedef union 
{
	unsigned short   all;
	S_RunStopCmdBK2 bit;
}U_RunStopCmdBK2;


typedef struct
{
	unsigned int   PosParamSwitchTerm:1;	// 0
	unsigned int   SearchOriginTerm:1; 	// 1
	unsigned int   ServoCtrlModeTerm:1; 	// 2	伺服切换端子
	unsigned int   SpdOrTorq:1; 		// 3	0 -- 速度控制; 1 -- 转矩控制
	unsigned int   StartFan:1;  		// 4	风扇启动
	unsigned int   RunCmd:1;    		// 5	runcmd sean2006.8.23
	unsigned int   CtlMode:2;   		// 6~7	00--速度控制
						//	01--转矩控制 		
						//	10--位置控制 		
						//	11--VF控制
	unsigned int   VectorMode:1;  		// 8	VC模式  0:SVC   1:VC
	unsigned int   TermOLCLSwitch:1; 	// 9	端子开闭环切换
	unsigned int   CtrlModeFCSetBK:4;       // 10~13	
	unsigned int   PosToSpdTerm:1;		// 14	位置切换到速度控制
	unsigned int   PosToTorqTerm:1;		// 15	位置切换到转矩控制
}S_RunStopCmdBK3;
typedef union 
{
	unsigned short   all;
	S_RunStopCmdBK3 bit;
}U_RunStopCmdBK3;



//===========================================================================
/* 控制命令1－－bit fields  */
typedef struct 
{
	unsigned int   RunDirect:1;   		// 0	运行方向（命令）
	unsigned int   RunCmd:1; 		// 1	1－运行；0－停机
	unsigned int   ForbitRun:1;          	// 2	禁止运行
						//	变频器dai机则禁止起动
						//	运行则自由停机
	unsigned int   RSV3:1;     	// 3	禁止反转
	unsigned int   RSV4:1;     	// 4	封锁PWM
	unsigned int   EmergStop:1;     	// 5	紧急停机
	unsigned int   FreeStop:1;     		// 6	自由机         				
	unsigned int   RSV7:1; 	// 7	启动转速跟踪
	unsigned int   RSV8:1; 	// 8	???启动预励磁
	unsigned int   RSV9:1;        	// 9	启动直流制动
	unsigned int   RSV10:1;   		// 10	???启动调谐  
	unsigned int   RSV11:1;  		// 11	风扇启动
	unsigned int   RSV12:1;  	// 12	启动能耗制动
	unsigned int   ForceStop:1; 		// 13	强制停机
	unsigned int   RSV14:1;		// 14	禁止加减速
	unsigned int   RestErr:1;  		// 15	故障复位
}S_CtrlCmd1;

/* 控制命令1－－all & bit access */
typedef union 
{
	unsigned short  all;
	S_CtrlCmd1 bit;
}U_CtrlCmd1;


#define SPEED_CTRL		0
#define TORQUE_CTRL		1
#define IF_CTRL		3

/* 控制命令2－－bit fields  */
typedef struct 
{
	unsigned int   CtlMode:2;   		// 0~1	00--速度控制
						//	01--转矩控制 		
						//	10--位置控制 		
						//	11--VF控制							
	unsigned int   Rsv2:2;   		// 2~3	00--从起动频率起动
										//	01--先制动再从起动频率起动 		
										//	10--转速跟踪起动 		
										//	11--无效
	unsigned int   Rsv4:2;   		// 4~5	00--减速停机
										//	自动加入功能耗制动
										//	01--自由停机 		
									//	10--减速停机+直流制动 		
									//	11--无效
	unsigned int   Rsv5:1;   	// 6	0--转矩控制
										//	1--转矩电流控制
										
	unsigned int   Rsv6:1; 		// 7	需要转速跟踪起动					 
	unsigned int   Rsv7:1;  		// 8	加减速模式
	unsigned int   Rsv8:1;  		// 9	VC模式  0:SVC   1:VC
	unsigned int   Rsv10:1;
	unsigned int   Rsv11:1; 
	unsigned int   Rsv12:1;											
	unsigned int   Rsv13:1;          	// 13   
	unsigned int   Rsv14:1;   		// 14	送核心的运行方向,no use 0717	
	unsigned int   RunStopCmd:1;  		// 15	送核心的运行命令    				
	
}S_CtrlCmd2;
/* 控制命令2－－all & bit access */
typedef union 
{
	unsigned short  all;
	S_CtrlCmd2 bit;
}U_CtrlCmd2;

/* 控制命令3－－bit fields  */
typedef struct 
{
	unsigned int   CtlMode:2;   		// 0~1	00--速度控制
						//	01--转矩控制 		
						//	10--位置控制 		
						//	11--VF控制							
	unsigned int   ForbitFWD:1;     	// 2	禁止zheng转									
	unsigned int   BrakeFlag:1;		// 3	detect e027 on power up	
	unsigned int   InertiaIdbegin:1;		//4
	unsigned int   InertiaIdfinish:1;		//5 inertia identify finish	
	unsigned int   BrakeZeroSpd:1;			//6				
	unsigned int   BrakeHoldon:1;		// 7	
	unsigned int   UrgentStop:1;          	// 8				
	unsigned int   rsvd:7;          	// 9~15   reserved	
}S_CtrlCmd3;
/* 控制命令2－－all & bit access */
typedef union 
{
	unsigned short  all;
	S_CtrlCmd3 bit;
}U_CtrlCmd3;

//===========================================================================
/* 运行状态1－－bit fields  */
typedef struct 
{
	unsigned int   RunStatus:1; 		// 0	运：1－运行；0－停机
	unsigned int   OVSpeedHold:1; 		// 1	XX压失速：1－失速；0－XX
	unsigned int   OCSpeedHold:1; 		// 2	XX流失速 
	unsigned int   HaveError:1;        	// 3	有故障要处理 
	unsigned int   DCBrakeIsOn:1;    	// 4	起动制动XX在进行
	unsigned int   PreExcitIsOn:1;		// 5	预励磁XX在进行(核心送来的标志)
	unsigned int   SwitchToSpdMode:1;	// 6	
	unsigned int   StopDCBrakeIsOn:1;     	// 7	停机制动XX在进行
	unsigned int   StallingIsOn:1;     	// 8	 
	unsigned int   TuningIsOK:1;     	// 9	调谐XX常  060821 no use
	unsigned int   WritenMotorParaToROM:1; 	// 10	电机参XX已经写入ROM
	unsigned int   PowerIsOK:1;     	// 11	电源电压XX常 
	unsigned int   TorqueLimitIsOn:1;   	// 12	转矩限定XX在进行
	unsigned int   TorqueIsNegative:1;	// 13	转矩为负
	unsigned int   Spd2TorqIsFinished:1;    // 14	
	unsigned int   MDIReady:1;          	// 15   变频器运行准备完成
}S_RunStopStatus1;
/* 运行状态1－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus1 bit;
}U_RunStopStatus1;

/* 运行状态2－－bit fields  */
typedef struct 
{
	unsigned int   RuningStep:2;   		// 0~1	00--无效
						//	01--加速运行 		
						//	10--减速运行 		
						//	11--恒速运行
	unsigned int   CmdChannel:2;   		// 2~3	00--键盘控制
						//	01--端子控制 		
						//	10--通信控制 		
						//	11--无效
	unsigned int   RefChannel:4;   		// 4~6	0--键盘∧∨给定
						//	1--端子UP/DN给定 		
						//	2--串行口
						//	3--AI模拟给定 		
						//	4--端子PULSE给定
						//	5--PLC
						//	6--PID
						//	7--多段速
						//  8--扩展卡（非PG卡）
						//  其他无效
	//unsigned int   SpinState:1;		// 7    摆频状态     lxy100407 del          						
						//	1--zheng在摆频;0--无摆频
	unsigned int   ErrIsSaved:1;     	// 8	通知故障保存程序保存当前故障
	unsigned int   ErrIsMemorized:1;     	// 9	故障记忆guo
	unsigned int   AutoRstErrIsON:1;     	// 10	故障自复位中
	//unsigned int   rsvd:1;    	// 11	reserved
	//unsigned int   ErrIsValid:1;    	// 11	故障有效 
	unsigned int   ErrFreqRefIsValid:1;    	// 11	故障设定频率有效
	unsigned int   HaveErrLock:1;    	// 12	有故障锁存
	unsigned int   HavePreOLErr:1;         	// 13   有预guo载故障 no use 060926
	unsigned int   AutoRstAllErrIsON:1; 	// 14	
	unsigned int   HaveErrBeforePoff:1;   	// 15   
	
}S_RunStopStatus2;

/* 运行状态2－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus2 bit;
}U_RunStopStatus2;

/* 运行状态3－－bit fields  */
typedef struct 
{
	unsigned int   FreqHighLimit:1;    	// 0	频率上限限制
	unsigned int   FreqLowLimit:1;		// 1	频率下限限制	
	unsigned int   ZeroSpeedRunning:1;	// 2	变频器零速运行中
	unsigned int   SpdBeingLimited:1; 	// 3	速度限制中
	unsigned int   TorqBeingLimited:1; 	// 4	转矩限制中
	unsigned int   ZeroServoFinished:1; 	// 5	零伺服完成		
	unsigned int   AITorqBiasValid:1; 	// 6	模拟转矩偏置有效    	
	unsigned int   MAOFinished:1;		// 7	主轴定向完成		  	
	unsigned int   SMotorBraker:1;  	// 8	伺服电机抱闸 	
	unsigned int   MtrSelect:1;	  	// 9   电机选择甘?
						//      0 --- 电机1
						//	1 --- 电机2
	unsigned int   MtrMode:1;	  	// 10   电机类型					
						//	0 --- 异步机
						//	1 --- 同步机
	unsigned int   MAOSpd1Reached:1;	// 11	主轴第1定向速度到达 no use 20061122
	unsigned int   Spd1To2PosReached:1;	// 12	第1/2定向速度切换位置到达
	unsigned int   MAOSpd2Reached:1;	// 13	主轴第2定向速度完成 no use 20061122
	unsigned int   StartOrientPosReached:1;	// 14	开始定向位置到达
	unsigned int   StopSpdflag:1;    	// 15	stop speed time count 20071115
}S_RunStopStatus3;
/* 运行状态3－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus3 bit;
}U_RunStopStatus3;

/* 运行状态4－－bit fields  */
typedef struct 
{
	unsigned int   RunWaitIsOK:1;  		// 0	运行等XX完成
	unsigned int   StartIsOK:1;    		// 1	起动完成
	unsigned int   StopSpdIsReached:1;    	// 2	停机速度到达
	unsigned int   StopDCBrakeIsOK:1;    	// 3	停机直流制动完成
	unsigned int   Fwd2RevIsSwitching:1;   	// 4	zheng反转切换中?? useless
	unsigned int   SartDCBrakeIsOK:1;    	// 5	起动直流制动完成
	unsigned int   RunStopSts:1;    	// 6	run status exit Poff
	unsigned int   RunAfterPoff:1;    	// 7	停电再起动标志
	unsigned int   ErrFreqIsRefreshed:1;   	// 8	停电再起动标志
	unsigned int   SpdTorqIsOn:1;          	// 9    速度转矩进行中 
	unsigned int   MtrPwrPolar:1;          	// 10   电机功率极性  0 -- zheng; 1 -- 负
	unsigned int   FirstPowerOn:1;   	// 11	首次上电标志
						// 	0 -- 首次上电
						//	1 -- 非首次上电
	unsigned int   FirstJogRun:1;   	// 12	首次JOG运行标志
						// 	0 -- 首次JOG运行
						//	1 -- 非首次JOG运行
	unsigned int   MotorRunDirect:1;   	// 13	
	//unsigned int   ClrJogStopTimer:1;   	// 13	清JOG停机计时标志20070602 reserved
	unsigned int   PreOLIsOn:1;   		// 14	预guo载中
	unsigned int   PowerIsOn:1;   		// 15	通电标志，用于上电时恢复通电计时
}S_RunStopStatus4;
/* 运行状态4－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus4 bit;
}U_RunStopStatus4;

/* 运行状态5－－bit fields  */
typedef struct 
{
	unsigned int   PLCStepFinished:1;  	// 0	PLC阶段运转完成指示    no use 060621	
	unsigned int   PLCFinished:1;    	// 1	PLC循环完成指示  no use 060621
	unsigned int   SpinUpDnIsLimited:1; 	// 2	摆频上下限限制
	unsigned int   TorqPole:1;    		// 3	转矩极性检测输出
	unsigned int   OvBelowTorq1:1;		// 4	XX转矩/不足转矩1		
	unsigned int   OvBelowTorq2:1; 		// 5	XX转矩/不足转矩2
	unsigned int   OverSpdErr:1; 		// 6	速度偏差XX大，送核心
						//	暂时不需要键盘和端子指示
	unsigned int   OverSpdRef:1; 		// 7	guo速度（OS），送核心
						//	暂时不需要键盘和端子指示
	unsigned int   PIDIsRunning:1;   	// 8    PIDzheng运行
	unsigned int   PIDPreFreqIsReached:1;   // 9    PID预置频率到达
	unsigned int   PIDIsDisabled:1;   	// 10   PID失效
	unsigned int   PIDErrIsNeg:1;   	// 11   PID偏差为负
	unsigned int   SpinIsRunning:1;         // 12   摆频zheng在运行	
	unsigned int   PIDPeriodIsUnreached:1;  // 13   PID 采样周期未到达

	unsigned int   AssertCountEnable:1;	// 14   20070619

	//unsigned int   PGCloseLoopIsOn:1;       // 14   PG闭环zheng在进行 060816 DEL
						//	VF控制 1--PG闭环 0--PG闭环无效
						//	矢量控制 1--VC 	0--SVC
	unsigned int   CurrRunDirect:1; 	// 15	当前的运行方向,仅仅在初始化运行的时候判断
}S_RunStopStatus5;
/* 运行状态5－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus5 bit;
}U_RunStopStatus5;


/* 运行状态6－－bit fields  */
typedef struct 
{
	unsigned int   FirstInTorqMode:1;  	// 0
	unsigned int   BeInPwmOn:1;	  	// 1	
	unsigned int   PreErrIsOC:1;	  	// 2
	unsigned int   ErrIsOC:1;	  	// 3
	unsigned int   EepromIsErr:1;	  	// 4  deal in writing e2prom
	unsigned int   TorqPIDRefFlag:1;		// 5	PID转矩给定
	unsigned int   TorqPIDLmt1Flag:1;		// 6	PID转矩限制1
	unsigned int   TorqPIDLmt2Flag:1;		// 7	PID转矩限制2 
	unsigned int   PINegRunForbid:1;		// 8
	unsigned int   DIFirstFiltIsOK:1;		// 9
	unsigned int   FirstInNormOprMode:1;		// 10	
	unsigned int   OLT1FlgBk:1;		// 11 20070607
	unsigned int   OLT2FlgBk:1;		// 12
	unsigned int   AI1IsOverCurrent:1; 	// 13
	unsigned int   AI2IsOverCurrent:1; 	// 14
	unsigned int   NotSpdRunDirect:1; 	// 15	
}S_RunStopStatus6;
/* 运行状态6－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatus6 bit;
}U_RunStopStatus6;



//===========================================================================
/* 诵方式－－bit fields  */
typedef struct 
{
	unsigned int   TuneRun:1; 	// 0	电机调谐
	unsigned int   JogRun:1;   	// 1	点动运行：1－有效；0－无效，下同
	unsigned int   PIDRun:1;       	// 2	闭环运行
	unsigned int   PLCRun:1;    	// 3	PLC运行 
	unsigned int   MulStepRun:1;   	// 4	多段速运行
	unsigned int   NormRun:1;   	// 5	普通运行
	unsigned int   ServoRun:1;   	// 6	伺服运行	no use 20061122
	unsigned int   CustomRun:1;   	// 7	客户化运行
	unsigned int   SpinRun:1;	// 8	摆频运行
	unsigned int   SpdSynRun:1;	// 9	速度同步运行  no use 20061121
	unsigned int   InertiaTune:1;	// 10         guanliang调谐
	unsigned int   rsvd:5;		// 11~15: reserved	
						//其他客户化运行方式
						//摆频频率仅叠加PLC、MulSpd、Norm
}S_OperateMode;
/* 运行方式－－all & bit access */
typedef union  
{
	unsigned short   all;
	S_OperateMode bit;
}U_OperateMode;
//===========================================================================	
typedef struct 
{			
	unsigned int	SMTune:1;		//  0	0：异步机调谐，1：同步机调谐
	unsigned int	SMDcBrake:1;		//  1	0旱谝欢沃绷鳎?：第二段直流
	unsigned int	TuneRunbak:1;		//  2 	
	unsigned int	Rsv:12;			//  2~14	reserved
	unsigned int	TuneStop:1;		//  15	调谐停机
}S_TuneFlag;  
typedef union      
{                  
	unsigned short      all;
	S_TuneFlag  bit;
}U_TuneFlag;


//===========================================================================

/* Judge Alarm Flag */	
typedef struct 
{
	unsigned int   SciErr:1; 			// 0			
	unsigned int   ContactorErr:1; 		// 1
	unsigned int   EepromErr:1; 		// 2
	unsigned int   P24Err:1; 			// 3
	unsigned int   RefLossErr:1; 		// 4
	unsigned int   PreOLErr:1; 			// 5
	unsigned int   LLErr:1; 			// 6
	unsigned int   PidFbErr:1;			// 7
	unsigned int   TempInvOpenErr:1;	// 8
	unsigned int   TempRecOpenErr:1;	// 9
	unsigned int   TempMotorOvErr:1;	// 10
	unsigned int   AiFaultErr:1;		//11
	unsigned int   P10Err:1;			// 12
	unsigned int   PidLimErr:1; 	   // 13 lxy100707
	unsigned int   rsvd:2; 				// 14~15
}S_AlarmJudge;
/* all & bit access */
typedef union  
{
	unsigned short     all;
	S_AlarmJudge bit;
}U_AlarmJudge;
/*Valid Alarm Flag */
typedef struct 
{
	unsigned int   SciErr:1;			// 0
	unsigned int   ContactorErr:1;		// 1
	unsigned int   EepromErr:1;			// 2
	unsigned int   P24Err:1;			// 3
	unsigned int   RefLossErr:1;		// 4
	unsigned int   PreMdiOLErr:1;		// 5
	unsigned int   PreMtrOLErr:1;		// 6
	//unsigned int   LLErr:1; 			// 7
	unsigned int   PidFbLostErr:1;      // 7    ysh100603
	unsigned int   PidFbOverErr:1;		// 8    ysh100603
	unsigned int   TempInvOpenErr:1;	// 9
	unsigned int   TempRecOpenErr:1;	// 10
	unsigned int   TempMotorOvErr:1;	// 11
	unsigned int   AiFaultErr:1;	    // 12
	unsigned int   P10Err:1;			// 13
	unsigned int   PidLimErr:1; 		// 14 lxy100707
	unsigned int   rsvd:1; 				// 15
}S_PermitAlarm;

/* all & bit access */
typedef union  
{
	unsigned short     all;
	S_PermitAlarm bit;
}U_PermitAlarm;

typedef struct 
{
	unsigned int   CurrRunDirect:1;  	// 0	当前的运行方向 
	unsigned int   PowerIsOn:1;   		// 1	通电标志  
	unsigned int   AutoRstErrIsON:1;     	// 2	故障自复位中  	
	unsigned int   PLCRun:1;     		// 3	PLC运行
	unsigned int   CmdChannel:2;   		// 4~5	00--键盘控制
						//	01--端子控制 		
						//	10--通信控制 		
						//	11--无效
	unsigned int   rsvd:10;          	// 6~15   reserved
}S_RunStopStatusBK1;

/* 上次运行状态1－－all & bit access */
typedef union  
{
	unsigned short     all;
	S_RunStopStatusBK1 bit;
}U_RunStopStatusBK1;

// 为了检测部分状态的沿或上一次值，将上一次的状态记忆下来。
typedef struct
{
	unsigned int   TermFWD:1;		// 0	端子zheng转运行   																				
	unsigned int   TermREV:1;		// 1	端子反转运行
	unsigned int   TriTermOprInput:1; 	// 2	san线式运转控制
	unsigned int   TermFWDREVNeedTrim:1;	// 3	端子zheng转运行是否需要沿
	unsigned int   CmdScourceTerm1:1;    	// 4	命令源选择1     	
	unsigned int   CmdScourceTerm2:1;    	// 5	命令源选择2
	unsigned int   TermCMDValid:1; 		// 6	切换至端子命令
	unsigned int   TermMainFreqToAI:1;    	// 7	主给定频率切换至AI
	unsigned int   MainFreqScourceTerm1:1;	// 8	主给定频率源选择1
	unsigned int   MainFreqScourceTerm2:1;  // 9	主给定频率源选择2
	unsigned int   MainFreqScourceTerm3:1;  // 10	主给定频率源选择3
	unsigned int   ASMotor1To2Term:1;	// 11   异步电机1和2切换端子
	unsigned int   TermResetError:1;	// 6	端子故障复位
	unsigned int   RunDirect:1;   		// 13	运行方向
	unsigned int   TermFreeStop:1;    	// 14	端子自由停车
	unsigned int   PowerIsOK:1;     	// 15	电源电压XX常
}S_RunStopCmdBK1;
typedef union 
{
	unsigned short   all;
	S_RunStopCmdBK1 bit;
}U_RunStopCmdBK1;
		
/*全局变量*/


_VARIABLESEX_DEF_  U_AlarmJudge  uAlarmJudge;
_VARIABLESEX_DEF_  U_PermitAlarm  uPermitAlarm;
_VARIABLESEX_DEF_  U_RunStopCmd1  uRunStopCmd1;		//运行命令1  Key Pannel

_VARIABLESEX_DEF_  U_RunStopCmd4  uRunStopCmd4;		//运行命令4  serial com
_VARIABLESEX_DEF_  U_RunStopCmd5  uRunStopCmd5;		//运行命令5  exp card

_VARIABLESEX_DEF_  U_RunStopCmdBK2  uRunStopCmdBK2;
_VARIABLESEX_DEF_  U_RunStopCmdBK3  uRunStopCmdBK3;
_VARIABLESEX_DEF_  U_RunStopStatusBK1 uRunStopStatusBK1;	//运行状态备份
_VARIABLESEX_DEF_  U_RunStopCmdBK1  uRunStopCmdBK1;	//运行命令备份（用于检测沿）


_VARIABLESEX_DEF_  U_CtrlCmd1  uControlCmd1;	//控制命令1	//所有命令通道的命令汇总
_VARIABLESEX_DEF_  U_CtrlCmd2  UCoreCmd;	//控制命令2	//用于送核心的命令

_VARIABLESEX_DEF_  U_RunStopStatus1 uRunStopStatus1;	//运行状态1
_VARIABLESEX_DEF_  U_RunStopStatus2 uRunStopStatus2;	//运行状态2
_VARIABLESEX_DEF_  U_RunStopStatus3 uRunStopStatus3;	//运行状态3
_VARIABLESEX_DEF_  U_RunStopStatus4 uRunStopStatus4;	//运行状态4
_VARIABLESEX_DEF_  U_RunStopStatus5 uRunStopStatus5;	//运行状态5

_VARIABLESEX_DEF_  U_RunStopStatus6 uRunStopStatus6;

_VARIABLESEX_DEF_  long		MainFreqRef;		// 主给定通道设定频率（不含方向）
_VARIABLESEX_DEF_ 	unsigned short  TX0, TX1, TX2, TY0, TW0, TW1, TW2, TW3;	
_VARIABLESEX_DEF_  uint16  OutputVolt;       
_VARIABLESEX_DEF_  uint16  OutputCurr;		// 输出电流(单位：0.1A)
_VARIABLESEX_DEF_  uint16  VoltDC; 		// 母线电压（0~800V，单位：1V）

_VARIABLESEX_DEF_   long   OutputFreq; 			// 输出频率(单位：0.01Hz)（含方向）

_VARIABLESEX_DEF_  unsigned long 	CurrentRefFreq;		// 经加减速阶段后的输出频率
_VARIABLESEX_DEF_  long 		SpdLmtFreq1;		// 速度限制值1（无方向）
_VARIABLESEX_DEF_  long 		SpdLmtFreq2;		// 速度限制值2（无方向）
_VARIABLESEX_DEF_  long 		CurrentFreq;		// 送核心的设定频率（含方向）To Core	
//===========================================================================


_VARIABLESEX_DEF_  long 	Time1msBase;		// 1ms时基
_VARIABLESEX_DEF_  long 	TimerForPowerOn;		// 1ms时基

_VARIABLESEX_DEF_  short 	ComCardTorqRef;		// 通讯卡转矩给定（+/-300%，单位：0.1%）

_VARIABLESEX_DEF_  long TimerOL;


_VARIABLESEX_DEF_  unsigned short StartVoltDetect;

_VARIABLESEX_DEF_  unsigned short CurrSensorIsOk;

_VARIABLESEX_DEF_  uint16  TemperVoltSample;
_VARIABLESEX_DEF_  int16   TemperReal,TemperUReal,TemperVReal,TemperWReal;
_VARIABLESEX_DEF_  int32   TemperRealAcc,TemperURealAcc,TemperVRealAcc,TemperWRealAcc;
_VARIABLESEX_DEF_  int16   TemperRealFlt,TemperURealFlt,TemperVRealFlt,TemperWRealFlt;

_VARIABLESEX_DEF_  short    UsTemp[2];
_VARIABLESEX_DEF_  short  	UsAlphaRef;
_VARIABLESEX_DEF_  short  	UsBetaRef;
_VARIABLESEX_DEF_  short  	sinAgl;
_VARIABLESEX_DEF_  short  	cosAgl;

//***********************************************************************************************
_VARIABLESEX_DEF_  int  	UphasePeak;

//***********************************************************************************************

_VARIABLESEX_DEF_  Uint32 InterruptCnt;

_VARIABLESEX_DEF_  Uint16 CurrentSensorErr;

_VARIABLESEX_DEF_  Uint32 ForceAQFinished;

_VARIABLESEX_DEF_  long aglVf;

_VARIABLESEX_DEF_  Uint16    Ch1;
_VARIABLESEX_DEF_  Uint16    Ch2; 
_VARIABLESEX_DEF_  Uint16    Ch3; 
_VARIABLESEX_DEF_  Uint16    Ch4; 
  

_VARIABLESEX_DEF_  Uint16 Resolver_Sin;
_VARIABLESEX_DEF_  Uint16 Resolver_Cos;

_VARIABLESEX_DEF_  Uint32 CntTemp;

_VARIABLESEX_DEF_  unsigned int* pDA1;
_VARIABLESEX_DEF_  unsigned int* pDA2;

_VARIABLESEX_DEF_  Uint16 DAShift1;
_VARIABLESEX_DEF_  Uint16 DAShift2;

_VARIABLESEX_DEF_  Uint16 SpeedFltCnt;

_VARIABLESEX_DEF_  long rlSpeedFedLed;
_VARIABLESEX_DEF_  long rlSpeedFedLed1;

_VARIABLESEX_DEF_  long TrqCmdPercent;
_VARIABLESEX_DEF_  long TrqCurrCmdPercent;

_VARIABLESEX_DEF_  long TorqLmtFwdPosPu;
_VARIABLESEX_DEF_  long TorqLmtFwdNegPu;

_VARIABLESEX_DEF_  int TorqCurrOutPercentTemp;
_VARIABLESEX_DEF_  int ToqOutPercent;

//_VARIABLESEX_DEF_  int TorqCurrRefPercentTemp;
_VARIABLESEX_DEF_  long TorqRefPercent;
_VARIABLESEX_DEF_  int TorqIqGcw;

//_VARIABLESEX_DEF_  long TorqRealRaw;
_VARIABLESEX_DEF_  long TorqReal;
//_VARIABLESEX_DEF_  long TorqReal_1;
//_VARIABLESEX_DEF_  long TorqReal_2;
_VARIABLESEX_DEF_  long MotorRealPower;
_VARIABLESEX_DEF_  long MotorRealPower_1;
_VARIABLESEX_DEF_  long MotorRealPower_2;
_VARIABLESEX_DEF_  int  MotorPowerPercent;

_VARIABLESEX_DEF_  Uint32 UsSquare;
_VARIABLESEX_DEF_  Uint16 VoltOut;

_VARIABLESEX_DEF_  int MagnetCurrOutReal;
_VARIABLESEX_DEF_  int MagnetCurrOutPercent;
_VARIABLESEX_DEF_  int TorqCurrOutReal;
_VARIABLESEX_DEF_  int TorqCurrOutPercent;

_VARIABLESEX_DEF_  int MagnetCurrRefReal;
_VARIABLESEX_DEF_  int MagnetCurrRefPercent;
_VARIABLESEX_DEF_  int TorqCurrRefReal;
_VARIABLESEX_DEF_  int TorqCurrRefPercent;

_VARIABLESEX_DEF_  int MotorRealSpeed;
_VARIABLESEX_DEF_  int MotorRealSpeedForTorqCal;

_VARIABLESEX_DEF_  Uint16 ResolverMechAngleInit;
_VARIABLESEX_DEF_  Uint16 ResolverInitOK;
_VARIABLESEX_DEF_  Uint16 PowerIsReady;

extern int          Param_SpeedFwdCtrlOut;
extern int          Param_TrqRefValue;
extern int          Param_IqSetUnlim;

_VARIABLESEX_DEF_  Uint16 SoftOcCnt;

_VARIABLESEX_DEF_  Uint16 ReverseForbid;   // 禁止倒溜标志
_VARIABLESEX_DEF_  Uint16 ForwardForbid;   // 禁止前溜标志

_VARIABLESEX_DEF_  Uint16 ResAmpReal;
_VARIABLESEX_DEF_  Uint16 ResAmpError;
_VARIABLESEX_DEF_  Uint16 ResAmp;
_VARIABLESEX_DEF_  Uint16 ResolvCheckEnable;

_VARIABLESEX_DEF_  long    PowerPu;
_VARIABLESEX_DEF_  long    PowerReal;
_VARIABLESEX_DEF_  long    PowerFltAcc;
_VARIABLESEX_DEF_  long    PowerFlt;

_VARIABLESEX_DEF_  Uint16    Uphase;

_VARIABLESEX_DEF_  long    ForDriveJudge;

_VARIABLESEX_DEF_  uint16    temp_AI_Sample_NTCU;
_VARIABLESEX_DEF_  uint16    temp_AI_Sample_NTCV;
_VARIABLESEX_DEF_  uint16    temp_AI_Sample_NTCW;



_VARIABLESEX_DEF_	uint16 SimIu,SimIw,SimDC,SimMCUTemp,SimMotorTemp,SimSpeed;


_VARIABLESEX_DEF_   long ValueLong_MaxOutFrq;



#define DEBUG_VOL_DC			0
#define DEBUG_CURRENT			1
#define DEBUG_MCU_TEMP			2
#define DEBUG_MOTOR_TEMP		3
#define DEBUG_SPEED				4
#define DEBUG_U					5
#define DEBUG_W					6


_VARIABLESEX_DEF_	uint16  InitFinish;
_VARIABLESEX_DEF_ unsigned int    udc_rated_Sqrt2;

#endif  // end of OPERATE_VARIABLES_H definition
