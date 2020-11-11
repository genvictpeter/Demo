/****************************************************************************
 	@Module       
 	@Filename      uds_srv31_routinecontrol.c
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
#include "uds_confpriv.h"
#include "uds_confdefs.h"
#include "uds_pub.h"
#include "uds_priv.h"
#include "uds_inf.h"
#include "FlashDrv_ExtItf.h"
#include "FblMgr.h"



#ifdef UDS_ENABLE_ROUTINECONTROL

/* no Sun-Function parameter for this service */

/* NRC for ReadDataByIdentifier
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 * 	0x31	UDS_NRC_REQUESTOUTOFRANGE
 *	0x33	UDS_NRC_SECUTITYACCESSDENIED
 */

uint8_t  rub_Rtype;
uint8_t  rub_number;
uint8_t  rub_routineNb;
uint8_t  rub_dirout_pending;
/* uint8_t *pDIA_BUFF_Saved; */
uint8_t  rub_diaSelfTestMode;

uint16_t  ruw_routineID ;
uint32_t  rul_Dirout_WaitFinishTmr; // = 0xFFFFFFFFu;
uint8_t   rub_SavedRtnCtrlSubFunc; // = 0x00u;

Uint16 CheckedPreprogConditonFlg;


extern Uds_APduData_t*  pul_FblUds_APduDataRespPtr;



static Std_UdsReturnType  UdsApp_31RtnCtrl_MainControlProc(uint8_t         lub_mode,
	                                                       Uds_APduData_t* pAPduInd, 
                                                           Uds_APduData_t* pAPduResp);

static Std_UdsReturnType  UdsApp_31RtnCtrl_FsmEventHandler(uint8_t         lub_routinePos,   /* position in table */
                                                           uint8_t         leV_now,	 /* event occured     */
                                                           Uds_APduData_t* pAPduInd, 
                                                           Uds_APduData_t* pAPduResp); // diag routine control opt buffer.

static void Start0203(void);

Std_UdsReturnType UDS_FN_TYPE UdsApp_RoutineControl(Uds_APduData_t* pAPduInd, 
                                                    Uds_APduData_t* pAPduResp )
{

   uint8_t lub_error = UDS_POSITIVE_RESPONSE;

   if (TARGETADDR_FUNCTIONAL == UDS_APP_ITF_IMP_GET_TP_CHNL())
   {
       lub_error = UDS_NRC_SERVICENOTSUPPORTED;
   }
   #if 1
   else if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION)
   {
       lub_error = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
   }
   #endif
   else if (pAPduInd->msgLength < 0x04u)
   {
       lub_error = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
   else
   {

     rub_SavedRtnCtrlSubFunc = ((pAPduInd->pduData[0x01u]) & 0x7Fu);
     switch (((pAPduInd->pduData[0x01u]) & 0x7Fu))
     {
       default :
            lub_error = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
            break;
		   
       case ROUTINECTRL_START_ROUTINE:
            lub_error = UdsApp_31RtnCtrl_MainControlProc(ROUTINECTRL_START_ROUTINE, pAPduInd,pAPduResp);
            break;
		   
       case ROUTINECTRL_STOP_ROUTINE:
            lub_error = UdsApp_31RtnCtrl_MainControlProc(ROUTINECTRL_STOP_ROUTINE, pAPduInd,pAPduResp);
            break;
		   
       case ROUTINECTRL_REQ_ROUTINERESULT:
            lub_error = UdsApp_31RtnCtrl_MainControlProc(ROUTINECTRL_REQ_ROUTINERESULT, pAPduInd,pAPduResp);
            break;
     } /* end of switch (((pAPduInd->pduData[0x01u]) & 0x7Fu))()  */
   }
   return lub_error;  
} /* end of UdsApp_RoutineControl() */



static Std_UdsReturnType  UdsApp_31RtnCtrl_MainControlProc(uint8_t         lub_mode,
	                                                       Uds_APduData_t* pAPduInd, 
                                                           Uds_APduData_t* pAPduResp)
{
   /* routine local identifier look-up */
   uint8_t  lub_RoutineNb;
   /* uint8_t  lub_ODREAD_NbDTCs ; */
   /* uint32_t lul_aDTC ; */
   uint8_t  lub_response  = UDS_POSITIVE_RESPONSE;
   uint16_t luw_routineId2Search = 0x0000u;
   uint8_t    lub_CurrActiveSession = UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION();
 
   luw_routineId2Search  = (uint16_t)(pAPduInd->pduData[0x02u] << 0x08u);
   luw_routineId2Search |= (uint16_t)(pAPduInd->pduData[0x03u]);
   
   if(luw_routineId2Search == 0x0203)
   {
        Start0203();
		
   		lub_response = UDS_POSITIVE_RESPONSE;
			pAPduResp->msgLength = 0x04u; 
			pAPduResp->pduData[0x01u] = pAPduInd->pduData[0x01u];
			pAPduResp->pduData[0x02u] = pAPduInd->pduData[0x02u];
			pAPduResp->pduData[0x03u] = pAPduInd->pduData[0x03u];
			pAPduResp->pduData[0x04u] = pAPduInd->pduData[0x04u];
		return lub_response;
   }
   
 
   lub_RoutineNb = Uds_Generic_DatMgr_SearchTblByKey(luw_routineId2Search, 
                                                     KeyTypeIsUINT16, 
	                                                 (uint8_t *)&(Uds_g_RtnCtrlMngtDataTable[0x00u].routineIdentifier),
							                         sizeof(Uds_g_RtnCtrlMngtDataTable[0x00u]));
   /* is routine supported */
   if (lub_RoutineNb == UDS_C_IDX_NOT_IN_TBL  )
   {
       /* requested routine is not supported */
       /* send negative response */
       lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response;
   }
   else
   {
   }
   
   /* save the current RoutineNb. */
   rub_routineNb = lub_RoutineNb;

   if (((Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].AccessAttribute)  & (UDS_C_RID_ATR_ENA_RUN)) != UDS_C_RID_ATR_ENA_RUN)
   {
       lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response ;
   }
   else
   {
   }

   if ((((Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].AccessAttribute)  & (UDS_C_RID_ATR_SESN_EXTD)) == UDS_C_RID_ATR_SESN_EXTD) &&
       (lub_CurrActiveSession !=  UDS_EXTENDED_DIAGNOSTIC_SESSION) &&
       (lub_CurrActiveSession !=  UDS_ECU_SUPPLIER_SPEC_SESSION)  &&
       (lub_CurrActiveSession !=  UDS_PROGRAMMING_SESSION)        
      )
   {
       lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response ;
   }
   else
   {
   }

   if (( (((Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].AccessAttribute) & UDS_C_RID_ATR_SECU_LVL_11) == UDS_C_RID_ATR_SECU_LVL_11) &&
         (!UdsApp_27SecuAcc_IsSpecifiedSALHasUnlocked(UDS_C_SECU_ACC_SECU_LEVEL11))
       ) )
   {
       lub_response = UDS_NRC_SECUTITYACCESSDENIED;
       return lub_response;
   }
   else
   {
   }

   #if 1
   if ( (((pAPduInd->pduData[0x01u]) & 0x7Fu) == ROUTINECTRL_START_ROUTINE) &&
        (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrStart == NULL)
      )
   {
       lub_response = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
       return  lub_response;
   }
   else
   {
   }
   #endif

   if ( (((pAPduInd->pduData[0x01u]) & 0x7Fu) == ROUTINECTRL_STOP_ROUTINE) &&
        (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrStop  == NULL)
       )
   {
       lub_response = UDS_NRC_SUBFUNCTIONNOTSUPPORTED;
       return  lub_response;
   }
   else
   {
   }

   if  (((pAPduInd->pduData[0x01u] & 0x7Fu) == ROUTINECTRL_START_ROUTINE)  &&
         (pAPduInd->msgLength != Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].ValidArgumentNum))
   {
       lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
       return  lub_response;
   }
   else if (( (pAPduInd->pduData[0x01u] & 0x7Fu) == ROUTINECTRL_REQ_ROUTINERESULT  ||
               (pAPduInd->pduData[0x01u] & 0x7Fu) == ROUTINECTRL_STOP_ROUTINE 
            ) &&
            (pAPduInd->msgLength != 0x04u))
   {
       lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
       return  lub_response;
   }
   else
   {

   }

   if (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrRtnCheck != NULL)
   {
       lub_response = (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrRtnCheck)(&(pAPduInd->pduData[0x04u]));
       if (lub_response != UDS_POSITIVE_RESPONSE)
       {
           return lub_response;
       }
       else
       {
       }
   }
   else
   {
   }
 
   /* save the current RoutineNb. */
   /* rub_routineNb = lub_RoutineNb; */
   
   pAPduResp->msgLength = 0x04u; 
   
   switch (lub_mode)
   {
	   default :
		    /* ilegal calling of the service */
			lub_response = UDS_NRC_GENERALREJECT ;
		    break ;
		    
	   case ROUTINECTRL_START_ROUTINE :
		    lub_response = UdsApp_31RtnCtrl_FsmEventHandler(lub_RoutineNb, 
		                                                    UDS_C_RTNCTRL_EV_start, 
		                                                    pAPduInd, 
		                                                    pAPduResp);
			break ;
			
	   case ROUTINECTRL_STOP_ROUTINE :
	        lub_response = UdsApp_31RtnCtrl_FsmEventHandler(lub_RoutineNb, 
		                                                    UDS_C_RTNCTRL_EV_stop,
		                                                    pAPduInd, 
		                                                    pAPduResp);
			break ;

	   case ROUTINECTRL_REQ_ROUTINERESULT :
	        lub_response = UdsApp_31RtnCtrl_FsmEventHandler(lub_RoutineNb, 
			                                                UDS_C_RTNCTRL_EV_results,
			                                                pAPduInd, 
			                                                pAPduResp);
            if (lub_response == UDS_POSITIVE_RESPONSE)
            {   
		        pAPduResp->pduData[0x04u] = UdsApp_31RtnCtrl_FsmEventHandler(lub_RoutineNb, 
		                                                                     UDS_C_RTNCTRL_EV_status, 
		                                                                     pAPduInd, 
		                                                                     pAPduResp);
                pAPduResp->msgLength++;

                if (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrGetResult == NULL)
                {
                } 
                else /*  if (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrGetResult != NULL)  */
                {
                    if (UDS_C_RTNCTRL_FSMST_RUNNING != rub_diaSelfTestMode )
                    {
                        pAPduResp->pduData[pAPduResp->msgLength] = (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrGetResult)();
                        pAPduResp->msgLength++;
                    }
                    else
                    {
                    }
                } /* end of else of if  (Uds_g_RtnCtrlMngtDataTable[lub_RoutineNb].pFuncPtrGetResult != NULL) */
             } /* end of if (lub_response == UDS_POSITIVE_RESPONSE) */
             else
             {
             } /* end of else of if (lub_response == UDS_POSITIVE_RESPONSE) */
	         break ;
   } /* end of switch (lub_mode) */

   return lub_response;
} /* end of UdsApp_31RtnCtrl_MainControlProc()  */


void UdsApp_31RtnCtrl_Init(void)
{
   /* default state = no routine running */
   rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_NO_REQUEST;
   /* default routine = no routine performed */
   ruw_routineID = 0x0000u;
   rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu;
   rub_routineNb = 0x00u;
   rub_dirout_pending = FALSE;

   rub_SavedRtnCtrlSubFunc = 0x00u;

   CheckedPreprogConditonFlg = 0u;
}

static Std_UdsReturnType  UdsApp_31RtnCtrl_FsmEventHandler(uint8_t         lub_routinePos,   /* position in table */
                                                           uint8_t         leV_now,	 /* event occured     */
                                                           Uds_APduData_t* pAPduInd, 
                                                           Uds_APduData_t* pAPduResp) /* diag routine control opt buffer. */
{
   uint8_t  lub_return;
   uint8_t  lub_tmpRtnResult;
   
   lub_return = UDS_POSITIVE_RESPONSE;
   /* to remove the warning : unused parameter pAPduResp
    */
   pAPduResp = pAPduResp;

   switch (leV_now)
   {
	   default :
			/* this is an unknown event   */
			/* possible an ilegal calling */
			/* a reinitialization is mandatory */
		    UdsApp_31RtnCtrl_Init();			
		    break;
            
	   case UDS_C_RTNCTRL_EV_start :
			if (UDS_C_RTNCTRL_FSMST_RUNNING != rub_diaSelfTestMode)
			{   
				if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStart != NULL)
				{   
		            /* clear results of previous routines */
					lub_tmpRtnResult = Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStart(&(pAPduInd->pduData[0x04u]));
					if (lub_tmpRtnResult != FALSE )
					{   
						/* routine was trigered succesfully */
						rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_RUNNING ;
						ruw_routineID = Uds_g_RtnCtrlMngtDataTable[lub_routinePos].routineIdentifier ;
						lub_return =          UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING; //UDS_POSITIVE_RESPONSE;
                        rub_dirout_pending = TRUE;
                        // to start the routine run limit timer if it is a valid value
                        if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].RtnRunLimitTime > 0x00000000u &&
                            Uds_g_RtnCtrlMngtDataTable[lub_routinePos].RtnRunLimitTime < 0xFFFFFFFFu 	 )
                        {
                            rul_Dirout_WaitFinishTmr = Uds_g_RtnCtrlMngtDataTable[lub_routinePos].RtnRunLimitTime;
                        }
                        else
                        {
                        }
					}   
					else
					{   
                        /* default state = no routine running */
		                rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_NO_REQUEST;
                        ruw_routineID = 0x0000u; 
                        rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu;
                        rub_routineNb = 0x00u;
                        rub_dirout_pending = FALSE;
						lub_return = UDS_NRC_CONDITIONSNOTCORRECT ;
					}
				} /* end of if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStart != NULL) */
				else /* if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStart == NULL) */
				{
                    /* default state = no routine running */
		            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_NO_REQUEST;
                    ruw_routineID = 0x0000u;
                    rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu;
                    rub_routineNb = 0x00u;
                    rub_dirout_pending = FALSE;
					/* null pointer found */
					lub_return = UDS_NRC_REQUESTOUTOFRANGE;
				}
			} /* end of if (UDS_C_RTNCTRL_FSMST_RUNNING != rub_diaSelfTestMode) */
			else
			{
				/* a routine is now running */
				lub_return = UDS_NRC_BUSYREPEATREQUEST; //UDS_NRC_CONDITIONSNOTCORRECT ;
			}
		    break ;
	   case UDS_C_RTNCTRL_EV_stop :
	                      /* test routine execution state */
   			if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStop == NULL)
            {
				/* null pointer found */
				lub_return = UDS_NRC_REQUESTOUTOFRANGE;
            }
            else if (UDS_C_RTNCTRL_FSMST_RUNNING != rub_diaSelfTestMode )
	        {
	            /* there is no routine currently running */
	            /* send negative response */
	            lub_return = UDS_NRC_REQUESTSEQUENCEERROR; //UDS_NRC_CONDITIONSNOTCORRECT;
	        }
	        else if (ruw_routineID != Uds_g_RtnCtrlMngtDataTable[lub_routinePos].routineIdentifier )
	        {
	            /* the requested routine was not started */
	            /* prepare negative response */
	            lub_return = UDS_NRC_REQUESTSEQUENCEERROR; //UDS_NRC_CONDITIONSNOTCORRECT;
	        }
        	else // if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStop != NULL)
			{
				Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrStop();
				/* routine was stoped succesfully */
				rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_ABORTED ;
				lub_return = UDS_POSITIVE_RESPONSE ;
                rub_dirout_pending = FALSE;
                rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu;
			}
		    break ;
		    
	   case UDS_C_RTNCTRL_EV_results:
	        /* test routine execution state */
	        if (UDS_C_RTNCTRL_FSMST_NO_REQUEST == rub_diaSelfTestMode )
	        {
	            /* no routine was performed */
	            /* send negative response */
	            lub_return = UDS_NRC_REQUESTSEQUENCEERROR;
	        }
	        else if ( ruw_routineID != Uds_g_RtnCtrlMngtDataTable[lub_routinePos].routineIdentifier )
	        {
	            /* the requested routine was not started */
	            /* prepare negative response */
	            lub_return = UDS_NRC_REQUESTSEQUENCEERROR;
	        }
	        else if (UDS_C_RTNCTRL_FSMST_RUNNING      == rub_diaSelfTestMode ||
                     UDS_C_RTNCTRL_FSMST_CMPLT_PASSED == rub_diaSelfTestMode ||
                     UDS_C_RTNCTRL_FSMST_CMPLT_FAILED == rub_diaSelfTestMode ||
                     UDS_C_RTNCTRL_FSMST_ABORTED      == rub_diaSelfTestMode)
	        {
	            /* a routine is currently executing */
	            /* send positive response */
	            lub_return = UDS_POSITIVE_RESPONSE ;
	        }   
	        else
	        {   
		        lub_return = UDS_POSITIVE_RESPONSE ;
                /* rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu; */
	        }   
		    break ;
		    
	   case UDS_C_RTNCTRL_EV_status :
			if (ruw_routineID == Uds_g_RtnCtrlMngtDataTable[lub_routinePos].routineIdentifier)
			{
				lub_return = (uint8_t)rub_diaSelfTestMode ;
			}
			else
			{
			    lub_return = UDS_NRC_REQUESTSEQUENCEERROR;
			}
		    break;
		    
       case UDS_C_RTNCTRL_EV_finish :
	        /* test routine execution state */
	        if ((UDS_C_RTNCTRL_FSMST_RUNNING != rub_diaSelfTestMode) ||
	            (ruw_routineID != Uds_g_RtnCtrlMngtDataTable[lub_routinePos].routineIdentifier)
	           )
	        {
	            /* there is an error in application */
	            lub_return = UDS_NRC_REQUESTSEQUENCEERROR;
	        }
	        else /* if ((UDS_C_RTNCTRL_FSMST_RUNNING == rub_diaSelfTestMode) */
            {
                if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrGetResult != NULL)
                {
                    lub_tmpRtnResult = (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrGetResult)();

                    if (((uint8_t)0x80u) & (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].ExpectedPosResult))
                    {
                        if (lub_tmpRtnResult == (0x7Fu & (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].ExpectedPosResult)))
                        {
                            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_CMPLT_FAILED ;
                        }
                        else
                        {
                            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_CMPLT_PASSED;
                        }
                    }
                    else
                    {
                        if (lub_tmpRtnResult == (0x7Fu & (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].ExpectedPosResult)))
                        {
                            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_CMPLT_PASSED;
                        }
                        else
                        {
                            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_CMPLT_FAILED ;
                        }
                    }

		            lub_return = UDS_POSITIVE_RESPONSE ;
                    rub_dirout_pending = FALSE;
                } /* end off if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrGetResult != NULL) */
                else /* if (Uds_g_RtnCtrlMngtDataTable[lub_routinePos].pFuncPtrGetResult == NULL) */
                {
			        
		            rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_CMPLT_PASSED	 ;
			        lub_return = UDS_POSITIVE_RESPONSE ;
                    rub_dirout_pending = FALSE;			        
                }
                rul_Dirout_WaitFinishTmr = 0xFFFFFFFFu;
            } /* end of else if ((UDS_C_RTNCTRL_FSMST_RUNNING == rub_diaSelfTestMode)  */
	    	break;
   } /* end of switch (leV_now)  */
   return (lub_return);
} /* end of UdsApp_31RtnCtrl_FsmEventHandler()  */


/******************************************************************************
 * Name: UdsApp_31RtnCtrl_S3TmrTOHandler
 * Description: Resets the service routine if tester present times out.
 ******************************************************************************/
void  UdsApp_31RtnCtrl_S3TmrTOHandler(void)
{
   uint8_t lub_RtnFsmEvtHandlerResult;
   Uds_APduData_t* p_lul_APduInd2ndPtr = NULL; 
   Uds_APduData_t* p_lul_APduResp2ndPtr = NULL; 
	
   Uds_Get_2ndIndRespBufPtrSet(p_lul_APduInd2ndPtr, 
                               p_lul_APduResp2ndPtr);
   
   lub_RtnFsmEvtHandlerResult = UdsApp_31RtnCtrl_FsmEventHandler(rub_routineNb,
 		                                                         UDS_C_RTNCTRL_EV_status,
		                                                         p_lul_APduInd2ndPtr,
		                                                         p_lul_APduResp2ndPtr) ; 
   if (lub_RtnFsmEvtHandlerResult == UDS_C_RTNCTRL_FSMST_RUNNING)
   {
       UdsApp_31RtnCtrl_FsmEventHandler(rub_routineNb,
	                                    UDS_C_RTNCTRL_EV_stop, 
	                                    p_lul_APduInd2ndPtr,
	                                    p_lul_APduResp2ndPtr);
   }
   else 
   {
	   /* nothing to do */
   }

   UdsApp_31RtnCtrl_Init();
}/* end of UdsApp_31RtnCtrl_S3TmrTOHandler */

/******************************************************************************
 * Name: dirout_pending
 * Description: Pending task in order to check if self test routine finished its task
 * Parameter:   None
 * Return: 		error code
 * Critical:    No.
 * Explanation: Periodicaly called in 80ms task.
 ******************************************************************************/
uint8_t UdsApp_31RtnCtrl_pending(void)
{
   uint8_t         lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
   /* uint8_t         lub_routine_status = UDS_C_RTNCTRL_FSMST_NO_REQUEST; */
   uint8_t         lub_routine_is_finished = FALSE;
   Uds_APduData_t* p_lul_APduInd2ndPtr = NULL; 
   Uds_APduData_t* p_lul_APduResp2ndPtr = NULL; 
	
   Uds_Get_2ndIndRespBufPtrSet(p_lul_APduInd2ndPtr, 
                                  p_lul_APduResp2ndPtr);

   // lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
   // lub_routine_status = UDS_C_RTNCTRL_FSMST_NO_REQUEST;
   // lub_routine_is_finished = FALSE;


   if (rub_dirout_pending == TRUE )
   {
       if (rul_Dirout_WaitFinishTmr != 0xFFFFFFFFu &&
           rul_Dirout_WaitFinishTmr > 0x00000000u)
       {
           rul_Dirout_WaitFinishTmr--;
       }
       else
       {
       }

       /* to make sure , the routine at least to run for 100ms 
	    */
	   /*  
       if (rul_Dirout_WaitFinishTmr >= (Uds_g_RtnCtrlMngtDataTable[rub_routineNb].RtnRunLimitTime - 
	   	                                                 UDS_C_RID_RUN_TIM_MIN))
       {
           return lub_response;
       }
	   else
	   {
	   }
       */

       if (rul_Dirout_WaitFinishTmr == 0x00000000u)
       {
           UdsApp_31RtnCtrl_FsmEventHandler(rub_routineNb,
	                                                       UDS_C_RTNCTRL_EV_stop, 
	                                                       p_lul_APduInd2ndPtr,
	                                                       p_lul_APduResp2ndPtr);
           rub_diaSelfTestMode = UDS_C_RTNCTRL_FSMST_ABORTED;
           lub_response = UDS_NRC_GENERALREJECT;
           rub_dirout_pending = FALSE;
       }
       else /* if (rul_Dirout_WaitFinishTmr != 0x00000000u)*/
       {

           UdsApp_31RtnCtrl_FsmEventHandler(rub_routineNb,
		                                    UDS_C_RTNCTRL_EV_status,
		                                    p_lul_APduInd2ndPtr,
		                                    p_lul_APduResp2ndPtr);

           if ((Uds_g_RtnCtrlMngtDataTable[rub_routineNb].pFuncPtrIsRtnFinished) != NULL)
           {
               lub_routine_is_finished = (Uds_g_RtnCtrlMngtDataTable[rub_routineNb].pFuncPtrIsRtnFinished)();

               if (/* lub_routine_status == UDS_C_RTNCTRL_FSMST_RUNNING && */
                   lub_routine_is_finished == TRUE)
               {
                   UdsApp_31RtnCtrl_FsmEventHandler(rub_routineNb,
				                                    UDS_C_RTNCTRL_EV_finish, 
			                                        p_lul_APduInd2ndPtr,
		                                            p_lul_APduResp2ndPtr);
		           /* set the positive response message length */		   
			       pul_FblUds_APduDataRespPtr->msgLength      = 0x04u;
			       pul_FblUds_APduDataRespPtr->pduData[0x00u] = 0x31u; 
			       pul_FblUds_APduDataRespPtr->pduData[0x01u] = rub_SavedRtnCtrlSubFunc;  
			         
			       pul_FblUds_APduDataRespPtr->pduData[0x02u] = (uint8_t)((uint8_t)(ruw_routineID >>  0x08u) & 0xFFu);  
			       pul_FblUds_APduDataRespPtr->pduData[0x03u] = (uint8_t)((uint8_t)(ruw_routineID          ) & 0xFFu);  
			 
	               rub_dirout_pending = FALSE;
	               lub_response       = UDS_POSITIVE_RESPONSE ;
               }
               else
               {
               }
           }
           else
           {
		       /* final positive response */
		       lub_response = UDS_POSITIVE_RESPONSE ;
               /* rub_dirout_pending = (T_UBYTE)FALSE; */
           }
       } /* end of else if (rul_Dirout_WaitFinishTmr != 0x00000000u) */
   } /* end of if (rub_dirout_pending == TRUE ) */
   else
   {

   }

   return lub_response;
} /* end of UdsApp_31RtnCtrl_pending() */

void UdsApp_31RtnCtrl_pend_overtime(void)
{
   rub_dirout_pending = (uint8_t)FALSE;
} /* end of UdsApp_31RtnCtrl_pend_overtime() */

/**
 * This function is the interface to read if a routine is already running currently 
 * should be moved to the 0x31 RoutineControl service handler.
 *
 * \return
 *  - TRUE:		This routine is already running.
 *	- FALSE:	This routine is not running.
 */
uint8_t Uds_31RtnCtrl_Get_IsRoutineAlreadyRunning(void)
{
   if (rub_diaSelfTestMode == UDS_C_RTNCTRL_FSMST_RUNNING)
   {
       return (uint8_t)TRUE;
   }
   else
   {
       return (uint8_t)FALSE;
   }
} /* end of Uds_31RtnCtrl_Get_IsRoutineAlreadyRunning() */


static void Start0203(void)
{
	CheckedPreprogConditonFlg = 1u;
}

#endif /* UDS_ENABLE_ROUTINECONTROL */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
