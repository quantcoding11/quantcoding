//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KHOpenAPILib_OCX"
#pragma resource "*.dfm"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject* Sender)
{
    //로그인
    KHOpenAPI1->CommConnect();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KHOpenAPI1EventConnect(TObject *Sender, long nErrCode)

{
	if (nErrCode == 0) {
		AddLog("kiwoom login ok");
	} else {
		AddLog("kiwoom login failed ");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject* Sender)
{
	//조건식 가져오기
	GridInitList();

	KHOpenAPI1->GetConditionLoad();
}
//---------------------------------------------------------------------------


WideString __fastcall TForm1::GetScrNum()
{
    static int iscrum = 5000;

    WideString aa;
    if (iscrum < 5100)
        iscrum++;
    else
        iscrum = 5000;

    aa = IntToStr(iscrum);
    return aa;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GridInitList()
{
    //grid update
    //list
    TStringGrid* pGrid = StringGridList;

    for (int i = 0; i < 20; i++) {
        pGrid->Cols[i]->Clear();
	}

    pGrid->RowCount = 2;

    pGrid->Cells[0][0] = "No";
    pGrid->Cells[1][0] = "조건식";
}
//---------------------------------------------------------------------------

//내 조건식
void __fastcall TForm1::UpdateConditionList(String sNo, String sName)
{
    //grid update
    TStringGrid* pGrid = StringGridList;
    int index;

    index = pGrid->RowCount - 1;

    pGrid->RowCount = pGrid->RowCount + 1;
    pGrid->ColCount = 2;
    pGrid->FixedRows = 1;

    pGrid->Cells[0][index] = sNo;
    pGrid->Cells[1][index] = sName;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GridInitItem()
{
    //grid update
    //list
    TStringGrid* pGrid = StringGridLiteItem;

    for (int i = 0; i < 20; i++) {
        pGrid->Cols[i]->Clear();
    }

    pGrid->RowCount = 2;

    pGrid->Cells[0][0] = "No";
    pGrid->Cells[1][0] = "조건식";
    pGrid->Cells[2][0] = "code";
    pGrid->Cells[3][0] = "name";
}
//---------------------------------------------------------------------------
//내 조건식
void __fastcall TForm1::UpdateConditionItem(String sNo, String sConditionName, String sCode)
{
	String sName;
	//종목 코드로 종목 이름을 가져온다
	sName = KHOpenAPI1->GetMasterCodeName(sCode);


    //grid update
    TStringGrid* pGrid = StringGridLiteItem;
    int index;

    index = pGrid->RowCount - 1;

    pGrid->RowCount = pGrid->RowCount + 1;
    pGrid->ColCount = 4;
    pGrid->FixedRows = 1;

    pGrid->Cells[0][index] = sNo;
    pGrid->Cells[1][index] = sConditionName;
    pGrid->Cells[2][index] = sCode;
    pGrid->Cells[3][index] = sName;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::RequestCondition(String sNo, String sName)
{
    WideString scrum = GetScrNum();
    WideString wCondition;

    int index = -1;

    wCondition = sName;
    index = StrToInt(sNo);

    //BSTR
    KHOpenAPI1->SendCondition(scrum.c_bstr(), wCondition.c_bstr(), index, 0);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::StringGridListClick(TObject* Sender)
{
    m_sSelectCondition = StringGridList->Cells[1][m_iSelectRowList];
    if (m_sSelectCondition != "") {
        m_iSelectIndex = StrToInt(StringGridList->Cells[0][m_iSelectRowList]);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject* Sender)
{
	//조건검색
	String sNo, sName;
	int iReturn;

    sNo = m_iSelectIndex;
    sName = m_sSelectCondition;

    if (sName == "") {
        return;
    }

    GridInitItem();

	WideString scrum = GetScrNum();
//	WideString scrum = "9998";
    WideString wCondition;

    int index = -1;

    wCondition = sName;
    index = StrToInt(sNo);

	//iReturn = KHOpenAPI1->SendCondition(scrum, wCondition, index, 0); //조건
	iReturn = KHOpenAPI1->SendCondition(scrum, wCondition, index, 1);//조건 +실시간

	if(iReturn == 0){
		//요청한 조건식이 없거나 조건 고유번호와 조건명이 서로 안맞거나 조회횟수를 초과하는 경우 실패하게 됩니다.
		AddLog("SendCondition 요청 실패");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridListSelectCell(
    TObject* Sender, int ACol, int ARow, bool &CanSelect)
{
    m_iSelectRowList = ARow;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddLog(String sMsg)
{
    Memo1->Lines->Add(sMsg);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::KHOpenAPI1ReceiveChejanData(TObject *Sender, WideString sGubun,
          long nItemCnt, WideString sFIdList)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KHOpenAPI1ReceiveConditionVer(TObject *Sender, long lRet,
          WideString sMsg)
{


	//조건식

	if(lRet != 1){
        AddLog("조회 실패");
	}

    String conditionList;

    //조건식 결과
    conditionList = KHOpenAPI1->GetConditionNameList();

    //    001^abc;002^abc;000^abc

    TStringList* SL = new TStringList;
    int iLine;

    try {
		SL->Delimiter = ';';
        SL->DelimitedText = conditionList;

        iLine = SL->Count - 1;
        for (int i = 0; i < iLine; i++) {
            TStringList* temp = new TStringList;

            temp->Delimiter = '^';
            temp->DelimitedText = SL->Strings[i];

            UpdateConditionList(temp->Strings[0], temp->Strings[1]);

            delete temp;
        }
    } __finally
    {
        delete SL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KHOpenAPI1ReceiveInvestRealData(TObject *Sender, WideString sRealKey)

{
//
}
//---------------------------------------------------------------------------



void __fastcall TForm1::KHOpenAPI1ReceiveRealData(TObject *Sender, WideString sRealKey,
          WideString sRealType, WideString sRealData)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KHOpenAPI1ReceiveTrCondition(TObject *Sender, WideString sScrNo,
          WideString strCodeList, WideString strConditionName, int nIndex,
          int nNext)
{
	//조건 종목

    TStringList* SL = new TStringList;
    int iLine;

	//종목코드 리스트는 각 종목코드가 ';'로 구분되서 전달됩니다.

    WideString sCode;
    WideString sName;

	try {
        SL->Delimiter = ';';
        SL->DelimitedText = strCodeList;

        iLine = SL->Count;

        for (int i = 0; i < iLine; i++) {
            if (SL->Strings[i] != "") {
                sCode = SL->Strings[i];


				UpdateConditionItem(IntToStr(i), strConditionName, sCode);
            }
        }
    } __finally
    {
        delete SL;
    }

    if (nIndex == 2) { //남아있다
        KHOpenAPI1->SendCondition(sScrNo, strConditionName, m_iSelectIndex, 0);
    } else {

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KHOpenAPI1ReceiveTrData(TObject *Sender, WideString sScrNo,
          WideString sRQName, WideString sTrCode, WideString sRecordName,
          WideString sPrevNext, long nDataLength, WideString sErrorCode,
          WideString sMessage, WideString sSplmMsg)
{
//
}
//---------------------------------------------------------------------------



