//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ls_form.h"
#include "main.h"

#include <iniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XA_DATASETLib_OCX"
#pragma link "XA_SESSIONLib_OCX"
#pragma resource "*.dfm"
TFormLS *FormLS;
//---------------------------------------------------------------------------
__fastcall TFormLS::TFormLS(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLS::Button2Click(TObject *Sender)
{
//connect
	XASession1->ConnectServer(L"api.ls-sec.co.kr", 20001);
}
//---------------------------------------------------------------------------
void __fastcall TFormLS::Button1Click(TObject *Sender)
{
//login
	TIniFile* fIni = new TIniFile(g_AppDir + "config.ini");

	String sID, sPass, sCert;

	try {
		sID = fIni->ReadString("ls", "id", "");     //ls 계정
		sPass = fIni->ReadString("ls", "pass", ""); //ls 계정
		sCert = fIni->ReadString("ls", "cert", ""); //공인인증

	}
	__finally {
		delete fIni;
	}


	XASession1->Login(sID.w_str(), sPass.w_str(), sCert.w_str(), 1, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormLS::XASession1Login(TObject *Sender, OLECHAR *szCode, OLECHAR *szMsg)

{
    FormMain->AddLog("ls login ok");
}
//---------------------------------------------------------------------------
