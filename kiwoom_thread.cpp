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
			FormKiwoom->BuyStock(object->sStockCode, object->iBuyTarget, object->iBuyVolume);


			break;

	case _SELL_NEW_2: // 신규매도
		object->iTradeStatus = _SELL_NEW_ACCEPTING_20;

		// 매수 완료 목표가로 지정가 매도
		FormKiwoom->SellStock(object->sStockCode, object->sOrderCode, object->iSellTarget, object->iSellVolume);

		break;

	case _BUY_MODIFY_5://매수정정
		object->iTradeStatus = _BUY_MODIFY_ING_50;

		FormKiwoom->BuyChange(object->sStockCode, object->sOrderCode,object->iBuyTarget, object->iBuyVolume);

		break;
	case _SELL_CANCEL_4:
        object->iTradeStatus = _SELL_CANCEL_ING_40;

		FormKiwoom->SellCancel(object->sStockCode, object->sOrderCode, object->iSellVolume);


		break;
	case _BUY_CANCEL_3:
		object->iTradeStatus = _BUY_CANCEL_ING_30;

		FormKiwoom->BuyCancel(object->sStockCode, object->sOrderCode, object->iBuyVolume);

		break;
	case _SELL_MODIFY_6: // 매도정정
		object->iTradeStatus = _SELL_MODIFY_ING_60;

		FormKiwoom->SellChange(object->sStockCode, object->sOrderCode, object->iSellTarget, object->iSellVolume);

		break;


	case _BUY_IMMEDIATE_71:

		//즉시매수

		object->iTradeStatus = _BUY_IMMEDIATE_ING_72;
		object->iBoughtVolume = 0;

		FormKiwoom->BuyStockMarketPrice(object->sStockCode, object->iBuyVolume);


		break;
	case _SELL_IMMEDIATE_81:

		object->iTradeStatus = _SELL_IMMEDIATE_82;

		//즉시매도
		FormKiwoom->SellStockMarketPrice(object->sStockCode, object->sOrderCode, object->iSellVolume);

		break;
	}



}
// ---------------------------------------------------------------------------


void __fastcall ThreadKiwoom::UpdateStockInfo(String sStockCode, String sStockName, String sOrderCode,
	int iStatus, String sType, String sTradePrice, String sTradeVolume, String sTradeVolumeSplit,
	String sOrderVolume)
{

	TStock* object;


	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if (object->sStockCode == sStockCode) {

			switch (iStatus) {
				case 0: // "접수"

					//매수정정, 매도정정의 경우
					//접수 - 확인 - 접수 순서로 이벤트가 3번 발생
					//접수(new order code) - 확인(new order code) - 접수(old order code)
					//마지막에 접수에서 처리된 order code를 사용하면 안됨

					if (StrToInt(sOrderCode) > StrToInt(object->sOrderCode)) { //새로운 order code만 사용
						object->sOrderCode = sOrderCode;
					}

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

			if(object->bSellTry == false){
				//매수 수량이 다르다

				if(object->iBoughtVolume != iTotalVolume){

					FormMain->AddLog("bought 수량 조절 !! : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iBuyVolume) + ", bought:"+ IntToStr(object->iBoughtVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iBoughtVolume = iTotalVolume;
				}
			}
			else{
				//매도 수량이 다르다

				if(object->iSoldVolume != iTotalVolume){

					FormMain->AddLog("sold 수량 조절 !! : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iSellVolume) + ", bought:"+ IntToStr(object->iSoldVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iSoldVolume = iTotalVolume;
				}
            }


		}
	}


}

// ---------------------------------------------------------------------------