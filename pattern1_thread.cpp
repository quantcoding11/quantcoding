//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "pattern1_thread.h"
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
//      void __fastcall Pattern1_Thread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
Pattern1_Thread* g_Pattern1_Thread;
__fastcall Pattern1_Thread::Pattern1_Thread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall Pattern1_Thread::Execute()
{
	TStock* object;
	TDateTime dtNow;

    String sTemp1;
	volatile int iIndex = 0;

	int iNow;
	int iNowSec;
	volatile int iFindIndex = 0;

	double dTemp;

	bool bSilent1MinCandle;


	while (!Terminated) {

		if (g_bClosing == false) {
			dtNow = Now();
			iNow = dtNow.FormatString("hhmm").ToInt();
			iNowSec = dtNow.FormatString("hhmmss").ToInt();

			for (int i = 0; i < g_StockList->objectList->Count; i++){
				object = (TStock*)g_StockList->objectList->Items[i];


				if(object->iReal1SecChanged == 1){//��ü �̺�Ʈ
					object->iReal1SecChanged = 0;
					object->bEvent1SecCheck = true;

                    /*
                    //---
                    //�޵��� ����
					if(	(object->iReal10SecTradeMoneyDelta >= 200) && //10sec trade money 2��
						(object->dReal10SecRatioDelta >= 1.5)){ //10sec ratio delta 1.5%

						FormMain->Memo2->Lines->Add(dtNow.FormatString("hh:nn:ss") +" "+ object->sStockName);

						//Ű��hts ���� ����
						FormMain->ChangeHTSCode(object->sStockCode);

						sTemp1.printf(L"%.2f", object->dReal10SecRatioDelta);
						FormMain->AddLog("�޵� > "+ dtNow.FormatString("hh:nn:ss") +" "+
							object->sStockCode +" "+ object->sStockName +
							", now:"+ IntToStr(object->iRealMoney) +
							", 10sec_money:"+ IntToStr(object->iReal10SecTradeMoneyDelta) +
							", 10sec_ratio:"+ sTemp1);

					}
					*/

					//---
					//������ 1�� ĵ�� ���¿���, �޵�
					if(iNow > 910){ //9:10 ���� üũ

                        //1�к� ĵ���� 1%�̻��� �����ϸ� ����
						bSilent1MinCandle = true;
						for(int k=1; k<10; k++){
							if(object->dCandle1MinLength[k] >= 1.0){
								bSilent1MinCandle = false;
							}
						}

						if(	(bSilent1MinCandle == true) &&
							(object->dReal10SecRatioDelta >= 1.5)){ //������ ĵ�� ���¿��� �޵�


							FormMain->Memo2->Lines->Add(dtNow.FormatString("hh:nn:ss") +" "+ object->sStockName);

							//Ű��hts ���� ����
							if(iFindIndex <= 11){
								FormMain->ChangeHTSCode(object->sStockCode);
								iFindIndex++;
							}

							sTemp1.printf(L"%.2f", object->dReal10SecRatioDelta);
							FormMain->AddLog("�޵� #2 > "+ dtNow.FormatString("hh:nn:ss") +" "+
								object->sStockCode +" "+ object->sStockName +
								", now:"+ IntToStr(object->iRealMoney) +
								", 10sec_money:"+ IntToStr(object->iReal10SecTradeMoneyDelta) +
								", 10sec_ratio:"+ sTemp1);
						}
					}



				}//iReal1SecChanged




			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}

}
//---------------------------------------------------------------------------

