#ifndef _RTW_HEADER_IOFUNC_h_
#define _RTW_HEADER_IOFUNC_h_

#ifdef  _IOFUNC_DEF_H_
#define  _IOFUNC_DEF             
#else
#define  _IOFUNC_DEF 	extern  		 
#endif

//#define ENABLE_IO_FUNC	1

#define CLOSE_SWITCH	    GpioDataRegs.GPADAT.bit.GPIO7 = 1
#define OPEN_SWITCH		    GpioDataRegs.GPADAT.bit.GPIO7 = 0

#define RS485_RSV			GpioDataRegs.GPADAT.bit.GPIO6 = 0
#define RS485_TMS			GpioDataRegs.GPADAT.bit.GPIO6 = 1

#define POWER_ON()			GpioDataRegs.GPASET.bit.GPIO11 = 1
#define POWER_OFF()			GpioDataRegs.GPACLEAR.bit.GPIO11 = 1

/**********************************************************************
 zb-20161130
 电机温度检测选择  
                  PT100_SEL             NTC_SEL
 PT1000/KTY           0                    0
 PT100                1                    0
 NTY                  0                    1
************************************************************************/
#define PT100_SEL()			GpioDataRegs.GPBSET.bit.GPIO40 = 1
#define NTC_SEL()			GpioDataRegs.GPBSET.bit.GPIO42 = 1
#define PT100_NSEL()		GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1
#define NTC_NSEL()			GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1

#define LED					GpioDataRegs.GPBDAT.bit.GPIO34

#define HardOC				GpioDataRegs.GPADAT.bit.GPIO23
#define DRV_U               GpioDataRegs.GPADAT.bit.GPIO15
#define DRV_V               GpioDataRegs.GPADAT.bit.GPIO13
#define DRV_W               GpioDataRegs.GPADAT.bit.GPIO14

/* DI??×ó */
typedef struct 
{
	unsigned int   X1:1; 		// 0	
	unsigned int   X2:1;   		// 1	
	unsigned int   X3:1;   		// 2				
	unsigned int   X4:1; 		// 3	
	unsigned int   X5:1; 		// 4	
	unsigned int   X6:1;        // 5	
	unsigned int   X7:1;    	// 6	
	unsigned int   X8:1;		// 7	
	unsigned int   X9:1;		// 8	
	unsigned int   X10:1;     	// 9
	unsigned int   X11:1;     	// 10
	unsigned int   X12:1;     	// 11
	unsigned int   rsvd:4;     	// 12~15 reserved
}S_DIValue;
/* DI??×ó?μ1￡-￡-all & bit access */
typedef union  
{
	unsigned short     all;
	S_DIValue bit;
}U_DIValue;




// terminal function 
typedef struct 
{		
	unsigned int   MulStepSpdTerm1:1; 	// 0	?à???ù??×ó1
	unsigned int   MulStepSpdTerm2:1; 	// 1	?à???ù??×ó2
	unsigned int   MulStepSpdTerm3:1; 	// 2	?à???ù??×ó3
	unsigned int   MulStepSpdTerm4:1; 	// 3	?à???ù??×ó4
	unsigned int   AccDecTimeTerm1:1; 	// 4	?ó???ùê±????×ó1
	unsigned int   AccDecTimeTerm2:1; 	// 5	?ó???ùê±????×ó2		     	
	unsigned int   TermUPFreqInput:1;    	// 6	?μ?êμY????×óê?è?     	
	unsigned int   TermDNFreqInput:1;    	// 7	?μ?êμY????×óê?è?     	
	unsigned int   MainFreqScourceTerm1:1;	// 8	?÷???¨?μ?ê?′????1
	unsigned int   MainFreqScourceTerm2:1;  // 9	?÷???¨?μ?ê?′????2
	unsigned int   MainFreqScourceTerm3:1;  // 10	?÷???¨?μ?ê?′????3     	
	unsigned int   TermMainFreqToAI:1;    	// 11	?÷???¨?μ?ê?D???áAI 	
	unsigned int   CmdScourceTerm1:1;    	// 12	?üá??′????1     	
	unsigned int   CmdScourceTerm2:1;    	// 13	?üá??′????2
	unsigned int   ForbitFwdTerm:1; 	// 14	zheng×a???1
	unsigned int   ForbitRevTerm:1;		// 15	·′×a???1				
}S_DITermFunc1;
typedef union 
{
	unsigned short      all;
	S_DITermFunc1  bit;
}U_DITermFunc1;

/* é?′???DD×′ì?1￡-￡-bit fields  */
// ?aá??ì2a2?·?×′ì?μ????òé?ò?′??μ￡???é?ò?′?μ?×′ì???ò???à′
// 060506 ?Yê±??óDó?μ?



typedef struct
{
	uint16   AccTorqRef:1; 		
	uint16   BrakeTorqRef:1;    	        	        
	uint16   rsvd:14; 			      
	                                                                                
}S_AIFuncFlag;                                                                   
                                                                                       
typedef union                                                                          
{
	uint16   all;
	S_AIFuncFlag bit;
}U_AIFuncFlag;

typedef struct 
{		
	 int16 AccTorqRef; 	
	 int16 BrakeTorqRef;   
}S_AIFuncSetValue;

/* DO??×ó */
typedef struct 
{		
	unsigned int   Y1:1; 		// 	Y1
	unsigned int   Y2:1; 		// 	Y2
	unsigned int   Y3:1; 		// 	Y3
	unsigned int   Y4:1; 		// 	
	unsigned int   Y5:1; 		// 	
	unsigned int   Y6:1; 		// 	
	unsigned int   Y7:1; 		// 	
	unsigned int   Y8:1; 		// 	
	unsigned int   Y9:1; 		// 	
	unsigned int   Y10:1; 		// 
	unsigned int   Y11:1; 		// 
	unsigned int   Y12:1; 		// 	
	unsigned int   rsvd:4; 		// 				
}S_DoTermValue;
typedef union 
{
	unsigned short      all;
	S_DoTermValue  bit;
}U_DoTermValue;

_IOFUNC_DEF  void FuncManage_L1ms_Init_IO(void);
_IOFUNC_DEF  void FuncManage_L1ms_IO(void);
#endif  

