/****************************************************************************
 	@Module       
 	@Filename      SpeedFunc.c
 	@Project       BQApp
----------------------------------------------------------------------------
 	@Controller    TI 28034

 	@Compiler      V5.211

 	@Codegenerator CCS 3.3

 	@Description   

----------------------------------------------------------------------------
	 @Date          12/19/2014

******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

****************************************************************************/


#include "FunctionManage.h"
#include "main.h"
#include "IQmathLib.h"

#include "Ev72ctrl.h"
#include "const.h"
#include "FunctionManage_const.h"
#include "GlobalVariables.h"
#include "FunctionCode.h"
#include "KeyBoard_Extypes.h"
#include "DrivePublicVar.h"
#include "IOFunc.h"
#include "TorqFunc.h"
#include "Command.h"

#define _SPEEDFUNC_DEF_H_ 	1
#include "SpeedFunc.h"
//=========================================================================================================================

extern long DV3232_32(long,unsigned long,unsigned long); 
static void FuncManage_MainFreqSelect(void );
static void FuncManage_b_MainFreqSelect(Uint16 nSelect, void *reserved );
static void FuncManage_GetSpdModeFreq(void);
static void FuncManage_FreqLimit(void);
static void FuncManage_LINE(void );
static void FuncManage_enter_internal_RUNNI(void );
static void FuncManage_enter_atomic_RUNNING(void );
static void FuncManage_StopSpdDetect(void );
static void FuncManage_LAccStepProcess(void );
static void FuncManage_enter_internal_START(void );
static void FuncManage_StartAtStartFreq(void );
static  void FuncManage_GetSetFreq(void );
static  void FuncManage_LCalDecAcceleration(void );
static  void FuncManage_GetAccDecTime(void );
static void FuncManage_GetNotSpdModeFreq(void);
static void FuncManage_LCalAccAcceleration(void );
static void FuncManage_LDecStepProcess(void );
static  void FuncManage_exit_internal_RUNNIN(void );
//static   void GetCurrFreqDirect();



//CurrentFreq(+-) <----	CurrentRefFreq<-----CurrentOutputFreq<--(ACCTime)--- SetFreqScale
//SetFreq<----FreqRef <--- MainFreqRef
//
//
U_AccDecFlag uAccDecFlag;

Uint32 PreSetFreq,SetFreq,SetFreqScale,MaxOutputFreqScale,InitialOutputFreq,CurrentOutputFreq;
//Uint32 SetFreq;
Uint32 CurrentAcceleration;
Uint32 FX;
Uint32 AccTime,DecTime,PreAccTime,PreDecTime;
Uint32 PreExictTimer,PreExictT1ms;   	

Uint16 is_RUNNING,is_LINE,is_SPEED;
Uint16 SetFreqShiftR;

extern int CANRequestFreq;

void FuncManage_L1ms_Init_Speed(void)
{
	uAccDecFlag.all = 0;
	SetFreqScale = 0UL;
	SetFreq = 0;
	SetFreqShiftR = 0;


}

void FuncManage_MakeSetFreq(void )
{
	
	FuncManage_MainFreqSelect();
	uRunStopCmdBK2.bit.RefChannel = uRunStopStatus2.bit.RefChannel;
	
	if(UCoreCmd.bit.CtlMode == 0)		//Speed Mode
	{
		FuncManage_FreqLimit();
  		FuncManage_GetSpdModeFreq();
	}

		
	else if(UCoreCmd.bit.CtlMode == 1)		//Torque Mode
	{
		FuncManage_GetNotSpdModeFreq();
		FuncManage_FreqLimit();
	} 
	
	else   // IF mode
	{
		FreqRef = MainFreqRef;
	}	

}

void FuncManage_MainFreqSelect(void )
{
  	uRunStopStatus2.bit.RefChannel = Funcode.MainFrqSourceSlt.value;

	FuncManage_b_MainFreqSelect((Uint16)uRunStopStatus2.bit.RefChannel, NULL);
}

void FuncManage_b_MainFreqSelect(Uint16 nSelect, void *reserved )
{
	if(nSelect == 0U)	//Keyborad Set
	{
		MainFreqRef = (int32)10L*Funcode.MainFrqDigiSet.value;
	}
	else if(nSelect == 8U)
	{
		MainFreqRef = (int32)CANRequestFreq;
	}
	else
	{
		MainFreqRef = 0;
	}
	
}

void FuncManage_GetSpdModeFreq(void)
{
	//uControlCmd1.bit.RunDirect = Funcode.RunDir.value;

	FreqRef = MainFreqRef;
}

void FuncManage_GetNotSpdModeFreq(void)
{

	FreqRef = labs(rlSpeedFedLed);
  
}

static void FuncManage_FreqLimit(void)
{

	uRunStopStatus3.bit.FreqLowLimit = 0;		//ÏÂÏÞÎªÁã£¬ËùÒÔ²»»á³öÏÖ³¬¹ýÏÂÏÞµÄÇé¿ö
	
	if(FreqRef >= ValueLong_MaxOutFrq) 
	{
	  FreqRef = (uint32)ValueLong_MaxOutFrq;
	  uRunStopStatus3.bit.FreqHighLimit = 1;
	} 
	else 
	{
	  uRunStopStatus3.bit.FreqHighLimit = 0;
	}
	
	if((UCoreCmd.bit.CtlMode != 3) && (FreqRef > 65000UL)) 	//²»ÊÇVF, FreqRef < 650.00Hz
	{
	  FreqRef = 65000UL;
	}
}


//******************************************************************************************************************************
static void FuncManage_GetSetFreq(void )
{

	SetFreqShiftR = ValueLong_MaxOutFrq>>16;
	
	if (uControlCmd1.bit.RunCmd == 0) 
  	{

		SetFreq = 0UL;
  	}	 
  	else 
  	{
    	SetFreq = FreqRef;				//Freq   Set
  	}
  	

  	if((uRunStopStatus5.bit.CurrRunDirect != uControlCmd1.bit.RunDirect)) 
  	{

      if(CurrentOutputFreq != 0UL) 
      {
        SetFreq = 0UL;
      }
	  else
	  {
	  	uRunStopStatus5.bit.CurrRunDirect = uControlCmd1.bit.RunDirect;
	  }

  	}

  	if (PreSetFreq != SetFreq) 
  	{
    	uAccDecFlag.bit.FreqSetChg = 1;
  	} 
  	else 
  	{
    	uAccDecFlag.bit.FreqSetChg = 0;
  	}

	
  	PreSetFreq = SetFreq;    

	SetFreqScale = SetFreq>>SetFreqShiftR;             
	
	MaxOutputFreqScale = (Uint32)ValueLong_MaxOutFrq>>SetFreqShiftR; 

}


//******************************************************************************************************************************
static void FuncManage_GetAccDecTime(void )
{
	AccTime = (Uint32)Funcode.AccTime1.value;
	DecTime = (Uint32)Funcode.DecTime1.value;	
	AccTime *= 100UL;
	DecTime *= 100UL;

  	if (PreAccTime != AccTime) 
  	{
    	uAccDecFlag.bit.AccTimeChg = 1;
  	} 
  	else 
  	{
    	uAccDecFlag.bit.AccTimeChg = 0;
  	}
  	if (PreDecTime != DecTime) 
  	{
    	uAccDecFlag.bit.DecTimeChg = 1;
  	} 
  	else 
  	{
    	uAccDecFlag.bit.DecTimeChg = 0;
  	}
  	PreAccTime = AccTime;
  	PreDecTime = DecTime;
}


void FuncManage_MakeFreq(void)
{

	if(uRunStopStatus5.bit.CurrRunDirect == 1)   // ·´×ª
	{
		CurrentFreq = 0L - (int32)CurrentRefFreq;
	} 
	else 
	{
		CurrentFreq = (int32)CurrentRefFreq;
	}
	
	
	if (CoreFlag_CtrlMode == 3)   // IF¿ØÖÆ
	{
		OutputFreq = CurrentFreq;  // IF¿ØÖÆÊ±£¬Ä¬ÈÏµÄÏÔÊ¾ÆµÂÊÊÇÊµÊ±²Î¿¼ÆµÂÊ
	}
	else
	{
		OutputFreq = rlSpeedFedLed;  // Ê¸Á¿¿ØÖÆÊ±£¬Ä¬ÈÏµÄÏÔÊ¾ÆµÂÊÊÇÊµ²âÆµÂÊ£¨ÕÛËã³ÉµçÆµÂÊ£©
	}

	if (OutputFreq < 0L) 
	{
		uRunStopStatus4.bit.MotorRunDirect = 1;    // ·´×ª
	} 
	else 
	{
		uRunStopStatus4.bit.MotorRunDirect = 0;    // Õý×ª
	}
}


//******************************************************************************************************************************

static void FuncManage_LCalDecAcceleration(void )//2011.01.10
{
	Uint32 ActualDecTime;
  	
  	if (DecTime != 0UL) 
  	{
    	ActualDecTime = (Uint32)DV3232_32(DecTime, InitialOutputFreq - SetFreqScale,
     										MaxOutputFreqScale);
    	if (ActualDecTime == 0UL) 
    	{
      		ActualDecTime = 1UL;
    	}
    	CurrentAcceleration = ((InitialOutputFreq - SetFreqScale) << 16UL) / ActualDecTime;
    	if (CurrentAcceleration == 0UL) 
    	{
      		CurrentAcceleration = 1UL;
    	}
		CurrentAcceleration = CurrentAcceleration>>SetFreqShiftR;
  	}
}

//**********************************************************************************************************************
static void FuncManage_LINE(void )
{
	switch (is_LINE) 
	{
     	//========================================================================================
     	case FuncManage_In_AccStep:
      		if (is_LINE == (int16)FuncManage_In_AccStep) 
      		{
        		if ((CurrentOutputFreq >= SetFreqScale) 
        			|| (uAccDecFlag.bit.FreqSetChg == 1) || (uAccDecFlag.bit.AccTimeChg == 1)) 
        		{
          			if (CurrentOutputFreq > SetFreqScale) 
          			{
            			is_LINE = (Uint8)FuncManage_In_DecStep;
            			uRunStopStatus2.bit.RuningStep = 2;
            			InitialOutputFreq = CurrentOutputFreq;
            			FuncManage_LCalDecAcceleration();
            			FX = InitialOutputFreq << 16UL;
            			FuncManage_LDecStepProcess();
          			} 
          			else if (CurrentOutputFreq < SetFreqScale) 
          			{
            			is_LINE = (Uint8)FuncManage_In_AccStep;
            			InitialOutputFreq = CurrentOutputFreq;
            			FuncManage_LCalAccAcceleration();
            			FX = InitialOutputFreq << 16UL;
            			FuncManage_LAccStepProcess();
            			uRunStopStatus2.bit.RuningStep = 1;
          			} 
          			else 
          			{
            			is_LINE = (Uint8)FuncManage_In_ConstantSpeedStep;
            			CurrentOutputFreq = SetFreqScale;	//Set  Freq
            			CurrentAcceleration = 0UL;
            			uRunStopStatus2.bit.RuningStep = 3;
          			}
        		} 
        		else 
        		{
          			FuncManage_LAccStepProcess();
        		}
      		}
      		break;
      	//========================================================================================	
     	case FuncManage_In_ConstantSpeedStep:
      		if (is_LINE == (int16)FuncManage_In_ConstantSpeedStep) 
      		{
        		if (CurrentOutputFreq != SetFreqScale) 
        		{
          			if (CurrentOutputFreq > SetFreqScale) 
          			{
            			is_LINE = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
            			if (is_RUNNING == (int16)FuncManage_In_LINE) 
            			{
              				is_LINE = (Uint8)FuncManage_In_DecStep;
              				uRunStopStatus2.bit.RuningStep = 2;
              				InitialOutputFreq = CurrentOutputFreq;
              				FuncManage_LCalDecAcceleration();
              				FX = InitialOutputFreq << 16UL;
              				FuncManage_LDecStepProcess();
            			}
          			} 
          			else if (CurrentOutputFreq < SetFreqScale) 
          			{
            			is_LINE = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
            			if (is_RUNNING == (int16)FuncManage_In_LINE) 
            			{
              				is_LINE = (Uint8)FuncManage_In_AccStep;
              				InitialOutputFreq = CurrentOutputFreq;
              				FuncManage_LCalAccAcceleration();
              				FX = InitialOutputFreq << 16UL;
              				FuncManage_LAccStepProcess();
							uRunStopStatus2.bit.RuningStep = 1;
            			}
          			} 
          			else 
          			{
            			is_LINE = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
            			if (is_RUNNING == (int16)FuncManage_In_LINE) 
            			{
              				is_LINE = (Uint8)FuncManage_In_ConstantSpeedStep;
              				CurrentOutputFreq = SetFreqScale;
              				CurrentAcceleration = 0UL;
              				uRunStopStatus2.bit.RuningStep = 3;
            			}
          			}
        		} 
        		else 
        		{
          			//FuncManage_TuneRun();
        		}
      		}
      		break;
      	//========================================================================================	
     	case FuncManage_In_DecStep:
      		if ((CurrentOutputFreq <= SetFreqScale) 
      			|| (uAccDecFlag.bit.FreqSetChg == 1) || (uAccDecFlag.bit.DecTimeChg == 1)) 
      		{
        		if (CurrentOutputFreq > SetFreqScale) 
        		{
          			is_LINE = (Uint8)FuncManage_In_DecStep;
          			uRunStopStatus2.bit.RuningStep = 2;
          			InitialOutputFreq = CurrentOutputFreq;
          			FuncManage_LCalDecAcceleration();
          			FX = InitialOutputFreq << 16UL;
          			FuncManage_LDecStepProcess();
        		} 
        		else if (CurrentOutputFreq < SetFreqScale) 
        		{
          			is_LINE = (Uint8)FuncManage_In_AccStep;
          			InitialOutputFreq = CurrentOutputFreq;
          			FuncManage_LCalAccAcceleration();
          			FX = InitialOutputFreq << 16UL;
          			FuncManage_LAccStepProcess();
          			uRunStopStatus2.bit.RuningStep = 1;
        		}
        		else 
        		{
          			is_LINE = (Uint8)FuncManage_In_ConstantSpeedStep;
          			CurrentOutputFreq = SetFreqScale;
          			CurrentAcceleration = 0UL;
          			uRunStopStatus2.bit.RuningStep = 3;
        		}
      		} 
      		else 
      		{
        		FuncManage_LDecStepProcess();
      		}
      		break;
      	//========================================================================================	
	}
}


//**********************************************************************************************************************************
//0 : ×´ÌåÃ»ÓÐ¸Ä±ä
//1 : Í¨ÖªÍâ²¿ÏÖÔÚÒÑ¾­Í£»ú

int16 FuncManage_SPEED(void )
{
	if ((Funcode.StopMode.value ==0) && (uRunStopStatus4.bit.StopSpdIsReached == 1))    // ¼õËÙÍ£»úÇÒ¼õËÙÆµÂÊµ½´ï 
    {// P12.01ÔÝÊ±ÓÃÓÚÍ£»ú·½Ê½Ñ¡Ôñ
		uRunStopStatus4.bit.StopSpdIsReached = 0;
      	FuncManage_exit_internal_SPEED();
        FuncManage_ClearRunStsAndCmd();
		uRunStopStatus2.bit.RuningStep = 0;
        OutputFreq = 0L;
		return 1;
    }
    else if((Funcode.StopMode.value == 1) && (uControlCmd1.bit.RunCmd == 0)) 		//Free Stop
    {// P12.01ÔÝÊ±ÓÃÓÚÍ£»ú·½Ê½Ñ¡Ôñ
      //if(is_READY == FuncManage_In_RUN) 
      {
		ForceTZ();
		uRunStopStatus1.bit.RunStatus = 0;
      	FuncManage_exit_internal_SPEED();		
		FuncManage_ClearRunStsAndCmd();
		uRunStopStatus2.bit.RuningStep = 0;
    	//OutputFreq = 0L;//????
    	return 1;
      }
    }
	
    else 
    {
      	FuncManage_StopSpdDetect();
      	FuncManage_MakeFreq();			//CurrentRefFreq--->CurrentFreq
		
      	switch (is_SPEED) 
      	{
			case FuncManage_In_RUNNING:    
            	FuncManage_GetSetFreq();//--->SetFreqScale
            	FuncManage_GetAccDecTime();

            	switch (is_RUNNING) 
            	{
             		case FuncManage_In_LINE:
              			FuncManage_LINE();	//SetFreqScale-->CurrentOutputFreq
              			break;
              			
             		case FuncManage_In_SCurve:
              			break;
            	}
				CurrentRefFreq = CurrentOutputFreq<<SetFreqShiftR;	            		
        		break;
        	//=================================================================================================	
       		case FuncManage_In_START:      // Æð¶¯,Ô¤Àø´Å
        		if (is_SPEED == (int16)FuncManage_In_START) 
        		{
          			if (uRunStopStatus4.bit.StartIsOK == 1) //Ô¤Àø´Å½áÊø
          			{
						
						PreExictTimer = 0U;
            			uRunStopStatus4.bit.StartIsOK = 0;
						
              			FuncManage_enter_atomic_RUNNING();
                		FuncManage_enter_internal_RUNNI();
						is_SPEED = (Uint16)FuncManage_In_RUNNING;

          			} 
          			else 
         		 	{
         		 		FuncManage_StartAtStartFreq();            			
          			}
        		}
        		break;
        	//=================================================================================================	
      	}
    }
	return 0;
}


//**********************************************************************************************************************************
void FuncManage_exit_internal_SPEED(void )
{
	switch(is_SPEED) 
  	{
    	//=======================================================================================================	
   		case FuncManage_In_RUNNING:
    		FuncManage_exit_internal_RUNNIN();
      		
    		break;
    	//=======================================================================================================	
   		case FuncManage_In_START:    		
			PreExictTimer = 0U;
    		uRunStopStatus4.bit.StartIsOK = 0;
    		break;
		//=======================================================================================================
  	}

	is_SPEED = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;	
}


//*****************************************************************************************************************************
//FromTorq = 1 ´Ó×ª¾ØÇÐ»»¶øÀ´  FromTorq = 0 ËÙ¶ÈÄ£Ê½½øÈë
void FuncManage_enter_internal_SPEED(Uint16 FromTorq )
{
	if (FromTorq== 1) 		//´Ó×ª¾ØÇÐ»»¶øÀ´
	{
		FuncManage_enter_atomic_RUNNING();
		if (is_SPEED == (Uint16)FuncManage_In_RUNNING) 
		{
			FuncManage_enter_internal_RUNNI();
		}
	} 
	else 
	{

		is_SPEED = (Uint16)FuncManage_In_START;
		uRunStopStatus2.bit.RuningStep = 1;		//Acc run
		uRunStopStatus4.bit.StartIsOK = 0;
		Param_Int_n_HD = (long)ToqOutPercent<<16;	//½«µ±Ç°×ª¾ØÊä³ö¸¶¸øËÙ¶È»·µÄ»ý·ÖÆ÷
		
		FuncManage_enter_internal_START();//Ô¤Àø´Å
	}
}

//*******************************************************************************************************************************
//yshAC
static void FuncManage_exit_internal_RUNNIN(void )
{
	is_LINE = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
	is_RUNNING = (Uint8)FuncManage_In_NO_ACTIVE_CHILD;
}


//³õÊ¼»¯¼Ó¼õËÙÐèÒªµÄ²ÎÊý
//*******************************************************************************************************************************
static void FuncManage_enter_internal_RUNNI(void )
{
	//Ö»Ö§³ÖÖ±Ïß¼Ó¼õËÙ
  	{
    	if (is_RUNNING != (int16)FuncManage_In_LINE) 
    	{
      		is_RUNNING = (Uint8)FuncManage_In_LINE;
      		CurrentAcceleration = 0UL;
    	}
    	if (is_RUNNING == (int16)FuncManage_In_LINE) 
    	{
      		if (CurrentOutputFreq > SetFreqScale) 
      		{
        		if (is_LINE != (int16)FuncManage_In_DecStep) 
        		{
          			is_LINE = (Uint8)FuncManage_In_DecStep;
          			uRunStopStatus2.bit.RuningStep = 2;
          			InitialOutputFreq = CurrentOutputFreq;
          			FuncManage_LCalDecAcceleration();
          			FX = InitialOutputFreq << 16UL;
          			FuncManage_LDecStepProcess();
        		}
      		} 
      		else if (CurrentOutputFreq < SetFreqScale) 
      		{
        		if (is_LINE != (int16)FuncManage_In_AccStep) 
        		{
          			is_LINE = (Uint8)FuncManage_In_AccStep;
          			InitialOutputFreq = CurrentOutputFreq;
          			FuncManage_LCalAccAcceleration();
          			FX = InitialOutputFreq << 16UL;
          			FuncManage_LAccStepProcess();
          			uRunStopStatus2.bit.RuningStep = 1;
        		}
      		} 
      		else if (is_LINE != (int16)FuncManage_In_ConstantSpeedStep) 
      		{
        		is_LINE = (Uint8)FuncManage_In_ConstantSpeedStep;
        		CurrentOutputFreq = SetFreqScale;
        		CurrentAcceleration = 0UL;
        		uRunStopStatus2.bit.RuningStep = 3;
      		}
    	}
  	} 
}


//³õÊ¼»¯ËùÓÐËÙ¶ÈÔËÐÐÐèÒªµÄ²ÎÊý
static void FuncManage_enter_atomic_RUNNING(void )
{
	if (is_SPEED != (Uint16)FuncManage_In_RUNNING) 
	{
    	CurrentAcceleration = 0UL;
    	FX = 0UL;
    	InitialOutputFreq = 0UL;
    	AccTime = 0UL;
    	DecTime = 0UL;
    	SetFreqScale = 0UL;
    	MaxOutputFreqScale = 0UL;
    	
    	CurrentOutputFreq = 0UL;
    	is_SPEED = (Uint16)FuncManage_In_RUNNING;
		
		FuncManage_GetCurrFreq();					//¶¼ÊÇÒÔ×ªËÙ¸ú×ÙµÄÐÎÊ½Æô¶¯,½«¼Ó¼õËÙºóµÄ¸ø¶¨ËÙ¶ÈÉè¶¨Îªµ±Ç°Êµ¼ÊËÙ¶È
    	FuncManage_GetSetFreq();					//µÃµ½µ±Ç°Éè¶¨µÄËÙ¶È
    	FuncManage_GetAccDecTime();					//µÃµ½µ±Ç°µÄ¼Ó¼õËÙ
  	}
}

//****************************************************************************************************************************

static void FuncManage_StopSpdDetect(void )
{

  	if (uControlCmd1.bit.RunCmd == 0) 		
  	{
  		//Ö»Ö§³Ö¼õËÙÍ£³µ
		if (UCoreCmd.bit.CtlMode != 3)	//²»ÊÇVF¿ØÖÆ
		{
			if (labs(rlSpeedFed) <= Funcode.StopDetectFrq.value)
			{
				uRunStopStatus4.bit.StopSpdIsReached = 1;
			}
			else
			{
				uRunStopStatus4.bit.StopSpdIsReached = 0;
			}
			
		} 
    	
    	else if(CurrentRefFreq <= Funcode.StopDetectFrq.value) 
    	{
      		uRunStopStatus4.bit.StopSpdIsReached = 1;
    	} 
    	else 
    	{
      		uRunStopStatus4.bit.StopSpdIsReached = 0;
    	}
  	} 
}


//******************************************************************************************************************************
static void FuncManage_LAccStepProcess(void )
{
	Uint32 CurrentOutputFreqScale;
	
  	if (AccTime != 0UL) 
  	{
    	CurrentOutputFreqScale = FX + CurrentAcceleration;
    	FX = CurrentOutputFreqScale;
    	CurrentOutputFreq = (CurrentOutputFreqScale + 32768UL) >> 16UL;
  	} 
  	else 
  	{
    	CurrentOutputFreq = SetFreqScale;
  	}
}

//******************************************************************************************************************************
static void FuncManage_LCalAccAcceleration(void )
{
	Uint32 ActualAccTime;
  	
  	if (AccTime != 0UL) 
  	{
    	ActualAccTime = (Uint32)DV3232_32(AccTime, SetFreqScale - InitialOutputFreq,
     										MaxOutputFreqScale);
    	if (ActualAccTime == 0UL) 
    	{
      		ActualAccTime = 1UL;
    	}
    	CurrentAcceleration = ((Uint32)((SetFreqScale - InitialOutputFreq) << 16UL)) / ActualAccTime;
    	if (CurrentAcceleration == 0UL) 
    	{
      		CurrentAcceleration = 1UL;
    	}
		CurrentAcceleration = CurrentAcceleration>>SetFreqShiftR;
  	}
}



//******************************************************************************************************************************
static void FuncManage_LDecStepProcess(void )	//2011.01.10
{
	Uint64 TX1;
  	
  	if (DecTime != 0UL) 
  	{
    	TX1 = CurrentAcceleration;
    	if (FX <= TX1) 
    	{
      		TX1 = 0UL;
    	} 
    	else 
    	{
      		TX1 = FX - TX1;
    	}
    	FX = TX1;
    	CurrentOutputFreq = (TX1 + 32768UL) >> 16UL;
  	} 
  	else 
  	{
    	CurrentOutputFreq = SetFreqScale;
  	}
}

//********************************************************************************************************************************
static void FuncManage_enter_internal_START(void )
{
      		PreExictTimer = 0U;
    		PreExictT1ms = (Uint16)(Funcode.PreExcitTime.value * 100);   //  Ô¤¼¤´ÅÊ±¼ä
			FuncManage_StartAtStartFreq();

}


//*****************************************************************************************************************************
static void FuncManage_StartAtStartFreq(void )    // ID70007
{
    	if (PreExictT1ms == 0U) 
    	{
      		goto label_1;
    	} 
    	else if (PreExictTimer < PreExictT1ms) 
    	{
      		PreExictTimer++;
    	} 
    	else 
    	{
      		goto label_1;
    	}
    	CurrentRefFreq = 0UL;
    	goto label_2;
    	
		label_1:;
		CurrentRefFreq = 0;   								// Æð¶¯ÆµÂÊ¸³¸øµ±Ç°ÆµÂÊ
		uRunStopStatus4.bit.StartIsOK = 1;            			// Æð¶¯Íê³É, ×¢£º´ËÆð¶¯ÎÞð¶¯ÆµÂÊ±£³ÖµÈ´ýÊ±¼ä£¬¹ÊÔ¤¼¤´ÅÍê³É¾ÍÆð¶¯
		goto label_3;
		
		label_2:;
		uRunStopStatus4.bit.StartIsOK = 0;
	    	
		label_3:;
		
  		uRunStopStatus4.bit.StartIsOK = (int16)uRunStopStatus4.bit.StartIsOK | (int16)~uControlCmd1.bit.RunCmd;
}


/*static void GetCurrFreqDirect()
{
	if(UCoreCmd.bit.CtlMode == IF_CTRL)
	{
		uRunStopStatus5.bit.CurrRunDirect = uControlCmd1.bit.RunDirect;
	}
	else
	{	
		if (rlSpeedFed < 0L) 
		{
			uRunStopStatus5.bit.CurrRunDirect = 1;		
		} 
		else 
		{
			uRunStopStatus5.bit.CurrRunDirect = 0;
		}
	}
}*/


void FuncManage_GetCurrFreq(void)
{
	int32 tmp;
	if(UCoreCmd.bit.CtlMode == IF_CTRL)
	{
		tmp = CurrentRefFreq;
		uRunStopStatus5.bit.CurrRunDirect = uControlCmd1.bit.RunDirect;
	}
	else
	{
		if (rlSpeedFed < 0L) 
		{
			tmp = 0L - rlSpeedFed;
			uRunStopStatus5.bit.CurrRunDirect = 1;		
		} 
		else 
		{
			uRunStopStatus5.bit.CurrRunDirect = 0;
			tmp = rlSpeedFed;
		}		
	}
	
	CurrentRefFreq = (Uint32)tmp;
	CurrentFreq = rlSpeedFed;	
	CurrentOutputFreq = CurrentRefFreq>>SetFreqShiftR;
	InitialOutputFreq = CurrentRefFreq>>SetFreqShiftR;	
}
