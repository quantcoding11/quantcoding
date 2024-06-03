//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nh_form.h"
#include "main.h"
#include "trio_inv.h"
#include "trio_ord.h"

#include <iniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNH *FormNH;

const	int	TRID_c1101	=1;		//<--예시를 보이기 위함이며 고정값일 필요는 없습니다

const	int	TRID_c8101	=1011; //sell
const	int	TRID_c8102	=1012; //buy
const	int	TRID_c8103	=1013; //modify
const	int	TRID_c8104	=1014; //cancel



//---------------------------------------------------------------------------
__fastcall TFormNH::TFormNH(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::LoadDLL()
{

	m_hDll	= LoadLibraryA("wmca.dll");
	if(m_hDll == NULL){
		FormMain->AddLog("fail load dll");
	}

	m_pLoad					=(TLoad*)					GetProcAddress(m_hDll,"wmcaLoad");
	m_pFree					=(TFree*)					GetProcAddress(m_hDll,"wmcaFree");
	m_pSetServer			=(TSetServer*)				GetProcAddress(m_hDll,"wmcaSetServer");
	m_pSetPort				=(TSetPort*)				GetProcAddress(m_hDll,"wmcaSetPort");
	m_pIsConnected			=(TIsConnected*)			GetProcAddress(m_hDll,"wmcaIsConnected");
	m_pConnect				=(TConnect*)				GetProcAddress(m_hDll,"wmcaConnect");
	m_pDisconnect			=(TDisconnect*)				GetProcAddress(m_hDll,"wmcaDisconnect");
	m_pTransact				=(TTransact*)				GetProcAddress(m_hDll,"wmcaTransact");
	m_pQuery				=(TQuery*)					GetProcAddress(m_hDll,"wmcaQuery");
	m_pRequest				=(TRequest*)				GetProcAddress(m_hDll,"wmcaRequest");
	m_pAttach				=(TAttach*)					GetProcAddress(m_hDll,"wmcaAttach");
	m_pDetach				=(TDetach*)					GetProcAddress(m_hDll,"wmcaDetach");
	m_pDetachWindow			=(TDetachWindow*)			GetProcAddress(m_hDll,"wmcaDetachWindow");
	m_pDetachAll			=(TDetachAll*)				GetProcAddress(m_hDll,"wmcaDetachAll");
	m_pSetOption			=(TSetOption*)				GetProcAddress(m_hDll,"wmcaSetOption");
	m_pSetAccountIndexPwd	=(TSetAccountIndexPwd*)		GetProcAddress(m_hDll,"wmcaSetAccountIndexPwd");
	m_pSetOrderPwd			=(TSetOrderPwd*)			GetProcAddress(m_hDll,"wmcaSetOrderPwd");
	m_pSetHashPwd			=(TSetHashPwd*)				GetProcAddress(m_hDll,"wmcaSetHashPwd");
	m_pSetAccountNoPwd		=(TSetAccountNoPwd*)		GetProcAddress(m_hDll,"wmcaSetAccountNoPwd");
	m_pSetAccountNoByIndex	=(TSetAccountNoByIndex*)	GetProcAddress(m_hDll,"wmcaSetAccountNoByIndex");

}
//---------------------------------------------------------------------------
void __fastcall TFormNH::ConnectNH(AnsiString sID, AnsiString sPass, AnsiString sPublic)
{
	Connect(this->Handle ,CA_WMCAEVENT,'P','1',sID.c_str(), sPass.c_str(), sPublic.c_str());	//QV OpenAPI 사용자용
}
//---------------------------------------------------------------------------
void __fastcall TFormNH::DisconnectNH()
{

	if(IsConnected() == true){
		Disconnect();
	}


	Sleep(100);
	if(IsConnected() == false){
		AddLog("nh disconnected");
	}

	Sleep(100);

	if(m_hDll)
	{
		if(m_pFree)
			m_pFree();

		FreeLibrary(m_hDll);

		m_hDll	=0;
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormNH::OnMessageData(TMessage &Msg)
{

	switch(Msg.WParam){


		case CA_CONNECTED:			//로그인 성공
			OnWmConnected( (LOGINBLOCK*)Msg.LParam );
			break;
		case CA_RECEIVEDATA:		//서비스 응답 수신(TR)
			OnWmReceivedata( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_RECEIVESISE:		//실시간 데이터 수신(BC)
			OnWmReceivesise( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_DISCONNECTED:
			AddLog("접속 끊김");
			break;

		case CA_RECEIVEMESSAGE:
			OnWmReceivemessage( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_RECEIVECOMPLETE:
			AddLog("서비스 처리 완료");
			break;

		case CA_RECEIVEERROR:
            AddLog("서비스 처리중 오류 발생");
			break;

		default:
			break;

	}
}

//---------------------------------------------------------------------------
void __fastcall TFormNH::OnWmConnected( LOGINBLOCK* pLogin )

{

	String ss;
	ss = pLogin->pLoginInfo->szDate;
	AddLog(ss);
    FormMain->AddLog("nh login ok");

}

//---------------------------------------------------------------------------
void __fastcall TFormNH::OnWmReceivesise( OUTDATABLOCK* pSiseData )
{


}

//---------------------------------------------------------------------------

void __fastcall TFormNH::OnWmReceivedata( OUTDATABLOCK* pOutData )
{


}
//---------------------------------------------------------------------------
void __fastcall TFormNH::OnWmReceivemessage( OUTDATABLOCK* pMessage )
{
	MSGHEADER*	pMsgHeader		=(MSGHEADER*)pMessage->pData->szData;

	String sCD, sMsg;
	sCD = pMsgHeader->msg_cd;
	sMsg = pMsgHeader->user_msg;

	AddLog(sCD);
	AddLog(sMsg);
}

//---------------------------------------------------------------------------

bool __fastcall TFormNH::Load()
{
	if(m_pLoad)
		return	m_pLoad();

	return false;
}

bool __fastcall TFormNH::Free()
{
	if(m_pFree)
		return	m_pFree();

	return false;
}

bool __fastcall TFormNH::Connect(HWND hWnd, DWORD msg, char MediaType,char UserType,const char* szID,const char* szPW, const char* szCertPW)
{
	if(m_pConnect)
		return	m_pConnect(hWnd, msg, MediaType,UserType,szID,szPW, szCertPW);

	return false;
}

bool __fastcall TFormNH::Disconnect()
{
	if(m_pDisconnect)
		return m_pDisconnect();

	return false;
}

bool __fastcall TFormNH::Transact(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nHeadType, int nAccountIndex)
{
	if(m_pTransact)
		return m_pTransact(hWnd, nTRID, szTRCode, szInput, nInputLen, nHeadType, nAccountIndex);

	return false;
}

bool __fastcall TFormNH::Query(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nAccountIndex)
{
	if(m_pQuery)
		return m_pQuery(hWnd, nTRID, szTRCode, szInput, nInputLen, nAccountIndex);

	return false;
}

bool __fastcall TFormNH::Request(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, const char* szOpenBranchCode)
{
	if(m_pRequest)
		return m_pRequest(hWnd, nTRID, szTRCode, szInput, nInputLen, szOpenBranchCode);

	return false;
}

bool __fastcall TFormNH::Attach(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen)
{
	if(m_pAttach)
		return m_pAttach(hWnd, szBCType, szInput, nCodeLen, nInputLen);

	return false;
}

bool __fastcall TFormNH::Detach(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen)
{
	if(m_pDetach)
		return m_pDetach(hWnd, szBCType, szInput, nCodeLen, nInputLen);

	return false;
}

bool __fastcall TFormNH::DetachWindow(HWND hWnd)
{
	if(m_pDetachWindow)
		return m_pDetachWindow(hWnd);

	return false;
}

bool __fastcall TFormNH::DetachAll()
{
	if(m_pDetachAll)
		return m_pDetachAll();

	return false;
}

bool __fastcall TFormNH::SetOption(const char* szKey,const char* szValue)
{
	if(m_pSetOption)
		return m_pSetOption(szKey,szValue);

	return false;
}

bool __fastcall TFormNH::SetServer(const char* szServer)
{
	if(m_pSetServer)
		return m_pSetServer(szServer);

	return false;
}

bool __fastcall TFormNH::SetPort(int port)
{
	if(m_pSetPort)
		return m_pSetPort(port);

	return false;
}

bool __fastcall TFormNH::IsConnected()
{
	if(m_pIsConnected)
		return m_pIsConnected();

	return false;
}

bool __fastcall TFormNH::SetAccountIndexPwd		(const char* pszHashOut,int nAccountIndex,const char* pszPassword)
{
	if(m_pSetAccountIndexPwd)
		return m_pSetAccountIndexPwd(pszHashOut,nAccountIndex,pszPassword);

	return false;
}

bool __fastcall TFormNH::SetOrderPwd		(const char* pszHashOut,const char* pszPassword)
{
	if(m_pSetOrderPwd)
		return m_pSetOrderPwd(pszHashOut,pszPassword);

	return false;
}

bool __fastcall TFormNH::SetHashPwd	(const char* pszHashOut,const char* pszKey,const char* pszPassword)
{
	if(m_pSetHashPwd)
		return m_pSetHashPwd(pszHashOut,pszKey,pszPassword);

	return false;
}

bool __fastcall TFormNH::SetAccountNoPwd	(const char* pszHashOut,const char* pszAccountNo,const char* pszPassword)
{
	if(m_pSetAccountNoPwd)
		return m_pSetAccountNoPwd(pszHashOut,pszAccountNo,pszPassword);

	return false;
}

bool __fastcall TFormNH::SetAccountNoByIndex	(const char* pszHashOut,int nAccountIndex)
{
	if(m_pSetAccountNoByIndex)
		return m_pSetAccountNoByIndex(pszHashOut,nAccountIndex);

	return false;
}

//---------------------------------------------------------------------------
void __fastcall TFormNH::AddLog(String sMsg)
{
	Memo1->Lines->Add(sMsg);
}
//---------------------------------------------------------------------------
void __fastcall TFormNH::Button1Click(TObject *Sender)
{
//connect
	FormNH->LoadDLL();

}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button2Click(TObject *Sender)
{
//nh 로그인

	AnsiString sNHID, sNHPass, sNHCert;
	TIniFile* fIni = new TIniFile(g_AppDir + "config.ini");

	try {
		sNHID = fIni->ReadString("nh", "id", "");
		sNHPass = fIni->ReadString("nh", "pass", "");
		sNHCert = fIni->ReadString("nh", "cert", "");
	}
	__finally {
		delete fIni;
	}

	FormNH->ConnectNH(sNHID, sNHPass, sNHCert);
}
//---------------------------------------------------------------------------


