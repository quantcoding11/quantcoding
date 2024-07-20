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
	unsigned __int64 tMoney;
	int iMoney;

	bool bSilent1MinCandle;


	while (!Terminated) {

		if (g_bClosing == false) {
			dtNow = Now();
			iNow = dtNow.FormatString("hhmm").ToInt();
			iNowSec = dtNow.FormatString("hhmmss").ToInt();

			for (int i = 0; i < g_StockList->objectList->Count; i++){
				object = (TStock*)g_StockList->objectList->Items[i];


				if(object->iReal1SecChanged == 1){//자체 이벤트
					object->iReal1SecChanged = 0;
					object->bEvent1SecCheck = true;

                    /*
                    //---
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

                    /*
					//---
					//조용한 1분 캔들 상태에서, 급등
					if(iNow > 910){ //9:10 부터 체크

                        //1분봉 캔들이 1%이상이 존재하면 제외
						bSilent1MinCandle = true;

						for(int k=0; k<10; k++){
							if(object->dCandle1MinLength[k] >= 1.0){
								bSilent1MinCandle = false;
							}

							if(object->dCandle1MinRatio[k] == 0) {//캔들 체크가 되야함
								bSilent1MinCandle = false;
							}
						}

						//1분 거래대금 1억이상 존재하면 제외
						for(int k=1; k<=10; k++){
							if(object->i1MinTradeMoney[k] >= 100){
								bSilent1MinCandle = false;
							}
						}


						if(	(bSilent1MinCandle == true) &&

							//(object->iReal1SecTradeMoney[0] >= 100) && //10sec 1억 매수

							(object->dRealChegyul > object->d1MinLastChegyul +10) && //체결강도 +10 (키움증권)

							(object->i1MinTradeMoney[0] >= 100) && //1분 캔들기준 1억 매수

							(object->dReal10SecRatioDelta >= 1.5)){ //조용한 캔들 상태에서 급등


							FormMain->Memo2->Lines->Add(dtNow.FormatString("hh:nn:ss") +" "+ object->sStockName);

							//키움hts 종목 변경
							if(iFindIndex <= 11){
								if(object->bPattern1Find == false){
									object->bPattern1Find = true;
									FormMain->ChangeHTSCode(object->sStockCode);
									iFindIndex++;
								}
							}

							sTemp1.printf(L"%.2f", object->dReal10SecRatioDelta);
							FormMain->AddLog("급등 #2 > "+ dtNow.FormatString("hh:nn:ss") +" "+
								object->sStockCode +" "+ object->sStockName +
								", now:"+ IntToStr(object->iRealMoney) +
								", 10sec_money:"+ IntToStr(object->iReal10SecTradeMoneyDelta) +
								", 10sec_ratio:"+ sTemp1);
						}
					}
					*/


				}//iReal1SecChanged



				if(object->iNHGet1101 == 1){ //nh 종목마스터기본 수신
					object->iNHGet1101 = 0;

					tMoney = object->iNHForeMesu - object->iNHForeMesuOLD;
					tMoney = tMoney * object->iNHNowMoney;
					tMoney = tMoney / 1000000; //1백만원 단위
					iMoney = tMoney;

					if(iMoney >= 100){ //1억이상 매수 증가
							FormMain->AddLog("외국인 매수 증가 > "+ dtNow.FormatString("hh:nn:ss") +" "+
								object->sStockCode +" "+ object->sStockName +
								", now:"+ IntToStr(object->iNHNowMoney) +
								", mesu money:"+ IntToStr(iMoney) +
								", mesu_vol:" +IntToStr(object->iNHForeMesu) +
								", mesu_old:"+ IntToStr(object->iNHForeMesuOLD) +
								", medo_vol:"+ IntToStr(object->iNHForeMedo) );
					}

				}





			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}

}
//---------------------------------------------------------------------------

