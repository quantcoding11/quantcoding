//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "nh_thread.h"
#include "nh_form.h"
#include "candle_thread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ThreadNH::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
ThreadNH* g_ThreadNH;
__fastcall ThreadNH::ThreadNH(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThreadNH::Execute()
{
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------


void __fastcall ThreadNH::UpdateStockData(String sStockCode, String sStockName, String sYesterday, String sKOSPI)
{
	TStock* object;

	int iYesterdayMoney;
	iYesterdayMoney = StrToInt(sYesterday);

	static volatile int index = 0;

	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){
			if(object->iYesterdayMoney == 0){
				index++;
			}

			object->iYesterdayMoney = iYesterdayMoney;

			if(sKOSPI == "코스피"){
				object->sKOSPI_KOSDAQ = "KOSPI";
			}
			else if(sKOSPI == "코스닥"){
				object->sKOSPI_KOSDAQ = "KOSDAQ";
			}
		}

	}

	FormNH->LabelItem->Caption = index;


}
//---------------------------------------------------------------------------

void __fastcall ThreadNH::UpdateRealData(String sStockCode, String sTime, String sRealMoney, String sSign,
	String sRealRatio, String sChange, String sRealVolume, String sMoVolume, String sRealMedo1, String sRealMesu1)
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

    int iChange;
	int iChangeVolume;

	double dRatioDelta;
	int i10SecTMoney;
	String sTemp1;
	TDateTime dtNow;
	int iNowSec;

	String sTemp;
	int iTemp;

	int iTMoney;
	unsigned __int64 tMoney;

	String sTimeMin;

	dtNow = Now();
	iNowSec = dtNow.FormatString("hhmmss").ToInt();


	iRealVolume = StrToInt(sRealVolume);
	iRealMedo1 = StrToInt(sRealMedo1);
	iRealMesu1 = StrToInt(sRealMesu1);


	iChange = StrToInt(sChange);
	iChangeVolume = StrToInt(sMoVolume);

	sTimeMin = sTime.SubString(1,5);//hh:mm:ss

	for (int i = 0; i < g_StockList->objectList->Count; i++) {
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sStockCode == sStockCode){


			//tick count sum
			if(iChangeVolume != 1){ //1제외
				object->iReal1SecTickSum++;
			}

			if(object->sKOSPI_KOSDAQ == "KOSPI"){
				if(sSign == "2"){//상승
					iRealMoney = StrToInt(sRealMoney);

					dRealRatio = StrToFloat(sRealRatio);
				}
				else if(sSign == "5"){//하락
					iRealMoney = StrToInt(sRealMoney);

					dRealRatio = StrToFloat(sRealRatio);
					dRealRatio = dRealRatio * -1;
				}
			}
			else if(object->sKOSPI_KOSDAQ == "KOSDAQ"){
				if(sRealMoney.SubString(1,1) == "2"){//상승
					sTemp = sRealMoney.SubString(2, 7);
					iTemp = StrToInt(sTemp);
					iRealMoney = object->iYesterdayMoney + iTemp;

					dRealRatio = StrToFloat(sRealRatio);
				}
				else if(sRealMoney.SubString(1,1) == "5"){//하락
					sTemp = sRealMoney.SubString(2, 7);
					iTemp = StrToInt(sTemp);
					iRealMoney = object->iYesterdayMoney - iTemp;

					dRealRatio = StrToFloat(sRealRatio);
					dRealRatio = dRealRatio * -1;
				}
			}

			if(dRealRatio != 0){ //xxx.xxx
				dRealRatio = dRealRatio / 1000;
			}

			if(iRealMoney >= iRealMedo1){
				iSign = 1;//매수
			}
			else{
				iSign = -1;//매도
            }


			//real data
			object->iRealMoney = iRealMoney;
			object->dRealRatio = dRealRatio;
			object->iRealVolume = iRealVolume;
			object->iRealMedo1 = iRealMedo1;
			object->iRealMesu1 = iRealMesu1;
			object->sRealTimeMinute = sTimeMin;

            //real time log
			/*
			sTemp.printf(L"%.2f",dRealRatio);
			DebugLog( sStockCode,
				sTime +
				" "+IntToStr(object->iRealMoney) +
				", R:"+ sTemp +
				", V:"+ sRealVolume

				);
			*/


			//거래대금
			tMoney = iRealMoney * iChangeVolume;
			iTMoney = 0;
			if(tMoney != 0){
				tMoney = tMoney / 1000000;
				iTMoney = (int)tMoney;
			}

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

                /*
				//5초 증가 ratio
				if(object->dReal1SecRatio[4] != 0){
					dRatioDelta = object->dReal1SecRatio[0] - object->dReal1SecRatio[4];
				}


				object->dRealUpRatioDelta = dRatioDelta;

				//tick
				object->iReal1SecTickCount = object->iReal1SecTickSum;

                //-
                //자체 이벤트
				object->iReal1SecChanged = 1;
				*/

                /*
				//-
				//1sec log
				sTemp1.printf(L"%.2f", dRatioDelta);

				DebugLog( sStockCode ,
					" "+sRealMoney +
					", 1sec_tmoney:"+ IntToStr(object->iReal1SecTradeMoney[0]) +
					", 10sec_tmoney:"+ IntToStr(i10SecTMoney) +
					", 10sec_ratio_delta:"+ sTemp1
					);
				*/

				//-
				//init
				object->iReal1SecMesuSum = 0;
				object->iReal1SecMedoSum = 0;
				object->iReal1SecTickSum = 0;

			}//1sec changed

		//<- check stock code

			//-
			//거래대금 누적
			if(iSign == 1){//매수
				object->iReal1SecMesuSum = object->iReal1SecMesuSum + iTMoney;
			}
			else{//매도
				object->iReal1SecMedoSum = object->iReal1SecMedoSum + iTMoney;
			}


			//---
			//1min update
			if(object->sRealTimeMinuteOLD != object->sRealTimeMinute){

				//update
				g_ThreadCandle->Update1Min(object, object->sRealTimeMinuteOLD, object->iRealMoney, object->dRealRatio);

				object->sRealTimeMinuteOLD = object->sRealTimeMinute;
			}


			//top
			if(object->iRealMoney > object->iCandle1MinTop[0]){
				object->iCandle1MinTop[0] = object->iRealMoney;
			}

			//bottom
			if(object->iRealMoney < object->iCandle1MinBottom[0]){
				object->iCandle1MinBottom[0] = object->iRealMoney;
			}

			//end
			object->iCandle1MinEnd[0] = object->iRealMoney;

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
