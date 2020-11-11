

#ifndef _RTW_HEADER_TORQUEFUNC_h_
#define _RTW_HEADER_TORQUEFUNC_h_

#ifdef  _TORQUEFUNC_DEF_H_
#define  _TORQUEFUNC_DEF             
#else
#define  _TORQUEFUNC_DEF 	extern  		 
#endif

#define MAX_TORQ			16385
#define ONE_THIRD_MAX_TORQ	5461

_TORQUEFUNC_DEF  void FuncManage_enter_atomic_TORQUE(void );
_TORQUEFUNC_DEF  void FuncManage_TorqueRef(void) ;
_TORQUEFUNC_DEF  void FuncManage_L4ms_Torque(void);
_TORQUEFUNC_DEF  void FuncManage_exit_internal_TORQUE(void);
_TORQUEFUNC_DEF  void TorqueLimitSet(void);
_TORQUEFUNC_DEF	 void FuncManage_enter_Torque(void);
_TORQUEFUNC_DEF  void FuncManage_L4ms_Init_Torque(void);


_TORQUEFUNC_DEF	 int16   TorqSet; 					// 转矩指令（+/-300%，单位：0.1%）,滤波前
_TORQUEFUNC_DEF	 int16   TorqSetFilter; 					// 转矩指令（+/-300%，单位：0.1%）,滤波后



#endif  

