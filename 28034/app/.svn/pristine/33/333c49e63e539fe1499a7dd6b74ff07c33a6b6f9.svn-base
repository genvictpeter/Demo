//****************************************************************************/
// @Module       
// @Filename      KeyBoard.c
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



#include "KeyBoard.h"

#define KeyBoard_event_ENTER            (4U)
#define KeyBoard_event_UP               (5U)
#define KeyBoard_event_DOWN             (6U)
#define KeyBoard_event_ESC              (2U)
#define KeyBoard_event_SHIFT            (12U)
#define KeyBoard_event_RUN              (7U)
#define KeyBoard_event_STOP             (9U)

#define KeyBoard_event_RESET            (3U)

#define KeyBoard_event_TIMEUP           (14U)
#define KeyBoard_event_CYCLEOVER        (11U)
#define KeyBoard_In_NO_ACTIVE_CHILD     (0L)
#define KeyBoard_In_FuncEdit            (2L)
#define KeyBoard_In_ErrDisplay          (1L)
#define KeyBoard_In_RunDisplay          (1L)
#define KeyBoard_In_StopDisplay         (2L)
#define KeyBoard_In_Normal              (2L)
#define KeyBoard_In_DataDisplay         (1L)
#define KeyBoard_In_RSDisplay           (2L)
#define KeyBoard_In_SetFreq             (1L)
#define KeyBoard_In_SetSpd              (3L)

#define KeyBoard_In_SetLSpd             (2L)


#define CALL_EVENT                      255



#ifndef NULL
#define NULL                            ((void *)0)
#endif

#define _FUNCTIONCODE_
#include "FunctionCode.h"

#define _KEYBOARDEX_
#include "KeyBoard_Extypes.h"

#define _CONST_
#include "const.h"

#include "GlobalVariables.h"
#include "SpeedFunc.h"
#include "Error.h"
#include "AppDefine.h"
#include "EepromManage.h"

Uint8 _sfEvent_KeyBoard_;
Uint16 PowerOnDelay;
Deal_Work_KEYBOARD KeyBoard_DealWork;


static int32 KeyBoard_power(int16 x1, int16 x2);
 Uint32 KeyBoard_GetValue(Uint16 x);
static void KeyBoard_FromKB(void );
static void KeyBoard_FuncEdit(void );
static void KeyBoard_ErrDisplay(void );
void KeyBoard_SetValue(Uint16 x, Uint32 y);
static void KeyBoard_DnManage(void );
static void KeyBoard_ParaRefresh(void );
static void KeyBoard_enter_internal_Normal(void );
static void KeyBoard_Normal(void );
static void KeyBoard_DataDisplay(void );
static void KeyBoard_enter_internal_RSDispl(void );
static void KeyBoard_LEDDeal(void );

static void KeyBoard_DecValueLED(void );
static void KeyBoard_MenuLED(void );
static void KeyBoard_RunDataRefresh(void);
static void KeyBoard_LEDLight(void );

static void KeyBoard_FuncMain(void );


static void KeyBoard_SpecialFunc(void );

static void KeyBoard_FuncodeRela(void );

void KeyBoard_StopLedParamD(void);
void KeyBoard_RunLedParam1D(void);
void KeyBoard_RunLedParam2D(void);

static void KeyBoard_StopDataRefresh(void);


static void KeyBoard_UpManage(void );
void KeyBoard_RatedVolt(void);
void KeyBoard_ParaInitD(void );

static void KeyBoard_KeyCmd(void );


static void KeyBoard_broadcast_CYCLEOVER(void );
//static void KeyBoard_HideGroup(uint16 x, void *reserved );

extern void GetAllVersion();

extern uint16 FlagShowErr;
//********************************************************************************************************************************
static int32 KeyBoard_power(int16 x1, int16 x2)
{
	int32   y;
  	y = 1L;
  	while (x2 > 0) 
	{
    	y *= (int32)x1;
    	x2--;
  	}
  	return y;
}

//********************************************************************************************************************************
 Uint32 KeyBoard_GetValue(Uint16 x)
{

  	{
    	funcipTP = firstip + x;             // 找到功能码的指针
    	return (Uint32)funcipTP->value;   // 返回对应的值
  	}  
  	
}


//********************************************************************************************************************************
// yshAC：得到 _sfEvent_KeyBoard_ 的值

static void KeyBoard_FromKB(void )   
{
	//====================================================================================================================
	// UP键按下
  	if (((KeyValue & (Uint16)0x08) == 0x08) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x08) == 0U)) 
  	{		
		_sfEvent_KeyBoard_ = KeyBoard_event_UP;    // 此次keyBoard事件定义为 KeyBoard_event_UP 事件
  	}
	
	//====================================================================================================================
	// DN键按下
	else if (((KeyValue & (Uint16)0x40) == 0x40) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x40) == 0U)) 
	{
		_sfEvent_KeyBoard_ = KeyBoard_event_DOWN;   // 此次keyBoard事件定义为 KeyBoard_event_DOWN 事件
    }
    //====================================================================================================================
    
	KeyBoard_DealWork.KeyBoard.ShiftPress = 0U;

	//====================================================================================================================
	// ENTER键按下	
	if (((KeyValue & (Uint16)0x01) != 0U) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x01) == 0U)) 
    {
      	_sfEvent_KeyBoard_ = KeyBoard_event_ENTER;   // 此次keyBoard事件定义为 KeyBoard_event_ENTER 事件

	} 

	//====================================================================================================================
	// ESC键按下		
	else if (((KeyValue & (Uint16)0x0100) != 0U) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x0100) == 0U)) 
	{
		_sfEvent_KeyBoard_ = KeyBoard_event_ESC;  // 此次keyBoard事件定义为 KeyBoard_event_ESC 事件
	} 
	
	//====================================================================================================================
	// SHIFT键按下 	
	else if(((KeyValue & (Uint16)0x04) != 0U) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x04) == 0U)) 
	{
		_sfEvent_KeyBoard_ = KeyBoard_event_SHIFT;    // 此次keyBoard事件定义为 KeyBoard_event_SHIFT 事件
		
		KeyBoard_DealWork.KeyBoard.ShiftPress = 1U;
    } 

	//====================================================================================================================
	// RUN键按下
	else if (((KeyValue & (Uint16)0x020) != 0U) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x020) == 0U)) 
	{
		_sfEvent_KeyBoard_ = KeyBoard_event_RUN;   // 此次keyBoard事件定义为 KeyBoard_event_RUN 事件
    } 

	//====================================================================================================================
	// STOP键按下
    else if (((KeyValue & (Uint16)0x080) != 0U) && ((KeyBoard_DealWork.KeyBoard.KeyValueBak & (Uint16)0x080) == 0U)) 
    {
	    _sfEvent_KeyBoard_ = KeyBoard_event_STOP;   // 此次keyBoard事件定义为 KeyBoard_event_STOP 事件

    } 
    //====================================================================================================================
    
    KeyBoard_DealWork.KeyBoard.KeyValueBak = KeyValue;

	//-----------------------------------------------------------
	// 闪烁 -LU- 相关
	if((KeyValue & (Uint16)0x1ff) != 0U) 
	{
		KeyBoard_DealWork.KeyBoard.Poffflag = 0U;
		KeyBoard_DealWork.KeyBoard.poffcnt = 0U;
	} 
	else 
	{
		KeyBoard_DealWork.KeyBoard.poffcnt++;
	}
	if(KeyBoard_DealWork.KeyBoard.poffcnt > 100U)  // 5.6s以内都没有按键，则Poffflag置位，若满足Poffflag为1且PowerIsOK为0，则报"-LU-"
	{
		KeyBoard_DealWork.KeyBoard.poffcnt = 0U;
		KeyBoard_DealWork.KeyBoard.Poffflag = 1U;
	}    
	//-----------------------------------------------------------
}


//********************************************************************************************************************************
static void KeyBoard_FuncEdit(void )
{
	if ((_sfEvent_KeyBoard_ == KeyBoard_event_ESC) && (KeyBoard_DealWork.KeyBoard.curpos != 2U)) 
	{
		KeyBoard_DealWork.KeyBoard.FlagFromErr = 0U;
		
		KeyBoard_DealWork.KeyBoard.is_Display = (Uint8)KeyBoard_In_DataDisplay;  
		
		if (uKeyPara.bErr == 1)  // 故障状态， is_DataDisplay 数据显示模式为 KeyBoard_In_ErrDisplay 
		{
	  		if (KeyBoard_DealWork.KeyBoard.is_DataDisplay != (int16)KeyBoard_In_ErrDisplay) 
	  		{
	    		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_ErrDisplay;
	    		if ((uKeyPara.bErrFlag == 0) && (uKeyPara.bAlarm == 0)) 
	    		{
	    			uKeyPara.bErrFlag = 1;
	    			KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
	     			KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
	    		} 
	    		else 
	    		{
	    			KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
	    			uKeyPara.bErrFlag = 1;
	    		}
	    		uRunStopCmd1.bit.KBUP = 0;
	    		uRunStopCmd1.bit.KBDN = 0;
	  		}
		} 
		else   // 正常状态， is_DataDisplay 数据显示模式为 KeyBoard_In_Normal 
		{
	  		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_Normal;
	  		KeyBoard_enter_internal_Normal();  
		}
	} 
	else if ((uKeyPara.bErr == 1) && (uKeyPara.bErrFlag == 0)) 
	{
		KeyBoard_DealWork.KeyBoard.is_Display = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
		if (KeyBoard_DealWork.KeyBoard.is_active_Display != 0) 
		{
			KeyBoard_DealWork.KeyBoard.FlagFromErr = 0U;
			KeyBoard_DealWork.KeyBoard.is_Display = (Uint8)KeyBoard_In_DataDisplay;
			if (uKeyPara.bErr == 1) 
			{
	  			if (KeyBoard_DealWork.KeyBoard.is_DataDisplay != (int16)KeyBoard_In_ErrDisplay) 
	  			{
	    			KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_ErrDisplay;
	    			if ((uKeyPara.bErrFlag == 0) && (uKeyPara.bAlarm == 0)) 
	    			{
	      				uKeyPara.bErrFlag = 1;
	      				KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
	      				KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
	    			} 
	    			else 
	    			{
	      				KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
	      				uKeyPara.bErrFlag = 1;
	    			}
	    			uRunStopCmd1.bit.KBUP = 0;
	    			uRunStopCmd1.bit.KBDN = 0;
	  			}
			} 
			else 
			{
	  			KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_Normal;
	  			KeyBoard_enter_internal_Normal();
			}
		}
	} 
	else 
	{
		KeyBoard_FuncMain();
	}
}

//**********************************************************************************************************************************
static void KeyBoard_ErrDisplay(void )
{
	if (KeyBoard_DealWork.KeyBoard.is_DataDisplay == (int16)KeyBoard_In_ErrDisplay) 
	{
    	if (_sfEvent_KeyBoard_ == KeyBoard_event_SHIFT) 
    	{
      		KeyBoard_DealWork.KeyBoard.FlagFromErr = 1U;
      		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_Normal;
      		KeyBoard_enter_internal_Normal();
    	} 
    	else if ((uKeyPara.bErr == 0) && (uKeyPara.bErrFlag == 0)) 
    	{
      		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_Normal;
      		KeyBoard_enter_internal_Normal();
    	} 
    	else if ((_sfEvent_KeyBoard_ == KeyBoard_event_RESET) && (uKeyPara.bErr == 1)) 
    	{
      		KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
      		KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
    	}
  	}
}

//**********************************************************************************************************************************
void KeyBoard_SetValue(Uint16 x, Uint32 y)
{

  	funcipTP = firstip + x;
  	
  	{
		if((x == FTuneMode) || (x == FResolverTest)) 
		{  
			funcipTP->value = y;
		} 
    	else if (funcipTP->value != y) 
    	{
      		funcipTP->value = y;
      		funcipTP->changed = 1;
    	}
  	}   	
}

//*******************************************************************************************************************************
static void KeyBoard_DnManage(void )
{
	Uint16   temp;
  	Uint16   Temp1;
  	Uint16   b_i;
  	Uint16   x;
  	Uint16   b_Temp1;
  	Uint16   Temp2;
  	boolean_T  y;
  	boolean_T  b_y;
  	int16    initialdot;
  	
  	if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
  	{
    	if (KeyBoard_DealWork.KeyBoard.flicker != 5U) 
    	{
      		if ((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x0001) == 0U)  // 十进制约束
      		{
            	temp = KeyBoard_DealWork.KeyBoard.flicker;

          		if (KeyBoard_DealWork.KeyBoard.Led > KeyBoard_DealWork.KeyBoard.LowerValue + (Uint32)KeyBoard_power(10, (int16)temp)) 
          		{
            		KeyBoard_DealWork.KeyBoard.Led -= (Uint32)KeyBoard_power(10, (int16)temp); // 个位减1，十位减10，百位减100 ...
          		} 
          		else 
          		{
            		KeyBoard_DealWork.KeyBoard.Led = KeyBoard_DealWork.KeyBoard.LowerValue;
          		}
          		if (KeyBoard_DealWork.KeyBoard.Led > KeyBoard_DealWork.KeyBoard.UpperValue) 
          		{
            		KeyBoard_DealWork.KeyBoard.Led = KeyBoard_DealWork.KeyBoard.UpperValue;
          		}
      		} 
      		else if ((KeyBoard_DealWork.KeyBoard.Led >> (Uint32)(KeyBoard_DealWork.KeyBoard.flicker << 2U) & (Uint32)0x0F) > 0UL) 
      		{
        		KeyBoard_DealWork.KeyBoard.Led -= (Uint32)(1 << (KeyBoard_DealWork.KeyBoard.flicker << 2U));
      		}
      		if (!(((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x0001) == 1U) || (KeyBoard_DealWork.KeyBoard.flicker == 0U))) 
      		{
        		while (((Uint32)KeyBoard_power(10, (int16)KeyBoard_DealWork.KeyBoard.flicker) 
        			   > KeyBoard_DealWork.KeyBoard.Led) && (KeyBoard_DealWork.KeyBoard.flicker > 0U)) 
				{
   					KeyBoard_DealWork.KeyBoard.flicker--;
        		}
      		}
    	}
  	} 
  	else   // 完全菜单模式
  	{
	
	label_4:;

		if ((KeyBoard_DealWork.KeyBoard.curpos == 0U) && (KeyBoard_DealWork.KeyBoard.flicker != 4)) 
    	{
    		KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
    		if ((KeyBoard_DealWork.KeyBoard.flicker == 2U) && (KeyBoard_DealWork.KeyBoard.pos[0][0] > 0U)) 
    		{
    			goto label_1;
    		} 
    		else if (KeyBoard_DealWork.KeyBoard.pos[0][0] == 0U) 
    		{
    			KeyBoard_DealWork.KeyBoard.pos[0][0] = NumFunc[0];
    			goto label_2;
    		} 
    		else if (NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] <= 10U) 		//lxy100319 十位一下序号清零
    		{
    			KeyBoard_DealWork.KeyBoard.pos[0][0] = 0U;
    			goto label_2;
    		} 
    		else 
    		{
    			Temp1 = NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] / 10U;		//lxy100319 除十得到组数
    			while(1) 
    			{
    	  			b_i = Temp1 - 1U;
    	  			if (FuncGroup[b_i] != 0) 
    	  			{
    	    			break;
    	  			}
    	  			Temp1--;
    			}
    			Temp1 = 10U * b_i + NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] % 10U;
    			temp = 1U;
    		}
    		
label_3:;
    		if (temp <= NumFunc[0]) 
    		{
    			if (Temp1 == NumGroup[temp]) 
    			{        //lxy100319 判断显示序号是否匹配
    	  			KeyBoard_DealWork.KeyBoard.pos[0][0] = temp;
    	  			x = KeyBoard_DealWork.KeyBoard.pos[0][0];
    	  			b_Temp1 = x >> 4U;
    	  			if ((x & (Uint16)0x0F) == 15U) 
    	  			{
    	    			Temp2 = 32768U;
    	  			} 
    	  			else 
    	  			{
    	    			Temp2 = (Uint16)(1 << (x & (Uint16)0x0F));
    	  			}
    	  			if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[b_Temp1] & Temp2) == 0U) 
    	  			{
    	    			y = 0U;
    	  			} 
    	  			else 
    	  			{
    	    			y = 1U;
    	  			}
    	  			if (y == 0) 
    	  			{
    	    			goto label_2;
    	  			} 
    	  			else 
    	  			{
    	    			temp = NumFunc[0];
    	  			}
    			}
    		} 
    		else 
    		{
    			Temp1 = 0U;
    			for (temp = 0U; temp <= b_i; temp++) 
    			{
    	  			Temp1 += FuncGroup[temp];
    	 		}
    			KeyBoard_DealWork.KeyBoard.pos[0][0] = Temp1 - 1U;

    			goto label_2;
    		}
    		temp++;
    		goto label_3;
    		
label_1:;
    	
    	KeyBoard_DealWork.KeyBoard.pos[0][0]--;
    	if (unnLEDLight.bit.btest == 0)
		{
			if((KeyBoard_DealWork.KeyBoard.pos[0][0] >=21U) && (KeyBoard_DealWork.KeyBoard.pos[0][0] <=25U))
		  	{
		  		goto label_1;	
		  	}
    	}
    	else
    	{
    		if (KeyBoard_DealWork.KeyBoard.pos[0][0] <= 20U)
		 	{
		 		KeyBoard_DealWork.KeyBoard.pos[0][0] = 25U;
		 	}
		}
		
label_2:;
		
    	temp = KeyBoard_DealWork.KeyBoard.pos[0][0];
    	Temp1 = temp >> 4U;
    	if ((temp & (Uint16)0x0F) == 15U) 
    	{
    		temp = 32768U;
    	} 
    	else 
    	{
    		temp = (Uint16)(1 << (temp & (Uint16)0x0F));
    	}
    	if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[Temp1] & temp) == 0U) 
    	{
    		b_y = 0U;
    	} 
    	else 
    	{
    		b_y = 1U;
    	}
    	if (b_y == 1) 
    	{
    		goto label_1;
    	}
    	while(1) 
    	{
    		initialdot = 0;
    		for (temp = 0U; temp < KeyBoard_DealWork.KeyBoard.pos[0][0]; temp++) 
    		{
    	  		initialdot = (int16)((Uint16)initialdot + NumFunc[(int16)(temp + 1U)]);
    		}
    		KeyBoard_DealWork.KeyBoard.dot = (Uint16)initialdot + KeyBoard_DealWork.KeyBoard.pos[1][0];
    		funcip = firstip + KeyBoard_DealWork.KeyBoard.dot;
    		if (funcip->ignore != 1) 
    		{
    	  		break;
    		}
    		KeyBoard_DealWork.KeyBoard.pos[1][0]++;   //lxy100428
    	}
    	} 
    	else if((KeyBoard_DealWork.KeyBoard.curpos == 0U) && (KeyBoard_DealWork.KeyBoard.flicker == 4))		//F闪烁时，根据功能码组数，决定是F or H
    	{    	
    		unnLEDLight.bit.btest = 0;
    		KeyBoard_DealWork.KeyBoard.pos[0][0] = 0U;
    		KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
    		KeyBoard_DealWork.KeyBoard.dot = 0U;	
    	} 
    	else 
    	{
      		temp = KeyBoard_DealWork.KeyBoard.pos[0][0];
      		Temp1 = temp >> 4U;
      		if ((temp & (Uint16)0x0F) == 15U) 
      		{
        		temp = 32768U;
      		} 
      		else 
      		{
        		temp = (Uint16)(1 << (temp & (Uint16)0x0F));
      		}
      		if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[Temp1] & temp) == 0U) 
     	 	{
        		b_y = 0U;
      		} 
      		else 
      		{
        		b_y = 1U;
      		}
      		if (b_y == 1) 
      		{
        		KeyBoard_DealWork.KeyBoard.curpos = 0U;
        		KeyBoard_DealWork.KeyBoard.flicker = 2U;
        		goto label_4;
      		} 
      		else 
      		{
        		if (KeyBoard_DealWork.KeyBoard.pos[1][0] == 0U) 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = NumFunc[(int16)(KeyBoard_DealWork.KeyBoard.pos[0][0] + 1U)] - 1U;
        		} 
        		else if ((int32)KeyBoard_DealWork.KeyBoard.pos[1][0] > KeyBoard_power(10, (int16)KeyBoard_DealWork.KeyBoard.flicker)) 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = (Uint16)((int32)KeyBoard_DealWork.KeyBoard.pos[1][0] 
          				- KeyBoard_power(10, (int16)KeyBoard_DealWork.KeyBoard.flicker));
        		} 
        		else 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
        		}
        		while(1) 
        		{
          			initialdot = 0;
          			for (temp = 0U; temp < KeyBoard_DealWork.KeyBoard.pos[0][0]; temp++) 
          			{
            			initialdot = (int16)((Uint16)initialdot + NumFunc[(int16)(temp + 1U)]);
          			}
          			KeyBoard_DealWork.KeyBoard.dot = (Uint16)initialdot +
            		KeyBoard_DealWork.KeyBoard.pos[1][0];
          			funcip = firstip + KeyBoard_DealWork.KeyBoard.dot;
          			if (funcip->ignore != 1) 
          			{
            			break;
          			}
          			if (KeyBoard_DealWork.KeyBoard.pos[1][0] > 0U)  // 子菜单下翻
          			{
            			KeyBoard_DealWork.KeyBoard.pos[1][0]--;
          			} 
          			else  // 子菜单下翻到零，从顶部开始 
          			{
            			KeyBoard_DealWork.KeyBoard.pos[1][0] = NumFunc[(int16)(KeyBoard_DealWork.KeyBoard.pos[0][0] + 1U)] - 1U;
          			}
        		}
      		}
    	}
	} 
}

//*******************************************************************************************************************************
static void KeyBoard_ParaRefresh(void )
{
	Uint8     b_previousEvent;
	Uint16    b_k;
	KeyBoard_FuncodeRela();
	if (KeyBoard_DealWork.KeyBoard.ErrCodeBak != GetErrorCode()) 
	{
    	if (GetErrorCode() != 0) 
    	{
      		uKeyPara.bErr = 1;
      		uKeyPara.bAlarm = 0;
    	} 
		else		
    	{
      		uKeyPara.bErr = 0;
      		uKeyPara.bAlarm = 0;			
    	}
    	
    	b_previousEvent = _sfEvent_KeyBoard_;
    	_sfEvent_KeyBoard_ = KeyBoard_event_RESET;
    	
    	KeyBoard_ErrDisplay();
    	
    	_sfEvent_KeyBoard_ = b_previousEvent;
    	uKeyPara.bErrFlag = 0;
  	} 
  	else if (GetErrorCode() == 0) 
  	{
	    if((isAlarmWarn() != 0)&&(Funcode.AlarmDis.value == 0))
		{
      		uKeyPara.bErr = 1;
      		uKeyPara.bAlarm = 1;		
    	}
		else
		{
      		uKeyPara.bAlarm = 0;
      		uKeyPara.bErr = 0;
      		uKeyPara.bErrFlag = 0;
		}
  	}
  	
  	KeyBoard_DealWork.KeyBoard.ErrCodeBak = GetErrorCode();
  	
  	if (KeyBoard_DealWork.KeyBoard.RunStsBak != uRunStopStatus1.bit.RunStatus)  // 处理运行中参数的修改属性
  	{
    	KeyBoard_DealWork.KeyBoard.RunStsBak = uRunStopStatus1.bit.RunStatus;
    	
    	for (b_k = 0U; b_k < SumFunc; b_k++) 
    	{
      		if (((Para[b_k] & (Uint16)0x0010) != 0U) // 可以在运行中更改
      			|| (((Para[b_k] & (Uint16)0x0020) != 0U) && (uRunStopStatus1.bit.RunStatus == 0)))   // 停机状态可更改 
      		{
        		(firstip + b_k)->modify = 1;
      		} 
      		else 
      		{
        		(firstip + b_k)->modify = 0;   // 只读参数，不可更改
      		}
    	}
  	}

  	KeyBoard_DealWork.KeyBoard.RefreshCnt++;
  	if (KeyBoard_DealWork.KeyBoard.RefreshCnt >= 2U)    // 停机和运行参数的刷新
  	{
    	KeyBoard_DealWork.KeyBoard.RefreshCnt = 0U;
    	KeyBoard_StopDataRefresh();
    	KeyBoard_RunDataRefresh();
  	}
  	
  	// KeyBoard_DealWork.KeyBoard.upper1 为当前主菜单下的子菜单个数-1
  	KeyBoard_DealWork.KeyBoard.upper1 = NumFunc[(int16)(KeyBoard_DealWork.KeyBoard.pos[0][0] + 1U)] - 1U;
  	
}

//*******************************************************************************************************************************
static void KeyBoard_enter_internal_Normal(void )
{
  KeyBoard_DealWork.KeyBoard.is_Normal = (Uint8)KeyBoard_In_RSDisplay;
  KeyBoard_enter_internal_RSDispl();
}

//**********************************************************************************************************************************
static void KeyBoard_Normal(void )
{
	if (KeyBoard_DealWork.KeyBoard.is_DataDisplay == (int16)KeyBoard_In_Normal) 
	{
    	if ((_sfEvent_KeyBoard_ == KeyBoard_event_CYCLEOVER) && (uKeyPara.bErr == 1))
    	{
      		KeyBoard_DealWork.KeyBoard.is_ParaAdjust = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_Normal = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_ErrDisplay;
      		if ((uKeyPara.bErrFlag == 0) && (uKeyPara.bAlarm == 0)) 
      		{
        		uKeyPara.bErrFlag = 1;
        		KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
        		KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
      		} 
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
        		uKeyPara.bErrFlag = 1;
      		}
      		uRunStopCmd1.bit.KBUP = 0;
      		uRunStopCmd1.bit.KBDN = 0;
    	} 
    	else if ((uKeyPara.bErr == 1) && (uKeyPara.bErrFlag == 0)) 
    	{
      		KeyBoard_DealWork.KeyBoard.is_ParaAdjust = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_Normal = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
      		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_ErrDisplay;
      		if ((uKeyPara.bErrFlag == 0) && (uKeyPara.bAlarm == 0)) 
      		{
        		uKeyPara.bErrFlag = 1;
        		KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
        		KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
      		} 
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
        		uKeyPara.bErrFlag = 1;
      		}
      		uRunStopCmd1.bit.KBUP = 0;
      		uRunStopCmd1.bit.KBDN = 0;
    	} 
    	else 
    	{
      		switch (KeyBoard_DealWork.KeyBoard.is_Normal) 
      		{
       			//=====================================================================================================
//       			case KeyBoard_In_ParaAdjust:   // 快闪模式，UP键或DN键改变设定频率
//        			break;
        		//=====================================================================================================	
       			case KeyBoard_In_RSDisplay:	   // 运行或停机参数显示
          			switch (KeyBoard_DealWork.KeyBoard.is_RSDisplay) 
          			{
           				//---------------------------------------------------------------------------------
           				case KeyBoard_In_RunDisplay:   //(1L)
            				KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;  //(0L)
            				KeyBoard_enter_internal_RSDispl();
            				break;
            			//---------------------------------------------------------------------------------	
           				case KeyBoard_In_StopDisplay:  //(2L)
            				KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;  //(0L)
            				KeyBoard_enter_internal_RSDispl();
            				break;
            			//---------------------------------------------------------------------------------	
          			}
        			break;
        		//=====================================================================================================	
      		}
    	}
  	}
}

//**********************************************************************************************************************************
// yshAC
static void KeyBoard_DataDisplay(void )
{
    if ((_sfEvent_KeyBoard_ == KeyBoard_event_ESC) && (KeyBoard_DealWork.KeyBoard.EnterPress == 0)) 
    {
    	KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
    	KeyBoard_DealWork.KeyBoard.is_ParaAdjust = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
    	KeyBoard_DealWork.KeyBoard.is_Normal = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
    	KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_NO_ACTIVE_CHILD;
    	
    	/*
    		数据显示模式下碰到 KeyBoard_event_ESC 事件，KeyBoard_DealWork.KeyBoard.is_Display 退出 KeyBoard_In_DataDisplay
    																						  进入 KeyBoard_In_FuncEdit 
    	*/
    	KeyBoard_DealWork.KeyBoard.is_Display = (Uint8)KeyBoard_In_FuncEdit; 

    	/*
    		KeyBoard_DealWork.KeyBoard.curpos 的说明：
    			== 0，当前菜单等级是0级，主菜单
    			== 1，当前菜单等级是1级，子菜单
    			== 2，当前菜单等级是2级，功能码数值
    	*/
    	KeyBoard_DealWork.KeyBoard.curpos = 1U;
    	
    	
    	/*
    		KeyBoard_DealWork.KeyBoard.flicker 的说明：
    			== 0，闪烁位为LED 0位置，最低位
    			== 1，闪烁位为LED 1位置
    			== 2，闪烁位为LED 2位置
    			== 3，闪烁位为LED 3位置
    			== 4，闪烁位为LED 4位置，最高位
    			== 5，全部都不闪烁
    			== 6，全闪烁
    			== 7，全快闪，闪烁周期缩短一半
    	*/         	 	
     	 KeyBoard_DealWork.KeyBoard.flicker = 0U;
    } 
    else 
    {
    	switch (KeyBoard_DealWork.KeyBoard.is_DataDisplay) 
    	{
    		//---------------------------------------------------
    		case KeyBoard_In_ErrDisplay:
    			KeyBoard_ErrDisplay();
    			break;
    		//---------------------------------------------------	
    		case KeyBoard_In_Normal:
    			KeyBoard_Normal();
    			break;
    		//---------------------------------------------------	
    	}
    }
}

//**********************************************************************************************************************************
static void KeyBoard_enter_internal_RSDispl(void )
{
	if (uRunStopStatus1.bit.RunStatus == 1) 
	{
    	KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_RunDisplay;
    	if ((_sfEvent_KeyBoard_ == KeyBoard_event_SHIFT) && (KeyBoard_DealWork.KeyBoard.FlagFromErr == 0U)) 
    	{
      		curRunData++;
    	}
    	KeyBoard_DealWork.KeyBoard.FlagFromErr = 0U;
    	goto label_1;
  	} 
  	else 
  	{
    	KeyBoard_DealWork.KeyBoard.is_RSDisplay = (Uint8)KeyBoard_In_StopDisplay;
    	if ((_sfEvent_KeyBoard_ == KeyBoard_event_SHIFT) && (KeyBoard_DealWork.KeyBoard.FlagFromErr == 0U)) 
    	{
      		curStopData++;
   	 	}
    	KeyBoard_DealWork.KeyBoard.FlagFromErr = 0U;
  	}
  	
label_2:;
	
	if (curStopData > 11U)  // sStopData结构体共12个成员
	{
    	curStopData = 0U;
    	KeyBoard_broadcast_CYCLEOVER();
    	if (KeyBoard_DealWork.KeyBoard.is_RSDisplay != (int16)KeyBoard_In_StopDisplay) 
    	{
      		return;
    	}
  	}
  	SDfuncip = SDfirstip + curStopData;
  	if (SDfuncip->ignore == 1) 
  	{
    	curStopData++;
    	goto label_2;
  	} 
  	else 
  	{
    	KeyBoard_DealWork.KeyBoard.Led = (Uint32)SDfuncip->value;
    	KeyBoard_DealWork.KeyBoard.flicker = 5U;
    	if ((curStopData == 0U) || (curStopData == 2U) || (curStopData == 5U) || (curStopData == 7U)) 
    	{
      		KeyBoard_DealWork.KeyBoard.flicker = 6U;
    	}
    	return;
  	}
  	
label_1:;
  	
  	if (curRunData >= 17U)   // sRunData结构体共17个成员
  	{
    	curRunData = 0U;
    	KeyBoard_broadcast_CYCLEOVER();
    	if (KeyBoard_DealWork.KeyBoard.is_RSDisplay != (int16)KeyBoard_In_RunDisplay) 
    	{
      		return;
    	}
  	}
  	RDfuncip = RDfirstip + curRunData;
  	if (RDfuncip->ignore == 1) 
  	{
    	curRunData++;
    	goto label_1;
  	} 
  	else 
  	{
    	KeyBoard_DealWork.KeyBoard.Led = (Uint32)RDfuncip->value;
    	KeyBoard_DealWork.KeyBoard.flicker = 5U;
    	if ((curRunData == 1U) || (curRunData == 4U) || (curRunData == 6U) || (curRunData == 14U)) 
    	{
      		KeyBoard_DealWork.KeyBoard.flicker = 6U;  // 参考值，全闪烁
    	}
  	}
}

//**********************************************************************************************************************************
static void KeyBoard_LEDDeal(void )
{
	int16 sf_i1;
	Uint32 LEDValue[5][1]; 
  	int16 b_i;
  	Uint32 b_LEDValue[5][1];
  	Uint16 Temp;
  	boolean_T Temp1;
  	boolean_T Temp2;
  	Uint32 c_lTemp;
  	
	//刚上电

    KeyBoard_DealWork.KeyBoard.pofftime++;
    if (KeyBoard_DealWork.KeyBoard.pofftime < 50U)   // 5.6s以内显示"BA+Date"
    {
      	LEDSeg[4] = SegGen[SoftVer1];
      	LEDSeg[3] = SegGen[SoftVer2];
      	LEDSeg[2] = SegGen[SoftVer3];
      	LEDSeg[1] = SegGen[SoftVer4];
      	LEDSeg[0] = SegGen[SoftVer5];
        goto label_1;
   } 
   else 
   {
        KeyBoard_DealWork.KeyBoard.pofftime = 100U;
   }
    
	
	//显示LU
	if((PowerIsOK == 0) && (KeyBoard_DealWork.KeyBoard.Poffflag == 1U)) 
    {
      	LEDSeg[4] = SegGen[16];
      	LEDSeg[3] = (Uint16)0xBF; //lxy100331 modify poff-> -LU- 0C
      	LEDSeg[2] = (Uint16)0xC7; //lxy100331 modify poff-> -LU- A3
      	LEDSeg[1] = (Uint16)0xC1; //lxy100331 modify poff-> -LU- 8E
      	LEDSeg[0] = (Uint16)0xBF; //lxy100331 modify poff-> -LU- 8E
    }
			
    KeyBoard_DealWork.KeyBoard.UnitFlicker = 0U;
    //显示功能码的编辑	
    if (KeyBoard_DealWork.KeyBoard.is_Display == (int16)KeyBoard_In_FuncEdit)   //  (2L)
    {
		if (KeyBoard_DealWork.KeyBoard.curpos != 2U) 
      	{
			KeyBoard_MenuLED();
		} 
		else if ((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x0001) == 0U) 
      	{
			KeyBoard_DecValueLED();
		} 
		else 
		{
			for(sf_i1 = 0; sf_i1 < 4; sf_i1++) 
        	{
          		LEDValue[sf_i1][0] = 0UL;
        	}
        	LEDValue[0][0] = KeyBoard_DealWork.KeyBoard.Led & (Uint32)0x0F;
        	LEDValue[1][0] = KeyBoard_DealWork.KeyBoard.Led >> 4UL & (Uint32)0x0F;
        	LEDValue[2][0] = KeyBoard_DealWork.KeyBoard.Led >> 8UL & (Uint32)0x0F;
        	LEDValue[3][0] = KeyBoard_DealWork.KeyBoard.Led >> 12UL & (Uint32)0x0F;
        	LEDSeg[0] = SegGen[LEDValue[0][0]];
        	LEDSeg[1] = SegGen[LEDValue[1][0]];
        	LEDSeg[2] = SegGen[LEDValue[2][0]];
        	LEDSeg[3] = SegGen[LEDValue[3][0]];
        	LEDSeg[4] = SegGen[16];
        	b_i = 3;
        	KeyBoard_DealWork.KeyBoard.MaxFlicker = 3U;
        	while (b_i >= 0) 
        	{
          		if ((UpLimit[KeyBoard_DealWork.KeyBoard.dot] & (Uint32)((Uint16)0x0F << (Uint16)(b_i << 2))) == 0UL) 
				{
            		LEDSeg[b_i] = SegGen[16];
          		} 
          		else 
          		{
            		KeyBoard_DealWork.KeyBoard.MaxFlicker = (Uint16)b_i;
            		b_i = 0;
          		}
          		b_i--;
        	}

		}
    }
	//显示故障
    else if (KeyBoard_DealWork.KeyBoard.is_DataDisplay == (int16)KeyBoard_In_ErrDisplay)  // (1L)
    {
		for (sf_i1 = 0; sf_i1 < 4; sf_i1++) 
      	{
        	LEDValue[sf_i1][0] = 0UL;
      	}
      	KeyBoard_DealWork.KeyBoard.flicker = 6U;
      	if (GetErrorCode() != 0) 
      	{
        	KeyBoard_DealWork.KeyBoard.Led = (Uint32)GetErrorCode();
        	LEDValue[4][0] = (Uint32)0x0E;
        	LEDValue[3][0] = (Uint32)0x17;

			if(KeyBoard_DealWork.KeyBoard.Led<LEDDisDataNumber)
			{
      		LEDValue[0][0] = LEDDisData[KeyBoard_DealWork.KeyBoard.Led - 1U][0];
      		LEDValue[1][0] = LEDDisData[KeyBoard_DealWork.KeyBoard.Led - 1U][1];
      		LEDValue[2][0] = LEDDisData[KeyBoard_DealWork.KeyBoard.Led - 1U][2];
			}
			
      		if ((LEDValue[0][0] == 0U) && (LEDValue[1][0] == 0U) && (LEDValue[2][0] == 0U))
      		{
      			LEDValue[0][0] = KeyBoard_DealWork.KeyBoard.Led % 10UL;
      			LEDValue[1][0] = KeyBoard_DealWork.KeyBoard.Led / 10UL;
      			LEDValue[2][0] = 0UL;
      		}			
      	}       	    	

      	LEDSeg[0] = SegGen[LEDValue[0][0]];
     	LEDSeg[1] = SegGen[LEDValue[1][0]];
      	LEDSeg[2] = SegGen[LEDValue[2][0]];
      	LEDSeg[3] = SegGen[LEDValue[3][0]];
      	LEDSeg[4] = SegGen[LEDValue[4][0]];   //lxy100409 0x0E
    } 
    else 
    {
		for (sf_i1 = 0; sf_i1 < 5; sf_i1++) 
		{
			b_LEDValue[sf_i1][0] = 0UL;
		}
      	if (KeyBoard_DealWork.KeyBoard.is_RSDisplay == (int16)KeyBoard_In_StopDisplay) 
       	{
        	RSfuncip = SDfuncip;
      	} 
      	else 
      	{
        	RSfuncip = RDfuncip;
      	}
      	Temp = (Uint16)RSfuncip->scal;
      	Temp1 = (RSfuncip->sign != 0);
      	Temp2 = (RSfuncip->flicker != 0);
      	
      	if (RSfuncip->bhex != 0 == 1) 
      	{
        	b_LEDValue[0][0] = KeyBoard_DealWork.KeyBoard.Led & (Uint32)0x0F;
        	b_LEDValue[1][0] = KeyBoard_DealWork.KeyBoard.Led >> 4UL & (Uint32)0x0F;
        	b_LEDValue[2][0] = KeyBoard_DealWork.KeyBoard.Led >> 8UL & (Uint32)0x0F;
        	b_LEDValue[3][0] = KeyBoard_DealWork.KeyBoard.Led >> 12UL & (Uint32)0x0F;
        	
        	LEDSeg[0] = SegGen[b_LEDValue[0][0]];
        	LEDSeg[1] = SegGen[b_LEDValue[1][0]];
        	LEDSeg[2] = SegGen[b_LEDValue[2][0]];
        	LEDSeg[3] = SegGen[b_LEDValue[3][0]];
        	LEDSeg[4] = SegGen[16];
      	} 
      	else 
      	{
        	if (KeyBoard_DealWork.KeyBoard.Led > 99999UL) 
        	{
          		c_lTemp = KeyBoard_DealWork.KeyBoard.Led / 10UL;
          		Temp--;
        	} 
        	else 
        	{
          		c_lTemp = KeyBoard_DealWork.KeyBoard.Led;
        	}
        	
        	b_LEDValue[0][0] = c_lTemp % 10UL;
        	b_LEDValue[1][0] = c_lTemp % 100UL / 10UL;
        	b_LEDValue[2][0] = c_lTemp % 1000UL / 100UL;
        	b_LEDValue[3][0] = c_lTemp % 10000UL / 1000UL;
        	b_LEDValue[4][0] = c_lTemp / 10000UL;
        	
        	LEDSeg[0] = SegGen[b_LEDValue[0][0]];
        	LEDSeg[1] = SegGen[b_LEDValue[1][0]];
        	LEDSeg[2] = SegGen[b_LEDValue[2][0]];
        	LEDSeg[3] = SegGen[b_LEDValue[3][0]];
        	LEDSeg[4] = SegGen[b_LEDValue[4][0]];
        	if(Temp < 4U) 
        	{
          		if(Temp > 0U) 
          		{
            		LEDSeg[Temp] &= (Uint16)0x7F;
          		}
          		for(b_i = 4; b_i > (int16)Temp; b_i--) 
          		{
            		if(b_LEDValue[b_i][0] == 0UL) 
            		{
              			LEDSeg[b_i] = SegGen[16];
            		} 
            		else 
            		{
              			b_i = 1;
            		}
          		}
        	}
        	if (Temp1 == 1) 
        	{
          		LEDSeg[4] = SegGen[17];
        	}
        	if (Temp2 == 1) 
        	{
          		KeyBoard_DealWork.KeyBoard.UnitFlicker = 1U;
        	}
      	}
    }
    
    if ((PowerIsOK == 0) && (KeyBoard_DealWork.KeyBoard.Poffflag == 1U)) 
    {
		LEDSeg[4] = SegGen[16];
		LEDSeg[3] = (Uint16)0xBF; //lxy100331 modify poff-> -LU- 0C
		LEDSeg[2] = (Uint16)0xC7; //lxy100331 modify poff-> -LU- A3
		LEDSeg[1] = (Uint16)0xC1; //lxy100331 modify poff-> -LU- 8E
		LEDSeg[0] = (Uint16)0xBF; //lxy100331 modify poff-> -LU- 8E
    }
    
label_1:;
	
	if (KeyBoard_DealWork.KeyBoard.flicker != 5U) 
	{  
		if ((KeyValue & (Uint16)0x48) != 0U) 
      	{
        	KeyBoard_DealWork.KeyBoard.UnitLightCnt = 0U;
      	}
      	if (KeyBoard_DealWork.KeyBoard.ShiftPress == 1U) 
      	{
        	KeyBoard_DealWork.KeyBoard.UnitLightCnt = 10U;
      	}
      	if (KeyBoard_DealWork.KeyBoard.UnitLightCnt < 20U) 
      	{
        	KeyBoard_DealWork.KeyBoard.UnitLightCnt++;
        	if (KeyBoard_DealWork.KeyBoard.flicker == 7U) 
        	{
				KeyBoard_DealWork.KeyBoard.UnitLightCnt++;
        	}
      	} 
      	else 
      	{
        	KeyBoard_DealWork.KeyBoard.UnitLightCnt = 0U;
      	}
      	
      	/* 
      		制造闪烁效果：UnitLightCnt 为0~10，全显示
      		              UnitLightCnt 为10~20，闪烁位灭灯
      		故效果是：闪烁位亮560ms，灭560ms
      		
      		注： KeyBoard_DealWork.KeyBoard.flicker 用以标示哪个LED要闪烁，具体的实现靠交替点亮
      		     和灭掉闪烁位，即此处的处理。
      	*/
      	if ((KeyBoard_DealWork.KeyBoard.UnitLightCnt > 10U) && (KeyBoard_DealWork.KeyBoard.UnitLightCnt < 20U)) 
      	{
        	if((KeyBoard_DealWork.KeyBoard.flicker == 6U) || (KeyBoard_DealWork.KeyBoard.flicker == 7U) 
        		|| ((PowerIsOK == 0) && (KeyBoard_DealWork.KeyBoard.Poffflag == 1U))) 
          	{// 满足此条件，5个LED全灭
          		LEDSeg[0] = SegGen[16];
          		LEDSeg[1] = SegGen[16];
          		LEDSeg[2] = SegGen[16];
          		LEDSeg[3] = SegGen[16];
          		LEDSeg[4] = SegGen[16];
        	} 
        	else 
        	{
          		LEDSeg[KeyBoard_DealWork.KeyBoard.flicker] = SegGen[16];   // 闪烁位的LED灭
        	}
      	}
    }
    if ((KeyBoard_DealWork.KeyBoard.curpos == 2U) && (KeyBoard_DealWork.KeyBoard.flicker < 5U) 
    	&& (KeyBoard_DealWork.KeyBoard.flicker > KeyBoard_DealWork.KeyBoard.MaxFlicker)) 
	{
		KeyBoard_DealWork.KeyBoard.flicker = KeyBoard_DealWork.KeyBoard.MaxFlicker;
	}
}

//**********************************************************************************************************************************
static void KeyBoard_DecValueLED(void )
{
	int16    b_i;
  	int16    sf_i2;
  	Uint32   LEDValue[5][1];
  	Uint16   Temp;
  	Uint32   RealValue;
	  	
	b_i = 0;
  	
	for (sf_i2 = 0; sf_i2 < 5; sf_i2++) 
  	{
    	LEDValue[sf_i2][0] = 0UL;
  	}
  	
  	Temp = Para[KeyBoard_DealWork.KeyBoard.dot] >> 1U & (Uint16)0x07;
  
  	if ((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x4000) != 0U) 
  	{
    	if (KeyBoard_DealWork.KeyBoard.Led < (UpLimit[KeyBoard_DealWork.KeyBoard.dot] >> 1UL)) 
    	{
      		RealValue = (UpLimit[KeyBoard_DealWork.KeyBoard.dot] >> 1UL) - KeyBoard_DealWork.KeyBoard.Led;
      		if (RealValue > 9999UL) 
      		{
        		RealValue /= 10UL;
        		Temp--;
      		}
      		if (RealValue > 9999UL) 
      		{
        		RealValue /= 10UL;
        		Temp--;
      		}
      		LEDValue[4][0] = 17UL;
    	}	 
    	else 
    	{
      		RealValue = KeyBoard_DealWork.KeyBoard.Led - (UpLimit[KeyBoard_DealWork.KeyBoard.dot] >> 1UL);
      		if (RealValue > 99999UL) 
      		{
        		RealValue /= 10UL;
        		Temp--;
      		}
    	}
  	} 
  	else if (KeyBoard_DealWork.KeyBoard.Led > 99999UL) 
  	{

      	RealValue = KeyBoard_DealWork.KeyBoard.Led / 10UL;
      	Temp--;

  	} 
  	else 
  	{
    	RealValue = KeyBoard_DealWork.KeyBoard.Led;
  	}
  	
  	LEDValue[0][0] = RealValue % 10UL;
  	LEDValue[1][0] = RealValue % 100UL / 10UL;
  	LEDValue[2][0] = RealValue % 1000UL / 100UL;
  	LEDValue[3][0] = RealValue % 10000UL / 1000UL;
  	if (LEDValue[4][0] != 17UL) 
  	{
    	LEDValue[4][0] = RealValue / 10000UL;
  	}
  	
  	LEDSeg[0] = SegGen[LEDValue[0][0]];
  	LEDSeg[1] = SegGen[LEDValue[1][0]];
  	LEDSeg[2] = SegGen[LEDValue[2][0]];
  	LEDSeg[3] = SegGen[LEDValue[3][0]];
  	LEDSeg[4] = SegGen[LEDValue[4][0]];
  	
  	if (Temp < 4U) 
  	{
    	if (Temp > 0U) 
    	{//lxy100719
//      		if (((KeyBoard_DealWork.KeyBoard.dot == FM2R2orEmf) || (KeyBoard_DealWork.KeyBoard.dot == FM1R2orEmf)) 
//      			&& (uRunStopStatus3.bit.MtrMode == 1))
//      		{
//      			//lxy100719
//      		}
      		//else
      		{
      			if (Funcode.ACRSlt.value == 0)
      			{
      			}
      			else
      			{
//      				if ((KeyBoard_DealWork.KeyBoard.dot == FM2R2orEmf ) || (KeyBoard_DealWork.KeyBoard.dot == FM1R2orEmf) 
//      					|| (KeyBoard_DealWork.KeyBoard.dot == (FM2R2orEmf - 2U)) || (KeyBoard_DealWork.KeyBoard.dot == (FM1R2orEmf- 2U)))
//      				{
//      					Temp--;
//      				}
//      				if ((KeyBoard_DealWork.KeyBoard.dot == (FM2R2orEmf - 1U)) || (KeyBoard_DealWork.KeyBoard.dot == (FM1R2orEmf- 1U)))
//      				{
//      					Temp++;
//      				}
      			}
      			LEDSeg[Temp] &= (Uint16)0x7F;
      		}
    	}
    	if (LEDSeg[4] == SegGen[17]) 
    	{
      		b_i = 3;
    	} 
    	else 
    	{
      		b_i = 4;
    	}
    	KeyBoard_DealWork.KeyBoard.MaxFlicker = Temp;
  	}
  	if ((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x0030) == 0U) 
  	{
    	while ((int32)b_i > (int32)Temp) 
  	 	{
      		if (LEDValue[b_i][0] == 0UL) 
      		{
        		LEDSeg[b_i] = SegGen[16];
      		} 
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.MaxFlicker = b_i;
        		b_i = 1;
      		}
      		b_i--;
    	}
  	} 
  	else if (UpLimit[KeyBoard_DealWork.KeyBoard.dot] <= 99999UL) 
  	{
    	while ((int32)b_i > (int32)Temp) 
    	{
      		if (UpLimit[KeyBoard_DealWork.KeyBoard.dot] / (Uint32)KeyBoard_power(10, (int16)b_i) == 0UL) 
      		{
        		LEDSeg[b_i] = SegGen[16];
      		}	 
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.MaxFlicker = b_i;
        		b_i = 1;
      		}
      		b_i--;
    	}
  	} 
  	else 
  	{
    	KeyBoard_DealWork.KeyBoard.MaxFlicker = b_i;
  	}
}

//**********************************************************************************************************************************
static void KeyBoard_MenuLED(void )
{
	int16    sf_i3;
  	Uint16   LEDValue[5][1];
  	Uint16   Temp;
  	
  	for (sf_i3 = 0; sf_i3 < 5; sf_i3++) 
  	{
    	LEDValue[sf_i3][0] = 0U;
  	} 	
  	/*
  		(1)
  			KeyBoard_DealWork.KeyBoard.pos[0][0] 表示当前LED显示内容所属主菜单的索引号
  			KeyBoard_DealWork.KeyBoard.pos[1][0] 表示当前LED显示内容所属子菜单的索引号
  				例如，假设现有功能码共6组，分别为P00，P02，P03，P04，P98，P99
  				如果当前LED显示停留在P98.06，则 KeyBoard_DealWork.KeyBoard.pos[0][0] = 4  // 表征是第5组主菜单
  			                                	KeyBoard_DealWork.KeyBoard.pos[1][0] = 6  // 表征是第7个子菜单
  				即使进入了P98.06菜单进行功能码参数的设置，上述两值也不变，因为它反映了一种归属关系。表征当前参数所属
  				主菜单和子菜单的索引号
  		
  		(2)	
  			NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] 的作用是根据主菜单的索引号，返回期望显示出来的主菜单号。
  				如上述(1)里所举的例子，假设现有功能码共6组，分别为P00，P02，P03，P04，P98，P99
  				则 NumGroup 会定义如下：
  										NumGroup[0] = 0
  										NumGroup[1] = 2
  										NumGroup[2] = 3
  										NumGroup[3] = 4
  										NumGroup[4] = 98
  										NumGroup[5] = 99			
  				当前LED显示停留在P98.06， KeyBoard_DealWork.KeyBoard.pos[0][0] = 4
  				NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] = NumGroup[4] = 98
  	*/
  	
  	Temp = NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]];
  	
  	LEDValue[0][0] = KeyBoard_DealWork.KeyBoard.pos[1][0] % 10U;    // LED最低位(bit0)的显示内容
  	LEDValue[1][0] = KeyBoard_DealWork.KeyBoard.pos[1][0] / 10U;    // LED次低位(bit1)的显示内容
  	LEDValue[2][0] = Temp % 10U;                                    // LED      (bit2)的显示内容 
  	LEDValue[3][0] = Temp / 10U;                                    // LED      (bit3)的显示内容
  	LEDValue[4][0] = (Uint16)0x13;                                // LED最高位(bit4)的显示内容  --> "P"

  	LEDSeg[0] = SegGen[(Uint32)LEDValue[0][0]];
  	LEDSeg[1] = SegGen[(Uint32)LEDValue[1][0]];
  	LEDSeg[2] = SegGen[(Uint32)LEDValue[2][0]] & (Uint16)0x7F;
  	LEDSeg[3] = SegGen[(Uint32)LEDValue[3][0]];
  	LEDSeg[4] = SegGen[(Uint32)LEDValue[4][0]];
  	
  	if (LEDSeg[3] == 0xB0)
  	{
  		LEDSeg[3] = (Uint16)0xC0;
  	}
}

//*********************************************************************************************************************
// yshAC
static void KeyBoard_RunDataRefresh(void)
{
	RunData.RDOutFreq.value = labs((int32)OutputFreq);
  	RunData.RDFreqRef.value = FreqRef;
  	RunData.RDOutCurr.value = OutputCurr;
  	RunData.RDOutSpd.value = StopData.SDOutSpd.value;
  	RunData.RDSpdRef.value = StopData.SDSpdRef.value;
  	RunData.RDOutVolt.value = OutputVolt;
  	RunData.RDDCVolt.value = VoltDC;
  	RunData.RDFreqRef.flicker = 1;
}

//*********************************************************************************************************************
// yshAC
static void KeyBoard_LEDLight(void )
{
	Uint16    Temp;
  	boolean_T   y;
  	
  	unnLEDLight.bit.bDirFWD = 1;
  	unnLEDLight.bit.bDirREV = 1;
  	
  	if (uRunStopStatus1.bit.RunStatus == 1) 
  	{
    	unnLEDLight.bit.bRun = 0;      // 运行灯亮
    	if(uRunStopStatus4.bit.MotorRunDirect == 0) 
    	{
      		unnLEDLight.bit.bDirFWD = 0;
    	} 
    	else 
    	{
      		unnLEDLight.bit.bDirREV = 0;
    	}
	} 
  	else 
  	{
    	unnLEDLight.bit.bRun = 1;  // 运行灯灭
  	}


	unnLEDLight.bit.bPanel = 0;
    unnLEDLight.bit.bAlarm = 1;
    unnLEDLight.bit.bMenuQuick = 1;   // quick灯灭
    unnLEDLight.bit.bMenuBasic = 0;   // basic灯亮

  	//if (GpioDataRegs.GPBDAT.bit.GPIOB1 == 0) //LXY100517
  	{
    	Temp = 0U;
    	unnLEDLight.bit.bUnitA = 1;
    	unnLEDLight.bit.bUnitV = 1;
    	if (KeyBoard_DealWork.KeyBoard.is_DataDisplay == (int16)KeyBoard_In_Normal) 
    	{
      		if (KeyBoard_DealWork.KeyBoard.is_RSDisplay == (int16)KeyBoard_In_StopDisplay) 
      		{
        		Temp = (Uint16)SDfuncip->unit;
      		}
      		else 
      		{
        		Temp = (Uint16)RDfuncip->unit;
      		}
    	} 
    	else if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
    	{
      		Temp = Para[KeyBoard_DealWork.KeyBoard.dot] >> 6U & (Uint16)0x07;
    	} 
    	else 
    	{
      		unnLEDLight.bit.bUnitH = 1;
      		unnLEDLight.bit.bUnitR = 1;
      		unnLEDLight.bit.bUnitM = 1;
      		goto label_1;
    	}
    	if (Temp != KeyBoard_DealWork.KeyBoard.UnitBak) 
    	{
     		unnLEDLight.bit.bUnitH = 1;
      		unnLEDLight.bit.bUnitR = 1;
      		unnLEDLight.bit.bUnitM = 1;
      		KeyBoard_DealWork.KeyBoard.UnitLightCnt = 0U;
    	}
    	if (Temp == 1U) 
    	{
      		y = 0U;
      		if ((KeyBoard_DealWork.KeyBoard.UnitFlicker == 1) && (KeyBoard_DealWork.KeyBoard.UnitLightCnt >= 10U)) 
      		{
        		y = 1U;
      		}
      		unnLEDLight.bit.bUnitH = y;
    	} 
    	else if (Temp == 2U) 
    	{	
      		unnLEDLight.bit.bUnitA = 0;
    	} 
    	else if (Temp == 3U) 
    	{
      		unnLEDLight.bit.bUnitV = 0;
    	} 
    	else if (Temp == 4U) 
    	{
      		y = 0U;
      		if ((KeyBoard_DealWork.KeyBoard.UnitFlicker == 1) && (KeyBoard_DealWork.KeyBoard.UnitLightCnt >= 10U)) 
      		{
        		y = 1U;
      		}
      		unnLEDLight.bit.bUnitR = y;
    	} 
    	else if (Temp == 5U) 
    	{	
      		y = 0U;
      		if ((KeyBoard_DealWork.KeyBoard.UnitFlicker == 1) && (KeyBoard_DealWork.KeyBoard.UnitLightCnt >= 10U)) 
      		{
        		y = 1U;
      		}
      		unnLEDLight.bit.bUnitM = y;
    	}
    	label_1:;
    	KeyBoard_DealWork.KeyBoard.UnitBak = Temp;
  	}
}

//********************************************************************************************************************************
// yshAC
static void KeyBoard_FuncMain(void )
{
  	Uint16    y;
	Uint32	  Temp;
  	 
  	if (_sfEvent_KeyBoard_ == KeyBoard_event_ENTER) 
  	{
		if ((KeyBoard_DealWork.KeyBoard.curpos < 2U))  // 当前为0级菜单或1级时，响应 KeyBoard_event_ENTER 事件
		{
			KeyBoard_DealWork.KeyBoard.curpos = 2U;   // 不管是0级还是1级菜单，ENTER后都进入2级菜单
        	KeyBoard_DealWork.KeyBoard.flicker = 0U;
        	//if (KeyBoard_DealWork.KeyBoard.dot == FFactoryPassWord) 
        	//{
          		//KeyBoard_DealWork.KeyBoard.Led = 0UL;  // 厂家密码功能码，进来显示0
        	//}		 
        	//else 
        	{
          		KeyBoard_DealWork.KeyBoard.Led = KeyBoard_GetValue(KeyBoard_DealWork.KeyBoard.dot);  // 显示功能码的值
        	}
        	
        	KeyBoard_DealWork.KeyBoard.UpperValue = UpLimit[KeyBoard_DealWork.KeyBoard.dot];  // 得到每个功能码的上限值
        	KeyBoard_DealWork.KeyBoard.LowerValue = 0UL;
        	

        	for (y = 1U; y < (DnNoZero[0] << 1U); y += 2U) //lxy100324 下限非零判断
        	{
          		if (KeyBoard_DealWork.KeyBoard.dot == DnNoZero[y]) 
          		{
            		KeyBoard_DealWork.KeyBoard.LowerValue = (Uint32)DnNoZero[(int16)(y + 1U)]; // 得到每个功能码的下限值
            		y = DnNoZero[0] << 1U;
          		}
        	}

			for(y = 1U; y < (UpRela[0] << 1U); y += 2U) //lxy100324 关联判断
        	{
          		if(KeyBoard_DealWork.KeyBoard.dot == UpRela[y]) 
          		{
            		Temp = KeyBoard_GetValue(UpRela[(int16)(y + 1U)]);
            		y = UpRela[0] << 1U;
            		if(Temp < KeyBoard_DealWork.KeyBoard.UpperValue) 
            		{
              			KeyBoard_DealWork.KeyBoard.UpperValue = Temp;
            		}
          		}
        	}
						
        	if (funcip->modify == 1) 
        	{
          		KeyBoard_DealWork.KeyBoard.flicker = 0U;
        	} 
        	else 
        	{
          		KeyBoard_DealWork.KeyBoard.flicker = 5U;
        	}
        	KeyBoard_DealWork.KeyBoard.flickerBak = 0U;
    	} 
    	else  // 当前为2级菜单时，响应 KeyBoard_event_ENTER 事件
    	{
      		KeyBoard_DealWork.KeyBoard.NeedUp = 1U;  // 参数设置完毕，子菜单上翻一次
      
      		if (funcip->modify == 1) 
      		{
        		KeyBoard_SetValue(KeyBoard_DealWork.KeyBoard.dot, KeyBoard_DealWork.KeyBoard.Led);   // 设定功能码的值
         		KeyBoard_SpecialFunc();  // 改变机型或运行停机显示参数
      		}
      		KeyBoard_DealWork.KeyBoard.curpos = 1U;
      		KeyBoard_DealWork.KeyBoard.Led = 0UL;
        	KeyBoard_DealWork.KeyBoard.flicker = 0U;
    	}
  	} 
  	else if (_sfEvent_KeyBoard_ == KeyBoard_event_UP) 
  	{
    	KeyBoard_UpManage();
  	} 
  	else if (_sfEvent_KeyBoard_ == KeyBoard_event_ESC) 
  	{
    	if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
    	{
      		KeyBoard_DealWork.KeyBoard.curpos = 1U;

        	KeyBoard_DealWork.KeyBoard.flicker = 0U;
    	}
  	} 
  	else if (_sfEvent_KeyBoard_ == KeyBoard_event_SHIFT) 
  	{
    	if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
    	{
      		if (!(KeyBoard_DealWork.KeyBoard.flicker == 5U)) 
      		{
        		if (KeyBoard_DealWork.KeyBoard.flicker > 0U) 
        		{
          			KeyBoard_DealWork.KeyBoard.flicker--;
        		} 
        		else 
        		{
          			KeyBoard_DealWork.KeyBoard.flicker = KeyBoard_DealWork.KeyBoard.MaxFlicker;
        		}
        		KeyBoard_DealWork.KeyBoard.flickerBak = KeyBoard_DealWork.KeyBoard.flicker;
      		}
    	}
    	else
    	{
      		if (KeyBoard_DealWork.KeyBoard.flicker > 0U) 
      		{
        		KeyBoard_DealWork.KeyBoard.flicker--;
      		}
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.flicker = 4U;
      		}
      		if (KeyBoard_DealWork.KeyBoard.flicker < 2U) 
      		{
        		KeyBoard_DealWork.KeyBoard.curpos = 1U;
      		} 
      		else 
      		{
        		KeyBoard_DealWork.KeyBoard.curpos = 0U;
      		}
    	}
  	}	 
  	else if (_sfEvent_KeyBoard_ == KeyBoard_event_DOWN) 
  	{
    	KeyBoard_DnManage();
  	} 
  	else 
  	{
    	if (KeyBoard_DealWork.KeyBoard.NeedUp == 1) 
    	{
      		KeyBoard_DealWork.KeyBoard.NeedUp = 0U;
      		KeyBoard_UpManage();
    	}
    	if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
    	{
      		if ((KeyBoard_DealWork.KeyBoard.dotLast == KeyBoard_DealWork.KeyBoard.dot) 
      			&& (KeyBoard_DealWork.KeyBoard.modifyLast != funcip->modify)) 
      		{
        		if (funcip->modify == 1) 
        		{
          			KeyBoard_DealWork.KeyBoard.flicker = KeyBoard_DealWork.KeyBoard.flickerBak;
        		} 
        		else 
        		{
          			KeyBoard_DealWork.KeyBoard.flicker = 5U;
        		}
      		}
      		KeyBoard_DealWork.KeyBoard.modifyLast = (funcip->modify != 0);
      		KeyBoard_DealWork.KeyBoard.dotLast = KeyBoard_DealWork.KeyBoard.dot;

			//Group update set
			if ((uKeyPara.bUserLock == 0) && ((KeyBoard_DealWork.KeyBoard.pos[0][0] == 01U)||
												((KeyBoard_DealWork.KeyBoard.pos[0][0] == 12U)
												&&(KeyBoard_DealWork.KeyBoard.pos[0][1]>=4U))
												)) 
			{
				KeyBoard_DealWork.KeyBoard.F01RefrCnt++;
				if (KeyBoard_DealWork.KeyBoard.F01RefrCnt >= 2U) 
				{
					KeyBoard_DealWork.KeyBoard.F01RefrCnt = 0U;
					KeyBoard_DealWork.KeyBoard.Led = KeyBoard_GetValue(KeyBoard_DealWork.KeyBoard.dot);
				}
			} 
			else 
			{
				KeyBoard_DealWork.KeyBoard.F01RefrCnt = 0U;
			}      		
    	}

    	return;
  	}
}


//********************************************************************************************************************************
// yshAC
static void KeyBoard_SpecialFunc(void )
{
/*  	if (KeyBoard_DealWork.KeyBoard.dot == FRunLedPara1) 
  	{
    	KeyBoard_RunLedParam1D();
  	}
	else*/ 
	if (KeyBoard_DealWork.KeyBoard.dot == FParaInit) 
  	{
    	KeyBoard_ParaInitD();
  	}
  	/*else if (KeyBoard_DealWork.KeyBoard.dot == FRunLedPara2) 
  	{
    	KeyBoard_RunLedParam2D();
  	} 
  	else if (KeyBoard_DealWork.KeyBoard.dot == FStopLedPara) 
  	{
    	KeyBoard_StopLedParamD();
  	} 
 
  	else if ((KeyBoard_DealWork.KeyBoard.dot == FModuleSet) && (funcip->changed == 1)) 
  	{
    	//KeyBoard_ModuleSetD();    // 改变机型
  	} 
	else*/ 
	else if (KeyBoard_DealWork.KeyBoard.dot == FRunCmdChannel) 
  	{
    		uRunStopCmd1.bit.CmdChFCSet = 1;	
  	}

	else if(KeyBoard_DealWork.KeyBoard.dot == FErrNumber)
	{
		FlagShowErr = 1;
	}
  	else if (KeyBoard_DealWork.KeyBoard.dot == FTorqSpdSelect) 
  	{
    	uRunStopCmd1.bit.Torq2SpdFCSet = 1;
  	}
	
}


//********************************************************************************************************************************
// 定义每个参数的modify属性

void KeyBoard_ParaProtectD(void)
{
	Uint16   b_i;
	b_i = 0U;

	while (b_i < SumFunc) 
	{
		funcipTP = firstip + b_i;
      	if (((Para[b_i] & (Uint16)0x0010) != 0U)     // 停机运行均可更改
      		|| (((Para[b_i] & (Uint16)0x0020) != 0U) && (uRunStopStatus1.bit.RunStatus == 0)))    // 停机可更改 
      	{
        	funcipTP->modify = 1;
      	} 
      	else 
      	{
        	funcipTP->modify = 0;
      	}
      	b_i++;
	}
}

void KeyBoard_ParaInitD(void )
{
  Uint16 b_i;
  b_i = 0U;
  if((firstip + FParaInit)->value == 1) 		//clear error record 
  {
  	NoticeClearError();
    (firstip + FParaInit)->value = 0;
  } 
  else 
  {
    uKeyPara.bParaInit = 1;
    if((firstip + FParaInit)->value == 2) 		//restore factore para
    {
      while(b_i < SumFunc) 
      {
        if((Para[b_i] & (Uint16)0x0400) != 0U) 
        {
          KeyBoard_SetValue(b_i, (Uint32)OrgValue[b_i]);
        }
        b_i++;
      }
      uRunStopCmd1.bit.CmdChFCSet = 1;
	  uRunStopCmd1.bit.Torq2SpdFCSet = 1;

      curStopData = 0U;
      curRunData = 0U;
    } 
    else if((firstip + FParaInit)->value == 3) //only restore quick para
    {
      while(b_i < SumFunc) 
      {
        funcipTP = firstip + b_i;
        if(((Para[b_i] & (Uint16)0x0800) != 0U) && ((Para[b_i] &
           (Uint16)0x0400) != 0U)) 
        {
          KeyBoard_SetValue(b_i, (Uint32)OrgValue[b_i]);
        }
        b_i++;
      }
      uRunStopCmd1.bit.CmdChFCSet = 1;
    } 
    
    else 
    {
      uKeyPara.bParaInit = 0;
      
      return;
    }
    /* SpecialFunc.X8FuncD(); */
    KeyBoard_RunLedParam1D();
    KeyBoard_RunLedParam2D();
    KeyBoard_StopLedParamD();
    KeyBoard_ParaProtectD();
    KeyBoard_DealWork.KeyBoard.NeedUp = 0U;
    (firstip + FParaInit)->value = 0;
    uKeyPara.bParaInit = 0;
    
    KeyBoard_DealWork.KeyBoard.pos[0][0] = 0U;
    KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
    KeyBoard_DealWork.KeyBoard.dot = 0U;
    funcip = firstip;
  }
}

//********************************************************************************************************************************
void KeyBoard_StopLedParamD(void)
{
  Uint32 Temp;
  Temp = 0x09;//(Uint32)(firstip + FStopLedPara)->value;
  StopData.SDFreqRef.ignore = ((Temp & (Uint32)0x0001) == 0UL);
  StopData.SDOutSpd.ignore = ((Temp & (Uint32)0x0002) == 0UL);
  StopData.SDSpdRef.ignore = ((Temp & (Uint32)0x0004) == 0UL);
  StopData.SDDCVolt.ignore = ((Temp & (Uint32)0x0008) == 0UL);
  StopData.SDOutLSpd.ignore = ((Temp & (Uint32)0x0010) == 0UL);
  StopData.SDLSpdRef.ignore = ((Temp & (Uint32)0x0020) == 0UL);
  StopData.SDPIDFB.ignore = ((Temp & (Uint32)0x0040) == 0UL);
  StopData.SDPIDRef.ignore = ((Temp & (Uint32)0x0080) == 0UL);
  StopData.SDAI1Volt.ignore = ((Temp & (Uint32)0x0100) == 0UL);
  StopData.SDAI2Volt.ignore = ((Temp & (Uint32)0x0200) == 0UL);
  StopData.SDAI3Volt.ignore = ((Temp & (Uint32)0x0400) == 0UL);
  StopData.SDDITermSts.ignore = ((Temp & (Uint32)0x0800) == 0UL);
  if(Temp == 0UL) {
    StopData.SDFreqRef.ignore = 0;
  }
}
void KeyBoard_RunLedParam1D(void)
{
  Uint32 Temp;
  Temp = 0x07;//(Uint32)(firstip + FRunLedPara1)->value;
  RunData.RDOutFreq.ignore = ((Temp & (Uint32)0x0001) == 0UL);
  RunData.RDFreqRef.ignore = ((Temp & (Uint32)0x0002) == 0UL);
  RunData.RDOutCurr.ignore = ((Temp & (Uint32)0x0004) == 0UL);
  RunData.RDOutSpd.ignore = ((Temp & (Uint32)0x0010) == 0UL);
  RunData.RDSpdRef.ignore = ((Temp & (Uint32)0x0020) == 0UL);
  RunData.RDOutLSpd.ignore = ((Temp & (Uint32)0x0040) == 0UL);
  RunData.RDLSpdRef.ignore = ((Temp & (Uint32)0x0080) == 0UL);
  RunData.RDOutPower.ignore = ((Temp & (Uint32)0x0100) == 0UL);
  RunData.RDOutTorq.ignore = ((Temp & (Uint32)0x0200) == 0UL);
  if(Temp == 0UL) {
    RunData.RDOutFreq.ignore = 0;
  }
}
void KeyBoard_RunLedParam2D(void)
{
  Uint32 Temp;
  Temp = 0x00;//(Uint32)(firstip + FRunLedPara2)->value;
  RunData.RDOutVolt.ignore = ((Temp & (Uint32)0x0001) == 0UL);
  RunData.RDAI1Volt.ignore = ((Temp & (Uint32)0x0002) == 0UL);
  RunData.RDAI2Volt.ignore = ((Temp & (Uint32)0x0004) == 0UL);
  RunData.RDAI3Volt.ignore = ((Temp & (Uint32)0x0008) == 0UL);
  RunData.RDPIDFB.ignore = ((Temp & (Uint32)0x0010) == 0UL);
  RunData.RDPIDRef.ignore = ((Temp & (Uint32)0x0020) == 0UL);
  RunData.RDDITermSts.ignore = ((Temp & (Uint32)0x0040) == 0UL);
  RunData.RDDCVolt.ignore = ((Temp & (Uint32)0x0080) == 0UL);
}


//**************************************************************************************************************************
// yshAC
static void KeyBoard_StopDataRefresh(void)
{  
  	StopData.SDFreqRef.value = labs(FreqRef);    // 参考频率 
  	StopData.SDDCVolt.value = VoltDC;      // DC电压
}

//********************************************************************************************************************************
// yshAC
static void KeyBoard_UpManage(void )
{
	Uint16    temp;
	Uint16    Temp1;
	Uint16    b_i;
	Uint16    x;
	Uint16    b_Temp1;
	Uint16    Temp2;
	boolean_T   y;
	boolean_T   b_y;
	int16     initialdot;
	  
	if (KeyBoard_DealWork.KeyBoard.curpos == 2U) 
	{
		if (KeyBoard_DealWork.KeyBoard.flicker != 5U) 
		{
			if ((Para[KeyBoard_DealWork.KeyBoard.dot] & (Uint16)0x0001) == 0U)   // 十进制约束
			{
            	temp = KeyBoard_DealWork.KeyBoard.flicker;

          		KeyBoard_DealWork.KeyBoard.Led += (Uint32)KeyBoard_power(10, (int16)temp); // 个位加1，十位加10，百位加100 ...

          		if (KeyBoard_DealWork.KeyBoard.Led > KeyBoard_DealWork.KeyBoard.UpperValue) 
          		{
            		KeyBoard_DealWork.KeyBoard.Led = KeyBoard_DealWork.KeyBoard.UpperValue;
          		}
          		if (KeyBoard_DealWork.KeyBoard.Led < KeyBoard_DealWork.KeyBoard.LowerValue) 
          		{
            		KeyBoard_DealWork.KeyBoard.Led = KeyBoard_DealWork.KeyBoard.LowerValue;
          		}
      		} 
      		else if ((KeyBoard_DealWork.KeyBoard.Led >> (Uint32)(KeyBoard_DealWork.KeyBoard.flicker << 2U) & (Uint32)0x0F) 
      				 < (UpLimit[KeyBoard_DealWork.KeyBoard.dot] >> (Uint32)(KeyBoard_DealWork.KeyBoard.flicker << 2U) & (Uint32)0x0F)) 
			{
				KeyBoard_DealWork.KeyBoard.Led += (Uint32)(1 << (KeyBoard_DealWork.KeyBoard.flicker << 2U));
			}
		}
	} 
	else // 完全菜单模式
	{
		
label_4:;
	
		if ((KeyBoard_DealWork.KeyBoard.curpos == 0U) && (KeyBoard_DealWork.KeyBoard.flicker != 4)) 
		{
			KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
			if ((KeyBoard_DealWork.KeyBoard.flicker == 2U) && (KeyBoard_DealWork.KeyBoard.pos[0][0] < NumFunc[0])) 
      		{
        		goto label_1;
      		} 
      		else if (KeyBoard_DealWork.KeyBoard.pos[0][0] == NumFunc[0]) 
      		{
        		KeyBoard_DealWork.KeyBoard.pos[0][0] = 0U;
        		goto label_2;
      		} 
      		else if ((NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] >= 90U) 
      			|| (KeyBoard_DealWork.KeyBoard.pos[0][0] > NumFunc[0])) 
      		{
        		KeyBoard_DealWork.KeyBoard.pos[0][0] = NumFunc[0];
        		goto label_2;
      		} 
      		else 
      		{
        		Temp1 = NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] / 10U;
        		while(1) 
        		{
          			b_i = Temp1 + 1U;
          			if (FuncGroup[b_i] != 0) 
          			{
            			break;
          			}
          			Temp1++;
        		}
       		 	Temp1 = 10U * b_i + NumGroup[KeyBoard_DealWork.KeyBoard.pos[0][0]] % 10U;
        		temp = 1U;
      		}
      		
label_3:;
      		if (temp <= NumFunc[0]) 
      		{
        		if (Temp1 == NumGroup[temp]) 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[0][0] = temp;
          			x = KeyBoard_DealWork.KeyBoard.pos[0][0];
          			b_Temp1 = x >> 4U;
          			if ((x & (Uint16)0x0F) == 15U) 
          			{
            			Temp2 = 32768U;
          			} 
          			else 
          			{
            			Temp2 = (Uint16)(1 << (x & (Uint16)0x0F));
          			}
          			if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[b_Temp1] & Temp2) == 0U) 
          			{
            			y = 0U;
          			} 
          			else 
         	 		{
            			y = 1U;
          			}
          			if (y == 0) 
          			{
            			goto label_2;
          			} 
          			else 
          			{
            			temp = NumFunc[0];
          			}
        		}
      		} 
      		else 
      		{
        		Temp1 = 0U;
       	 		for (temp = 0U; temp < b_i; temp++) 
        		{
          			Temp1 += FuncGroup[temp];
        		}
        		KeyBoard_DealWork.KeyBoard.pos[0][0] = Temp1;
        		if (unnLEDLight.bit.btest == 0)
        		{
	        		if ((KeyBoard_DealWork.KeyBoard.pos[0][0] >=21U) && (KeyBoard_DealWork.KeyBoard.pos[0][0] <=25U))			//CH091217
	      			{
	      				goto label_1;
	      			}
	     		}
	     		else
	     		{
	     			if (KeyBoard_DealWork.KeyBoard.pos[0][0] >=26U)
	     			{
	     				KeyBoard_DealWork.KeyBoard.pos[0][0] = 20U;
	     			}
	     		}
       	 		goto label_2;
      		}
      		temp++;  		
			goto label_3;
			
label_1:;
	
			KeyBoard_DealWork.KeyBoard.pos[0][0]++;
      		if (unnLEDLight.bit.btest == 0)
      		{
	      		if ((KeyBoard_DealWork.KeyBoard.pos[0][0] >=21U) && (KeyBoard_DealWork.KeyBoard.pos[0][0] <=25U))  
				{
					goto label_1;
				}
			}
      		else
	  		{
	     		if (KeyBoard_DealWork.KeyBoard.pos[0][0] >=26U)
	     		{
	     			KeyBoard_DealWork.KeyBoard.pos[0][0] = 20U;
	     		}
	  		}
	  		
label_2:;
	
			temp = KeyBoard_DealWork.KeyBoard.pos[0][0];
      		Temp1 = temp >> 4U;
      		if ((temp & (Uint16)0x0F) == 15U) 
      		{
        		temp = 32768U;
      		} 
      		else 
      		{
        		temp = (Uint16)(1 << (temp & (Uint16)0x0F));
      		}
      		if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[Temp1] & temp) == 0U) 
      		{
        		b_y = 0U;
      		} 
      		else 
      		{
        		b_y = 1U;
      		}
      		if (b_y == 1) 
      		{
        		goto label_1;
      		}
      		while(1) 
      		{
        		initialdot = 0;
        		for (temp = 0U; temp < KeyBoard_DealWork.KeyBoard.pos[0][0]; temp++) 
        		{
          			initialdot = (int16)((Uint16)initialdot + NumFunc[(int16)(temp + 1U)]);
        		}
        		KeyBoard_DealWork.KeyBoard.dot = (Uint16)initialdot + KeyBoard_DealWork.KeyBoard.pos[1][0];
        		funcip = firstip + KeyBoard_DealWork.KeyBoard.dot;
        		if (funcip->ignore != 1) 
        		{
					break;
				}
        		KeyBoard_DealWork.KeyBoard.pos[1][0]++;
      		}
    	} 
    	else 
    	{
      		temp = KeyBoard_DealWork.KeyBoard.pos[0][0];
      		Temp1 = temp >> 4U;
      		if ((temp & (Uint16)0x0F) == 15U) 
      		{
        		temp = 32768U;
      		} 
      		else 
      		{
        		temp = (Uint16)(1 << (temp & (Uint16)0x0F));
      		}
      		if ((KeyBoard_DealWork.KeyBoard.GroupIgnore[Temp1] & temp) == 0U) 
      		{
        		b_y = 0U;
      		} 
      		else 
      		{
       	 		b_y = 1U;
      		}
      		if (b_y == 1) 
      		{
        		KeyBoard_DealWork.KeyBoard.curpos = 0U;
        		KeyBoard_DealWork.KeyBoard.flicker = 2U;
        		goto label_4;
      		} 
      		else 
      		{
        		if (KeyBoard_DealWork.KeyBoard.pos[1][0] == KeyBoard_DealWork.KeyBoard.upper1)  // 子菜单上翻到顶，从零开始
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = 0U;
        		} 
        		else 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = (Uint16)((int32)KeyBoard_DealWork.KeyBoard.pos[1][0] 
          					+ KeyBoard_power(10, (int16)KeyBoard_DealWork.KeyBoard.flicker));
          			goto label_5;
        		}
        		
label_7:;
	
        		initialdot = 0;
        		for (temp = 0U; temp < KeyBoard_DealWork.KeyBoard.pos[0][0]; temp++) 
        		{
          			initialdot = (int16)((Uint16)initialdot + NumFunc[(int16)(temp + 1U)]);
        		}
        		KeyBoard_DealWork.KeyBoard.dot = (Uint16)initialdot + KeyBoard_DealWork.KeyBoard.pos[1][0];
        		funcip = firstip + KeyBoard_DealWork.KeyBoard.dot;
        		goto label_6;
        		
label_5:;
	
        		if (KeyBoard_DealWork.KeyBoard.pos[1][0] >= KeyBoard_DealWork.KeyBoard.upper1) 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0] = KeyBoard_DealWork.KeyBoard.upper1;
        		}
        		goto label_7;
        		
label_6:;
	
        		if (funcip->ignore == 1) 
        		{
          			KeyBoard_DealWork.KeyBoard.pos[1][0]++;
					
					if (KeyBoard_DealWork.KeyBoard.pos[1][0] >= KeyBoard_DealWork.KeyBoard.upper1) 
        			{
          				KeyBoard_DealWork.KeyBoard.pos[1][0] = 0;
        			}
					
          			goto label_5;
        		}
      		}
    	}
  	} 
}

//********************************************************************************************************************
void KeyBoard_RatedVolt(void)
{

  //Funcode.DCLVLevel.value = Funcode.RatedVoltage.value * 90U / 100U;//lxy100628
  //Funcode.DCLVLevel.changed = 1;


}



//********************************************************************************************************************************
// yshAC  键盘的起停事件处理， 即 KeyBoard_event_RUN 和 KeyBoard_event_STOP 事件处理

static void KeyBoard_KeyCmd(void )
{
	int32 Stopcnt;
	
	if (_sfEvent_KeyBoard_ == KeyBoard_event_RUN)   // 运行
    {
		uRunStopCmd4.bit.KeyRun = 1;
		uRunStopCmd1.bit.KBRun = 1;
    } 
	else if (_sfEvent_KeyBoard_ == KeyBoard_event_STOP) 
	{
		Stopcnt = (int32)Time1msBase;
		
		if ((labs(Stopcnt - KeyBoard_DealWork.KeyBoard.Stopcntbak) < 1000L) && (uRunStopStatus1.bit.RunStatus == 1)) 
		{
			uRunStopCmd1.bit.KBEmergStop = 1;   // STOP双击，急停
			KeyBoard_DealWork.KeyBoard.Stopcntbak = Stopcnt;
		} 
		else 
		{
			KeyBoard_DealWork.KeyBoard.Stopcntbak = Stopcnt;
			if (uRunStopStatus1.bit.RunStatus == 0) 
			{
	        	uRunStopCmd1.bit.KBReset = 1;   // 键盘复位
	        } 
	        else if (uRunStopStatus2.bit.CmdChannel == 0) 
	        {
	        	uRunStopCmd4.bit.KeyStop = 1;   // 正常停机
	        	uRunStopCmd1.bit.KBRun = 0;
	        }
		}
	} 
}


//**********************************************************************************************************************************
static void KeyBoard_broadcast_CYCLEOVER(void )
{
	Uint8 b_previousEvent;
	  
	b_previousEvent = _sfEvent_KeyBoard_;     // 备份此前的keyBoard事件
  	_sfEvent_KeyBoard_ = KeyBoard_event_CYCLEOVER;  // 指示当前的keyBoard事件为 KeyBoard_event_CYCLEOVER 事件
	  
	KeyBoard_DataDisplay();   
	
	_sfEvent_KeyBoard_ = b_previousEvent;    // 恢复此前的keyBoard事件
}

//**********************************************************************************************************************************
void KeyBoard_KB(void)
{
    _sfEvent_KeyBoard_ = CALL_EVENT;    //     #define CALL_EVENT   255
    
	if (KeyBoard_DealWork.KeyBoard.is_active_c1_KBManage == 0)    // 初始化
	{
		KeyBoard_DealWork.KeyBoard.is_active_c1_KBManage = 1U;
		if (KeyBoard_DealWork.KeyBoard.is_active_DataDeal != 1) 
		{
        	KeyBoard_DealWork.KeyBoard.UnitFlicker = 0U;
        	//KeyBoard_DealWork.KeyBoard.F01cnt = 0;
        	KeyBoard_DealWork.KeyBoard.UnitLightCnt = 0U;
        	KeyBoard_DealWork.KeyBoard.Poffflag = 0U;
	        KeyBoard_DealWork.KeyBoard.pofftime = 0U;
	        KeyBoard_DealWork.KeyBoard.ShiftPress = 0U;
	        KeyBoard_DealWork.KeyBoard.is_active_DataDeal = 1U;
	        KeyBoard_DealWork.KeyBoard.flicker = 5U;
	        KeyBoard_DealWork.KeyBoard.curpos = 1U;
	        KeyBoard_DealWork.KeyBoard.dot = 0U;
	         
	        firstip = &Funcode.MenuModeSlt;        // 功能码首指针

	        funcip = firstip;     // 功能码指针赋初值
	        
	        SDfirstip = &StopData.SDFreqRef;   // 停机显示数据首指针
	        RDfirstip = &RunData.RDOutFreq;    // 运行显示数据首指针
	        SDfuncip = SDfirstip;    // 停机显示数据指针赋初值
	        RDfuncip = RDfirstip;    // 运行显示数据指针赋初值
	        RSfuncip = SDfuncip;
	        
	        
	        if (GetErrorCode() != 0) 
	        {
	          	uKeyPara.bErr = 1;
	        } 
	        else 
	        {
	          	uKeyPara.bErr = 0;
	        }
	        StopData.SDFreqRef.scal = 2;
	        StopData.SDOutSpd.scal = 1;
	        StopData.SDDCVolt.scal = 0;

	        StopData.SDFreqRef.unit = 1;
	        StopData.SDOutSpd.unit = 4;
	        StopData.SDDCVolt.unit = 3;

	        RunData.RDOutFreq.scal = 2;
	        RunData.RDFreqRef.scal = 2;
	        RunData.RDOutCurr.scal = 1;
	        RunData.RDOutSpd.scal = 1;
	        RunData.RDOutLSpd.scal = 2;
	        RunData.RDOutPower.scal = 1;
	        RunData.RDOutVolt.scal = 0;
	        RunData.RDDCVolt.scal = 0;
	        
	        RunData.RDOutFreq.unit = 1;
	        RunData.RDFreqRef.unit = 1;
	        RunData.RDOutCurr.unit = 2;
	        RunData.RDOutSpd.unit = 4;
	        RunData.RDOutVolt.unit = 3;        
	        RunData.RDDCVolt.unit = 3;


	        KeyBoard_RunLedParam1D();
	        KeyBoard_RunLedParam2D();
	        KeyBoard_StopLedParamD();
	        
	        KeyBoard_ParaProtectD();  // 定义每个参数的modify属性
			 
	        KeyBoard_DealWork.KeyBoard.dot = 0U;

	        KeyBoard_DealWork.KeyBoard.Panelflag = (Uint16)uRunStopCmd4.bit.KBPanel;
	        
	        KeyBoard_StopDataRefresh();
      	}
      	if (KeyBoard_DealWork.KeyBoard.is_active_DataDeal != 0) 
      	{
        	KeyBoard_DealWork.KeyBoard.LowerValue = 0UL;
        	KeyBoard_DealWork.KeyBoard.UpperValue = 0UL;

        	KeyBoard_DealWork.KeyBoard.dotBak = 0U;
        	KeyBoard_DealWork.KeyBoard.is_active_Display = 1U;
        	KeyBoard_DealWork.KeyBoard.FlagFromErr = 0U;
        	KeyBoard_DealWork.KeyBoard.is_Display = (Uint8)KeyBoard_In_DataDisplay;
        	if (uKeyPara.bErr == 1) 
        	{
          		if (KeyBoard_DealWork.KeyBoard.is_DataDisplay != (int16)KeyBoard_In_ErrDisplay) 
          		{
            		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_ErrDisplay;
            		if ((uKeyPara.bErrFlag == 0) && (uKeyPara.bAlarm == 0)) 
            		{
              			uKeyPara.bErrFlag = 1;
              			KeyBoard_DealWork.KeyBoard.ErrIndex = GetErrorCode();
              			KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
            		} 
            		else 
            		{
              			KeyBoard_DealWork.KeyBoard.Led = (Uint32)KeyBoard_DealWork.KeyBoard.ErrIndex;
              			uKeyPara.bErrFlag = 1;
            		}
            		uRunStopCmd1.bit.KBUP = 0;
            		uRunStopCmd1.bit.KBDN = 0;
          		}
        	} 
        	else 
        	{
          		KeyBoard_DealWork.KeyBoard.is_DataDisplay = (Uint8)KeyBoard_In_Normal;
          		KeyBoard_enter_internal_Normal();
        	}
      	}
    }	 
    else 
    {
		KeyBoard_FromKB();      // 得到 _sfEvent_KeyBoard_ 的值  ,Get the press key value
        KeyBoard_LEDDeal();     // 得到5个LED当前的显示内容 LEDSeg[0]~LEDSeg[4]
        KeyBoard_LEDLight();    // 得到灯的亮灭状态
        KeyBoard_ParaRefresh();
		
        KeyBoard_KeyCmd();
     	
		switch (KeyBoard_DealWork.KeyBoard.is_Display) 
        {
        	//----------------------------------------------------
        	case KeyBoard_In_DataDisplay:
        		
          		KeyBoard_DataDisplay();
          		
          		break;
          	//----------------------------------------------------	
         	case KeyBoard_In_FuncEdit:
         		
          		KeyBoard_FuncEdit();
          		
				break;
			//----------------------------------------------------	
		}
	}
	
}

//**********************************************************************************************************************************

static void KeyBoard_FuncodeRela(void )			/*参数的隐藏*/
{
	//KeyBoard_HideGroup(7,NULL);
	//KeyBoard_HideGroup(9,NULL);
	//KeyBoard_HideGroup(10,NULL);

	//KeyBoard_HideGroup(13,NULL);	

	//F00

	Funcode.MenuModeSlt.ignore = 1;
	Funcode.ParaCopy.ignore = 1;

	Funcode.AI1Volt.ignore = 1;
	Funcode.AI2Volt.ignore = 1;

	Funcode.DCCur.ignore = 1;	

	//F03
	
	Funcode.M1PowerFactor.ignore = 1;
	Funcode.M1OLAlarm.ignore = 1;
    Funcode.M1OLCoeff.ignore = 1;
	Funcode.M1OLTime.ignore = 1;
	Funcode.DeratFact2.ignore = 1;
	Funcode.DeratFact1.ignore = 1;
	Funcode.M1OLValue.ignore = 1;
	


	Funcode.SMZPlsAng.ignore = 1;



	Funcode.TorqLmtRsvPos.ignore = 1;
	Funcode.TorqLmtRsvNeg.ignore = 1;


	Funcode.AccMax.ignore = 1;
	Funcode.AccJerkStart.ignore = 1;
	Funcode.AccJerkEnd.ignore = 1;
	Funcode.DecJerkStart.ignore = 1;
	Funcode.AccJerkEnd.ignore = 1;
	
	Funcode.DecMax.ignore = 1;
	Funcode.DecJerkEnd.ignore = 1;
	Funcode.DecJerkEnd.ignore = 1;	


	
	//F12

	Funcode.CarrierFrq.ignore = 1;               
	Funcode.ACRSlt.ignore = 1;

	Funcode.DeltaFrqComVolt.ignore = 1;  
   

	Funcode.ErrMDISts.ignore = 1;
	Funcode.RSV28.ignore = 1;
	Funcode.RSV29.ignore = 1;
	Funcode.RSV30.ignore = 1;
	Funcode.RSV34.ignore = 1;

	
	
	//F99
	Funcode.Ipeak.ignore = 1;

	Funcode.WarnMotorSpeedOVFWD.ignore = 1;
	Funcode.WarnMotorSpeedOVREV.ignore = 1;
	Funcode.WarnMotorOTLevel.ignore = 1;
}

/*
static void KeyBoard_HideGroup(uint16 x, void *reserved )
{
  	uint16 b_i;
  	uint16 y;
  	uint16 c_i;
  	b_i = 0U;
  	label_1:;
  	if(b_i <= NumFunc[0]) 
  	{
    	if(NumGroup[b_i] == x) 
    	{
      		y = b_i;
    	} else 
    	{
      		b_i++;
      		goto label_1;
    	}
  	} 
  	else 
  	{
    	y = NumFunc[0] + 1U;
  	}
  	b_i = 0U;
  	for(c_i = 1U; c_i <= y; c_i++) 
  	{
    	b_i += NumFunc[c_i];
  	}
  	for(c_i = 0U; c_i <= NumFunc[(int16)(y + 1U)] - 1U; c_i++) 
  	{
   		funcipTP = (firstip + b_i) + c_i;
    	funcipTP->ignore = 1;
  	}
  	c_i = y >> 4U;
  	b_i = y & (uint16)0x0F;
  	if(b_i == 15U) 
  	{
    	KeyBoard_DealWork.KeyBoard.GroupIgnore[c_i] |= 32768U;
  	} 
  	else 
  	{
    	KeyBoard_DealWork.KeyBoard.GroupIgnore[c_i] |= (uint16)(1 << b_i);
  	}
}
*/
