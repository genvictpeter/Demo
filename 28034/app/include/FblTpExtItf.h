/**
*
* \file
*
* \brief Flash Boot Loader Transport Layer (TP) design .
*
*        This file will define all of the imported and exported interfaces 
*        which will be used in the FBL Tp layer
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



#ifndef _FBLTPEXTITF_H
#define _FBLTPEXTITF_H

#ifdef __cplusplus
extern "C" {
#endif



#include "MAIN.h"



/* Imported interfaces . */
#define FBLTP_DISABLE_ALL_INTERRUPTS()    SuspendAllInterrupts()
#define FBLTP_ENABLE_ALL_INTERRUPTS()     ResumeAllInterrupts()

#define FBLTP_ITF_IMP_MEM_COPY                 Uds_MemCopy  // defined in the uds_target.h
#define FBLTP_ITF_IMP_READ_RX_CAN_MSG_FRM_DRV   CanDrv_ReadRxCanMsg 
#define FBLTP_ITF_IMP_TX_MSG_REQ                               CanDrv_TransmitMessageRequest
#define FBLTP_ITF_IMP_GET_TX_MSG_FINISH_FLG         CanDrv_GetTxMsgFinishedFlag

/* Exported functions prototypes and macros */
/* ---------------------------------------- */
extern void FblTp_N_USData_request(uint8_t * lpub_Data, 
                                   uint16_t luw_Size);
extern void FblTp_N_USData_indication (uint16_t luw_Length);
extern void FblTp_N_USData_confirm(uint8_t lub_status);


extern void FblTp_L_Data_request(uint8_t ub_Size, 
                                 uint8_t *pub_Data );


extern void FblTp_L_Data_indication (uint8_t rub_size, 
	                              uint8_t    i_lubCanBufIndex,  
                                     uint8_t * const pub_data);

extern void FblTp_L_Data_confirm (void ); 

extern void  FblTp_TickTpTimer(void);
extern uint32_t  FblTp_GetTpTimer(void);
extern void      FblTp_Init(void);
extern void      FblTp_CyclicTaskEntryPoint(void);
extern uint8_t*  FblTp_GetReceivedCanMsg(uint16_t * lpuw_Size);
extern uint8_t   FblTp_IsTxMessageSent(void );
extern uint8_t  FblTp_Get_CurrRxReqChannel(void);

extern void FblTp_NotifyCBForEndOfTxRsp(void);




#define FBLTP_ITF_EXP_TICK_TP_TIMER                     FblTp_TickTpTimer
#define FBLTP_ITF_EXP_TP_CYCLIC_TASK                   FblTp_CyclicTaskEntryPoint
#define FBLTP_ITF_EXP_TP_INIT                                 FblTp_Init


#define FBLTP_ITF_EXP_GET_CURR_TP_CHANNEL    FblTp_Get_CurrRxReqChannel


#define FBLTP_ITF_EXP_NOTIFY_END_OF_TX           FblTp_NotifyCBForEndOfTxRsp


















#ifdef __cplusplus
extern "C" {
#endif



#endif /* end of #ifndef _FBLTPEXTITF_H */
