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
// WMCA_CONNECTED �α��� ����ü
//----------------------------------------------------------------------//
typedef	struct {
	char 	szAccountNo[11];		//���¹�ȣ
	char	szAccountName[40];		//���¸�
    char	act_pdt_cdz3[3];		//��ǰ�ڵ�
    char	amn_tab_cdz4[4];		//�������ڵ�
    char	expr_datez8[8];			//���Ӹ�����
	char	granted;				//�ϰ��ֹ� ������(G:���)
    char	filler[189];			//filler
}ACCOUNTINFO;

typedef struct {
	char    szDate			[14];	// ���ӽð�
	char	szServerName	[15];	// ���Ӽ���
	char	szUserID		[8];	// ������ID
	char    szAccountCount	[3];	// ���¼�
	ACCOUNTINFO	accountlist	[999];	// ���¸��
}LOGININFO;

typedef struct{
	int       TrIndex;
	LOGININFO *pLoginInfo;
}LOGINBLOCK;

//----------------------------------------------------------------------//
// WMCA ����message ����ü
//----------------------------------------------------------------------//
typedef struct  {
	char	msg_cd		[5];	//00000:����, ��Ÿ:������(�ش� �ڵ尪�� �̿��Ͽ� �ڵ����� ������. �ڵ尪�� �������� ����� �� �ֽ��ϴ�.)
	char	user_msg	[80];
} MSGHEADER;


//----------------------------------------------------------------------//
// WMCA TR ���� ����ü
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
	bool __fastcall Connect				(HWND hWnd, DWORD msg, char MediaType,char UserType,const char* szID,const char* szPW, const char* szCertPW);				//����� ���� �� ����
	bool __fastcall Disconnect			();
	bool __fastcall SetServer			(const char* szServer);																										//���Ӽ��� ����(�ʿ��)
	bool __fastcall SetPort				(int port);																													//������Ʈ ����(�ʿ��)
	bool __fastcall IsConnected			();
	bool __fastcall Transact			(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nHeadType=0, int nAccountIndex=0);		//�Ǽ��� �����Ϸ��� Transact()���
	bool __fastcall Query				(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nAccountIndex=0);						//Query()�Լ��� ����ϼ���.
	bool __fastcall Request				(HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, const char* szOpenBranchCode=NULL);
	bool __fastcall Attach				(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);	//�ǽð� �ü� ��û
	bool __fastcall Detach				(HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);	//�ǽð� �ü� ���
	bool __fastcall DetachWindow		(HWND hWnd);																			//�ǽð� �ü� �ϰ����(���������)
	bool __fastcall DetachAll			();																						//�ǽð� �ü� �ϰ����(��ü)
	bool __fastcall SetOption			(const char* szKey,const char* szValue);
	bool __fastcall SetAccountIndexPwd	(const char* pszHashOut,int nAccountIndex,const char* pszPassword);						//�����ε��� �� ��й�ȣ �Է�
	bool __fastcall SetOrderPwd			(const char* pszHashOut,const char* pszPassword);										//�ŷ���й�ȣ �Է�
	bool __fastcall SetAccountNoPwd		(const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);				//���¹�ȣ �� ��й�ȣ �Է�
	bool __fastcall SetHashPwd			(const char* pszHashOut,const char* pszKey,const char* pszPassword);
	bool __fastcall SetAccountNoByIndex	(const char* pszHashOut,int nAccountIndex);						//�����ε����� �ش��ϴ� ���¹�ȣ

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
