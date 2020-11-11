/****************************************************************************
 	@Module       
 	@Filename      Task.c
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


#include "Task.h"       // Task module header
#include "CAN.h"
//#include "IO.h"
#include "FblTpExtItf.h"
#include "FblUdsExtItf.h"
//#include "watchDog.h"
#include "FblMgr.h"




#ifdef __cplusplus
extern "C" {
#endif



void Os_Sys_Timer_1000us_task_MainEntryPoint(void)
{
   /* to call the tick function interface , unit : 1000us 
    */  

   
	FBLTP_ITF_EXP_TICK_TP_TIMER();			//本来200us

											//本来400us		
	FBLTP_ITF_EXP_TP_CYCLIC_TASK();
	FBLUDS_ITF_EXP_UDS_CYCLIC_TASK();

}


#ifdef __cplusplus
}
#endif



