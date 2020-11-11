/**
*
* \file
*
* \brief Flash Boot Loader Uds Services Layer (FblUds) design .
*
*        This file will define all of the imported and exported interfaces 
*        which will be used in the FBL Uds Services layer
* 
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is attached in
* the Flash Boot Loader software package.
*
*
*================================================================================*
*                               REVERSION HISTORY                                *
*================================================================================*
*  REVISION         |   DATE        |                         |      AUTHOR      *
*--------------------------------------------------------------------------------*
*  RTA_UDS_1.0      | Aug/13/2012   |                         | Yongqiang Deng   *
* Creation of this file                                                          *
*--------------------------------------------------------------------------------*
*  RTA_BSW_2.0      | Jan/12/2014   |                         | Yongqiang Deng   *
* Update this file for eAAM FBL project                                          *
*--------------------------------------------------------------------------------*
**********************************************************************************/



#ifndef _FBLUDSEXTITF_H
#define _FBLUDSEXTITF_H

#ifdef __cplusplus
extern "C" {
#endif


#include "uds_target.h"
#include "uds_priv.h"
#include "FblTpExtItf.h"



/* Imported interfaces . */
#define FBLUDS_DISABLE_ALL_INTERRUPTS()    SuspendAllInterrupts()
#define FBLUDS_ENABLE_ALL_INTERRUPTS()     ResumeAllInterrupts()



#define FBLUDS_ITF_IMP_MEM_COPY                 Uds_MemCopy  // defined in the uds_target.h
#define FBLUDS_ITF_IMP_CHK_AND_RD_RX_REQ_MSG    FblTp_GetReceivedCanMsg /* defined in FblTp.c */
#define FBLUDS_ITF_IMP_N_USDATA_REQUEST         FblTp_N_USData_request /* defined in FblTp.c */





/* Exported functions prototypes and macros */
/* ---------------------------------------- */
extern void FblUds_Initialize( void );
extern void FblUds_MainTaskEntryPoint_CyclicTask(void);

extern uint8_t FblUds_SimpleSesnMgr_ChkSesnChangePreCndIsAllow(uint8_t i_CurrSession,
                                                                         uint8_t i_DestSession);


extern uint8_t FblUds_SimpleSesnMgr_GetActiveSession( void );
extern uint8_t FblUds_SimpleSesnMgr_SetActiveSession( const uint8_t sessionLevel );
extern uint8_t FblUds_SimpleSesnMgr_GetReceivedTaType( void );
extern void    FblUds_SimpleSesnMgr_Reload_S3_SeverTimer(void); 
extern void FblUds_SimpleSesnMgr_SetS3ServerTimerValue(uint32_t i_NewValue);

extern uint8_t   FblUds_SimpleSesnMgr_ChangeSession(uint8_t i_DestSession); 


#define FBLUDS_ITF_EXP_UDS_INIT                                 FblUds_Initialize
#define FBLUDS_ITF_EXP_UDS_CYCLIC_TASK          FblUds_MainTaskEntryPoint_CyclicTask

#define FBLUDS_ITF_EXP_CHK_SESN_CHNG_PRE_CND_IS_ALLOW  FblUds_SimpleSesnMgr_ChkSesnChangePreCndIsAllow
#define FBLUDS_ITF_EXP_SET_ACTIVE_SESSION              FblUds_SimpleSesnMgr_SetActiveSession
#define FBLUDS_ITF_EXP_GET_ACTIVE_SESSION              FblUds_SimpleSesnMgr_GetActiveSession
#define FBLUDS_ITF_EXP_RELOAD_S3_SVR_TMR               FblUds_SimpleSesnMgr_Reload_S3_SeverTimer
#define FBLUDS_ITF_EXP_CHANGE_SESSION                  FblUds_SimpleSesnMgr_ChangeSession 
#define FBLUDS_ITF_EXP_GET_RX_TA_TYPE                  FBLTP_ITF_EXP_GET_CURR_TP_CHANNEL


#ifdef __cplusplus
extern "C" {
#endif



#endif /* end of #ifndef _FBLUDSEXTITF_H */
