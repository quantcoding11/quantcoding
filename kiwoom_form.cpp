//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "kiwoom_form.h"
#include "main.h"
#include "kiwoom_thread.h"
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

    AnsiString sType;
    AnsiString sTradePrice;
    AnsiString sTradeVolume;
	AnsiString sOrderVolume;

    AnsiString sTotalVolume;
    AnsiString sHoldVolume;

    AnsiString sKey;
    AnsiString sValue;

	try {
		sOrderCode = KHOpenAPI1->GetChejanData(9203);
		sStockCode = KHOpenAPI1->GetChejanData(9001);
		sStockCode = sStockCode.SubString(2, sStockCode.Length());//�տ� A ���ִ�

        sStockName = KHOpenAPI1->GetChejanData(302);
        sStockName = sStockName.Trim();

        //���
        sResult = KHOpenAPI1->GetChejanData(913);
        sType = KHOpenAPI1->GetChejanData(907);

        sTradePrice = KHOpenAPI1->GetChejanData(910);
        sTradeVolume = KHOpenAPI1->GetChejanData(911);

        sOrderVolume = KHOpenAPI1->GetChejanData(900); //�ֹ�����

        sTotalVolume = KHOpenAPI1->GetChejanData(930); //��������
        sHoldVolume = KHOpenAPI1->GetChejanData(933); //�ֹ����ɼ���

		if (sGubun == "0") { // 0:�ֹ�ü���뺸

			if (sResult == "ü��") {

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume, sOrderVolume);

			}
			else if (sResult == "����") { //�ż�,�ŵ� ����

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume, sOrderVolume);

			}
			else if (sResult == "Ȯ��") { //�ż�, �ŵ� ����. �ż�, �ŵ����.

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume, sOrderVolume);
			}

		}
		else if (sGubun == "1") { // 1:�ܰ��뺸

			UpdateStockVolume(sStockCode, sStockName, sTotalVolume, sHoldVolume);
			g_ThreadKiwoom->UpdateStockVolume(sStockCode, sStockName, sTotalVolume, sHoldVolume);
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
    FormMain->AddLog("msg");
	FormMain->AddLog(sRQName);
    FormMain->AddLog(sTrCode);
    FormMain->AddLog(sMsg);
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveRealData(TObject* Sender,
	WideString sRealKey, WideString sRealType, WideString sRealData)
{

	TStock* object;

	String sRealMoney;
	String sRealTime;
	String sRealRatio;
	String sRealTradeMoney;
	String sRealVolume;
	String sRealMedo1;
	String sRealMesu1;
	String sRealChegyul;



	if(sRealType == "�ֽ�ü��"){


		sRealMoney 		= KHOpenAPI1->GetCommRealData(sRealKey, 10);
		sRealTime       = KHOpenAPI1->GetCommRealData(sRealKey, 20);
		sRealRatio 		= KHOpenAPI1->GetCommRealData(sRealKey, 12);
		sRealTradeMoney = KHOpenAPI1->GetCommRealData(sRealKey, 14);
		sRealVolume     = KHOpenAPI1->GetCommRealData(sRealKey, 15);
		sRealMedo1 		= KHOpenAPI1->GetCommRealData(sRealKey, 27);
		sRealMesu1 		= KHOpenAPI1->GetCommRealData(sRealKey, 28);
		sRealChegyul 	= KHOpenAPI1->GetCommRealData(sRealKey, 228);


		//update
		g_ThreadKiwoom->UpdateRealData(sRealKey, sRealTime, sRealMoney, sRealRatio,
			sRealTradeMoney, sRealVolume, sRealMedo1, sRealMesu1, sRealChegyul);



	}

}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveTrData(TObject* Sender,
    WideString sScrNo, WideString sRQName, WideString sTrCode,
	WideString sRecordName, WideString sPrevNext, long nDataLength,
    WideString sErrorCode, WideString sMessage, WideString sSplmMsg)
{
	//

	TStock* object;

	FormMain->AddLog("tr");
	FormMain->AddLog(sRQName);
	FormMain->AddLog(sMessage);


	AnsiString RQName = sRQName;


	AnsiString svStockCode, svStockName;
	AnsiString svNowMoney, svSign, svRatio;
	AnsiString svStart, svTop, svBottom;
	AnsiString svVolume, svChe;

	WideString sStockName = "�����";
	WideString sStockCode = "�����ڵ�";
	WideString sNowMoney = "���簡";

	WideString sSign = "���ϴ���ȣ";
	WideString sRatio = "�����";
	WideString sStart = "�ð�";
	WideString sTop = "��";
	WideString sBottom = "����";
	WideString sVolume = "����ŷ���";
	WideString sChe = "ü�ᰭ��";

	int iNext = 0;
	if(sPrevNext != ""){
		iNext = StrToInt(sPrevNext);
	}

	bool bNull = false;
	int iNowMoney;

	if(RQName == "����ü������������û"){



		for(int k=0; k <100; k++){
			svStockName = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStockName);
			svStockName = svStockName.Trim();

			svStockCode = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStockCode);
			svStockCode = svStockCode.Trim();

			svNowMoney = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sNowMoney);
			svNowMoney = svNowMoney.Trim();

			svSign = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sSign);
			svSign = svSign.Trim();

			svRatio = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sRatio);
			svRatio = svRatio.Trim();


            //�ȿ´�
            /*
			svStart = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStart);
			svStart = svStart.Trim();

			svTop = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sTop);
			svTop = svTop.Trim();

			svBottom = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sBottom);
			svBottom = svBottom.Trim();

			svVolume = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sVolume);
			svVolume = sVolume.Trim();

			svChe = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sChe);
			svChe = svChe.Trim();
			*/

			if(svStockCode == ""){
				bNull = true;
			}

			//stock object �߰�
			if(svStockCode != ""){
				object = new TStock();
				object->sStockCode = svStockCode;
				object->sStockName = svStockName;

				if(svNowMoney != ""){
					object->iNowMoney = StrToInt(svNowMoney);
				}

				if(svRatio != ""){
					object->dNowRatio = StrToFloat(svRatio);
				}

				//add
				if(g_StockList->CheckAdd(object) == true){
					g_StockList->Add(object);
				}
			}


			FormMain->AddLog(IntToStr(k)+" > "+ sStockCode +":"+ svStockCode +", "+ sStockName +":"+ svStockName +", "+
					sNowMoney +":"+ svNowMoney +", "+ sSign +":"+ svSign +","+
					sRatio +":"+ svRatio );
//					", "+ sStart +":"+ svStart +", "+
//					sTop +":"+ svTop +", "+ sBottom +":"+ svBottom +", "+
//					sVolume +":"+ svVolume +", "+ sChe +":"+ svChe );
		}

		if((iNext != 0) && (bNull == false)){
			//�����ִ�
			RequestExpectTop(iNext);
		}

	}
	else if(RQName == "�ŷ���ݻ�����û"){

		for(int k=0; k <100; k++){
			svStockName = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStockName);
			svStockName = svStockName.Trim();

			svStockCode = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStockCode);
			svStockCode = svStockCode.Trim();

			svNowMoney = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sNowMoney);
			svNowMoney = svNowMoney.Trim();

			svSign = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sSign);
			svSign = svSign.Trim();

			svRatio = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sRatio);
			svRatio = svRatio.Trim();

			/*
			svStart = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sStart);
			svStart = svStart.Trim();

			svTop = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sTop);
			svTop = svTop.Trim();

			svBottom = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sBottom);
			svBottom = svBottom.Trim();

			svVolume = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sVolume);
			svVolume = sVolume.Trim();

			svChe = KHOpenAPI1->GetCommData(sTrCode, sRQName, k, sChe);
			svChe = svChe.Trim();
			*/

			if(svStockCode == ""){
				bNull = true;
			}

			//stock object �߰�
			if(svStockCode != ""){
				object = new TStock();
				object->sStockCode = svStockCode;
				object->sStockName = svStockName;

				if(svNowMoney != ""){
					object->iNowMoney = StrToInt(svNowMoney);
				}

				if(svRatio != ""){
					object->dNowRatio = StrToFloat(svRatio);
				}

				//add
				if(g_StockList->CheckAdd(object) == true){
					g_StockList->Add(object);
				}
			}

			FormMain->AddLog(IntToStr(k)+" > "+ sStockCode +":"+ svStockCode +", "+ sStockName +":"+ svStockName +", "+
					sNowMoney +":"+ svNowMoney +", "+ sSign +":"+ svSign +","+
					sRatio +":"+ svRatio );
//					", "+ sStart +":"+ svStart +", "+
//					sTop +":"+ svTop +", "+ sBottom +":"+ svBottom +", "+
//					sVolume +":"+ svVolume +", "+ sChe +":"+ svChe );
		}

		if((iNext != 0) && (bNull == false)){
			//�����ִ�
			RequestTradeMoneyTop(iNext);
		}

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
	int iStatus, String sType, String sTradePrice, String sTradeVolume, String sOrderVolume)
{

	if(sOrderCode != ""){
		if(m_sOrderNo != ""){
			if (StrToInt(sOrderCode) > StrToInt(m_sOrderNo)) { //���ο� order code�� ���
				m_sOrderNo = sOrderCode;
			}
		}
		else{
			m_sOrderNo = sOrderCode;
		}
    }

	/*
    switch (iStatus) {
        case 0: // "����"

            //�ż�����, �ŵ������� ���
            //���� - Ȯ�� - ���� ������ �̺�Ʈ�� 3�� �߻�
            //����(new order code) - Ȯ��(new order code) - ����(old order code)
            //�������� �������� ó���� order code�� ����ϸ� �ȵ�


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
    */
}

// ---------------------------------------------------------------------------

void __fastcall TFormKiwoom::UpdateStockVolume(String sStockCode,
    String sStockName, String sTotalVolume, String sHoldVolume)
{
    /*
	FormMain->AddLog("vol info : stock code:" + sStockCode + " " + sStockName +
					 ", total vol:" + sTotalVolume + ", hold vol:" + sHoldVolume);
	*/
}

// ---------------------------------------------------------------------------


void __fastcall TFormKiwoom::Button7Click(TObject *Sender)
{
//�ż�
	TStock* object;

    String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iBuyTargetPrice = iPrice;
			object->iBuyTargetVolume = iVol;

			if(CheckBoxMarketPrice2->Checked == true){//���尡 �ż�
				object->iTradeStatus = _BUY_IMMEDIATE_71;
			}
			else{//������ �ż�
				object->iTradeStatus = _BUY_NEW_1;
			}
		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button8Click(TObject *Sender)
{
//�ŵ�

	TStock* object;

	String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iSellTargetPrice = iPrice;
			object->iSellTargetVolume = iVol;

			if(CheckBoxMarketPrice2->Checked == true){//���尡 �ŵ�
				object->iTradeStatus = _SELL_IMMEDIATE_81;
			}
			else{//������ �ŵ�
				object->iTradeStatus = _SELL_NEW_2;
			}
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button9Click(TObject *Sender)
{
//�ż�����

	TStock* object;

	String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iBuyTargetPrice = iPrice;
			object->iBuyTargetVolume = iVol;

			object->iTradeStatus = _BUY_MODIFY_5;

		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button10Click(TObject *Sender)
{
//�ŵ�����

	TStock* object;

	String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iSellTargetPrice = iPrice;
			object->iSellTargetVolume = iVol;

			object->iTradeStatus = _SELL_MODIFY_6;

		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button11Click(TObject *Sender)
{
//�ż����

	TStock* object;

	String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iBuyTargetPrice = iPrice;
			object->iBuyTargetVolume = iVol;

			object->iTradeStatus = _BUY_CANCEL_3;

		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button12Click(TObject *Sender)
{
//�ŵ� ���

	TStock* object;

	String sStockCode;
	int iPrice;
	int iVol;

	sStockCode = EditStockCode2->Text;
	iPrice = StrToInt(EditPrice2->Text);
	iVol = StrToInt(EditVolume2->Text);


	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			object->iSellTargetPrice = iPrice;
			object->iSellTargetVolume = iVol;

			object->iTradeStatus = _SELL_CANCEL_4;

		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button13Click(TObject *Sender)
{
//add obejct

	TStock* object;
	object = new TStock();
	object->sStockCode = EditObject->Text;


	if(g_StockList->CheckAdd(object) == true){
		g_StockList->Add(object);
	}

}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button16Click(TObject *Sender)
{
//opt10029 : ����ü������������û

	RequestExpectTop(0);
}
//---------------------------------------------------------------------------
/*
	���屸�� = 000:��ü, 001:�ڽ���, 101:�ڽ���
	���ı��� = 1:��·�, 2:�����, 3:����, 4:�϶���,5:�϶���, 6, ü�ᷮ, 7:����, 8:����
	�ŷ������� = 0:��ü��ȸ, 1;õ���̻�, 3:3õ���̻�, 5:5õ���̻�, 10:�����̻�, 50:5�����̻�, 100:10�����̻�
	�������� = 0:��ü��ȸ, 1:������������, 3:�켱������, 4:��������,�켱������, 5:��100����, 6:��100������,
				7:��40������, 8:��30������, 9:��20������, 11:�����Ÿ���������, 12:��50������, 13:��60������,
				14:ETF����, 15:��������, 16:ETF+ETN����
	�ſ����� = 0:��ü��ȸ, 1:�ſ�����A��, 2:�ſ�����B��, 3:�ſ�����C��, 4:�ſ�����D��, 5:�ſ��ѵ��ʰ�����,
				8:�ſ����, 9:�ſ�������ü
	�������� = 0:��ü��ȸ, 1:1õ���̸�, 2:1õ��~2õ��, 3:2õ��~5õ��, 4:5õ��~1����, 5:1�����̻�, 8:1õ���̻�, 10:1�����̸�
*/

void __fastcall TFormKiwoom::RequestExpectTop(int index)
{
//opt10029 : ����ü������������û

	WideString strTrCode, strRecordName;


	strRecordName = "����ü������������û";
	strTrCode = "OPT10029";

	KHOpenAPI1->SetInputValue("���屸��", "000");
	KHOpenAPI1->SetInputValue("���ı���", "1");
	KHOpenAPI1->SetInputValue("�ŷ�������", "0");
	KHOpenAPI1->SetInputValue("��������", "0"); // => 1500 ����
	KHOpenAPI1->SetInputValue("�ſ�����", "0");
	KHOpenAPI1->SetInputValue("��������", "0");


	KHOpenAPI1->CommRqData(strRecordName, strTrCode, index, GetScrNum());
}

//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button15Click(TObject *Sender)
{
//OPT10032 : �ŷ���ݻ�����û

	RequestTradeMoneyTop(0);

}
//---------------------------------------------------------------------------
/*

	���屸�� = 000:��ü, 001:�ڽ���, 101:�ڽ���
	������������ = 0:�������� ������, 1:�������� ����

*/
void __fastcall TFormKiwoom::RequestTradeMoneyTop(int index)
{
//OPT10032 : �ŷ���ݻ�����û

	WideString strTrCode, strRecordName;


	strRecordName = "�ŷ���ݻ�����û";
	strTrCode = "OPT10032";

	KHOpenAPI1->SetInputValue("���屸��", "000");
	KHOpenAPI1->SetInputValue("������������", "0"); //=>��ü���� ��ȸ

	KHOpenAPI1->CommRqData(strRecordName, strTrCode, index, GetScrNum());
}


//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button14Click(TObject *Sender)
{
//object list ��ȸ
	TStock* object;
	String sTemp;


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];


		sTemp.printf(L"%.2f", object->dNowRatio);
		AddLog(IntToStr(i) +" "+ object->sStockCode +" "+ object->sStockName +
			+", "+ IntToStr(object->iNowMoney) + ", ratio:"+ sTemp );
	}


}

//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button17Click(TObject *Sender)
{
//�ǽð� ��û
	TStock* object;
	String sTemp;


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		RequestRealTimeData(object->sStockCode);
	}
}
//---------------------------------------------------------------------------
/*
	Real Type : �ֽĽü�

	20 ü��ð� (HHMMSS)
	10 ���簡, ü�ᰡ, �ǽð�����
	11 ���� ���
	12 �����
	27 (�ֿ켱)�ŵ�ȣ��
	28 (�ֿ켱)�ż�ȣ��
	15 �ŷ���, ü�ᷮ
	13 �����ŷ���, ����ü�ᷮ
	14 �����ŷ����
	16 �ð�
	17 ��
	18 ����
	25 ���ϴ�� ��ȣ
	26 ���ϰŷ��� ���(���, ��)
	29 �ŷ���� ����
	30 ���ϰŷ��� ���(����)
	31 �ŷ�ȸ����
	32 �ŷ����
	228 ü�ᰭ��
	311 �ð��Ѿ�(��)
	290 �屸��
	691 K,O ���ٵ� (ELW��������߻� ���ذ���, ����)

*/

void __fastcall TFormKiwoom::RequestRealTimeData(String sStockCode)
{
//Real Type : �ֽĽü�

	static int iFirst = 0;//ó���� 0, ���ĺ��ʹ� 1

	WideString scrum = "9000";//����
	WideString sCode;
	WideString sFID;
	WideString sType;

	sCode = sStockCode;
	sFID = "9001;20;10;12;14;15;27;28;228";
	sType = IntToStr(iFirst);

	int iRtn;

	iRtn = KHOpenAPI1->SetRealReg(scrum, sCode, sFID, sType);

	if(iRtn != 0){
		FormMain->AddLog("�ǽð� ��û ����. "+ sStockCode );
	}

	iFirst = 1;

}


//---------------------------------------------------------------------------

