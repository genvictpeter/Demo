/****************************************************************************
 	@Module       
 	@Filename      uds_svc_dataMngr.c
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

#ifndef _UDS_SVC_DATA_MNGR_C
#define _UDS_SVC_DATA_MNGR_C



#include "uds_target.h"
#include "uds_confpriv.h"
#include "uds_confdefs.h"
#include "uds_priv.h"
#include "uds_inf.h"
#include "uds_svc_dataMngr.h"
#include "uds_pub.h"
#include "AppDefine.h"
#include "FlashDrv_ExtItf.h"

extern uint8_t 	  VIN[17];			/*F190*/
extern uint8_t 	  SW_Finger[9];
extern uint8_t 	  ECUBootDataVersion[10]; 
extern uint8_t    MotCode[30];
uint8_t    Mcu_Configuration[2];


extern const uint8_t PartNumber[9];
extern const uint8_t SuppID[10];
extern const uint8_t HW_VER[];
extern const uint8_t SW_VER[];
extern const uint8_t PRO_DATA[3];

#ifdef UDS_ENABLE_READDATABYIDENTIFIER

/* 0x22 ReadDataByIdentifier service data Managing table 
        Note : this table is located in the rom, can not be changed dynamically
               if a new did which is need to read, then must update this table 
               before build the whole of project again;
               The periodicalDid must also be configured into this table first, 
               then to configure the below table  Uds_g_RdDatByPeriodDidMngTbl
               to decide using which kind of period rate to read. 
               The DynamicDefined Did is not put into this table , but 
               the Dynamically defined Did must reference to the one or more of 
               DID in this read-only table, i.e. dynamicaDefined Did can only reference 
               to the pre-configured common DID.
        
 */
UDS_CONFIG_TYPE UDS_DidDatMngRecd_t Uds_g_DidDataTable[] =
{
/*      dataIdentifier                	DataSize            AccessAttribute      pDataBuf                  pFuncPtrToReadData */
/* 0u*/{UDS_C_DID_VIN_F190, 			UDS_C_DID_LEN_F190, UDS_C_DID_ATTR_F190, UDS_ITF_IMP_DAT_PTR_F190, UDS_ITF_IMP_RD_FNCPTR_F190 }, 
/* 1u*/{UDS_C_DID_SYS_PART_NUMBER_F187, UDS_C_DID_LEN_F187, UDS_C_DID_ATTR_F187, UDS_ITF_IMP_DAT_PTR_F187, UDS_ITF_IMP_RD_FNCPTR_F187 }, 
/* 2u*/{UDS_C_DID_ASW_FNGR_PRNT_F183,	UDS_C_DID_LEN_F183, UDS_C_DID_ATTR_F183, UDS_ITF_IMP_DAT_PTR_F183, UDS_ITF_IMP_RD_FNCPTR_F183 },  /* ECU Application Software FingerPrint Identification */
/* 3u*/{UDS_C_DID_ASW_FNGR_PRNT_F184, 	UDS_C_DID_LEN_F184, UDS_C_DID_ATTR_F184, UDS_ITF_IMP_DAT_PTR_F184, UDS_ITF_IMP_RD_FNCPTR_F184 },  /* ECU Application Software FingerPrint Identification */
/* 4u*/{UDS_C_DID_SYS_SUP_ID_F18A,    	UDS_C_DID_LEN_F18A, UDS_C_DID_ATTR_F18A, UDS_ITF_IMP_DAT_PTR_F18A, UDS_ITF_IMP_RD_FNCPTR_F18A },  /* ECU System Supplier Identifier Identification */
/* 5u*/{UDS_C_DID_APP_HW_VER_F191,   	UDS_C_DID_LEN_F191, UDS_C_DID_ATTR_F191, UDS_ITF_IMP_DAT_PTR_F191, UDS_ITF_IMP_RD_FNCPTR_F191 },	
/* 6u*/{UDS_C_DID_APP_SW_VER_F195,   	UDS_C_DID_LEN_F195, UDS_C_DID_ATTR_F195, UDS_ITF_IMP_DAT_PTR_F195, UDS_ITF_IMP_RD_FNCPTR_F195 },  /* ECU System Supplier Boot software Version Identification */
/* 7u*/{UDS_C_DID_PROGRAM_DATE_F199,  	UDS_C_DID_LEN_F199, UDS_C_DID_ATTR_F199, UDS_ITF_IMP_DAT_PTR_F199, UDS_ITF_IMP_RD_FNCPTR_F199 },  /* ECU programming date Identification */
/* 8u*/{UDS_C_DID_MOT_CODE_02FF,        UDS_C_DID_LEN_02FF, UDS_C_DID_ATTR_02FF, UDS_ITF_IMP_DAT_PTR_02FF, UDS_ITF_IMP_RD_FNCPTR_02FF },
/* 9u*/{UDS_C_DID_MOT_CODE_02FE,        UDS_C_DID_LEN_02FE, UDS_C_DID_ATTR_02FE, UDS_ITF_IMP_DAT_PTR_02FE, UDS_ITF_IMP_RD_FNCPTR_02FE },

       {0x0200,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0200, NULL},
       {0x0201,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0201, NULL},
       {0x0202,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0202, NULL},
       {0x0203,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0203, NULL},
       {0x0204,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0204, NULL},
       {0x0205,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0205, NULL},
       {0x0206,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0206, NULL},
       {0x0207,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0207, NULL},
       {0x0208,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0208, NULL},
       {0x0209,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0209, NULL},
       {0x020A,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020A, NULL},
       {0x020B,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020B, NULL},
       {0x020C,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020C, NULL},
       {0x020D,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020D, NULL},
       {0x020E,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020E, NULL},
       {0x020F,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_020F, NULL},
       {0x0210,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0210, NULL},
       {0x0212,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0212, NULL},
	   {0x0213,  	                    2,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0213, NULL},
	   {0x0214,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0214, NULL},
	   {0x0215,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0215, NULL},
	   {0x0216,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0216, NULL},
	   {0x0217,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0217, NULL},
	   {0x0218,  	                    1,                  UDS_C_DID_ATTR_SREC, UDS_ITF_IMP_DAT_PTR_0218, NULL},

/*This Line indicate the end of the data table , do not delete */
/*FFu*/{UDS_C_DID_END_OF_TBL_FFFF,    0x00u,              0x0000u,             NULL,                     NULL                       }
}; /* end of table : UDS_CONFIG_TYPE UDS_DidDatMngRecd_t Uds_g_DidDataTable[]  */
#endif  /* #ifdef UDS_ENABLE_READDATABYIDENTIFIER  */


#ifdef UDS_ENABLE_WRITEMEMORYBYADDRESS  

/* 0x23 ReadMemoryByAddress and 
   0x3D WriteMemoryByAddress service data Managing Table  
   Note : this table is located in the rom, can not be changed dynamically
               if a new did which is need to read, then must update this table 
               before build the whole of project again;
                 
 */
UDS_CONFIG_TYPE UDS_RdWtMemByAddDatMngRecd_t Uds_g_RdWtMemoryByAddrMngTbl[]  =  
{
/* Note : bi-rows for each record , please don't use other editor to modify , to avoid indent changing */
/*      RdWtByAddStartAdd                  DataSize                    AccessAttribute                    pDataBuf                        */
/* 0u*//* {UDS_C_MADD_00008000,               UDS_C_MADD_LEN_00008000,    UDS_C_MADD_ATTR_00008000,          UDS_ITF_IMP_DPTR_MADD_00008000, */
/*      PFuncPtrPreRdChk                   pFuncPtrToReadData          pFuncPtrPreWtChk                   pFuncPtrToWriteData             */
/* 0u*/ /* UDS_ITF_IMP_PRERD_CHK_FP_00008000, UDS_ITF_IMP_RD_FP_00008000, UDS_ITF_IMP_PREWT_CHK_FP_00008000, UDS_ITF_IMP_WT_FP_00008000     }, */



/*This Line indicate the end of the data table , do not delete */
/*FFu*/{0xFFFFFFFFu,                       0x0000u,                    0x0000u,                           NULL,     
/*FFu*/ NULL,                              NULL,                       NULL,                              NULL                           },
}; /* end of table UDS_CONFIG_TYPE UDS_RdWtMemByAddDatMngRecd_t Uds_g_RdWtMemoryByAddrMngTbl[]] */
#endif /* end of #ifdef UDS_ENABLE_WRITEMEMORYBYADDRESS */






#ifdef UDS_ENABLE_READDATABYPERIODICIDENTIFIER

/* 0x2A ReadDataByPeriodicalId service data Managing Table  
   Note : this table is located in ram, can be updated dynamically, 
          the below table is just initialization. 
          The period rate of periodicalDid can be configued into below table , 
          so it is very flexable  
 */

UDS_RdDatByPeriodDidMngRecd_t Uds_g_RdDatByPeriodDidMngTbl[UDS_C_PERIODIC_DID_MAX_NUM] =  
{
/*      PeriodDid  PeriodDidTbl  IsDynaDef  PeriodRateType                                               Starting    Running     */
/*                      RcdIndex                                                                                             Offset       PeriodTimer  */
/* 0u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x01u,      0x00000000u   },
/* 1u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x02u,      0x00000000u   },
/* 2u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x03u,      0x00000000u   },
/* 3u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x04u,      0x00000000u   },
/* 4u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x05u,      0x00000000u   },
/* 5u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x06u,      0x00000000u   },
/* 6u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x07u,      0x00000000u   },
/* 7u*/{0xFFu,     0xFFu,        FALSE,     UDS_C_PERIODIC_DID_TXMOD_STOPSENDING, 0x08u,      0x00000000u   }

}; /* end of table UDS_RdDatByPeriodDidMngRecd_t Uds_g_RdDatByPeriodDidMngTbl[UDS_C_PERIODIC_DID_MAX_NUM] */

#endif /* end of #ifdef UDS_ENABLE_READDATABYPERIODICIDENTIFIER */


#ifdef UDS_ENABLE_DYNAMICALLYDEFINEDATAIDENTIFIER

/* 0x2C DynamicallyDefineDataIdentifier service data Managing Table  
   Note : this table is located in ram, can be updated dynamically, 
          the below table is just initialization 
          The dynamically defined Data Identifier can reference to 
          one or more of the pre-configured common DID in table 
          Uds_g_DidDataTable. 
          The number of the dynamically defined DID , and the number of 
          the referenced common did can be combined flexiblely, 
          only depends on the RAM resource limitation. 
          for example : 
          F300 is 1st DynaDefDid, can refer to 4 common did; 
          F301 is 2nd dynDefDid, can refer to 8 common did; 
          F302 is 3rd dynDefDid, can refer to 2 common did; 
          F303 is 4th dynDefDid, can refer to 2 common did;
          totally , all of these 4 dynaDefDid using up all these 
          16 record resource in the below table. 
          or in the next use case , tester operate can 
          define a single DynaDefDid: 
          F305 , refer to 16 common did, then no more 
          dynaDefDid is supported anymore. 
          
         
 */
UDS_DynaDefDidMngRecd_t Uds_g_DynaDefDidMngTbl[UDS_C_DYNA_DEF_DID_MAX_NUM] = 
{
/*      DynaDefDid ReferedIs  Refered  PriorDyna  NextDyna  Access    */
/*                 DynaDef    DidIdx   TblIdx     TblIdx    Attribute */
/* 0u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 1u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 2u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 3u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 4u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 5u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 6u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 7u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 8u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/* 9u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*10u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*11u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*12u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*13u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*14u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  },
/*15u*/{0xFFFFu,   FALSE,     0xFFu,   0xFFu,     0xFFu,    0x0000u  }

}; /* end of table : UDS_DynaDefDidMngRecd_t Uds_g_DynaDefDidMngTbl[UDS_C_DYNA_DEF_DID_MAX_NUM] */
#endif /* end of #ifdef UDS_ENABLE_DYNAMICALLYDEFINEDATAIDENTIFIER */


#ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER

/* 0x2E WriteDataByIdentifier service data Managing table 
        Note : this table is located in the rom, can not be changed dynamically
               if a new did which is need to write , then must update this table 
               before build the whole of project again
               
               a Writable Did must be also readable , so 
               the writable Did must be alos configured in reading table : 
               Uds_g_DidDataTable
                
 */
UDS_CONFIG_TYPE UDS_DidEepromDatMngRecd_t Uds_g_DidEepromDataTable[] =
{
/*      dataIdentifier                				DataSize           		 AccessAttribute      	EepromBlkIdx,               		pDataBuf                  			pFuncPtrCheckData             		pFuncPtrToWriteData */
/* 0u*/{UDS_C_DID_ASW_FNGR_PRNT_F184, 	UDS_C_DID_LEN_F184, UDS_C_DID_ATTR_F184, UDS_ITF_IMP_E2_BLKIDX_F184, UDS_ITF_IMP_DAT_PTR_F184, UDS_ITF_IMP_CHK_FNCPTR_F184,  UDS_ITF_IMP_WT_FNCPTR_F184 },  /* ECU Application Software FingerPrint Identification */
/*1u*/{UDS_C_DID_VIN_F190,				UDS_C_DID_LEN_F190, UDS_C_DID_ATTR_F190, UDS_ITF_IMP_E2_BLKIDX_F190, UDS_ITF_IMP_DAT_PTR_F190, UDS_ITF_IMP_CHK_FNCPTR_F190,  UDS_ITF_IMP_WT_FNCPTR_F190 },  /* ECU programming date Identification */
/*2u*/{UDS_C_DID_MOT_CODE_02FF,			UDS_C_DID_LEN_02FF, UDS_C_DID_ATTR_02FF, UDS_ITF_IMP_E2_BLKIDX_02FF, UDS_ITF_IMP_DAT_PTR_02FF, UDS_ITF_IMP_CHK_FNCPTR_02FF,  UDS_ITF_IMP_WT_FNCPTR_02FF },
/*3u*/{UDS_C_DID_MOT_CODE_02FE,         UDS_C_DID_LEN_02FE, UDS_C_DID_ATTR_02FE, UDS_ITF_IMP_E2_BLKIDX_02FE, UDS_ITF_IMP_DAT_PTR_02FE, UDS_ITF_IMP_CHK_FNCPTR_02FE, UDS_ITF_IMP_WT_FNCPTR_02FE  },
                 
/*This Line indicate the end of the data table , do not delete */
/*FFu*/{UDS_C_DID_END_OF_TBL_FFFF,    0x00u,              0x0000u,             0x00u,                      NULL,                     NULL,                         NULL                       }

}; /* end of table : UDS_CONFIG_TYPE UDS_DidEepromDatMngRecd_t Uds_g_DidEepromDataTable[]  */
#endif /* end of #ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER */

#ifdef UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER
/* 0x2F InputOutputControlByIdentifier 
   Note : this table is located in the rom, can not be changed dynamically
          if a new did which is need to control InputOutput , then must update this table 
          before build the whole of project again;
                 
 */

UDS_CONFIG_TYPE UDS_IoCtrlIdxTblRcd_t Uds_g_IoCtrlByDidIdxTable[] = 
{
/*      dataIdentifier             DataSize            AccessAttribute      StartIndex,  NumOfEntry    */
/* 0u*/{UDS_C_DID_ECU_OUT_ST_3042, UDS_C_DID_LEN_3042, UDS_C_DID_ATTR_3042, 0x00u,       0x08u     }, 
                 
/*This Line indicate the end of the data table , do not delete */
/*FFu*/{UDS_C_DID_END_OF_TBL_FFFF, 0x00u,              0x0000u,             0x00u,       0x00u     }

}; /* end of table : UDS_CONFIG_TYPE UDS_IoCtrlIdxTblRcd_t Uds_g_IoCtrlByDidIdxTable[]  */


UDS_CONFIG_TYPE UDS_IoCtrlMngtDatTblRcd_t Uds_g_IoCtrlByDidMngtTable[UDS_2FIOCTRL_MNGT_RCD_MAX_NUM] = 
{
/*      pDataBuf                    IoCtrlBitmapMask               pFuncPtrToIoCtrl               */
/* 0u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_1, UDS_ITF_IMP_IOCTRL_3042_FP_1 }, 
/* 1u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_2, UDS_ITF_IMP_IOCTRL_3042_FP_2 }, 
/* 2u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_3, UDS_ITF_IMP_IOCTRL_3042_FP_3 }, 
/* 3u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_4, UDS_ITF_IMP_IOCTRL_3042_FP_4 }, 
/* 4u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_5, UDS_ITF_IMP_IOCTRL_3042_FP_5 }, 
/* 5u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_6, UDS_ITF_IMP_IOCTRL_3042_FP_6 }, 
/* 6u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_7, UDS_ITF_IMP_IOCTRL_3042_FP_7 }, 
/* 7u*/{UDS_ITF_IMP_DAT_PTR_3042,   UDS_ITF_IMP_IOCTRL_3042_MSK_8, UDS_ITF_IMP_IOCTRL_3042_FP_8 }, 

}; /* end of table : UDS_CONFIG_TYPE UDS_IoCtrlMngtDatTblRcd_t Uds_g_IoCtrlByDidMngtTable[]  */

#endif // end of #ifdef UDS_ENABLE_INPUTOUTPUTCONTROLBYIDENTIFIER

#ifdef UDS_ENABLE_ROUTINECONTROL
/* 0x31 RoutineControl service data Managing table 
        Note : this table is located in the rom, can not be changed dynamically
               if a new did which is need to perform routine control  , then must update this table 
               before build the whole of project again 
               for this table, due to the number of attributes is greater than 10 , so split as two rows. 
 */



UDS_CONFIG_TYPE UDS_RtnCtrlMngtDatTblRcd_t Uds_g_RtnCtrlMngtDataTable[] =
{
/*      routineIdentifier              AccessAttribute               ValidArgumentNum,               RtnRunLimitTime                  ExpectedPosResult              */
/* 0u*/{UDS_C_RID_ERS_MEM_RTN_FD00,    UDS_C_RID_ATTR_FD00,          UDS_C_RID_VLD_ARGU_NUM_FD00,    UDS_C_RID_RUN_TIM_LIMIT_FD00,    UDS_C_RID_EXP_POS_RSLT_FD00,  /* Routine : Erease Memory record , 1st line */
/*      pFuncPtrStart                  pFuncPtrStop                  pFuncPtrGetResult               pFuncPtrRtnCheck                 pFuncPtrIsRtnFinished          */
/* 0u*/ UDS_C_RID_FP_START_RTN_FD00,   UDS_C_RID_FP_STOP_RTN_FD00,   UDS_C_RID_FP_RESULT_RTN_FD00,   UDS_C_RID_FP_CHECK_RTN_FD00,     UDS_C_RID_FP_FINISH_RTN_FD00},/* Routine : Erease Memory record , 2nd line  */                 



/* These last two Lines indicate the end of the data table , do not delete                                                                                           */
/*      routineIdentifier              AccessAttribute               ValidArgumentNum,               RtnRunLimitTime                  ExpectedPosResult              */
/*FFu*/{0xFFFFu,                       0x0000u,                      0x00u,                          0x0000u,                         0x00u,                        /* Routine : Last Ending indication record , 1st line */
/*      pFuncPtrStart                  pFuncPtrStop                  pFuncPtrGetResult               pFuncPtrRtnCheck                 pFuncPtrIsRtnFinished          */
/*FFu*/ NULL,                          NULL,                         NULL,                           NULL,                            NULL                        },/* Routine : Last Ending indication record , 2nd line */
}; /* end of table : UDS_CONFIG_TYPE UDS_RtnCtrlMngtDatTblRcd_t Uds_g_RtnCtrlMngtDataTable[]  */

#endif /* end of #ifdef UDS_ENABLE_ROUTINECONTROL */



#ifdef UDS_ENABLE_REQUESTDOWNLOAD  


/* 0x34 RequestDownload  
   Note : this table is located in the rom, can not be changed dynamically
          if a new memory address which is need to download by 0x34 service , 
          then must update this table before build the whole of project again;
                 
 */
UDS_CONFIG_TYPE UDS_ReqDnldMngRecd_t Uds_g_ReqDnldMngTbl[]  =  
{
/*      ReqDnldStartMemAdd         MemorySize                 AccessAttribute             pDataBuf                          pFuncPtrPreDnldChk                    pFuncPtrDnldWrtData       pFuncPtrIsProgFinished  */
/* 0u*/ /* {UDS_C_REQ_DN_ADD_D0000000, UDS_C_REQ_DN_LEN_D0000000, UDS_C_REQ_DN_ATTR_D0000000, UDS_ITF_IMP_DPTR_REQ_DN_D0000000, UDS_ITF_IMP_PRE_DNLD_CHK_FP_D0000000, UDS_ITF_IMP_DNLD_WT_DAT_FP_D0000000, UDS_ITF_IMP_PROG_IS_FINISH_FP_D0000000 }, */
/* 1u*/ /* {UDS_C_REQ_DN_ADD_A0020000, UDS_C_REQ_DN_LEN_A0020000, UDS_C_REQ_DN_ATTR_A0020000, UDS_ITF_IMP_DPTR_REQ_DN_A0020000, UDS_ITF_IMP_PRE_DNLD_CHK_FP_A0020000, UDS_ITF_IMP_DNLD_WT_DAT_FP_A0020000, UDS_ITF_IMP_PROG_IS_FINISH_FP_A0020000 }, */

/*This Line indicate the end of the data table , do not delete */
/*FFu*/{0xFFFFFFFFu,               0x00000000u,               0x0000u,                    NULL,                             NULL,                                 NULL ,                 NULL                      } 

}; /* end of table UDS_CONFIG_TYPE UDS_ReqDnldMngRecd_t Uds_g_ReqDnldMngTbl[]  */

#endif /* end of #ifdef UDS_ENABLE_REQUESTDOWNLOAD */



uint8_t check_DID(uint8_t *checkdata)
{
	uint8_t checkdata_temp;
	uint8_t  Mcu_Configuration_check;
	checkdata_temp = *checkdata;
	if((checkdata_temp != 0x02u)|(checkdata_temp != 0x04u))
	{
		Mcu_Configuration_check = 49;
	}
	return Mcu_Configuration_check;
}


void Uds_Generic_DatMgr_Init(void)
{
}


/*********************************************************************************
* Name: Uds_Generic_DatMgr_SearchTblByKey                                        *
* Description:  Find an index into a table (the searched id is uword             *
*               (16bits)value, or a ubyte(8 bits) value)                         *
* Inputs:  searched ID                                                           *
*			     adress of first ID in table                                           *
*			     size of a table entry                                                 *
* Outputs: index in table for ID found or  UDS_C_IDX_NOT_IN_TBL in case of error *
**********************************************************************************
*/
uint8_t  Uds_Generic_DatMgr_SearchTblByKey (uint16_t                         i_luwKey2Search,    /* searched ID */
                                          UDS_DidDatMngSearchKeyType_t   i_lubSearchKeyType, /* uword(16bits) or ubyte(8bits) */             
                                          uint8_t const *                  iPTbl2LookUp, 		   /* address of first ID in table */
                                          uint8_t                          lub_entrySize )	   /* size of a table entry */
{
	 uint8_t  lub_ndx = UDS_C_IDX_NOT_IN_TBL;
	 uint8_t  lub_response = 0x00u;
	 uint16_t luw_DIDInTbl = 0x0000u;
	 uint16_t luw_Key2Search = 0x0000u;
	 uint16_t luw_EndOfTblValue = UDS_C_DID_END_OF_TBL_FFFF; 
	 
	 luw_Key2Search = i_luwKey2Search; 
   if (i_lubSearchKeyType == KeyTypeIsUINT8) 
   {
       luw_Key2Search    &= 0x00FFu; 
       luw_EndOfTblValue &= 0x00FFu;
   } 
   else 
   {    
   }
  
  
   while (lub_response < lub_ndx )
	 {
	
       if (i_lubSearchKeyType == KeyTypeIsUINT8) 
       {
	         luw_DIDInTbl = (uint16_t)((*iPTbl2LookUp) & 0x00FFu);	         
       } 
       else 
       {    
		       luw_DIDInTbl = (*((uint16_t *)iPTbl2LookUp));
       }
  
   		 if (luw_DIDInTbl == luw_EndOfTblValue )
		   {
			     lub_response = UDS_C_IDX_NOT_IN_TBL ;
			     lub_ndx-- ;
		   }
		   else if ( luw_DIDInTbl == luw_Key2Search)
		   {
			     lub_ndx = 0x00u	;
		   }
		   else
		   {
			     lub_response++;
			     iPTbl2LookUp += lub_entrySize ;
		   }
	 }  /* end of while (lub_response < lub_ndx ) */
	 return lub_response ;
} /* end of Uds_Generic_DatMgr_SearchTblByKey */








#endif /* _UDS_SVC_DATA_MNGR_C */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
