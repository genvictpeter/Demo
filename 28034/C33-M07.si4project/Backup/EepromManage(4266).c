//****************************************************************************/
// @Module       
// @Filename      EepromManage.c
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

//****************************************************************************


#include "main.h"

#include "GlobalVariables.h"
#include "const.h"
#include "FunctionCode.h"

#include "Error.h"
#define	EPROMMANAGE_H
#include "EepromManage.h"

#include "uds_target.h"
#include "uds_confdefs.h"
#include "Uds_priv.h"
#include "AppDefine.h"

#define UDS_PARA_NUM_BY_WT           4

#define MOT_CODE_EP_ADR              3700
#define SW_FINGER_EP_ADR     	     3800//0x2100
#define VIN_EP_ADR                   (SW_FINGER_EP_ADR + (2 * UDS_C_DID_LEN_F184))
#define Mcu_Configuration_Adr        (MOT_CODE_EP_ADR + 2*UDS_C_DID_LEN_02FF)//3760



extern UDS_CONFIG_TYPE UDS_DidEepromDatMngRecd_t Uds_g_DidEepromDataTable[];
extern uint8_t rub_2eWtDatByDid_CurrUsingTblIndex ;
extern uint16 WriteStep;

const Uint16 UdsParaEpAdr[UDS_PARA_NUM_BY_WT] =
{
	SW_FINGER_EP_ADR,
	VIN_EP_ADR,
	MOT_CODE_EP_ADR,
	Mcu_Configuration_Adr
};

extern Uint16 DtcOccHisOrder[];
extern Uint16 PreDtcStatus[];

Uint16	FirstPowerFlag = 0u;

extern uint8_t rub_0x85CtrlDtcSetting_SubFunc;
Uint16 ClrInsideErr = 0u;

extern uint16 VmsState;

void InitEeprom()
{
	
  	 // Initialize I2Cs
   	I2caRegs.I2CSAR = I2C_SLAVE_ADDR;		// Slave address - EEPROM control code

   	I2caRegs.I2CPSC.all = 5;		    // Prescaler - need 7-12 Mhz on module clk
   	I2caRegs.I2CCLKL = 45;			// NOTE: must be non zero
   	I2caRegs.I2CCLKH = 45;			// NOTE: must be non zero		about 5.2us/bit
   	I2caRegs.I2CIER.all = 0x24;			// Disable all  interrupts

   	I2caRegs.I2CMDR.all = 0x0020;		// Take I2C out of reset
   									// Stop I2C when suspended

   	I2caRegs.I2CFFTX.all = 0x6000;	// Disable  FIFO mode and TXFIFO
   	I2caRegs.I2CFFRX.all = 0x2040;	// Disalbe RXFIFO, clear RXFFINT,
   
    EDIS;

}

//所有和EEPROM相关的操作都放在这个函数中，以防止出现EEPROM操作上的冲突产生错误
void DealEpData()
{

	SaveParameters();	//处理功能码的改动
	ClearErrLog();
	SaveErrorLog();		
	ShowErrLog();
	GetErrLog();
	WriteUds();
	UpdateErrorStatus();
}

Uint16 WriteEeprom(Uint16 Address,Uint16 WPara)
{

	Uint16 count;                                                                                                     

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   count = 0;
   while (I2caRegs.I2CMDR.bit.STP == 1)
   {

 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}		
   }

   // Setup slave address
   I2caRegs.I2CSAR = I2C_SLAVE_ADDR;

   // Check if bus busy
   count = 0;   
   while (I2caRegs.I2CSTR.bit.BB == 1)
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}	
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = 4;

   // Setup data to send
   I2caRegs.I2CDXR = (Address&0xFF00)>>8;
   I2caRegs.I2CDXR = Address&0x00FF;
   I2caRegs.I2CDXR = (WPara&0xFF00)>>8;
   I2caRegs.I2CDXR = WPara&0x00FF;

   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x6E20;	//Master Mode	
   									//Generate a START conditon 
   									//and generate a STOP conditon when the internal data counter of the I2C module counts down to 0
   									//Transmitter mode

   DelayUs(10000);					//5ms wait eeprom write	
   return RET_OK;
}

Uint16 ReadEeprom(Uint16 Address)
{
	Uint16 RetData;
	Uint16 count;                                                                                                      
	Uint16 RData[4];

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.

   count = 0;      
   while (I2caRegs.I2CMDR.bit.STP == 1)	//STP has been set by the device to generate a STOP condition when the internal data counter of
										//the I2C module counts down to 0.
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}
   }

   // Setup slave address
   I2caRegs.I2CSAR = I2C_SLAVE_ADDR;
   
   // Check if bus busy
   count = 0;   
   while (I2caRegs.I2CSTR.bit.BB == 1)
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = 2;

   // Setup data to send
   I2caRegs.I2CDXR = (Address&0xFF00)>>8;
   I2caRegs.I2CDXR = Address&0x00FF;
   
   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x2620;		//diff with 0x6E20
   										//debugger ??
   										//STT 1:In the master mode, setting STT to 1 causes the I2C module to generate a START condition on the I2C-bus.
   										//STP is automatically cleared after the STOP condition has been generated.
   										//MST Master mode. The I2C module is a master and generates the serial clock on the SCL pin.
   										//TRX Transmitter mode. The I2C module is a transmitter and transmits data on the SDA pin.
   										//DLB Digital loopback mode is enabled.
   										
   DelayUs(200);		//5.2us*28bit = 145 us	 200us is about 300us									
								
   I2caRegs.I2CCNT = 4;
   I2caRegs.I2CMDR.all = 0x2C20;		//Receive mode

   DelayUs(800);		//5.2us*47bit = 764 us      

   count = 0;
   while (I2caRegs.I2CSTR.bit.BB == 1) //busy
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}	
   }
   
   RData[0] = I2caRegs.I2CDRR;
   RData[1] = I2caRegs.I2CDRR;
   RData[2] = I2caRegs.I2CDRR;
   RData[3] = I2caRegs.I2CDRR;

   RetData = RData[0]<<8;
   RetData += RData[1];

   return RetData;
}



Uint16 Rodata[2];
Uint16 Checkdata[2];
//After Power ON, Read all Funcode from EEPROM
/*****************************************************************************
	    上电读功能码
 1.首次下载程序全覆盖EEPROM，初始化功能码
 2.版本更新选择性覆盖EEPROM(目前全覆盖)，初始化功能码
 3.p99.00=384A,读EEPROM更新功能码
 4.p99.00!=384A,初始化功能码，但不覆盖EEPROM(F99.19?99.20?99.00不初始化，读EEPROM)
   此时也修改不了功能码
******************************************************************************/
void FuncManage_ReadParameters(void)
{
	Uint16 index;
	Uint16 Func16Num;
	
	 SizeErrLog = sizeof(ErrorLog_t);
	 Func16Num = sizeof(Funcode)/sizeof(Funcode.MenuModeSlt);
	 
  if (CheckEEprom()==RET_ERROR)    //需要覆盖EEPROM  初始化参数
	{
	  if ((Checkdata[0] != 0x4556) || (Checkdata[1] != 0x364B)) //首次烧写程序 全部覆盖eeprom
		 {
			index = 0U;
			funcpointer = (FuncBits *)&Funcode; 
			while(index < sizeof(OrgValue) / sizeof(Funcode.MenuModeSlt.value)) 
			{
				funcpointer->value = OrgValue[index];
				funcpointer++;
    			Save16Func(index);
				index++;
			}
		
			NoticeClearError();
			
			//SetError(ErEEPROM);//此处显示EEPROM故障不合适.但是最好进行一个显示
			return;
		 }
	   else    //版本更改  选择性覆盖EEPROM  目前全部覆盖
		 {
            index = 0U;
			funcpointer = (FuncBits *)&Funcode; 
			while(index < sizeof(OrgValue) / sizeof(Funcode.MenuModeSlt.value)) 
			{
				funcpointer->value = OrgValue[index];
				funcpointer++;
    			Save16Func(index);
				index++;
			}
		
			NoticeClearError();
			
			//SetError(ErEEPROM);//此处显示EEPROM故障不合适.但是最好进行一个显示
			return;
		 }

  	} 

	//Read all parameter from EEPROM or ini
  	{
      if(ReadEeprom(FFactoryPassWord * 2) == 0x384A)    //读EEPROM
      	{
		    index = 0U;
		    funcpointer = (FuncBits *)&Funcode; 
			while (index < Func16Num) 
			 {
				Read2Para16Bit(index << 1U, Rodata);
				funcpointer->value = Rodata[0];	        //保存功能码数值
				index++;
				if(index < Func16Num)
				  {
					funcpointer++;
					funcpointer->value = Rodata[1];  
					index++;
					funcpointer++;
				  }
			 }
	    }
	  else                                            //初始化 特殊功能码除外
	  	{
            index = 0U;
			funcpointer = (FuncBits *)&Funcode; 
			while(index < sizeof(OrgValue) / sizeof(Funcode.MenuModeSlt.value)) 
			{
               if((index==FMotorTempOffset)||(index==FMCUTempOffset)||(index==FFactoryPassWord))
               	{
                  funcpointer->value = ReadEeprom(index * 2);
			    }
			   else
			   	{
				   funcpointer->value = OrgValue[index];
			    }	
				funcpointer++;
				index++;
			}
	    }			
  	}

	//read VIN
	ReadUds();

    //
    ReadDtcOccHisOrder();
	MakePreDtcStatus();

	ValueLong_MaxOutFrq = 10L*Funcode.MaxOutFrq.value;	
}




int16 WriteBootPara(uint16 value)
{
	if (WriteEeprom(BOOT_LOG,value) == RET_OK)
	{
		if (ReadEeprom(BOOT_LOG) == value)	return 1;
	}

	return 0;
}



Uint16 Read2Para16Bit(Uint16 Address,Uint16 *data)
{
	Uint16 RetData;
	Uint16 count;                                                                                                      
	Uint16 RData[4];

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.

   count = 0;      
   while (I2caRegs.I2CMDR.bit.STP == 1)	//STP has been set by the device to generate a STOP condition when the internal data counter of
										//the I2C module counts down to 0.
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}
   }

   // Setup slave address
   I2caRegs.I2CSAR = I2C_SLAVE_ADDR;
   
   // Check if bus busy
   count = 0;   
   while (I2caRegs.I2CSTR.bit.BB == 1)
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = 2;

   // Setup data to send
   I2caRegs.I2CDXR = (Address&0xFF00)>>8;
   I2caRegs.I2CDXR = Address&0x00FF; 
   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x2620;		//diff with 0x6E20
   										//debugger ??
   										//STT 1:In the master mode, setting STT to 1 causes the I2C module to generate a START condition on the I2C-bus.
   										//STP is automatically cleared after the STOP condition has been generated.
   										//MST Master mode. The I2C module is a master and generates the serial clock on the SCL pin.
   										//TRX Transmitter mode. The I2C module is a transmitter and transmits data on the SDA pin.
   										//DLB Digital loopback mode is enabled.
   										
   DelayUs(200);		//5.2us*28bit = 145 us	 200us is about 300us									
								
   I2caRegs.I2CCNT = 4;
   I2caRegs.I2CMDR.all = 0x2C20;		//Receive mode

   DelayUs(800);		//5.2us*47bit = 764 us      

   count = 0;
   while (I2caRegs.I2CSTR.bit.BB == 1) //busy
   {
   
 	DelayUs(100);	
	if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
	{
			SetError(ErEEPROM);
			return RET_ERROR;	
	}	
   }
   
   RData[0] = I2caRegs.I2CDRR;
   RData[1] = I2caRegs.I2CDRR;
   RData[2] = I2caRegs.I2CDRR;
   RData[3] = I2caRegs.I2CDRR;

   	
   RetData = RData[0]<<8;
   RetData += RData[1];
   data[0] = RetData;

   RetData = RData[2]<<8;
   RetData += RData[3];
   data[1] = RetData;
   
   return RetData;
}



int CheckEEprom()
{
    Checkdata[0] = ReadEeprom(FFstPwrOnFlg1 * 2);
	Checkdata[1] = ReadEeprom(FFstPwrOnFlg2 * 2);
	if ((Checkdata[0] != 0x4556) 
		|| (Checkdata[1] != 0x364B) 
		|| (ReadEeprom(FSerialNum * 2) != OrgValue[FSerialNum]) 
		|| (ReadEeprom(FSoftWareVer * 2) != OrgValue[FSoftWareVer]))
	{
		return RET_ERROR;
	}

	return RET_OK;
}




//Index16 is the index of Funcode
Uint16 Save16Func(Uint16 Index16)                                                                                                            
{
	int16 Writetimes=0,WriteDatabak=0,ReadData=0;
	Uint16 addr;

	if(Index16>=SumFunc)	return RET_ERROR;
	
    WriteDatabak = ((((FuncBits *)&Funcode)+Index16)->value);
	addr = Index16<<1;
	
	for(Writetimes=0;Writetimes<=3;Writetimes++)
	{
		if(addr>=PARA_ZONE_MAX)
		{
			SetError(ErEEPROM);
			return RET_ERROR;
		}
		
		if(RET_OK == WriteEeprom(addr, WriteDatabak))
		{
    		ReadData = ReadEeprom(addr);
    		if(ReadData == WriteDatabak)
    		{
    			(((FuncBits *)&Funcode)+Index16)->changed=0;
				return RET_OK;
    		}    		    		      		
      	}
	}
	
	SetError(ErEEPROM);
	return RET_ERROR;
}


void SaveErrorIndex(ErrorLog_t* Err,uint16 Index)
{

	Uint16 Adr;
	
	if(Index >= 100)	//Display First Falut Recored
	{
		Index = Index - 100;
		if(Index >= MAX_ERR_NUMBER)
		{
			Index = MAX_ERR_NUMBER-1;
		}
		Adr = Index<<6;
		Adr += FIRST_ERROR_ZONE_ADR;			
	}
	else
	{
		if(Index >= MAX_ERR_NUMBER)
		{
			Index = MAX_ERR_NUMBER-1;
		}	
		Adr = Index<<6;
		Adr += ERROR_ZONE_ADR;		
	}
	

	WritePageEeprom(Adr,SizeErrLog,&(Err->U16Data[0]));

}




void LoadError(ErrorLog_t* Err,Uint16 Index)
{
	Uint16 i,Adr;
	
	if(Index >= 100)	//Display First Falut Recored
	{
		Index = Index - 100;
		if(Index >= MAX_ERR_NUMBER)
		{
			Index = MAX_ERR_NUMBER-1;
		}
		Adr = Index<<6;
		Adr += FIRST_ERROR_ZONE_ADR;			
	}
	else
	{
		if(Index >= MAX_ERR_NUMBER)
		{
			Index = MAX_ERR_NUMBER-1;
		}	
		Adr = Index<<6;
		Adr += ERROR_ZONE_ADR;		
	}

	
	for(i=0;i<SizeErrLog;i++)
	{
		Err->U16Data[i] = ReadEeprom(Adr + 2*i);
	}

}



//Uint16 ErrZone[512];
//Uint16 TstFlag;

Uint16 ErrSaveAdr,ReadFisrtErr;
void SaveErrorLog()
{
	uint16 RErr;
    uint16 OccOrder;

	if(FirstPowerFlag == 0)		//First Run after power on
	{
		ErrorNumber = ReadEeprom(ERROR_NUM_ADR);
		FirstPowerFlag = 1;
	}
	else
	{
		if ((rub_0x85CtrlDtcSetting_SubFunc == UDS_C_CTRLDTCSET_DTC_STORE_ON) && (VmsState != 255)){
		RErr = GetErrInfo();
		if(0xFF !=RErr)
		{
            //
			ErrSaveAdr = Get_Error_Adr(ErrLog[RErr].ErrLog.ErrorCode);

            //
            if ((ErrSaveAdr != 0xFF) && (ErrorNumber < MUL_MAX_ERROR_LOG)){
                //
                OccOrder = CurrDtcOccOrder(ErrSaveAdr,ErrorNumber+1);
                WriteDtcOccHisOrder();

                //
                if (OccOrder == 1) {
                    ErrSaveAdr = 100 + ErrSaveAdr;

                    ErrorNumber++;
                    WriteEeprom(ERROR_NUM_ADR,ErrorNumber);
                }
                else if (OccOrder == 2) {
                    ErrorNumber++;
                    WriteEeprom(ERROR_NUM_ADR,ErrorNumber);
                }
                else if (OccOrder == 3) {

                }
                else {

                }

	            //
			    SaveErrorIndex(&(ErrLog[RErr]),ErrSaveAdr);

			    //
			    FlagSaveErr = 0;
            }
		}
		}
	}
}



void ClearErrLog()
{
    #if 0
    StClrErrLog = TRUE;
    #else		
	int i;
	if(FlagClrErr)
	{

		for(i=0;i<sizeof(ErrLog[0]);i++)
			ErrLog[0].U16Data[i] = 0;

		CopyLogToFuncode(&(ErrLog[0]));

		for(i=0;i<MAX_ERR_NUMBER;i++)		
		{
			
			SaveErrorIndex(ErrLog,i);		//Clear current Error
			SaveErrorIndex(ErrLog,i+100);	//Clear First Error;
			
		}

		ErrorNumber = 0;
		WriteEeprom(ERROR_NUM_ADR,0x00);

        for (i = 0; i < MUL_MAX_ERROR_LOG; i++) {
            DtcOccHisOrder[i] = 0xFFFF;
            WriteEeprom(ERROR_SAVE_ORDER + (2 * i), 0xFFFF);
        }

		FlagClrErr = 0;

		ClrInsideErr = 1u;
	}
	#endif	
}

void ShowErrLog()
{
	Uint16	ErrorNum;

	if(FlagShowErr !=1) return;
	
	ErrorNum = Funcode.ErrNumber.value;
	
	LoadError(&ErrShow,ErrorNum);
	
	CopyLogToFuncode(&ErrShow);	
	
	FlagShowErr = 0;
}



void SaveParameters( )
{

	unsigned short SaveIndex=0;
	
	if(SaveIndex>=SumFunc)	SaveIndex=0;
	
    //find a parameter need to be saved
    while(!(((FuncBits *)&Funcode)+SaveIndex)->changed)
    {
    	SaveIndex+=1;
    	if(SaveIndex>=SumFunc)		return;
    }
	
	
    //save 16 bits parameters
    {
      if((ReadEeprom(FFactoryPassWord * 2) != 0x384A)  //上电初始化功能码，不保存到EEprom,特殊功能码除外
	  	  &&(SaveIndex!=FMotorTempOffset)
	  	  &&(SaveIndex!=FMCUTempOffset)
	  	  &&(SaveIndex!=FFactoryPassWord))    
      	{
		   (((FuncBits *)&Funcode)+SaveIndex)->changed=0;			  
	    }
	  else
	  	{
   		  if(RET_OK == Save16Func(SaveIndex))
   		   {
			(((FuncBits *)&Funcode)+SaveIndex)->changed=0;   			
   		   }
        }
    }
    	
} 	




Uint16 WritePageEeprom(Uint16 Address,Uint16 UintNumber,Uint16 *data)
{

	Uint16	count=0,i=0,WriteData;
   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.

   count = 0;
   while (I2caRegs.I2CMDR.bit.STP == 1)
   {
 		DelayUs(100);	
		if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
		{
			SetError(ErEEPROM);
			return RET_ERROR;	
		}
   }
	
   // Setup slave address
   I2caRegs.I2CSAR = I2C_SLAVE_ADDR;
	
   // Check if bus busy
	count = 0;
   while (I2caRegs.I2CSTR.bit.BB == 1)
   {
   
 		DelayUs(100);	
		if(count++>EPERR_WAIT_TIME)	//Max wait 20ms	
		{
			SetError(ErEEPROM);
			return RET_ERROR;	
		}
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = 2 + (UintNumber<<1);

   // Setup data to send
   I2caRegs.I2CDXR = (Address&0xFF00)>>8;
   I2caRegs.I2CDXR = Address&0x00FF;
   
   
   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x6E20;	//Master Mode	
   									//Generate a START conditon 
   									//and generate a STOP conditon when the internal data counter of the I2C module counts down to 0
   									//Transmitter mode

    								
	for(i=0;i<UintNumber;i++)
	{
		WriteData = *(data+i);
		count = 0;
		while(I2caRegs.I2CSTR.bit.XRDY==0)
		{
			DelayUs(50);				//5.2us*8bit = 41.6 us	 50us is about 75us	
			if(count++>EPERR_WAIT_TIME)	//Max wait 10ms	
			{
				SetError(ErEEPROM);
				return RET_ERROR;	
			}
		}
		I2caRegs.I2CDXR = WriteData>>8;
		
		count = 0;		
		while(I2caRegs.I2CSTR.bit.XRDY==0)
		{
			DelayUs(50);				//5.2us*8bit = 41.6 us	 50us is about 75us	
			if(count++>EPERR_WAIT_TIME)	//Max wait 10ms	
			{
				SetError(ErEEPROM);
				return RET_ERROR;	
			}
		}
		I2caRegs.I2CDXR = WriteData&0xFF;
		
	}
   
   DelayUs(5000);					//5ms wait eeprom write	
   return RET_OK;
}

 

uint16 NoticeClearError()
{
	FlagClrErr = 1;
	return 1;
}

void GetErrLog(void)
{
    Uint16	ErrorShowIndex;
	
	if (StReadErrLog == TRUE) {
        //
        if ((GetErrOrderNum & (Uint16)1) == 0) {
            ErrorShowIndex = 100 + (GetErrOrderNum >> 1);
        }
        else {
            ErrorShowIndex = GetErrOrderNum >> 1;
        }
        ErrorShowIndex = ErrorShowIndex + 1;

        //
        LoadError( & ErrSubmit, ErrorShowIndex);

		//
		StReadErrLog = FALSE;
	}
}

void WriteUds(void)
{
	Uint16 i;
	uint8_t * pDataBuf;

	if (WriteStep) {

		pDataBuf = Uds_g_DidEepromDataTable[rub_2eWtDatByDid_CurrUsingTblIndex].pDataBuf;
		for(i =0; i< Uds_g_DidEepromDataTable[rub_2eWtDatByDid_CurrUsingTblIndex].DataSize; i++)
		{
			WriteEeprom((UdsParaEpAdr[rub_2eWtDatByDid_CurrUsingTblIndex] + (2 * i)), * pDataBuf++);
		}
		
		WriteStep = 0;
	}
}

void ReadUds(void)
{
	Uint16 ParaIndex;
	Uint16 i;
	uint8_t * pDataBuf;

	for (ParaIndex = 0; ParaIndex < UDS_PARA_NUM_BY_WT; ParaIndex++) {
		pDataBuf = Uds_g_DidEepromDataTable[ParaIndex].pDataBuf;
		for(i =0; i< Uds_g_DidEepromDataTable[ParaIndex].DataSize; i++)
		{
			* pDataBuf++ = ReadEeprom(UdsParaEpAdr[ParaIndex] + (2 * i));
		}
	}
}

void WriteDtcOccHisOrder(void)
{
    Uint16 i;

    for (i = 0; i < MUL_MAX_ERROR_LOG; i++) {
        WriteEeprom(ERROR_SAVE_ORDER + (2 * i), DtcOccHisOrder[i]);
    }
}

void ReadDtcOccHisOrder(void)
{
    Uint16 i;

    for (i = 0; i < MUL_MAX_ERROR_LOG; i++) {
        DtcOccHisOrder[i] = ReadEeprom(ERROR_SAVE_ORDER + (2 * i));
    }
}

void MakePreDtcStatus(void)
{
	Uint16 i;
	Uint16 CurrDtcSaveOrder;

	for (i = 0u; i < MAX_ERROR_LOG; i++) {
		CurrDtcSaveOrder = i << 1;
		if ((DtcOccHisOrder[CurrDtcSaveOrder] == 0xFFFF) 
			&& (DtcOccHisOrder[CurrDtcSaveOrder + 1] == 0xFFFF)) {
			PreDtcStatus[i] = 0u;
		}
		else {
			PreDtcStatus[i] = 1u;
		}
	}
}

