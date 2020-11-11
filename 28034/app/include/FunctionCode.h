//源文件名为:Microsoft Excel - BeiQiC50DaYang.XLS  [兼容模式]
//下列表格建立时间: Friday, Jul 26 2019 09:57:07


 #ifndef _FUNCTIONCODE_H_
 #define _FUNCTIONCODE_H_

/*******************************************************************************************/
 #ifdef  _FUNCTIONCODE_
     #define  _FUNCTIONCODE_DEF_
 #else
     #define  _FUNCTIONCODE_DEF_     extern 
 #endif

#include "DSP2803x_Device.h"

/*******************************************************************************************/
/*共享变量*/
 
 /*功能码属性*/  
 typedef struct{
     uint ignore:1;      //=0可见 =1不可见
     uint modify:1;      //=0不可改写 =1可改写
     uint PLCmodify:1;      //=0不可改写 =1可改写
     uint changed:1;     //=0 未更改  =1已更改
     uint rsv:12;        //保留
     uint16 value;       //功能码值
 }FuncBits;
 
 
 _FUNCTIONCODE_DEF_  FuncBits    *firstip;       //功能码初始指针
 _FUNCTIONCODE_DEF_  FuncBits    *funcip;        //功能码当前指针
 _FUNCTIONCODE_DEF_  FuncBits    *funcipTP;      //功能码临时指针

 _FUNCTIONCODE_DEF_  FuncBits    *funcpointer;       // 上电参shu初始化指针


 typedef struct  {
                FuncBits MenuModeSlt;                        //P00.00
                FuncBits AppDate;                            //P00.01
                FuncBits AutoDate;                           //P00.02
                FuncBits DriveVer;                           //P00.03
                FuncBits BootVer;                            //P00.04
                FuncBits ParaInit;                           //P00.05
                FuncBits ParaCopy;                           //P00.06
                FuncBits MainFrqRef;                         //P01.00
                FuncBits OutFrqRef;                          //P01.01
                FuncBits OutFrq;                             //P01.02
                FuncBits OutVoltage;                         //P01.03
                FuncBits OutCurrent;                         //P01.04
                FuncBits TorqCurrent;                        //P01.05
                FuncBits MagFluxCurrent;                     //P01.06
                FuncBits TorqRef;                            //P01.07
                FuncBits OutTorq;                            //P01.08
                FuncBits MotorPower;                         //P01.09
                FuncBits MaxDriveTorque;                     //P01.10
                FuncBits MaxBraveTorque;                     //P01.11
                FuncBits DCVoltage;                          //P01.12
                FuncBits DetMtrFrq;                          //P01.13
                FuncBits MDIStatus;                          //P01.14
                FuncBits DITermStatus;                       //P01.15
                FuncBits DOTermStatus;                       //P01.16
                FuncBits AI1Volt;                            //P01.17
                FuncBits AI2Volt;                            //P01.18
                FuncBits ConVolt;                            //P01.19
                FuncBits TorqLimit;                          //P01.20
                FuncBits DCCur;                              //P01.21
                FuncBits MCUTemp;                            //P01.22
                FuncBits MotorTemp;                          //P01.23
                FuncBits Speedrpm;                           //P01.24
                FuncBits MtrCtrlSelect;                      //P02.00
                FuncBits MainFrqSourceSlt;                   //P02.01
                FuncBits RunCmdChannel;                      //P02.02
                FuncBits RunDir;                             //P02.03
                FuncBits StopDetectFrq;                      //P02.04
                FuncBits MainFrqDigiSet;                     //P02.05
                FuncBits AccTime1;                           //P02.06
                FuncBits DecTime1;                           //P02.07
                FuncBits MaxOutFrq;                          //P02.08
                FuncBits M1RatedPower;                       //P03.00
                FuncBits M1RatedVoltage;                     //P03.01
                FuncBits M1RatedCurrent;                     //P03.02
                FuncBits M1RatedFrq;                         //P03.03
                FuncBits M1RatedSpd;                         //P03.04
                FuncBits M1PowerFactor;                      //P03.05
                FuncBits M1R1;                               //P03.06
                FuncBits M1X1orLD;                           //P03.07
                FuncBits M1R2orEmf;                          //P03.08
                FuncBits M1XmorLq;                           //P03.09
                FuncBits MotorMagnetCurrent;                 //P03.10
                FuncBits MotorPolePairs;                     //P03.11
                FuncBits MotorSlipFrequency2;                //P03.12
                FuncBits M1Ld;                               //P03.13
                FuncBits M1Lq;                               //P03.14
                FuncBits M1Emf;                              //P03.15
                FuncBits M1OLAlarm;                          //P03.16
                FuncBits M1OLCoeff;                          //P03.17
                FuncBits M1OLTime;                           //P03.18
                FuncBits MotorMode;                          //P03.19
                FuncBits DeratFact2;                         //P03.20
                FuncBits DeratFact1;                         //P03.21
                FuncBits M1OLValue;                          //P03.22
                FuncBits MotorPhase;                         //P03.23
                FuncBits TuneMode;                           //P03.24
                FuncBits SM1TuneCurrent;                     //P03.25
                FuncBits SMIniAng;                           //P03.26
                FuncBits SMZPlsAng;                          //P03.27
                FuncBits PGSlt;                              //P04.00
                FuncBits PGPulsPerR;                         //P04.01
                FuncBits PGDirect;                           //P04.02
                FuncBits PGFilterCoef;                       //P04.03
                FuncBits ResolverPP;                         //P04.04
                FuncBits ResolverTest;                       //P04.05
                FuncBits ResolverAmpTest;                    //P04.06
                FuncBits ResolverAmpSet;                     //P04.07
                FuncBits ResolverCheckOut;                   //P04.08
                FuncBits ResolverCheckNumber;                //P04.09
                FuncBits Rsv50;                              //P04.10
                FuncBits ASR1P;                              //P05.00
                FuncBits ASR1I;                              //P05.01
                FuncBits FieldWeakKp;                        //P05.02
                FuncBits FieldWeakTi;                        //P05.03
                FuncBits AccMax;                             //P05.04
                FuncBits AccJerkStart;                       //P05.05
                FuncBits AccJerkEnd;                         //P05.06
                FuncBits DecMax;                             //P05.07
                FuncBits DecJerkStart;                       //P05.08
                FuncBits DecJerkEnd;                         //P05.09
                FuncBits TorqSpdSelect;                      //P06.00
                FuncBits TorqRefSlt;                         //P06.01
                FuncBits TorqRefChannel;                     //P06.02
                FuncBits TorqKbRef;                          //P06.03
                FuncBits TorAccDecTime;                      //P06.04
                FuncBits SpdLmt1;                            //P06.05
                FuncBits SpdLmt2;                            //P06.06
                FuncBits TorqLmtFwdPos;                      //P06.07
                FuncBits TorqLmtFwdNeg;                      //P06.08
                FuncBits TorqLmtRsvPos;                      //P06.09
                FuncBits TorqLmtRsvNeg;                      //P06.10
                FuncBits SlideSpeedEnter;                    //P07.00
                FuncBits SlideSpeedExit;                     //P07.01
                FuncBits SpdLmtFreq1;                        //P07.02
                FuncBits SpdLmtFreq2;                        //P07.03
                FuncBits IqULimit;                           //P07.04
                FuncBits IqLLmit;                            //P07.05
                FuncBits IqSetUnlim;                         //P07.06
                FuncBits IqAct;                              //P07.07
                FuncBits SlipCutTime;                        //P07.08
                FuncBits SlipCutSpeed;                       //P07.09
                FuncBits CurrLimitPH;                        //P07.10
                FuncBits CurrLimitPL;                        //P07.11
                FuncBits Rsv712;                             //P07.12
                FuncBits Rsv713;                             //P07.13
                FuncBits Rsv714;                             //P07.14
                FuncBits Rsv715;                             //P07.15
                FuncBits Rsv716;                             //P07.16
                FuncBits Mscorrect;                          //P12.00
                FuncBits StopMode;                           //P12.01
                FuncBits CarrierFrq;                         //P12.02
                FuncBits PWMMode;                            //P12.03
                FuncBits ACRSlt;                             //P12.04
                FuncBits ACRP;                               //P12.05
                FuncBits ACRI;                               //P12.06
                FuncBits FanControl;                         //P12.07
                FuncBits DeltaFrqComVolt;                    //P12.08
                FuncBits PreExcitTime;                       //P12.09
                FuncBits DCLinkCtrlVoltSet;                  //P12.10
                FuncBits DCLinkCtrl_Pgain;                   //P12.11
                FuncBits DCLinkCtrl_Itime;                   //P12.12
                FuncBits FluxCtrl_Pgain;                     //P12.13
                FuncBits FluxCtrl_Itime;                     //P12.14
                FuncBits SmWeakenCurr;                       //P12.15
                FuncBits PWMIndexMax;                        //P12.16
                FuncBits PwmIndexLimit;                      //P12.17
                FuncBits RelucTorqAngle;                     //P12.18
                FuncBits P1229;                              //P12.19
                FuncBits Pr1;                                //P13.00
                FuncBits Pr2;                                //P13.01
                FuncBits Pr3;                                //P13.02
                FuncBits Pr4;                                //P13.03
                FuncBits Pr5;                                //P13.04
                FuncBits DisPr1;                             //P13.05
                FuncBits DisPr2;                             //P13.06
                FuncBits DisPr3;                             //P13.07
                FuncBits DisPr4;                             //P13.08
                FuncBits DisPr5;                             //P13.09
                FuncBits CANBand;                            //P15.00
                FuncBits CANAddress;                         //P15.01
                FuncBits CANOverTime;                        //P15.02
                FuncBits CANDiaPeriod;                       //P15.03
                FuncBits CANCtrl;                            //P15.04
                FuncBits CANSpeedRef;                        //P15.05
                FuncBits CANTorqueRef;                       //P15.06
                FuncBits MCUState;                           //P15.07
                FuncBits AlarmDis;                           //P97.00
                FuncBits ErrorListH;                         //P97.01
                FuncBits ErrorListL;                         //P97.02
                FuncBits AlarmCode;                          //P97.03
                FuncBits WarnCode;                           //P97.04
                FuncBits ErrNumber;                          //P97.05
                FuncBits ErrorCode;                          //P97.06
                FuncBits ErrDCVoltage;                       //P97.07
                FuncBits ErrDCCur;                           //P97.08
                FuncBits ErrVmsCtrl;                         //P97.09
                FuncBits ErrMCUState;                        //P97.10
                FuncBits ErrTorqueCmd;                       //P97.11
                FuncBits ErrTorqueFed;                       //P97.12
                FuncBits ErrOutFreq;                         //P97.13
                FuncBits ErrSpeed;                           //P97.14
                FuncBits ErrMCUTemp;                         //P97.15
                FuncBits ErrMotorTemp;                       //P97.16
                FuncBits ErrUd;                              //P97.17
                FuncBits ErrUq;                              //P97.18
                FuncBits ErrIdRef;                           //P97.19
                FuncBits ErrIqRef;                           //P97.20
                FuncBits ErrIdFed;                           //P97.21
                FuncBits ErrIqFed;                           //P97.22
                FuncBits Err12V;                             //P97.23
                FuncBits ErrStateH;                          //P97.24
                FuncBits ErrStateL;                          //P97.25
                FuncBits ErrCurrent;                         //P97.26
                FuncBits ErrMDISts;                          //P97.27
                FuncBits RSV28;                              //P97.28
                FuncBits RSV29;                              //P97.29
                FuncBits RSV30;                              //P97.30
                FuncBits ErrHour;                            //P97.31
                FuncBits ErrSecond;                          //P97.32
                FuncBits ErrMs;                              //P97.33
                FuncBits RSV34;                              //P97.34
                FuncBits SerialNum;                          //P98.00
                FuncBits SoftWareVer;                        //P98.01
                FuncBits RatedCurrent;                       //P98.02
                FuncBits MaxConVoltage;                      //P98.03
                FuncBits MaxDCVoltage;                       //P98.04
                FuncBits MaxOutCurrent;                      //P98.05
                FuncBits FactoryPassWord;                    //F99.00
                FuncBits ModuleSet;                          //F99.01
                FuncBits CusID;                              //F99.02
                FuncBits DCOVLevel;                          //F99.03
                FuncBits WarnLVLevel;                        //F99.04
                FuncBits DCLVLevel;                          //F99.05
                FuncBits OCLevel;                            //F99.06
                FuncBits Imax;                               //F99.07
                FuncBits Ipeak;                              //F99.08
                FuncBits MCUOT;                              //F99.09
                FuncBits WarnMCUOT;                          //F99.10
                FuncBits MCUOTClear;                         //F99.11
                FuncBits MotorSpeedOVFWD;                    //F99.12
                FuncBits WarnMotorSpeedOVFWD;                //F99.13
                FuncBits MotorSpeedOVREV;                    //F99.14
                FuncBits WarnMotorSpeedOVREV;                //F99.15
                FuncBits MotorOTLevel;                       //F99.16
                FuncBits WarnMotorOTLevel;                   //F99.17
                FuncBits Low12V;                             //F99.18
                FuncBits Over12V;                            //F99.21
                FuncBits MotorTempOffset;                    //F99.19
                FuncBits MCUTempOffset;                      //F99.20
                FuncBits FstPwrOnFlg1;                       //F99.22
                FuncBits FstPwrOnFlg2;                       //F99.23
    }sfunccode;
    _FUNCTIONCODE_DEF_  sfunccode Funcode;

/*******************************************************************************************/
#endif

