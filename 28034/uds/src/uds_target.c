/****************************************************************************
 	@Module       
 	@Filename      uds_target.c
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

#include "uds_target.h"

#define GET_HI_BYTE                        1
#define GET_LOW_BYTE                       0

/******************************************************************
 * This function copies bytes from one location to another.
 *
 * \param [in] pDest        The destination location.
 * \param [in] pSrc         The source location.
 * \param [in] numBytes     The number of bytes to be copied.
 *
 *****************************************************************/
void UDS_FN_TYPE Uds_MemCopy(
    uint8_t*          pDest,
    const uint8_t*    pSrc,				/*lint !e963*/
    uint32_t          numBytes
)
{
	while (numBytes--)
	{
		*pDest++ = *pSrc++; 		
	}
  	return;
}



/******************************************************************
 * This function clear all of the bytes indicated by the pDest.
 *
 * \param [in] pDest        The destination buffer location.
 * \param [in] numBytes     The number of bytes to be copied.
 *
 *****************************************************************/
void UDS_FN_TYPE Uds_MemClear(
    uint8_t*          pDest,
    uint32_t          numBytes
)
{
 	while (numBytes > 0x00000000u)
 	{
		*pDest = 0x00u;
		pDest++; 
		numBytes--;    	 		
 	}
	return;
}

void UDS_FN_TYPE Uds_MemCopyDataFlow(uint8_t * pDest,
                                const uint8_t * pSrc,
                                uint32_t numBytes)
{
	Uint16 HiOrlowByte;
	
	//
	if ((numBytes & (Uint16)1) == 1) {
		HiOrlowByte = GET_LOW_BYTE;
	}
	else {
		HiOrlowByte = GET_HI_BYTE;
	}
	for ( ; numBytes > 0; numBytes--) {
		if (HiOrlowByte == GET_HI_BYTE) {
			* pDest++ = (* pSrc >> 8) & (Uint16)0xFF;
			HiOrlowByte = GET_LOW_BYTE;
		}
		else if (HiOrlowByte == GET_LOW_BYTE) {
			* pDest++ = (* pSrc++) & (Uint16)0xFF;
			HiOrlowByte = GET_HI_BYTE;
		}
	}
}

/******************************************************************************
*                               end of file                                   *
******************************************************************************/

