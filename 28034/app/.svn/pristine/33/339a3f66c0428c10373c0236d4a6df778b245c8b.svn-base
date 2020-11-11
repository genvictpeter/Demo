/**
*
* \file
*
* \brief Preprocessor definitions derived from the UDS network transport layer configuration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the UDS software package.
*
* \version $Id: Version 1.0 Revision 0 2012-06-18 Tan Yang $
*
*============================================================================*
*                               REVERSION HISTORY                            *
*============================================================================*
*  REVISION     |   DATE        |                         |      AUTHOR      *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev4  | Dec/12/2012   |                         | Yang TAN         *
* Delivery_001                                                               *
*----------------------------------------------------------------------------*
* UDS_1.0 Rev5  | Jan/18/2013   |                         | Yongqiang Deng   *
* Delivery_002                                                               *
*         update the code after 1st round integration with customer running  *
*         sw project, change detail please refer to                          *
*         UDSonCAN Protocol Stack Release Note_v1_0r5.doc                    *
*                                                                            *
*----------------------------------------------------------------------------*
* UDS_1.1 Rev0 | May/15/2013    |                         | Yang TAN         *
* Delivery_004                                                               *
*         Add one definition UDSTP_TIMING_TICK_PERIOD which is used as       *
*         granularity of ticking network transport layer timers in user      *
*         application.                                                       *
*         Resolution of timer values is changed from millisecond to          *
*         microsecond.                                                       *
*                                                                            *
*----------------------------------------------------------------------------*
******************************************************************************/

#ifndef _UDSTP_CONFDEFS_H
#define _UDSTP_CONFDEFS_H

/*lint -e750*/

/******************************************************************************
*
* Sessions General preprocessor definitions
*
******************************************************************************/

/* Define tick period for network transport layer timing.
 *
 * Unit: us
 * This value shall be configured to period of function that is used to tick the timing.
 */
#define UDSTP_TIMING_TICK_PERIOD			    500u /* TODO */

/* Enable change of BS and STmin parameters by upper layer service requests
 *
 * The changes of N_STmin and N_BS will go into session structures, not cfg structures.
 */
#define UDSTP_ENABLE_CHANGEPARAMETER

/******************************************************************************
*
* Sessions NSdu preprocessor definitions
*
******************************************************************************/

/* Define NSdu Max Length of data to be received/transmited
 *
 * uint16_t type
 * maxium available length is 12bit(1~4095) as defined in ISO15765-2.
 */
#define ISO15765_NSDU_MSGDATA_LENGTH		  64u/* TODO */

/* Define NSdu Mtype
 *
	DIAGNOSTIC			= 0, 
	REMOTEDIAGNOSTIC	= 1
 */
#define UDSTP0_NMTYPE_DIAGNOSTIC			    0x00u
#define UDSTP0_NMTYPE_REMOTEDIAGNOSTIC			0x01u
#define UDSTP0_NPDU_MTYPE					    (UDSTP0_NMTYPE_DIAGNOSTIC) /* TODO */

/* Define NPdu Address Information
 *
	UDSTP0_NPDU_SERVER_ADDR, 		uint8_t type server address
	UDSTP0_NPDU_CLIENT_ADDR, 		uint8_t type client address
	UDSTP0_NPDU_SERVER_ADDREXTEN, 	uint8_t type server address extention
	UDSTP0_NPDU_CLIENT_ADDREXTEN	uint8_t type client address extention
	NTaType:
			CANTP_FUNCTIONAL 	= 0,
			CANTP_PHYSICAL		= 1
 */
#define UDSTP0_NPDU_SERVER_ADDR			  	    (uint8_t)(11u)/* TODO */
#define UDSTP0_NPDU_CLIENT_ADDR				    (uint8_t)(22u)/* TODO */
#define UDSTP0_NPDU_SERVER_ADDREXTEN		    (uint8_t)(33u)/* TODO */
#define UDSTP0_NPDU_CLIENT_ADDREXTEN	  	    (uint8_t)(44u)/* TODO */

/******************************************************************************
*
* Sessions NPdu preprocessor definitions
*
******************************************************************************/

/* Define NPdu STmin for segment data receiver (FC sender)
 *
 * 0x00 - 0x7F: 0ms - 127ms (in resolution of 1ms)
 * 0x80 - 0xF0: reserved
 * 0xF1 - 0xF9: 100us - 900us (in resolution of 100us)
 * 0xFA - 0xFF: reserved
 *
 * Note:
 * 0xF1 - 0xF9 will further defined in ISO15765-3 as vehicle manufacturer defined/requested
 * value range.
 * So in uds application the STmin value range from 0xF1 to 0xF9 will be checked against
 * configured values to judge whether these are as vehicle manufacturer required.
 */
#define UDSTP0_NPDU_STMIN				        	20u/* TODO */

/* Define NPdu block size for segment data receiver (FC sender)
 *
 * 0x00(not configurable):
 *				means no more FC will be sent by segment receiver, the sender shall send all datas
 *				without waiting for further FC.
 *				This value implement mostly as runtime time in case the segment data can be received by receiver
 *			 	at one time without any FC needed.
 * 0x01 - 0xFF: max number of consecutive frames in one block.
 *
 * [Note]: 
 * 0x00 is only used dymamicly for segmented data receiver(CF receiver) to indicate to sender that no
 * more FC frames will be send by receiver during the reception of the segmented data, and it shall send
 * all CF frames with considering value of STmin.
 */
#define UDSTP0_NPDU_BLOCKSIZE				    8u/* TODO */

/* Define NPdu Maximum number of transmissions of FC.Wait frame
 *
 * Value is user defined
 * 0: The segment data receiver (FC sender) shall not send out any FC.Wait frame.
 */
#define UDSTP0_NPDU_WFTMAX				    	3u/* TODO */

/* Define Network layer timing parameters
 *
 * ISO15765-2 specified timeout value shall be treated as the lower limit for real application defined values.
 * Real timeout value shall at most 150% of the value defined in the specification, as below:
 *			lower limit		performance req(further defined in upper layer, e.g. ISO15765-3(UDSonCAN).)
	Nas: 	1000ms
	Nbs: 	1000ms
	Ncs: 	N/A 			[(Ncs + Nas) < (0.9 * Ncr)]
	Nar: 	1000ms
	Nbr: 	N/A				[(Nbr + Nar) < (0.9 * Nbs)]
	Ncr: 	1000ms
 *
 * Unit: ms (Configured value)
 * Unit: us (Real value used by application)
 *
 * Formula: UDSTPx_NPDU_Nxx (us) = UDSTPx_NPDU_Nxx_VAL(ms) * 1000u
 * Definitions for UDSTP0_NPDU_Nxx values shall be carried out by define UDSTP0_NPDU_Nxx_VAL(ms) and we then
 * convert them to values in unit of microsecond by multiple 1000.
 */
#define UDSTP0_NPDU_NAR_VAL		        ((uint32_t)(70u))  /* TODO */
#define UDSTP0_NPDU_NBR_VAL		        ((uint32_t)(40u))  /* TODO */
#define UDSTP0_NPDU_NCR_VAL		        ((uint32_t)(150))  /* TODO */
#define UDSTP0_NPDU_NAS_VAL	        	((uint32_t)(70u))  /* TODO */
#define UDSTP0_NPDU_NBS_VAL	        	((uint32_t)(150u)) /* TODO */
#define UDSTP0_NPDU_NCS_VAL		        ((uint32_t)(40u))  /* TODO */
#define UDSTP0_NPDU_NAR			        ((uint32_t)(UDSTP0_NPDU_NAR_VAL * 1000u))
#define UDSTP0_NPDU_NBR		          	((uint32_t)(UDSTP0_NPDU_NBR_VAL * 1000u))
#define UDSTP0_NPDU_NCR			        ((uint32_t)(UDSTP0_NPDU_NCR_VAL * 1000u))
#define UDSTP0_NPDU_NAS			        ((uint32_t)(UDSTP0_NPDU_NAS_VAL * 1000u))
#define UDSTP0_NPDU_NBS			        ((uint32_t)(UDSTP0_NPDU_NBS_VAL * 1000u))
#define UDSTP0_NPDU_NCS		          	((uint32_t)(UDSTP0_NPDU_NCS_VAL * 1000u))

/******************************************************************************
*
* ISO15765-2 data link layer interface required definitions
*
******************************************************************************/

/* Define addressing format
 *
 * ISO15765-2 data link layer interface required addressing format for send/receive N_PDUs which will
 * be used for encapsulating CAN ID values. 
 *	enum
	NORMAL 			= 0,
	NORMAL_FIXED	= 1,
	EXTENDED		= 2,
	MIXED11BIT		= 3,
	MIXED29BIT		= 4
 */
#define UDSTP0_CAN_ADDRESSINGFORMAT		NORMAL/* TODO */

/* Define padding enable config
 *
 * (Optional) configuration for padding CAN frames concerning the length of the data field in a CAN frame
 * less than 8 bytes. 
 *  enum
 	PADDING_ON 		= 0,
	PADDING_OFF		= 1
 */
#define UDSTP0_CAN_PADDINGCFG		    	PADDING_ON/* TODO */
#define UDSTP0_CAN_PADDINGVALUE	    	    0x00u /* TODO */


/******************************************************************************
*
* Sessions preprocessor definitions
*
******************************************************************************/

/* Define session numbers
 *
 * This defines number of element of UdsTp_SessionCfgs
 * For each session there will be one UdsTp_SessionCfg_t and one UdsTp_Session_t type defined.
 */
#define UDSTP_NUM_SESSIONS	        		0x01u


#endif /* _UDSTP_CONFDEFS_H */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
