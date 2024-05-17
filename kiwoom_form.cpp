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
void __fastcall TFormKiwoom::AddLog(String sMsg)
{
    Memo1->Lines->Add(sMsg);
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::KHOpenAPI1EventConnect(TObject* Sender, long nErrCode)
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

    if (iAccount > 1) {
        FormMain->AddLog("���¹�ȣ ���� �ʿ� (���߰���) " + g_sKiwoomAcountNo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveConditionVer(TObject* Sender, long lRet, WideString sMsg)
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
	}
	__finally{
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

	try{
        SL->Delimiter = ';';
        SL->DelimitedText = strCodeList;

        iLine = SL->Count;

        for (int i = 0; i < iLine; i++) {
            if (SL->Strings[i] != "") {
                sCode = SL->Strings[i];

				FormMain->UpdateConditionItem(IntToStr(i), strConditionName, sCode);
            }
        }
	}
	__finally{
        delete SL;
    }

    if (nIndex == 2) { //�����ִ�
        KHOpenAPI1->SendCondition(
            sScrNo, strConditionName, FormMain->m_iSelectIndex, 0);
	}
	else {
    }
}
//---------------------------------------------------------------------------
/*
		"9201" : "���¹�ȣ"
		"9203" : "�ֹ���ȣ"
		"9001" : "�����ڵ�"
		"913" : "�ֹ�����"
        "302" : "�����"
        "900" : "�ֹ�����"
        "901" : "�ֹ�����"
        "902" : "��ü�����"
        "903" : "ü�ᴩ��ݾ�"
        "904" : "���ֹ���ȣ"
        "905" : "�ֹ�����"
        "906" : "�Ÿű���"
        "907" : "�ŵ�������"
        "908" : "�ֹ�/ü��ð�"
        "909" : "ü���ȣ"
        "910" : "ü�ᰡ"
		"911" : "ü�ᷮ"
		"10" : "���簡"
        "27" : "(�ֿ켱)�ŵ�ȣ��"
        "28" : "(�ֿ켱)�ż�ȣ��"
        "914" : "����ü�ᰡ"
		"915" : "����ü�ᷮ"
        "919" : "�źλ���"
        "920" : "ȭ���ȣ"
        "917" : "�ſ뱸��"
        "916" : "������"
		"930" : "��������"
		"931" : "���Դܰ�"
		"932" : "�Ѹ��԰�"
		"933" : "�ֹ����ɼ���"
		"945" : "���ϼ��ż�����"
		"946" : "�ŵ�/�ż�����"
        "950" : "�����Ѹŵ�����"
        "951" : "������"  (��������)
        "307" : "���ذ�"
        "8019" : "������"
		"957" : "�ſ�ݾ�"
        "958" : "�ſ�����"
        "918" : "������"
        "990" : "���Ͻ�������(����)"
        "991" : "���Ͻ������ͷ�(����)"
        "992" : "���Ͻ�������(�ſ�)"
        "993" : "���Ͻ������ͷ�(�ſ�)"
        "397" : "�Ļ���ǰ�ŷ�����"
        "305" : "���Ѱ�"
		"306" : "���Ѱ�"

*/
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveChejanData(
    TObject* Sender, WideString sGubun, long nItemCnt, WideString sFIdList)
{
    AnsiString sStockCode;
    AnsiString sStockName;
    AnsiString sResult;
    AnsiString sOrderCode;
    AnsiString sTemp;

    AnsiString sType;
    AnsiString sTradePrice;
    AnsiString sTradeVolume;
    AnsiString sTradeVolumeSplit;
    AnsiString sOrderVolume;

    AnsiString sTotalVolume;
    AnsiString sHoldVolume;

    AnsiString sKey;
    AnsiString sValue;

	try {
		sOrderCode = KHOpenAPI1->GetChejanData(9203);
		sStockCode = KHOpenAPI1->GetChejanData(9001);
        sStockName = KHOpenAPI1->GetChejanData(302);
        sStockName = sStockName.Trim();

        //���
        sResult = KHOpenAPI1->GetChejanData(913);
        sType = KHOpenAPI1->GetChejanData(907);

        sTradePrice = KHOpenAPI1->GetChejanData(910);
        sTradeVolume = KHOpenAPI1->GetChejanData(911);
        sTradeVolumeSplit = KHOpenAPI1->GetChejanData(915);

        sOrderVolume = KHOpenAPI1->GetChejanData(900); //�ֹ�����

        sTotalVolume = KHOpenAPI1->GetChejanData(930); //��������
        sHoldVolume = KHOpenAPI1->GetChejanData(933); //�ֹ����ɼ���

        if (sGubun == "0") { // 0:�ֹ�ü���뺸

			if (sResult == "ü��") {

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume,
					sTradeVolumeSplit, sOrderVolume);

			}
			else if (sResult == "����") { //�ż�,�ŵ� ����

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume,
					sTradeVolumeSplit, sOrderVolume);

			}
			else if (sResult == "Ȯ��") { //�ż�, �ŵ� ����. �ż�, �ŵ����.

                UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume,
                    sTradeVolumeSplit, sOrderVolume);
            }

		}
		else if (sGubun == "1") { // 1:�ܰ��뺸

            UpdateStockVolume(sStockCode, sStockName, sTotalVolume, sHoldVolume);
        }

    } catch (Exception &e) {
        AddLog(e.Message);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveInvestRealData(
    TObject* Sender, WideString sRealKey)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveMsg(TObject* Sender,
    WideString sScrNo, WideString sRQName, WideString sTrCode, WideString sMsg)
{
	FormMain->AddLog(sRQName);
    FormMain->AddLog(sTrCode);
    FormMain->AddLog(sMsg);
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
    FormMain->AddLog(sMessage);

    if (sRQName == "") {
    }
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


    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 1, wStockCode,
				iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//���尡 �ŵ�
int __fastcall TFormKiwoom::SellStockMarketPrice(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "03"; //���尡
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 2, wStockCode,
							iVolume, 0, wHogaGb, wOrgOrderNo);

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

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 1, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//�ż� ����
int __fastcall TFormKiwoom::BuyChange(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 5, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//�ż� ���
int __fastcall TFormKiwoom::BuyCancel(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 3, wStockCode,
							iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//������ �ŵ�
int __fastcall TFormKiwoom::SellStock(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 2, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//�ŵ� ����
int __fastcall TFormKiwoom::SellChange(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 6, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//�ŵ� ���
int __fastcall TFormKiwoom::SellCancel(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "�ֽ��ֹ�";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // �ֽ��ֹ�
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 4, wStockCode,
        					iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::Button1Click(TObject* Sender)
{
    //buy
    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    if (CheckBoxMarketPrice->Checked == true) {
        //���尡
        BuyStockMarketPrice(sStockCode, iVol);
    } else {
        //������
        BuyStock(sStockCode, iPrice, iVol);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button2Click(TObject* Sender)
{
    //sell

    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    if (CheckBoxMarketPrice->Checked == true) {
        //���尡
        SellStockMarketPrice(sStockCode, m_sOrderNo, iVol);
    } else {
        //������
        SellStock(sStockCode, m_sOrderNo, iPrice, iVol);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button3Click(TObject* Sender)
{
    //buy change

    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    BuyChange(sStockCode, m_sOrderNo, iPrice, iVol);
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button4Click(TObject* Sender)
{
    //sell change

    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    SellChange(sStockCode, m_sOrderNo, iPrice, iVol);
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button5Click(TObject* Sender)
{
    //buy cancel

    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    BuyCancel(sStockCode, m_sOrderNo, iVol);
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button6Click(TObject* Sender)
{
    //sell cancel

    String sStockCode;
    int iPrice;
    int iVol;

    sStockCode = EditStockCode->Text;
    iPrice = StrToInt(EditPrice->Text);
    iVol = StrToInt(EditVolume->Text);

    SellCancel(sStockCode, m_sOrderNo, iVol);
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::UpdateStockInfo(String sStockCode, String sStockName, String sOrderCode,
	int iStatus, String sType, String sTradePrice, String sTradeVolume, String sTradeVolumeSplit,
	String sOrderVolume)
{

    switch (iStatus) {
        case 0: // "����"

            //�ż�����, �ŵ������� ���
            //���� - Ȯ�� - ���� ������ �̺�Ʈ�� 3�� �߻�
            //����(new order code) - Ȯ��(new order code) - ����(old order code)
            //�������� �������� ó���� order code�� ����ϸ� �ȵ�

            if (StrToInt(sOrderCode) > StrToInt(m_sOrderNo)) { //���ο� order code�� ���
                m_sOrderNo = sOrderCode;
            }

			FormMain->AddLog("���� : " + sStockCode + " " + sStockName +  ", order code:" + sOrderCode +
                             ", last order code:" + m_sOrderNo);

            break;

        case 1: // "Ȯ��"

            if (sType.Trim() == "2") { // �ż�

				FormMain->AddLog("�ż� Ȯ�� : " + sStockCode + " " + sStockName + ", order code:" + sOrderCode);
            } else if (sType.Trim() == "1") { //�ŵ�

				FormMain->AddLog("�ŵ� Ȯ�� : " + sStockCode + " " + sStockName + ", order code:" + sOrderCode);
            }

            break;
        case 2: // "ü��"

            // �ż�
            if (sType.Trim() == "2") {
				FormMain->AddLog("�ż� ü�� : " + sStockCode + " " + sStockName + ", vol:" + sTradeVolume +
								 ", money:" + sTradePrice + ", order code:" + sOrderCode);

            }
            // �ŵ�
            else if (sType.Trim() == "1")
            {
				FormMain->AddLog("�ŵ� ü�� : " + sStockCode + " " + sStockName + ", vol:" + sTradeVolume +
								 ", money:" + sTradePrice + ", order code:" + sOrderCode);
            }

            break;
    }
}

// ---------------------------------------------------------------------------

void __fastcall TFormKiwoom::UpdateStockVolume(String sStockCode,
    String sStockName, String sTotalVolume, String sHoldVolume)
{
    FormMain->AddLog("vol info : stock code:" + sStockCode + " " + sStockName +
                     ", total vol:" + sTotalVolume + ", hold vol:" + sHoldVolume);
}

// ---------------------------------------------------------------------------

