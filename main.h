//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "KHOpenAPILib_OCX.h"
#include <Vcl.OleCtrls.hpp>
#include <Vcl.Grids.hpp>

#include "global.h"
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TGroupBox *GroupBox1;
	TButton *Button2;
	TStringGrid *StringGridList;
	TButton *Button3;
	TStringGrid *StringGridLiteItem;
	TMemo *Memo1;
	TMainMenu *MainMenu1;
	TMenuItem *file1;
	TMenuItem *N1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall StringGridListClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall StringGridListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);






private:	// User declarations

	int m_iSelectRowList;
	String m_sSelectCondition;


	WideString __fastcall GetScrNum();

	void __fastcall GridInitList();
	void __fastcall GridInitItem();



public:		// User declarations

	int m_iSelectIndex;


    void __fastcall UpdateConditionList(String sNo, String sName);
	void __fastcall RequestCondition(String sNo, String sName);

	void __fastcall UpdateConditionItem(String sNo, String sConditionName, String sCode);

	void __fastcall AddLog(String sMsg);

	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------

extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
