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
//---------------------------------------------------------------------------
class TFormKiwoom : public TForm
{
__published:	// IDE-managed Components
	TKHOpenAPI *KHOpenAPI1;
	TGroupBox *GroupBox2;
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




private:	// User declarations

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

	__fastcall TFormKiwoom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKiwoom *FormKiwoom;
//---------------------------------------------------------------------------
#endif
