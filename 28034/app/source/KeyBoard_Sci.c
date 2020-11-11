//****************************************************************************/
// @Module       
// @Filename      keyboard_sci.c
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


#define _KEYBOARDSCI_H_


#include "main.h"				// Peripheral address definitions
#include "FunctionCode.h"			
#include "KeyBoard_Extypes.h"
#include "keyboard_sci.h"
#include "const.h"
#include "IOFunc.h"
#include "CAN.h"

#define	CANKEY	1 

#define  KEYCANCMD	0x57

uint16 DisCount,KeyCmdChannel;
extern Uint16 CAN_vTransmit(ubyte ubObjNr,uint8_t *data);
CAN_SWObj rul_SDOCanSwObj;
void CANTIMECHK(void);

void CANREADTOSEND(void)
{
	if ((TxReady == 1)&&(KeyCmdChannel == KEYCANCMD))                             //reload a fram
	{
		if(DisCount++ <2)	return;
		else	  
		{
			DisCount = 0;
			if (Txnumber > 0)
			{
				CAN_vTransmit(28u,&(DataTxd[2]));		
			}   				
		}
	}
}


void READTOSEND(void)
{
	int ii = 0;		    		
	CANREADTOSEND();
	
	if (TxReady == 1)                             //reload a fram
	{
		if (SciaRegs.SCICTL2.bit.TXEMPTY == 1)    // ysh2802x : scia
		{ 
			if (Txnumber > 0)
		  	{
		  		RS485_TMS;
				if (Txnumber>=4)	// the 2803x SCI has a 4-level transmit FIFO
				{
					Txnumber -= 4;
					for (ii=0;ii<4;ii++)
					{	 
						SciaRegs.SCITXBUF = DataTxd[ii+delay*4];					
					} 
					delay ++;
				}
				else
				{
					
					loop:		
							if (ii < Txnumber)   
							{
								while (SciaRegs.SCICTL2.bit.TXEMPTY == 0) 	
								{
									;
								}								
							    SciaRegs.SCITXBUF = DataTxd[ii+delay*4]; 
								ii++;
								goto loop;
							}
							else
							{
								Txnumber = 0;
								delay = 0;			
							}					
				}
		  	}   
		  	else 
		  	{
		  		RS485_RSV;
				TxReady = 0;
		  	}				
		}
	}              			   	          	
}

void LEDDISPLAY(void)
{
	int j = 0, temp = 0;
	
	DataTxbuff[0] = 0x88;
	DataTxbuff[1] = 0x0b;
	DataTxbuff[2] = LEDSeg[4] & 0x0ff;		//inver the order to comply with 430
	DataTxbuff[3] = LEDSeg[3] & 0x0ff;
	DataTxbuff[4] = LEDSeg[2] & 0x0ff;
	DataTxbuff[5] = LEDSeg[1] & 0x0ff;
	DataTxbuff[6] = LEDSeg[0] & 0x0ff;
	DataTxbuff[7] = unnLEDLight.all & 0x0ff;
	DataTxbuff[8] = (unnLEDLight.all & 0x0ff00) >> 8;
	for (j = 0; j <= 8; j++)
	{
		temp += DataTxbuff[j];
	}
	DataTxbuff[9] = temp & 0xff;
	DataTxbuff[10] = (temp & 0x0ff00) >> 8;
}



void SCITIMECHK(void)
{
	int i = 0;
	Rxtimecnt +=1;
	Txtimecnt +=1;        			
	if(Rxtimecnt>=1000)
	{						
		Rxtimecnt = 0;
	}
	
	CANTIMECHK();
	
	if(KeyCmdChannel!=KEYCANCMD)
	{
	if(SciaRegs.SCIFFRX.bit.RXFFST != 0)
	{	
		Rxtimetmp = Rxtimecnt;						
		while(SciaRegs.SCIFFRX.bit.RXFFST != 0)
		{	
			DataRxbuff[i+Rxcnt]=(SciaRegs.SCIRXBUF.all & 0x0ff);
			i++;
		}
		Rxcnt += i;
		if(Rxcnt>=12) Rxcnt = 12;												
	}	
	}
}


void CANTIMECHK(void)
{
	volatile Uint32 ShadowReg;
	uint16 CanLen;
		
	int i = 0;

	ShadowReg=ECanaRegs.CANRMP.all;

	if(ShadowReg&(0x0001L<<15))	
	{	
		Rxtimetmp = Rxtimecnt;	
		CAN_vGetMsgObj(15, &rul_SDOCanSwObj); 
		CanLen = ((rul_SDOCanSwObj.usMOCfg & 0xFFF3u) >> 0x04u); 
		
		for(i =0;i<CanLen;i++)
		{
			DataRxbuff[i+Rxcnt] = rul_SDOCanSwObj.ubData[i];
		}
		Rxcnt = 8;	

		KeyCmdChannel = KEYCANCMD; 
	}
	else
	{
	}
}



void GETKEY(void)
{
	KeyValue = (DataRxd[3] << 8) + DataRxd[2];   
	KeyHoldtmr = (DataRxd[5] << 8) + DataRxd[4];
	KeyValue = (~KeyValue) & 0x1ff;	
}


//////////////////////////////////////////////////////////    	

void KBCOMM(void)
{	
	int i,j;
	
	if (ParaInit == 0)
	{//////地址指针初始化//////////////
		ParaInit = 1;
		firaddress  = &Funcode.MenuModeSlt;
		nowaddress  = &Funcode.MenuModeSlt;
	}
	
	/////////////////////receive data frame ///////////////////////////////		
	if (Rxcnt > 0)
	{
		if (Rxtimecnt >= Rxtimetmp)
		{
			Deltatime = Rxtimecnt - Rxtimetmp;
		}
		else 
		{
			Deltatime = 1000 + Rxtimecnt - Rxtimetmp;
		}
	}
    else 
    {
    	Deltatime = 0;
    }    
                                           
	if (Deltatime >= 5)		// a frame over
	{			   
		Nobacktimes = 0;   		//收到数据后清零   
		if (DataRxbuff[0] == 0x88)
		{
			Dataorg = (DataRxbuff[Rxcnt - 1] << 8) + DataRxbuff[Rxcnt - 2];
			for (i = 0; i < (Rxcnt - 2); i++)
			{
				Datacal += DataRxbuff[i];
			}
			if (Dataorg == Datacal)
			{
				for (i = 0; i < Rxcnt; i++)
				{
					DataRxd[i] = DataRxbuff[i];
				}
				switch (DataRxd[1])
		 		{
					case(0x48):	GETKEY();	break;
					default:				break;
		 		}						
			}
			else
			{
				;
			}
			Datacal = 0;		
	    }
		Rxcnt = 0;
		RxReady = 1;		// rx finish flag
	} //end of if (Deltatime>=5)
	
	RxReady = 0;		
	Nobacktimes++;
	
	LEDDISPLAY();
			
//send:	
	Txnumber = DataTxbuff[1] & 0x0f;
	if (Txnumber == 0)		
	{
		Txnumber = 46;
	}
	for (j = 0; j < Txnumber; j++)
	{
		DataTxd[j] = DataTxbuff[j];
	}
	Txtimecnt = 0;
	TxReady = 1;	
		
//sendover:	
	if (SciaRegs.SCIRXST.bit.BRKDT == 1)
	{
		SciaRegs.SCICTL1.bit.SWRESET = 0;
		SciaRegs.SCICTL1.bit.SWRESET = 1;
	}
}	


/*** end of file *****************************************************/
