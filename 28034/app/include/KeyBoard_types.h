

#ifndef _RTW_HEADER_KeyBoard_types_h_
#define _RTW_HEADER_KeyBoard_types_h_
#include "main.h"
#ifndef _CSC1_KEYBOARD_CHARTSTRUCT_
#define _CSC1_KEYBOARD_CHARTSTRUCT_

typedef struct {
  int32 Stopcntbak;
  Uint32 Led;
  Uint32 LowerValue;
  Uint32 Panelcnt;
  Uint32 T5minCnt;
  Uint32 UpperValue;
  Uint32 lTemp[5][1];
  int16 F01cnt;
  Uint16 DnKeyCnt;
  Uint16 ErrCodeBak;
  Uint16 ErrIndex;
  Uint16 ErrTimeCnt;
  Uint16 F01RefrCnt;
  Uint16 FlagFromErr;
  Uint16 FuncECnt;
  Uint16 GroupIgnore[6];
  Uint16 KeyValueBak;
  Uint16 MaxFlicker;
  Uint16 PanelLightCnt;
  Uint16 PanelSwitchcnt;
  Uint16 Panelflag;
  Uint16 Poffflag;
  Uint16 RefreshCnt;
  Uint16 ShiftPress;
  Uint16 T3sCnt;
  Uint16 UnitBak;
  Uint16 UnitLightCnt;
  Uint16 UpKeyCnt;
  Uint16 alarmcnt;
  Uint16 alarmcntlcd;
  Uint16 b_j;
  Uint16 b_lTemp[5][1];
  Uint16 b_line4cnt;
  Uint16 unlockcnt; //lxy100330 add
  Uint16 lockcnt; //lxy100330 add
  Uint16 locktime; //lxy100330 add
  Uint16 locklastvalue; //lxy100330 add
  Uint16 locksetdistime; //lxy100331 add
  Uint16 dblockcnt; //lxy100331 add 调试密码相关变量
  Uint16 dblocktime; //lxy100331 add
  Uint16 dblocklastvalue; //lxy100331 add
  Uint16 dblocksetdistime; //lxy100331 add
  Uint32 dbT5minCnt;//lxy100401 add
  Uint16 curpos;
  Uint16 dot;
  Uint16 dotBak;
  Uint16 dotLast;
  Uint16 firstinit;
  Uint16 flicker;
  Uint16 flickerBak;
  Uint16 flickertemp;
  Uint16 i;
  Uint16 j;
  Uint16 line4cnt;
  Uint16 poffcnt;
  Uint16 pofftime;
  Uint16 pos[2][1];
  Uint16 positemp;
  Uint16 uKeyUnlockCnt;
  Uint16 uKeylockCnt;
  Uint16 upper1;
  Uint16 is_DataDisplay : 2;
  Uint16 is_Display : 2;
  Uint16 is_Normal : 2;
  Uint16 is_ParaAdjust : 2;
  Uint16 is_RSDisplay : 2;
  Uint16 EnterPress : 1;
  Uint16 NeedUp : 1;
  Uint16 RunStsBak : 1;
  Uint16 T5min : 1;
  Uint16 UnitFlicker : 1;
  Uint16 modifyLast : 1;
  Uint16 is_active_DataDeal : 1;
  Uint16 is_active_Display : 1;
  Uint16 is_active_c1_KBManage : 1;
  Uint16 userlock_ok : 1; //lxy100330 用户密码锁成功标志
} CSc1_KeyBoard_ChartStruct;

#endif                                  /* _CSC1_KEYBOARD_CHARTSTRUCT_ */

#endif                                  /* _RTW_HEADER_KEYBOARD_types_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
