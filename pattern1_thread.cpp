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

	while (!Terminated) {

		if (g_bClosing == false) {
			dtNow = Now();
			iNowSec = dtNow.FormatString("hhmmss").ToInt();

			for (int i = 0; i < g_StockList->objectList->Count; i++){
				object = (TStock*)g_StockList->objectList->Items[i];


				if(object->iReal1SecChanged == 1){//자체 이벤트
					object->iReal1SecChanged = 0;
					object->bEvent1SecCheck = true;

                    /*
                    //급등주 패턴
					if(	(object->iReal10SecTradeMoneyDelta >= 200) && //10sec trade money 2억
						(object->dReal10SecRatioDelta >= 1.5)){ //10sec ratio delta 1.5%

						FormMain->Memo2->Lines->Add(dtNow.FormatString("hh:nn:ss") +" "+ object->sStockName);

						//키움hts 종목 변경
						FormMain->ChangeHTSCode(object->sStockCode);

						sTemp1.printf(L"%.2f", object->dReal10SecRatioDelta);
						FormMain->AddLog("급등 > "+ dtNow.FormatString("hh:nn:ss") +" "+
							object->sStockCode +" "+ object->sStockName +
							", now:"+ IntToStr(object->iRealMoney) +
							", 10sec_money:"+ IntToStr(object->iReal10SecTradeMoneyDelta) +
							", 10sec_ratio:"+ sTemp1);

					}
					*/


					//장초반 급등주 찾기
					if(
						(iNow <= 905) && //9:00 ~ 9:01
						(iFindIndex < 11) && //11개만 찾기

//                        (object->iReal10SecTradeMoneyDelta >= 100) && //1억
						(object->iReal1SecTickCount >= 20) && //1sec tick
						(object->dRealUpRatioDelta >= 1.0) && //ratio delta 1.0%

						//(object->bPattern1Clear == false) &&
						(object->bPattern1Find == false) ){

						object->bPattern1Find = true;
						iFindIndex++;

						FormMain->Memo2->Lines->Add(dtNow.FormatString("hh:nn:ss") +" "+ object->sStockName);

						//키움hts 종목 변경
						FormMain->ChangeHTSCode(object->sStockCode);

						sTemp1.printf(L"%.2f", object->dRealUpRatioDelta);
						FormMain->AddLog("급등 > "+ dtNow.FormatString("hh:nn:ss") +" "+
							object->sStockCode +" "+ object->sStockName +
							", now:"+ IntToStr(object->iRealMoney) +
							", ratio delta:"+ sTemp1);
					}


				}//iReal1SecChanged


				/*
				if(object->iEventNowSec != iNowSec){
					object->iEventNowSec = iNowSec;

					//장초반 조용한 종목 체크
					if(	(object->bEvent1SecCheck == false) &&
						(object->iRealMoney != 0) ){
						object->iEvent1SecSilentCount++;
					}

					if(object->iEvent1SecSilentCount > 3){
						object->bPattern1Clear = true;
					}


				}//thread 1sec
				*/


			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}

}
//---------------------------------------------------------------------------

