//---------------------------------------------------------------------------

#ifndef pattern1_threadH
#define pattern1_threadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "global.h"
#include "kiwoom_form.h"
//---------------------------------------------------------------------------
class Pattern1_Thread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Pattern1_Thread(bool CreateSuspended);
};
//---------------------------------------------------------------------------

extern Pattern1_Thread* g_Pattern1_Thread;
#endif
