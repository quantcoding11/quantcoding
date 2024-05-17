//---------------------------------------------------------------------------

#ifndef LIstStockH
#define LIstStockH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <ComCtrls.hpp>

class TStock : public TObject
{
private:

protected:

public:

	String sStockID;
	String sStockCode;
	String sStockName;

	int iTradeStatus;

	String sOrderCode;

	int iBuyTarget;
	int iBuyVolume;
	int iSellTarget;
	int iSellVolume;

	int iBoughtVolume;
	int iBoughtMoney;

	int iSoldVolume;
	int iSoldMoney;

	bool bSellTry;


};


//---------------------------------------------------------------------------
class TStocks : public TObject
{
public:
	TObjectList* objectList;

public:
	void __fastcall Add(TStock* object);
    void __fastcall Delete(int nIndex);
    void __fastcall Clear();
	bool __fastcall CheckAdd(TStock* objectNew);


    __fastcall TStocks();
    __fastcall ~TStocks();
};
//---------------------------------------------------------------------------

extern TStocks* g_StockList;

#endif
