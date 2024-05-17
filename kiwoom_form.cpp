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

    //계좌 정보 요청
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
        FormMain->AddLog("계좌번호 검토 필요 (다중계좌) " + g_sKiwoomAcountNo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKiwoom::KHOpenAPI1ReceiveConditionVer(TObject* Sender, long lRet, WideString sMsg)
{
    //조건식

    if (lRet != 1) {
        FormMain->AddLog("조회 실패");
    }

    String conditionList;

    //조건식 결과
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
	//조건 종목

    TStringList* SL = new TStringList;
    int iLine;

    //종목코드 리스트는 각 종목코드가 ';'로 구분되서 전달됩니다.

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

    if (nIndex == 2) { //남아있다
        KHOpenAPI1->SendCondition(
            sScrNo, strConditionName, FormMain->m_iSelectIndex, 0);
	}
	else {
    }
}
//---------------------------------------------------------------------------
/*
		"9201" : "계좌번호"
		"9203" : "주문번호"
		"9001" : "종목코드"
		"913" : "주문상태"
        "302" : "종목명"
        "900" : "주문수량"
        "901" : "주문가격"
        "902" : "미체결수량"
        "903" : "체결누계금액"
        "904" : "원주문번호"
        "905" : "주문구분"
        "906" : "매매구분"
        "907" : "매도수구분"
        "908" : "주문/체결시간"
        "909" : "체결번호"
        "910" : "체결가"
		"911" : "체결량"
		"10" : "현재가"
        "27" : "(최우선)매도호가"
        "28" : "(최우선)매수호가"
        "914" : "단위체결가"
		"915" : "단위체결량"
        "919" : "거부사유"
        "920" : "화면번호"
        "917" : "신용구분"
        "916" : "대출일"
		"930" : "보유수량"
		"931" : "매입단가"
		"932" : "총매입가"
		"933" : "주문가능수량"
		"945" : "당일순매수수량"
		"946" : "매도/매수구분"
        "950" : "당일총매도손일"
        "951" : "예수금"  (지원안함)
        "307" : "기준가"
        "8019" : "손익율"
		"957" : "신용금액"
        "958" : "신용이자"
        "918" : "만기일"
        "990" : "당일실현손익(유가)"
        "991" : "당일실현손익률(유가)"
        "992" : "당일실현손익(신용)"
        "993" : "당일실현손익률(신용)"
        "397" : "파생상품거래단위"
        "305" : "상한가"
		"306" : "하한가"

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

        //결과
        sResult = KHOpenAPI1->GetChejanData(913);
        sType = KHOpenAPI1->GetChejanData(907);

        sTradePrice = KHOpenAPI1->GetChejanData(910);
        sTradeVolume = KHOpenAPI1->GetChejanData(911);
        sTradeVolumeSplit = KHOpenAPI1->GetChejanData(915);

        sOrderVolume = KHOpenAPI1->GetChejanData(900); //주문수량

        sTotalVolume = KHOpenAPI1->GetChejanData(930); //보유수량
        sHoldVolume = KHOpenAPI1->GetChejanData(933); //주문가능수량

        if (sGubun == "0") { // 0:주문체결통보

			if (sResult == "체결") {

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume,
					sTradeVolumeSplit, sOrderVolume);

			}
			else if (sResult == "접수") { //매수,매도 접수

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume,
					sTradeVolumeSplit, sOrderVolume);

			}
			else if (sResult == "확인") { //매수, 매도 정정. 매수, 매도취소.

                UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume,
                    sTradeVolumeSplit, sOrderVolume);
            }

		}
		else if (sGubun == "1") { // 1:잔고통보

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
//시장가 매수
int __fastcall TFormKiwoom::BuyStockMarketPrice(String sStockCode, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;
    WideString wBuyCode = "1"; //
    WideString wHogaGb = "03"; //시장가
    WideString wOrgOrderNo = "";


    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 1, wStockCode,
				iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//시장가 매도
int __fastcall TFormKiwoom::SellStockMarketPrice(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "03"; //시장가
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 2, wStockCode,
							iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//지정가 매수
int __fastcall TFormKiwoom::BuyStock(String sStockCode, int iPrice, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = "";

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 1, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//매수 정정
int __fastcall TFormKiwoom::BuyChange(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 5, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//매수 취소
int __fastcall TFormKiwoom::BuyCancel(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 3, wStockCode,
							iVolume, 0, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//지정가 매도
int __fastcall TFormKiwoom::SellStock(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 2, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//매도 정정
int __fastcall TFormKiwoom::SellChange(
    String sStockCode, String sOrderNo, int iPrice, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
    int lRet = -1;

    lRet = KHOpenAPI1->SendOrder(wRQName, GetScrNum(), wBankCode, 6, wStockCode,
							iVolume, iPrice, wHogaGb, wOrgOrderNo);

    return lRet;
}
//---------------------------------------------------------------------------
//매도 취소
int __fastcall TFormKiwoom::SellCancel(
    String sStockCode, String sOrderNo, int iVolume)
{
    WideString wRQName = "주식주문";

    WideString wStockCode = sStockCode;
    WideString wBankCode = g_sKiwoomAcountNo;

    WideString wHogaGb = "00";
    WideString wOrgOrderNo = sOrderNo;

    // 주식주문
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
        //시장가
        BuyStockMarketPrice(sStockCode, iVol);
    } else {
        //지정가
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
        //시장가
        SellStockMarketPrice(sStockCode, m_sOrderNo, iVol);
    } else {
        //지정가
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
        case 0: // "접수"

            //매수정정, 매도정정의 경우
            //접수 - 확인 - 접수 순서로 이벤트가 3번 발생
            //접수(new order code) - 확인(new order code) - 접수(old order code)
            //마지막에 접수에서 처리된 order code를 사용하면 안됨

            if (StrToInt(sOrderCode) > StrToInt(m_sOrderNo)) { //새로운 order code만 사용
                m_sOrderNo = sOrderCode;
            }

			FormMain->AddLog("접수 : " + sStockCode + " " + sStockName +  ", order code:" + sOrderCode +
                             ", last order code:" + m_sOrderNo);

            break;

        case 1: // "확인"

            if (sType.Trim() == "2") { // 매수

				FormMain->AddLog("매수 확인 : " + sStockCode + " " + sStockName + ", order code:" + sOrderCode);
            } else if (sType.Trim() == "1") { //매도

				FormMain->AddLog("매도 확인 : " + sStockCode + " " + sStockName + ", order code:" + sOrderCode);
            }

            break;
        case 2: // "체결"

            // 매수
            if (sType.Trim() == "2") {
				FormMain->AddLog("매수 체결 : " + sStockCode + " " + sStockName + ", vol:" + sTradeVolume +
								 ", money:" + sTradePrice + ", order code:" + sOrderCode);

            }
            // 매도
            else if (sType.Trim() == "1")
            {
				FormMain->AddLog("매도 체결 : " + sStockCode + " " + sStockName + ", vol:" + sTradeVolume +
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

