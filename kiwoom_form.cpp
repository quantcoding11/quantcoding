//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "kiwoom_form.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KHOpenAPILib_OCX"
#pragma resource "*.dfm"
TFormKiwoom* FormKiwoom;
//---------------------------------------------------------------------------
__fastcall TFormKiwoom::TFormKiwoom(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
WideString __fastcall TFormKiwoom::GetScrNum()
{
    static int iscrum = 5000;

    WideString aa;
    if (iscrum < 5100)
        iscrum++;
    else
        iscrum = 5000;

    aa = IntToStr(iscrum);
    return aa;
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1EventConnect(
	TObject* Sender, long nErrCode)

{
	String sAccount;
	int iAccount = 0;

	if (nErrCode == 0) {
		FormMain->AddLog("kiwoom login ok");
	} else {
		FormMain->AddLog("kiwoom login failed ");
	}

	Close();

	//���� ���� ��û
	sAccount = KHOpenAPI1->GetLoginInfo("ACCLIST");


    TStringList* SL = new TStringList;
    int iLine;

	try {
        SL->Delimiter = ';';
        SL->DelimitedText = sAccount;

		iLine = SL->Count;

        for (int i = 0; i < iLine; i++) {
			if (SL->Strings[i] != "") {
				iAccount++;
				g_sKiwoomAcountNo = SL->Strings[i];

            }
        }
    } __finally
    {
        delete SL;
	}



	if(iAccount > 1){
		FormMain->AddLog("���¹�ȣ ���� �ʿ� (���߰���) " +g_sKiwoomAcountNo);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveConditionVer(
    TObject* Sender, long lRet, WideString sMsg)
{
    //���ǽ�

    if (lRet != 1) {
        FormMain->AddLog("��ȸ ����");
    }

    String conditionList;

    //���ǽ� ���
    conditionList = KHOpenAPI1->GetConditionNameList();

    //    001^abc;002^abc;000^abc

    TStringList* SL = new TStringList;
    int iLine;

    try {
        SL->Delimiter = ';';
        SL->DelimitedText = conditionList;

        iLine = SL->Count - 1;
        for (int i = 0; i < iLine; i++) {
            TStringList* temp = new TStringList;

            temp->Delimiter = '^';
            temp->DelimitedText = SL->Strings[i];

            FormMain->UpdateConditionList(temp->Strings[0], temp->Strings[1]);

            delete temp;
        }
    } __finally
    {
        delete SL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveTrCondition(TObject* Sender,
    WideString sScrNo, WideString strCodeList, WideString strConditionName,
    int nIndex, int nNext)
{
    //���� ����

    TStringList* SL = new TStringList;
    int iLine;

    //�����ڵ� ����Ʈ�� �� �����ڵ尡 ';'�� ���еǼ� ���޵˴ϴ�.

    WideString sCode;
    WideString sName;

    try {
        SL->Delimiter = ';';
        SL->DelimitedText = strCodeList;

        iLine = SL->Count;

        for (int i = 0; i < iLine; i++) {
            if (SL->Strings[i] != "") {
                sCode = SL->Strings[i];

				FormMain->UpdateConditionItem(IntToStr(i), strConditionName, sCode);
            }
        }
    } __finally
    {
        delete SL;
    }

    if (nIndex == 2) { //�����ִ�
        KHOpenAPI1->SendCondition(
            sScrNo, strConditionName, FormMain->m_iSelectIndex, 0);
    } else {
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveChejanData(
    TObject* Sender, WideString sGubun, long nItemCnt, WideString sFIdList)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveInvestRealData(
    TObject* Sender, WideString sRealKey)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveRealData(TObject* Sender,
    WideString sRealKey, WideString sRealType, WideString sRealData)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveTrData(TObject* Sender,
    WideString sScrNo, WideString sRQName, WideString sTrCode,
    WideString sRecordName, WideString sPrevNext, long nDataLength,
    WideString sErrorCode, WideString sMessage, WideString sSplmMsg)
{
    //

    FormMain->AddLog(sRQName);

    if (sRQName == "") {
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::AddLog(String sMsg)
{
    DebugLog("kiwoom", sMsg);
}
//---------------------------------------------------------------------------
//���尡 �ż�
int __fastcall TFormKiwoom::BuyStockMarketPrice(String sStockCode, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;
    WideString wBuyCode = "1"; //
    WideString wHogaGb = "03"; //���尡
    WideString wOrgOrderNo = "";

    int iBuy;

    AddLog("BuyStockMarketPrice > " + sStockCode + "," + IntToStr(iVolume));

    // �ֽ��ֹ�
    int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 1,
		wStockCode, iVolume, 0, wHogaGb, wOrgOrderNo);

	return lRet;

}
//---------------------------------------------------------------------------
//���尡 �ŵ�
int __fastcall TFormKiwoom::SellStockMarketPrice(String sStockCode, String sOrderNo, int iVolume)
{

    WideString wRQName = "�ֽ��ֹ�";

	WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

	WideString wHogaGb = "03";//���尡
    WideString wOrgOrderNo = sOrderNo;

	AddLog("SellStockMarketPrice > " + sStockCode +","+ sOrderNo +","+ IntToStr(iVolume));

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								2, wStockCode, iVolume,
								0, wHogaGb, wOrgOrderNo);

	return lRet;
}
//---------------------------------------------------------------------------
//������ �ż�
int __fastcall TFormKiwoom::BuyStock(String sStockCode, int iPrice, int iVolume)
{

	WideString wRQName = "�ֽ��ֹ�";

	WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

	WideString wHogaGb = "00";
	WideString wOrgOrderNo = "";

	AddLog("BuyStock > " + sStockCode +","+ IntToStr(iPrice) +","+ IntToStr(iVolume));

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								1, wStockCode, iVolume,
								iPrice, wHogaGb, wOrgOrderNo);

	return lRet;
}
//---------------------------------------------------------------------------
//�ż� ����
int __fastcall TFormKiwoom::BuyChange(String sStockCode, String sOrderNo, int iPrice, int iVolume)
{

    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;


	AddLog("BuyChange > " + sStockCode +","+ sOrderNo +","+ IntToStr(iPrice) +","+ IntToStr(iVolume) );

    // �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								5, wStockCode, iVolume,
								iPrice, wHogaGb, wOrgOrderNo);

	return lRet;
}
//---------------------------------------------------------------------------
//�ż� ���
int __fastcall TFormKiwoom::BuyCancel(String sStockCode, String sOrderNo, int iVolume)
{

	WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

	WideString wHogaGb = "00";
	WideString wOrgOrderNo = sOrderNo;


	AddLog("BuyCancel > " + sStockCode +","+ sOrderNo +","+ IntToStr(iVolume) );

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								3, wStockCode, iVolume,
								0, wHogaGb, wOrgOrderNo);

	return lRet;

}
//---------------------------------------------------------------------------
//������ �ŵ�
int __fastcall TFormKiwoom::SellStock(String sStockCode, String sOrderNo, int iPrice, int iVolume)
{

	WideString wRQName = "�ֽ��ֹ�";

	WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

	WideString wHogaGb = "00";
	WideString wOrgOrderNo = sOrderNo;

	AddLog("SellStock > " + sStockCode +","+ sOrderNo +","+ IntToStr(iPrice) +","+ IntToStr(iVolume));

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								2, wStockCode, iVolume,
								iPrice, wHogaGb, wOrgOrderNo);

	return lRet;
}
//---------------------------------------------------------------------------
//�ŵ� ����
int __fastcall TFormKiwoom::SellChange(String sStockCode, String sOrderNo, int iPrice, int iVolume)
{

    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;


	AddLog("SellChange > " + sStockCode +","+ sOrderNo +","+ IntToStr(iPrice) +","+ IntToStr(iVolume) );

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								6, wStockCode, iVolume,
								iPrice, wHogaGb, wOrgOrderNo);

	return lRet;

}
//---------------------------------------------------------------------------
//�ŵ� ���
int __fastcall TFormKiwoom::SellCancel(String sStockCode, String sOrderNo, int iVolume)
{

    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
	WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

	AddLog("SellCancel > " + sStockCode +","+ sOrderNo +","+ IntToStr(iVolume));

	// �ֽ��ֹ�
	int lRet = -1;

	lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode,
								4, wStockCode, iVolume,
								0, wHogaGb, wOrgOrderNo);

	return lRet;
}
//---------------------------------------------------------------------------
