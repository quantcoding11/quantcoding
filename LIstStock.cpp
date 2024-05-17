//---------------------------------------------------------------------------

#pragma hdrstop

#include "LIstStock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TStocks* g_StockList;

//---------------------------------------------------------------------------
__fastcall TStocks::TStocks()
{
	objectList = new TObjectList();
}
//---------------------------------------------------------------------------
__fastcall TStocks::~TStocks()
{
	objectList->Clear();
	delete objectList;
}
//---------------------------------------------------------------------------
void __fastcall TStocks::Add(TStock* object)
{
	objectList->Add(object);
}
//---------------------------------------------------------------------------
void __fastcall TStocks::Delete(int index)
{
	objectList->Delete(index);
}
//---------------------------------------------------------------------------
void __fastcall TStocks::Clear()
{
	objectList->Clear();
}
//---------------------------------------------------------------------------
bool __fastcall TStocks::CheckAdd(TStock* objectNew)
{
	TStock* object;

	for(int i=0; i<objectList->Count; i++){
		object = (TStock*)objectList->Items[i];
		if(objectNew->sStockCode == object->sStockCode){
			return false;
		}
    }

	return true;
}
//---------------------------------------------------------------------------