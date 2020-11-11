/**
*
* \file
*
* \brief Flash Boot Loader Transport Layer (TP) design .
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the Flash Boot Loader software package.
*
* \version $Id: Version 1.0 Revision 0 2012-08-12 Deng Yongqiang $
*
*================================================================================*
*                               REVERSION HISTORY                                *
*================================================================================*
*  REVISION         |   DATE        |                         |      AUTHOR      *
*--------------------------------------------------------------------------------*
*  RTA_CAN_1.0      | Aug/12/2012   |                         | Yongqiang Deng   *
* Creation of this file                                                          *
*--------------------------------------------------------------------------------*
*  RTA_BSW_2.0      | Jan/12/2014   |                         | Yongqiang Deng   *
* Update this file for eAAM FBL project                                          *
*--------------------------------------------------------------------------------*
**********************************************************************************/

#ifndef _FBLTP_H
#define _FBLTP_H

#ifdef __cplusplus
extern "C" {
#endif


#include "MAIN.h"


#ifndef TC17XX_FBL_USING_POLLING_TO_DRIVE
#define  TC17XX_FBL_USING_POLLING_TO_DRIVE
#endif


/* Config */
#define FBLTP_C_DIAG_CHANNEL      (uint32_t)0x01u

 /* Bit masks for the CAN status */
 #define FBLTP_C_CAN_STATUS_IDLE              0x00u
 #define FBLTP_C_CAN_STATUS_BUSOFF            0x01u
 #define FBLTP_C_CAN_STATUS_OVERFLOW          0x02u
 #define FBLTP_C_CAN_STATUS_DATA_RECEIVED     0x04u
 #define FBLTP_C_CAN_STATUS_TX_PENDING        0x08u


#define FBLTP_C_INIT_FRAME_BEFORE_TX      TRUE 


#define FBLTP_C_BS_RX                        0x08u // 0x08u  /* max block size is 8 frames between FC frames */
#define FBLTP_C_ST_MIN_RX_US          (0x14u) // (0x00u) // (0x01u)  /* ST min can be no seperation time between CF frames */
#define FBLTP_C_BUFFER_SIZE           180u    /* original 360u , the TP buffer size , currently is 360 bytes */



#ifdef TC17XX_FBL_USING_POLLING_TO_DRIVE
#define FBLTP_C_TASK_CYCLE              1000u   /* TP timer tick task is put in the 1us  task */
#define FBLTP_C_TASK_CYCLE_ZOOM         (0x01u)
#endif

/*Timeouts*/
#define FBLTP_C_TP_TMR_FC_CF_US   (((uint32_t)FBLTP_C_ST_MIN_RX_US*FBLTP_C_TASK_CYCLE_ZOOM)/ FBLTP_C_TASK_CYCLE)      
#define FBLTP_C_TP_TMR_N_AS_US    (((uint32_t)70u*1000u*FBLTP_C_TASK_CYCLE_ZOOM) /FBLTP_C_TASK_CYCLE)              /* ISO 15675-2 value: 1000 ms =  due to granuity is : 1ms, so : value is 1000 */
#define FBLTP_C_TP_TMR_N_AR_US    (((uint32_t)70u*1000u*FBLTP_C_TASK_CYCLE_ZOOM)/FBLTP_C_TASK_CYCLE)               /* ISO 15675-2 value: 1000 ms*/
#define FBLTP_C_TP_TMR_N_BS_US    (((uint32_t)150u*1000u*FBLTP_C_TASK_CYCLE_ZOOM)/FBLTP_C_TASK_CYCLE)                /* ISO 15675-2 value: 1000 ms*/
#define FBLTP_C_TP_TMR_N_CR_US    (((uint32_t)150u*1000u*FBLTP_C_TASK_CYCLE_ZOOM)/FBLTP_C_TASK_CYCLE)               /* ISO 15675-2 value: 1000 ms*/

#define	FBLTP_C_USE_DEFAULT_4_RESVD_ST		TRUE

#define	FBLTP_C_DEFAULT_STMIN	   (127u)

/*Value to be copied to non-used bytes in TP frame*/
#define FBLTP_C_INIT_FRAME_VALUE        (0x00AAu)




/* Private function macros, constants, types and datas */
/* ---------------------------------------------------- */

/* CAN TP Message related Data */

typedef struct
{
    uint8_t  TPState;                /* Current TP state for this message */
    uint8_t  BS_Tx;                  /* Block Size when TP is in Transmission (receiving FC) */
    uint8_t  BS_Rx;                  /* Block Size when TP is in Reception (transmiting FC) */
    uint8_t  SN_Rx;                  /* Sequence Number when TP is in Reception */

    uint8_t  SN_Tx;                  /* Sequence Number when TP is in Transmission */
    uint8_t  STmin_Rx;               /* Minimum separation time, when TP is in Reception (transmiting FC) */
    uint8_t  rub_TxMsgInProgress;
    uint8_t  rub_TPTimerActive;
	
    uint8_t  rub_TO_flag; 
    uint8_t  rub_TPMessageSent;
    uint8_t  rub_CurrRxReqChannel; 
	
    uint16_t ruw_MsgSize;
    uint16_t CompleteLength_Rx;      /* Total nr. of bytes to be received on current reception */

    uint16_t RemainingBlockCFs_Rx;   /* How many CF blocks are still expected to be received */
    uint16_t RemainingLength_Rx;     /* How many bytes are still expected to be received */

    uint16_t RemainingCFs_Rx;        /* How many CFs still have to be received */
    uint16_t RemainingCFs_Tx;        /* How many CFs still have to be transmitted */

    uint16_t RemainingLength_Tx;     /* How many bytes still have to be transmitted */
    uint16_t RemainingBlockCFs_Tx;   /* How many CF blocks still have to be transmitted */

    uint16_t BufferIndex;            /* Index in the data buffer */

    uint32_t STmin_Tx;               /* Minimum separation time, when TP is in Transmission (receiving FC) */
    uint32_t rul_TP_Timer_ExpirationData ;
	
    uint8_t laub_CanBuffer[0x08u];
    uint8_t lub_CanBufIndex; 
    uint8_t lub_CanMsgCount;
  	
}T_FBLTP_MSG_MNGT;


/* Maximum data length of a CAN frame */
#define FBLTP_C_TP_FLOW_ST_CONTINUE_2_SEND         0x00u    /* Flow Status Continue To Send */
#define FBLTP_C_TP_FLOW_ST_WAIT                    0x01u    /* Flow Status Wait */
#define FBLTP_C_TP_FLOW_ST_OVFLW                   0x02u    /* Flow Status Overflow */


#define FBLTP_C_SF_LEN                             0x07u   /* Number of data bytes in a Single Frame */
#define FBLTP_C_FF_LEN                             0x06u   /* Number of data bytes in a First Frame */
#define FBLTP_C_CF_LEN                             0x07u   /* Number of data bytes in a Consecutive Frame */

#define FBLTP_C_N_PCI_POSITION                          0x00u   /* Start Position of the PCI bytes */
#define FBLTP_C_LEN_OF_FF_POSITION                 0x01u   /* Low byte for FF_DL */
#define FBLTP_C_FC_BS_POSITION                         0x01u   /* Block size position */
#define FBLTP_C_FC_ST_MIN_POSITION                 0x02u   /* Separation time position */
#define FBLTP_C_MIN_FC_LEN                                 0x03u

#define FBLTP_C_MASK_N_PCI_TYPE                      0xF0u   /* Mask for reading Frame Type*/
#define FBLTP_C_MASK_SF_DAT_LEN                     0x0Fu   /* Mask for reading Single Frame Data Length */
#define FBLTP_C_MASK_FF_DAT_LEN                     0x0Fu   /* Mask for reading the First Frame Data Length */
#define FBLTP_C_MASK_CF_SEQ_NUM                    0x0Fu   /* Mask for reading Sequence Number of a Consecutive Frame */
#define FBLTP_C_MASK_FC_FLOW_ST                    0x0Fu   /* Mask for reading Flow Status of a Flow Control Frame */

#define FBLTP_C_N_PCI_TYP_SF                       0x00u    /* Frame type = Single Frame */
#define FBLTP_C_N_PCI_TYP_FF                       0x10u    /* Frame type = First Frame */
#define FBLTP_C_N_PCI_TYP_CF                       0x20u    /* Frame type = Consecutive Frame */
#define FBLTP_C_N_PCI_TYP_FC                       0x30u    /* Frame type = Flow Control Frame */

#define	FBLTP_C_CAN_FRAME_MAX_LEN	               0x08u
#define FBLTP_C_CAN_MAX_DLC                        0x08u    /* Maximum size for the DLC of a CAN Frame */
#define FBLTP_C_MAX_FC_LEN                         0x08u    /* Length of a Flow Control Frame */
#define FBLTP_C_MAX_CF_SN                          0x0Fu    /* Max value of the Sequnce Number */
#define FBLTP_C_MAX_FC_BS                          0x0Fu    /* Max value of the Block Size */

#define FBLTP_C_TMR_TIMOUT_FC_CF                   FBLTP_C_TP_TMR_FC_CF_US 
#define FBLTP_C_TMR_TIMOUT_N_AS                    FBLTP_C_TP_TMR_N_AS_US  
#define FBLTP_C_TMR_TIMOUT_N_AR                    FBLTP_C_TP_TMR_N_AR_US  
#define FBLTP_C_TMR_TIMOUT_N_BS                    FBLTP_C_TP_TMR_N_BS_US  
#define FBLTP_C_TMR_TIMOUT_N_CR                    FBLTP_C_TP_TMR_N_CR_US  

/* Trasnport Protocol States */
#define FBLTP_C_TPST_IDLE                          0x00u
#define FBLTP_C_TPST_WAIT_SF_TX_CNFM               0x01u    /* N_As timeout */
#define FBLTP_C_TPST_WAIT_FF_TX_CNFM               0x02u    /* N_As timeout */
#define FBLTP_C_TPST_WAIT_CF_TX_CNFM               0x03u    /* N_As timeout */
#define FBLTP_C_TPST_WAIT_CFBLK_TX_CNFM            0x04u    /* N_As timeout */
#define FBLTP_C_TPST_WAIT_LST_CF_TX_CNFM           0x05u    /* N_As timeout */
#define FBLTP_C_TPST_WAIT_FC_TX_CNFM               0x06u    /* N_Ar timeout */
#define FBLTP_C_TPST_WAIT_CF_TX                    0x08u    /* N_Cs timeout */
#define FBLTP_C_TPST_WAIT_CF_RX                    0x20u
#define FBLTP_C_TPST_WAIT_FC_RX                    0x40u    /* N_Bs timeout */
#define FBLTP_C_TPST_WAIT_1ST_FC_RX                0x60u    /* N_Bs timeout */
#define FBLTP_C_TPST_WAIT_CNFM                     0x07u    /* Mask used to test confirmation states */
#define FBLTP_C_TPST_WAIT_TX                       0x18u    /* Mask used to test transisions states */

 /* Values used for the indication and confirmation functions for the upper layer */
#define FBLTP_C_TP_RSLT_N_OK                       0x00u    /* Confirmation/Indication OK */
#define FBLTP_C_TP_RSLT_N_TIMEOUT_A                0x01u    /* Confirmation/Indication Timeout A */
#define FBLTP_C_TP_RSLT_N_TIMEOUT_BS               0x02u    /* Confirmation Timeout Bs */
#define FBLTP_C_TP_RSLT_N_OVFLW                    0x06u    /* Indication Overflow */
#define FBLTP_C_TP_RSLT_N_INVALID_FS               0x07u    /* Indication invalid Flow Status */
#define FBLTP_C_TP_RSLT_N_ERROR                    0xFFu    /* General error (not covered by the previous definitions) */

/* FBL error codes */
typedef enum
{
     FBLTP_C_E_OK             = 0x00u,	// 0
     FBLTP_C_E_HW_FAIL,				    // 1
     FBLTP_C_E_SW_FAIL,				    // 2
     FBLTP_C_E_ALIGN_ERR,	            // 3
     FBLTP_C_E_FORBIDDEN,		        // 4
     FBLTP_C_E_OUT_OF_RANGE,		    // 5
     FBLTP_C_E_INVLID_PARAM,		    // 6
     FBLTP_C_E_BAD_CRC,				    // 7
     FBLTP_C_E_INCOMPATIBLE,		    // 8
     FBLTP_C_E_EEPROM_ERR,			    // 9
     FBLTP_C_E_MEM_NOT_ENOUGH,		    // 10
     FBLTP_C_E_BUSY					    // 11
} T_FBL_C_TP_ERR_CODE;

#define FBLTP_SET_START_TIMEOUT_US(WhichTimer, TimeoutValue)  {  \
                                                                FBLTP_DISABLE_ALL_INTERRUPTS(); \
                                                                    WhichTimer = TimeoutValue; \
                                                                FBLTP_ENABLE_ALL_INTERRUPTS();}

#define FBLTP_GET_HAS_TIMEOUT_EXPIRED(WhichTimer)   (WhichTimer == 0x00000000u)


extern uint8_t  raub_TP_buffer[FBLTP_C_BUFFER_SIZE];  


#ifdef __cplusplus
extern "C" {
#endif


#endif /* end of  #ifndef _FBLTP_H */
