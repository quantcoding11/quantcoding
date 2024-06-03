//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "kiwoom_thread.h"
#include "main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ThreadKiwoom::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
ThreadKiwoom* g_ThreadKiwoom;

__fastcall ThreadKiwoom::ThreadKiwoom(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThreadKiwoom::Execute()
{

	TStock* object;

	volatile int iIndex = 0;

	while (!Terminated) {

		if (g_bClosing == false) {

			for (int i = 0; i < g_StockList->objectList->Count; i++){
				object = (TStock*)g_StockList->objectList->Items[i];

				//매수 매도에 집중
				if((object->iTradeStatus > 0) && (object->iTradeStatus < 99)){
					BuySellLogic(object);
				}


				//매수, 매도 모니터



			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall ThreadKiwoom::BuySellLogic(TStock* object)
{


	switch (object->iTradeStatus) {
		case _BUY_NEW_1: // 매수신호 발생

			object->iTradeStatus = _BUY_NEW_ACCEPTING_10;
			object->iBoughtVolume = 0;

			// 지정가 매수
			FormKiwoom->BuyStock(object->sStockCode, object->iBuyTargetPrice, object->iBuyTargetVolume);


			break;

	case _SELL_NEW_2: // 신규매도
		object->iTradeStatus = _SELL_NEW_ACCEPTING_20;

		// 매수 완료 목표가로 지정가 매도
		FormKiwoom->SellStock(object->sStockCode, object->sOrderCode, object->iSellTargetPrice, object->iSellTargetVolume);

		break;

	case _BUY_MODIFY_5://매수정정
		object->iTradeStatus = _BUY_MODIFY_ING_50;

		FormKiwoom->BuyChange(object->sStockCode, object->sOrderCode,object->iBuyTargetPrice, object->iBuyTargetVolume);

		break;
	case _SELL_CANCEL_4:
        object->iTradeStatus = _SELL_CANCEL_ING_40;

		FormKiwoom->SellCancel(object->sStockCode, object->sOrderCode, object->iSellTargetVolume);


		break;
	case _BUY_CANCEL_3:
		object->iTradeStatus = _BUY_CANCEL_ING_30;

		FormKiwoom->BuyCancel(object->sStockCode, object->sOrderCode, object->iBuyTargetVolume);

		break;
	case _SELL_MODIFY_6: // 매도정정
		object->iTradeStatus = _SELL_MODIFY_ING_60;

		FormKiwoom->SellChange(object->sStockCode, object->sOrderCode, object->iSellTargetPrice, object->iSellTargetVolume);

		break;


	case _BUY_IMMEDIATE_71:

		//즉시매수

		object->iTradeStatus = _BUY_IMMEDIATE_ING_72;
		object->iBoughtVolume = 0;

		FormKiwoom->BuyStockMarketPrice(object->sStockCode, object->iBuyTargetVolume);


		break;
	case _SELL_IMMEDIATE_81:

		object->iTradeStatus = _SELL_IMMEDIATE_82;

		//즉시매도
		FormKiwoom->SellStockMarketPrice(object->sStockCode, object->sOrderCode, object->iSellTargetVolume);

		break;
	}



}
// ---------------------------------------------------------------------------


void __fastcall ThreadKiwoom::UpdateStockInfo(String sStockCode, String sStockName, String sOrderCode,
	int iStatus, String sType, String sTradePrice, String sTradeVolume, String sOrderVolume)
{

	TStock* object;




	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if (object->sStockCode == sStockCode) {


			if(sOrderCode != ""){
				if(object->sOrderCode != ""){
					if (StrToInt(sOrderCode) > StrToInt(object->sOrderCode)) { //새로운 order code만 사용
						object->sOrderCode = sOrderCode;
					}
				}
				else{
					object->sOrderCode = sOrderCode;
				}
			}


			switch (iStatus) {
				case 0: // "접수"

					//매수정정, 매도정정의 경우
					//접수 - 확인 - 접수 순서로 이벤트가 3번 발생
					//접수(new order code) - 확인(new order code) - 접수(old order code)
					//마지막에 접수에서 처리된 order code를 사용하면 안됨


					FormMain->AddLog("접수 : " + sStockCode + " " + sStockName +  ", order code:" + sOrderCode +
									 ", last order code:" + object->sOrderCode);

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
	}
}

// ---------------------------------------------------------------------------

void __fastcall ThreadKiwoom::UpdateStockVolume(String sStockCode,
	String sStockName, String sTotalVolume, String sHoldVolume)
{
    FormMain->AddLog("vol info : stock code:" + sStockCode + " " + sStockName +
					 ", total vol:" + sTotalVolume + ", hold vol:" + sHoldVolume);


	TStock* object;


	int iTotalVolume;
	if (TryStrToInt(sTotalVolume, iTotalVolume) == true) {
	}
	else {
		iTotalVolume = 0;
	}


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if (object->sStockCode == sStockCode) {

			if(object->bSellTry == false){//매도 시도 한적이 없다면, 매수 volume 변화
				//매수 수량이 다르다

				if(object->iBoughtVolume != iTotalVolume){

					FormMain->AddLog("bought 수량 조절 : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iBuyTargetVolume) + ", bought:"+ IntToStr(object->iBoughtVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iBoughtVolume = iTotalVolume;
				}
			}
			else{//매도 volume 변화
				//매도 수량이 다르다

				if(object->iSoldVolume != iTotalVolume){

					FormMain->AddLog("sold 수량 조절 : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iSellTargetVolume) + ", bought:"+ IntToStr(object->iSoldVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iSoldVolume = iTotalVolume;
				}
            }


		}
	}


}

// ---------------------------------------------------------------------------
void __fastcall ThreadKiwoom::UpdateRealData(String sStockCode, String sTime, String sRealMoney, String sRealRatio,
	String sRealTradeMoney, String sRealVolume, String sRealMedo1, String sRealMesu1, String sRealChegyul)
{

	String sRatio;
	String sChegyul;

	TStock* object;

	int iRealMoney;
	double dRealRatio;
	int iRealTradeMoney;
	int iRealVolume;
	int iRealMedo1;
	int iRealMesu1;
	double dRealChegyul;
	int iSign;

	double dRatioDelta;
	int i10SecTMoney;
	String sTemp1;
	TDateTime dtNow;
	int iNowSec;


	dtNow = Now();
	iNowSec = dtNow.FormatString("hhmmss").ToInt();

	iRealMoney = StrToInt(sRealMoney);
	dRealRatio = StrToFloat(sRealRatio);
	iRealTradeMoney = StrToInt(sRealTradeMoney);
	iRealVolume = StrToInt(sRealVolume);
	iRealMedo1 = StrToInt(sRealMedo1);
	iRealMesu1 = StrToInt(sRealMesu1);
	dRealChegyul = StrToFloat(sRealChegyul);


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){

			if(iRealVolume > 0){
				iSign = 1;//매수
			}
			else{
				iSign = -1;//매도
            }

			//iRealVolume 을 양수처리
			if(iRealVolume < 0){
				iRealVolume = iRealVolume *-1;
			}

            //iRealMoney 을 양수처리
			if(iRealMoney < 0){
				iRealMoney = iRealMoney *-1;
			}

			//tick count sum
			if(iRealVolume != 1){ //1제외
				object->iReal1SecTickSum++;
			}

			//real data
			object->iRealMoney = iRealMoney;
			object->dRealRatio = dRealRatio;
			object->iRealTradeMoney = iRealTradeMoney;
			object->iRealVolume = iRealVolume;
			object->iRealMedo1 = iRealMedo1;
			object->iRealMesu1 = iRealMesu1;
			object->dRealChegyul = dRealChegyul;


			//1sec changed
			if(object->iRealNowSec != iNowSec){
				object->iRealNowSec = iNowSec;


				//-
                //1초 거래대금
				for(int k=9; k>=1; k--){
					object->iReal1SecTradeMoney[k] = object->iReal1SecTradeMoney[k-1];
				}

                //매수 강세명 +, 매도 강세면 -
				object->iReal1SecTradeMoney[0] = object->iReal1SecMesuSum - object->iReal1SecMedoSum;


				//10초 증가 trade money => 수정했습니다.
                i10SecTMoney = 0;
				for(int k=0; k<10; k++){
					i10SecTMoney = i10SecTMoney + object->iReal1SecTradeMoney[k];
				}

				object->iReal10SecTradeMoneyDelta = i10SecTMoney;


				//-
				//1초 ratio
				for(int k=9; k>=1; k--){
					object->dReal1SecRatio[k] = object->dReal1SecRatio[k-1];
				}

				object->dReal1SecRatio[0] = dRealRatio;

				//10초 증가 ratio
				if(object->dReal1SecRatio[9] != 0){
					dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[9];
				}

				object->dReal10SecRatioDelta = dRatioDelta;

				//5초 증가 ratio
				if(object->dReal1SecRatio[4] != 0){
					dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[4];
				}
				else{
					if(object->dReal1SecRatio[3] != 0){
						dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[3];
					}
					else{
						if(object->dReal1SecRatio[2] != 0){
							dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[2];
						}
						else{
							if(object->dReal1SecRatio[1] != 0){
								dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[1];
							}
						}
					}
				}

				object->dRealUpRatioDelta = dRatioDelta;

				//tick
				object->iReal1SecTickCount = object->iReal1SecTickSum;

                //-
                //자체 이벤트
				object->iReal1SecChanged = 1;


				//-
				//log
				sTemp1.printf(L"%.2f", dRatioDelta);

				DebugLog( sStockCode ,
					" "+sRealMoney +
					", 1sec_tmoney:"+ IntToStr(object->iReal1SecTradeMoney[0]) +
                    ", 10sec_tmoney:"+ IntToStr(i10SecTMoney) +
					", 10sec_ratio_delta:"+ sTemp1
					);

				//-
				//init
				object->iReal1SecMesuSum = 0;
				object->iReal1SecMedoSum = 0;
                object->iReal1SecTickSum = 0;

			}//1sec changed


            //-
			//거래대금 누적
			if(object->iRealTradeMoneyOLD != 0){//처음 제외

				if(iSign == 1){//매수 sum
					object->iReal1SecMesuSum = object->iReal1SecMesuSum + (iRealTradeMoney - object->iRealTradeMoneyOLD);
				}
				else{//매도 sum
					object->iReal1SecMedoSum = object->iReal1SecMedoSum + (iRealTradeMoney - object->iRealTradeMoneyOLD);
				}
			}

			object->iRealTradeMoneyOLD = iRealTradeMoney;





		}
    }


    /*
    //save real data
	DebugLog( sStockCode,
		sTime +
		" "+sRealMoney +
		", R:"+ sRealRatio +
		", M:"+ sRealTradeMoney +
		", V:"+ sRealVolume +
		", C:"+ sRealChegyul
		);
	*/

}
