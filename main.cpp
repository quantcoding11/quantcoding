//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "kiwoom_form.h"
#include "kiwoom_thread.h"

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

void __fastcall TFormMain::N1Click(TObject *Sender)
{
    FormKiwoom->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	g_bClosing = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject* Sender)
{
	//�α���
	FormKiwoom->Show();
	FormKiwoom->KHOpenAPI1->CommConnect();
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::Button2Click(TObject* Sender)
{
	//���ǽ� ��������
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
    pGrid->Cells[1][0] = "���ǽ�";
}
//---------------------------------------------------------------------------

//�� ���ǽ�
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
    pGrid->Cells[1][0] = "���ǽ�";
    pGrid->Cells[2][0] = "code";
    pGrid->Cells[3][0] = "name";
}
//---------------------------------------------------------------------------
//�� ���ǽ�
void __fastcall TFormMain::UpdateConditionItem(String sNo, String sConditionName, String sCode)
{
	String sName;
	//���� �ڵ�� ���� �̸��� �����´�
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
	//���ǰ˻�
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

	iReturn = FormKiwoom->KHOpenAPI1->SendCondition(scrum, wCondition, index, 0); //����


	if(iReturn == 0){
		//��û�� ���ǽ��� ���ų� ���� ������ȣ�� ���Ǹ��� ���� �ȸ°ų� ��ȸȽ���� �ʰ��ϴ� ��� �����ϰ� �˴ϴ�.
		AddLog("SendCondition ��û ����");
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


	//kiwoom thread start
	g_ThreadKiwoom = new ThreadKiwoom(true);
	g_ThreadKiwoom->Start();



}
//---------------------------------------------------------------------------




