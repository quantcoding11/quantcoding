//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nh_form.h"
#include "nh_thread.h"
#include "main.h"
#include "trio_inv.h"
#include "trio_ord.h"

#include <iniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNH *FormNH;


const	int	TRID_c1101	=1;		//<--���ø� ���̱� �����̸� �������� �ʿ�� �����ϴ�


const	int	TRID_c8101	=8101;
const	int	TRID_c8102	=8102;
const	int	TRID_c8103	=8103;
const	int	TRID_c8104	=8104;

const	int	TRID_c8201	=8201;

const	int	TRID_p1003	= 11003;
const	int	TRID_s4101	= 14101;

const	int	TAG1_KOSPI	= 15001;
const	int	TAG1_KOSDAQ	= 15002;



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
	Connect(this->Handle ,CA_WMCAEVENT,'P','1',sID.c_str(), sPass.c_str(), sPublic.c_str());	//QV OpenAPI ����ڿ�
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


		case CA_CONNECTED:			//�α��� ����
			OnWmConnected( (LOGINBLOCK*)Msg.LParam );
			break;
		case CA_RECEIVEDATA:		//���� ���� ����(TR)
			OnWmReceivedata( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_RECEIVESISE:		//�ǽð� ������ ����(BC)
			OnWmReceivesise( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_DISCONNECTED:
			AddLog("���� ����");
			break;

		case CA_RECEIVEMESSAGE:
			OnWmReceivemessage( (OUTDATABLOCK*)Msg.LParam );
			break;

		case CA_RECEIVECOMPLETE:
			AddLog("���� ó�� �Ϸ�");
			break;

		case CA_RECEIVEERROR:
            AddLog("���� ó���� ���� �߻�");
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
	String ss;
//	ss = pSiseData->pData->szBlockName;
	//Memo1->Lines->Add(ss);


	ss = pSiseData->pData->szBlockName;

//	Tj8OutBlock*	pj8	=(Tj8OutBlock*)(pSiseData->pData->szData+3);

	String sCode;
	String sName;
	String sName2;
	String sTime;
	String sPrice;
	String sVolume;
	String sChange;
	String sSign;

    String sType;
	String sResult;

	String sChrate;
	String sBid;
	String sVolate;
	String sMovolume;
	String sValue;
	String sOpen;
	String sAvgPrice;
	String sJang;

	String sMoVolume;//�����ŷ���
	String sJanggubun;//���� kospi, kosdaq ���� ó��

	String sMedoHoga;
	String sMesuHoga;



	if((ss.SubString(1,2) == "j8") || (ss.SubString(1,2) == "k8")){ //real-time
		Tj8OutBlock*	pj8	=(Tj8OutBlock*)(pSiseData->pData->szData + 3);



		ss = pj8->code;
		sCode = ss.SubString(0, 6);

		ss = pj8->time;
		sTime = ss.SubString(0, 8);

		ss = pj8->price;
		sPrice = ss.SubString(1, 7);


		ss = pj8->volume;
		sVolume = ss.SubString(0, 9);

		ss = pj8->sign;
		sSign = ss.SubString(0, 1);


		ss = pj8->chrate;
		//sChrate = ss.SubString(0, 5);
		sChrate = ss.SubString(0, 6);

		ss = pj8->change;
		sChange = ss.SubString(0, 6);


		ss = pj8->avgprice;
		sAvgPrice = ss.SubString(0, 7);

		ss = pj8->movolume;
		sMoVolume = ss.SubString(0, 8);


		ss = pj8->janggubun;
		sJanggubun = ss.SubString(0, 1);


		ss = pj8->offer;
		sMedoHoga = ss.SubString(0, 7);

		ss = pj8->bid;
		sMesuHoga = ss.SubString(0, 7);


		ss = pj8->open;
		sOpen = ss.SubString(0, 7);


		g_ThreadNH->UpdateRealData(sCode, sTime, sPrice, sSign, sChrate, sChange, sVolume, sMoVolume, sMedoHoga, sMesuHoga);



		/*
		DebugLog( sCode, +" price:"+ sPrice +", vol:"+ sVolume +", chrate:"+ sSign+" "+sChrate + ", change:"+ sChange+ ", move:"+ sMoVolume+

			", medo:"+ sMedoHoga +", mesu:"+sMesuHoga +
			", avg:"+ sAvgPrice + ", open:"+ sOpen  + ", jang:"+ sJanggubun);
		*/


	}
	else if(ss.SubString(1,2) == "d2"){//�ǽð� ü��
		Td2OutBlock*	pd2	=(Td2OutBlock*)(pSiseData->pData->szData + 3);


	}
	else if(ss.SubString(1,2) == "d3"){//�ֹ� �뺸
		Td3OutBlock*	pd3	=(Td3OutBlock*)(pSiseData->pData->szData + 3);

		ss = pd3->issuecd;
		sCode = ss.SubString(0, 15);

		ss = pd3->issuename;
		sName = ss.SubString(0, 20);

		ss = pd3->slbygb;
		sType = ss.SubString(0, 1);

		ss = pd3->ordergty;
		sVolume = ss.SubString(0, 10);

		ss = pd3->orderprc;
		sPrice = ss.SubString(0, 11);

		ss = pd3->procnm;
		sResult = ss.SubString(0, 2);


		ss = "�ֹ��뺸 code:"+ sCode +" , name: "+ sName +" , type: "+ sType +
			", price: "+ sPrice +" , vol: "+ sVolume + ", result: "+ sResult;

		AddLog(ss);

	}
	else if(ss.SubString(1,2) == "u1"){

		Tu1OutBlock*	pu1	=(Tu1OutBlock*)(pSiseData->pData->szData + 3);

		ss = pu1->jisusign;  //+:2, -:5
		sSign = ss.SubString(0, 1);


		ss = pu1->jisu;
		sValue = ss.SubString(0, 8);


		ss = pu1->jisuchrate;
		sChange = ss.SubString(0, 5);


		AddLog("kospi : " + sSign +"  "+ sValue +" "+ sChange);
	}

	else if(ss.SubString(1,2) == "k1"){

		Tu1OutBlock*	pu1	=(Tu1OutBlock*)(pSiseData->pData->szData + 3);

		ss = pu1->jisusign;
		sSign = ss.SubString(0, 1);


		ss = pu1->jisu;
		sValue = ss.SubString(0, 8);

		ss = pu1->jisuchrate;
		sChange = ss.SubString(0, 5);

		AddLog("kosdaq : " + sSign +"  "+ sValue +" "+ sChange);
	}

}

//---------------------------------------------------------------------------

void __fastcall TFormNH::OnWmReceivedata( OUTDATABLOCK* pOutData )
{


	String ss;
	String s1;

	String sCode;
	String sName;
	String sName2;
	String sPrice;
	String sVolume;

	String sSign;
	String sRatio;

	String sKOSPI;
	String sSichong;
	String sYesterdayMoney;

	String sForeMedo;
    String sForeMesu;

//	static int index = 0;


	if((pOutData->TrIndex >= TRID_c1101) && //response
		(pOutData->TrIndex <= TRID_c1101 +5000)){

		ss = pOutData->pData->szBlockName;
		if(ss == "c1101OutBlock"){

			Tc1101OutBlock*	pc1101outblock	=(Tc1101OutBlock*)pOutData->pData->szData;

			ss = pc1101outblock->code;
			sCode = ss.SubString(0, 6);

//			ss = pc1101outblock->hname;
//			sName = ss.SubString(0, 13);
//			sName = sName.Trim();

			ss = pc1101outblock->hnamez21;
			sName2 = ss.SubString(0, 15);
			sName2 = sName2.Trim();

			ss = pc1101outblock->price;
			sPrice = ss.SubString(0, 7);

			ss = pc1101outblock->volume;
			sVolume = ss.SubString(0, 10);

			ss = pc1101outblock->chrate;
			sRatio = ss.SubString(0, 5); //xxx.xx

			ss = pc1101outblock->prepricez7;
			sYesterdayMoney = ss.SubString(0, 7);

			ss = pc1101outblock->sosokz6_1;
			sKOSPI = ss.SubString(0, 3);


			ss = pc1101outblock->N_offvolall;//�ܱ��� �ŵ�
			sForeMedo = ss.SubString(0, 9);

			ss = pc1101outblock->N_bidvolall;//�ܱ��� �ż�
			sForeMesu = ss.SubString(0, 9);



			g_ThreadNH->UpdateStockData(sCode, sName2, sYesterdayMoney, sKOSPI,
				sPrice, sForeMedo, sForeMesu);

			//AddLog(sCode +" "+ sName2 +" "+ sKOSPI +", price"+ sPrice +	", vol:"+ sVolume );

		}


	}
	else if(pOutData->TrIndex == TRID_c8102){

		ss = pOutData->pData->szBlockName;

		if(ss == "c8102OutBlock"){//�ż�
			Tc8102OutBlock*	pc8102OutBlock	=(Tc8102OutBlock*)pOutData->pData->szData;
			String sOrder;

			sOrder = pc8102OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);


			if(sOrder.Trim() == "") {
				AddLog("�ż� �ֹ� ����");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("�ż� �ֹ� ����");
				AddLog(sOrder);
			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8101){
		ss = pOutData->pData->szBlockName;

		if(ss == "c8101OutBlock"){//�ŵ�
			Tc8101OutBlock*	pc8101OutBlock	=(Tc8101OutBlock*)pOutData->pData->szData;
			String sOrder;

			sOrder = pc8101OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);


			if(sOrder.Trim() == "") {
				AddLog("�ŵ� �ֹ� ����");
			}
			else{
                EditCode->Text = sOrder;
				AddLog("�ŵ� �ֹ� ����");
				AddLog(sOrder);
			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8103){
		ss = pOutData->pData->szBlockName;

		if(ss == "c8103OutBlock"){//����
			Tc8103OutBlock*	pc8103OutBlock	=(Tc8103OutBlock*)pOutData->pData->szData;

			String sOrderOrg;
			String sOrder;
			String sOrderMother;
			String sVol;
			String sPrice;

			sOrderOrg = pc8103OutBlock->orgnl_order_noz10;
			sOrderOrg = sOrderOrg.SubString(0, 10);

			sOrder = pc8103OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);

			sOrderMother = pc8103OutBlock->mom_order_noz10;
			sOrderMother = sOrderMother.SubString(0, 10);

			sVol = pc8103OutBlock->crctn_qtyz12;
			sVol = sVol.SubString(0, 12);

			sPrice = pc8103OutBlock->crctn_pricez10;
			sPrice = sPrice.SubString(0, 10);

			if(sOrder.Trim() == "") {
				AddLog("���� �ֹ� ����");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("���� �ֹ� ����");
				AddLog("org order :"+ sOrderOrg);
				AddLog("order :"+ sOrder);
				AddLog("vol :"+ sVol);
				AddLog("price :"+ sPrice);

			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8104){
		ss = pOutData->pData->szBlockName;
		if(ss == "c8104OutBlock"){//���
			Tc8104OutBlock*	pc8104OutBlock	=(Tc8104OutBlock*)pOutData->pData->szData;

			String sOrderOrg;
			String sOrder;
			String sOrderMother;
			String sVol;
			String sPrice;

			sOrderOrg = pc8104OutBlock->orgnl_order_noz10;
			sOrderOrg = sOrderOrg.SubString(0, 10);

			sOrder = pc8104OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);

			sOrderMother = pc8104OutBlock->mom_order_noz10;
			sOrderMother = sOrderMother.SubString(0, 10);

			sVol = pc8104OutBlock->canc_qtyz12;
			sVol = sVol.SubString(0, 12);

			if(sOrder.Trim() == "") {
				AddLog("��� �ֹ� ����");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("��� �ֹ� ����");
				AddLog("org order :"+ sOrderOrg);
				AddLog("order :"+ sOrder);
				AddLog("vol :"+ sVol);
			}

		}

	}
	else if(pOutData->TrIndex == TRID_p1003){ //response
	//���� �ڵ�
		String sCode;
		String sName;

		tagp1003OutBlock*	t1003OutBlock	=(tagp1003OutBlock*)pOutData->pData->szData;

		sCode = t1003OutBlock->codez8;
		sCode = sCode.SubString(0, 8);
		sName = t1003OutBlock->namez30;
		sName = sName.SubString(0, 30);


		sPresentCode = sCode;

		AddLog("���� �ڵ�");
		AddLog(sCode);
		AddLog(sName);

	}

	else if(pOutData->TrIndex == TRID_s4101){ //response
	//����

		tags4101OutBlock*	t4101OutBlock	=(tags4101OutBlock*)pOutData->pData->szData;
//		tags4101OutBlock1*	t4101OutBlock	=(tags4101OutBlock1*)pOutData->pData->szData;

		String sCode;
		String sName;
		String sNow;
		String sSign;
		String sPoint;
		String sRatio;
		String sClose;
		String sChange;

		sCode = t4101OutBlock->fuitem;
		sCode = sCode.SubString(0, 8);

		if((sCode == sPresentCode) && (sPresentCode != "")){
	//		sName = t4101OutBlock->fuhname;
	//		sName = sName.SubString(0, 12);

			sNow = t4101OutBlock->fucurr;
			sNow = sNow.SubString(0, 5);

			sSign = t4101OutBlock->fusign;
			sSign = sNow.SubString(0, 1);

			sPoint = t4101OutBlock->fuchange;
			sPoint = sPoint.SubString(0, 5);

			sRatio = t4101OutBlock->fuchrate;
			sRatio = sRatio.SubString(0, 5);


			sChange = t4101OutBlock->fuchange;
			sChange = sChange.SubString(0, 5);

			sClose = t4101OutBlock->preclose;
			sClose = sClose.SubString(0, 5);

			double dClose;
			double dValue;
			double dRatio;

				dClose = sClose.ToDouble();
				if(dClose != 0){
					dClose = dClose / 100;
				}

				dValue = sNow.ToDouble();
				if(dValue != 0){
					dValue = dValue / 100 ;
				}
				dRatio = sRatio.ToDouble();
				if(dRatio != 0){
					dRatio = dRatio / 100;
				}

				if(dValue < dClose){
					dValue = dValue * -1;
					dRatio = dRatio * -1;
				}

			if((sCode == sPresentCode) && (sPresentCode != "")){
				AddLog("---");
				AddLog("code : "+ sCode);
				AddLog("name :" +sName);
				AddLog("now : "+ sNow);
				AddLog("sign : "+ sSign); //3 => ���̳ʽ�
				AddLog("point :" +sPoint);
				AddLog("ratio :" + sRatio);
				AddLog(FloatToStr(dValue));
			}

        }
	}


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
	if(Memo1->Lines->Count > 1000){
		Memo1->Lines->Clear();
	}

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
//nh �α���


	TIniFile* fIni = new TIniFile(g_AppDir + "config.ini");

	try {
		m_sNHID = fIni->ReadString("nh", "id", "");
		m_sNHPass = fIni->ReadString("nh", "pass", "");
		m_sNHCert = fIni->ReadString("nh", "cert", "");
		m_sAccountPass = fIni->ReadString("nh", "account", "");
	}
	__finally {
		delete fIni;
	}

	FormNH->ConnectNH(m_sNHID, m_sNHPass, m_sNHCert);
}
//---------------------------------------------------------------------------



void __fastcall TFormNH::Button3Click(TObject *Sender)
{
//buy
	AnsiString sPassword, sCode, sVol, sPrice;

	Tc8102InBlock	c8102inblock	={0};
	memset(&c8102inblock,0x20,sizeof (Tc8102InBlock) );

	sCode = EditStockCode->Text;
	sPrice = EditPrice->Text;
	sVol = EditVolume->Text;

	//�� �Է� �ʵ忡�� �䱸�ϴ� ���鿡 ���� ���Ǵ� *.doc ������ ���� Ȯ���� �� �ֽ��ϴ�.
	//���º�й�ȣ�� ��������ȯ�濡���� Ȯ������ ������ ��ȯ�濡���� Ȯ���ϹǷ� ��Ȯ�ϰ� �Է��Ͻñ� �ٶ��ϴ�
	//���º�й�ȣ�� �ŷ�(�ֹ�)��й�ȣ�ʹ� �ٸ��ϴ�. �ŷ���й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.

	SetAccountIndexPwd(c8102inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8102inblock.issue_codez6 , sCode.c_str(), 6);
	strncpy(c8102inblock.order_qtyz12 , sVol.c_str(), 12);
	strncpy(c8102inblock.order_unit_pricez10 , sPrice.c_str(), 10);
	strncpy(c8102inblock.trade_typez2 , "00", 2);


	//�Ʒ� �Է��ϴ� �ŷ���й�ȣ1, 2������ ������� �ŷ���й�ȣ�� �Է��ؾ��մϴ�.
	//�ŷ�(�ֹ�)��й�ȣ�� ���º�й�ȣ�ʹ� �ٸ��� ���º�й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	SetOrderPwd(c8102inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8102inblock.trad_pswd_no_2z8,"########");

	//�ֽ� �ֹ�
	Query(
			this->Handle,			//�� ������� ���� �޽����� �ްڽ��ϴ�.
			TRID_c8102,				//�� ���񽺿� ���ؼ� TRID_c8102 �ĺ��ڸ� ���̰ڽ��ϴ�. (������ ���̸�,�ٸ� ���� �־ ����ϼŵ� �˴ϴ�)
			"c8102",				//ȣ���Ϸ��� ���� �ڵ�� c8102 �Դϴ�.
			(char*)&c8102inblock,	//c8102���� �䱸�ϴ� �Է� ����ü �����͸� �����մϴ�.
			sizeof (Tc8102InBlock),	//�Է� ����ü ũ���Դϴ�
			1			//���ϴ� ���¹�ȣ �ε����� �����մϴ�.		(���¹�ȣ�� '1'������ ����)
	);

	AddLog("try buy");

}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button4Click(TObject *Sender)
{
    //sell
	AnsiString sPassword, sCode, sVol, sPrice;

	Tc8101InBlock	c8101inblock	={0};
	memset(&c8101inblock,0x20,sizeof (Tc8101InBlock) );


	sCode = EditStockCode->Text;
	sPrice = EditPrice->Text;
	sVol = EditVolume->Text;

	//�� �Է� �ʵ忡�� �䱸�ϴ� ���鿡 ���� ���Ǵ� *.doc ������ ���� Ȯ���� �� �ֽ��ϴ�.
	//���º�й�ȣ�� ��������ȯ�濡���� Ȯ������ ������ ��ȯ�濡���� Ȯ���ϹǷ� ��Ȯ�ϰ� �Է��Ͻñ� �ٶ��ϴ�
	//���º�й�ȣ�� �ŷ�(�ֹ�)��й�ȣ�ʹ� �ٸ��ϴ�. �ŷ���й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8101inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8101inblock.issue_codez6 , sCode.c_str(), 6);
	strncpy(c8101inblock.order_qtyz12 , sVol.c_str(), 12);
	strncpy(c8101inblock.order_unit_pricez10 , sPrice.c_str(), 10);
	strncpy(c8101inblock.trade_typez2 , "00", 2);


	//�Ʒ� �Է��ϴ� �ŷ���й�ȣ1, 2������ ������� �ŷ���й�ȣ�� �Է��ؾ��մϴ�.
	//�ŷ�(�ֹ�)��й�ȣ�� ���º�й�ȣ�ʹ� �ٸ��� ���º�й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	SetOrderPwd(c8101inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8101inblock.trad_pswd_no_2z8,"########");

	//�ֽ� �ֹ�
	Query(
			this->Handle,			//�� ������� ���� �޽����� �ްڽ��ϴ�.
			TRID_c8101,				//�� ���񽺿� ���ؼ� TRID_c8102 �ĺ��ڸ� ���̰ڽ��ϴ�. (������ ���̸�,�ٸ� ���� �־ ����ϼŵ� �˴ϴ�)
			"c8101",				//ȣ���Ϸ��� ���� �ڵ�� c8102 �Դϴ�.
			(char*)&c8101inblock,	//c8102���� �䱸�ϴ� �Է� ����ü �����͸� �����մϴ�.
			sizeof (Tc8101InBlock),	//�Է� ����ü ũ���Դϴ�
			1			//���ϴ� ���¹�ȣ �ε����� �����մϴ�.		(���¹�ȣ�� '1'������ ����)
	);

	AddLog("try sell");
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button5Click(TObject *Sender)
{
	//modify
	AnsiString sPassword, sCode, sVol, sPrice;
	AnsiString sOrder;

	Tc8103InBlock	c8103inblock	={0};
	memset(&c8103inblock,0x20,sizeof (Tc8103InBlock) );


	sCode = EditStockCode->Text;
	sPrice = EditPrice->Text;
	sVol = "0";//�ܷ�
	sOrder = EditCode->Text;


	//�� �Է� �ʵ忡�� �䱸�ϴ� ���鿡 ���� ���Ǵ� *.doc ������ ���� Ȯ���� �� �ֽ��ϴ�.
	//���º�й�ȣ�� ��������ȯ�濡���� Ȯ������ ������ ��ȯ�濡���� Ȯ���ϹǷ� ��Ȯ�ϰ� �Է��Ͻñ� �ٶ��ϴ�
	//���º�й�ȣ�� �ŷ�(�ֹ�)��й�ȣ�ʹ� �ٸ��ϴ�. �ŷ���й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8103inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8103inblock.issue_codez6 , sCode.c_str(), 6);

	//�������� �ܷ��ϰ�� 0
	strncpy(c8103inblock.crctn_qtyz12 , sVol.c_str(), 12);
	strncpy(c8103inblock.crctn_pricez10 , sPrice.c_str(), 10);

	//���ֹ���ȣ
	strncpy(c8103inblock.orgnl_order_noz10 , sOrder.c_str(), 10);

	//�������� 1:�Ϻ�, 2:�ܷ�
    strncpy(c8103inblock.all_part_typez1 , "2", 1);


	//�Ʒ� �Է��ϴ� �ŷ���й�ȣ1, 2������ ������� �ŷ���й�ȣ�� �Է��ؾ��մϴ�.
	//�ŷ�(�ֹ�)��й�ȣ�� ���º�й�ȣ�ʹ� �ٸ��� ���º�й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	SetOrderPwd(c8103inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8103inblock.trad_pswd_no_2z8,"########");

	//�ֽ� �ֹ�
	Query(
			this->Handle,			//�� ������� ���� �޽����� �ްڽ��ϴ�.
			TRID_c8103,				//�� ���񽺿� ���ؼ� TRID_c8102 �ĺ��ڸ� ���̰ڽ��ϴ�. (������ ���̸�,�ٸ� ���� �־ ����ϼŵ� �˴ϴ�)
			"c8103",				//ȣ���Ϸ��� ���� �ڵ�� c8102 �Դϴ�.
			(char*)&c8103inblock,	//c8102���� �䱸�ϴ� �Է� ����ü �����͸� �����մϴ�.
			sizeof (Tc8103InBlock),	//�Է� ����ü ũ���Դϴ�
			1			//���ϴ� ���¹�ȣ �ε����� �����մϴ�.		(���¹�ȣ�� '1'������ ����)
	);

	AddLog("try modify");
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button6Click(TObject *Sender)
{
	//cancel


	AnsiString sPassword, sCode, sVol, sPrice;
	AnsiString sOrder;

	Tc8104InBlock	c8104inblock	={0};
	memset(&c8104inblock,0x20,sizeof (Tc8104InBlock) );

	sCode = EditStockCode->Text;
	sPrice = EditPrice->Text;
	sVol = "0";//�ܷ�
	sOrder = EditCode->Text;

	//�� �Է� �ʵ忡�� �䱸�ϴ� ���鿡 ���� ���Ǵ� *.doc ������ ���� Ȯ���� �� �ֽ��ϴ�.
	//���º�й�ȣ�� ��������ȯ�濡���� Ȯ������ ������ ��ȯ�濡���� Ȯ���ϹǷ� ��Ȯ�ϰ� �Է��Ͻñ� �ٶ��ϴ�
	//���º�й�ȣ�� �ŷ�(�ֹ�)��й�ȣ�ʹ� �ٸ��ϴ�. �ŷ���й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8104inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8104inblock.issue_codez6 , sCode.c_str(), 6);

	//�������� �ܷ��ϰ�� 0
	strncpy(c8104inblock.canc_qtyz12 , sVol.c_str(), 12);

	//���ֹ���ȣ
	strncpy(c8104inblock.orgnl_order_noz10 , sOrder.c_str(), 10);

	//�������� 1:�Ϻ�, 2:�ܷ�
	strncpy(c8104inblock.all_part_typez1 , "2", 1);


	//�Ʒ� �Է��ϴ� �ŷ���й�ȣ1, 2������ ������� �ŷ���й�ȣ�� �Է��ؾ��մϴ�.
	//�ŷ�(�ֹ�)��й�ȣ�� ���º�й�ȣ�ʹ� �ٸ��� ���º�й�ȣ�� ���� �ʵ��� �����Ͻñ� �ٶ��ϴ�.
	SetOrderPwd(c8104inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8104inblock.trad_pswd_no_2z8,"########");

	//�ֽ� �ֹ�
	Query(
			this->Handle,			//�� ������� ���� �޽����� �ްڽ��ϴ�.
			TRID_c8104,				//�� ���񽺿� ���ؼ� TRID_c8102 �ĺ��ڸ� ���̰ڽ��ϴ�. (������ ���̸�,�ٸ� ���� �־ ����ϼŵ� �˴ϴ�)
			"c8104",				//ȣ���Ϸ��� ���� �ڵ�� c8102 �Դϴ�.
			(char*)&c8104inblock,	//c8102���� �䱸�ϴ� �Է� ����ü �����͸� �����մϴ�.
			sizeof (Tc8104InBlock),	//�Է� ����ü ũ���Դϴ�
			1			//���ϴ� ���¹�ȣ �ε����� �����մϴ�.		(���¹�ȣ�� '1'������ ����)
	);

	AddLog("try cancel");
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button7Click(TObject *Sender)
{
//kospi
	Attach(this->Handle, "u1", "01",2,2);

}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button8Click(TObject *Sender)
{
	Attach(this->Handle, "k1", "01",2,2);
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button9Click(TObject *Sender)
{
//���� �ڵ� ��ȸ


	tagp1003InBlock	t1003InBlock;
	memset(&t1003InBlock,0x02,sizeof(tagp1003InBlock));

	AnsiString lang;
	AnsiString gubun;

	lang = "k";
	gubun = "u";

	strncpy(t1003InBlock.formlang, lang.c_str(), lang.Length());
	strncpy(t1003InBlock.gubun, gubun.c_str(), gubun.Length());



	Query(this->Handle, TRID_p1003, "p1003", (char*)&t1003InBlock, sizeof( tagp1003InBlock));
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button10Click(TObject *Sender)
{
//���� ����
//TRID_s4101

	tags4101InBlock	t4101InBlock;
	memset(&t4101InBlock,0x20,sizeof(tags4101InBlock));

	AnsiString code;

	code = "k" + sPresentCode;

	//t4113InBlock

	strncpy(t4101InBlock.fuitemz9, code.c_str(), code.Length());

	Query(this->Handle, TRID_s4101, "s4101", (char*)&t4101InBlock, sizeof( tags4101InBlock));
}
//---------------------------------------------------------------------------

void __fastcall TFormNH::Button11Click(TObject *Sender)
{
//���񸶽�Ÿ�⺻�ڷ�

	Timer1->Enabled = true;

//	GetQuery("005930");

}
//---------------------------------------------------------------------------
void __fastcall TFormNH::Timer1Timer(TObject *Sender)
{
//timer
	static int count = 0;
	static volatile int index = 0;
	TStock* object;


	for (int i = count; i < count+100; i++) {
		if(index < g_StockList->objectList->Count){
			object = (TStock*)g_StockList->objectList->Items[i];

			if(object != NULL){
				GetQuery(object->sStockCode, index++);
			}
        }
	}

	count = count +100; //100���� ��û

	//��� ��û�ϴ� ���
	if(index >= g_StockList->objectList->Count){
		count = 0;
		index = 0;

        //FormMain->AddLog("request finish "+ IntToStr(index) );
	}


	/*
	//1���� ��û�ϴ� ���
	if(index >= g_StockList->objectList->Count){
		FormMain->AddLog("request finish "+ IntToStr(index) );

		Timer1->Enabled = false;
		count = 0;
		index = 0;
	}
	*/

}
//---------------------------------------------------------------------------
void __fastcall TFormNH::GetQuery(AnsiString sCode, int iTRID)
{

	Tc1101InBlock	c1101inblock;
	memset(&c1101inblock,0x20,sizeof(Tc1101InBlock));

	AnsiString form;


	form = "k";

	strncpy(c1101inblock.formlang, form.c_str(), form.Length());
	strncpy(c1101inblock.code, sCode.c_str(), sCode.Length());


	//�ֽ� ���簡 ��ȸ
	Query(this->Handle, TRID_c1101 + iTRID, "c1101", (char*)&c1101inblock, sizeof( Tc1101InBlock));
}

//---------------------------------------------------------------------------

void __fastcall TFormNH::Button12Click(TObject *Sender)
{
//�ǽð�

	TStock* object;
	int iKospi = 0;
	int iKosdaq = 0;

	for (int i = 0; i < g_StockList->objectList->Count; i++){
		object = (TStock*)g_StockList->objectList->Items[i];

		if(object->sKOSPI_KOSDAQ == "KOSPI"){
			iKospi++;

			AttatchKOSPI(object->sStockCode, iKospi);
		}
		else if(object->sKOSPI_KOSDAQ == "KOSDAQ"){
			iKosdaq++;

			AttatchKOSDAQ(object->sStockCode, iKosdaq);
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall TFormNH::AttatchKOSPI(AnsiString sCode, int iCount)
{
	char *c_code;
	c_code = sCode.c_str();

	Attach(this->Handle, "j8", c_code,6,6 *iCount);

}
//---------------------------------------------------------------------------
void __fastcall TFormNH::AttatchKOSDAQ(AnsiString sCode, int iCount)
{
	char *c_code;
	c_code = sCode.c_str();

	Attach(this->Handle, "k8", c_code,6,6 *iCount);

}

//---------------------------------------------------------------------------
