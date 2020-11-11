
//****************************************************************************/
// @Module       
// @Filename      FunctionManage.c
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
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****/

/****************************************************************************/


#include "main.h"
#include "AsmAlgorithm_N.h"
#include "Ev72ctrl.h"
#include "const.h"
#include "FunctionManage_const.h"
#include "IOFunc.h"
#include "SpeedFunc.h"
#include "TorqFunc.h"
#include "Error.h"
#include "Command.h"
#include "CANProtocal.h"
#define _FunctionManage_H_
#include "GlobalVariables.h"
#include "FunctionCode.h"
#include "KeyBoard_Extypes.h"
#include "DrivePublicVar.h"
#include "FunctionManage.h"

//=========================================================================================================================
#ifndef	NULL
#define NULL                            (0L)
#endif
extern long DV3232_32(long,unsigned long,unsigned long);   // !!!


void FuncManage_RUNSTOP();


void FuncManage_enter_internal_PWMON(void );
void FuncManage_exit_internal_PWMON(void );


static void FuncManage_ControlPowerSupply(void);
static void FuncManage_exit_internal_READY(void );
static void FuncManage_RunTimer(void );
static void FuncManage_SaveParam(void);
static void FuncManage_F01Refresh(void);



Uint16 is_init_OK;
Uint16 is_READY,is_CONTROL,is_PWMON;
  
int16 itemper;
uint16 MotorTemp,MotorTempFilter;
int32 MotorTempFilterACC;
extern long TorqLmtFlt;
int32 DCCur_ValueFilter,DCCur_Value;
long MotorOutPutPower;
extern long CANTorqRealDis;
extern uint8_t  Mcu_Configuration[2];



//*****************************************************************************************************************************
void FuncManage_L1ms(void)
{   

	//第一次进来，初始化
	if (is_init_OK != 1) 
	{
		is_CONTROL = NotReadyToSwitchOn;

		is_init_OK = 1U;
		PowerOffStep = 1U;

		InitCommand();
		FuncManage_L1ms_Init_Speed();
		//FuncManage_L1ms_Init_IO();
		Init_Error();
			//首次进来，设定poff状态
		is_CONTROL = SwitchOnDisabled;
  	} 
  	else 
  	{
      		TimerForPowerOn++;
      		Time1msBase++;
      		TIMECOUNT_1MS = Time1msBase;
			FuncManage_RunTimer();
			//FuncManage_L1ms_IO();


	      	FuncManage_ControlPowerSupply();			
	  		FuncManage_Error();
	  		FuncManage_MakePara(); 

			
      		switch(is_CONTROL) 
      		{
       			//===================================================================================================
       			case StatusFault:  // (1L)
        			{
          				EALLOW;
          				EPwm1Regs.TZFRC.bit.OST = 1;   // 强制OST, 封锁输出
          				EPwm2Regs.TZFRC.bit.OST = 1;   // 强制OST, 封锁输出
          				EPwm3Regs.TZFRC.bit.OST = 1;   // 强制OST, 封锁输出
          				EDIS;
          				
          				if (GetErrorCode() == 0U) 
          				{
            				FuncManage_CmdClear();
            				is_CONTROL = (Uint8)FuncManage_In_READY;
            				is_CONTROL = (Uint8)OperationEnabled;
							is_READY = (Uint8)FuncManage_In_STOP;
          				} 
          				else if (PowerIsOK == 0) 
          				{
            				is_CONTROL = (Uint8)SwitchOnDisabled;
							FuncManage_SaveParam();

          				} 
          				else 
          				{
            				//FuncManage_ResetErr();
          				}
        			}
       	 			break;
       	 		//===================================================================================================
       			case SwitchOnDisabled:    // (2L)
        			if (PowerIsOK == 1) 
        			{
          				FuncManage_CmdClear();
            			is_CONTROL = (Uint8)OperationEnabled;
              			is_READY = (Uint8)FuncManage_In_STOP;
        			}
        			break;
        		//===================================================================================================
       			case OperationEnabled:   // (3L)
        			{
          				if (PowerIsOK == 0) 
          				{
							FuncManage_SaveParam();

							if(is_READY == FuncManage_In_RUN)
            				{
            					FuncManage_exit_internal_READY();
							}	

							is_READY = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
                			is_CONTROL = (Uint8)SwitchOnDisabled;		//Enter SwithcOnDisabled, then CmdClear, then runstep 8-->7
							
          				} 
          				else if (GetErrorCode() != 0U) 
          				{
            				//FuncManage_JdgOCTimes();
            				uControlCmd1.bit.RestErr = 0;
							
							if(is_READY == FuncManage_In_RUN)
            				{
            					FuncManage_exit_internal_READY();
							}

							is_READY = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
                			is_CONTROL = (Uint8)StatusFault;
                			FuncManage_ResetErr();
          				} 
          				else
          				{
          					FuncManage_RUNSTOP();
          				}	
        			}
        			break;
        		//===================================================================================================	
      		}      

			FuncManage_ResetErr();
	}

	//Update status
	if(is_CONTROL == OperationEnabled)
	{
		uRunStopStatus1.bit.MDIReady = 1;
	}
	else
	{
		uRunStopStatus1.bit.MDIReady = 0;	
	}

	if(is_READY == FuncManage_In_RUN)
	{
		uRunStopStatus1.bit.RunStatus = 1;
	}
	else
	{
		uRunStopStatus1.bit.RunStatus = 0;	
	}
	
	
}


void FuncManage_RUNSTOP()
{
	
	switch (is_READY) 
	{
		//-----------------------------------------------------------------------------------	
		case FuncManage_In_STOP:
			if ((uControlCmd1.bit.RunCmd == 1) && (uControlCmd1.bit.ForceStop == 0) 
				&& (uControlCmd1.bit.ForbitRun == 0) && (uControlCmd1.bit.FreeStop == 0) 
				&& (uControlCmd1.bit.EmergStop == 0)) 
				{
					is_READY = FuncManage_In_STOP2RUN;
					UCoreCmd.bit.RunStopCmd = 0;
					CurrentFreq = 0L;
						
				} 
		break;
		
		case FuncManage_In_STOP2RUN:		//原来的FuncManage.L1ms.is_RUN 的 FuncManage_In_WAIT状态
			if ((uControlCmd1.bit.RunCmd == 0) || (uControlCmd1.bit.ForceStop == 1) 
				|| (uControlCmd1.bit.ForbitRun == 1) || (uControlCmd1.bit.FreeStop == 1) 
				|| (uControlCmd1.bit.EmergStop == 1)) 
				{
					is_READY = FuncManage_In_STOP;
				} 
		
			uRunStopStatus4.bit.MotorRunDirect = uControlCmd1.bit.RunDirect;
		
			is_READY = FuncManage_In_RUN;
			UCoreCmd.bit.RunStopCmd = 1;		

			FuncManage_enter_internal_PWMON();					
			
		break;
		//-----------------------------------------------------------------------------------

		case FuncManage_In_RUN: 
		
				switch (is_PWMON) 
				{
		    	
					case FuncManage_In_SPEED:
						if((uControlCmd1.bit.RunCmd == 1) && (UCoreCmd.bit.CtlMode == 1)) 	// Speed  to Torque
    					{
							FuncManage_exit_internal_SPEED();
							uRunStopStatus2.bit.RuningStep = 0;
							FuncManage_enter_Torque();
							is_PWMON = (int16)FuncManage_In_TORQUE;
							is_READY = FuncManage_In_RUN;
						}
						
						else if(1 == FuncManage_SPEED())	
						{
							is_READY = FuncManage_In_STOP;
							is_PWMON = FuncManage_In_NO_ACTIVE_CHILD;
						}
					break;

					case FuncManage_In_TORQUE:
		    			//Torque to Speed Mode or Stop     
						if((UCoreCmd.bit.CtlMode == 0) || (uControlCmd1.bit.RunCmd == 0)) 
						{
							FuncManage_GetCurrFreq();
							UCoreCmd.bit.CtlMode = 0;			//Speed mode																					
							is_PWMON = (Uint16)FuncManage_In_SPEED; 
							FuncManage_enter_internal_SPEED(1);  // 进入速度控制状态 初始化励磁等待参数
						}

						FuncManage_TorqueRef();
					break;
		    	
				}
					
		break;
	
	}
}

	
//*****************************************************************************************************************************
static void FuncManage_ControlPowerSupply(void)
{

	int AbsMotorRealSpeed = abs(MotorRealSpeed);
	
	ConPowerON = 1;

	if((VmsState==48)||(VmsState==128)||(VmsState==188)

		||(VmsState==49)||(VmsState==129)||(VmsState==189))
	{
		PowerOffStep = 2;		//Get Power off Ins
		DisNormComTx();
	}
	else
	{
		PowerOffStep = 1;		//No Power Off Ins
	}

	
	if(PowerOffStep == 1)
	{
		if((GpioDataRegs.GPBDAT.bit.GPIO44) == 0)
		{
			ConPowerON = 1;
		}		
	}
	else if(PowerOffStep == 2)
	{
		LostCount = 0;		//Vcu has die , no check com over 
		
		if((VmsState == 12)||(VmsState == 82)||(VmsState == 142))	//Power On Again
		{
			EnNormComTx();
			PowerOffStep = 1;
			ConPowerON = 1;
		}
		else
		{

			if((VoltDC < 36)&&(AbsMotorRealSpeed<500))
			{
				ConPowerON = 0; 		
			}
			else
			{
				ConPowerON = 1;
			}			
		}
	}
	else
	{
		PowerOffStep = 1;
		ConPowerON = 0;
		
	}

	
	if(ConPowerON == 1)						//Key ON
	{
		KeyOffDelay = 0;
		if(KeyONDelay++>10)	POWER_ON();
	}
	
	else
	{
		
		KeyONDelay = 0;
		//Do Some thing for power off
		//wenbo debug 
		if(KeyOffDelay++>250) POWER_OFF();	
	}
	


}

//*********************************************************************************************************************************

static void FuncManage_exit_internal_READY(void )
{
		FuncManage_exit_internal_PWMON();
		FuncManage_ClearRunStsAndCmd();
		OutputFreq = 0L;
    		
}


//**********************************************************************************************************************
void FuncManage_enter_internal_PWMON(void )
{
 	if (UCoreCmd.bit.CtlMode == 1) 			//Torque Mode
	{
		is_PWMON = (int16)FuncManage_In_TORQUE;
		FuncManage_enter_atomic_TORQUE();
 	}
	else
	{

		is_PWMON = (Uint8)FuncManage_In_SPEED;
		FuncManage_MakeFreq();
		FuncManage_enter_internal_SPEED(0);
	}
}

//**********************************************************************************************************************
void FuncManage_exit_internal_PWMON(void )
{
	switch (is_PWMON) 
	{
    	//----------------------------------------------------------------------------------------	
   		case FuncManage_In_SPEED:
    		FuncManage_exit_internal_SPEED();
      		uRunStopStatus2.bit.RuningStep = 0;
    		break;
    	//----------------------------------------------------------------------------------------
   		case FuncManage_In_TORQUE:
			FuncManage_exit_internal_TORQUE();
    		break;
    	//----------------------------------------------------------------------------------------
  	}

	is_PWMON = (Uint16)FuncManage_In_NO_ACTIVE_CHILD;
}







//*****************************************************************************************************************************
static void FuncManage_F01Refresh(void)	//Upadate at 4ms
{
	Uint16 bit13,bit14,bit2,bit1,bit45,bit67,bit89,bitErr;
  
	Funcode.MainFrqRef.value = FreqRef/10 + 30000L;		//F0.0
	Funcode.OutFrqRef.value = CurrentFreq/10 + 30000L;	//F0.1
	Funcode.OutFrq.value = OutputFreq/10 + 30000L;		//F0.2
	
	//Funcode.OutVoltage.value = DV3232_32(VoltOut,70,16384);			//F0.3   70 = 100/1.414
	Funcode.OutVoltage.value = DV3232_32(VoltOut,udc_rated,23167);			//F0.3   283 = 400/1.414  16384*1.414=23167
	
	Funcode.OutCurrent.value = OutputCurr;							//F0.4

	Funcode.TorqCurrent.value = TorqCurrOutReal + 30000;					//F0.5
	Funcode.MagFluxCurrent.value =  MagnetCurrOutReal+ 30000;				//F0.6

	
	Funcode.TorqRef.value = TorqSetFilter + 3000;;				//F0.7		0.1%
	Funcode.OutTorq.value = DV3232_32(TorqReal,1,100) + 30000;						//F0.8		0.001Nm--->0,1Nm

	Funcode.MotorPower.value = labs(MotorRealPower);					//P01.09	0.01KW
	

	Funcode.DetMtrFrq.value = rlSpeedFedLed/10 + 30000L;	//P01.10


	//Funcode.MaxDriveTorque.value = 1000;						//P01.11	1Nm
	Funcode.MaxBraveTorque.value = 1000;                      //P01.12	1Nm

	Funcode.DCVoltage.value = VoltDC;						//P01.13


	Funcode.MDIStatus.value = 0;                          //P01.14		


	
	if (rlSpeedFed < 0L) 
	{
		bit1 = 1;		
	} 
	else 
	{
		bit1 = 0;		
	}	

	bit2 = MCUEnable;
	
	bit45 = VCUCommand;
	bit67 = CtrlMode; 
	bit89 = CANDirect;
		
	if((UCoreCmd.bit.CtlMode == SPEED_CTRL)||(UCoreCmd.bit.CtlMode == IF_CTRL))
	{
		bit13 = 1;
	}
	else
	{
		bit13 = 0;
	}

	if(UCoreCmd.bit.CtlMode == TORQUE_CTRL)
	{
		bit14 = 1;
	}
	else
	{
		bit14 = 0;
	}

	bit1  <<= 1U;
	bit2  <<= 2U;
	bit45 <<= 4U;
	bit67 <<= 6U;
	bit89 <<= 8U;	
	bit13 <<= 13U;
	bit14 <<= 14U;

	if(ErrNONE == GetErrorCode())	bitErr = 0;
	else bitErr = 1;

  	bitErr <<= 12U;
	
	Funcode.MDIStatus.value = (Uint16)uRunStopStatus1.bit.RunStatus |
    							bit1|bit2|bit45|bit67|bit89|
    							bitErr | bit13 | bit14;

	  
	Funcode.DITermStatus.value = 0;//uDITermSts.all;           //P01.15
	Funcode.DOTermStatus.value = 0;//uDoTermSts.all;           //P01.16
	
	Funcode.AI1Volt.value = 0;//(Uint16)((uint32)abs(AI1ValueAdjusted) * 1212UL >> 12UL) + 1000;	//P01.17
  	//Funcode.AI2Volt.value = 0;//(Uint16)((uint32)abs(AI2ValueAdjusted) * 1212UL >> 12UL) + 1000; 	//P01.18  
	
	Funcode.ConVolt.value =  ConVdcFlt + 3000; 	//P01.19    

	
	Funcode.TorqLimit.value = (TorqLmtFlt>>14L);              //P01.20		转矩限制	

	MotorOutPutPower = DV3232_32((long)(MotorRealSpeed),(unsigned long)labs(TorqReal),9550UL);	//1w 
	DCCur_Value = DV3232_32(labs(MotorOutPutPower),100L,VoltDC);                 //P01.21	  
	DCCur_ValueFilter = DCCur_ValueFilter + (((DCCur_Value<<16) - DCCur_ValueFilter)>>2);
	Funcode.DCCur.value = DCCur_ValueFilter>>16;  //0.01A 	  

	SpeedRpm = MotorRealSpeed;	//1rpm
	Funcode.Speedrpm.value = SpeedRpm + 30000L;

	//Funcode.MCUTemp.value                      //P01.22 update at error.c
	//Funcode.MotorTemp.value;                          //P01.23	update at error.c

	//update other FuncManage_RunTimer

}


//*****************************************************************************************************************************

Uint16 L4ms_is_init_OK = 0; 
void FuncManage_L4ms(void)
{
	if (L4ms_is_init_OK!= 1) 
  	{
    		L4ms_is_init_OK = 1U;
  	} 
  	else 
  	{
	 	FuncManage_F01Refresh();
		FuncManage_L4ms_Torque();
		Asert_Alarm_Warn();
  	}
}


static void FuncManage_RunTimer(void )
{

}

//Save Para when poweroff
static void FuncManage_SaveParam(void)
{

}


 uint16 GetMin(uint16 a,uint16 b)
 {
	 if(a>b) return b;
	 else	 return a;
 }


 const uint16 TemperTabOld[]={1779,	 			//  20 	   
									 1565,		 //  25 	   
									 1344,		 //  30 	   
									 1232,		 //  35 	 
									 1121,		 //  40 	   
									 1012,		 //  45 	   
									  908,		 //  50 	   
									  809,		 //  55 	   
									  718,		 //  60 	   
									  635,		 //  65 	   
									  560,		 //  70 		
									  493,		 //  75 	 
									  433,		 //  80 		
									  380,		 //  85 		
									  334,		 //  90 		
									  294,		 //  95 		
									  258,		 // 100 		
									  227,		 // 105 		
									  200,		 // 110 		
									  177}; 	 // 115

   		
 	 
									  


 const uint16 *TemperTab;

 void FuncManage_TempDetect(void)
{

//	if(0==(Funcode.ModuleSet.value&0xF000))	TemperTab = TemperTabNew;
//	else									TemperTab = TemperTabOld;	

	TemperTab = TemperTabOld;

	if(AI_Sample.NTCU>=TemperTab[0])         temp_AI_Sample_NTCU = TemperTab[0];
	else if(AI_Sample.NTCU<TemperTab[19])    temp_AI_Sample_NTCU = TemperTab[19];
	else                                     temp_AI_Sample_NTCU = AI_Sample.NTCU; 

	if(AI_Sample.NTCV>=TemperTab[0])         temp_AI_Sample_NTCV = TemperTab[0];
	else if(AI_Sample.NTCV<TemperTab[19])    temp_AI_Sample_NTCV = TemperTab[19];
	else                                     temp_AI_Sample_NTCV = AI_Sample.NTCV; 

	if(AI_Sample.NTCW>=TemperTab[0])         temp_AI_Sample_NTCW = TemperTab[0];
	else if(AI_Sample.NTCW<TemperTab[19])    temp_AI_Sample_NTCW = TemperTab[19];
	else                                     temp_AI_Sample_NTCW = AI_Sample.NTCW; 
	
	//Get the min(temp_AI_Sample_NTCW,V,W) is the max of temp
	{
		
#ifdef DEBUG_SIM
		TemperVoltSample = SimMCUTemp;
#else
		TemperVoltSample = GetMin(temp_AI_Sample_NTCU,temp_AI_Sample_NTCV);

		TemperVoltSample = GetMin(TemperVoltSample,temp_AI_Sample_NTCW);

#endif

		if(TemperVoltSample >TemperTab[0])
		{
			itemper = 0;
		}
		else
		{
			for (itemper = 0; itemper < sizeof(TemperTabOld); itemper++)
			{
				if (TemperVoltSample >= TemperTab[itemper])
				{
					break;	
				}
			}
		}
    	
		
		if ((itemper > 0) && (itemper < sizeof(TemperTabOld)))
		{
			TemperReal = (int)(5 * itemper +20) -  (int)((TemperVoltSample - TemperTab[itemper]) * 5L / ( TemperTab[itemper - 1] - TemperTab[itemper]));
		}
		else if (itemper == 0)
		{
			TemperReal = 20;
			
		}
		else if (itemper == sizeof(TemperTabOld))	//TempSensor Line Short 
		{
			TemperReal = 115;
		}
	}
	TemperRealAcc = TemperRealAcc + ((((long)TemperReal << 16) - TemperRealAcc) >> 4);//about 74ms filter
	TemperRealFlt = TemperRealAcc >> 16;

	if(TemperRealFlt < 20)	TemperRealFlt = 20;
	Funcode.MCUTemp.value = (500 + TemperRealFlt);
}

void FuncManage_IGBTUDetect(void)
{
      TemperTab = TemperTabOld;
      TemperVoltSample = temp_AI_Sample_NTCU;
	  
         if(TemperVoltSample >TemperTab[0])
		  {
			  itemper = 0;
		  }
		  else
		  {
			  for (itemper = 0; itemper < sizeof(TemperTabOld); itemper++)
			  {
				  if (TemperVoltSample >= TemperTab[itemper])
				  {
					  break;  
				  }
			  }
		  }
		  		  
		  if ((itemper > 0) && (itemper < sizeof(TemperTabOld)))
		  {
			  TemperUReal = (int)(5 * itemper +20) -  (int)((TemperVoltSample - TemperTab[itemper]) * 5L / ( TemperTab[itemper - 1] - TemperTab[itemper]));
		  }
		  else if (itemper == 0)
		  {
			  TemperUReal = 20;			  
		  }
		  else if (itemper == sizeof(TemperTabOld))   //TempSensor Line Short 
		  {
			  TemperUReal = 115;
		  }
		  
	  TemperURealAcc = TemperURealAcc + ((((long)TemperUReal << 16) - TemperURealAcc) >> 4);//about 74ms filter
	  TemperURealFlt = TemperURealAcc >> 16;
  
	  if(TemperURealFlt < 20)  TemperURealFlt = 20;
	  //Funcode.MCUTemp.value = (500 + TemperURealFlt);
}

void FuncManage_IGBTVDetect(void)
{
      TemperTab = TemperTabOld;
      TemperVoltSample = temp_AI_Sample_NTCV;
	  
         if(TemperVoltSample >TemperTab[0])
		  {
			  itemper = 0;
		  }
		  else
		  {
			  for (itemper = 0; itemper < sizeof(TemperTabOld); itemper++)
			  {
				  if (TemperVoltSample >= TemperTab[itemper])
				  {
					  break;  
				  }
			  }
		  }
		  		  
		  if ((itemper > 0) && (itemper < sizeof(TemperTabOld)))
		  {
			  TemperVReal = (int)(5 * itemper +20) -  (int)((TemperVoltSample - TemperTab[itemper]) * 5L / ( TemperTab[itemper - 1] - TemperTab[itemper]));
		  }
		  else if (itemper == 0)
		  {
			  TemperVReal = 20;			  
		  }
		  else if (itemper == sizeof(TemperTabOld))   //TempSensor Line Short 
		  {
			  TemperVReal = 115;
		  }
		  
	  TemperVRealAcc = TemperVRealAcc + ((((long)TemperVReal << 16) - TemperVRealAcc) >> 4);//about 74ms filter
	  TemperVRealFlt = TemperVRealAcc >> 16;
  
	  if(TemperVRealFlt < 20)  TemperVRealFlt = 20;
	  //Funcode.MCUTemp.value = (500 + TemperURealFlt);
}

void FuncManage_IGBTWDetect(void)
{
      TemperTab = TemperTabOld;
      TemperVoltSample = temp_AI_Sample_NTCW;
	  
         if(TemperVoltSample >TemperTab[0])
		  {
			  itemper = 0;
		  }
		  else
		  {
			  for (itemper = 0; itemper < sizeof(TemperTabOld); itemper++)
			  {
				  if (TemperVoltSample >= TemperTab[itemper])
				  {
					  break;  
				  }
			  }
		  }
		  		  
		  if ((itemper > 0) && (itemper < sizeof(TemperTabOld)))
		  {
			  TemperWReal = (int)(5 * itemper +20) -  (int)((TemperVoltSample - TemperTab[itemper]) * 5L / ( TemperTab[itemper - 1] - TemperTab[itemper]));
		  }
		  else if (itemper == 0)
		  {
			  TemperWReal = 20;			  
		  }
		  else if (itemper == sizeof(TemperTabOld))   //TempSensor Line Short 
		  {
			  TemperWReal = 115;
		  }
		  
	  TemperWRealAcc = TemperWRealAcc + ((((long)TemperWReal << 16) - TemperWRealAcc) >> 4);//about 74ms filter
	  TemperWRealFlt = TemperWRealAcc >> 16;
  
	  if(TemperWRealFlt < 20)  TemperWRealFlt = 20;
	  //Funcode.MCUTemp.value = (500 + TemperURealFlt);
}


//V(mV) = R*2(mA)*0.75

// T = =518*(1030+KTY)/(3885-KTY) - 259

//PT1000
const unsigned long TempPT1000[32]={ 1861,		// 0    
								     2097,		// 32	     
								     2325,		// 64	     
								     2550,		// 96	     
								     2772,		// 128	     
								     2998,		// 160	     
								     3222,		// 192
								     3437,      // 224
	                                 };	

uint16 MotorTempPowerOnDelay; 
void FuncManage_MotorTempDetect(void)
{
	uint32 MAIValue,PIndex;
	
#ifdef DEBUG_SIM
	MAIValue = SimMotorTemp;
#else
	MAIValue = AI_Sample.KTY;
#endif
	Funcode.MaxDriveTorque.value = AI_Sample.KTY;

	 MotorTempPowerOnDelay++;
	  if(MotorTempPowerOnDelay>1000U)  MotorTempPowerOnDelay=1000U;
	
	  if(MotorTempPowerOnDelay <(FuncManage_TempLinetime + 100U))
	  {
		  MotorTempFilter = 0;
		  MotorTemp = 0;
		  MotorTempFilterACC = 0;
		  Funcode.MotorTemp.value = Funcode.MotorTempOffset.value;
		  if(Funcode.MotorMode.value==1)	//PT100
		  	{
               PT100_SEL();
		       NTC_NSEL();
		    }
		  else if(Funcode.MotorMode.value==2)  //NTC
		  	{
               PT100_NSEL();
		       NTC_SEL();
		    }
		  else//PT1000*/
		  	{
               PT100_NSEL();
		       NTC_NSEL();
		    }
		  return;
	  }
		
	if(Funcode.MotorMode.value==1)	//PT100
	{		    
		if(MAIValue <= 1720) 	        MotorTemp = 0;
		else if(MAIValue >= 3025)		MotorTemp = 200; 
		else{	
			   MAIValue = 5022*MAIValue;
			   MAIValue = MAIValue>>15;		
			   MotorTemp = MAIValue- 264L;
			}
	}
	else if(Funcode.MotorMode.value==2)  //NTC
	{      
		MotorTemp = 0;
	}
	else//PT1000*/
	{      
		if(MAIValue <= TempPT1000[0]) 		    MotorTemp = 0;
		else if(MAIValue >=  TempPT1000[7])		MotorTemp = 224; 
		else{

			for (PIndex = 1; PIndex <= 7; PIndex++)
			{
				if (MAIValue <= TempPT1000[PIndex])
				{
					break;	
				}
			}			
			MAIValue = 32*(MAIValue -TempPT1000[PIndex-1])/(TempPT1000[PIndex] -TempPT1000[PIndex-1]);
			
			MotorTemp = (PIndex-1)<<5;
			MotorTemp +=  MAIValue;
		
			}		
		
	}

	if(1 == WarningCode.bit.PTSensor)	MotorTemp = 0;
		
	MotorTempFilterACC = MotorTempFilterACC + ((((long)MotorTemp << 16) - MotorTempFilterACC) >> 9);
	MotorTempFilter = MotorTempFilterACC >> 16;	

	if(MotorTempFilter>=220)	MotorTempFilter = 220;
	//Fl = a/2Pi*t	Fl = 1/2*pi*R*C		==> RC = t/a
	//上式中 a = 1/32 , t= 0.001s  , Fl = 4.97Hz
	Funcode.MotorTemp.value = MotorTempFilter + Funcode.MotorTempOffset.value;
}

/*
   首次上电判断一次c50程序和硬件是否对应
*/
void Check_Module(void)
{
//	int i;
	if((GpioDataRegs.GPADAT.bit.GPIO21) == 1)  //c50
	{
		Funcode.OCLevel.value = 5950;
		Funcode.Imax.value = 3480;
		SetModuleTable(600);

		ErrorList.bit.ParaSet = 1;
	}
	else	//c33
	{
		Funcode.OCLevel.value = 4950;
		Funcode.Imax.value = 2850;
		SetModuleTable(450);		
	}
}


