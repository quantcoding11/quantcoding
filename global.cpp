//---------------------------------------------------------------------------

#pragma hdrstop

#include "global.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

String g_AppDir;
bool g_bClosing;
String g_sKiwoomAcountNo;

//---------------------------------------------------------------------------
void __fastcall DebugLog(String title, AnsiString Msg)
{
	if(Msg.Trim() == "")
		return;

	SYSTEMTIME st;
    HANDLE hFile;

	GetLocalTime(&st);

	WideString sTime;
	WideString sFile;
    UTF8String utf8;

	sFile = g_AppDir + "log\\" + Now().FormatString("yyyymmdd") +"\\"+ title +".txt";

	sTime.printf(L"%02d:%02d:%02d.%03d => ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    utf8 = sTime + Msg + "\r\n";

    hFile = CreateFile(sFile.c_bstr(), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile != INVALID_HANDLE_VALUE){
        unsigned long written;
        SetFilePointer(hFile, 0, NULL, FILE_END);
        WriteFile(hFile, utf8.c_str(), utf8.Length(), &written, NULL);
        CloseHandle(hFile);
    }

}
//---------------------------------------------------------------------------