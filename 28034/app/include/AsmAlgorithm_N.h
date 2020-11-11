/***************************************************************************
  Name:        AsmAlgorithm.h
			   汇编算法头文件				
  Funktion:    Deklaration aller Assembler-Funktionen  
               声明所有的汇编功能块

****************************************************************************


****************************************************************************/

#ifndef _AsmAlgorithm_H
#define _AsmAlgorithm_H


#include "main.h"           // Datentypen


/*********************************************************************
 *  external variables                                               *
 *********************************************************************/


/*******************************************************************************
;  _divu16
;
;  Parameter:    Uint32 dividend, Uint16 divisor 
;                 in ACC            in AR4 
;  
;  Beschreibung: dividend / divivor, quotient auf 0xFFFF begrenzt
;                if divisor > dividend.high
;                { AL = dividend / divisor;}
;                 else
;                { AL = 0xFFFF;}                        
;  Returnwert:   Uint16 in ACC             0 bis 0x0000FFFF
;  
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;  
; *******************************************************************************/
Uint16 divu16 (Uint32 dividend32, Uint16 divisor16);  // 32位除16位数程序（不带余数）声明


/*******************************************************************************
;  _divu32
;
;  Parameter:    Uint32 dividend, Uint16 divisor 
;                in ACC            in AR4 
;  
;  Beschreibung: dividend / divivor, quotient gleich 0 - 0xFFFF FFFF
;                quotient.high = dividend.high / divisor;
;                quotient.low  = (dividend.high + reamainder.high) / divisor;
;
;                quotient.high is temporarily saved in dividend.high after the 
;                first division. 
;
;  Returnwert:   Uint16 in ACC             0 bis 0xFFFFFFFF
;  
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;
; *******************************************************************************/
unsigned long divu32 (Uint32 dividend32, Uint16 divisor16); // 32位除16位数程序（带余数）声明



/*******************************************************************************
;  _divu64d32
;
;  Parameter:     Uint32 factor1, Uint32 factor2, Uint32 divisor 
;                 in ACC            in stack          in stack
;  
;  Beschreibung: (factor1*factor2) / divivor, quotient auf 0xFFFF FFFF begrenzt
;                if divisor > (dividend>>31)
;                { ACC = dividend / divisor;}
;                else
;                { ACC = 0xFFFF FFFF;}                        
;  Returnwert:   Uint16 in ACC             0 bis 0xFFFF FFFF
;  
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|
;  | divisor.low           |              | divisor.low           |
;  |-----------------------|              |-----------------------|
;  | divisor.high          |              | divisor.high          |
;  |-----------------------|              |-----------------------|
;  | factor2.low           |              | factor2.low           |
;  |-----------------------|              |-----------------------|         
;  | factor2.high          |              | factor2.high          |
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;  
; *******************************************************************************/

Uint32 divu64d32 (Uint32 factor1, Uint32 factor2, Uint32 divisor); // 64位除32位函数声明

/*******************************************************************************
;  _mulu32by32
;
;  Parameter:    Uint32 factor1, Uint32 factor2 
;                in ACC            in stack 
;  
;  Beschreibung: ACC = (factor1*factor2)>>32 
;  Returnwert:   Uint32 in ACC             0 bis 0xFFFF FFFF
;  
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|
;  | factor2.low           |              | factor2.low           |
;  |-----------------------|              |-----------------------|         
;  | factor2.high          |              | factor2.high          |
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;  
; *******************************************************************************
*/
Uint32 mulu32by32 (Uint32 factor1, Uint32 factor2); // 无符号32位乘32位乘法函数声明


/*******************************************************************************
;  _mulu32x16
;
;  Parameter:    Uint32 factor1, Uint16 factor2 
;                 in ACC            in AR4 
;  
;  Beschreibung: factor1*factor2 auf 0x7FFF FFFF begrenzt
;                                       
;  Returnwert:   Uint32 in ACC             0 bis 0x7FFF FFFF
;  
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;  
; *******************************************************************************/ 
Uint32 mulu32x16 (Uint32 factor1, Uint16 factor2); // 无符号32位乘16位函数声明



/*******************************************************************************
;  _mulu32
;
;  Parameter:    Uint16 factor1, Uint16 factor2 
;                   in AL              in AH
;  
;  Beschreibung: product = factor1 * factor2, in A 0 - 0xFFFE 0001 
;				 			 		
;  Returnwert:   Uint32  product in A			0 bis 0xFFFE 0001
;	
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;
; *******************************************************************************/

Uint32 mulu32 (Uint16 factor1, Uint16 factor2); // 无符号16位乘16位，返回32函数声明


/*******************************************************************************
;  _mul32
;
;  Parameter:    int16 factor1, int16 factor2 
;                   in AL           in AH
;  
;  Beschreibung: product = factor1 * factor2, in A 0xC000 8000 - 0x4000 0000 
;				 			 		
;  Returnwert:   int32  product in A			0xC000 8000 - 0x4000 0000
;	
;          Stack befor call                        stack after call
;  |-----------------------|              |-----------------------|         
;  | Stack top             | <- SP        | RPC(15:0)             |    
;  |-----------------------|              |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | SP = RPC     | RPC(21_16)            |
;  |-----------------------| RPC = PC + 2 |-----------------------|
;  | xxxxxxxxxxxxxxxxxxxxx | PC = 22bit   |  Stack top            | <- SP
;  |-----------------------|              |-----------------------|
;
; *******************************************************************************/

int32 mul32 (int16 factor1, int16 factor2); // 有符号16位乘16位，返回32函数声明


#endif // _AsmAlgorithm_H

/*EOF*/
