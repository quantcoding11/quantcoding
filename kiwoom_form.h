//---------------------------------------------------------------------------

#ifndef kiwoom_formH
#define kiwoom_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "KHOpenAPILib_OCX.h"
#include <Vcl.OleCtrls.hpp>

#include "global.h"
#include "ListStock.h"
//---------------------------------------------------------------------------
class TFormKiwoom : public TForm
{
__published:	// IDE-managed Components
	TKHOpenAPI *KHOpenAPI1;
	TGroupBox *GroupBox2;
	TEdit *EditStockCode;
	TLabel *Label1;
	TEdit *EditPrice;
	TLabel *Label2;
	TCheckBox *CheckBoxMarketPrice;
	TEdit *EditVolume;
	TLabel *Label3;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TMemo *Memo1;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *EditStockCode2;
	TEdit *EditPrice2;
	TCheckBox *CheckBoxMarketPrice2;
	TEdit *EditVolume2;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TEdit *EditObject;
	TGroupBox *GroupBox3;
	TButton *Button16;
	TButton *Button15;
	TButton *Button14;
	TButton *Button17;
	TButton *Button18;
	TLabel *LabelTop;
	TLabel *LabelTrade;
	void __fastcall KHOpenAPI1EventConnect(TObject *Sender, long nErrCode);
	void __fastcall KHOpenAPI1ReceiveConditionVer(TObject *Sender, long lRet, WideString sMsg);
	void __fastcall KHOpenAPI1ReceiveTrCondition(TObject *Sender, WideString sScrNo,
          WideString strCodeList, WideString strConditionName, int nIndex,
          int nNext);
	void __fastcall KHOpenAPI1ReceiveChejanData(TObject *Sender, WideString sGubun,
          long nItemCnt, WideString sFIdList);
	void __fastcall KHOpenAPI1ReceiveInvestRealData(TObject *Sender, WideString sRealKey);
	void __fastcall KHOpenAPI1ReceiveRealData(TObject *Sender, WideString sRealKey,
          WideString sRealType, WideString sRealData);
	void __fastcall KHOpenAPI1ReceiveTrData(TObject *Sender, WideString sScrNo,
          WideString sRQName, WideString sTrCode, WideString sRecordName,
          WideString sPrevNext, long nDataLength, WideString sErrorCode,
          WideString sMessage, WideString sSplmMsg);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall KHOpenAPI1ReceiveMsg(TObject *Sender, WideString sScrNo, WideString sRQName,
          WideString sTrCode, WideString sMsg);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);




private:	// User declarations
	String m_sOrderNo;

	WideString __fastcall GetScrNum();

    void __fastcall AddLog(String sMsg);

public:		// User declarations


	int __fastcall BuyStockMarketPrice(String sStockCode, int iVolume);
	int __fastcall SellStockMarketPrice(String sStockCode, String sOrderNo, int iVolume);

	int __fastcall BuyStock(String sStockCode, int iPrice, int iVolume);
	int __fastcall BuyChange(String sStockCode, String sOrderNo, int iPrice, int iVolume);
	int __fastcall BuyCancel(String sStockCode, String sOrderNo, int iVolume);

	int __fastcall SellStock(String sStockCode, String sOrderNo, int iPrice, int iVolume);
	int __fastcall SellChange(String sStockCode, String sOrderNo, int iPrice, int iVolume);
	int __fastcall SellCancel(String sStockCode, String sOrderNo, int iVolume);

    void __fastcall UpdateStockInfo(String sStockCode, String sStockName, String sOrderCode,
		int iStatus, String sType, String sTradePrice, String sTradeVolume, String sOrderVolume);
	void __fastcall UpdateStockVolume(String sStockCode, String sStockName, String sTotalVolume, String sHoldVolume);


	void __fastcall RequestExpectTop(int index);
	void __fastcall RequestTradeMoneyTop(int index);
	void __fastcall RequestYesterdayTradeTop(int index);

	void __fastcall RequestRealTimeData(String sStockCode);

	__fastcall TFormKiwoom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKiwoom *FormKiwoom;
//---------------------------------------------------------------------------
#endif
