/***************************************************************************
  Name:         DrivePublicVar.h
****************************************************************************/

extern unsigned int    Param_MotorStatorResist;

extern unsigned int    Param_MotorPowerFactor;

extern unsigned int    Param_MotorStatorLeakInduct;
extern unsigned int    Param_MotorRotorLeakInduct;
extern unsigned int    MotorLeakInductD;
extern unsigned int    MotorDeltaLd;
extern unsigned int    MotorLeakInductQ;
extern unsigned int    Param_MotorMutualInductance;
extern unsigned int    Param_MotorKeFactor;
extern unsigned int    MotorPolePairs;

extern unsigned int    Param_PWMIndexMax;
extern unsigned int    PwmIndexLimit;

extern unsigned int    InjectStartSpeed;
extern unsigned int    InjectEndSpeed;

extern unsigned int    TorqKpAdjSpd1;             // newLG
extern unsigned int    TorqKpAdjSpd2;             // newLG

extern unsigned int    Param_CurrentCtrl_PGain;
extern unsigned int    Param_CurrentCtrl_ITime;
extern unsigned int    Param_SpeedCtrl_PGain;
extern unsigned int    Param_SpeedCtrl_ITime;

extern unsigned int    Param_DCLinkCtrlVoltSet;
extern unsigned int    Param_DCLinkCtrl_PGain;
extern unsigned int    Param_DCLinkCtrl_ITime;
   
extern unsigned int    Param_FluxCtrl_PGain;
extern unsigned int    Param_FluxCtrl_ITime;

extern unsigned int    Param_MotorInitAngle;

extern unsigned int    SmFieldWeakeningCurrent;

extern unsigned int    Param_FieldWeakCtrl_PGain;
extern unsigned int    Param_FieldWeakCtrl_ITime;

extern unsigned int    Imax;
extern unsigned int    ImaxPeak;
extern unsigned int    Nmax;
extern unsigned int    udc_rated;

extern unsigned int    SM_StartFinish;

extern unsigned int    StartFreqHoldFinished;
extern unsigned int    StartFreqStableStep;

extern  long    SenLessFilter;

extern int          Param_IphaseU;
extern int          Param_IphaseV;
extern int          Param_IphaseW;

extern unsigned int    Param_AmpActDCLinkVolt;

extern unsigned int    M_svm;
extern unsigned int    n_period_1;

extern unsigned int  VoltMargin;
extern unsigned int  VqSetLimByMargin;

extern unsigned int    CMP0;
extern unsigned int    CMP1;
extern unsigned int    CMP2;

extern int  DeadTimeInPules;

extern long   Param_SpeedSetValue;
extern long   Param_SpeedFwdLimit;
extern long   Param_SpeedRevLimit;

extern long    TIMECOUNT_1MS;
extern long    OUTPUT_FREQ;

extern unsigned int    INJECT_MODE;             // P13.00  转矩补偿使能,  0:不补偿, 2:补偿
extern unsigned int    CurrentTorqGain;         //
extern unsigned int    INJECT_TORQUE;           // P13.01, 转矩补偿基准值, in 1%

extern unsigned int    ModulationMode;
//==================================================================
extern int              Param_SpeedCtrlOut;
extern int              Param_TrqAddValue;
extern unsigned int     InjectAngle;
extern unsigned int     OffsetAngleTemp;
extern unsigned int     Rho_estMechanical;
extern unsigned int     Param_Rho;
extern unsigned int     Test_Rho;
extern long             Speed_daxisFilt;
extern long             Speed_qaxisFilt;
extern long             SpeedSum;
extern unsigned long    ResonanceAngle;
extern long             SpeedSumFilt;
extern long			    SpeedStart;      // TCL
extern long             SpeedTabTemp;
extern long             SpeedCosPhiFilt;
extern unsigned int     PhiIndex;
extern unsigned int     SpeedCosIndex;
extern int    		    SpeedCtrlOutFilt;
extern unsigned int     COMP_DELAY_TIME;
extern unsigned int     SpeedKp1;
extern unsigned int     SpeedKp2;
extern unsigned int     SpeedTi1;
extern unsigned int     SpeedTi2;
extern int              Param_IdSetLimited;
extern int              Param_IqSetLimited;
extern int              Param_IdAct;
extern int              Param_IqAct;
extern unsigned long    VibrateSpeedBaseSquare;
extern unsigned int     VibrateSpeedBase;
extern unsigned int     VibSpdLLimit;
extern unsigned int     VibSpdULimit;
extern unsigned int     TORQ_GAIN_LowLim;
extern unsigned int     TORQ_GAIN_UpLim;
extern unsigned long    TorqGainAdjustTime;
extern unsigned int     InitTorqGain;
extern unsigned int     TorqCompGain1;         // newLG
extern unsigned int     TorqCompGain2;         // newLG
extern unsigned int     Param_FluxActValue; 
extern unsigned int     CurrentLoopDelayCompen;
extern long             Param_SpeedActValue;
extern unsigned int     RevDetectEn;
extern long				Param_PsiAlpha;
extern long				Param_PsiBeta;
extern int              RevDetectValue;

extern unsigned int Param_AutotuningCtrl;
extern unsigned int         Param_Reg_ctrl;

//==================================================================
extern unsigned int    Param_MotorNomCurrent;
extern unsigned int    Param_MotorNomVolt;
extern unsigned int    Param_MotorNomPower;
extern unsigned int    Param_MotorNomSpeed;
extern unsigned int    Param_MotorNomFrequency;
extern unsigned int    Param_MotorSlipFrequency2;
extern unsigned int    Param_MotorPolePairs;
extern unsigned int    Param_TimeRotorActValue;
extern unsigned int    Param_MotorMagnetCurrent;

extern unsigned int    Param_CalcMagnetCurrent;

//==================================================================
extern int    Param_VdSet;
extern int    Param_VqSet;

extern int    Param_IdAct;
extern int    Param_IqAct;

extern unsigned long        Param_Enc1MechAngle;
extern long Rho2;
extern unsigned int         Param_FluxSetValue;

extern int                 Param_Enc1TrackA;
extern int                 Param_Enc1TrackB;
extern unsigned int        Enc1AbPhi;
extern long                Param_Enc1ActSpeed;
extern long       		   Param_Enc1DeltaPhi_D;

extern int                 Param_TrqSetValue;
extern unsigned int 	   Shadw_Pt_enc1;
extern unsigned int        CoreFlag_CtrlMode;
extern unsigned int        ExcitationTime;
extern unsigned int        Param_Enc1PulsesPerRev;

extern long * SinTab;
extern long             PosNeg00007FFF[2]; 					  //plus a. minus 0x7FFF 
extern long             PosNeg7FFFFFFF[4];        //plus a. minus 0x7FFFFFFF
extern long             ZeroLimit; 
extern int              IqULimitGen[2];
extern long             Param_SpeedSet_ULim;
extern long             Param_SpeedSet_LLim;
extern int              Param_TrqDirectULim;
extern int              Param_TrqDirectLLim;
extern int              Param_IqULimit;
extern int              Param_IqLLimit;
extern int              SinRho_est;
extern int              CosRho_est;
extern unsigned int     PrSqrt3by2;
extern unsigned int     InvPrSqrt3by2;
extern unsigned int     Param_VdqLimit;
extern unsigned int     SampleTimeILoop;
extern unsigned int     MotorNomTrqCurrent;
extern unsigned long    MotorNomTrq;              //in 0,001 Nm
extern int   		    US_ALPHA;
extern int   		    US_BETA;
extern long				Param_Int_n_HD;
extern unsigned int     CurrLimitPH;
extern unsigned int     CurrLimitPL;
extern unsigned int     Param_EncMode;
extern unsigned int     DriveNomCurrent;
extern unsigned int     SEARCH_INIT_ANGLE_FINISHED;
extern unsigned int     SearchAngControl;
extern unsigned int     Param_MotorSearchAngleStatus;
extern unsigned int     Param_MotorSearchAngError;
extern unsigned long	Param_Enc1pos_D;
extern unsigned int 	Enc1RemainOld;
extern long				Param_Enc1DeltaPhi_D;
//extern int				RelucTorqCoeff1;
//extern int				RelucTorqCoeff2;
extern unsigned int		Param_Reg_ctrl2;

extern int           Param_IdSetUnlim;

extern  long   PowerElectric;
extern  long   PowerRsAlpha;
extern  long   PowerRsBeta;

