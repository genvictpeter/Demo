//****************************************************************************/
// @Module       
// @Filename      Error.c
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

/****************************************************************************/


#include "FunctionManage.h"
#include "main.h"
#include "AsmAlgorithm_N.h"
#include "DriveLib.h"
#include "Ev72ctrl.h"
#include "const.h"
#include "FunctionManage_const.h"
#include "IOFunc.h"
#include "GlobalVariables.h"
#include "FunctionCode.h"
#include "KeyBoard_Extypes.h"
#include "DrivePublicVar.h"
#include "EepromManage.h"
#include "CANProtocal.h"
#define _ERROR_DEF_H_ 	1
#include "Error.h"
unsigned int CurrentErr;
unsigned int OutVolErr;
unsigned int VdcSensorErrCounter;

extern int Param_IdSetLimited,Param_IqSetLimited,Param_IdAct,Param_IqAct,ICoff;
extern Uint16 ClrInsideErr;
extern unsigned int Ibase;

Uint16 GenMcuState2(void);


void Init_Alarm(void)
{
	DelayLow12V = 0;
	DelayOv12V = 0;
	AlarmCode.all = 0;
	AlarmCodeBak.all = 0;
	WarningCode.all = 0;
	WarningCodeBak.all = 0;
	ErrorList.all = 0;
	LuDetectCount = 0;
	PG2Count = 0;
}



void Init_Error(void)
{
	OvSpeedTime = 0;	
	ErrorCode = ErrNONE;
	ErrorCodeBak = ErrNONE;
	LogWrite = 0;
	LogRead = 0;

	ConPowerIsOK = 0;
	PowerIsOK = 0;
	PG1Count = 0;
	ErrorListIndex = 0;
	CurrentErr = 0;
	VdcSensorErrCounter = 0;

	Init_Alarm();


}




void FuncManage_Error(void )  //1ms
{
	FuncManage_DetectErr();
	
	Error_ErrClass();


	FuncManage_AssertErr();

	if(ErrorCodeBak != ErrorCode)
	{
		PushErrInfo(ErrorListIndex);
		FuncManage_RecordErr();
	}
	ErrorCodeBak = ErrorCode;
	
}

void FuncManage_DetectErr(void)
{
	//Drv interrupt
	HardwareFault();	
		
	//OC in 125us
		
	FuncManage_PowerDetect();

	if((ErrorList.bit.Over12V)||(ErrorList.bit.Low12V))
	{
		return;
	}
	
	FuncManage_OtDetect();	
		
	ResolverCheck();	//PG1 in Pwn interrupt

	//gcw debug 20160907
	TorqErrCheck( );	
    VdcSensorCheck( );      //直流母线电压采样回路检测
    
	
	//Er.Curu &CurW in 125us
	//Er.EEP at power start
	
	FuncManage_ExFaultDetect();	

	FuncManage_TuneDetect();

	if(Funcode.MaxOutFrq.value == 0) ErrorList.bit.ParaSet = 1;

	
}


void Detect_Alaram(void)
{
	if((ErrorList.bit.Over12V)||(ErrorList.bit.Low12V))
	{
		AlarmCode.all = 0;
		return;
	}
	

	AutoOverSpeedDetect();

//-----------------MCU_OT_ALRAM--------------------------------------------//

	if(WarningCode.bit.IGBTTempSensor)
	{
		AlarmCode.bit.U_OT = 0;
	}
	else
	{
		if(TemperURealFlt >= Funcode.WarnMCUOT.value) 
		{
			AlarmCode.bit.U_OT = 1;
		}
		else if(TemperURealFlt <= (Funcode.WarnMCUOT.value - 5))
		{
			AlarmCode.bit.U_OT = 0;
		}
		else
		{
			//keep State
		}
	}

	if(WarningCode.bit.IGBTVTempSensor)
	{
		AlarmCode.bit.V_OT = 0;
	}
	else
	{
		if(TemperVRealFlt >= Funcode.WarnMCUOT.value) 
		{
			AlarmCode.bit.V_OT = 1;
		}
		else if(TemperVRealFlt <= (Funcode.WarnMCUOT.value - 5))
		{
			AlarmCode.bit.V_OT = 0;
		}
		else
		{
			//keep State
		}
	}

	if(WarningCode.bit.IGBTWTempSensor)
	{
		AlarmCode.bit.W_OT = 0;
	}
	else
	{
		if(TemperWRealFlt >= Funcode.WarnMCUOT.value) 
		{
			AlarmCode.bit.W_OT = 1;
		}
		else if(TemperWRealFlt <= (Funcode.WarnMCUOT.value - 5))
		{
			AlarmCode.bit.W_OT = 0;
		}
		else
		{
			//keep State
		}
	}

	//-----------------Motor_OT_ALRAM--------------------------------------------//

	if((WarningCode.bit.PTSensor))
	{
		AlarmCode.bit.MotorOT = 0;
	}
	else
	{
		if(Funcode.MotorTemp.value >= (500+Funcode.MotorOTLevel.value))
  		{
  			AlarmCode.bit.MotorOT = 1;
  		}
  		else if(Funcode.MotorTemp.value <= (495+Funcode.MotorOTLevel.value))
  		{
  			AlarmCode.bit.MotorOT = 0;

  		}
	}


	//-----------------CAN COM OVERTIME--------------------------------------------//
	if((COM_OVERTIME!=0)&&(Funcode.TorqRefChannel.value == 5)&&(Time1msBase>1000))
	{
		if(LostCount>COM_OVERTIME)
		{
			AlarmCode.bit.VMSLost  = 1;
		}
		else
		{
			LostCount += 4;	//4ms period
		}		
	}
	else
	{
		AlarmCode.bit.VMSLost  = 0;
	}
	
	//-----------------VMSTorqLimit check in VCU_CMD_0--------------------------------------------//



}


void Detect_Warn(void)
{
	if((ErrorList.bit.Over12V)||(ErrorList.bit.Low12V))
	{
		WarningCode.all = 0;
		return;
	}
	

	TempLineOpenDetect();



//-------------EEPROM--------------------------------//


//-----------------VMSTorqErr check --------------------------------------------//
	
			
//Update to Funcode

	Funcode.ErrorListH.value = (ErrorList.all)>>16;
	Funcode.ErrorListL.value =  ErrorList.all&0xFFFF;
	Funcode.AlarmCode.value =  AlarmCode.all;
	Funcode.WarnCode.value =  WarningCode.all;
	
}




void Error_ErrClass()	
{
	uint tmpIndex;
	if ((ErrorCode == ErrNONE)&&(ErrorCode1 == ErrNONE)&&(ErrorList.all != 0))
	{
		for(ErrorListIndex=0;ErrorListIndex<ErrorInfo_Size;ErrorListIndex++)
		{
			tmpIndex = ((ErrorList.all>>ErrorListIndex)&0x01);
			if(tmpIndex != 0)
			{
				ErrorCode1 = ErrorInfo[ErrorListIndex].KeyCode;
				break;
			}
		}

		if(ErLU == ErrorCode1)
		{
			if((VmsState ==23)||(VmsState ==28)||(VmsState ==30))	
			{
				ErrorCode1 = ErLU;	
			}
			else
			{
				ErrorCode1 = ErrNONE;	
			}
		}
		
	}
}

//故障处理
void FuncManage_AssertErr(void)
{
  ErrorStates ErrorCode1BK;
  ErrorCode1BK = ErrorCode1;


  if(ErrorCode1BK != 0)
  {
  		EALLOW;
		EPwm1Regs.TZFRC.bit.OST = 1;     // 强制OST, 封锁输出
		EPwm2Regs.TZFRC.bit.OST = 1;     // 强制OST, 封锁输出
		EPwm3Regs.TZFRC.bit.OST = 1;     // 强制OST, 封锁输出
		EDIS;	
	
    	ErrorCode = ErrorCode1BK;

  		ErrorCode1 = ErrNONE;
   
  }

}



void SetError(ErrorStates Code)
{
	if((ErrorList.bit.Over12V)||(ErrorList.bit.Low12V))
	{
		return;
	}

	if(ErEEPROM == Code)
	{
		if(InitFinish == 0)
		{
			ErrorList.bit.EEP = 1;
		}
		else
		{
			WarningCode.bit.EEp = 1;
		}
	}
	else if(ErCurU == Code)
	{
		ErrorList.bit.CurU = 1;		
	}
	else if(ErCurV == Code)
	{
		ErrorList.bit.CurV = 1;		
	}
	else if(ErCurW == Code)
	{
		ErrorList.bit.CurW = 1;		
	}
	else if(EroSoftOC == Code)
	{
		if((ErrorList.bit.CurU==0)&&(ErrorList.bit.CurW==0)&&(ErrorList.bit.CurV==0))	
		{
			if(SoftOCCount>=MAX_SOFT_OC)
			ErrorList.bit.Mul_Soft_OC = 1;
			else	
			ErrorList.bit.Soft_OC = 1;
		}
	}
	else if(ErDrv == Code)
	{
		if(HardOC == 0)
		{	
			ErrorList.bit.Hard_OC = 1;
		}
		else
		{
	    	ErrorList.bit.DRV = 1;	
		}
	}	

	else if(ErTune == Code)
	{
		ErrorList.bit.Tune = 1;
	}
	else if(ErCurCheck == Code)
	{
		ErrorList.bit.CurCheck = 1;	
	}
	else if(ErVdcCheck == Code)
	{
		ErrorList.bit.VdcCheck = 1;  
	}	
	else
	{
		ErrorList.bit.ParaSet = 1;
	}	
	
}


Uint16 GetErrorCode()
{
	return ErrorCode;
}


Uint16 isAlarmWarn()
{
	return (AlarmCode.all|WarningCode.all);
}
//***********************************************************************************************************************************
void HardwareFault(void)
{
	if (GpioDataRegs.GPADAT.bit.GPIO12 == 0)
	{
		if(HardOC == 0)
		{
			Funcode.AI2Volt.value = 1;
			ErrorList.bit.Hard_OC = 1;
		}
		else
		{
			Funcode.AI2Volt.value = 2;	
			ErrorList.bit.DRV = 1;	
		}
	}
}

//****************************************************************************************************************************
static void FuncManage_PowerDetect(void )
{

	
	if(ConVdcFlt >= Funcode.Over12V.value)
	{
		if(DelayOv12V++>100)
		{
			ConPowerIsOK = 0;
			ErrorList.bit.Over12V = 1;
		
		}
	}
	else
	{
		DelayOv12V = 0;
	}
	
	//Control Voltage 12V or 24V
	if(ConVdcFlt <= Funcode.Low12V.value)
	{
		if(DelayLow12V++>100)
		{
			ConPowerIsOK = 0;
			ErrorList.bit.Low12V = 1;
		}
	
	}
	else
	{
		DelayLow12V =0;
	}

	ConPowerIsOK = 1;
	

	if (VoltDC >= Funcode.DCOVLevel.value)
	{
		if((2 == VCUCommand)||(Funcode.TorqRefChannel.value != 5)||((VmsState>=40)&&(VmsState<=50))) 				//发电状态
		{
			ErrorList.bit.OU = 1;
			PowerIsOK = 0;
		}
  	}
	

	if (VoltDC < Funcode.DCLVLevel.value)				
	{
		if(LuDetectCount++>100)
		{
			if((VmsState ==23)||(VmsState ==28)||(VmsState ==30))
			{
				ErrorList.bit.LU = 1;
			}
			PowerIsOK = 0;
		}
	}
	else if (VoltDC > (Funcode.DCLVLevel.value + 5))		
	{
		PowerIsOK = 1;
		LuDetectCount = 0;
	}
	else
	{
		LuDetectCount = 0;
	}
	
}



static void FuncManage_OtDetect(void)
{
  {
      if(Funcode.MCUTemp.value >= (500+Funcode.MCUOT.value)) 
      {
          ErrorList.bit.MCUOH = 1;

      }
  }	
}


//**************************************************************************************************************************
// 旋变信号异常检出

void ResolverCheck()
{

	if ((ResolverInitOK == 1)&&(Funcode.PGSlt.value == RESOLVER))
	{

		if(PG1Count > 400)  
		{
			ErrorList.bit.PGSignal = 1;
		}
		else
		{

			ResAmpReal = sqrtu16((unsigned long)((long)Param_Enc1TrackA * (long)Param_Enc1TrackA) 
				       + (unsigned long)((long)Param_Enc1TrackB * (long)Param_Enc1TrackB));            // in Q15

			ResAmpError = abs(ResAmpReal - Funcode.ResolverAmpSet.value);  // 实测旋变幅值 - 设定的旋变幅值

			if (ResAmpError >= Funcode.ResolverCheckOut.value)        // 若大于检出门槛值
			{
				if(PG2ErrCount++>1000)
				{
					PG2ErrCount = 1000;
				}

			}
			else
			{
				//if(PG2ErrCount>0)		PG2ErrCount--;

			}	

			if(PG2Count++>400)		//400ms check 
			{
				
				if(PG2ErrCount>Funcode.ResolverCheckNumber.value)	{ErrorList.bit.PGSignal = 1;}
				else												{ErrorList.bit.PGSignal = 0;}	

				PG2ErrCount = 0;
				PG2Count = 0;
			}			
		}
	}	
}

void TorqErrCheck(void)
{
	if((labs(rlSpeedFed)*3<(MotorRatedFreq*10))&&(RunStep==8)&&(Funcode.TuneMode.value==0))
	{
		if((abs(Param_IdSetLimited-Param_IdAct)>=16L*ICoff)||(abs(Param_IqSetLimited-Param_IqAct)>=16L*ICoff))
		{
			if(CurrentErr<400)
				CurrentErr++;
			else
				SetError(ErCurCheck);
		}
		else
		{
				CurrentErr=0;
		}
    }
  else
	{
		CurrentErr=0;
	}
}

void VdcSensorCheck(void)  //母线电压检测回路检测
{
   if(((abs(SpeedRpm)<1000)&&((VoltDC>480)||(Udc1Flt>480)))||(abs(VoltDC-Udc1Flt)>50))
   	{
		if(VdcSensorErrCounter++>=400)
			{
               VdcSensorErrCounter = 400;
			   SetError(ErVdcCheck);			  
			}
    }
   else
   	{
        VdcSensorErrCounter = 0;
    }
}


//**************************************************************************************************************************
// 紧急复位故障
void FuncManage_ExFaultDetect(void)
{
	if (uControlCmd1.bit.EmergStop == 1) 
  	{
		ErrorList.bit.EFT = 1;
  	}
}



static void FuncManage_TuneDetect()
{
	if (SEARCH_INIT_ANGLE_FINISHED == 1)
	{
		if (Param_MotorSearchAngleStatus & 0x0010)   //  M_SEARCH_ANGLE_OK , 角度寻找成功标志
		{
			Funcode.SMIniAng.value = Param_MotorInitAngle;
			Funcode.SMIniAng.changed = 1;
		}
		if (Param_MotorSearchAngError == 4)  // 初始安装角学习失败
		{
			ErrorList.bit.Tune = 1;
		}
		Param_MotorSearchAngError = 0;		
		Funcode.TuneMode.value = 0;
		SEARCH_INIT_ANGLE_FINISHED = 0;
		uControlCmd1.bit.ForceStop = 1;
	}		
}








void FuncManage_ResetErr(void )
{

	if ((uControlCmd1.bit.RestErr == 1) || (ClrInsideErr == 1u))
	{

		//if((ErrorList.bit.DRV)||(ErrorList.bit.Hard_OC)||(ErrorList.bit.Soft_OC))
		{
			//No reset Error . Must Restart
		}
		//else
		{
			if(ErrorCode1 == ErrNONE)
			{
    			ErrorCode = ErrNONE;
				ErrorCodeBak = ErrNONE;
				ErrorListIndex = 0;
				ErrorList.all = 0;
			}
		}
			
		AlarmCode.all = 0u;
		AlarmCodeBak.all = 0u;
			
		WarningCodeBak.all = 0u;
		WarningCode.all = 0u;
	}
	
	uControlCmd1.bit.RestErr = 0;
	ClrInsideErr = 0u;
}

void CopyLogToFuncode(ErrorLog_t *Err)
{
 	FuncBits    *fpCopy; 
	uint i;

	fpCopy = &(Funcode.ErrorCode); 	

	for(i=0;i<SizeErrLog;i++)
	{
		fpCopy->value = Err->U16Data[i];
		fpCopy++;

	}
}

void FuncManage_RecordErr(void)
{	

	CopyLogToFuncode(&(ErrLog[LogWrite]));	
	
}





//**************************************************************************************************************************

//*****************************************************************************************************************************





static void TempLineOpenDetect(void)
{
#ifdef DEBUG_SIM

#else
	//IGBT温度传感器
	//短路
	if(AI_Sample.NTCU <65 )
	{
		UTempLinetime++;
		if (UTempLinetime > FuncManage_TempLinetime)
		{
			UTempLinetime = 0;
			TestWarn.bit.IGBTUShort = 1;
			TestWarn.bit.IGBTUOPEN = 0;
		}
	}
	else if(AI_Sample.NTCU > 4033 ) 
	{
		UTempLinetime++;
		if (UTempLinetime > FuncManage_TempLinetime)
		{
			UTempLinetime = 0;
			TestWarn.bit.IGBTUOPEN = 1;
			TestWarn.bit.IGBTUShort = 0;
		}	

	}
	else 
	{
		TestWarn.bit.IGBTUShort = 0;
		TestWarn.bit.IGBTUOPEN = 0;
		UTempLinetime = 0;
	}

	if(AI_Sample.NTCV <100 )
	{
		VTempLinetime++;
		if (VTempLinetime > FuncManage_TempLinetime)
		{
			VTempLinetime = 0;
			TestWarn.bit.IGBTVShort = 1;
			TestWarn.bit.IGBTVOPEN = 0;
		}
	}
	else if(AI_Sample.NTCV > 3800 ) 
	{
		VTempLinetime++;
		if (VTempLinetime > FuncManage_TempLinetime)
		{
			VTempLinetime = 0;
			TestWarn.bit.IGBTVOPEN = 1;
			TestWarn.bit.IGBTVShort = 0;
		}	

	}
	else 
	{
		TestWarn.bit.IGBTVShort = 0;
		TestWarn.bit.IGBTVOPEN = 0;
		VTempLinetime = 0;
	}

	if(AI_Sample.NTCW <100 )
	{
		WTempLinetime++;
		if (WTempLinetime > FuncManage_TempLinetime)
		{
			WTempLinetime = 0;
			TestWarn.bit.IGBTWShort = 1;
			TestWarn.bit.IGBTWOPEN = 0;
		}
	}
	else if(AI_Sample.NTCW > 3800 ) 
	{
		WTempLinetime++;
		if (WTempLinetime > FuncManage_TempLinetime)
		{
			WTempLinetime = 0;
			TestWarn.bit.IGBTWOPEN = 1;
			TestWarn.bit.IGBTWShort = 0;
		}	

	}
	else 
	{
		TestWarn.bit.IGBTWShort = 0;
		TestWarn.bit.IGBTWOPEN = 0;
		WTempLinetime = 0;
	}	
	
	if((TestWarn.bit.IGBTUOPEN||TestWarn.bit.IGBTUShort))
	{
		WarningCode.bit.IGBTTempSensor = 1;
	}
	else
	{
		WarningCode.bit.IGBTTempSensor = 0;		
	}

	if((TestWarn.bit.IGBTVOPEN||TestWarn.bit.IGBTVShort))
	{
		WarningCode.bit.IGBTVTempSensor = 1;
	}
	else
	{
		WarningCode.bit.IGBTVTempSensor = 0;		
	}

	if((TestWarn.bit.IGBTWOPEN||TestWarn.bit.IGBTWShort))
	{
		WarningCode.bit.IGBTWTempSensor = 1;
	}
	else
	{
		WarningCode.bit.IGBTWTempSensor = 0;		
	}


	//电机温度传感器断路

	if(AI_Sample.KTY <100 )
	{
		MotorTempLineTime++;
		if (MotorTempLineTime > FuncManage_TempLinetime)
		{
			MotorTempLineTime = 0;
			TestWarn.bit.PTShort = 1;
			TestWarn.bit.PTOPEN = 0;
		}
		MotorTempLineOKTime = 0;
	}
	else if(AI_Sample.KTY > 3800 ) 
	{
		MotorTempLineTime++;
		if (MotorTempLineTime > FuncManage_TempLinetime)
		{
			MotorTempLineTime = 0;
			TestWarn.bit.PTOPEN = 1;
			TestWarn.bit.PTShort = 0;
		}
		MotorTempLineOKTime = 0;

	}
	else 
	{	if(MotorTempLineOKTime++ > FuncManage_TempLinetime)
		{
	
			TestWarn.bit.PTShort = 0;
			TestWarn.bit.PTOPEN = 0;
			MotorTempLineTime = 0;
		}
	}

	if((TestWarn.bit.PTShort)||(TestWarn.bit.PTOPEN))
	{
		WarningCode.bit.PTSensor = 1;
	}
	else
	{
		WarningCode.bit.PTSensor = 0;		
	}
#endif	
}






//*****************************************************************************************************************************
/*void FuncManage_JdgOCTimes(void )
{
	uRunStopStatus6.bit.PreErrIsOC = uRunStopStatus6.bit.ErrIsOC;
  	if ((GetErrorCode() == 1U) || (GetErrorCode() == 2U) || (GetErrorCode() == 3U)) 
  	{ 
  		uRunStopStatus6.bit.ErrIsOC = 1;
  	} 
  	else 
  	{
    	uRunStopStatus6.bit.ErrIsOC = 0;
  	}
  	if ((uRunStopStatus6.bit.PreErrIsOC == 1) && (uRunStopStatus6.bit.ErrIsOC == 1)) 
  	{
    	OCTimes++;
    	OcTimer++;
  	} 
  	else 
  	{
    	OCTimes = 0;
    	OcTimer = 0U;
  	}
  	if (OcTimer > 60000U) 
  	{
    	OcTimer = 60000U;
  	}
  	if ((OCTimes > 3) && (!(OcTimer == 60000U))) 
  	{
    	OCTimes = 0;
    	OcTimer = 0U;
  	}	
}*/



void ResolverSignalCheck()
{
	if((ResolverInitOK==1)&&(Funcode.PGSlt.value == RESOLVER))
	{
		if((Resolver_Sin>=4090)||(Resolver_Cos>=4090))		
		{
			PG1Count++;
		}
		else
		{
			if(PG1Count>0)	PG1Count--;
		}
	}
	else
	{
		PG1Count = 0;
	}
}

void AutoOverSpeedDetect()
{

	if(ErrorList.bit.PGSignal)
	{
		AlarmCode.bit.OvSpeed = 0;
		return;
	}
	
	
	RevLimit = Funcode.MotorSpeedOVREV.value;
	RevLimit = - RevLimit;

	if((abs(SpeedRpm) >= Funcode.MotorSpeedOVFWD.value)||(SpeedRpm <= RevLimit))
	{
		if(OvSpeedTime >= 25)		AlarmCode.bit.OvSpeed = 1;
		else						OvSpeedTime++;
	}

	else if(1 == AlarmCode.bit.OvSpeed)
	{
		if((abs(SpeedRpm)<= (Funcode.MotorSpeedOVFWD.value-200))||(SpeedRpm >= (RevLimit+200)))
		{
			if(OvSpeedTime <= 0)			AlarmCode.bit.OvSpeed = 0;
			else							OvSpeedTime--;
		}

	}
	else	//(0xaa55 != OvSpeedFlag) &&(((abs(SpeedRpm) <= Funcode.MotorSpeedOVFWD.value)||(SpeedRpm >= RevLimit)))
	{

	
	}
}



//说明
//DID = 0x200 直流母线电流用 0xFF（无效）
//DID = 0x214,0x215,0x216  IGBT 温度都用ErrIGBTTemp;
//DID = 0x208 MCU温度不支持，用0xFF(无效)

static void PushErrInfo(Uint16  Code)
{
		ErrorLog_t *CurLog;
				
		LogWrite++;
		if(LogWrite >= MAX_LOG) LogWrite = 0;
		
	
		if(LogWrite == LogRead) 	return; //Buffer Fill
		
		//
        CANMotorCmd.Bit.CANDirect = CANDirect;
        CANMotorCmd.Bit.CtrlMode = CtrlMode;
        CANMotorCmd.Bit.MCUEnable = MCUEnable;

        //
        DriveState.Bit.isBrake = isBrake;
        DriveState.Bit.NoSlide = NoSlide;
        DriveState.Bit.VcuGearGet = VcuGearGet;
		
		
		CurLog = &(ErrLog[LogWrite]);
	
		CurLog->ErrLog.ErrorCode	 = Code;
		CurLog->ErrLog.ErrDCVoltage  = 50L * VoltDC;										// 1V --->0.02V
		CurLog->ErrLog.ErrTorqueCmd  = 32750+(CANTorq>>1);									// 0.02Nm--->0.04Nm
		CurLog->ErrLog.ErrTorqueFed  = 32750+(CANTorqRealDis>>17);							// 0.02Nm--->0.04Nm 		
		CurLog->ErrLog.ErrSpeedSet	 = ((CANSpeed * (int16)13653) >> 15) + 32767;			// 0.25rpm --->0.6rpm
		CurLog->ErrLog.ErrSpeed 	 = (((int32)MotorRealSpeed * (int16)13653) >> 13) + 32767;//1rpm---->0.6rpm    
		CurLog->ErrLog.ErrIGBTTemp	 = TemperRealFlt + 48;	 
		CurLog->ErrLog.ErrMotorTemp  = (Funcode.MotorTemp.value-452); 
		CurLog->ErrLog.ErrUd		 = abs(((long)Param_VdSet*Uphase)>>14) * 25 + 32750; 	// 1V ---> 0.04v
		CurLog->ErrLog.ErrUq		 = abs(((long)Param_VqSet*Uphase)>>14) * 25 + 32750; 	// 1V ---> 0.04v					
		CurLog->ErrLog.ErrIdRef 	 = ((abs(((long)Param_IdSetUnlim*Imax)>>14) * 5L) >> 1) + 32750;  //0.1A ---> 0.04A 
		CurLog->ErrLog.ErrIqRef 	 = ((abs(((long)Param_IqSetUnlim*Imax)>>14) * 5L) >> 1) + 32750;  //0.1A ---> 0.04A
		CurLog->ErrLog.ErrIdFed 	 = ((abs(((long)Param_IdAct*Imax)>>14) * 5L) >> 1) + 32750;		 //0.1A ---> 0.04A
		CurLog->ErrLog.ErrIqFed 	 = ((abs(((long)Param_IqAct*Imax)>>14) * 5L) >> 1) + 32750;		 //0.1A ---> 0.04A
		CurLog->ErrLog.Err12V		 = ((int32)ConVdcFlt * 13653) >> 14;					//0.1V--->0.12V
		CurLog->ErrLog.ErrState 	 = VmsState;
		CurLog->ErrLog.ErrMotorModeCmd	= (Uint8)(CANMotorCmd.Word);
		CurLog->ErrLog.ErrDriveState	= (Uint8)(DriveState.Word);
		CurLog->ErrLog.ErrMCUState		= GenMcuState2();
		CurLog->ErrLog.Angle			= (85L*360L*Param_Rho)>>23; 						//0-65535 ---> 1Degree ---> 1.5Degree
		CurLog->ErrLog.AngleInit		= (85L*360L*Funcode.SMIniAng.value)>>23;			//0-65535 ---> 1Degree ---> 1.5Degree
		CurLog->ErrLog.ErrMCUTemp		= 0xFF;
		CurLog->ErrLog.DC_Cur			= (Funcode.DCCur.value >> 2) + 32750u;
		
		//CurrentFedFlt
}


void GetDataFlowInfo(void)
{
	//
    CANMotorCmd.Bit.CANDirect = CANDirect;
    CANMotorCmd.Bit.CtrlMode = CtrlMode;
    CANMotorCmd.Bit.MCUEnable = MCUEnable;

    //
    DriveState.Bit.isBrake = isBrake;
    DriveState.Bit.NoSlide = NoSlide;
    DriveState.Bit.VcuGearGet = VcuGearGet;

	ErrSubmit.ErrLog.ErrDCVoltage  = 50L * VoltDC;				                            //1V  --->0.02V 
	ErrSubmit.ErrLog.ErrTorqueCmd  = 32750+(CANTorq>>1); 			                        //0.02Nm--->0.04Nm	
	ErrSubmit.ErrLog.ErrTorqueFed  = 32750+(CANTorqRealDis>>17);                             // 0.02Nm--->0.04Nm 		
	ErrSubmit.ErrLog.ErrSpeedSet   = ((CANSpeed * (int16)13653) >> 15) + 32767;             // 0.25rpm --->0.6rpm
	ErrSubmit.ErrLog.ErrSpeed      = (((int32)MotorRealSpeed * (int16)13653) >> 13) + 32767;  //1rpm---->0.6rpm    
	ErrSubmit.ErrLog.ErrIGBTTemp   = TemperRealFlt + 48;   
	ErrSubmit.ErrLog.ErrMotorTemp  = (Funcode.MotorTemp.value-452); 
	ErrSubmit.ErrLog.ErrUd		   = abs(((long)Param_VdSet*Uphase)>>14) * 25 + 32750;       // 1V ---> 0.04v 
	ErrSubmit.ErrLog.ErrUq		   = abs(((long)Param_VqSet*Uphase)>>14) * 25 + 32750;       // 1V ---> 0.04v							
	ErrSubmit.ErrLog.ErrIdRef	   = ((abs(((long)Param_IdSetUnlim*Imax)>>14) * 5L) >> 1) + 32750;  //0.1A ---> 0.04A
	ErrSubmit.ErrLog.ErrIqRef	   = ((abs(((long)Param_IqSetUnlim*Imax)>>14) * 5L) >> 1) + 32750;  //0.1A ---> 0.04A
	ErrSubmit.ErrLog.ErrIdFed	   = ((abs(((long)Param_IdAct*Imax)>>14) * 5L) >> 1) + 32750;       //0.1A ---> 0.04A 
	ErrSubmit.ErrLog.ErrIqFed	   = ((abs(((long)Param_IqAct*Imax)>>14) * 5L) >> 1) + 32750;       //0.1A ---> 0.04A
	ErrSubmit.ErrLog.Err12V		   = ((int32)ConVdcFlt * 13653) >> 14;                      //0.1V--->0.12V  
	ErrSubmit.ErrLog.ErrState	   = VmsState;
	ErrSubmit.ErrLog.ErrMotorModeCmd = CANMotorCmd.Word;
	ErrSubmit.ErrLog.ErrDriveState	 = DriveState.Word;
	ErrSubmit.ErrLog.ErrMCUState	 = GenMcuState2();
	ErrSubmit.ErrLog.Angle			 = (85L*360L*Param_Rho)>>23;						    //0-65535 ---> 1Degree ---> 1.5Degree
	ErrSubmit.ErrLog.AngleInit		 = (85L*360L*Funcode.SMIniAng.value)>>23;			    //0-65535 ---> 1Degree ---> 1.5Degree
	ErrSubmit.ErrLog.ErrMCUTemp      = 0xFF;
	ErrSubmit.ErrLog.DC_Cur          = (Funcode.DCCur.value >> 2) + 32750u;
}


uint16  GetErrInfo()
{
	uint16 ret = 0;
	ret = GetErrBuffer();
	return ret;       
}


uint16 GetErrBuffer()
{
	uint16 ret;
	if(LogRead == LogWrite)	ret = 0xFF;		//No Err Info in buffer
	else
	{
		LogRead++;
		if(LogRead >= MAX_LOG)	LogRead = 0;
		ret = LogRead;
	}
	return ret;
}


void Asert_Alarm_Warn()
{
	Uint16 i;
	Detect_Alaram();
	Detect_Warn();

	for(i=0;i<16;i++)
	{
		if((1==((AlarmCode.all>>i)&0x01))&&(0==(AlarmCodeBak.all>>i))&&(0!=(AlarmInfo[i].UDSNumber)))
		{

			PushErrInfo(i+0x100);
		}
	}
	AlarmCodeBak.all = AlarmCode.all;

	for(i=0;i<16;i++)
	{
		if((1==((WarningCode.all>>i)&0x01))&&(0==(WarningCodeBak.all>>i))&&(0!=(WarnInfo[i].UDSNumber)))
		{	

			PushErrInfo(i+0x200);
		}
	}
	WarningCodeBak.all = WarningCode.all;

	
}



uint16 Get_Error_Adr(uint16 ErrNo)
{
	uint16 Adr;
	
	if(ErrNo <= 0x00FF)	//Error
	{
        if (ErrorInfo[ErrNo].UDSNumber != 0) {
		    Adr = ErrorInfo[ErrNo].EpAdr;
        }
        else {
            Adr = 0xFF; // Illegal Error
        }
	}
	else if(ErrNo<=0x1FF)//Alarm
	{
        if (AlarmInfo[ErrNo&0xFF].UDSNumber != 0) {
		    Adr = AlarmInfo[ErrNo&0xFF].EpAdr;
        }
        else {
            Adr = 0xFF; // Illegal Error
        }		
	}
	else if(ErrNo <=0x2FF)//Warn
	{
        if (WarnInfo[ErrNo&0xFF].UDSNumber != 0) {
		    Adr = WarnInfo[ErrNo&0xFF].EpAdr;
        }
        else {
            Adr = 0xFF; // Illegal Error
        }	
	}
	else
	{
		Adr = 0xFF; // Illegal Error
	}

	return Adr;
}


uint16 UpdateErrorStatus() 
{ 
    Uint16 i,j; 

    if(FlagUpdateErrorStatus!=1) return 0; 

    //Get All ErrorNumber 

	i = 0;
	for(j=0;j<25;j++)
    {
		if((ErrorInfo[j].EpAdr!=0)&&(i<MAX_ERROR_LOG))	
		{
			ErrLogStatus[i] = ErrorInfo[j].KeyCode; 
			i++;
    	}
	}

	for(j=0;j<16;j++)
    {
		if((AlarmInfo[j].EpAdr!=0)&&(i<MAX_ERROR_LOG))	
		{
			ErrLogStatus[i] = AlarmInfo[j].KeyCode; 
			i++;
    	}
	}

	for(j=0;j<16;j++)
    {
		if((WarnInfo[j].EpAdr!=0)&&(i<MAX_ERROR_LOG))	
		{
			ErrLogStatus[i] = WarnInfo[j].KeyCode; 
			i++;
    	}
	}

    for ( ; i < MAX_ERROR_LOG; i++)
    {
        ErrLogStatus[i] = 0;
    }

    //if(ErrorCode!=ErrNONE)
    {
        for(i=0;i<MAX_ERROR_LOG;i++)
        {
            if(ErrLogStatus[i] == ErrorCode) 
            {
                ErrLogStatus[i] = 0x500;
                break;
            }
        }
    }

    //if(AlarmCode.all) 
    {
        for(j=0;j<16;j++)
        {
            if(AlarmCode.all&(1<<j))
            {
                for(i=0;i<MAX_ERROR_LOG;i++)
                {
                    if(ErrLogStatus[i] == (0x100+j)) 
                    { 
                        ErrLogStatus[i] = 0x500; 
                        break; 
                    }
                }
            }
        }
    }

    //if(WarningCode.all)
    {
        for(j=0;j<16;j++)
        {
            if(WarningCode.all&(1<<j))
            {
                for(i=0;i<MAX_ERROR_LOG;i++)
                {
                    if(ErrLogStatus[i] == (0x200+j)) 
                    {
                        ErrLogStatus[i] = 0x500;
                        break; 
                    }
                }
            }
        }
    } 

    for(i=0;i<MAX_ERROR_LOG;i++) 
    { 
        if(ErrLogStatus[i] !=0x500) ErrLogStatus[i] = 0; 

    } 

    FlagUpdateErrorStatus = FALSE; 
    return 1; 
}

Uint16 GenMcuState2(void)
{
    union Un_McuState2 McuState2;

    McuState2.Word = 0;

    McuState2.Bit.InitState = McuState.bit.InitState;
    McuState2.Bit.State = McuState.bit.State;
    McuState2.Bit.McuMode = McuState.bit.McuMode;
    McuState2.Bit.McuDir = McuState.bit.McuDir;
    McuState2.Bit.HighVolOK = McuState.bit.HighVolOK;
    McuState2.Bit.EpWtOk = 1;
    if (((VmsState >= 41) && (VmsState <= 49))
        || ((VmsState >= 121) && (VmsState <= 129)) 
        || ((VmsState >= 181) && (VmsState <= 189))) {
        if (VoltDC < 25) {
            McuState2.Bit.PowerOffOk = 1;
        }
        else {
            McuState2.Bit.PowerOffOk = 0;
        }
    }
    else {
        McuState2.Bit.PowerOffOk = 0;
    }
    McuState2.Bit.RequestPowerOff12V = McuState.bit.RequestPowerOff12V;
    if (McuState.bit.RequestVCU == R_REDUCE_POWER) {
        McuState2.Bit.RequestReducePower = 1;
    }
    else {
         McuState2.Bit.RequestReducePower = 0;
    }
    if (McuState.bit.RequestVCU == R_DISABLE) {
        McuState2.Bit.RequestDisable = 1;
    }
    else {
         McuState2.Bit.RequestDisable = 0;
    }

    return McuState2.Word;
}
