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

				//�ż� �ŵ��� ����
				if((object->iTradeStatus > 0) && (object->iTradeStatus < 99)){
					BuySellLogic(object);
				}


				//�ż�, �ŵ� �����



			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall ThreadKiwoom::BuySellLogic(TStock* object)
{


	switch (object->iTradeStatus) {
		case _BUY_NEW_1: // �ż���ȣ �߻�

			object->iTradeStatus = _BUY_NEW_ACCEPTING_10;
			object->iBoughtVolume = 0;

			// ������ �ż�
			FormKiwoom->BuyStock(object->sStockCode, object->iBuyTargetPrice, object->iBuyTargetVolume);


			break;

	case _SELL_NEW_2: // �űԸŵ�
		object->iTradeStatus = _SELL_NEW_ACCEPTING_20;

		// �ż� �Ϸ� ��ǥ���� ������ �ŵ�
		FormKiwoom->SellStock(object->sStockCode, object->sOrderCode, object->iSellTargetPrice, object->iSellTargetVolume);

		break;

	case _BUY_MODIFY_5://�ż�����
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
	case _SELL_MODIFY_6: // �ŵ�����
		object->iTradeStatus = _SELL_MODIFY_ING_60;

		FormKiwoom->SellChange(object->sStockCode, object->sOrderCode, object->iSellTargetPrice, object->iSellTargetVolume);

		break;


	case _BUY_IMMEDIATE_71:

		//��øż�

		object->iTradeStatus = _BUY_IMMEDIATE_ING_72;
		object->iBoughtVolume = 0;

		FormKiwoom->BuyStockMarketPrice(object->sStockCode, object->iBuyTargetVolume);


		break;
	case _SELL_IMMEDIATE_81:

		object->iTradeStatus = _SELL_IMMEDIATE_82;

		//��øŵ�
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
					if (StrToInt(sOrderCode) > StrToInt(object->sOrderCode)) { //���ο� order code�� ���
						object->sOrderCode = sOrderCode;
					}
				}
				else{
					object->sOrderCode = sOrderCode;
				}
			}


			switch (iStatus) {
				case 0: // "����"

					//�ż�����, �ŵ������� ���
					//���� - Ȯ�� - ���� ������ �̺�Ʈ�� 3�� �߻�
					//����(new order code) - Ȯ��(new order code) - ����(old order code)
					//�������� �������� ó���� order code�� ����ϸ� �ȵ�


					FormMain->AddLog("���� : " + sStockCode + " " + sStockName +  ", order code:" + sOrderCode +
									 ", last order code:" + object->sOrderCode);

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

			if(object->bSellTry == false){//�ŵ� �õ� ������ ���ٸ�, �ż� volume ��ȭ
				//�ż� ������ �ٸ���

				if(object->iBoughtVolume != iTotalVolume){

					FormMain->AddLog("bought ���� ���� : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iBuyTargetVolume) + ", bought:"+ IntToStr(object->iBoughtVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iBoughtVolume = iTotalVolume;
				}
			}
			else{//�ŵ� volume ��ȭ
				//�ŵ� ������ �ٸ���

				if(object->iSoldVolume != iTotalVolume){

					FormMain->AddLog("sold ���� ���� : " + object->sStockCode + " " + object->sStockName +
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
				iSign = 1;//�ż�
			}
			else{
				iSign = -1;//�ŵ�
            }

			//iRealVolume �� ���ó��
			if(iRealVolume < 0){
				iRealVolume = iRealVolume *-1;
			}

            //iRealMoney �� ���ó��
			if(iRealMoney < 0){
				iRealMoney = iRealMoney *-1;
			}

			//tick count sum
			if(iRealVolume != 1){ //1����
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
                //1�� �ŷ����
				for(int k=9; k>=1; k--){
					object->iReal1SecTradeMoney[k] = object->iReal1SecTradeMoney[k-1];
				}

                //�ż� ������ +, �ŵ� ������ -
				object->iReal1SecTradeMoney[0] = object->iReal1SecMesuSum - object->iReal1SecMedoSum;


				//10�� ���� trade money => �����߽��ϴ�.
                i10SecTMoney = 0;
				for(int k=0; k<10; k++){
					i10SecTMoney = i10SecTMoney + object->iReal1SecTradeMoney[k];
				}

				object->iReal10SecTradeMoneyDelta = i10SecTMoney;


				//-
				//1�� ratio
				for(int k=9; k>=1; k--){
					object->dReal1SecRatio[k] = object->dReal1SecRatio[k-1];
				}

				object->dReal1SecRatio[0] = dRealRatio;

				//10�� ���� ratio
				if(object->dReal1SecRatio[9] != 0){
					dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[9];
				}

				object->dReal10SecRatioDelta = dRatioDelta;

				//5�� ���� ratio
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
                //��ü �̺�Ʈ
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
			//�ŷ���� ����
			if(object->iRealTradeMoneyOLD != 0){//ó�� ����

				if(iSign == 1){//�ż� sum
					object->iReal1SecMesuSum = object->iReal1SecMesuSum + (iRealTradeMoney - object->iRealTradeMoneyOLD);
				}
				else{//�ŵ� sum
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
