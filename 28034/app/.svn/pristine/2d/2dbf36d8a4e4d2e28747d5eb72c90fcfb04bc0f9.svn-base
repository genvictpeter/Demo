//****************************************************************************
// @Module       
// @Filename      CANProtocal.c
// @Project       BQApp
//----------------------------------------------------------------------------
// @Controller    TI 28034
//
// @Compiler      V5.211
//
// @Codegenerator CCS 3.3
//
// @Description   V1.5 CAN Protocal
//
//----------------------------------------------------------------------------
// @Date          12/19/2014
//
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****
//
//***************************************************************************
//C30DB经济型电动车项目(锂电池方案)
//CAN网络驱动电机控制系统节点报文协议参考BJEV_C33DB-M07_EVBUS_MCU_CAN_V7.1_20190410

#include "main.h"     // DSP281x Headerfile Include File
#include "FunctionCode.h"
#include "SpeedFunc.h"
#include "KeyBoard_Extypes.h"
#include "GlobalVariables.h"
#include "Ev72ctrl.h"
#include "DrivePublicVar.h"
#include "Error.h"
#include "EepromManage.h"
#include "Const.h"
#include "TorqFunc.h"
#include "CAN.h"
#include "IOFunc.h"
#include "AppDefine.h"
#define CAN_PROTOCAL_DEF_SET 1
#include "CANProtocal.h"


void MCU_RES0();
void MCU_RES1();
void MCU_RES2();
void MCU_RES3();
void MCU_RES4();
void MCU_RES5();
void MCU_RES6();
void MCU_RES7();
void MCU_RES8();
void MCU_RES9();
void MCU_RES10();
void MCU_RES11();
void MCU_RES12();
void MCU_RES13();
void MCU_RES14();
void MCU_RES15();

void Diagnosis_Res1();
//void Diagnosis_Res2();
//void Diagnosis_Res3();

void J1939_ReceiveMessages( void );
int  J1939_DequeueMessage( J1939_MESSAGE *MsgPtr );
int  SendOneMessage( J1939_MESSAGE *MsgPtr ,int ch);
void VCU_CMD_0();
void VCU_CMD_2();
void VCU_CMD_4();
void VCU_CMD_7();
void Diagnosis_func();
extern long DV3232_32(long,unsigned long,unsigned long);
extern unsigned long divu64d32 (unsigned long factor1, unsigned long factor2, unsigned long divisor); 
extern int Udc,TorqComp,Delta_Flux;

extern int Thta,OneByPsiMax,TrqSetTotal,ModifiedKtFactor,MaxTorqueEnable,IqRefOpt,Shadw_IdULimit1;

extern long SpdLmtFilter1,SpdLmtFilter2,SpdLmtFilter11,SpdLmtFilter12,Int_FluxCtrl;

extern int IuSample;
extern int IwSample;
extern int IuError;
extern int IwError,ShutPWM;
extern int Param_SpeedRevCtrlOut,Param_SpeedRevCtrlDev,Param_SpeedFwdCtrlDev,delta_theta,TorqComp1,TorqComp2;
extern long Param_Int_FwdN_HD,Param_Int_RevN_HD,SmoothDelta,rlSpeedFedEst,rlSpeedFedHigh;
long CANTorqRealDis,CANTorqFed;
uint16 EnNormalTrans,BootWaitTime,isUpdateMe,MCUBeat,PowerOff12VDelay;
uint16 err_level,err_num;

extern Uint16 ErrorIndex;
extern int EnableDischarge,DischargeCurrent;
extern uint16 PowerOffStep;

extern uint8_t  Mcu_Configuration[2];
extern uint8_t	  MotCode[30];
extern uint8_t 	  VIN[17];	
extern int ImagRms;

extern Uint16 CheckedPreprogConditonFlg;

void CAN_Cfg1939Mail()
{	
	uint32 CANMDSET,CANMESET;
	
	CANMDSET = ECanaRegs.CANMD.all;
	CANMESET = ECanaRegs.CANME.all;
	ECanaRegs.CANME.all = 0;
	/* Disable all Mailboxes */
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.

	
	//RX
	ECanaMboxes.MBOX16.MSGID.all = 0;	
	ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = VCU_0; 

	ECanaMboxes.MBOX17.MSGID.all = 0;		
	ECanaMboxes.MBOX17.MSGID.bit.STDMSGID = VCU_2; 

	ECanaMboxes.MBOX18.MSGID.all = 0;	
	ECanaMboxes.MBOX18.MSGID.bit.STDMSGID = VCU_7; 

	ECanaMboxes.MBOX19.MSGID.all = 0;	
	ECanaMboxes.MBOX19.MSGID.bit.STDMSGID = VCU_4; 


	
	
	//TX
	ECanaMboxes.MBOX0.MSGID.all = 0;
	ECanaMboxes.MBOX0.MSGID.bit.STDMSGID= MCU_0;

	ECanaMboxes.MBOX1.MSGID.all = 0;	
	ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = MCU_1;

	ECanaMboxes.MBOX2.MSGID.all = 0;	
	ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = MCU_2;

	ECanaMboxes.MBOX3.MSGID.all = 0;	
	ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = MCU_3;

	ECanaMboxes.MBOX25.MSGID.all = 0;
	ECanaMboxes.MBOX25.MSGID.bit.STDMSGID = MCU_4;

	ECanaMboxes.MBOX5.MSGID.all = 0;
	ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = MCU_5;

	ECanaMboxes.MBOX6.MSGID.all = 0;
	ECanaMboxes.MBOX6.MSGID.bit.STDMSGID = MCU_6;

	ECanaMboxes.MBOX12.MSGID.all = 0;	
	ECanaMboxes.MBOX12.MSGID.bit.STDMSGID = MCU_7;
	
	ECanaMboxes.MBOX13.MSGID.all = 0;	
	ECanaMboxes.MBOX13.MSGID.bit.STDMSGID = MCU_8;
	
	ECanaMboxes.MBOX14.MSGID.all = 0;
	ECanaMboxes.MBOX14.MSGID.bit.STDMSGID = MCU_9;
	
	ECanaMboxes.MBOX20.MSGID.all = 0;	
	ECanaMboxes.MBOX20.MSGID.bit.STDMSGID = MCU_10;
	
	ECanaMboxes.MBOX23.MSGID.all = 0;
	ECanaMboxes.MBOX23.MSGID.bit.STDMSGID = MCU_11;
	
	ECanaMboxes.MBOX29.MSGID.all = 0;
	ECanaMboxes.MBOX29.MSGID.bit.STDMSGID = MCU_12;
	
	ECanaMboxes.MBOX30.MSGID.all = 0;
	ECanaMboxes.MBOX30.MSGID.bit.STDMSGID = MCU_13;
	
	ECanaMboxes.MBOX31.MSGID.all = 0;
	ECanaMboxes.MBOX31.MSGID.bit.STDMSGID = MCU_14;
	
	ECanaMboxes.MBOX27.MSGID.all = 0;
	ECanaMboxes.MBOX27.MSGID.bit.STDMSGID = MCU_15;

	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	
	CANMDSET |=  0x000F0000;			//rsv mail set to 1
	ECanaRegs.CANMD.all = CANMDSET;

	
	CANMESET |= 0xE09F707F;
	ECanaRegs.CANME.all = CANMESET;	
	
}



void J1939_Initialization()
{
		RXHead = 0;
		RXTail = 0;
		RXQueueCount = 0;

		InvStatus = INV_12V_ON;
		CANCtrlMode = 0;
		CANCtrlModeBak = 0;
		CANRequestFreq = 0;
		CANRequestTorque = 0;
		CANRequestTorque1 = 0;
		MaxTorqueFilt = 0;
		Gear = 0;
		NoSlide = 0;
		GeraErr = 0;
		VmsState = 0;
		CANDirect = 0;
		DriveTorqLimit = 261L*50;		//0.02Nm
		GenTorqLimit   = 261L*50;
		BusOffTime = 0;
		BusOffResetTime = 0;
		CANTorq = 0;
		LifeSignalClick = 0;

	
		EnNormalTrans = 1;

		isBrake = FALSE;

		SendCount0 = 8;		//10ms		2,12,22,32,42,52,62,72,82
		SendCount1 = 16;	//20ms		4,24,44,64,84,104,124,
		SendCount2 = 0;		//1ms
		SendCount3 = 12;	//100ms		88,188,288,388,	
		SendCount4 = 984;	//1000ms		16,1016,2016,3016			
		SendCount5 = 1;     //5000MS
		SendCount6 = 10;    //5000ms
		CANErrorUpdate = 0;
		isUpdateMe = 0;
		MCUBeat = 0;
		CANMotorCmd.Word = 0;
        DriveState.Word = 0;
		PowerOff12VDelay = 0;

        SlipCut_counter = 0;                        //防溜坡切换计数器
        SlipQuit_flag = 0;
        SlipQuit_Clear_Counter = 0;
		SlipCut_timer = 0;
}




void J1939_Poll( unsigned int ElapsedTime )
{
	if(4u == (Mcu_Configuration[1]&0x00ff))
	{
		CANTorqReal = TorqReal/100;		//0.001Nm-->0.1Nm;
		CANTorqRealDis=(CANTorqReal*8192L-CANTorqRealDis)/2+CANTorqRealDis;
		Funcode.CurrLimitPH.value = 0u;//关闭防抖
	}
	else 
	{
		CANTorqReal = TorqReal/20;		//0.001Nm-->0.02Nm;
		CANTorqRealDis=(CANTorqReal*8192L-CANTorqRealDis)/4+CANTorqRealDis;	
	}
	CANTorqFed = CANTorqRealDis/8192L;
	CANTorqFed = labs(CANTorqFed);
	if (CANTorqFed<=10L)  CANTorqFed = 0L;

	
	if(ECanaRegs.CANTA.all)//any successful transmit reset BusOffCounter
	{
		BusOffTime=0;
		BusOffResetTime=0;
	}

	J1939_ReceiveMessages();
	if(J1939_DequeueMessage(&OneMessage)==RC_SUCCESS)
	{
		if((OneMessage.FormatMsg.STDMSGID) == VCU_0)
		{
			VCU_CMD_0();
			LostCount = 0;
		}
		else if(OneMessage.FormatMsg.STDMSGID == VCU_2)
		{
			VCU_CMD_2();	
		}
		else if(OneMessage.FormatMsg.STDMSGID == VCU_4)
		{
			VCU_CMD_4();	
		}		
		else if(OneMessage.FormatMsg.STDMSGID == VCU_7)
		{
			VCU_CMD_7();
		}

		BusOffResetTime = 0;
		BusOffTime = 0;


	}



	if((VmsState == 12)||(VmsState == 82)||(VmsState == 142))		
	{
		EnNormalTrans = 1;
	}

	if(EnNormalTrans == 0)	
	{
		return;
	}
	else
	{
		//BootWaitTime= 0; 
		if(VmsState == 255)   EnNormalTrans = 0;
	}

	

	//Send msg
	{
		if((SendCount0+=ElapsedTime)>= 10)
		{
			MCU_RES0();
			if(4u == (Mcu_Configuration[1]&0x00ff))			
			MCU_RES15();			
			SendCount0 = 0;
		
		}

		if((SendCount3+=ElapsedTime)>= 100)
		{

			MCU_RES2();	
			MCU_RES3();
			MCU_RES5();	
			SendCount3 = 0;
		}

		if((SendCount1 +=ElapsedTime)>= 20)
		{

			MCU_RES1();
			SendCount1 = 0;
		}
		
		if((SendCount4+= ElapsedTime)>= 1000)
		{


			MCU_RES4();
			MCU_RES6();
			SendCount4 = 0;
		}
		if((SendCount5+= ElapsedTime)>= 5000)
		{
			MCU_RES7();
			MCU_RES8();
			MCU_RES9();
			MCU_RES10();
			SendCount5 = 0;
		}
		if((SendCount6+= ElapsedTime)>= 5000)
		{
			MCU_RES11();
			MCU_RES12();
			MCU_RES13();
			MCU_RES14();
			SendCount6 = 0;
		}
	}	
}


void J1939_ReceiveMessages( void )
{
	unsigned long	*RegPtr;
	unsigned char	RXBuffer;
	unsigned char	Loop;
	volatile Uint32 ShadowReg;

  for(RXBuffer = 16;RXBuffer <= 19;RXBuffer++)		
  {

	ShadowReg=ECanaRegs.CANRMP.all;

	if(ShadowReg&(0x0001L<<RXBuffer))
	{
		while(ShadowReg&(0x0001L<<RXBuffer))
		{
			ECanaRegs.CANRMP.all=(0x0001L<<RXBuffer);
			ShadowReg=ECanaRegs.CANRMP.all;

		}

		//Get CAN mailbox beginning address
		RegPtr = ((unsigned long *)&ECanaMboxes);
		//Round to the specific maibox
		RegPtr=RegPtr+4*RXBuffer;
		// Read a message from the mapped receive buffer.
		for (Loop=0; Loop<J1939_MSG_LENGTH; Loop++, RegPtr++)
			OneMessage.Array[Loop] = *RegPtr;
		if (OneMessage.FormatMsg.DataLength > 8)
			OneMessage.FormatMsg.DataLength = 8;


		if(RXQueueCount < J1939_RX_QUEUE_SIZE)
		{

			RXQueue[RXTail] = OneMessage;

			RXQueueCount ++;
			RXTail ++;
			if (RXTail >= J1939_RX_QUEUE_SIZE)	RXTail = 0;
	
		}
		else
		{
			//数据帧丢失，需要进一步处理
		}
					

	 }
  }
}


int J1939_DequeueMessage( J1939_MESSAGE *MsgPtr )
{
	int	rc = RC_SUCCESS;

	if (RXQueueCount == 0)
	{
		rc = RC_FAIL;
	}
	else
	{
		*MsgPtr = RXQueue[RXHead];
		RXHead ++;
		if (RXHead >= J1939_RX_QUEUE_SIZE)
			RXHead = 0;
		RXQueueCount --;
	}

	return rc;
}


void Request_VCU()
{
	McuState.bit.RequestVCU  = 0;

	if((CANError1.bit.PTSensor)||(CANError1.bit.IGBTU_Err)||(CANError1.bit.IGBTV_Err)
		||(CANError1.bit.IGBTW_Err))
	{
		McuState.bit.RequestVCU = R_REDUCE_POWER;
	}
	
	if((CANError1.bit.OverSpeed)||(CANError1.bit.IGBTU_OT)
		||(CANError1.bit.IGBTV_OT)||(CANError1.bit.IGBTW_OT)
		||(CANError1.bit.MotorOT)||(CANError1.bit.VMSTorqLimit))
	{
		McuState.bit.RequestVCU = R_ZERO_TORQUE;
	}

	if((CANError1.bit.DRVU)||(CANError1.bit.SOFT_OC)||(CANError1.bit.CurCheck)
		||(CANError1.bit.OU)||(CANError1.bit.LU)||(CANError1.bit.RESOLVE)
		||(CANError1.bit.LU_12V)||(CANError1.bit.OU_12V)||(CANError1.bit.UdcCheckErr)
		||((CANError1.bit.IGBTU_Err)&&(CANError1.bit.IGBTV_Err)&&(CANError1.bit.IGBTW_Err))
		||(CANError1.bit.Hard_OC)||(CANError1.bit.ErUCUR)||(CANError1.bit.Mul_Soft_OC)
		||(CANError1.bit.ErVCUR)||(CANError1.bit.ErWCUR))

	{
		McuState.bit.RequestVCU = R_DISABLE;		
	}


	if(CANError1.bit.VMSLost)
	{
		if(VmsLostDelay ++ > 100)
		{
			McuState.bit.RequestVCU = R_DISABLE;
			VmsLostDelay = 101;
		}
		else
		{
			McuState.bit.RequestVCU = R_ZERO_TORQUE;
			
		}
			
	}
	else
	{
		VmsLostDelay = 0;	
	}

}

void MCU_RES15()
{
	uint8_t MCU_CheckSum = 0;

	
	Speed = abs(MotorRealSpeed);
	if(MCUBeat>=16)	MCUBeat = 0;
	
	OneMessage.FormatMsg.DataLength = 8;
	
	OneMessage.FormatMsg.Data[0]  = MCUBeat;
	OneMessage.FormatMsg.Data[0]  = (OneMessage.FormatMsg.Data[0]<<8)&0x0F00u;
	if((ErrorList.bit.PGSignal))   
	{
		OneMessage.FormatMsg.Data[1]  = 0xFFFF; 		        //ERROE
		OneMessage.FormatMsg.Data[3] =  ((McuState.bit.State<<11)&0x1800) +0x40;
		
	}
	else                           
	{
		OneMessage.FormatMsg.Data[1]  = Swap(Speed+32768); 		// 1rpm
		OneMessage.FormatMsg.Data[3] =  (McuState.bit.State<<11)&0x1800;

	}
	OneMessage.FormatMsg.Data[2] =  Swap(CANTorqFed+32768);	


	MCU_CheckSum = (uint8_t)((OneMessage.FormatMsg.Data[0])>>8);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[1]&0xFF);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[1]>>8);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[2]&0xFF);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[2]>>8);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[3]&0xFF);
	MCU_CheckSum = MCU_CheckSum^(uint8_t)(OneMessage.FormatMsg.Data[3]>>8);

	OneMessage.FormatMsg.Data[0]  = (uint16_t)((MCU_CheckSum&0xFF)+(MCUBeat<<8));
	
	SendOneMessage(&OneMessage,27);

}


void MCU_RES0()
{

	//if(uRunStopStatus1.bit.PowerIsOK == 1)
	//{
		McuState.bit.InitState = 1;
	//}
	//else
	//{
	//	InitState = 0;
	//}


	Speed = abs(MotorRealSpeed);
	Speed = Speed<<2;		//0.25rpm


	if(uRunStopStatus1.bit.RunStatus == 1){
		if (Gear == DRIVE){

			if(MotorRealSpeed >=20)			//>-20rpm
			{
				McuState.bit.McuDir = 1;			//Fwd
			}
			else if(MotorRealSpeed <= -20)
			{
				McuState.bit.McuDir = 2;			//Rsv
			}
			
		}
		else if(Gear == REVERSE){
			if(MotorRealSpeed >=20)			//>20rpm
			{
				McuState.bit.McuDir = 1;			//Fwd
			}
			else if(MotorRealSpeed <= -20)
			{
				McuState.bit.McuDir = 2;			//Rsv
			}
			
		}
		else//N档和其他档位
		{
			if((MotorRealSpeed > -20)&&(MotorRealSpeed < 20))
			{
                if(Gear==NEUTRAL)  McuState.bit.McuDir = 0;			//void
                else               McuState.bit.McuDir = 1;         //Fwd
				Speed = 0;
			}
			else
			{
				if(MotorRealSpeed>0)		McuState.bit.McuDir = 1;			//Fwd
				else						McuState.bit.McuDir = 2;			//Rsv
			}
				
		}
	}
	else
	{
		McuState.bit.McuDir = 0;				//待机
	}


	
	if(uRunStopStatus1.bit.RunStatus == 1)
	{

		if(VCUCommand == 2)		//发电状态
		{
			if ((McuState.bit.McuDir==1)&&(Param_IqSetLimited < 0)		//TorqReal Unit 0.001Nm 	
			||(McuState.bit.McuDir == 2)&&(Param_IqSetLimited > 0))
			{
				McuState.bit.State = 2;		//发电状态
			}
			else if ((McuState.bit.McuDir==1)&&(Param_IqSetLimited >= 0)		//TorqReal Unit 0.001Nm 	
			||(McuState.bit.McuDir == 2)&&(Param_IqSetLimited <= 0))

			{
				McuState.bit.State = 1;		//驱动
			}
		}
		else 				//驱动状态和其他状态
		{
			if ((McuState.bit.McuDir==1)&&(Param_IqSetLimited < 0)		
				||(McuState.bit.McuDir == 2)&&(Param_IqSetLimited > 0))
			{
				McuState.bit.State = 2;		//发电状态
			}
			else if ((McuState.bit.McuDir==1)&&(Param_IqSetLimited >= 0)		//TorqReal Unit 0.001Nm 	
			||(McuState.bit.McuDir == 2)&&(Param_IqSetLimited <= 0))
			{
				McuState.bit.State = 1;		//驱动				
			}
		}
		if(McuState.bit.State==0)
			McuState.bit.State=1;	

		if((Gear==NEUTRAL)&&(labs(CANTorq)<10)&&(abs(MotorRealSpeed)<20))  //0.2Nm
			McuState.bit.State=0;
		
	}
	else
	{
		McuState.bit.State = 0;
	}

	if(UCoreCmd.bit.CtlMode == TORQUE_CTRL)	//Torque Mode
	{
      if((ReverseForbid == 1)||(ForwardForbid == 1)) 
      	{
		    McuState.bit.McuMode = 0x02;  //speed
	    }
	  else
	  	{
            McuState.bit.McuMode = 0x01; 
	    }
		 
	}
	else if(UCoreCmd.bit.CtlMode == SPEED_CTRL)
	{
		McuState.bit.McuMode = 0x02;	
	}
	else
	{
		McuState.bit.McuMode = 0x03;			
	}


	if(DCBUS_TEST_OK == InvStatus)	McuState.bit.HighVolOK = 1;
	else	McuState.bit.HighVolOK = 0;
	


	Request_VCU();

	if((47 == VmsState) ||(127 == VmsState)||(187 == VmsState))
	{
		if(++PowerOff12VDelay>2)
		{
			McuState.bit.RequestPowerOff12V = 1;
		}
		else
		{
			McuState.bit.RequestPowerOff12V = 0;
		}
	}
	else
	{
		PowerOff12VDelay = 0;
		McuState.bit.RequestPowerOff12V = 0;
	}

	McuState.bit.Rsv1 = 0;
	McuState.bit.Rsv2 = 0;	
	
	MCUBeat++;
	if(MCUBeat>=16)	MCUBeat = 0;
	
	OneMessage.FormatMsg.DataLength = 8;	
	OneMessage.FormatMsg.Data[0]  = McuState.data;
	if((ErrorList.bit.PGSignal))   OneMessage.FormatMsg.Data[1]  = 0xFFFF; 		        //ERROE
	else                           OneMessage.FormatMsg.Data[1]  = Swap(Speed); 		//0.25 rpm
	OneMessage.FormatMsg.Data[2] =  Swap(CANTorqFed);
	if(4u == (Mcu_Configuration[1]&0x00ff))
	{	
		OneMessage.FormatMsg.Data[1]  = 0u;
		OneMessage.FormatMsg.Data[2]  = 0u;
	}	
	OneMessage.FormatMsg.Data[3] =  MCUBeat;
	SendOneMessage(&OneMessage,0);

	Funcode.MCUState.value = McuState.data;

}

void MCU_RES1()
{
  uint16  OutputCurr_Can;		// 输出电流(单位：0.1A)

	OneMessage.FormatMsg.DataLength = 8;
	if(CANError1.bit.UdcCheckErr)
		OneMessage.FormatMsg.Data[0]  = Swap(0xffff);
	else
	    OneMessage.FormatMsg.Data[0]  = Swap(VoltDC*50);	//0.02V
	OneMessage.FormatMsg.Data[1]  = Swap(Funcode.DCCur.value); 			//DC Current 0.01A

	if (UCoreCmd.bit.RunStopCmd == 0)  OutputCurr_Can = 0U;
	else                               OutputCurr_Can = OutputCurr;

	if(CANError1.bit.ErUCUR)
		{OneMessage.FormatMsg.Data[2] = 0xFFFF;}
	else
		{OneMessage.FormatMsg.Data[2] =  Swap(abs(OutputCurr_Can*10));}	//0.01A
		
	OneMessage.FormatMsg.Data[3] =  0;
	
	SendOneMessage(&OneMessage,1);
}




void MCU_RES2()
{
	uint16 TorqRealLimit;
	TorqRealLimit = MaxTorqueEnable*5;

	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = Swap(TorqRealLimit);	
	OneMessage.FormatMsg.Data[1]  = Swap(TorqRealLimit); 			
	OneMessage.FormatMsg.Data[2] =  0;	
	OneMessage.FormatMsg.Data[3] =  0;
	
	SendOneMessage(&OneMessage,2);
}

void MCU_RES3()
{
	OneMessage.FormatMsg.DataLength = 8;
	if((1==WarningCode.bit.IGBTTempSensor)||(1==WarningCode.bit.IGBTVTempSensor)
		||(1==WarningCode.bit.IGBTWTempSensor))
		{OneMessage.FormatMsg.Data[0] = 0xFF00;}
	else
		{OneMessage.FormatMsg.Data[0]  = Swap(Funcode.MCUTemp.value-452);}			//200-48	
	if(CANError1.bit.PTSensor)
		{OneMessage.FormatMsg.Data[1] = 0x00FF;}
	else
		{OneMessage.FormatMsg.Data[1]  = (Funcode.MotorTemp.value-452) + 0xFF00;} 			//500 - 48;
		
		
	
	OneMessage.FormatMsg.Data[2] = 0x00;	
	OneMessage.FormatMsg.Data[3] = 0x00;

	SendOneMessage(&OneMessage,3);	
}

void MCU_RES4()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = 0x0b;			//200-48		
	OneMessage.FormatMsg.Data[1]  = 0; 			//500 - 48;
	OneMessage.FormatMsg.Data[2] =  0;	
	OneMessage.FormatMsg.Data[3] =  0;


	SendOneMessage(&OneMessage,25);	
}



void MCU_RES5()
{
  uint16 i,j;

	CANError1.all[0] = 0;
	CANError1.all[1] = 0;
	CANError1.all[2] = 0;
	
//------------Get CANError from Error,Alaram,Warn-------------------------------------//

	if(ErrorList.bit.Over12V)
	{	
		CANError1.bit.OU_12V = 1;
	}
	else if(ErrorList.bit.Low12V)		
	{
		CANError1.bit.LU_12V = 1;
	}
	else
	{

		if((ErrorList.bit.PGSignal))
			{CANError1.bit.RESOLVE = 1;}
		else
			{CANError1.bit.OverSpeed = AlarmCode.bit.OvSpeed;}
			

		if((ErrorList.bit.Soft_OC)&&(0 == CANError1.bit.RESOLVE)
			&&(0 == ErrorList.bit.CurU)&&(0 == ErrorList.bit.CurW)&&(0 == ErrorList.bit.CurV))
			CANError1.bit.SOFT_OC = 1;

		if((ErrorList.bit.DRV))
			CANError1.bit.DRVU = 1;

			CANError1.bit.ErUCUR = ErrorList.bit.CurU;

			CANError1.bit.ErVCUR = ErrorList.bit.CurV;

			CANError1.bit.ErWCUR = ErrorList.bit.CurW;
 
			CANError1.bit.OU     = ErrorList.bit.OU;
		
			CANError1.bit.LU     = ErrorList.bit.LU;

			if(0 == WarningCode.bit.IGBTTempSensor)
			{CANError1.bit.IGBTU_OT = AlarmCode.bit.U_OT | ErrorList.bit.MCUOH;}

            if(0 == WarningCode.bit.IGBTVTempSensor)
			{CANError1.bit.IGBTV_OT = AlarmCode.bit.V_OT;}

			if(0 == WarningCode.bit.IGBTWTempSensor)
			{CANError1.bit.IGBTW_OT = AlarmCode.bit.W_OT;}
		
			CANError1.bit.IGBTU_Err =  WarningCode.bit.IGBTTempSensor;

			CANError1.bit.IGBTV_Err =  WarningCode.bit.IGBTVTempSensor;

			CANError1.bit.IGBTW_Err =  WarningCode.bit.IGBTWTempSensor;

			CANError1.bit.PTSensor  =  WarningCode.bit.PTSensor;

			if(0 == CANError1.bit.PTSensor)
				{CANError1.bit.MotorOT	= AlarmCode.bit.MotorOT;}
			

			CANError1.bit.VMSTorqErr = 0;
			
			CANError1.bit.VMSTorqLimit = AlarmCode.bit.VMSTorqLimit;

			CANError1.bit.VMSLost = AlarmCode.bit.VMSLost;

			CANError1.bit.EEPROM =  WarningCode.bit.EEp|ErrorList.bit.EEP;

           if((0==CANError1.bit.ErUCUR)&&(0==CANError1.bit.ErWCUR)&&(0==CANError1.bit.ErVCUR))
           	{CANError1.bit.CurCheck = ErrorList.bit.CurCheck;}

		   CANError1.bit.UdcCheckErr = ErrorList.bit.VdcCheck;
		   CANError1.bit.Hard_OC = ErrorList.bit.Hard_OC;
		   CANError1.bit.Mul_Soft_OC = ErrorList.bit.Mul_Soft_OC;	
				
	}


//------------------------VmsState  Filiter------------------------------------------------//	
	{
	if((VmsState ==12)||(VmsState ==14)||(VmsState ==17)||(VmsState ==20)
		||(VmsState ==23)||(VmsState ==28)||(VmsState ==30)||(VmsState ==35)
		||(VmsState ==40)||(VmsState ==41)||(VmsState ==44)||(VmsState ==46)
		||(VmsState ==82)||(VmsState ==84)||(VmsState ==87)||(VmsState ==90)
		||(VmsState ==93)||(VmsState ==100)||(VmsState ==110)||(VmsState ==115)
		||(VmsState ==120)||(VmsState ==121)||(VmsState ==124)||(VmsState ==126)
		||(VmsState ==142)||(VmsState ==143)||(VmsState ==144)||(VmsState ==147)
		||(VmsState ==150)||(VmsState ==153)||(VmsState ==170)||(VmsState ==175)
		||(VmsState ==180)||(VmsState ==181)||(VmsState ==184)||(VmsState ==185)
		||(VmsState ==186))
	{
		
	}
	else
	{
		CANError1.bit.OU_12V = 0;
		CANError1.bit.LU_12V = 0;
		CANError1.bit.Err_12V = 0;
	}
	

	if((VmsState ==23)||(VmsState ==28)||(VmsState ==30)||(VmsState ==35))
	{
	
	}
	else
	{
		CANError1.bit.DRVU = 0;			//01
		CANError1.bit.Hard_OC = 0;
		CANError1.bit.Mul_Soft_OC = 0;
		
		CANError1.bit.SOFT_OC = 0;		//02

		CANError1.bit.OverSpeed = 0;	//03

		CANError1.bit.OU = 0;

		CANError1.bit.VMSTorqLimit = 0;	
		
		CANError1.bit.VMSTorqErr = 0;

		CANError1.bit.CurCheck = 0;
		
	}


	if((VmsState ==23)||(VmsState ==28)||(VmsState ==30))
	{
	
	}
	else
	{
		CANError1.bit.LU = 0;				
	}



	if(((VmsState ==12)||(VmsState ==14)||(VmsState ==17)||(VmsState ==20)
		 ||(VmsState ==23)||(VmsState ==28)||(VmsState ==30)||(VmsState ==35)
		 ||(VmsState ==40)||(VmsState ==41)||(VmsState ==44)||(VmsState ==46)))
		 
	{
	
	}
	else
	{
		CANError1.bit.IGBTU_OT = 0;
		CANError1.bit.IGBTV_OT = 0;
		CANError1.bit.IGBTW_OT = 0;
		CANError1.bit.MotorOT = 0;
		CANError1.bit.RESOLVE = 0;
		CANError1.bit.IGBTU_Err = 0;
		CANError1.bit.IGBTV_Err = 0;
		CANError1.bit.IGBTW_Err = 0;
		CANError1.bit.PTSensor = 0;
		CANError1.bit.VMSLost = 0; 		
		CANError1.bit.UdcCheckErr = 0;
	}



	if(VmsState ==12)
	{


	}
	else
	{
		CANError1.bit.ErUCUR = 0;
		CANError1.bit.ErWCUR = 0;
		
	}

	
	if((VmsState ==11)||(VmsState ==81)||(VmsState ==141)
		||(VmsState == 12)||(VmsState == 82)||(VmsState == 142))
	{	
	}
	else
	{
		CANError1.bit.EEPROM = 0;
	}
	
 	
	}

    err_num = 0;
	for(i=0;i<3;i++)
    {  
      for(j=0;j<16;j++)
      {
        if(CANError1.all[i]&(0x01L<<j))   err_num++; 
	  }	 
	}

	//if(CANError1.all[0]||CANError1.all[1]||CANError1.all[2])  err_num=1;

	CANErrorUpdate++;

	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = CANError1.all[0];			
	OneMessage.FormatMsg.Data[1]  = CANError1.all[1]; 			
	OneMessage.FormatMsg.Data[2] =  CANError1.all[2];	
	OneMessage.FormatMsg.Data[3] =  0;
	
	SendOneMessage(&OneMessage,5);
	

	
}



void MCU_RES6()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = Swap(MCUCALVER);				
	OneMessage.FormatMsg.Data[1]  = Swap(MCUIDH); 				
	OneMessage.FormatMsg.Data[2] =  Swap(MCUIDL);	
	OneMessage.FormatMsg.Data[3] =  Swap(MCUVER);


	SendOneMessage(&OneMessage,6);		
}

void MCU_RES7()
{
   	err_level = 0;

	if(err_num != 0)
	{
		if (ErrorList.all != 0) 	   err_level = 3;
        else if(AlarmCode.all!= 0)     err_level = 2;
        else                           err_level = 1;
	}
           
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = 0x0101;				
	OneMessage.FormatMsg.Data[1]  = (err_level<<8) + err_num; 				
	OneMessage.FormatMsg.Data[2] =  0;	
	OneMessage.FormatMsg.Data[3] =  0;
	SendOneMessage(&OneMessage,12);		
}

void MCU_RES8()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = (((uint)MotCode[1])<<8)+MotCode[0];				
	OneMessage.FormatMsg.Data[1]  = (((uint)MotCode[3])<<8)+MotCode[2]; 				
	OneMessage.FormatMsg.Data[2]  = (((uint)MotCode[5])<<8)+MotCode[4];	
	OneMessage.FormatMsg.Data[3]  = (((uint)MotCode[7])<<8)+MotCode[6];
	SendOneMessage(&OneMessage,13);		
}

void MCU_RES9()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = (((uint)MotCode[9])<<8)+MotCode[8];				
	OneMessage.FormatMsg.Data[1]  = (((uint)MotCode[11])<<8)+MotCode[10]; 				
	OneMessage.FormatMsg.Data[2] =  (((uint)MotCode[13])<<8)+MotCode[12];	
	OneMessage.FormatMsg.Data[3] =  (((uint)MotCode[15])<<8)+MotCode[14];
	SendOneMessage(&OneMessage,14);		
}

void MCU_RES10()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = (((uint)MotCode[17])<<8)+MotCode[16];				
	OneMessage.FormatMsg.Data[1]  = (((uint)MotCode[19])<<8)+MotCode[18]; 				
	OneMessage.FormatMsg.Data[2] =  (((uint)MotCode[21])<<8)+MotCode[20];	
	OneMessage.FormatMsg.Data[3] =  (((uint)MotCode[23])<<8)+MotCode[22];
	SendOneMessage(&OneMessage,20);		
}
void MCU_RES11()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = (((uint)MotCode[25])<<8)+MotCode[24];				
	OneMessage.FormatMsg.Data[1]  = (((uint)MotCode[27])<<8)+MotCode[26]; 				
	OneMessage.FormatMsg.Data[2] =  (((uint)MotCode[29])<<8)+MotCode[28];	
	OneMessage.FormatMsg.Data[3] =  0;
	SendOneMessage(&OneMessage,23);		
}

void MCU_RES12()
{
	OneMessage.FormatMsg.DataLength = 8; 
	OneMessage.FormatMsg.Data[0]  = (((uint)VIN[1])<<8)+VIN[0];				
	OneMessage.FormatMsg.Data[1]  = (((uint)VIN[3])<<8)+VIN[2]; 				
	OneMessage.FormatMsg.Data[2] =  (((uint)VIN[5])<<8)+VIN[4];	
	OneMessage.FormatMsg.Data[3] =  (((uint)VIN[7])<<8)+VIN[6];
	SendOneMessage(&OneMessage,29);		
}

void MCU_RES13()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = (((uint)VIN[9])<<8)+VIN[8];				
	OneMessage.FormatMsg.Data[1]  = (((uint)VIN[11])<<8)+VIN[10]; 				
	OneMessage.FormatMsg.Data[2] =  (((uint)VIN[13])<<8)+VIN[12];	
	OneMessage.FormatMsg.Data[3] =  (((uint)VIN[15])<<8)+VIN[14];
	SendOneMessage(&OneMessage,30);		
}
void MCU_RES14()
{
	OneMessage.FormatMsg.DataLength = 8;
	OneMessage.FormatMsg.Data[0]  = VIN[16];				
	OneMessage.FormatMsg.Data[1]  = 0; 				
	OneMessage.FormatMsg.Data[2] =  0;	
	OneMessage.FormatMsg.Data[3] =  0; 
	SendOneMessage(&OneMessage,31);	
}

//Byte 0 Define
//  bit0:	MCU使能		0:Disable	1:Enable
//	Bit1-2:	电机状态命令		0：待机		1：电动		2：发电		3：Void
//	Bit3-4:	工作模式命令		0：待机		1：转矩		2：转速		3: void
//	Bit5-6:	旋转方向		0:待机		1：正转		2：反转		3：Void
//	Bit7：	Void

//Byte 2-3 SpeedRef , 0.25rpm
//Byte 4-5 TorqueRef, 0.02Nm


//Drive 10Nm FWD
//2B 00 00 00 01 F4 00 00 		;	2B MCU Enable,Drive State,Torque Mode,FWD
//								;	0x 1F4 = 500 = 10Nm/0.02;

//Brake 10Nm FWD
//2D 00 00 00 01 F4 00 00		;	2D MCU Enable,Brake State,Torque Mode,FWD

//Drive 10Nm REV
//4B 00 00 00 01 F4 00 00 		;	4B MCU Enable,Drive State,Torque Mode,FWD
//								;	0x 1F4 = 500 = 10Nm/0.02;

//Brake 10Nm REV
//4D 00 00 00 01 F4 00 00		;	4D MCU Enable,Brake State,Torque Mode,FWD



//Drive 100Rpm FWD
//33 00 01 90 00 00 00 00 		;	33 MCU Enable,Drive State,Speed Mode,FWD
//								;	0x 190 = 400 = 100Rpm/0.25;


//Drive 100Rpm REV
//53 00 01 90 00 00 00 00 		;	53 MCU Enable,Drive State,Speed Mode,REV
//								;	0x 190 = 400 = 100Rpm/0.25;

void VCU_CMD_0()
{
	if(((Mcu_Configuration[1]&0x00ff)==0x04u)||((Mcu_Configuration[1]&0x00ff)==0x02u))
	{
		MCUEnable = OneMessage.FormatMsg.Data[0]&0x01;
	}
	else
	{
		MCUEnable = 0;
	}

	VCUCommand = (OneMessage.FormatMsg.Data[0]>>1)&0x03;
	CtrlMode  = (OneMessage.FormatMsg.Data[0]>>3)&0x03;
	CANDirect = (OneMessage.FormatMsg.Data[0]>>5)&0x03;
	
	if(MCUEnable == 0x00)	//Disble MCU
	{
		uRunStopCmd5.bit.CommCardCmd = 0;
		CANRequestTorque = 0;
		CANRequestTorque1 = 0;
		CANControlMode = 0x01;
		CANRequestFreq = 0;
	}
	if(MCUEnable == 0x01)	//Enable MCU
	{
		if(0x01 == CtrlMode)	//Torque
		{
			CANTorq = Swap(OneMessage.FormatMsg.Data[2]);

			if((Funcode.TorqRefChannel.value == 5)
				&&(ErrorList.bit.Over12V==0)&&(ErrorList.bit.Low12V==0))
			{
				if(VCUCommand == 1 )		//Drive
				{	
					if(CANTorq > DriveTorqLimit)
					{
						if(TorqLimitCount1++>10)	AlarmCode.bit.VMSTorqLimit = 1;
							
					}
					else
					{
						TorqLimitCount1 = 0;
						TorqLimitCount2 = 0;						
					}
				}
				else if(VCUCommand == 2 )	//GEN
				{
					if(CANTorq > GenTorqLimit)				
					{
						if(TorqLimitCount2++>10)	AlarmCode.bit.VMSTorqLimit = 1;
							
					}
					else
					{
						TorqLimitCount1 = 0;
						TorqLimitCount2 = 0;						
					}				
				}
			}
			else
			{
				AlarmCode.bit.VMSTorqLimit = 0;
				TorqLimitCount1 = 0;
				TorqLimitCount2 = 0;
			}


			//FWD or RSV
			if(CANDirect == 1)	//FWD
			{
				uRunStopCmd5.bit.CommCardCmd = 1;
				if(VCUCommand == 2 )		//发电状态
				{
					CANTorq = - CANTorq;
				}
				else if((VCUCommand == 0)||(VCUCommand == 3))	//待机状态和void
				{
					CANTorq = 0;
				}
				else					//驱动状态
				{
					
				}
				
			}
			else if(CANDirect == 2)	//RSV
			{
				uRunStopCmd5.bit.CommCardCmd = 2;

				if(VCUCommand == 2 )		//发电状态
				{
					CANTorq =  CANTorq;
				}
				else if((VCUCommand == 0)||(VCUCommand == 3))	//待机状态和void
				{
					CANTorq = 0;
				}
				else					//驱动状态
				{
					CANTorq = - CANTorq;					
				}


				
			}
			else	//待机模式或者 void--执行零转矩
			{
                uRunStopCmd5.bit.CommCardCmd = 1;
				CANTorq = 0;
			}		

			if((35 == VmsState)||(30 == VmsState))
			{
				CANRequestTorque1 = DV3232_32(CANTorq, 20000L, MotorNomTrq);
			}
			else
			{
				CANRequestTorque1 = 0;
			}
			//MotorNomTrq		0.001Nm
			//CANTorq			0.02 Nm
			//CANRequestTorque  0.1%
			CANControlMode = 0x01;
			
		}

		else		//待机  零转矩
		{
				uRunStopCmd5.bit.CommCardCmd = 1;
				CANRequestTorque = 0;
				CANRequestTorque1 = 0;
				CANControlMode = 0x01;				
		}
	}





}

void VCU_CMD_2()
{	

	isBrake = 	(OneMessage.FormatMsg.Data[2]>>5)&0x01;//制动信号(1 = Enable)
		
	NoSlide = 	(OneMessage.FormatMsg.Data[2]>>7)&0x01;//防止溜坡功能使能(1==Enable)

	GeraErr =   (OneMessage.FormatMsg.Data[2]>>6)&0x01;//档位故障(1 == Fault)

}


void VCU_CMD_4()
{
	VcuGearGet 	= 	(OneMessage.FormatMsg.Data[2]>>2)&0x07;//档位 0-Void； 1-P档； 2-N档； 3-R档； 4-D档； 5-L档； 6-E档； 7-Invalid；

	if((ECONOMY == VcuGearGet)||(SPORT == VcuGearGet))	{Gear = DRIVE;}
	else	{Gear = VcuGearGet;}
	
}



void VCU_CMD_7()
{

	VmsState = Swap(OneMessage.FormatMsg.Data[0]);


	if((12==VmsState)||(82==VmsState)||(142==VmsState))
	{
		InvStatus = SEFT_TEST_OK;
	}

	if((23==VmsState)||(90==VmsState)||(143==VmsState))
	{
		InvStatus = DCBUS_TEST_OK;		
	}

	if((46==VmsState)||(126==VmsState)||(186==VmsState))
	{
		InvStatus = SEFT_TEST_OK;
	}

	if((VmsState == 48)||(VmsState == 128)||(VmsState == 148))
	{
		InvStatus = INV_12V_OFF;
	}

	if((VoltDC <= 36))
	{
        EnableDischarge = 0;
	}

	if(((VmsState==12)||(VmsState==14)||(VmsState==17)||(VmsState==20)))
	{
		EnableDischarge = 0;
	}


}



void Diagnosis_Res1()	//200
{


	OneMessage.FormatMsg.DataLength = 8;	

	OneMessage.FormatMsg.Data[0]  = Swap(Param_IdSetLimited);	
	OneMessage.FormatMsg.Data[1]  = Swap(rlSpeedFed/10);
	OneMessage.FormatMsg.Data[2] =	Swap(Param_IqSetLimited);
	OneMessage.FormatMsg.Data[3] =	Swap(Param_IqAct);

	SendOneMessage(&OneMessage,24);	

}


/*void Diagnosis_Res2()	//201
{

	OneMessage.FormatMsg.DataLength = 8;	
	
	OneMessage.FormatMsg.Data[0]  = Swap(rlSpeedFedHigh/10);
	OneMessage.FormatMsg.Data[1]  = Swap(TorqComp1);
	OneMessage.FormatMsg.Data[2] =	Swap(Param_VdSet);
	OneMessage.FormatMsg.Data[3] =	Swap(Param_VqSet);

	SendOneMessage(&OneMessage,25);	
}*/


/*

void Diagnosis_Res3()	//202
{

	OneMessage.FormatMsg.DataLength = 8;	
	OneMessage.FormatMsg.Data[0]  = Swap(TrqSetTotal);
	OneMessage.FormatMsg.Data[1]  = Swap(DischargeCurrent);
	OneMessage.FormatMsg.Data[2] =  Swap(RunStep);
	OneMessage.FormatMsg.Data[3] =  Swap(ConVdcFlt);
	SendOneMessage(&OneMessage,26);	//202


}

*/


int SendOneMessage( J1939_MESSAGE *MsgPtr,int ch )
{

	union CANTRS_REG CANTRS;
	union CANTA_REG CANTA;
	struct MBOX  *RegPtr=((struct MBOX *)&ECanaMboxes);
	// Set up the final pieces of the message and make sure DataLength isn't
	// out of spec.
	RegPtr += ch;
	
	
	CANTRS.all=ECanaRegs.CANTRS.all;
	if(CANTRS.all&(0x01L<<ch))
		return 1;
	else
	{
		if (MsgPtr->FormatMsg.DataLength > 8)
			MsgPtr->FormatMsg.DataLength = 8;
		
					//load data length and 8 bytes
			RegPtr->MSGCTRL.bit.DLC=MsgPtr->FormatMsg.DataLength;					
			RegPtr->MDL.all=MsgPtr->Array[2];
			RegPtr->MDH.all=MsgPtr->Array[3];

			//CANTA.all=ECanaRegs.CANTA.all;
					
			//clear transimit acknowledge
			CANTA.all = ((Uint32)1 << ch);
			
			//start transmit
			CANTRS.all |= ((Uint32)1 << ch);	

			ECanaRegs.CANTA.all  = CANTA.all;
			ECanaRegs.CANTRS.all = CANTRS.all;
			return 0;
	}
}


void EcanIntHdl(void)
{                
	long temp,temp1;

		temp = ECanaRegs.CANES.all;
		temp1= ECanaRegs.CANMC.all;		 

		if(((temp&0x40000))||((temp1&0x1000)))//Bus---OFF
         {         								

				ECanaRegs.CANTA.all=ECanaRegs.CANTA.all;
				
				if(BusOffResetTime <10)
				{
					if(BusOffTime++>50)
					{
						EALLOW;
						ECanaRegs.CANES.all=temp;
						temp1=ECanaRegs.CANMC.all;
						temp1=(temp1&0xffffefff);
						ECanaRegs.CANMC.all = temp1 ;            		// Set CCR = 0*/
						EDIS;
					
						BusOffTime = 0;
						BusOffResetTime ++;
					}
				}
				else 
				{
					if(BusOffTime++>1000)
					{
						EALLOW;
						ECanaRegs.CANES.all=temp;
						temp1=ECanaRegs.CANMC.all;
						temp1=(temp1&0xffffefff);
						ECanaRegs.CANMC.all = temp1 ;            		// Set CCR = 0*/
						EDIS;
					
						BusOffTime = 0;
					}					
				}
		

         }
         else
         {
         			
                ECanaRegs.CANES.all=temp;
         }

//		 Funcode.DisPr1.value = temp;
//		 Funcode.DisPr2.value = temp>>16;

//		 Funcode.DisPr4.value = ECanaRegs.CANTEC.bit.TEC;
//		 Funcode.DisPr5.value = ECanaRegs.CANREC.bit.REC;	
}


int Swap(int inputdata)
{
	return(((inputdata>>8)&0xff)+(inputdata<<8));
}


void  EnNormComTx()
{
	if(VmsState != 0xFF)	
	EnNormalTrans = 1;	
}


void  DisNormComTx()
{
	EnNormalTrans = 0;		
}

uint8_t CheckProgramCondition()
{
	uint8_t ret;
	
	if (CheckedPreprogConditonFlg) {
	if((AlarmCode.bit.VMSLost == 1)||(COM_OVERTIME == 0)||(Funcode.TorqRefChannel.value != 5))
	{
		ret = (uint8_t)TRUE;
	}
	else if((ErrorList.bit.Low12V))//工装板5V供电
	{
		ret = (uint8_t)TRUE;
	}
	else	
	{
		
		if(VmsState == 255) ret = (uint8_t)TRUE;
		else				ret = (uint8_t)FALSE;
	}
	}
	else {
		ret = (uint8_t)FALSE;
	}

	return ret;
}


void Diagnosis_poll( unsigned int ElapsedTime )
{
	if((SendCount2 >= Funcode.CANDiaPeriod.value)&&(Funcode.CANAddress.value!=0))
	{
			Diagnosis_Res1();
		  //Diagnosis_Res2();
          //Diagnosis_Res3();
			SendCount2 = 0;
	}
	else
	{
		SendCount2 += ElapsedTime;	
	}

}

void Anti_Slip( unsigned int ElapsedTime1 )    //防溜坡处理函数   1ms  
{
	 CANRequestTorque = CANRequestTorque1;
/*  if((ReverseForbid != 0)||(ForwardForbid != 0))  //进入防溜坡模式
   {
	  //判断退出    CANTorq--0.02 Nm  TorqReal--0.001Nm a.0转速调速稳定后才进行切换判断 b.CANTorq>TorqReal+15
	  if((0==SlipQuit_flag)&&(labs(CANTorq)>labs(TorqReal/20))&&((1==ReverseForbid)||(1==ForwardForbid))&&(abs(MotorRealSpeed)<Funcode.SlipCutSpeed.value))
	    {
		   SlipQuit_flag = 1;
		   SlipQuit_Clear_Counter = 0;
	    }
      else if((0==SlipQuit_flag)&&(labs(CANTorq)>(labs(TorqReal/20)+750))&&((2==ReverseForbid)||(2==ForwardForbid)))
      	{
           SlipQuit_flag = 1;
		   SlipQuit_Clear_Counter = 0;
	    }
      //切换开始后1s判断切换标志位清零条件
	  if((1==SlipQuit_flag)&&(SlipCut_timer>=1000))
	   {
		 //切换后车继续溜，表明vcu给定力矩过小，退出切换
		  if(((ReverseForbid != 0)&&(MotorRealSpeed<-10))||((ForwardForbid != 0)&&(MotorRealSpeed>10)))
		   {
			  SlipQuit_Clear_Counter++;
			  if(SlipQuit_Clear_Counter >= 5)
			   {
				  SlipQuit_flag = 0;
				  SlipQuit_Clear_Counter = 0;
			   }
		   }
		  else
		   {
			  SlipQuit_Clear_Counter = 0;
		   }
	   }
      //开始切换？
	  if(1==SlipQuit_flag)
	   {
           SlipCut_timer++;
		   if(SlipCut_timer>=1000)   SlipCut_timer=1000; //1s
		   if(SlipCut_counter >= Funcode.SlipCutTime.value) //切换完成
		  	{
		  	   CANRequestTorque = CANRequestTorque1;
		  	}
		   else
		  	{
              CANRequestTorque=DV3232_32((int32)CANRequestTorque1,SlipCut_counter,Funcode.SlipCutTime.value);
			  SlipCut_counter++;
		  	}
	   }
	  else
	   {
		   CANRequestTorque = 0;
		   SlipCut_counter = 0;
		   SlipQuit_Clear_Counter = 0;
		   SlipCut_timer = 0;
	   }
   }
  else
   {
           CANRequestTorque = CANRequestTorque1;
           SlipCut_counter = 0;                        //防溜坡切换计数器
           SlipQuit_flag = 0;
           SlipQuit_Clear_Counter = 0;
		   SlipCut_timer = 0;
   }*/
}

