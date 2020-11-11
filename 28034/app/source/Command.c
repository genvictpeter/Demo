//****************************************************************************/
// @Module       
// @Filename      Command.c
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
//
/****************************************************************************/
#include "Typedefs.h"
#include "FunctionManage.h"
#include "main.h"

#include "Ev72ctrl.h"
#include "const.h"
#include "FunctionManage_const.h"

#include "GlobalVariables.h"
#include "FunctionCode.h"
#include "KeyBoard_Extypes.h"
#include "DrivePublicVar.h"
#include "Error.h"
#include "EepromManage.h"
#include "SpeedFunc.h"
extern int CANControlMode;


#define _COMMAND_DEF_H_ 	1
#include "Command.h"

static void FuncManage_MakeCmd(void );
static void FuncManage_CmdChannelChange(void);
static void FuncManage_ParseKBCmd(void);
static void FuncManage_ParseTerrmCmd(void);
static void FuncManage_MakeCtlPara(void);
static void FuncManage_MtrCtlSelect(void);
static void FuncManage_GetCtlCmd(void);
static void FuncManage_AssertCmd(void);
static void FuncManage_ParseCommCardCmd(void);
extern int EnableDischarge;

int SoftOCResetTime,NoErrorTime;

void InitCommand(void)
{
	uRunStopCmd1.all = 0;
	uRunStopCmdBK2.all = 0;
	uControlCmd1.all = 0;
	UCoreCmd.all = 0;
	uRunStopStatus1.all = 0;
	uRunStopStatus2.all = 0;
	uRunStopStatus3.all = 0;
	uRunStopStatus4.all = 0;
	uRunStopStatus5.all = 0;
	uRunStopCmd1.bit.CmdChFCSet = 1;
	uRunStopCmd1.bit.Torq2SpdFCSet = 1;
	SoftOCResetTime = 0;
	SoftOCCount = 0;
	NoErrorTime = 0;
}

void FuncManage_MakePara(void)
{
	FuncManage_MakeCmd();
	FuncManage_MakeCtlPara();
	FuncManage_MakeSetFreq();
}


//Get Command from keyborad、IO or CAN
//To uControlCmd1
static void FuncManage_MakeCmd(void )
{
	uRunStopCmdBK1.bit.RunDirect = uControlCmd1.bit.RunDirect;
	uRunStopCmdBK3.bit.RunCmd = uControlCmd1.bit.RunCmd;
	
	if(uRunStopCmd1.bit.CmdChFCSet == 1)		//Change cmd soure by keyboard 
	{
	  	uRunStopStatus2.bit.CmdChannel = Funcode.RunCmdChannel.value;
	  	uRunStopCmd1.bit.CmdChFCSet = 0;
	}
	
	FuncManage_CmdChannelChange();
	
	if(uRunStopStatus2.bit.CmdChannel == 0)
	{
	  FuncManage_ParseKBCmd();
	} 
	else if(uRunStopStatus2.bit.CmdChannel == 1) 
	{
	  FuncManage_ParseTerrmCmd();
	} 
	else if(uRunStopStatus2.bit.CmdChannel == 3) 
	{
		FuncManage_ParseCommCardCmd();
	}
	uRunStopStatusBK1.bit.CmdChannel = uRunStopStatus2.bit.CmdChannel;
}


static void FuncManage_CmdChannelChange(void)
{
  if(uRunStopStatusBK1.bit.CmdChannel != uRunStopStatus2.bit.CmdChannel) 	
  	{
		uRunStopCmd1.bit.KBRun = 0;
		uRunStopCmd5.bit.CommCardCmd = 0;
			
		if(uRunStopStatus2.bit.CmdChannel == 0) 		//Keyborad
		{
			uRunStopCmd1.bit.KBRun = uControlCmd1.bit.RunCmd;		
    	}
		
		else if(uRunStopStatus2.bit.CmdChannel == 3) 		//Can Control
		{
			//keep state
			if((uControlCmd1.bit.RunCmd == 1) && (uControlCmd1.bit.RunDirect ==0)) 
			{
        		uRunStopCmd5.bit.CommCardCmd = 1;
      		} 
			else if((uControlCmd1.bit.RunCmd == 1) && (uControlCmd1.bit.RunDirect ==1)) 
			{
        		uRunStopCmd5.bit.CommCardCmd = 2;
      		} 
			else 
			{
        		uRunStopCmd5.bit.CommCardCmd = 0;
        	}		
		}
  }
}


static void FuncManage_ParseKBCmd(void)
{
    uControlCmd1.bit.RunCmd = uRunStopCmd1.bit.KBRun;
  	uControlCmd1.bit.RunDirect = Funcode.RunDir.value; 
}


static void FuncManage_ParseTerrmCmd(void)	
{

	uControlCmd1.bit.RunCmd = 0;
	uControlCmd1.bit.RunDirect = 0;
}

static void FuncManage_ParseCommCardCmd(void)
{

    if(uRunStopCmd5.bit.CommCardCmd == 0) {
      uControlCmd1.bit.RunCmd = 0;
    } 
	else if(uRunStopCmd5.bit.CommCardCmd == 1) {
      uControlCmd1.bit.RunCmd = 1;
      uControlCmd1.bit.RunDirect = 0;
    } 
	else if(uRunStopCmd5.bit.CommCardCmd == 2) {
      uControlCmd1.bit.RunCmd = 1;
      uControlCmd1.bit.RunDirect = 1;
    } 
	else if(uRunStopCmd5.bit.CommCardCmd == 3) {
      uControlCmd1.bit.RunCmd = 1;
      uControlCmd1.bit.RunDirect = Funcode.RunDir.value;
    }
}


static void FuncManage_MakeCtlPara(void)
{
	FuncManage_MtrCtlSelect();     // VF or SVC
  	FuncManage_GetCtlCmd();        // 复位及强制停机标志
  	FuncManage_AssertCmd();        // 强制停机
}


static void FuncManage_MtrCtlSelect(void)
{
	Uint16 tmp1;
  	Uint16 tmp2;

	tmp1 = (Uint16)((int16)Funcode.MtrCtrlSelect.value & 0x0F);				//Control mode			
	tmp2 = (Uint16)(((int16)Funcode.MtrCtrlSelect.value & 0x0F0) >> 4);		//Motor mode

  	uRunStopStatus3.bit.MtrMode = tmp2;
  
  	if (tmp1 == 2U)   // IF
  	{
    	UCoreCmd.bit.CtlMode = 3;
  	} 
	else if (tmp1 == 1U)    // vector control
	{  
		if(Funcode.RunCmdChannel.value == 3)		//CANContrl
		{
				if(CANControlMode == 1)
				{
					uRunStopCmdBK3.bit.CtlMode = 1;			//Torque
				}
				else
				{
					uRunStopCmdBK3.bit.CtlMode = 0;
				}
		}			
		else
		{
		
    		if (uRunStopCmd1.bit.Torq2SpdFCSet == 1)		//发生了改变
    		{
      			uRunStopCmd1.bit.Torq2SpdFCSet = 0;
				if((Funcode.TorqSpdSelect.value&0x000F) == 1)
				{
					uRunStopCmdBK3.bit.CtlMode = 1;	
				}
				else
				{
					uRunStopCmdBK3.bit.CtlMode = 0;
				}
    		}
		}		

		
    	if ((uRunStopStatus1.bit.RunStatus == 1) && (uControlCmd1.bit.RunCmd == 0)) 
    	{// 运行中接到停机命令，切换到速度模式
      		UCoreCmd.bit.CtlMode = 0;
    	} 
    	else 
    	{
			UCoreCmd.bit.CtlMode = uRunStopCmdBK3.bit.CtlMode;		//0x01
			uRunStopStatus1.bit.Spd2TorqIsFinished = 0;
    	}
    }  
  	else   // reserved
  	{
  		UCoreCmd.bit.CtlMode = 0;  // 保留模式默认为速度控制
  	}
}


//*********************************************************************************************************************************
static void FuncManage_GetCtlCmd(void)
{
	uControlCmd1.bit.FreeStop = (int16)uRunStopCmd1.bit.KBFreeStop; 
	uRunStopCmd1.bit.KBFreeStop = 0;
  	
	// yshAC
	uControlCmd1.bit.EmergStop = (int16)uRunStopCmd1.bit.KBEmergStop;
	uRunStopCmd1.bit.KBEmergStop = 0;  	
	
  	if (GetErrorCode() != 0U) 
  	{
		NoErrorTime = 0;

		if(EroSoftOC == GetErrorCode())
		{
			if((SoftOCResetTime++>100)&&(SoftOCCount <= MAX_SOFT_OC))
			{
				uRunStopCmd5.bit.CommCardResetError = 1;
				SoftOCResetTime = 0;
				SoftOCCount ++;
			}
		}
		else
		{
			SoftOCResetTime = 0;
		}

		uControlCmd1.bit.RestErr = (uint16)uRunStopCmd1.bit.KBReset|
									(uint16)uRunStopCmd5.bit.CommCardResetError;
		
  	} 
  	else 
  	{
    	uControlCmd1.bit.RestErr = 0;
		if(NoErrorTime++>2000)
		{
			SoftOCCount = 0;
			NoErrorTime = 0;
		}
		
  	}
  	uRunStopCmd1.bit.KBReset = 0;
	uRunStopCmd5.bit.CommCardResetError = 0;
  	
	if (uRunStopStatus1.bit.RunStatus == 1) 
  	{ 
		uControlCmd1.bit.ForceStop = (int16)uControlCmd1.bit.ForceStop |(int16)uRunStopCmd1.bit.KBForceStop ;
		
    	uRunStopCmd1.bit.KBForceStop = 0;
  	} 
  	else 
  	{
    	uControlCmd1.bit.ForceStop = 0;
		uRunStopCmd1.bit.KBForceStop = 0;
  	}
}

//*********************************************************************************************************************************
static void FuncManage_AssertCmd(void)
{
	if (((int16)uControlCmd1.bit.ForceStop | (int16)uControlCmd1.bit.FreeStop | (int16)uControlCmd1.bit.EmergStop) != 0) 
	{
		if (uRunStopStatus1.bit.RunStatus == 1)  
		{
			uControlCmd1.bit.RunCmd = 0;
		} 
    	else 
    	{
      		uRunStopCmd1.bit.KBRun = 0;
      		uControlCmd1.bit.RunCmd = 0;
      		UCoreCmd.bit.RunStopCmd = 0;
      		uControlCmd1.bit.ForceStop = 0;
      		uControlCmd1.bit.FreeStop = 0;
    	}
  	}
}


void FuncManage_CmdClear(void)
{
	uRunStopCmd1.bit.KBRun = 0;  
  	uControlCmd1.bit.RunCmd = 0;
  	UCoreCmd.bit.RunStopCmd = 0;
  	uControlCmd1.bit.ForceStop = 0;
  	uControlCmd1.bit.FreeStop = 0;
	uControlCmd1.bit.EmergStop = 0;
}


//*******************************************************************************************************************************
void FuncManage_ClearRunStsAndCmd(void)
{
	CurrentFreq = 0L;
	
	uRunStopCmd1.bit.KBRun = 0;

	uControlCmd1.bit.RunCmd = 0;
	UCoreCmd.bit.RunStopCmd = 0;
	uControlCmd1.bit.ForceStop = 0;
	uControlCmd1.bit.FreeStop = 0;

}

//*****************************************************************************************************************************
void FuncManage_StartStopMode(void)
{
}

