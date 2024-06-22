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

	int iYesterdayMoney;
	String sKOSPI_KOSDAQ;

	//tr 조회
	int iNowMoney;
	double dNowRatio;

	//real 조회
	volatile int iRealMoney;
	double dRealRatio;
	int iRealTradeMoney;
	int iRealVolume;
	int iRealMedo1;
	int iRealMesu1;
	double dRealChegyul;
	int iRealTradeMoneyOLD;
	double dRealMaxRatio;
	String sRealTimeMinute;//xx:xx
	String sRealTimeMinuteOLD;

	//1초처리
	int iRealNowSec;
	int iReal1SecChanged;
	int iReal1SecMesuSum;//1백만원단위
	int iReal1SecMedoSum;
	int iReal1SecTradeMoney[10];
	double dReal1SecRatio[10];
	double dReal1SecChe[10];

	int iReal10SecTradeMoneyDelta;
	double dReal10SecRatioDelta;
	double dRealUpRatioDelta;

	//1분 캔들
    int iReal1MinChanged;
	int iCandle1MinStart[10];
	int iCandle1MinTop[10];
	int iCandle1MinBottom[10];
	int iCandle1MinEnd[10];
    double dCandle1MinLength[10];
	double dCandle1MinRatio[10];

	//tick count
	volatile int iReal1SecTickSum;
	int iReal1SecTickCount;

	//silent
	bool bEvent1SecCheck;
	int iEvent1SecSilentCount;
	int iEventNowSec;

	int iBuyTargetPrice;
	int iBuyTargetVolume;
	int iSellTargetPrice;
	int iSellTargetVolume;

	int iBoughtVolume;
	int iBoughtMoney;

	int iSoldVolume;
	int iSoldMoney;


	bool bSellTry;

    //장초반 급등주 찾기
	bool bPattern1Find;
	bool bPattern1Clear;



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
