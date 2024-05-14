//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "KHOpenAPILib_OCX.h"
#include <Vcl.OleCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TGroupBox *GroupBox1;
	TButton *Button2;
	TStringGrid *StringGridList;
	TButton *Button3;
	TStringGrid *StringGridLiteItem;
	TMemo *Memo1;
	TKHOpenAPI *KHOpenAPI1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall StringGridListClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall StringGridListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall KHOpenAPI1EventConnect(TObject *Sender, long nErrCode);
	void __fastcall KHOpenAPI1ReceiveChejanData(TObject *Sender, WideString sGubun,
          long nItemCnt, WideString sFIdList);
	void __fastcall KHOpenAPI1ReceiveConditionVer(TObject *Sender, long lRet, WideString sMsg);
	void __fastcall KHOpenAPI1ReceiveInvestRealData(TObject *Sender, WideString sRealKey);
	void __fastcall KHOpenAPI1ReceiveRealData(TObject *Sender, WideString sRealKey,
          WideString sRealType, WideString sRealData);
	void __fastcall KHOpenAPI1ReceiveTrCondition(TObject *Sender, WideString sScrNo,
          WideString strCodeList, WideString strConditionName, int nIndex,
          int nNext);
	void __fastcall KHOpenAPI1ReceiveTrData(TObject *Sender, WideString sScrNo,
          WideString sRQName, WideString sTrCode, WideString sRecordName,
          WideString sPrevNext, long nDataLength, WideString sErrorCode,
          WideString sMessage, WideString sSplmMsg);













private:	// User declarations

	int m_iSelectRowList;
	String m_sSelectCondition;
	int m_iSelectIndex;

	WideString __fastcall GetScrNum();

	void __fastcall GridInitList();
	void __fastcall GridInitItem();


    void __fastcall UpdateConditionList(String sNo, String sName);
	void __fastcall RequestCondition(String sNo, String sName);

	void __fastcall UpdateConditionItem(String sNo, String sConditionName, String sCode);

public:		// User declarations



	void __fastcall AddLog(String sMsg);

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
