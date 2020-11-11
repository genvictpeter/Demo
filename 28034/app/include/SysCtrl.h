#ifndef SYSCTRL_H
#define SYSCTRL_H

#include "main.h"

/*******************************************************************************************/
#ifdef  _SYSCTRL_DEF_H_
#define  _SYSCTRL_DEF_H_             
#else
#define  _SYSCTRL_DEF_H_ 	extern  		 
#endif



_SYSCTRL_DEF_H_ void InitSysCtrl(void);
_SYSCTRL_DEF_H_ void InitGpio(void);
_SYSCTRL_DEF_H_ void InitEPwm(void);
_SYSCTRL_DEF_H_ void InitPieCtrl(void);
_SYSCTRL_DEF_H_ void DisableDog(void);
_SYSCTRL_DEF_H_ void EnableDog(void);

_SYSCTRL_DEF_H_ void KickDog(void);
_SYSCTRL_DEF_H_ void InitFlash(void);
_SYSCTRL_DEF_H_ void InitAdc(void);
_SYSCTRL_DEF_H_ void InitSci(void);
//_SYSCTRL_DEF_H_ void InitSpi(void);
//_SYSCTRL_DEF_H_ void InitCap();
#endif

