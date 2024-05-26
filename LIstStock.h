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

	//tr 조회
	int iNowMoney;
	double dNowRatio;

	//real 조회
	int iRealMoney;
	double dRealRatio;
	int iRealTradeMoney;
	int iRealVolume;
	int iRealMedo1;
	int iRealMesu1;
	double dRealChegyul;
	int iRealTradeMoneyOLD;

	//1초처리
	int iRealNowSec;
	int iReal1SecChanged;
	int iReal1SecMesuSum;//1백만원단위
	int iReal1SecMedoSum;
	int iReal1SecTradeMoney[10];
	double dReal1SecRatio[10];


	int iBuyTargetPrice;
	int iBuyTargetVolume;
	int iSellTargetPrice;
	int iSellTargetVolume;

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
