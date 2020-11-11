/**
*
* \file
*
* \brief Definitions the basic type definition to the TCxxx target
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 1 2013-11-11 Yongqiang Deng $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
*----------------------------------------------------------------------------*
* UDS_1.0 Rev1 | Nov/11/2013    |                         | Yongqiang Deng   *
* Delivery_001                                                               *
*    to define the unified basic type : uint8_t , uint16_t,                  *
*    uint32_t, uint64_t                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_




#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
	   
	typedef	  signed char		int8;
	       	             		
	typedef	unsigned char		Uint8;
	typedef	unsigned char		uint8_t;
         	
	typedef	unsigned  int		boolean_T;
	typedef	unsigned  int		_Bool;

	typedef           int		int16;         	
	typedef	unsigned  int		uint;	
	typedef	unsigned  int		Uint16;
	typedef	unsigned  int		uint16;
	typedef	unsigned  int		uint16_t;	
         	
	typedef	         long		int32;
	typedef	unsigned long		uint32;
	typedef	unsigned long		uint32_t;
	typedef	unsigned long		Uint32;   
	       	
	       	
	typedef	float           float32;
	typedef	long double     float64;
         	
         	
	       	
	typedef	long long       int64;
	       	   
	typedef	unsigned long long	Uint64;
	typedef	unsigned long long 	uint64_t;
	           
	           
	//****************************************************************************
	           
	typedef unsigned char		ubyte;	// 1 byte unsigned; prefix: ub 
	typedef   signed char		sbyte;	// 1 byte signed;	prefix: sb 
	typedef unsigned  int		ushort;	// 2 byte unsigned; prefix: us 
	typedef   signed  int		sshort;	// 2 byte signed;	prefix: ss 
	typedef unsigned long		uword;	// 4 byte unsigned; prefix: uw 
	typedef   signed long		sword;	// 4 byte signed;	prefix: sw 
	
	typedef unsigned char				BYTE;
	typedef unsigned  int				UINT;
	typedef unsigned long				WORD;
	typedef unsigned long long  DWORD;
	typedef unsigned long long 	QWORD;	//Flash 操作使用，我们不支持
	   
#endif





		#ifndef TRUE
			#define TRUE (1)
		#endif
		#ifndef FALSE
			#define FALSE (0)
		#endif
			   
		#ifndef	NULL
			#define NULL                            (0L)
		#endif


		
		//#define PWM_PERIOD_8KHZ		3750L									  // (60M/8K/2)=3750
#define PWM_PERIOD_4KHZ		7500L					                  // beiqi4k, (60M/4K/2)=7500
		
#define PWM__8KHZ		3750L	


#endif /* end of #ifndef _TYPEDEFS_H_ */

