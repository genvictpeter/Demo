
//****************************************************************************/
// @Module       
// @Filename      FblTp.c
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
//******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****/

//****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "MAIN.h"
#include "can.h"
#include "FblTp.h"
#include "FblTpExtItf.h"   /* Configuration of TP */
#include "uds_target.h"
#include "Task.h"




uint8_t  raub_TP_buffer[FBLTP_C_BUFFER_SIZE];  
//static T_FBLTP_MSG_MNGT rul_FblTp_Msg_Mngt_Dat;
T_FBLTP_MSG_MNGT rul_FblTp_Msg_Mngt_Dat;

/* static (private) functions declerations
 */
static void FblTp_CheckForEndOfTxRsp(void);
static void FblTp_CheckForRxReq(void);
static void FblTp_CheckForTimer(void);
static void FblTp_Task (void);
static void FblTp_TimerStop(void);
static void FblTp_TimerStart(uint32_t ul_Value);
static void FblTp_Return2InitStAndCallConfirm(uint8_t rub_status);
static void FblTp_Return2InitStAndCallIndication (uint16_t luw_length);


 /*********************************************************************************************
 *  Name                 : FblTp_Init
 *  Description          : initializes all configured messages 
 *                       : with their start values
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_Init(void)
{
    uint8_t i; 
    FBLTP_DISABLE_ALL_INTERRUPTS();
         rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress = FALSE;
       
        /* The boolean rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive is set to FALSE. */
        rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive = FALSE;
     
        /* The TP Timer epiration date is initialized to 0. */
        rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData = 0x00u;

        /* No message received yet ... */
       rul_FblTp_Msg_Mngt_Dat.ruw_MsgSize = 0x00u;
   
       /* No TP message sent */
       rul_FblTp_Msg_Mngt_Dat.rub_TPMessageSent = 0x00u;
    
       /* At initialization there is no timeout */
       rul_FblTp_Msg_Mngt_Dat.rub_TO_flag = 0x00u;
   
       /* Initial State of the TP is Idle */
       rul_FblTp_Msg_Mngt_Dat.TPState              = FBLTP_C_TPST_IDLE;
       /* Initialise the Block size and 
           separation Time 
         */
       rul_FblTp_Msg_Mngt_Dat.BS_Tx                = 0x00u;
       rul_FblTp_Msg_Mngt_Dat.BS_Rx                = FBLTP_C_BS_RX;
   
       /* Initialise sequence number for 
           transmission and reception 
         */
       rul_FblTp_Msg_Mngt_Dat.SN_Rx                = 0x00u;
       rul_FblTp_Msg_Mngt_Dat.SN_Tx                = 0x00u;

       /* Set the default values for BS and STmin, 
            when TP is in reception                  
         */
       rul_FblTp_Msg_Mngt_Dat.STmin_Rx             = FBLTP_C_ST_MIN_RX_US;

       /* Is nothing to send/receive */
       rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx    = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx   = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx      = 0x0000u;
   
       rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Tx      = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx   = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Tx = 0x0000u;
       rul_FblTp_Msg_Mngt_Dat.BufferIndex          = 0x0000u;

       rul_FblTp_Msg_Mngt_Dat.STmin_Tx             = 0x00000000u;

	for (i = 0x00u; i < 0x08u; i++)
	{
             rul_FblTp_Msg_Mngt_Dat.laub_CanBuffer[i] = 0x00u;  
	}
	  
       rul_FblTp_Msg_Mngt_Dat.lub_CanBufIndex = 0xFFu; 
       rul_FblTp_Msg_Mngt_Dat.lub_CanMsgCount = 0x00u;

   FBLTP_ENABLE_ALL_INTERRUPTS();
   
   /* The TP layer is initialized. */
}


/*********************************************************************************************
 *  Name                 : FblTp_CyclicTaskEntryPoint
 *  Description          :
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_CyclicTaskEntryPoint(void)
{
   /* check Tx Confirmation */
   FblTp_CheckForEndOfTxRsp();
   
   /* check Rx Indication */
   FblTp_CheckForRxReq();
    
   /* check for Timer interrupts */
   FblTp_CheckForTimer();
   
   /* activation of the TP jobs */
   FblTp_Task();
    
}

/*********************************************************************************************
 *  Name                 : FblTp_GetReceivedCanMsg
 *  Description          :
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
uint8_t* FblTp_GetReceivedCanMsg( uint16_t * lpuw_Size)
{
   if (rul_FblTp_Msg_Mngt_Dat.ruw_MsgSize ) 
   {   
       (*lpuw_Size) = rul_FblTp_Msg_Mngt_Dat.ruw_MsgSize;

       FBLTP_DISABLE_ALL_INTERRUPTS();
             rul_FblTp_Msg_Mngt_Dat.ruw_MsgSize = 0x00u; /* Reset MsgSize */
       FBLTP_ENABLE_ALL_INTERRUPTS();
   
       return &(raub_TP_buffer[0x00u]);
   }
   else
   {
       *lpuw_Size = 0x00u;
       return NULL;
   }
}

/*********************************************************************************************
 *  Name                 : TP_IsTxMessageSent
 *  TAG                  : 
 *  Description          : Check if TP message is sent on CAN
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : 1 if message is sent else 0
 *  Critical/explanation : [No] 
 ********************************************************************************************/
uint8_t FblTp_IsTxMessageSent(void)
{
   return(rul_FblTp_Msg_Mngt_Dat.rub_TPMessageSent);
}

/*********************************************************************************************
 *  Name                 : FblTp_N_USData_request
 *  Description          : This function executes the request to transmit a message
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  rul_CAN_ID - The CAN ID on which the transmission is done
 *                       : [input]  ruw_Length - Number of bytes of usable data
 *                       : [input]  pub_data   - Pointer to data
 *                       : [output] None
 *  Return               : E_TP_OK   - The transmission process was initiated successfully
 *                       : E_TP_BUSY - The Generic TP is currently busy with a different task
 *                       : E_TP_INVALID_DATA - Pointer to the data to be sent is NULL
 *                       : E_TP_INVALID_ID - required CAN ID for transimission is invalid
 *                       : E_TP_TOO_LARGE - the ruw_length param is larger then the buffer size
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_N_USData_request(uint8_t * pub_data, 
                            uint16_t ruw_Length)
{
   uint8_t raub_tp_buffer[FBLTP_C_CAN_MAX_DLC];
    
   /* Copy the data to the message buffer */   
   FBLTP_ITF_IMP_MEM_COPY(&(raub_TP_buffer[0]), 
                          pub_data,
                          ruw_Length);

   /* Reset flag "message sent" */
   FBLTP_DISABLE_ALL_INTERRUPTS();
       rul_FblTp_Msg_Mngt_Dat.rub_TPMessageSent = 0x00u;
   FBLTP_ENABLE_ALL_INTERRUPTS();
 
   /* ------------ */
   /* SINGLE FRAME */
   /* ------------ */
   if (ruw_Length <= FBLTP_C_SF_LEN )
   {
       raub_tp_buffer [FBLTP_C_N_PCI_POSITION] = (uint8_t)ruw_Length;
       
       /* Copy the data to be sent in the transmmit buffer */
       FBLTP_ITF_IMP_MEM_COPY(&(raub_tp_buffer[FBLTP_C_N_PCI_POSITION + 0x01u]), 
                              &(raub_TP_buffer[0]), 
                              ruw_Length);
       FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_AS);
	   
       FBLTP_DISABLE_ALL_INTERRUPTS();	   
           rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_SF_TX_CNFM;
	FBLTP_ENABLE_ALL_INTERRUPTS();   

	FblTp_L_Data_request((uint8_t)(ruw_Length + 0x01u), 
                            &raub_tp_buffer[0]);
       
   } /* if ( rub_Length <= FBLTP_C_SF_LEN ) */    
   /* ----------- */
   /* FIRST FRAME */
   /* ----------- */
   else
   {
        /* Set the PCI bytes for First Frame */
        raub_tp_buffer [FBLTP_C_N_PCI_POSITION]  = (FBLTP_C_N_PCI_TYP_FF | 
                                                    ((uint8_t)(ruw_Length >> 0x08u)));
        raub_tp_buffer [FBLTP_C_LEN_OF_FF_POSITION] = (uint8_t)(ruw_Length % 256u);

        /* Initialise sequence number */
       FBLTP_DISABLE_ALL_INTERRUPTS();		
        rul_FblTp_Msg_Mngt_Dat.SN_Tx = 0x00u;
       FBLTP_ENABLE_ALL_INTERRUPTS();
        /* Copy data to the local buffer */
        FBLTP_ITF_IMP_MEM_COPY(&raub_tp_buffer[FBLTP_C_N_PCI_POSITION + 0x02u], 
                               &(raub_TP_buffer[0]), 
                               FBLTP_C_FF_LEN);
        /* Update index used for reading from the buffer */
		
        FBLTP_DISABLE_ALL_INTERRUPTS();		
        rul_FblTp_Msg_Mngt_Dat.BufferIndex += FBLTP_C_FF_LEN;
        /* Send the First Frame */
                                  
        rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_FF_TX_CNFM;
        /* Update the number of CF Frames and number of bytes still to be sent */
        rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Tx    = (ruw_Length / FBLTP_C_CF_LEN);
        rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx = (ruw_Length - FBLTP_C_FF_LEN);
        FBLTP_ENABLE_ALL_INTERRUPTS();
		
        FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_AS);

        FblTp_L_Data_request(FBLTP_C_CAN_MAX_DLC,
                             &raub_tp_buffer[0x00u]);
   } /* else (for FF) */
}  /* end of FblTp_N_USData_request() */ 



/* Private functions prototypes */
/* ---------------------------- */

 /*********************************************************************************************
 *  Name                 : FblTp_N_USData_indication
 *  Description          :
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_N_USData_indication (uint16_t luw_Length)
{
   /* Gets len=0 in case of problem ... Data are always in raub_TP_buffer */
   FBLTP_DISABLE_ALL_INTERRUPTS();
       rul_FblTp_Msg_Mngt_Dat.ruw_MsgSize = luw_Length;
   FBLTP_ENABLE_ALL_INTERRUPTS();

}

 /*********************************************************************************************
 *  Name                 : FblTp_N_USData_confirm
 *  Description          :
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_N_USData_confirm(uint8_t rub_status)
{
   /* Confirms the end of transmission */
   switch (rub_status)
   {
       case FBLTP_C_TP_RSLT_N_OK:
            /* Indicates message is sent */
            FBLTP_DISABLE_ALL_INTERRUPTS();
                 rul_FblTp_Msg_Mngt_Dat.rub_TPMessageSent = 0x01u;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            break;
       default:
            /* Do Nothing */
            break;
   }
}


/*********************************************************************************************
 *  Name                 : FblTp_L_Data_confirm
 *  Description          : This function is called after a CAN frame was transmitted
 *                       : over the bus. Depending on the current state of the TP,
 *                       : this function changes the current TP State and/or re-sets
 *                       : the value of the time-out counter and/or calls the
 *                       : corresponding upper layer confirmation function
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  rul_CAN_ID: the CAN ID for which the confirmation is given
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_L_Data_confirm (void )
{
   
   switch (rul_FblTp_Msg_Mngt_Dat.TPState )
   {
       case FBLTP_C_TPST_WAIT_SF_TX_CNFM:
       case FBLTP_C_TPST_WAIT_LST_CF_TX_CNFM:
            /* End of transmission. Go to Idle state */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
            rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_IDLE;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
	     /* Stop the TP timer ON THIS CHANNEL - in this case for As */
            FblTp_TimerStop();
		 
            FBLTP_DISABLE_ALL_INTERRUPTS();
            rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x0000u;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            /* Confirm the end of transmision to the upper layer. Ignore the return value. We have no error handling strategy defined here */
            FblTp_N_USData_confirm(FBLTP_C_TP_RSLT_N_OK);              
            break;

       case FBLTP_C_TPST_WAIT_CFBLK_TX_CNFM:
            /* A block of Consecutive Frames was transmited. Waiting for Flow Control Frame Reception */
            /* Start timer for the next FC reception */
            FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_BS);
            FBLTP_DISABLE_ALL_INTERRUPTS();
            rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_FC_RX;
            FBLTP_ENABLE_ALL_INTERRUPTS();			
            break;

       case FBLTP_C_TPST_WAIT_FF_TX_CNFM:
            /* First Frame was transmited. Wait for First Flow Control Frame reception */
            /* Start timer for the first FC reception */
            FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_BS);
			
            FBLTP_DISABLE_ALL_INTERRUPTS();
            rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_1ST_FC_RX;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            break;

       case FBLTP_C_TPST_WAIT_CF_TX_CNFM:
            /* A consecutive Frame was transmited. Wait the Separation time before sending the next Consecutive Frame */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
                rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_CF_TX;
            FBLTP_ENABLE_ALL_INTERRUPTS();

            if(0x00000000u == rul_FblTp_Msg_Mngt_Dat.STmin_Tx)
            {
               /* In case of STmin==0 the CF is transmitted right now */
               /* Tmr CB is called in order to keep the ctrl information consistent */
               FBLTP_DISABLE_ALL_INTERRUPTS();
                   rul_FblTp_Msg_Mngt_Dat.rub_TO_flag = 0x01u;
               FBLTP_ENABLE_ALL_INTERRUPTS();
			   
            }
            else
            {
               /* Start timer for the Separation Time */
               FblTp_TimerStart(rul_FblTp_Msg_Mngt_Dat.STmin_Tx);
            }                            
            break;

       case FBLTP_C_TPST_WAIT_FC_TX_CNFM:
            /* Flow Control Frame was transmitetd. Wait for reception of Consecutive Frame */
            /* Start timer for the next CF reception */
            FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_CR);
			
            FBLTP_DISABLE_ALL_INTERRUPTS();
                rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_CF_RX;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            break;

       default:
            /* Ignore it */
            return;
   }  /* switch ( rub_tp_TPState ) */
}/* FblTp_L_Data_confirm() */

/*********************************************************************************************
 *  Name                 : FblTp_L_Data_indication
 *  Description          : This function is called after a CAN frame
 *                       : was received over the bus. Depending on
 *                       : the type of the received frame (Single Frame, First Frame,
 *                       : Consecutive Frame, Flow Control Frame) it reacts
 *                       : accordingly to process the frame
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  rul_CAN_ID - The CAN ID of the frame that was received
 *                       : [input]  rub_size   - The DLC of the CAN frame that was received
 *                       : [input]  pub_data   - Pointer to the data bytes from the CAN Frame
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : [No] 
 ********************************************************************************************/
void FblTp_L_Data_indication (uint8_t rub_size, 
    	                              uint8_t    i_lubCanBufIndex,
                              uint8_t* const pub_data)
{  
   uint8_t lub_FlowStatus;  /* Flow status field from the Flow Control Frame */
   uint8_t lub_PCIByte;     /* First PCI byte i.e. Frame type (SF/FF/CF/FC) */
   uint8_t lub_ST;          /* Current STmin value */
   uint8_t lub_SnRx; 
   uint8_t raub_tp_buffer[FBLTP_C_CAN_MAX_DLC];

   i_lubCanBufIndex = i_lubCanBufIndex;
   /* If TP is in a transmission state, ignore any received frame */ 
   if ((rul_FblTp_Msg_Mngt_Dat.TPState & FBLTP_C_TPST_WAIT_CNFM) ||
       (rul_FblTp_Msg_Mngt_Dat.TPState & FBLTP_C_TPST_WAIT_TX  ))
   {
   
        return;
   }
    
   /* Frame padding is required */
   #if (FBLTP_C_INIT_FRAME_BEFORE_TX==TRUE) /*lint !e731 Filter Info 731 "Boolean argument to equal/not equal" */
       if (rub_size != FBLTP_C_CAN_MAX_DLC)
       {
           /* DLC is less than 8, invalid situation if data padding is required */
           return;
       }
   #else
       /*If DLC of the received frame is zero, ignore it*/
       if (!rub_size)
       {
           return;
       }
   #endif    
    
   /* Check for NULL pointer */
   if (!pub_data)
   {
       return;
   }

   /* Check what type of frame was received. */
   lub_PCIByte = pub_data[FBLTP_C_N_PCI_POSITION];
   
   

   switch (lub_PCIByte & FBLTP_C_MASK_N_PCI_TYPE)
   {

       /* ------------ */
       /* SINGLE FRAME */
       /* ------------ */
       case FBLTP_C_N_PCI_TYP_SF:
            /* Get the Data length from the PCI byte 
             */
            FBLTP_DISABLE_ALL_INTERRUPTS();             
                rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx = (uint16_t)((uint16_t)lub_PCIByte & 
                                                                       FBLTP_C_MASK_SF_DAT_LEN);
            FBLTP_ENABLE_ALL_INTERRUPTS();
            
            /* If the received size of the frame does not correspond with 
               Data length from PCI byte, ignore it 
             */
            if((rub_size <= rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx) || 
               (!rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx))
            {
                return;
            }
            switch (rul_FblTp_Msg_Mngt_Dat.TPState)
            {
                case FBLTP_C_TPST_WAIT_FC_RX:
                case FBLTP_C_TPST_WAIT_1ST_FC_RX:
                     /* TP is in the midle of transmission. 
                        Ignore the received Frame 
                      */
                     return;
                     
                case FBLTP_C_TPST_WAIT_CF_RX:
                     /* TP is waiting for a CF. Indicate to the upper layer. 
                       Ignore the return status. We have no error handling 
                       strategy defined here. 
                     */
                     FblTp_N_USData_indication(0x00u);
                     /* Abort the current reception */
                     break;

                default:
                     /* Abort current reception */
                     break;
            } /* switch ( rub_tp_TPState ) */

            /* Start reception of a Single Frame */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
                rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x00u;
            FBLTP_ENABLE_ALL_INTERRUPTS();

            /* Copy received data to the message buffer */
            FBLTP_ITF_IMP_MEM_COPY(&(raub_TP_buffer[0x00u]), 
                                   (pub_data+FBLTP_C_LEN_OF_FF_POSITION), 
                                   rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx);
            /* Reception ended. Go to Idle */
	     FblTp_Return2InitStAndCallIndication (rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx);
			
            break;

       /* ----------- */
       /* FIRST FRAME */
       /* ----------- */
       case FBLTP_C_N_PCI_TYP_FF:
            /* Ignore frames with DLC less than FBLTP_C_CAN_MAX_DLC */
            if (rub_size < FBLTP_C_CAN_MAX_DLC)
            {
            
                return;
            }
            else
            {

            }
			//
			if (rul_FblTp_Msg_Mngt_Dat.rub_CurrRxReqChannel == CANDRV_C_RX_FUNCTIONAL_ADDRESSING) {
				return;
			}
			else {

			}
            //
            switch (rul_FblTp_Msg_Mngt_Dat.TPState )
            {
                case FBLTP_C_TPST_WAIT_FC_RX:
                case FBLTP_C_TPST_WAIT_1ST_FC_RX:
                     /* TP is in the midle of transmission. 
                        Ignore the received Frame 
                      */
                      
                     return;

                case FBLTP_C_TPST_WAIT_CF_RX:
                     /* TP is waiting for a CF. Indicate to the upper layer. 
                        Ignore the return status. We have no error handling 
                        strategy defined here.  
                      */
                     FblTp_N_USData_indication( 0x00u );
                     /* Abort the current reception */
                     break;

                default:
                    /* Abort current reception */
                    break;

            } /* switch ( rub_tp_TPState ) */
            /* Start the reception of the new message */
            /* Get 12-bit message length information */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
                rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx  =
                    (uint16_t)( ( (uint16_t)(pub_data[FBLTP_C_N_PCI_POSITION]) & 
                                  (uint16_t)FBLTP_C_MASK_FF_DAT_LEN 
                                ) << (uint16_t)0x0008u 
                              ) +
                    (uint16_t)(pub_data[FBLTP_C_LEN_OF_FF_POSITION]); 
            FBLTP_ENABLE_ALL_INTERRUPTS();

            /* Ignore frames with FF_DL <= 7 (Normal addressing) and 6 (Extended addressing) */
            if (rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx <= FBLTP_C_SF_LEN)
            {
            
                return;
            }

            /* Check for overflow */
            if (rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx > FBLTP_C_BUFFER_SIZE )
            {
                /* Overflow. Assemble a flow control frame */
                raub_tp_buffer[FBLTP_C_N_PCI_POSITION]     = (FBLTP_C_N_PCI_TYP_FC | 
                                                              FBLTP_C_TP_FLOW_ST_OVFLW);
                raub_tp_buffer[FBLTP_C_FC_BS_POSITION]     = rul_FblTp_Msg_Mngt_Dat.BS_Rx;
                raub_tp_buffer[FBLTP_C_FC_ST_MIN_POSITION] = rul_FblTp_Msg_Mngt_Dat.STmin_Rx;

                /* Go to Idle */
                FBLTP_DISABLE_ALL_INTERRUPTS();				
                    rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x00u;
                    rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_IDLE;
                FBLTP_ENABLE_ALL_INTERRUPTS();
				
                /* During the IDLE state the timers are stopped anyway */
                FblTp_TimerStop();

                FblTp_L_Data_request(FBLTP_C_MIN_FC_LEN, 
                                     &raub_tp_buffer[0x00u]);
                return;
            }
            /* Set the remaining data bytes stil to receive */
            FBLTP_DISABLE_ALL_INTERRUPTS();						
                rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx = rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx;
                rul_FblTp_Msg_Mngt_Dat.SN_Rx = 0x00u;
                rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x00u;
            FBLTP_ENABLE_ALL_INTERRUPTS();			
			
            /* Copy the received bytes to the buffer */
            /* lint !e960 ; here the sums can be done on a 8-bit type, 
               the further cast to a bigger type is absolutely safe 
             */
            FBLTP_ITF_IMP_MEM_COPY(&(raub_TP_buffer[0x00u]), 
                                   (pub_data + FBLTP_C_LEN_OF_FF_POSITION + 0x01u), 
                                   (rub_size - (FBLTP_C_LEN_OF_FF_POSITION + 0x01u))); 
            /* Update the index in buffer */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
                rul_FblTp_Msg_Mngt_Dat.BufferIndex += (rub_size - (FBLTP_C_LEN_OF_FF_POSITION + 0x01u)) ; 
            FBLTP_ENABLE_ALL_INTERRUPTS();

            /* Indicate FF reception to the upper layer. 
               Ignore the return status. We have no error 
               handling strategy defined here.  
             */
 
            /* Assemble Flow Control Frame */
            raub_tp_buffer[FBLTP_C_N_PCI_POSITION]     = FBLTP_C_N_PCI_TYP_FC;
            raub_tp_buffer[FBLTP_C_FC_BS_POSITION]     = rul_FblTp_Msg_Mngt_Dat.BS_Rx;
            raub_tp_buffer[FBLTP_C_FC_ST_MIN_POSITION] = rul_FblTp_Msg_Mngt_Dat.STmin_Rx;

                                   
            /* Set the timeout */
            FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_AR);
            /* Set the number of Consecutive Frames for this message and for this block */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
                rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx = (uint16_t)(rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx / 
                                                                    FBLTP_C_CF_LEN);
                /* Update the nr. of frames inside the block */
                if (!rul_FblTp_Msg_Mngt_Dat.BS_Rx)
                {
                    rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx = rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx;
                }
                else
                {
                    rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx = rul_FblTp_Msg_Mngt_Dat.BS_Rx;
                }
                rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_FC_TX_CNFM;
                /* Update the number of Data bytes still to receive */
                rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx -= FBLTP_C_FF_LEN;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            FblTp_L_Data_request(FBLTP_C_MIN_FC_LEN, 
                                 &raub_tp_buffer[0]);
		 

		 
            break;
            
       /* ----------------- */
       /* CONSECUTIVE FRAME */
       /* ----------------- */
       case FBLTP_C_N_PCI_TYP_CF:
            if (rul_FblTp_Msg_Mngt_Dat.TPState != FBLTP_C_TPST_WAIT_CF_RX )
            {
            
                return;
				
            }
			//
			if (rul_FblTp_Msg_Mngt_Dat.rub_CurrRxReqChannel == CANDRV_C_RX_FUNCTIONAL_ADDRESSING) {
				return;
			}
			else {

			}   
            /* Increment Sequence Number */
            FBLTP_DISABLE_ALL_INTERRUPTS();			
            //rul_FblTp_Msg_Mngt_Dat.SN_Rx = (uint8_t)((rul_FblTp_Msg_Mngt_Dat.SN_Rx + 0x01u) % 
            //                                         (uint8_t)(FBLTP_C_MAX_CF_SN + 0x01u));

              lub_SnRx =  (uint8_t) ((rul_FblTp_Msg_Mngt_Dat.SN_Rx + 0x01u)	% 0x10u);
		rul_FblTp_Msg_Mngt_Dat.SN_Rx =   lub_SnRx;
		
            FBLTP_ENABLE_ALL_INTERRUPTS();						
            /* If the received SN is not correct, abort reception */
            if ((lub_PCIByte & FBLTP_C_MASK_CF_SEQ_NUM ) != rul_FblTp_Msg_Mngt_Dat.SN_Rx )
            {
                /* Go to Idle state */
                
                FblTp_Return2InitStAndCallIndication (0x00u);
				
                return;
            } /* if ((pub_data[FBLTP_C_N_PCI_POSITION] ... )) */

            /* If the received frame is the last Consecutive Frame */
            if (rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx == 0x01u)
            {
                /* If the DLC of the received frame do not corespond with the expected number of bytes (+ PCI) */
                /* the frame is ignored */
                if (rub_size < (uint8_t)(rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx + 0x01u))
                {
                    return;
                } /* End wrong size for last CF */
                /* Proccess the Frame */
                /* Copy the received data bytes to the buffer */
                FBLTP_ITF_IMP_MEM_COPY(&(raub_TP_buffer[rul_FblTp_Msg_Mngt_Dat.BufferIndex]), 
                                       (pub_data+FBLTP_C_LEN_OF_FF_POSITION),
                                       (uint8_t)(rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx));
                /* Go to IDLE */
                FBLTP_DISABLE_ALL_INTERRUPTS();                
                    rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx = 0x00u;
                    rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx      = 0x00u;
                    rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx   = 0x00u;
                FBLTP_ENABLE_ALL_INTERRUPTS();
				
                /* Indication to the upper layer that the reception was finshed OK. . 
                    Ignore the return status. We have no error handling strategy defined here.  
                 */
                FblTp_Return2InitStAndCallIndication (rul_FblTp_Msg_Mngt_Dat.CompleteLength_Rx);

				
            }   
            /* The received frame is not the last Consecutive Frame */    
            else
            {
                /* A CF that is not the last CF, must have a DLC of a full CAN Frame */
                /* If this is not the case, ignore it */
                if (rub_size < FBLTP_C_CAN_MAX_DLC)
                {
                    /* Decrement the Sequence number */
                    if (!rul_FblTp_Msg_Mngt_Dat.SN_Rx)
                    {
                         FBLTP_DISABLE_ALL_INTERRUPTS();						                    
                          rul_FblTp_Msg_Mngt_Dat.SN_Rx = FBLTP_C_MAX_CF_SN;
                         FBLTP_ENABLE_ALL_INTERRUPTS();						
						
                    }
                    else
                    {
                         FBLTP_DISABLE_ALL_INTERRUPTS();                    
                          rul_FblTp_Msg_Mngt_Dat.SN_Rx--;
                         FBLTP_ENABLE_ALL_INTERRUPTS();						                    
						
                    }
                    return;
                } /* End check size */
                else
                {

                }
                /* The received frame has a correct DLC. Proccess it */
                /* Copy the data bytes to the buffer */
                /*lint !e960 ; here the sums can be done on a 8-bit type, 
                  the further cast to a bigger type is absolutely safe 
                 */
                FBLTP_ITF_IMP_MEM_COPY(&(raub_TP_buffer[rul_FblTp_Msg_Mngt_Dat.BufferIndex]), 
                                       (pub_data+FBLTP_C_LEN_OF_FF_POSITION), 
                                       (rub_size-FBLTP_C_LEN_OF_FF_POSITION) ); 
                /* Update the number of CF still to receive */
                FBLTP_DISABLE_ALL_INTERRUPTS();				
                rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx--;
                rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Rx--;
                rul_FblTp_Msg_Mngt_Dat.BufferIndex += (rub_size-FBLTP_C_LEN_OF_FF_POSITION);
                FBLTP_ENABLE_ALL_INTERRUPTS();
				
                /* Is the received frame the last CF of the current block? */
                if (!rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx )
                {
                    /* Assemble Flow Control Frame */
                    raub_tp_buffer[FBLTP_C_N_PCI_POSITION]     = FBLTP_C_N_PCI_TYP_FC;
                    raub_tp_buffer[FBLTP_C_FC_BS_POSITION]     = rul_FblTp_Msg_Mngt_Dat.BS_Rx;
                    raub_tp_buffer[FBLTP_C_FC_ST_MIN_POSITION] = rul_FblTp_Msg_Mngt_Dat.STmin_Rx;
                    FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_AR);

                    FBLTP_DISABLE_ALL_INTERRUPTS();					
                        rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Rx = rul_FblTp_Msg_Mngt_Dat.BS_Rx; 
                        rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_FC_TX_CNFM;
                        rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx -= FBLTP_C_CF_LEN;
                    FBLTP_ENABLE_ALL_INTERRUPTS();

                    FblTp_L_Data_request(FBLTP_C_MIN_FC_LEN, 
                                         &raub_tp_buffer[0]);

                }   
                /* The received frame is an ordinary CF */
                else
                {
                    FblTp_TimerStart( FBLTP_C_TMR_TIMOUT_N_CR);
					
                    FBLTP_DISABLE_ALL_INTERRUPTS();					
                    rul_FblTp_Msg_Mngt_Dat.RemainingLength_Rx -= FBLTP_C_CF_LEN;
                    FBLTP_ENABLE_ALL_INTERRUPTS();
					
                }   /* else */
            }   /* else - received Frame is not the Last Consecutive Frame */

            break;
            
       /* ------------------ */
       /* FLOW CONTROL FRAME */
       /* ------------------ */
       case FBLTP_C_N_PCI_TYP_FC:
            if ((rul_FblTp_Msg_Mngt_Dat.TPState != FBLTP_C_TPST_WAIT_FC_RX ) &&
                (rul_FblTp_Msg_Mngt_Dat.TPState != FBLTP_C_TPST_WAIT_1ST_FC_RX ) )
            {
                return;
            }   
            /* Check the size of the received frame */
            if ((rub_size > FBLTP_C_MAX_FC_LEN) || (rub_size < FBLTP_C_MIN_FC_LEN))
            {
                return;
            }
            else
            {

            }
			//
			if (rul_FblTp_Msg_Mngt_Dat.rub_CurrRxReqChannel == CANDRV_C_RX_FUNCTIONAL_ADDRESSING) {
				return;
			}
			else {

			}
            /* Get Flow Status */
            lub_FlowStatus = lub_PCIByte & FBLTP_C_MASK_FC_FLOW_ST;

            /* Is the received Frame the first FC ? */
            if (rul_FblTp_Msg_Mngt_Dat.TPState == FBLTP_C_TPST_WAIT_1ST_FC_RX )
            {
                /* Check the Flow Status */
                switch(lub_FlowStatus)
                {
                    /* Flow Status is Continue To Send. Get the Block size, separation time */
                    case FBLTP_C_TP_FLOW_ST_CONTINUE_2_SEND:
                             FBLTP_DISABLE_ALL_INTERRUPTS();						
                                   rul_FblTp_Msg_Mngt_Dat.BS_Tx = pub_data[FBLTP_C_FC_BS_POSITION];
                             FBLTP_ENABLE_ALL_INTERRUPTS();
						 
                         /* Treatment of the STmin */
                         lub_ST = pub_data[FBLTP_C_FC_ST_MIN_POSITION];
                         if (lub_ST <= 0x7Fu)
                         {   
                             FBLTP_DISABLE_ALL_INTERRUPTS();                             
                                 rul_FblTp_Msg_Mngt_Dat.STmin_Tx = ((lub_ST*1000u*FBLTP_C_TASK_CYCLE_ZOOM)/FBLTP_C_TASK_CYCLE ); /* Convert into us , granuity is : 100us  */
                             FBLTP_ENABLE_ALL_INTERRUPTS();
							 
                         }   
                         else if ((lub_ST >= 0xF1)&&(lub_ST <= 0xF9))
                         {
                             /* STmin between 100-900us => Fast Timer */
                            FBLTP_DISABLE_ALL_INTERRUPTS();							 
                                 /* Convert into us, granuity is : 100us , currently , not supported, so to use default stmin 
                                  */
				            rul_FblTp_Msg_Mngt_Dat.STmin_Tx = ( ((lub_ST - 0xF0u) * 100u*FBLTP_C_TASK_CYCLE_ZOOM)/ FBLTP_C_TASK_CYCLE); /* granuity is : 100us */
                            FBLTP_ENABLE_ALL_INTERRUPTS();
							 
                         }
		                 else if (lub_ST == 0x00u)
		                 {
                            FBLTP_DISABLE_ALL_INTERRUPTS();							 
                                 /* Convert into us, granuity is : 100us ,  
                                  */
				            rul_FblTp_Msg_Mngt_Dat.STmin_Tx = ( (0x02u * 100u*FBLTP_C_TASK_CYCLE_ZOOM)/ FBLTP_C_TASK_CYCLE); /* granuity is : 100us */
                            FBLTP_ENABLE_ALL_INTERRUPTS();
		              
		                 }
                         else
                         {
                            /* Reserved STmin */
                            #if (FBLTP_C_USE_DEFAULT_4_RESVD_ST == TRUE) 
                                /*lint !e731 Filter Info 731 "Boolean argument to equal/not equal" */
                                FBLTP_DISABLE_ALL_INTERRUPTS();							
                                    rul_FblTp_Msg_Mngt_Dat.STmin_Tx = ( (FBLTP_C_DEFAULT_STMIN * 1000u*FBLTP_C_TASK_CYCLE_ZOOM)/FBLTP_C_TASK_CYCLE ); /* Convert into us : granuity is : 100us  */							
                                FBLTP_ENABLE_ALL_INTERRUPTS();
								
                            #else                           
                                /* Reserved STmin => abort reception */
                                /* Inform upper layer of an incorrect STmin received */
                                FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_ERROR); 
								
                                return;
                            #endif
                         }
                         FBLTP_DISABLE_ALL_INTERRUPTS();						 
                             rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Tx = rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Tx;
                         FBLTP_ENABLE_ALL_INTERRUPTS();
						 
                         break;
                    /* Flow Status is Wait. Set the Timeout */
                    case FBLTP_C_TP_FLOW_ST_WAIT:
                         FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_BS);

                         return;
                    /* Flow Status is overflow. Abort transmission. */
                    case FBLTP_C_TP_FLOW_ST_OVFLW:
                         FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_OVFLW); 

                         return;
                    default:
                    /* Unknown FS received. Abort transmission */
                         FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_INVALID_FS); 
                                                                                          
                         return;
                } /* end of switch(lub_FlowStatus) */
            } /* End First Flow Control if (rul_FblTp_Msg_Mngt_Dat.TPState == FBLTP_C_TPST_WAIT_1ST_FC_RX ) */
            
            /* It is not the First Flow Control. Check Flow Status */
            if (lub_FlowStatus == FBLTP_C_TP_FLOW_ST_WAIT)
            {
                /* Flow Status is Wait. Set the timeout */
                FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_BS);
                
                return;
            }
            /* The Flow Status is Continue To Send */
            else if(lub_FlowStatus == FBLTP_C_TP_FLOW_ST_CONTINUE_2_SEND)
            {
                /* Update the Block size */
                FBLTP_DISABLE_ALL_INTERRUPTS();				
                    if (rul_FblTp_Msg_Mngt_Dat.BS_Tx)
                    {
                        rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Tx = rul_FblTp_Msg_Mngt_Dat.BS_Tx;
                    }
                    rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_WAIT_CF_TX;
                               
                    /* send the next Consecutive frame as soon as possible */
                    /* In case of STmin==0 the CF is transmitted right now */
                    /* Tmr CB is called in order to keep the ctrl information consistent */
                    rul_FblTp_Msg_Mngt_Dat.rub_TO_flag = 0x01u;
               FBLTP_ENABLE_ALL_INTERRUPTS();
				
            } /* End Flow Status CTS */
            else
            {
                ///* Invalid Flow Status. Abort reception */				
                FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_INVALID_FS); 
                return;
            }

            break;
            
        default:
            break;
    } /* switch ( pub_data[FBLTP_C_N_PCI_POSITION] & c_N_PCIType ) */
} 

static void FblTp_Return2InitStAndCallConfirm (uint8_t rub_status)
{
    FBLTP_DISABLE_ALL_INTERRUPTS();
        rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x00u;
        rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_IDLE;
    FBLTP_ENABLE_ALL_INTERRUPTS();

   /* Running Bs TO */
   FblTp_TimerStop();
   /*  Ignore the callback return status. 
        We have no error handling strategy defined here.  
     */
   FblTp_N_USData_confirm(rub_status); 
}

static void FblTp_Return2InitStAndCallIndication (uint16_t luw_length)
{
            FBLTP_DISABLE_ALL_INTERRUPTS();
                rul_FblTp_Msg_Mngt_Dat.BufferIndex = 0x00u;
                rul_FblTp_Msg_Mngt_Dat.TPState = FBLTP_C_TPST_IDLE;
            FBLTP_ENABLE_ALL_INTERRUPTS();
			
            FblTp_TimerStop();
            /* Indication to the upper layer. Ignore the return status. 
               We have no error handling strategy defined here.  
             */
            FblTp_N_USData_indication(luw_length);


}

 /*********************************************************************************************
 *  Name                 : TP_TimersCB
 *  Description          : This is the TO treatment function  
 *  Parameters           : [Input, Output, Input / output]
 *                       : [input]  None
 *                       : [output] None
 *  Return               : None
 *  Critical/explanation : Observe execution time - it can be called at interrupt level 
 ********************************************************************************************/
static void FblTp_Task (void)
{
   uint8_t raub_tp_buffer[FBLTP_C_CAN_MAX_DLC];
   uint16_t lub_lenght_TX;   /* local variable for Tx lenght */
   /* Only if a timeout occured. All other activities 
      are done in the CAN callbacks 
    */
   if (rul_FblTp_Msg_Mngt_Dat.rub_TO_flag)
   {
       FBLTP_DISABLE_ALL_INTERRUPTS();
       rul_FblTp_Msg_Mngt_Dat.rub_TO_flag = 0x00u;
       FBLTP_ENABLE_ALL_INTERRUPTS();
	   
       switch ( rul_FblTp_Msg_Mngt_Dat.TPState )
       {
           /* If As timeout has expired */
           case FBLTP_C_TPST_WAIT_SF_TX_CNFM:
           case FBLTP_C_TPST_WAIT_FF_TX_CNFM:
           case FBLTP_C_TPST_WAIT_CF_TX_CNFM:
           case FBLTP_C_TPST_WAIT_CFBLK_TX_CNFM:
           case FBLTP_C_TPST_WAIT_LST_CF_TX_CNFM:
                /* Go to Idle state*/
                FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_TIMEOUT_A);				
                break;
                
           case FBLTP_C_TPST_WAIT_FC_TX_CNFM:
                /* TP is in the midle of reception, and Ar timeout ocurred */    
                /* Go Idle state */
	            FblTp_Return2InitStAndCallIndication(0);			
                break;
                
           case FBLTP_C_TPST_WAIT_1ST_FC_RX:
           case FBLTP_C_TPST_WAIT_FC_RX:
                /* TP is in the midle of transmission */
                /* Abort transmission and go to Idle state */
                FblTp_Return2InitStAndCallConfirm(FBLTP_C_TP_RSLT_N_TIMEOUT_BS);				
				
                break;
                
          case FBLTP_C_TPST_WAIT_CF_RX:
               /* TP is in the middle of reception. The Cr timeout expired */
               /* Abort the reception and go to IDLE state */
		       FblTp_Return2InitStAndCallIndication(0);	   
               break;
              
          case FBLTP_C_TPST_WAIT_CF_TX:
               /* STmin timeout expired. Send the next CF */
               /* Add target node address */
               /* Increment sequence number */
               FBLTP_DISABLE_ALL_INTERRUPTS();			   
               rul_FblTp_Msg_Mngt_Dat.SN_Tx = (uint8_t)((rul_FblTp_Msg_Mngt_Dat.SN_Tx + 0x01u) % 
                                                            (uint8_t)(FBLTP_C_MAX_CF_SN + 0x01u));
               FBLTP_ENABLE_ALL_INTERRUPTS();
			   
               /* Set the PCI byte */
               raub_tp_buffer [FBLTP_C_N_PCI_POSITION] = (FBLTP_C_N_PCI_TYP_CF | 
                                                          rul_FblTp_Msg_Mngt_Dat.SN_Tx);
               
               // Fill content and length
               if (rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx < FBLTP_C_CF_LEN )
               {
                   /* This is the last CF to be sent for this message */
                   FBLTP_ITF_IMP_MEM_COPY(&raub_tp_buffer[FBLTP_C_N_PCI_POSITION + 0x01u], 
                                          &(raub_TP_buffer[rul_FblTp_Msg_Mngt_Dat.BufferIndex]), 
                                          rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx);
                   /* Update reading index */
                   FBLTP_DISABLE_ALL_INTERRUPTS();				   
                       rul_FblTp_Msg_Mngt_Dat.BufferIndex += rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx;
                   FBLTP_ENABLE_ALL_INTERRUPTS();
				   
                  /*Store the DLC because it is modified later */

                  /* Here RemainingLength_Tx is smaller than 7 (FBLTP_C_CF_LEN), 
                     that's the condition to enter this
                  ** block. Therefore, rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx+1 
                     is smaller than 8 and can safely 
                  ** be stored  on a 8-bits carrier */
                  lub_lenght_TX = rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx + 0x01u; /*lint !e734 See above */
              }
              else
              {
                  /* Is not the Last CF */
                  FBLTP_ITF_IMP_MEM_COPY(&raub_tp_buffer[FBLTP_C_N_PCI_POSITION+1], 
                                         &(raub_TP_buffer[ rul_FblTp_Msg_Mngt_Dat.BufferIndex]), 
                                         FBLTP_C_CF_LEN);
                  FBLTP_DISABLE_ALL_INTERRUPTS();				  
                  rul_FblTp_Msg_Mngt_Dat.BufferIndex +=  FBLTP_C_CF_LEN;
                  FBLTP_ENABLE_ALL_INTERRUPTS();
				  
                  /*  Set  DLC to FBLTP_C_CAN_MAX_DLC in case the CF is not the last*/
                  lub_lenght_TX = FBLTP_C_CAN_MAX_DLC;
              }
              
              /* Set the timeout(wait for confirmation) */
              FblTp_TimerStart(FBLTP_C_TMR_TIMOUT_N_AS);
              
              /* Update the number of consecutive frame still to send for this message and */
              /* for this block */
              FBLTP_DISABLE_ALL_INTERRUPTS();			  
              rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Tx--;
              rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Tx--;
              if (!rul_FblTp_Msg_Mngt_Dat.RemainingCFs_Tx )
              {
                  /* The CF sent, was the Last CF of the current message */
                  rul_FblTp_Msg_Mngt_Dat.TPState            = FBLTP_C_TPST_WAIT_LST_CF_TX_CNFM;
                  /* Update the data bytes number still to be sent */
                  rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx = 0x00u;
              }   
              else if (!rul_FblTp_Msg_Mngt_Dat.RemainingBlockCFs_Tx )
              {
                  /* The CF sent was the last CF of the current block */
                  rul_FblTp_Msg_Mngt_Dat.TPState             =   FBLTP_C_TPST_WAIT_CFBLK_TX_CNFM;
                  /* Update the data bytes number still to be sent */
                  rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx -= FBLTP_C_CF_LEN;
              }   
              else
              {
                  /* The sent CF was a ordinary one */
                  rul_FblTp_Msg_Mngt_Dat.TPState             = FBLTP_C_TPST_WAIT_CF_TX_CNFM;
                  /* Update the data bytes number still to be sent */
                  rul_FblTp_Msg_Mngt_Dat.RemainingLength_Tx -= FBLTP_C_CF_LEN;
              }
              FBLTP_ENABLE_ALL_INTERRUPTS();
			  
              // Send
              FblTp_L_Data_request((uint8_t)lub_lenght_TX,  /* uint8_t ub_Size   */
                                   (uint8_t*)&raub_tp_buffer[0]);    /* uint8_t* pub_Data */           
              break;
              /* end FBLTP_C_TPST_WAIT_CF_TX */

          default:
              break;
      } /* switch ( rub_tp_TPState ) */
   } /* if TO */
 } /* FblTp_Task() */




/***************************************************************/
/*! \brief Sends a TP request (message) over the CAN bus.
 *  \param[in] pub_Data pointer to the data to sent
 *  \param[in] ub_Size number of bytes to sent
 *  \return none
 * 
 * This function is called by the TP to send data on the CAN bus. */
/**************************************************************/
void FblTp_L_Data_request( uint8_t ub_Size, uint8_t* pub_Data ) 
{ 
   uint8_t lub_CanDrvTxResult = FALSE;
   
   if ( rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress == FALSE) 
   {
       #if (FBLTP_C_INIT_FRAME_BEFORE_TX == TRUE)
       while ( ub_Size < FBLTP_C_CAN_MAX_DLC ) 
       {
           pub_Data[ub_Size] = FBLTP_C_INIT_FRAME_VALUE;
           ub_Size++;
       }
       #endif             
       lub_CanDrvTxResult = FBLTP_ITF_IMP_TX_MSG_REQ((uint32_t)FBLTP_C_DIAG_CHANNEL, /* uint32_t msgId,*/
                                                     (uint8_t*)pub_Data,  /* uint8_t* pBytes, */
                                                     (uint8_t)ub_Size);  /* uint8_t  numBytes */
	if (lub_CanDrvTxResult == TRUE) 
	{
	    FBLTP_DISABLE_ALL_INTERRUPTS();
	             rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress = 0x01u;
           FBLTP_ENABLE_ALL_INTERRUPTS();
		
	}

	else
	{
	}
   }
   else
   {
   }
   
}

/***************************************************************/
/*! \brief Starts the TP timer.
 *  \param[in] ub_TimerType timer can be a Fast or a Slow Timer
 *  \param[in] ub_Channel TP channel for which the timer is started
 *  \param[in] uw_Value delay expressed in ms
 *  \return none
 * 
 * This function starts the TP timer for a given delay.
 * \remark The 2 first parameters are kept to be compliant with the TP function prototypes,
 * they shouldn't be needed in the FBL architecture :
 * - only slow timer type is used
 * - there's only one TP channel */
/**************************************************************/
static void FblTp_TimerStart(uint32_t ul_Value)
{
   /*! A timer based on the variable rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData is started. */
   FBLTP_SET_START_TIMEOUT_US(rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData, ul_Value);
   /*! The boolean rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive is set to true significating the timer is running. */
   FBLTP_DISABLE_ALL_INTERRUPTS();
        rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive = TRUE;
   FBLTP_ENABLE_ALL_INTERRUPTS();

}

/******************************************************************************/
/*                            Private Functions                               */
/*! \brief Stops the TP timer.
 *  \param[in] ub_Channel TP channel for which the timer is stoped
 *  \return none
 * 
 * This function stops the TP timer.
 * \remark The channel parameter is kept to be compliant with the TP function prototype,
 * it shouldn't be needed in the FBL architecture : there's only one TP channel. */
/**************************************************************/
static void FblTp_TimerStop(void)
{

   /*! The boolean rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive is set to false significating the timer is not running anymore. */
   FBLTP_DISABLE_ALL_INTERRUPTS();
        rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive = FALSE;
   FBLTP_ENABLE_ALL_INTERRUPTS();
   
}

uint32_t FblTp_GetTpTimer(void)
{
   return (rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData);
}

void FblTp_TickTpTimer(void)
{
   FBLTP_DISABLE_ALL_INTERRUPTS();
       if (rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive == TRUE)
       {       
           if (rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData)
           {
               rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData--;       	
           }
           else
           {           	
           }
       }
       else
       {     	
       }
       
   FBLTP_ENABLE_ALL_INTERRUPTS();
   	
}

/***************************************************************/
/*                    Private Function                         */
/*! \brief Checks if the TP timer 'interrupt' occurs or not.
 *  \param none
 *  \return none
 * 
 * This function is called cyclically to check if the TP timer has elapsed.
 * If the timer has elapsed, the TP timer timeout 'interrupt' callback is called.
 * \remark There's not interrupt in the FBL, that's why this function is called cyclically
 * to check the occurence of the timeout. */
/**************************************************************/
static void FblTp_CheckForTimer(void)
{
   /*! The state of the timer (running or stopped) is checked. */
   if (rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive )
   {
       /*! If the timer is running and the delay has elapsed : */
       if (FBLTP_GET_HAS_TIMEOUT_EXPIRED(rul_FblTp_Msg_Mngt_Dat.rul_TP_Timer_ExpirationData))
       {
           /*! - the boolean rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive is set to false significating 
               the timer is not running anymore. 
            */
           FBLTP_DISABLE_ALL_INTERRUPTS();
                 rul_FblTp_Msg_Mngt_Dat.rub_TPTimerActive = FALSE;
           FBLTP_ENABLE_ALL_INTERRUPTS();

           /*! - the TP timer callback is called to excute the 'interrupt' 
               code of the timer timeout 'interrupt'. 
            */
           FBLTP_DISABLE_ALL_INTERRUPTS();
               rul_FblTp_Msg_Mngt_Dat.rub_TO_flag = 0x01u;
           FBLTP_ENABLE_ALL_INTERRUPTS();

           /*! - the TP layer task is executed immediatly. */
           FblTp_Task();
       }
   }
}




/******************************************************************************/
/*                            Private Functions                               */
/*! \brief Checks if the last CAN message has been successfully sent.
 *  \param none
 *  \return none
 * 
 * This function is called cyclically by the Disgnosis Job task to check if the last
 * CAN message has been successfully sent. If it is the case, the TP layer is notified.
 */
/**************************************************************/
static void FblTp_CheckForEndOfTxRsp(void)
{        
   /* Was a message submitted for Tx ? */
   if ( rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress )
   {
       /*! If a transmission was in progress ( rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress is TRUE) 
           and the status of it is not pending :  
        */
       if ( FBLTP_ITF_IMP_GET_TX_MSG_FINISH_FLG() == 0x00u )
       {
           /*! - the boolean rub_TxMsgInProgress is set to FALSE  */
           FBLTP_DISABLE_ALL_INTERRUPTS();
                   rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress = FALSE;
           FBLTP_ENABLE_ALL_INTERRUPTS();
       
           /*! - the TP layer is notified of the good transmission */
           FblTp_L_Data_confirm();
       }
    }
}

void FblTp_NotifyCBForEndOfTxRsp(void)
{        
   /* Was a message submitted for Tx ? */
   if ( rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress )
   {
       /*! If a transmission was in progress ( rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress is TRUE) 
           and the status of it is not pending :  
        */
           /*! - the boolean  rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress is set to FALSE  */
           FBLTP_DISABLE_ALL_INTERRUPTS();
                   rul_FblTp_Msg_Mngt_Dat.rub_TxMsgInProgress = FALSE;
           FBLTP_ENABLE_ALL_INTERRUPTS();
       
           /*! - the TP layer is notified of the good transmission */
           FblTp_L_Data_confirm();
       
    }
    else
    {
    }
}


uint8_t  FblTp_Get_CurrRxReqChannel(void)
{
       return (rul_FblTp_Msg_Mngt_Dat.rub_CurrRxReqChannel);
}
/***************************************************************/
/*                    Private Function                         */
/*! \brief Checks if a CAN message has been just received.
 *  \param none
 *  \return none
 * 
 * This function is called cyclically by the Disgnosis Job task to check if a
 * CAN message has been just received. If it is the case, the TP layer is notified.
 */
/**************************************************************/
static void FblTp_CheckForRxReq(void)
{        
   
   uint8_t lub_RxCanMsgReadResult = FALSE;
   
   /*! The Diagnosis CAN Cell is polled... */
   lub_RxCanMsgReadResult = FBLTP_ITF_IMP_READ_RX_CAN_MSG_FRM_DRV((uint8_t*)&(rul_FblTp_Msg_Mngt_Dat.rub_CurrRxReqChannel), 
                                             (uint8_t*)&(rul_FblTp_Msg_Mngt_Dat.lub_CanBufIndex), 
                                             (uint8_t*)&(rul_FblTp_Msg_Mngt_Dat.laub_CanBuffer[(uint8_t)0x00u]), 
                                             (uint8_t*)&(rul_FblTp_Msg_Mngt_Dat.lub_CanMsgCount));
   
   if (lub_RxCanMsgReadResult == TRUE)
   {
       /*! If a message has been just arrived and if its length 
           is not null, the TP layer is notified. 
        */
       if ( (rul_FblTp_Msg_Mngt_Dat.lub_CanMsgCount)  != 0x00u )
       {
		
           FblTp_L_Data_indication(rul_FblTp_Msg_Mngt_Dat.lub_CanMsgCount,
		   	                               rul_FblTp_Msg_Mngt_Dat.lub_CanBufIndex,  
                                                  &(rul_FblTp_Msg_Mngt_Dat.laub_CanBuffer[0x00u]));
       }
	else
	{
	}
   }
   else
   {
   }
}





#ifdef __cplusplus
extern "C" {
#endif
