//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "kiwoom_form.h"
#include "kiwoom_thread.h"
#include "pattern1_thread.h"
#include "nh_form.h"
#include "candle_thread.h"

#include <iniFiles.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KHOpenAPILib_OCX"
#pragma resource "*.dfm"
TFormMain* FormMain;


//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
	g_bClosing = false;
}
//---------------------------------------------------------------------------
__fastcall TFormMain::~TFormMain()
{
    delete g_StockList;

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::N1Click(TObject *Sender)
{
	FormKiwoom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::nhClick(TObject *Sender)
{
	FormNH->Show();
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	g_bClosing = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject* Sender)
{

	//로그인
	FormKiwoom->Show();
	FormKiwoom->KHOpenAPI1->CommConnect();

}
//---------------------------------------------------------------------------


void __fastcall TFormMain::Button2Click(TObject* Sender)
{
	//조건식 가져오기
	GridInitList();

	FormKiwoom->KHOpenAPI1->GetConditionLoad();
}
//---------------------------------------------------------------------------


WideString __fastcall TFormMain::GetScrNum()
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

void __fastcall TFormMain::GridInitList()
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
void __fastcall TFormMain::UpdateConditionList(String sNo, String sName)
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

void __fastcall TFormMain::GridInitItem()
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
void __fastcall TFormMain::UpdateConditionItem(String sNo, String sConditionName, String sCode)
{
	String sName;
	//종목 코드로 종목 이름을 가져온다
	sName = FormKiwoom->KHOpenAPI1->GetMasterCodeName(sCode);


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

void __fastcall TFormMain::RequestCondition(String sNo, String sName)
{
    WideString scrum = GetScrNum();
    WideString wCondition;

    int index = -1;

    wCondition = sName;
    index = StrToInt(sNo);


    FormKiwoom->KHOpenAPI1->SendCondition(scrum.c_bstr(), wCondition.c_bstr(), index, 0);
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::StringGridListClick(TObject* Sender)
{
    m_sSelectCondition = StringGridList->Cells[1][m_iSelectRowList];
    if (m_sSelectCondition != "") {
        m_iSelectIndex = StrToInt(StringGridList->Cells[0][m_iSelectRowList]);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button3Click(TObject* Sender)
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

	iReturn = FormKiwoom->KHOpenAPI1->SendCondition(scrum, wCondition, index, 0); //조건


	if(iReturn == 0){
		//요청한 조건식이 없거나 조건 고유번호와 조건명이 서로 안맞거나 조회횟수를 초과하는 경우 실패하게 됩니다.
		AddLog("SendCondition 요청 실패");
	}

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridListSelectCell(
    TObject* Sender, int ACol, int ARow, bool &CanSelect)
{
    m_iSelectRowList = ARow;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AddLog(String sMsg)
{
	Memo1->Lines->Add(sMsg);

    DebugLog("main", sMsg);
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormShow(TObject *Sender)
{
	g_AppDir = ExtractFilePath(Application->ExeName);

	WideString sPath;
	sPath = "Log";
	CreateDirectory(sPath.c_bstr(), NULL);


	Sleep(100);
	sPath = "Log\\" + Now().FormatString("yyyymmdd");
	CreateDirectory(sPath.c_bstr(), NULL);



	g_StockList = new TStocks();

	//kiwoom thread start
	g_ThreadKiwoom = new ThreadKiwoom(true);
	g_ThreadKiwoom->Start();


	//pattern1 thread start
	g_Pattern1_Thread = new Pattern1_Thread(true);
	g_Pattern1_Thread->Start();


	//candle thread start
	g_ThreadCandle = new ThreadCandle(true);
    g_ThreadCandle->Start();

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeHTSCode(String sCode)
{
	//키움증권 hts code를 변경한다

	HWND handle1 = FindWindow(L"_NKHeroMainClass", NULL);
	HWND handle2 = FindWindowEx(handle1 , NULL, L"MDIClient", NULL);
	HWND handle3 = FindWindowEx(handle2 , NULL, NULL, L"[0101] 키움현재가");
	HWND handle4 = FindWindowEx(handle3 , NULL, L"AfxFrameOrView110", NULL);
	HWND handle5 = FindWindowEx(handle4 , NULL, L"AfxWnd110", NULL);

	HWND handle6 = FindWindowEx(handle5 , NULL, L"AfxWnd110", NULL);
	HWND handle7 = FindWindowEx(handle5 , handle6, L"AfxWnd110", NULL);
	HWND handle8 = FindWindowEx(handle5 , handle7, L"AfxWnd110", NULL);
	HWND handle9 = FindWindowEx(handle5 , handle8, L"AfxWnd110", NULL);
	HWND handle10 = FindWindowEx(handle5 , handle9, L"AfxWnd110", NULL);
	HWND handle11 = FindWindowEx(handle5 , handle10, L"AfxWnd110", NULL);
	HWND handle12 = FindWindowEx(handle5 , handle11, L"AfxWnd110", NULL);

	HWND handle13 = FindWindowEx(handle12 , NULL, L"AfxWnd110", NULL);
	HWND handle14 = FindWindowEx(handle13 , NULL, L"Edit", NULL);

	SendMessage(handle14, 0x000C, 0 ,LPARAM(PChar(sCode.c_str())));
	SendMessage(handle14, 0x0100, 0x0D, 0);

}

//---------------------------------------------------------------------------

void __fastcall TFormMain::add1Click(TObject *Sender)
{
    ChangeHTSCode("005930");
}
//---------------------------------------------------------------------------




