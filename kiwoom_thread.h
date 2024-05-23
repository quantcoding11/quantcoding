//---------------------------------------------------------------------------

#ifndef kiwoom_threadH
#define kiwoom_threadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "LIstStock.h"
#include "global.h"
#include "kiwoom_form.h"
//---------------------------------------------------------------------------
class ThreadKiwoom : public TThread
{
private:

	void __fastcall BuySellLogic(TStock* object);


protected:
	void __fastcall Execute();
public:

    void __fastcall UpdateStockInfo(String sStockCode, String sStockName, String sOrderCode,
	int iStatus, String sType, String sTradePrice, String sTradeVolume,	String sOrderVolume);

	void __fastcall UpdateStockVolume(String sStockCode,
		String sStockName, String sTotalVolume, String sHoldVolume);

	__fastcall ThreadKiwoom(bool CreateSuspended);
};
//---------------------------------------------------------------------------

extern ThreadKiwoom* g_ThreadKiwoom;
#endif
