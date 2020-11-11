#ifndef _KEYBOARDSCI_H
#define _KEYBOARDSCI_H


#ifdef _KEYBOARDSCI_H_
#define _KEYBOARDSCI_DEF_
#else
#define _KEYBOARDSCI_DEF_ extern
#endif

#ifdef _KEYBOARDSCI_H_

static unsigned char DataTxd[46]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static unsigned char DataTxbuff[46]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static unsigned char DataRxbuff[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static unsigned char DataRxd[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
unsigned int Dataorg=0,Datacal=0,Rxtimecnt=0,Rxtimetmp=0,Rxcnt=0,Deltatime=0,Txtimecnt=0;
unsigned int TxReady=1,RxReady=1,Txnumber=0,delay;
unsigned int Para16,Para32L,Para32H,Para32,Funno,KeyHoldtmr;
unsigned int Address=0,Addressget=0,Contrastbak=5;
unsigned int ParaInit=0,Downerrtimes = 0,Uperrtimes=0,Nobacktimes=0;
unsigned int linex=0;	//lcd lines
unsigned int testL=0,testK=0,timecnt=0,LCDtestflag=0;
unsigned int Num32=0,Errortimes=0;		//32Î»²ÎÊý

FuncBits *firaddress;
FuncBits *nowaddress;

int ParaDownok=0,ParaUpok=0,ParaVerchk=0,Para16downok=0,Para16upok=0,Para32upok=0;
int LCDtestfinish=0;

#endif


_KEYBOARDSCI_DEF_  void SCITIMECHK(void);
_KEYBOARDSCI_DEF_  void READTOSEND(void);



#endif

