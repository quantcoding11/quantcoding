//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "candle_thread.h"
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
	bool bCheck = false;

	//length
	object->dCandle1MinLength[0] = GetCandleRatio(object->iCandle1MinStart[0], object->iCandle1MinEnd[0]);

	//ratio
	object->dCandle1MinRatio[0] = dRatio;

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


    //valid check
	if(object->iCandle1MinStart[0] != 0){
		bCheck = true;
	}

	//1min candle update
	for(int k=9; k>=1; k--){
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

