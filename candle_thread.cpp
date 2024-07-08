//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "candle_thread.h"
#include "main.h"
#include <math.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ThreadCandle::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
ThreadCandle* g_ThreadCandle;
__fastcall ThreadCandle::ThreadCandle(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThreadCandle::Execute()
{
	TStock* object;
	TDateTime dtNow;


	while (!Terminated) {

		if (g_bClosing == false) {
			dtNow = Now();


			for (int i = 0; i < g_StockList->objectList->Count; i++){
				object = (TStock*)g_StockList->objectList->Items[i];


			}

			WaitForSingleObject((void*)this->Handle, 100);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ThreadCandle::Update1Min(TStock* object, String sLastTime, int iNow, double dRatio)
{
	String sTemp;
	String sTemp1, sTemp2, sTemp3;
	bool bCheck = false;

	//length
	object->dCandle1MinLength[0] = GetCandleRatio(object->iCandle1MinStart[0], object->iCandle1MinEnd[0]);


	//log
	if(object->iCandle1MinStart[0] != 0){

		sTemp.printf(L"%.2f", object->dCandle1MinLength[0]);
		DebugLog( object->sStockCode+"_1min" ,
			" time:"+ sLastTime +
			", start:"+ IntToStr(object->iCandle1MinStart[0]) +
			", top:"+ IntToStr(object->iCandle1MinTop[0]) +
			", bottom:"+ IntToStr(object->iCandle1MinBottom[0]) +
			", end:"+ IntToStr(object->iCandle1MinEnd[0]) +
			", length:"+ sTemp
			);

	}



	//이동 평균
	CheckMovingAvg(object, 5);
	CheckMovingAvg(object, 10);
	CheckMovingAvg(object, 20);

	/*
	//log
	sTemp1.printf(L"%.2f", object->dMovingAvg5[0]);
	sTemp2.printf(L"%.2f", object->dMovingAvg10[0]);
	sTemp3.printf(L"%.2f", object->dMovingAvg20[0]);

	DebugLog( object->sStockCode+"_avg" ,
		" time:"+ sLastTime +
		", 5min:"+ sTemp1 +
		", 10min:"+ sTemp2 +
		", 20min:"+ sTemp3
		);
	*/

	//bolinger band
	CheckBolingerCenter(object);//중심선
	Check1MinBolinger(object);//top, bottom

	sTemp1.printf(L"%.2f", object->dBolingerCenter[0]);
	sTemp2.printf(L"%.2f", object->dBolingerTop[0]);
	sTemp3.printf(L"%.2f", object->dBolingerBottom[0]);

	DebugLog( object->sStockCode+"_bolinger" ,
		" time:"+ sLastTime +
		", center:"+ sTemp1 +
		", top:"+ sTemp2 +
		", bottom:"+ sTemp3
		);


    //valid check
	if(object->iCandle1MinStart[0] != 0){
		bCheck = true;
	}

	//1min candle update
	for(int k=29; k>=1; k--){
		object->iCandle1MinStart[k] 	= object->iCandle1MinStart[k-1];
		object->iCandle1MinTop[k] 		= object->iCandle1MinTop[k-1];
		object->iCandle1MinBottom[k] 	= object->iCandle1MinBottom[k-1];
		object->iCandle1MinEnd[k] 		= object->iCandle1MinEnd[k-1];
		object->dCandle1MinLength[k] 	= object->dCandle1MinLength[k-1];
		object->dCandle1MinRatio[k] 	= object->dCandle1MinRatio[k-1];
	}

	//init
	object->iCandle1MinStart[0] = iNow;
	object->iCandle1MinTop[0] = iNow;
	object->iCandle1MinBottom[0] = iNow;
	object->iCandle1MinEnd[0] = iNow;
	object->dCandle1MinRatio[0] = dRatio;

    //update 1min
	if(bCheck == true){
		object->iReal1MinChanged = 1;
	}

}
//---------------------------------------------------------------------------
double __fastcall ThreadCandle::GetCandleRatio(int iStart, int iEnd)
{
	double dRatio = 0;

	if((iStart != 0) && (iEnd != 0)){
		dRatio = iEnd - iStart;
		dRatio = dRatio / iStart * 100;
	}

	return dRatio;
}
//---------------------------------------------------------------------------
void __fastcall ThreadCandle::CheckMovingAvg(TStock* object, int iType)
{

	double dTemp;
	int iTemp;

	dTemp = 0;
	iTemp = 0;

	//sum
	for (int k = 0; k < iType; k++) {
		if (object->iCandle1MinEnd[k] != 0) {
			dTemp = dTemp + object->iCandle1MinEnd[k];
			iTemp++;
		}
	}

	//평균 구하기
	if ((dTemp != 0) && (iTemp != 0)) {
		dTemp = dTemp / iTemp;
	}


	if(iType == 5){//5분
		for (int k = 9; k >= 1; k--) {
			object->dMovingAvg5[k] = object->dMovingAvg5[k-1];
		}
		object->dMovingAvg5[0] = dTemp;
	}

	else if(iType == 10){//10분
		for (int k = 9; k >= 1; k--) {
			object->dMovingAvg10[k] = object->dMovingAvg10[k-1];
		}
		object->dMovingAvg10[0] = dTemp;
	}
	else if(iType == 20){//20분
		for (int k = 9; k >= 1; k--) {
			object->dMovingAvg20[k] = object->dMovingAvg20[k-1];
		}
		object->dMovingAvg20[0] = dTemp;
	}



}
//---------------------------------------------------------------------------

void __fastcall ThreadCandle::CheckBolingerCenter(TStock* object)
{

	double dValue;
	double dTemp;
	int iTemp;

	dTemp = 0;
	iTemp = 0;

	int iCandle1MinTop[30];
	int iCandle1MinBottom[30];
	int iCandle1MinEnd[30];

	//sum
	for (int k = 0; k < 20; k++) { //20 중심선
		if (object->iCandle1MinEnd[k] != 0) {

			//top, bottom, end 평균
			dValue =  (object->iCandle1MinTop[k] + object->iCandle1MinBottom[k] + object->iCandle1MinEnd[k]);
			dValue = dValue /3;
            object->dBolingerCandleAvg[k] = dValue;//평균값

			dTemp = dTemp + dValue;

			iTemp++;
		}
	}

	//평균 구하기
	if ((dTemp != 0) && (iTemp != 0)) {
		dTemp = dTemp / iTemp;
	}


	//bolinger center
	for (int k = 9; k >= 1; k--) {
		object->dBolingerCenter[k] = object->dBolingerCenter[k-1];
	}
	object->dBolingerCenter[0] = dTemp;




}
//---------------------------------------------------------------------------
void __fastcall ThreadCandle::Check1MinBolinger(TStock* object)
{

	double dTemp;
	double dValue;
	int iTemp;

	double dBolDev;
	double dBolTop;
	double dBolBottom;

    String sTemp, sTemp1, sTemp2, sTemp3;

	dTemp = 0;
	iTemp = 0;


	for (int k = 0; k < 20; k++) { //20 중심선

		if(object->dBolingerCandleAvg[k] != 0){

			dValue = object->dBolingerCandleAvg[k] - object->dBolingerCenter[0];//편차

			dTemp = dTemp + pow(dValue, 2);

			iTemp++;
		}
	}

	if((dTemp != 0) && (iTemp != 0)){
		dTemp = dTemp / iTemp;//분산
		dBolDev = sqrt(dTemp);//표준편차
	}


	//bolinger top, bottom
	dBolTop = object->dBolingerCenter[0] + dBolDev *2.0;
	dBolBottom = object->dBolingerCenter[0] - dBolDev *2.0;



	for (int k = 9; k >= 1; k--) {
		object->dBolingerTop[k] = object->dBolingerTop[k-1];
		object->dBolingerBottom[k] = object->dBolingerBottom[k-1];
	}

	object->dBolingerTop[0] = dBolTop;
	object->dBolingerBottom[0] = dBolBottom;

}
//---------------------------------------------------------------------------
