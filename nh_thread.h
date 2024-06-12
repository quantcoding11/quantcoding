//---------------------------------------------------------------------------

#ifndef nh_threadH
#define nh_threadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "LIstStock.h"
#include "global.h"

//---------------------------------------------------------------------------
class ThreadNH : public TThread
{
private:
protected:
	void __fastcall Execute();
public:


	void __fastcall UpdateStockData(String sStockCode, String sStockName, String sYesterday, String sKOSPI);


	void __fastcall UpdateRealData(String sStockCode, String sTime, String sRealMoney, String sSign,
		String sRealRatio, String sChange, String sRealVolume, String sMoVolume, String sRealMedo1, String sRealMesu1);


	__fastcall ThreadNH(bool CreateSuspended);
};
//---------------------------------------------------------------------------

extern ThreadNH* g_ThreadNH;
#endif
