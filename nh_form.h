//---------------------------------------------------------------------------

#ifndef nh_formH
#define nh_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "global.h"
#include "ListStock.h"
//---------------------------------------------------------------------------


const	DWORD	CA_WMCAEVENT		=WM_USER+8400;

const	DWORD	CA_CONNECTED		=WM_USER+110;
const	DWORD	CA_DISCONNECTED		=WM_USER+120;
const	DWORD	CA_SOCKETERROR		=WM_USER+130;
const	DWORD	CA_RECEIVEDATA		=WM_USER+210;
const	DWORD	CA_RECEIVESISE		=WM_USER+220;
const	DWORD	CA_RECEIVEMESSAGE	=WM_USER+230;
const	DWORD	CA_RECEIVECOMPLETE	=WM_USER+240;
const	DWORD	CA_RECEIVEERROR		=WM_USER+250;

typedef	String	(__stdcall TGetPass			)();

#define DLLIMP __declspec(dllimport) __stdcall

typedef LPCSTR DLLIMP (* TGET_PUBLIC_PASS)();


typedef	BOOL	(__stdcall TLoad				)();
typedef	BOOL	(__stdcall TFree				)();
typedef	BOOL	(__stdcall TSetServer			)(const char* szServer);
typedef	BOOL	(__stdcall TSetPort				)(const int nPort);
typedef	BOOL	(__stdcall TIsConnected			)();
typedef	BOOL	(__stdcall TConnect				)(HWND hWnd,DWORD dwMsg,char cMediaType,char cUserType,const char* pszID,const char* pszPassword,const char* pszSignPassword);
typedef	BOOL	(__stdcall TDisconnect			)();
typedef	BOOL	(__stdcall TTransact			)(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,int nHeaderType,int nAccountIndex);
typedef	BOOL	(__stdcall TQuery   			)(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,int nAccountIndex);
typedef	BOOL	(__stdcall TRequest				)(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,const char* pszOpenBranchCode);
typedef	BOOL	(__stdcall TAttach				)(HWND hWnd,const char* pszSiseName,const char* pszInputCode,int nInputCodeSize,int nInputCodeTotalSize);
typedef	BOOL	(__stdcall TDetach				)(HWND hWnd,const char* pszSiseName,const char* pszInputCode,int nInputCodeSize,int nInputCodeTotalSize);
typedef	BOOL	(__stdcall TDetachWindow		)(HWND hWnd);
typedef	BOOL	(__stdcall TDetachAll			)();
typedef BOOL	(__stdcall TSetOption			)(const char* szKey,const char* szValue);
typedef BOOL	(__stdcall TSetAccountIndexPwd	)(const char* pszHashOut,int nAccountIndex,const char* pszPassword);
typedef BOOL	(__stdcall TSetOrderPwd			)(const char* pszHashOut,const char* pszPassword);
typedef BOOL	(__stdcall TSetHashPwd			)(const char* pszHashOut,const char* pszKey,const char* pszPassword);
typedef BOOL	(__stdcall TSetAccountNoPwd		)(const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);
typedef BOOL	(__stdcall TSetAccountNoByIndex	)(const char* pszHashOut,int nAccountIndex);

//----------------------------------------------------------------------//
// WMCA_CONNECTED 로그인 구조체
//----------------------------------------------------------------------//
typedef	struct {
	char 	szAccountNo[11];		//계좌번호
	char	szAccountName[40];		//계좌명
    char	act_pdt_cdz3[3];		//상품코드
    char	amn_tab_cdz4[4];		//관리점코드
    char	expr_datez8[8];			//위임만기일
	char	granted;				//일괄주문 허용계좌(G:허용)
    char	filler[189];			//filler
}ACCOUNTINFO;

typedef struct {
	char    szDate			[14];	// 접속시각
	char	szServerName	[15];	// 접속서버
	char	szUserID		[8];	// 접속자ID
	char    szAccountCount	[3];	// 계좌수
	ACCOUNTINFO	accountlist	[999];	// 계좌목록
}LOGININFO;

typedef struct{
	int       TrIndex;
	LOGININFO *pLoginInfo;
}LOGINBLOCK;

//----------------------------------------------------------------------//
// WMCA 문자message 구조체
//----------------------------------------------------------------------//
typedef struct  {
	char	msg_cd		[5];	//00000:정상, 기타:비정상(해당 코드값을 이용하여 코딩하지 마세요. 코드값은 언제든지 변경될 수 있습니다.)
	char	user_msg	[80];
} MSGHEADER;


//----------------------------------------------------------------------//
// WMCA TR 응답 구조체
//----------------------------------------------------------------------//

typedef struct {
	char*	szBlockName;
	char*	szData;
	int	nLen;
} RECEIVED;

typedef struct {
	int		  TrIndex;
	RECEIVED* pData;
} OUTDATABLOCK;

class TFormNH : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *EditStockCode;
	TLabel *Label2;
	TEdit *EditPrice;
	TLabel *Label3;
	TEdit *EditVolume;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TEdit *EditCode;
	TLabel *Label4;
	TGroupBox *GroupBox2;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TTimer *Timer1;
	TButton *Button11;
	TButton *Button12;
	TLabel *LabelItem;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
private:	// User declarations

//add
private:	// User declarations
	TObjectList* NHItemList;


	bool __fastcall Load				();
	bool __fastcall Free				();
	bool __fastcall Connect				(HWND hWnd, DWORD msg, char MediaType,char UserType,const char* szID,const char* szPW, const char* szCertPW);				//사용자 인증 및 접속
	bool __fastcall Disconnect			();
	bool __fastcall SetServer			(const char* szServer);																										//접속서버 지정(필요시)
	bool __fastcall SetPort				(int port);																													//접속포트 지정(필요시)
	bool __fastcall IsConnected			();
	bool __fastcall Transact			(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nHeadType=0, int nAccountIndex=0);		//실수를 방지하려면 Transact()대신
	bool __fastcall Query				(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nAccountIndex=0);						//Query()함수를 사용하세요.
	bool __fastcall Request				(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, const char* szOpenBranchCode=NULL);
	bool __fastcall Attach				(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);	//실시간 시세 요청
	bool __fastcall Detach				(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);	//실시간 시세 취소
	bool __fastcall DetachWindow		(HWND hWnd);																			//실시간 시세 일괄취소(윈도우단위)
	bool __fastcall DetachAll			();																						//실시간 시세 일괄취소(전체)
	bool __fastcall SetOption			(const char* szKey,const char* szValue);
	bool __fastcall SetAccountIndexPwd	(const char* pszHashOut,int nAccountIndex,const char* pszPassword);						//계좌인덱스 및 비밀번호 입력
	bool __fastcall SetOrderPwd			(const char* pszHashOut,const char* pszPassword);										//거래비밀번호 입력
	bool __fastcall SetAccountNoPwd		(const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);				//계좌번호 및 비밀번호 입력
	bool __fastcall SetHashPwd			(const char* pszHashOut,const char* pszKey,const char* pszPassword);
	bool __fastcall SetAccountNoByIndex	(const char* pszHashOut,int nAccountIndex);						//계좌인덱스에 해당하는 계좌번호

	//LRESULT __fastcall WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	void __fastcall AppMessage(tagMSG &Msg, bool &Handled);


void __fastcall OnMessageData(TMessage &Msg);
BEGIN_MESSAGE_MAP
	VCL_MESSAGE_HANDLER(CA_WMCAEVENT, TMessage, OnMessageData)
END_MESSAGE_MAP(TForm)


	void __fastcall OnWmConnected( LOGINBLOCK* pLogin );
	void __fastcall OnWmDisconnected();
	void __fastcall OnWmSocketerror(int socket_error_code);
	void __fastcall OnWmReceivedata( OUTDATABLOCK* pOutData );
	void __fastcall OnWmReceivesise( OUTDATABLOCK* pSiseData );
	void __fastcall OnWmReceivemessage( OUTDATABLOCK* pMessage );
	void __fastcall OnWmReceivecomplete( OUTDATABLOCK* pOutData );
	void __fastcall OnWmReceiveerror( OUTDATABLOCK* pError );


public:		// User declarations

	AnsiString m_sNHID, m_sNHPass, m_sNHCert, m_sAccountPass;
    AnsiString sPresentCode;

	HINSTANCE		m_hDll;

	TLoad					*m_pLoad;
	TFree					*m_pFree;
	TSetServer				*m_pSetServer;
	TSetPort				*m_pSetPort;
	TIsConnected			*m_pIsConnected;
	TConnect				*m_pConnect;
	TDisconnect				*m_pDisconnect;
	TTransact				*m_pTransact;
	TQuery   				*m_pQuery;
	TRequest				*m_pRequest;
	TAttach					*m_pAttach;
	TDetach					*m_pDetach;
	TDetachWindow			*m_pDetachWindow;
	TDetachAll				*m_pDetachAll;
	TSetOption				*m_pSetOption;
	TSetAccountIndexPwd     *m_pSetAccountIndexPwd;
	TSetOrderPwd     		*m_pSetOrderPwd;
	TSetHashPwd     		*m_pSetHashPwd;
	TSetAccountNoPwd     	*m_pSetAccountNoPwd;
	TSetAccountNoByIndex	*m_pSetAccountNoByIndex;


	void __fastcall DisconnectNH();

	void __fastcall LoadDLL();
	void __fastcall ConnectNH(AnsiString sID, AnsiString sPass, AnsiString sPublic);

	void __fastcall GetQuery(AnsiString sCode, int iTRID);

	void __fastcall AttatchKOSPI(AnsiString sCode, int iCount);
	void __fastcall AttatchKOSDAQ(AnsiString sCode, int iCount);


	void __fastcall AddLog(String sMsg);

	__fastcall TFormNH(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNH *FormNH;
//---------------------------------------------------------------------------
#endif
