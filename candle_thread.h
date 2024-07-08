//---------------------------------------------------------------------------

#ifndef candle_threadH
#define candle_threadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "LIstStock.h"
#include "global.h"
//---------------------------------------------------------------------------
class ThreadCandle : public TThread
{
private:


protected:
	void __fastcall Execute();
public:

	void __fastcall Update1Min(TStock* object, String sLastTime, int iNow, double dRatio);
	double __fastcall GetCandleRatio(int iStart, int iEnd);
	void __fastcall CheckMovingAvg(TStock* object, int iType);

	void __fastcall CheckBolingerCenter(TStock* object);
    void __fastcall Check1MinBolinger(TStock* object);

	__fastcall ThreadCandle(bool CreateSuspended);
};
//---------------------------------------------------------------------------
extern ThreadCandle* g_ThreadCandle;
#endif
