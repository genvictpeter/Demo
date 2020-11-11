
//****************************************************************************/
// @Module       
// @Filename      FblUds.c
// @Project       BQApp
//----------------------------------------------------------------------------
// @Controller    TI 28034
//
// @Compiler      V5.211
//
// @Codegenerator CCS 3.3
//
// @Description   
//
//----------------------------------------------------------------------------
// @Date          12/19/2014
//
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

//****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#include "FblUdsExtItf.h"   /* external uds interfaces header file */
#include "uds_target.h"
#include "uds_priv.h"
#include "uds_confpriv.h"
#include "uds_inf.h"
#include "uds_pub.h"
#include "Task.h"
#include "FbltpExtItf.h"
#include "FblMgr.h"
#include "CANProtocal.h"


/* global data definitions */
/******************************************************************************
*
* UDS A_PDU.Data Buffers
*
******************************************************************************/
/* the private data definitions */

/* UDS A_PDU.Data unit for UDS <service>.indication to 
   be exchanged with Uds services. 
 */
/*
typedef UDS_STATE_TYPE struct
{
	Uds_PduLength_t		  msgLength;	
	uint8_t                           CurrSvcHavSubFunc; 
	uint8_t                           CurrSvcIsSupPosRspBitSet; 
	uint8_t                           CurrInTempDiagReqSid;
	uint8_t                           CurrIncomDiagReqSid;
	uint8_t                           CurrProcessingDiagReqSid;
	Uds_PduData_t		  pduData[ISO15765_APDU_MSGDATA_LENGTH];	
} Uds_APduData_t;
*/
Uds_APduData_t	g_FblUds_APduDataInd;

/* UDS A_PDU.Data unit for UDS <service>.response to 
   be exchanged with Uds services. 
 */
Uds_APduData_t	g_FblUds_APduDataResp;

Uds_APduData_t*  pul_FblUds_APduDataIndPtr; //  = &g_FblUds_APduDataInd;
Uds_APduData_t*  pul_FblUds_APduDataRespPtr; // = &g_FblUds_APduDataResp;

/******************************************************************************
*
* UDS Service Table Configuration structures
*
******************************************************************************/

/*
 * Configuration of uds services table.
 *
 * UDS_NUM_OF_SERVICES - Total number of services defined in uds_confdefs.h
 * Each service shall have one corresponding array element configured.
 */
const Uds_ServiceTable_t	Uds_ServiceTable[] =
{
 /*      service  pFnc_UdsSvcHdlr                   supported  addrPhy    addrFun    securityLevel            */
 /*      Id                                         Session    Supported  Supported                           */ 
 /* 0u*/{0x10u,   UdsApp_DiagSessionControl,           0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_DiagSessionControl           */
 /* 1u*/{0x11u,   UdsApp_EcuReset,                     0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_EcuReset                     */
 /* 2u*/{0x14u,   UdsApp_ClearDiagnosticInformation,   0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ClearDiagnosticInformation   */
 /* 3u*/{0x19u,   UdsApp_ReadDTCInformation,           0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ReadDTCInformation           */
 /* 4u*/{0x22u,   UdsApp_ReadDataByIdentifier,         0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ReadDataByIdentifier         */
 /* 5u*/{0x23u,   UdsApp_ReadMemoryByAddress,          0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_ReadMemoryByAddress          */
 /* 6u*/{0x24u,   UdsApp_ReadScalingDataByIdentifier,  0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ReadMemoryByAddress          */
 /* 7u*/{0x27u,   UdsApp_SecurityAccess,               0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_SecurityAccess               */
 /* 8u*/{0x28u,   UdsApp_ComControl,                   0x08u,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_CommunicationControl         */
 /* 9u*/{0x2Au,   UdsApp_ReadDataByPeriodicIdentifier, 0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ReadDataByPeriodicIdentifier */
 /*10u*/{0x2Cu,   UdsApp_DynamicDefineDataIdentifier,  0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_DynamicDefineDataIdentifier  */
 /*11u*/{0x2Eu,   UdsApp_WriteDataByIdentifier,        0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L11}, /* Uds_WriteDataByIdentifier        */
 /*12u*/{0x2Fu,   UdsApp_IOControlByIdentifier,        0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L11}, /* Uds_IOControlByIdentifier        */
 /*13u*/{0x31u,   UdsApp_RoutineControl,               0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_RoutineControl               */
 /*14u*/{0x34u,   UdsApp_RequestDownload,              0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_RequestDownload              */
 /*15u*/{0x35u,   UdsApp_RequestUpload,                0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_RequestUpload                */
 /*16u*/{0x36u,   UdsApp_TransferData,                 0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_TransferData                 */
 /*17u*/{0x37u,   UdsApp_RequestTransferExit,          0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_RequestTransferExit          */
 /*18u*/{0x3Du,   UdsApp_WriteMemoryByAddress,         0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_WriteMemoryByAddress         */
 /*19u*/{0x3Eu,   UdsApp_TesterPresent,                0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_TesterPresent                */
 /*20u*/{0x83u,   UdsApp_AccessTimingParameter,        0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_AccessTimingParameter        */
 /*21u*/{0x84u,   UdsApp_SecuredDataTransmission,      0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_SecuredDataTransmission      */
 /*22u*/{0x85u,   UdsApp_ControlDTCSetting,            0x0Au,     TRUE,      TRUE,      UDS_SECURITY_LEVEL_L0}, /* Uds_ControlDTCSetting            */
 /*23u*/{0x86u,   UdsApp_ResponseOnEvent,              0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_ResponseOnEvent              */
 /*24u*/{0x87u,   UdsApp_LinkControl,                  0x08u,     TRUE,      FALSE,     UDS_SECURITY_LEVEL_L0}, /* Uds_LinkControl                  */
 /*25u*/{0x01u,   UdsApp_ISO_15031_5_Read01, 		    0x0Au,	   TRUE,	  TRUE, 	 UDS_SECURITY_LEVEL_L0},
 /*26u*/{0x03u,   UdsApp_ISO_15031_5_Read03, 		    0x0Au,	   TRUE,	  TRUE, 	 UDS_SECURITY_LEVEL_L0},
 /*27u*/{0x07u,   UdsApp_ISO_15031_5_Read07, 		    0x0Au,	   TRUE,	  TRUE, 	 UDS_SECURITY_LEVEL_L0},
 /*28u*/{0x09u,   UdsApp_ISO_15031_5_Read09, 		    0x0Au,	   TRUE,	  TRUE, 	 UDS_SECURITY_LEVEL_L0},
 
}; /* end of table : Uds_ServiceTable_t	Uds_ServiceTable[]   */

static uint16_t  ruw_FblUds_RxDiagReqMsgLen ;//= 0x0000u;
static uint8_t*  pub_FblUds_RxDiagReqMsgBufPtr ;//= NULL;

//static uint8_t   rub_FblUds_SimpleSesnMgr_CurrActiveSession ;//= 0x00u;
uint8_t   rub_FblUds_SimpleSesnMgr_CurrActiveSession;
static uint32_t    rul_FblUds_SimpleSesnMngr_S3_SeverTmr ;//= 0x00000000u;
static uint32_t    rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr  ;//= 0x00000000u;

static uint8_t rub_FblUds_AppFsmSt  ;//= 0x00u;
static uint32_t rul_FblUds_AppFsmPendingTmr  ;//= 0x00000000u;
static uint32_t rul_FblUds_AppFsmMaxPendingTmr ;//= 0x00000000u;

static uint8_t rub_SavedExitResponse ;//= 0x00u;
static uint8_t rub_ResultCanExitDpPend ;//= FALSE;
static uint8_t rub_RspSendCanExitDpPend ;//= FALSE;


static const T_FBLUDS_FP_PERIODIC_PARAMVOID capf_FblUdsPeriodicItfTable[] =
{
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_DTC_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RTN_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_SECU_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_WTDID_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RDDID_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_IOCTL_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_CMD_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_CMD_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_TSFRDAT_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_CDF_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RNODBSM_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RDBSM_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RDSI_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_ITF_INT_RSRBDN_PEND_PERIODIC_CHK,
   (T_FBLUDS_FP_PERIODIC_PARAMVOID)UDS_APP_28_PEND_PERIODIC_CHK
};

extern Uint16 CurRxUdsMsgBuf;
extern Uint16 PreRxUdsMsgBuf0[];
extern Uint16 PreRxUdsMsgBuf1[];
extern Uint16 PreRxUdsMsgBuf2[];
extern Uint16 PreRxUdsMsgBuf3[];


/* private functions declerations */
static void FblUds_CyclicTask_RxRdAndDispatchProc(void);

static void FblUds_DispatchRxDiagSvcReqProc(Uds_APduData_t* pAPduInd,
		                                    Uds_APduData_t* pAPduResp);
static void UDS_FN_TYPE Uds_Service_Pending_StateManager(uint8_t lub_SevericNRC);
static UDS_FSM_PENDING_ST_t UDS_FN_TYPE Uds_generic_Get_CurrPendFSMState(void); 
static Std_UdsReturnType UDS_FN_TYPE Uds_generic_RcvAndSaveDiagReqMsg(
		                          Uds_APduData_t* pAPduInd,
		                          Uds_APduData_t* pAPduResp);
static uint8_t UDS_FN_TYPE Uds_generic_chkPendingNeededForSvc( uint8_t lub_SID );
static void UDS_FN_TYPE Uds_generic_ServiceCommonProcess(
		                      Uds_APduData_t* 			  pAPduInd, 
		                      Uds_APduData_t* 			  pAPduResp,
                              T_FUNC_PTR_UDS_SVC_HANDLER  pFnc_UdsSvcSpecProc);


static void FblUds_SimpleSesnMgr_TickS3ServerTimerValue(void); 
static void FblUds_SimpleSesnMngr_CyclicTskEntryPoint( void ); 

static void Uds_generic_if_Task (void);

static void UDS_FN_TYPE UdsApp_PendingPeriod_OvertimeEvtHandler(void);

static void FblUds_CyclicTask_RxRdAndDispatchProc(void)
{
   uint8_t*  plub_TpBufferPtr;
   uint16_t  lubMsgLen; 
   
   plub_TpBufferPtr = FBLUDS_ITF_IMP_CHK_AND_RD_RX_REQ_MSG(&lubMsgLen);
   
   if (plub_TpBufferPtr != NULL &&
       lubMsgLen != 0x00u)
   {
       /* this means the new diag request is received, to reload the S3 timer */
       UDS_APP_ITF_IMP_SET_RELOAD_S3SVR_TMR();
	   
       pub_FblUds_RxDiagReqMsgBufPtr = plub_TpBufferPtr;
	 ruw_FblUds_RxDiagReqMsgLen =   lubMsgLen;
	 
       /* read into the message length 
        */
   	   pul_FblUds_APduDataIndPtr->msgLength = ruw_FblUds_RxDiagReqMsgLen; 
	   /* Copy msgLen bytes of data into the current session Rx buffer. 
	    */
	   FBLUDS_ITF_IMP_MEM_COPY( &(pul_FblUds_APduDataIndPtr->pduData[0x00u]), 
	                            pub_FblUds_RxDiagReqMsgBufPtr, 
	                            (uint32_t)(ruw_FblUds_RxDiagReqMsgLen) );
	   /* and copy first 2 bytes into the response message buffer in advance 
	    */                         
   	   (pul_FblUds_APduDataRespPtr->pduData[0x00u]) = (pul_FblUds_APduDataIndPtr->pduData[0x00u]);
   	   (pul_FblUds_APduDataRespPtr->pduData[0x01u]) = (pul_FblUds_APduDataIndPtr->pduData[0x01u]);
  	   (pul_FblUds_APduDataRespPtr->pduData[0x02u]) = (pul_FblUds_APduDataIndPtr->pduData[0x02u]);

       FblUds_DispatchRxDiagSvcReqProc(pul_FblUds_APduDataIndPtr,
		                               pul_FblUds_APduDataRespPtr);
   }
   else
   {
   	
   	
   }	
	
} /* end of FblUds_CyclicTask_MainEntryPoint() */



static void FblUds_DispatchRxDiagSvcReqProc(Uds_APduData_t* pAPduInd,
		                                    Uds_APduData_t* pAPduResp)
{
   uint8_t  i; 
   uint8_t  lub_RcvdReqSid = 0x00u;
   uint8_t  lub_uds_service_found = 0xFFu;	/* Init to invalid index. */
   
   /* Start processing of UDS service requests */
   lub_RcvdReqSid = pAPduInd->pduData[0x00u];

   // Save service identifier
   pAPduInd->CurrInTempDiagReqSid = lub_RcvdReqSid;
   pAPduResp->CurrInTempDiagReqSid = lub_RcvdReqSid;

    // Inquire uds service table
	for ( i = 0x00u; i < UDS_NUM_OF_SERVICES; i++ ) 
	{
		if ( Uds_ServiceTable[i].serviceId == lub_RcvdReqSid ) 
		{
			lub_uds_service_found = i; 
			break;  
		}
		else
		{
		}
	} /* end of for (i = 0x00u; i < UDS_NUM_OF_SERVICES; i++) */ 

	if ( lub_uds_service_found != 0xFFu ) 
	{	 
		/* Call the diag service handler to process service. 
		 */
		Uds_generic_ServiceCommonProcess( pAPduInd, 
										  pAPduResp,
										  (Uds_ServiceTable[lub_uds_service_found].pFnc_UdsSvcHdlr) );  
	}
	else
	{
		/* Service not found, should return the NRC: 0x11 ServiceNotSupported. */
		Uds_generic_SendResp(pAPduResp, UDS_NRC_SERVICENOTSUPPORTED);
	}

	return;
}




/**
 * This function initialises the UDS software package. It must be called exactly once.
 */
void FblUds_Initialize( void )
{

   pul_FblUds_APduDataIndPtr  = & g_FblUds_APduDataInd;
   pul_FblUds_APduDataRespPtr = & g_FblUds_APduDataResp;

   ruw_FblUds_RxDiagReqMsgLen = 0x0000u;
   pub_FblUds_RxDiagReqMsgBufPtr = NULL;

   rub_FblUds_SimpleSesnMgr_CurrActiveSession = 0x00u;
   rul_FblUds_SimpleSesnMngr_S3_SeverTmr = 0x00000000u;
   rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr  = 0x00000000u;

   rub_FblUds_AppFsmSt  = 0x00u;
   rul_FblUds_AppFsmPendingTmr  = 0x00000000u;
   rul_FblUds_AppFsmMaxPendingTmr = 0x00000000u;

   rub_SavedExitResponse = 0x00u;
   rub_ResultCanExitDpPend = FALSE;
   rub_RspSendCanExitDpPend = FALSE;

   Uds_Generic_DatMgr_Init();

   #ifdef UDS_ENABLE_SECURITYACCESS
       UdsApp_27SecuAcc_Init();
   #endif /* end of #ifdef UDS_ENABLE_SECURITYACCESS */
	
   #ifdef UDS_ENABLE_READDATABYPERIODICIDENTIFIER
       UdsApp_2aRdDatByPeriodDid_Init(); 
   #endif /* end of #ifdef UDS_ENABLE_READDATABYPERIODICIDENTIFIER */

   #ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER
       UdsApp_2eWtDatByDid_Init();
   #endif /* end of #ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER */

   #ifdef UDS_ENABLE_ROUTINECONTROL
       UdsApp_31RtnCtrl_Init();
   #endif /* end of #ifdef UDS_ENABLE_ROUTINECONTROL */

   #ifdef UDS_ENABLE_REQUESTDOWNLOAD
       UdsApp_34ReqDnld_InitCurrReqDnldData();
   #endif /* end of #ifdef UDS_ENABLE_REQUESTDOWNLOAD */

   #ifdef UDS_ENABLE_TRANSFERDATA
       UdsApp_36TransferDat_InitBlkSeqCntrBefrTsfrDat();
   #endif /* end of #ifdef UDS_ENABLE_TRANSFERDATA */

   #ifdef UDS_ENABLE_CONTROLDTCSETTING
       UdsApp_85CtrlDtcSet_Init();
   #endif /* end of #ifdef UDS_ENABLE_CONTROLDTCSETTING */
	
   #ifdef UDS_ENABLE_LINKCONTROL
       UdsApp_87LnkCtrl_Init();
   #endif /* end of #ifdef UDS_ENABLE_LINKCONTROL */
	
	
}

         
/* all of the UDS cyclic tasks which should be processed in period 
   timebase shoud be put into this uds 400us task main entrypoint.
*/
void FblUds_MainTaskEntryPoint_CyclicTask(void)
{
   uint8_t lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
   uint8_t lub_FblUdsPendPeriodicTblNum = 0x00u;
   uint8_t lub_FblUdsPendPeriodicRecSize = 0x00u;
		
   FblUds_CyclicTask_RxRdAndDispatchProc(); 
   FblUds_SimpleSesnMngr_CyclicTskEntryPoint();
   
   #ifdef UDS_ENABLE_ECURESET
      UdsApp_11EcuRst_CyclicTskEntryPoint();
   #endif /* end of #ifdef UDS_ENABLE_ECURESET */

   #ifdef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION
      //UdsApp_14ClrDiagInfor_CyclicTskEntryPoint(); 
   #endif /* end of #ifdef UDS_ENABLE_CLEARDIAGNOSTICINFORMATION */
   
   #ifdef UDS_ENABLE_SECURITYACCESS
      UdsApp_27SecuAcc_CyclicTskEntryPoint();
   #endif /* end of #ifdef UDS_ENABLE_SECURITYACCESS  */

   
   Uds_generic_if_Task(); 
 
   if (rub_FblUds_AppFsmSt == UDS_APP_FSM_PENDING_ST)
   {
       lub_FblUdsPendPeriodicRecSize = sizeof(capf_FblUdsPeriodicItfTable) / 
		                                            sizeof (capf_FblUdsPeriodicItfTable[0x00u])	;
	/* search for all pending activities... */
       lub_FblUdsPendPeriodicTblNum = 0x00u;
	   while ( lub_FblUdsPendPeriodicTblNum < lub_FblUdsPendPeriodicRecSize  )
	   {
		 if (   (capf_FblUdsPeriodicItfTable[lub_FblUdsPendPeriodicTblNum]) == NULL )		   
		 {
		   /* nothing to do, function undefined */
		 }
		 else /* if (   (capf_FblUdsPeriodicItfTable[lub_FblUdsPendPeriodicTblNum]) != NULL ) */
		 {
			lub_response = (capf_FblUdsPeriodicItfTable[lub_FblUdsPendPeriodicTblNum])() ;
			if (lub_response != UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING)
			{
                          /* the service routine has finished, this means , each time, only a single pending is allowed , single thread */
			     lub_FblUdsPendPeriodicTblNum = lub_FblUdsPendPeriodicRecSize ;
						  
			}
			else
			{
			}
		 } /* end of else if (   (capf_FblUdsPeriodicItfTable[lub_FblUdsPendPeriodicTblNum]) != NULL ) */
              lub_FblUdsPendPeriodicTblNum++;
	   } /* end of while ( lub_FblUdsPendPeriodicTblNum < lub_FblUdsPendPeriodicRecSize  ) */
       
       Uds_Service_Pending_StateManager(lub_response);
   }
   else
   {
   }
} /* end of FblUds_MainTaskEntryPoint_CyclicTask() */

static void Uds_generic_if_Task (void)
{
  /*the pendig timers are used only in pnding sttate*/
   if(rub_FblUds_AppFsmSt == UDS_APP_FSM_PENDING_ST)
   {
      if(rul_FblUds_AppFsmPendingTmr < UDS_APP_FSM_TMR_PENDING_REL_TIME)
      {
         rul_FblUds_AppFsmPendingTmr ++;
      }
      if(rul_FblUds_AppFsmMaxPendingTmr < UDS_APP_FSM_TMR_MAX_PENDING_REL_TIME)
      {
         rul_FblUds_AppFsmMaxPendingTmr ++;
      }

   }
   else
   {
      /*reset pending timers (for robustness)*/
      rul_FblUds_AppFsmPendingTmr = 0x00000000u;
      rul_FblUds_AppFsmMaxPendingTmr = 0x00000000u;
   }


} /* end of Uds_generic_if_Task() */



/**
 * This function implement UDS services that do not implemented.
 */
Std_UdsReturnType UDS_FN_TYPE UdsApp_ServiceUnknown(Uds_APduData_t* pAPduInd, 
                                                       Uds_APduData_t* pAPduResp )
{
   pAPduInd = pAPduInd;  /* just to remove the compilation warning */
   Uds_generic_SendResp(pAPduResp, UDS_NRC_SERVICENOTSUPPORTED);
  
   return  UDS_NRC_SERVICENOTSUPPORTED;
}

/**
 * This function will handling all of the service pending states.
 *
 * \param [in] lub_SevericNRC	Value of negative response code.
 *
 */

static void UDS_FN_TYPE Uds_Service_Pending_StateManager(uint8_t i_lubSeviceRspCode) 
{
   uint8_t lub_SevericNRC = i_lubSeviceRspCode; 
  
   switch (rub_FblUds_AppFsmSt)
   {
      default:     
          lub_SevericNRC = UDS_NRC_GENERALREJECT;
	   Uds_generic_SendResp( pul_FblUds_APduDataRespPtr, lub_SevericNRC);	  
          rub_FblUds_AppFsmSt = UDS_APP_FSM_REGULAR_ST;     
          break;
      case UDS_APP_FSM_REGULAR_ST:
      
              /*check if a service needs to start the response pending mechanism*/
             if (lub_SevericNRC == UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING)
             {
                  rub_FblUds_AppFsmSt = UDS_APP_FSM_PENDING_ST;
                 rub_SavedExitResponse = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
                 rub_ResultCanExitDpPend = FALSE;
                 rub_RspSendCanExitDpPend = FALSE;
              }
	       else
	       {
	       }
		 
              rul_FblUds_AppFsmPendingTmr = 0x00000000u;
              rul_FblUds_AppFsmMaxPendingTmr = 0x00000000u;
              break;
      case UDS_APP_FSM_PENDING_ST:
      
           if (rub_ResultCanExitDpPend == TRUE)
           {
               //if (rub_RspSendCanExitDpPend == TRUE )
               {
                   // if busy condition is false and
                   // rsp is sent successfully , to
                   /// return to DEFAUL state
                   rub_FblUds_AppFsmSt = UDS_APP_FSM_REGULAR_ST;
               }
               //else // if (rub_RspSendCanExitDpPend == FALSE )
               {
                   // to resend the response
                   // Uds_generic_SendResp( p_SavedInPduRspPtrForPending, rub_SavedExitResponse);
               } // end of else // if (rub_RspSendCanExitDpPend == TRUE )
           } // end of if (rub_ResultCanExitDpPend == TRUE)
           else // if (rub_ResultCanExitDpPend == FALSE)
           {
               if(lub_SevericNRC != UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING)
               {
                  /*the service has finished , so send response*/
		    /* dyq at 20130911 */
		     // pul_FblUds_APduDataRespPtr->	msgLength = 0x03u;	  
		      
		          Uds_generic_SendResp( pul_FblUds_APduDataRespPtr, lub_SevericNRC);	  
                  rub_FblUds_AppFsmSt = UDS_APP_FSM_REGULAR_ST;
                  rub_ResultCanExitDpPend = TRUE;
                  rub_SavedExitResponse = lub_SevericNRC;
               }
               else //if(lub_SevericNRC == UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING)
               {
                  /*check if maxim response pendig time has ended*/
                  if(rul_FblUds_AppFsmMaxPendingTmr >= UDS_APP_FSM_TMR_MAX_PENDING_REL_TIME)
                  {
                     rub_FblUds_AppFsmSt = UDS_APP_FSM_REGULAR_ST;
                     rub_ResultCanExitDpPend = TRUE;
                     rub_SavedExitResponse = UDS_NRC_GENERALREJECT;
                     Uds_generic_SendResp( pul_FblUds_APduDataRespPtr, rub_SavedExitResponse);	 
 
                     /*notify the event of pending over timed to all of other services handler  */
                     UdsApp_PendingPeriod_OvertimeEvtHandler();
                  }
                  else //if(rul_FblUds_AppFsmMaxPendingTmr < UDS_APP_FSM_TMR_MAX_PENDING_REL_TIME)
                  {
                      /*check if is time for a new response pending message*/
                     if((rul_FblUds_AppFsmPendingTmr >= UDS_APP_FSM_TMR_PENDING_REL_TIME) ) //&&
                        // (rub_FblUds_AppFsmSt == UDS_APP_FSM_PENDING_ST))
                     {
                         rul_FblUds_AppFsmPendingTmr = 0x00000000u;
                         Uds_generic_SendResp( pul_FblUds_APduDataRespPtr, UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING);	 
                     }
                     else
                     {

                     }
                  } // end of else rul_FblUds_AppFsmMaxPendingTmr < UDS_APP_FSM_TMR_MAX_PENDING_REL_TIME
               } // end of elseif(lub_SevericNRC == UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING)
           } // end of else // if (rub_ResultCanExitDpPend == FALSE)
            // end of case DP_APPL_PENDING_STATE
           break;
   } // end of switch (rub_FblUds_AppFsmSt)
} /* end of Uds_Service_Pending_StateManager()  */


static void UDS_FN_TYPE UdsApp_PendingPeriod_OvertimeEvtHandler(void)
{
	/* inform all of the other needed services that 
	    UDS Application Finite State Machine Pending Periodic timer is overtimed 
	*/

   UDS_APP_ITF_INT_DTC_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_RTN_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_SECU_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_WTDID_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_RDDID_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_IOCTL_PEND_OVERTIME_HANDLER();   
   UDS_APP_ITF_INT_CMD_PEND_OVERTIME_HANDLER();   
	
}

/**
 *
 *
 */
static UDS_FSM_PENDING_ST_t UDS_FN_TYPE Uds_generic_Get_CurrPendFSMState(void) 
{
	/* TODO */
	return (UDS_FSM_PENDING_ST_t)rub_FblUds_AppFsmSt; 
}

/**
 * This function check whether previous uds service still under processing.
 *
 * \return
 *  - TRUE:		This previous uds service pending.
 *	- FALSE:	This previous uds service finished processing.
 */
uint8_t UDS_FN_TYPE Uds_generic_IsAPrevReqAlreadyRunning(uint8_t i_lub_CurrIncomeReqSid)
{
   uint8_t                      lub_IsAPrevReqAlreadingRunning = FALSE;
   uint8_t				lub_IsRoutineRunning;
   UDS_FSM_PENDING_ST_t	lub_CurrSvcPendFsmState; 
   
   lub_IsRoutineRunning = Uds_31RtnCtrl_Get_IsRoutineAlreadyRunning();
   lub_CurrSvcPendFsmState = Uds_generic_Get_CurrPendFSMState();
   if (i_lub_CurrIncomeReqSid != 0x31u) 
   {
       if ( (lub_CurrSvcPendFsmState == UDS_APP_FSM_PENDING_ST) ||
             (lub_IsRoutineRunning == (uint8_t)TRUE) )
       {
             lub_IsAPrevReqAlreadingRunning =  (uint8_t)TRUE;
       }
       else
       {
             lub_IsAPrevReqAlreadingRunning = (uint8_t)FALSE;
       }
   }
   else // if (i_lub_CurrIncomeReqSid == 0x31u) 
   { 
        if ( (lub_CurrSvcPendFsmState == UDS_APP_FSM_PENDING_ST)  &&   /* if previous request has already enter pending state */
	      //(rub_SavedPrevIncomingSid != 0x31u))    /* and this previous pending request is not 0x31 RoutineControl */
	       (pul_FblUds_APduDataIndPtr->CurrProcessingDiagReqSid != 0x31u))
        {
              lub_IsAPrevReqAlreadingRunning =  (uint8_t)TRUE;            
        }
	 else
	 {
              lub_IsAPrevReqAlreadingRunning = (uint8_t)FALSE;

	 }
       
   } /* end of  else if (i_lub_CurrIncomeReqSid == 0x31u)  */
   return lub_IsAPrevReqAlreadingRunning;
}

/**
 * This function
 * - Copy received service data to response buffer.
 * - Update response code.
 * - Check availability of sub-functions and updata SupPosRspBit.
 *
 * \param [in] pAPduInd		The container of service indication data buffer.
 * \param [in] pAPduResp	The container of service response data buffer.
 *
 * \return
 *  - Service response code.
 */
static Std_UdsReturnType UDS_FN_TYPE Uds_generic_RcvAndSaveDiagReqMsg(
		                          Uds_APduData_t* pAPduInd,
		                          Uds_APduData_t* pAPduResp
)
{
	Std_UdsReturnType lub_rc = UDS_POSITIVE_RESPONSE;

	/* Copy whole of the diag request data content into the response buffer. */
	Uds_MemCopy( &(pAPduResp->pduData[0x00u]), 		/* pDest */
				&(pAPduInd->pduData[0x00u]),  		/* pSrc */
				(uint32_t)(pAPduInd->msgLength) );    /* numBytes */

	/* Check whether have sub function or not according to the input service id. */
	switch ( pAPduInd->pduData[0x00u] )
	{
		default :
		   /* Drop in this case means service is not supported. */
		   /* In fact, before service is dispatched, non-supported services have already been found.*/
		   lub_rc = UDS_NRC_SERVICENOTSUPPORTED;
		   pAPduResp->CurrSvcHavSubFunc  = (uint8_t)FALSE;
		   break;
		 
		/* totally, there are 12 services with sub functions */              
		case 0x10u:  /* DiagnosticSessionControl        Service Id */
		case 0x11u:  /* EcuReset                        Service Id */
		case 0x19u:  /* ReadDtcInformation              Service Id */
		case 0x27u:  /* SecurityAccess                  Service Id */
		case 0x28u:  /* CommunicationControl            Service Id */
		case 0x2Cu:  /* DynamicallyDefineDataIdentifier Service Id */
		case 0x31u:  /* RoutineControl                  Service Id */
		case 0x3Eu:  /* TesterPresent                   Service Id */
		case 0x83u:  /* AccessTimingParameters          Service Id */ 
		case 0x85u:  /* ControlDtcSetting               Service Id */
		case 0x86u:  /* ResponseOnEvent                 Service Id */
		case 0x87u:  /* LinkControl                     Service Id */      
		   pAPduResp->CurrSvcHavSubFunc  = (uint8_t)TRUE;
		   break;
		   
		/* totally, there are 13 services without sub functions. */    
		case 0x14u:  /* ClearDiagnosticInformation      Service Id */
		case 0x22u:  /* ReadDataByIdentifier            Service Id */
		case 0x23u:  /* ReadMemoryByAddress             Service Id */
		case 0x24u:  /* ReadScallingDataByIdentifier    Service Id */ 
		case 0x2Au:  /* ReadDataByPeriodicalIdenfifier  Service Id */
		case 0x2Eu:  /* WriteDataByIdentifier           Service Id */
		case 0x2Fu:  /* InputOutputControlByIdentifier  Service Id */
		case 0x34u:  /* RequestDownload                 Service Id */
		case 0x35u:  /* RequestUpload                   Service Id */
		case 0x36u:  /* TransferData                    Service Id */
		case 0x37u:  /* RequestTransferExit             Service Id */
		case 0x3Du:  /* WriteMemoryByAddress            Service Id */
		case 0x84u:  /* SecuredDataTransmission         Service Id */
		case 0x01u:
		case 0x03u:
		case 0x07u:
		case 0x09u:
		   pAPduResp->CurrSvcHavSubFunc  = (uint8_t)FALSE;
		   break;
	}

	if ( (pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE) &&
		(pAPduInd->msgLength >= 0x02u) )
	{
		if ((pAPduInd->pduData[0x01u]) & UDS_C_SUB_FUNC_MASK_YES_SPRB7)
		{
			pAPduResp->CurrSvcIsSupPosRspBitSet = (uint8_t)TRUE;
		}
		else
		{
			pAPduResp->CurrSvcIsSupPosRspBitSet = (uint8_t)FALSE;
		}
	}
	else
	{
		pAPduResp->CurrSvcIsSupPosRspBitSet = (uint8_t)FALSE;
	}
	
	// rub_SavedPrevIncomingSid          = (pAPduInd->pduData[0x00u]);
	pAPduInd->CurrIncomDiagReqSid   = (pAPduInd->pduData[0x00u]);
	pAPduResp->CurrIncomDiagReqSid = (pAPduInd->pduData[0x00u]);
	
       pAPduInd->CurrProcessingDiagReqSid   = (pAPduInd->pduData[0x00u]);
	pAPduResp->CurrProcessingDiagReqSid = (pAPduInd->pduData[0x00u]); 

	UDS_APP_ITF_IMP_SET_PRVNT_ECU_2_SLEEP();
	return lub_rc;
}

/**
 * This function check whether the current UDS service need asynchronous processing.
 *
 * \param [in] lub_SID		The service Id for current UDS service.
 *
 * \return
 *  - TRUE:		This current service need asynchronous process(result will be generate later).
 *	- FALSE:	This current service can be processed this time.
 */
static uint8_t UDS_FN_TYPE Uds_generic_chkPendingNeededForSvc( uint8_t lub_SID )
{
	uint8_t lub_tmpIsPendingNeeded = (uint8_t)FALSE;

	switch (lub_SID)
	{
	  default :
		break;
	  /* Below services need pending handling, more services may be added in the future  */       
	  case 0x14u: /* ClearDiagnosticInformation */
	  case 0x22u: /* ReadDataByIdentifier (just remote asnychronized reading) */
	  case 0x2Eu: /* WriteDataByIdentifier  */
	  case 0x31u: /* RoutineControl */
		lub_tmpIsPendingNeeded = (uint8_t)TRUE;
		break;
	}

    return lub_tmpIsPendingNeeded;
}

/**
 * This function check service response type required to send and update serviceState.
 *
 * \param [in] pAPduResp	The container for the response data.
 * \param [in] lub_error	The response action according to current service processing.
 *
 */
void UDS_FN_TYPE Uds_generic_SendResp( Uds_APduData_t * pAPduResp, uint8_t lub_error )
{
	uint8_t	lub_IsAllowedToSendNegRsp = (uint8_t)FALSE;
	uint8_t	lub_IsAllowedToSendPosRsp = (uint8_t)FALSE;
       
	if ( Uds_generic_IsAPrevReqAlreadyRunning(pAPduResp->pduData[0x00u]) &&
	     pAPduResp->pduData[0x00u] == 0x3Eu) 
	{
	     /* if there is already a service is running 
	        then to ignore the 0x3E service , not to send back the response.
	      */  
		 //Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_NO_RESPONSE);
	     return; 
	} 
	else 
	{
	  
	}       
	   
	if(lub_error != UDS_POSITIVE_RESPONSE)
	{
		/*make negative response*/
		if (pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE)
		{
			/* current service have sub-function */
			if ( TARGETADDR_PHYSICAL == FBLUDS_ITF_EXP_GET_RX_TA_TYPE() )
			{/* Physical addressing */
				lub_IsAllowedToSendNegRsp = (uint8_t)TRUE;
			}
			else
			{/* Functional addressing */
				if ( (lub_error !=  UDS_NRC_SERVICENOTSUPPORTED)  	 &&  /* NRC 0x11 SNS  */
					 (lub_error !=  UDS_NRC_SUBFUNCTIONNOTSUPPORTED) &&  /* NRC 0x12 SFNS */
					 (lub_error !=  UDS_NRC_REQUESTOUTOFRANGE) )		 /* NRC 0x31 ROOR */
				{
					lub_IsAllowedToSendNegRsp = (uint8_t)TRUE;
				}
			} /* end of if (pAPduResp->tpChannel == CANTP_PHYSICAL) */
		} /* end of if (pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE) */
		else
		{/* pAPduResp->CurrSvcHavSubFunc == (uint8_t)FALSE */
			if ( TARGETADDR_PHYSICAL == FBLUDS_ITF_EXP_GET_RX_TA_TYPE() )
			{/* Physical addressing */
				lub_IsAllowedToSendNegRsp = (uint8_t)TRUE;
			}
			else
			{/* Functional addressing */
				if ((lub_error !=  UDS_NRC_SERVICENOTSUPPORTED) &&
					(lub_error !=  UDS_NRC_REQUESTOUTOFRANGE  ) )
				{
					lub_IsAllowedToSendNegRsp = (uint8_t)TRUE;
				}
			} /* end of if(TARGETADDR_PHYSICAL == FBLUDS_ITF_EXP_GET_RX_TA_TYPE()) */
		} /* end of else of if(pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE) */

		if (lub_IsAllowedToSendNegRsp == (uint8_t)TRUE)
		{
			pAPduResp->pduData[0x00u] = UDS_C_SVC_NEG_RSP_SID;
			if (lub_error == UDS_NRC_SERVICENOTSUPPORTED ||
			    lub_error == UDS_NRC_BUSYREPEATREQUEST     )
			{
			    pAPduResp->pduData[0x01u] = pAPduResp->CurrInTempDiagReqSid; // pAPduResp->pduData[0x00u]; 
			}
			else
			{
			    pAPduResp->pduData[0x01u] = pAPduResp->CurrIncomDiagReqSid; // pAPduResp->pduData[0x00u]; 
			
			}
			
			pAPduResp->pduData[0x02u] = lub_error;
			pAPduResp->msgLength      = 0x03u;
			
			// Start Send
			FBLUDS_ITF_IMP_N_USDATA_REQUEST(&(pAPduResp->pduData[0x00u]), 
                   	                        pAPduResp->msgLength);
			//FblTp_N_USData_request(&(pAPduResp->pduData[0x00u]), 
            //                	            pAPduResp->msgLength);

			/* notify the result to the session manager */
			if (lub_error == UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING) 
			{
				/* if NRC is 0x78 then should tell session manager */ 
				//Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_78HEX_NEG_RESP);            
			} 
			else
			{
				/* all other NRC is response available. */
				//Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_RESP_AVAILABLE);             
			}
		}
		else
		{
			/* not allowed to send back negative response , just do nothing. */
			//Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_NO_RESPONSE);
		}
	} /* end of if(lub_error != UDS_POSITIVE_RESPONSE) */
	else
	{/* if(lub_error == UDS_POSITIVE_RESPONSE) */
		/*make positive response*/
		if (pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE)
		{
			if ( TARGETADDR_PHYSICAL == FBLUDS_ITF_EXP_GET_RX_TA_TYPE() )
			{/* Physical addressing. */
				if (pAPduResp->CurrSvcIsSupPosRspBitSet == (uint8_t)FALSE)
				{/* SuppressPositiveResponseBit == 0 */
					lub_IsAllowedToSendPosRsp = (uint8_t)TRUE;
				}
				else
				{/* SuppressPositiveResponseBit == 1 */
					if ( Uds_generic_chkPendingNeededForSvc(pAPduResp->CurrIncomDiagReqSid) )
					{
						lub_IsAllowedToSendPosRsp = (uint8_t)TRUE;
					}
					else
					{
						/* Do not send back the positive response in this case */
					}
				}
			}
			else
			{/* Functional addressing */
				if (pAPduResp->CurrSvcIsSupPosRspBitSet == (uint8_t)FALSE)
				{/* SuppressPositiveResponseBit == 0 */
					lub_IsAllowedToSendPosRsp = (uint8_t)TRUE;
				}
				else /* if (pAPduResp->CurrSvcIsSupPosRspBitSet == (uint8_t)TRUE) */
				{/* SuppressPositiveResponseBit == 1 */
				   if (Uds_generic_chkPendingNeededForSvc(pAPduResp->CurrIncomDiagReqSid))
				   {
						lub_IsAllowedToSendPosRsp = (uint8_t)TRUE;
				   }
				   else
				   {
						/* Do not send back the positive response in this case */
				   }
				}
			} /* end of if(TARGETADDR_PHYSICAL == FBLUDS_ITF_EXP_GET_RX_TA_TYPE()) */
		}
		else
		{/* if (pAPduResp->CurrSvcHavSubFunc == (uint8_t)FALSE) */
			lub_IsAllowedToSendPosRsp = (uint8_t)TRUE;
		} /* end of if (pAPduResp->CurrSvcHavSubFunc == (uint8_t)TRUE) */

		if (lub_IsAllowedToSendPosRsp == (uint8_t)TRUE)
		{
			// pAPduResp->pduData[0x00u] += UDS_C_SVC_POS_RSP_SID_OFFSET;
			pAPduResp->pduData[0x00u]  = pAPduResp->CurrIncomDiagReqSid  + UDS_C_SVC_POS_RSP_SID_OFFSET;
			// Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_RESP_AVAILABLE);
			
			// Start Send
			FBLUDS_ITF_IMP_N_USDATA_REQUEST(&(pAPduResp->pduData[0x00u]), 
                            	            pAPduResp->msgLength);
			//FblTp_N_USData_request(&(pAPduResp->pduData[0x00u]), 
            //                	            pAPduResp->msgLength);

		}
		else
		{
			// Uds_SesnMgr_UpdateServiceRespState(UDS_SERVICE_NO_RESPONSE);
		}
	} /* end of else if(lub_error == UDS_POSITIVE_RESPONSE) */

	return;
} /* end of Uds_generic_SendResp() */



/**
 * This function is the general entry point for a UDS service handler.
 * - It checks whether previous service finished.
 * - Perform service handling by call corresponding handler for each UDS service.
 * - Perform post-processing according to response code by calling Uds_generic_SendResp().
 *
 * \param [in] pAPduInd				The container of service indication data buffer.
 * \param [in] pAPduResp			The container of service response data buffer.
 * \param [in] pFnc_UdsSvcSpecProc	UDS service handler function pointer.
 *
 */
static void UDS_FN_TYPE Uds_generic_ServiceCommonProcess(
		                      Uds_APduData_t* 			  pAPduInd, 
		                      Uds_APduData_t* 			  pAPduResp,
                              T_FUNC_PTR_UDS_SVC_HANDLER  pFnc_UdsSvcSpecProc
)
{
    //uint8_t i;
    Uint16 i;
	Std_UdsReturnType lub_error = UDS_POSITIVE_RESPONSE;

	/* Call the reserved the indication interface to notify diag Req CAN msg is received. */
	UDS_APP_ITF_EXP_REQ_CAN_FRAME_IND;

	if ( Uds_generic_IsAPrevReqAlreadyRunning(pAPduInd->pduData[0x00u]) )
	{/* Previously received UDS service still under processing. */
		lub_error = UDS_NRC_BUSYREPEATREQUEST; 
	}
	else
	{/* Previously received UDS service finished. */
		/* Transfer the request message from diagnostic protocol to applicaton buffer. */
		lub_error = Uds_generic_RcvAndSaveDiagReqMsg( pAPduInd, pAPduResp ); 
		if ( lub_error == UDS_POSITIVE_RESPONSE )
		{
			if (CurRxUdsMsgBuf == 0u) {
				if (TARGETADDR_PHYSICAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
					PreRxUdsMsgBuf0[0u] = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
				}
				else {
					PreRxUdsMsgBuf0[0u] = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
				}
				if (pAPduInd->msgLength > 8u) {
					PreRxUdsMsgBuf0[1u] = 8u;
				}
				else {
					PreRxUdsMsgBuf0[1u] = pAPduInd->msgLength;
				}
				for (i = 0u; i < PreRxUdsMsgBuf0[1u]; i++) {
					PreRxUdsMsgBuf0[i+2u] = pAPduInd->pduData[i];
				}
				CurRxUdsMsgBuf++;
			}
			else if (CurRxUdsMsgBuf == 1u) {
				if (TARGETADDR_PHYSICAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
					PreRxUdsMsgBuf1[0u] = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
				}
				else {
					PreRxUdsMsgBuf1[0u] = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
				}
				if (pAPduInd->msgLength > 8u) {
					PreRxUdsMsgBuf1[1u] = 8u;
				}
				else {
					PreRxUdsMsgBuf1[1u] = pAPduInd->msgLength;
				}
				for (i = 0u; i < PreRxUdsMsgBuf1[1u]; i++) {
					PreRxUdsMsgBuf1[i+2u] = pAPduInd->pduData[i];
				}
				CurRxUdsMsgBuf++;
			}
			else if (CurRxUdsMsgBuf == 2u){
				if (TARGETADDR_PHYSICAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
					PreRxUdsMsgBuf2[0u] = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
				}
				else {
					PreRxUdsMsgBuf2[0u] = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
				}
				if (pAPduInd->msgLength > 8u) {
					PreRxUdsMsgBuf2[1u] = 8u;
				}
				else {
					PreRxUdsMsgBuf2[1u] = pAPduInd->msgLength;
				}
				for (i = 0u; i < PreRxUdsMsgBuf2[1u]; i++) {
					PreRxUdsMsgBuf2[i+2u] = pAPduInd->pduData[i];
				}
				CurRxUdsMsgBuf++;
			}
			else if (CurRxUdsMsgBuf == 3u) {
				if (TARGETADDR_PHYSICAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
					PreRxUdsMsgBuf3[0u] = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
				}
				else {
					PreRxUdsMsgBuf3[0u] = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
				}
				if (pAPduInd->msgLength > 8u) {
					PreRxUdsMsgBuf3[1u] = 8u;
				}
				else {
					PreRxUdsMsgBuf3[1u] = pAPduInd->msgLength;
				}
				for (i = 0u; i < PreRxUdsMsgBuf3[1u]; i++) {
					PreRxUdsMsgBuf3[i+2u] = pAPduInd->pduData[i];
				}
				CurRxUdsMsgBuf++;
			}
			else {
				for (i = 0u; i < 10u; i++) {
					PreRxUdsMsgBuf0[i] = PreRxUdsMsgBuf1[i];
				}
				
				for (i = 0u; i < 10u; i++) {
					PreRxUdsMsgBuf1[i] = PreRxUdsMsgBuf2[i];
				}
				
				for (i = 0u; i < 10u; i++) {
					PreRxUdsMsgBuf2[i] = PreRxUdsMsgBuf3[i];
				}
				
				if (TARGETADDR_PHYSICAL == UDS_APP_ITF_IMP_GET_TP_CHNL()) {
					PreRxUdsMsgBuf3[0u] = CANDRV_C_RX_PHY_ADDR_STD_CANMSGID;
				}
				else {
					PreRxUdsMsgBuf3[0u] = CANDRV_C_RX_FUNC_ADDR_STD_CANMSGID;
				}
				if (pAPduInd->msgLength > 8u) {
					PreRxUdsMsgBuf3[1u] = 8u;
				}
				else {
					PreRxUdsMsgBuf3[1u] = pAPduInd->msgLength;
				}
				for (i = 0u; i < PreRxUdsMsgBuf3[1u]; i++) {
					PreRxUdsMsgBuf3[i+2u] = pAPduInd->pduData[i];
				}
			}

			/* After the generic common checking is finished, call the each service special
			* process to handle the request. */
			lub_error = (*pFnc_UdsSvcSpecProc)(pAPduInd, pAPduResp);

			/* check if UDS service processing goes to pending state which means service processing
			* will be finished asynchronously, and final service response(if required)will be generated
			* when finished. */
			if ( lub_error == UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING )
			{
				Uds_Service_Pending_StateManager( UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING );
			}
			else
			{
			}
		}
		else 
		{

		}
	} /* end of else if (!Uds_generic_IsAPrevReqAlreadyRunning(pAPduInd->pduData[0x00u])) */

	Uds_generic_SendResp(pAPduResp, lub_error);

	return;
} /* end of  Uds_generic_ServiceCommonProcess() */


Uds_SessionLevel_t UDS_FN_TYPE FblUds_SimpleSesnMgr_GetActiveSession( void )
{
   Uds_SessionLevel_t	  sessionLevel;
   
   FBLUDS_DISABLE_ALL_INTERRUPTS();
       sessionLevel = rub_FblUds_SimpleSesnMgr_CurrActiveSession;
   FBLUDS_ENABLE_ALL_INTERRUPTS();
   
   return ( sessionLevel );
}


uint8_t FblUds_SimpleSesnMgr_SetActiveSession( const uint8_t sessionLevel )
{
	
   FBLUDS_DISABLE_ALL_INTERRUPTS();
       rub_FblUds_SimpleSesnMgr_CurrActiveSession = sessionLevel; 	
   FBLUDS_ENABLE_ALL_INTERRUPTS();	
   return TRUE;
}

uint8_t FblUds_SimpleSesnMgr_ChkSesnChangePreCndIsAllow(
      uint8_t i_CurrSession,
      uint8_t i_DestSession) 
{
	if(i_DestSession == UDS_PROGRAMMING_SESSION)
		return CheckProgramCondition();
	else
		return (uint8_t)TRUE;
}



static void FblUds_SimpleSesnMngr_CyclicTskEntryPoint( void ) 
{
    // to decrement S3_Server_Timer safely. 
    FblUds_SimpleSesnMgr_TickS3ServerTimerValue(); 
       if (rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr > 0x00000001u ) 
       {
           FBLUDS_DISABLE_ALL_INTERRUPTS();    
           rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr--;
           FBLUDS_ENABLE_ALL_INTERRUPTS();  
     
       } 
       else  if (rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr == 0x00000001u ) 
       {
           FBLUDS_DISABLE_ALL_INTERRUPTS();    
           rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr--;
           FBLUDS_ENABLE_ALL_INTERRUPTS();
		   #ifdef SFBL_APP_SW_BUILD
    	       UDS_APP_ITF_IMP_SET_ECURST_HARD_RESET();
    	   #endif 
       }
	else
	{
	}
	
}

uint8_t FblUds_SimpleSesnMgr_ChangeSession(uint8_t i_DestSession) 
{


  uint8_t lub_Result = (uint8_t)TRUE; // FALSE;
  
  FBLUDS_DISABLE_ALL_INTERRUPTS();

  /*Found, set the current session index and return OK*/
  FblUds_SimpleSesnMgr_SetActiveSession(i_DestSession); 
  
  if (i_DestSession != UDS_DEFAULT_SESSION)
  {
      FblUds_SimpleSesnMgr_SetS3ServerTimerValue(SESSION_TIMING_S3SERVER); 
  }
  else
  {
	    /* reset S3_Server timer */
	    FblUds_SimpleSesnMgr_SetS3ServerTimerValue(0x00000000u);
  }
  FBLUDS_ENABLE_ALL_INTERRUPTS();
  
  if (i_DestSession == UDS_PROGRAMMING_SESSION)
  {
      #ifdef SFBL_BOOT_SW_BUILD
          switch (FBLMGR_ITF_EXP_GET_CURR_RUN_SW_IMG_STATE())
          {
              case BOOT_SW_IN_FLASH_RUNNING:      
                   /* already in the bootSwInFlash running mode , do nothing*/ 
                   break;
      	      case BOOT_SW_IN_RAM_DOWNLOADING: 
      	           /* already in the BootSwInRam Downloading mode , do nothing */
      	           break;
      	      case BOOT_SW_IN_RAM_RUNNING: 
       	           /* already in the BootSwInRam running mode , do nothing */
      	           break;
      	      case APP_SW_IN_FLASH_DOWNLOADING: 
       	           /* already in the AppSwInFlash downloading mode , do nothing */
      	           break;
      	      case APP_SW_IN_FLASH_RUNNING: 
       	           /* already in the AppSwInFlash running mode , do nothing */     	        
                   lub_Result =  FblMgr_SetBootModeAswModeToggleFlg();
                   FblMgr_ToggleFromAppSwModeToBootSwMode();
                   break;
              /* all of other situations are not supported , do nothing */     
              default: 
                   break;     
          }
      #endif
      
      
      #ifdef SFBL_APP_SW_BUILD
          lub_Result = FBLMGR_ITF_EXP_SET_REPROGFLG_FRM_ASW(); 
          if (lub_Result == TRUE)
          {
              /* to trigger a hard reset ,after reset, 
			     will switch from app sw to boot sw 
			   */ 
              // UDS_APP_ITF_IMP_SET_ECURST_HARD_RESET	();
              UDS_DISABLE_ALL_INTERRUPTS();
                    rul_FblUds_SimpleSesnMngr_ProgSesnResetTmr = UDS_C_ECURESET_POWER_DOWN_REL_TIME;
              UDS_ENABLE_ALL_INTERRUPTS();

          }
          else
          {
          }        
      #endif	  
      
	  
  }
  else
  {

  }
  return lub_Result;
}

void FblUds_SimpleSesnMgr_Reload_S3_SeverTimer(void) 
{
     FblUds_SimpleSesnMgr_SetS3ServerTimerValue(SESSION_TIMING_S3SERVER); 
}


void FblUds_SimpleSesnMgr_SetS3ServerTimerValue(uint32_t i_NewValue) 
{
   FBLUDS_DISABLE_ALL_INTERRUPTS(); 
   rul_FblUds_SimpleSesnMngr_S3_SeverTmr = i_NewValue;
   FBLUDS_ENABLE_ALL_INTERRUPTS();  
}

static void FblUds_SimpleSesnMgr_TickS3ServerTimerValue(void) 
{
   if (FblUds_SimpleSesnMgr_GetActiveSession() != UDS_DEFAULT_SESSION) 
   {
    
       if (rul_FblUds_SimpleSesnMngr_S3_SeverTmr > 0x00000001u ) 
       {
           FBLUDS_DISABLE_ALL_INTERRUPTS();    
           rul_FblUds_SimpleSesnMngr_S3_SeverTmr--;
           FBLUDS_ENABLE_ALL_INTERRUPTS();  
     
       } 
       else  if (rul_FblUds_SimpleSesnMngr_S3_SeverTmr == 0x00000001u ) 
       {
           FBLUDS_DISABLE_ALL_INTERRUPTS();    
           rul_FblUds_SimpleSesnMngr_S3_SeverTmr--;
           FBLUDS_ENABLE_ALL_INTERRUPTS();  
           
           
           /*back into default session*/
           FblUds_SimpleSesnMgr_SetActiveSession(UDS_DEFAULT_SESSION);
            
           /* notify uds application (services) layer that the S3_Server_Timer timeout occured
            */
           UDS_SESN_MGR_ITF_IMP_CB_FUNC_S3_SVR_TMR_TO_NOTIFY();
     
       }
   } 
   else 
   {
    
   }
}

void Uds_Get_2ndIndRespBufPtrSet(Uds_APduData_t* o_Ind2ndPtr, 
                                 Uds_APduData_t* o_Resp2ndPtr)
{
   o_Ind2ndPtr  =  pul_FblUds_APduDataIndPtr;
   o_Resp2ndPtr =   pul_FblUds_APduDataRespPtr;
}

#ifdef __cplusplus
extern "C" {
#endif





/********************************************************************************
*								end of file										*
********************************************************************************/
