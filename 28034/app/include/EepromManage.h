#ifndef EepromManage_VARIABLES
#define EepromManage_VARIABLES

#ifdef __cplusplus
extern "C" {
#endif



#define RET_OK		0
#define RET_ERROR	1


#define	EPERR_WAIT_TIME		200

//128Kbit(16K bytes) EEPROM,Max address is 16384
#define PARA_ZONE_MAX			3800

#define ERROR_SAVE_ORDER		3950

#define ERROR_NUM_ADR			4092
#define ERROR_ZONE_ADR			4096		//64的整倍数

#define FIRST_ERROR_ZONE_ADR			12288		//64的整倍数

#define BOOT_LOG			0x2000			//8192

#define APP_LOG			0x2004			//12288

#define DID_ADR			0x2100

#define I2C_SLAVE_ADDR      0x50

#define MAX_ERROR_LOG		30
#define MUL_MAX_ERROR_LOG   (MAX_ERROR_LOG * 2)

#define MAX_ERR_NUMBER		32

#ifdef	EPROMMANAGE_H
	#define	EpExtern
#else
	#define EpExtern	extern
#endif

EpExtern uint16 FlagShowErr,FlagClrErr;
EpExtern Uint16	SizeErrLog;
EpExtern Uint16	StClrErrLog;
EpExtern Uint16 StReadErrLog;
EpExtern Uint16 GetErrOrderNum;
EpExtern Uint16 ErrorNumber;
EpExtern Uint16 ErrLogStatus[MAX_ERROR_LOG];
EpExtern Uint16 FlagUpdateErrorStatus;


EpExtern void InitEeprom(void);
EpExtern int16 WriteBootPara(uint16 value);


EpExtern  int16 WriteBootPara(uint16 value);
EpExtern  void DealEpData();

EpExtern  uint16 NoticeClearError();

EpExtern uint16 GetErrorTypeofNumber(uint16 x);

EpExtern void FuncManage_ReadParameters(void);


#ifdef	EPROMMANAGE_H

Uint16 ReadEeprom(Uint16 Address);
Uint16 WriteEeprom(Uint16 Address,Uint16 WPara);
Uint16 Read2Para16Bit(Uint16 Address,Uint16 *data);
int CheckEEprom();
Uint16 Save16Func(Uint16 Index16);
void LoadError(ErrorLog_t* Err,Uint16 Index);
void SaveErrorLog();
void ClearErrLog();
void ShowErrLog();
void SaveParameters();
Uint16 WritePageEeprom(Uint16 Address,Uint16 UintNumber,Uint16 *data);
void GetErrLog(void);
void WriteUds(void);
void ReadUds(void);
void WriteDtcOccHisOrder(void);
void ReadDtcOccHisOrder(void);
void MakePreDtcStatus(void);
uint16 UpdateErrorStatus();
void SaveErrorIndex(ErrorLog_t* Err,uint16 Index);
extern Uint16 CurrDtcOccOrder(Uint16 CurrDtcSaveOrder, Uint16 pErrorNumber);


unsigned long *longfuncpointer; 
volatile uint16 wdata,rdata;
ErrorLog_t	ErrShow;

#endif


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif    // end of TRIP_VARIABLES definition
