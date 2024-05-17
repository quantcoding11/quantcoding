//---------------------------------------------------------------------------

#ifndef globalH
#define globalH
//---------------------------------------------------------------------------

#include <vcl.h>



#define _BUY_READY_0				0

#define _BUY_NEW_1		  			1
#define _BUY_NEW_ACCEPTING_10		10
#define _BUY_NEW_ACCEPTED_11		11
#define _BUY_NEW_FINISH_12          12

#define _SELL_NEW_2					2
#define _SELL_NEW_ACCEPTING_20		20
#define _SELL_NEW_ACCEPTED_21		21

#define _BUY_CANCEL_3				3
#define _BUY_CANCEL_ING_30			30

#define _SELL_CANCEL_4				4
#define _SELL_CANCEL_ING_40			40

#define _BUY_MODIFY_5				5
#define _BUY_MODIFY_ING_50			50
#define _BUY_MODIFYED_51			51

#define _SELL_MODIFY_6				6
#define _SELL_MODIFY_ING_60			60
#define _SELL_MODIFYED_61			61

#define _BUY_IMMEDIATE_71			7
#define _BUY_IMMEDIATE_ING_72		72

#define _SELL_IMMEDIATE_81			8
#define _SELL_IMMEDIATE_82			82

#define _TRADE_FAIL_99				99
#define _TRADE_FINISH_100			100



extern String g_AppDir;
extern bool g_bClosing;

extern String g_sKiwoomAcountNo;


void __fastcall DebugLog(String title, AnsiString Msg);


#endif


