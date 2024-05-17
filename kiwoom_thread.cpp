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
			FormKiwoom->BuyStock(object->sStockCode, object->iBuyTarget, object->iBuyVolume);


			break;

	case _SELL_NEW_2: // �űԸŵ�
		object->iTradeStatus = _SELL_NEW_ACCEPTING_20;

		// �ż� �Ϸ� ��ǥ���� ������ �ŵ�
		FormKiwoom->SellStock(object->sStockCode, object->sOrderCode, object->iSellTarget, object->iSellVolume);

		break;

	case _BUY_MODIFY_5://�ż�����
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
	case _SELL_MODIFY_6: // �ŵ�����
		object->iTradeStatus = _SELL_MODIFY_ING_60;

		FormKiwoom->SellChange(object->sStockCode, object->sOrderCode, object->iSellTarget, object->iSellVolume);

		break;


	case _BUY_IMMEDIATE_71:

		//��øż�

		object->iTradeStatus = _BUY_IMMEDIATE_ING_72;
		object->iBoughtVolume = 0;

		FormKiwoom->BuyStockMarketPrice(object->sStockCode, object->iBuyVolume);


		break;
	case _SELL_IMMEDIATE_81:

		object->iTradeStatus = _SELL_IMMEDIATE_82;

		//��øŵ�
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
				case 0: // "����"

					//�ż�����, �ŵ������� ���
					//���� - Ȯ�� - ���� ������ �̺�Ʈ�� 3�� �߻�
					//����(new order code) - Ȯ��(new order code) - ����(old order code)
					//�������� �������� ó���� order code�� ����ϸ� �ȵ�

					if (StrToInt(sOrderCode) > StrToInt(object->sOrderCode)) { //���ο� order code�� ���
						object->sOrderCode = sOrderCode;
					}

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

			if(object->bSellTry == false){
				//�ż� ������ �ٸ���

				if(object->iBoughtVolume != iTotalVolume){

					FormMain->AddLog("bought ���� ���� !! : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iBuyVolume) + ", bought:"+ IntToStr(object->iBoughtVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iBoughtVolume = iTotalVolume;
				}
			}
			else{
				//�ŵ� ������ �ٸ���

				if(object->iSoldVolume != iTotalVolume){

					FormMain->AddLog("sold ���� ���� !! : " + object->sStockCode + " " + object->sStockName +
						", ready:"+ IntToStr(object->iSellVolume) + ", bought:"+ IntToStr(object->iSoldVolume) +" => "+
						IntToStr(iTotalVolume));


					object->iSoldVolume = iTotalVolume;
				}
            }


		}
	}


}

// ---------------------------------------------------------------------------