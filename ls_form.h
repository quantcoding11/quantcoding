//---------------------------------------------------------------------------

#ifndef ls_formH
#define ls_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "XA_DATASETLib_OCX.h"
#include "XA_SESSIONLib_OCX.h"
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TFormLS : public TForm
{
__published:	// IDE-managed Components
	TXASession *XASession1;
	TXAQuery *XAQuery1;
	TXAReal *XAReal1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall XASession1Login(TObject *Sender, OLECHAR *szCode, OLECHAR *szMsg);

private:	// User declarations
public:		// User declarations
	__fastcall TFormLS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLS *FormLS;
//---------------------------------------------------------------------------
#endif
