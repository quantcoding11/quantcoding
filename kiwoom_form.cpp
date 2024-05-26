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
		sStockCode = sStockCode.SubString(2, sStockCode.Length());//앞에 A 가있다

        sStockName = KHOpenAPI1->GetChejanData(302);
        sStockName = sStockName.Trim();

        //결과
        sResult = KHOpenAPI1->GetChejanData(913);
        sType = KHOpenAPI1->GetChejanData(907);

        sTradePrice = KHOpenAPI1->GetChejanData(910);
        sTradeVolume = KHOpenAPI1->GetChejanData(911);

        sOrderVolume = KHOpenAPI1->GetChejanData(900); //주문수량

        sTotalVolume = KHOpenAPI1->GetChejanData(930); //보유수량
        sHoldVolume = KHOpenAPI1->GetChejanData(933); //주문가능수량

		if (sGubun == "0") { // 0:주문체결통보

			if (sResult == "체결") {

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 2, sType, sTradePrice, sTradeVolume, sOrderVolume);

			}
			else if (sResult == "접수") { //매수,매도 접수

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 0, sType, sTradePrice, sTradeVolume, sOrderVolume);

			}
			else if (sResult == "확인") { //매수, 매도 정정. 매수, 매도취소.

				UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume, sOrderVolume);
				g_ThreadKiwoom->UpdateStockInfo(sStockCode, sStockName, sOrderCode, 1, sType, sTradePrice, sTradeVolume, sOrderVolume);
			}

		}
		else if (sGubun == "1") { // 1:잔고통보

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



	if(sRealType == "주식체결"){


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

	WideString sStockName = "종목명";
	WideString sStockCode = "종목코드";
	WideString sNowMoney = "현재가";

	WideString sSign = "전일대비기호";
	WideString sRatio = "등락률";
	WideString sStart = "시가";
	WideString sTop = "고가";
	WideString sBottom = "저가";
	WideString sVolume = "현재거래량";
	WideString sChe = "체결강도";

	int iNext = 0;
	if(sPrevNext != ""){
		iNext = StrToInt(sPrevNext);
	}

	bool bNull = false;
	int iNowMoney;

	if(RQName == "예상체결등락률상위요청"){



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


            //안온다
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

			//stock object 추가
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
			//남아있다
			RequestExpectTop(iNext);
		}

	}
	else if(RQName == "거래대금상위요청"){

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

			//stock object 추가
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
			//남아있다
			RequestTradeMoneyTop(iNext);
		}

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
	int iStatus, String sType, String sTradePrice, String sTradeVolume, String sOrderVolume)
{

	if(sOrderCode != ""){
		if(m_sOrderNo != ""){
			if (StrToInt(sOrderCode) > StrToInt(m_sOrderNo)) { //새로운 order code만 사용
				m_sOrderNo = sOrderCode;
			}
		}
		else{
			m_sOrderNo = sOrderCode;
		}
    }

	/*
    switch (iStatus) {
        case 0: // "접수"

            //매수정정, 매도정정의 경우
            //접수 - 확인 - 접수 순서로 이벤트가 3번 발생
            //접수(new order code) - 확인(new order code) - 접수(old order code)
            //마지막에 접수에서 처리된 order code를 사용하면 안됨


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
//매수
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

			if(CheckBoxMarketPrice2->Checked == true){//시장가 매수
				object->iTradeStatus = _BUY_IMMEDIATE_71;
			}
			else{//지정가 매수
				object->iTradeStatus = _BUY_NEW_1;
			}
		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button8Click(TObject *Sender)
{
//매도

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

			if(CheckBoxMarketPrice2->Checked == true){//시장가 매도
				object->iTradeStatus = _SELL_IMMEDIATE_81;
			}
			else{//지정가 매도
				object->iTradeStatus = _SELL_NEW_2;
			}
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button9Click(TObject *Sender)
{
//매수정정

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
//매도정정

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
//매수취소

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
//매도 취소

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
//opt10029 : 예상체결등락률상위요청

	RequestExpectTop(0);
}
//---------------------------------------------------------------------------
/*
	시장구분 = 000:전체, 001:코스피, 101:코스닥
	정렬구분 = 1:상승률, 2:상승폭, 3:보합, 4:하락률,5:하락폭, 6, 체결량, 7:상한, 8:하한
	거래량조건 = 0:전체조회, 1;천주이상, 3:3천주이상, 5:5천주이상, 10:만주이상, 50:5만주이상, 100:10만주이상
	종목조건 = 0:전체조회, 1:관리종목제외, 3:우선주제외, 4:관리종목,우선주제외, 5:증100제외, 6:증100만보기,
				7:증40만보기, 8:증30만보기, 9:증20만보기, 11:정리매매종목제외, 12:증50만보기, 13:증60만보기,
				14:ETF제외, 15:스팩제외, 16:ETF+ETN제외
	신용조건 = 0:전체조회, 1:신용융자A군, 2:신용융자B군, 3:신용융자C군, 4:신용융자D군, 5:신용한도초과제외,
				8:신용대주, 9:신용융자전체
	가격조건 = 0:전체조회, 1:1천원미만, 2:1천원~2천원, 3:2천원~5천원, 4:5천원~1만원, 5:1만원이상, 8:1천원이상, 10:1만원미만
*/

void __fastcall TFormKiwoom::RequestExpectTop(int index)
{
//opt10029 : 예상체결등락률상위요청

	WideString strTrCode, strRecordName;


	strRecordName = "예상체결등락률상위요청";
	strTrCode = "OPT10029";

	KHOpenAPI1->SetInputValue("시장구분", "000");
	KHOpenAPI1->SetInputValue("정렬구분", "1");
	KHOpenAPI1->SetInputValue("거래량조건", "0");
	KHOpenAPI1->SetInputValue("종목조건", "0"); // => 1500 종목
	KHOpenAPI1->SetInputValue("신용조건", "0");
	KHOpenAPI1->SetInputValue("가격조건", "0");


	KHOpenAPI1->CommRqData(strRecordName, strTrCode, index, GetScrNum());
}

//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button15Click(TObject *Sender)
{
//OPT10032 : 거래대금상위요청

	RequestTradeMoneyTop(0);

}
//---------------------------------------------------------------------------
/*

	시장구분 = 000:전체, 001:코스피, 101:코스닥
	관리종목포함 = 0:관리종목 미포함, 1:관리종목 포함

*/
void __fastcall TFormKiwoom::RequestTradeMoneyTop(int index)
{
//OPT10032 : 거래대금상위요청

	WideString strTrCode, strRecordName;


	strRecordName = "거래대금상위요청";
	strTrCode = "OPT10032";

	KHOpenAPI1->SetInputValue("시장구분", "000");
	KHOpenAPI1->SetInputValue("관리종목포함", "0"); //=>전체종목 조회

	KHOpenAPI1->CommRqData(strRecordName, strTrCode, index, GetScrNum());
}


//---------------------------------------------------------------------------

void __fastcall TFormKiwoom::Button14Click(TObject *Sender)
{
//object list 조회
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
//실시간 요청
	TStock* object;
	String sTemp;


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		RequestRealTimeData(object->sStockCode);
	}
}
//---------------------------------------------------------------------------
/*
	Real Type : 주식시세

	20 체결시간 (HHMMSS)
	10 현재가, 체결가, 실시간종가
	11 전일 대비
	12 등락율
	27 (최우선)매도호가
	28 (최우선)매수호가
	15 거래량, 체결량
	13 누적거래량, 누적체결량
	14 누적거래대금
	16 시가
	17 고가
	18 저가
	25 전일대비 기호
	26 전일거래량 대비(계약, 주)
	29 거래대금 증감
	30 전일거래량 대비(비율)
	31 거래회전율
	32 거래비용
	228 체결강도
	311 시가총액(억)
	290 장구분
	691 K,O 접근도 (ELW조기종료발생 기준가격, 지수)

*/

void __fastcall TFormKiwoom::RequestRealTimeData(String sStockCode)
{
//Real Type : 주식시세

	static int iFirst = 0;//처음은 0, 이후부터는 1

	WideString scrum = "9000";//고정
	WideString sCode;
	WideString sFID;
	WideString sType;

	sCode = sStockCode;
	sFID = "9001;20;10;12;14;15;27;28;228";
	sType = IntToStr(iFirst);

	int iRtn;

	iRtn = KHOpenAPI1->SetRealReg(scrum, sCode, sFID, sType);

	if(iRtn != 0){
		FormMain->AddLog("실시간 요청 실패. "+ sStockCode );
	}

	iFirst = 1;

}


//---------------------------------------------------------------------------

