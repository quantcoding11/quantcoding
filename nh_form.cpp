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


const	int	TRID_c1101	=1;		//<--예시를 보이기 위함이며 고정값일 필요는 없습니다


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

	String sMoVolume;//변동거래량
	String sJanggubun;//추후 kospi, kosdaq 구분 처리

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
	else if(ss.SubString(1,2) == "d2"){//실시간 체결
		Td2OutBlock*	pd2	=(Td2OutBlock*)(pSiseData->pData->szData + 3);


	}
	else if(ss.SubString(1,2) == "d3"){//주문 통보
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


		ss = "주문통보 code:"+ sCode +" , name: "+ sName +" , type: "+ sType +
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


			ss = pc1101outblock->N_offvolall;//외국인 매도
			sForeMedo = ss.SubString(0, 9);

			ss = pc1101outblock->N_bidvolall;//외국인 매수
			sForeMesu = ss.SubString(0, 9);



			g_ThreadNH->UpdateStockData(sCode, sName2, sYesterdayMoney, sKOSPI,
				sPrice, sForeMedo, sForeMesu);

			//AddLog(sCode +" "+ sName2 +" "+ sKOSPI +", price"+ sPrice +	", vol:"+ sVolume );

		}


	}
	else if(pOutData->TrIndex == TRID_c8102){

		ss = pOutData->pData->szBlockName;

		if(ss == "c8102OutBlock"){//매수
			Tc8102OutBlock*	pc8102OutBlock	=(Tc8102OutBlock*)pOutData->pData->szData;
			String sOrder;

			sOrder = pc8102OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);


			if(sOrder.Trim() == "") {
				AddLog("매수 주문 실패");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("매수 주문 성공");
				AddLog(sOrder);
			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8101){
		ss = pOutData->pData->szBlockName;

		if(ss == "c8101OutBlock"){//매도
			Tc8101OutBlock*	pc8101OutBlock	=(Tc8101OutBlock*)pOutData->pData->szData;
			String sOrder;

			sOrder = pc8101OutBlock->order_noz10;
			sOrder = sOrder.SubString(0, 10);


			if(sOrder.Trim() == "") {
				AddLog("매도 주문 실패");
			}
			else{
                EditCode->Text = sOrder;
				AddLog("매도 주문 성공");
				AddLog(sOrder);
			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8103){
		ss = pOutData->pData->szBlockName;

		if(ss == "c8103OutBlock"){//정정
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
				AddLog("정정 주문 실패");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("정정 주문 성공");
				AddLog("org order :"+ sOrderOrg);
				AddLog("order :"+ sOrder);
				AddLog("vol :"+ sVol);
				AddLog("price :"+ sPrice);

			}
		}
	}
	else if(pOutData->TrIndex == TRID_c8104){
		ss = pOutData->pData->szBlockName;
		if(ss == "c8104OutBlock"){//취소
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
				AddLog("취소 주문 실패");
			}
			else{
				EditCode->Text = sOrder;

				AddLog("취소 주문 성공");
				AddLog("org order :"+ sOrderOrg);
				AddLog("order :"+ sOrder);
				AddLog("vol :"+ sVol);
			}

		}

	}
	else if(pOutData->TrIndex == TRID_p1003){ //response
	//선물 코드
		String sCode;
		String sName;

		tagp1003OutBlock*	t1003OutBlock	=(tagp1003OutBlock*)pOutData->pData->szData;

		sCode = t1003OutBlock->codez8;
		sCode = sCode.SubString(0, 8);
		sName = t1003OutBlock->namez30;
		sName = sName.SubString(0, 30);


		sPresentCode = sCode;

		AddLog("선물 코드");
		AddLog(sCode);
		AddLog(sName);

	}

	else if(pOutData->TrIndex == TRID_s4101){ //response
	//선물

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
				AddLog("sign : "+ sSign); //3 => 마이너스
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
//nh 로그인


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

	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	//계좌비밀번호를 모의투자환경에서는 확인하지 않지만 실환경에서는 확인하므로 정확하게 입력하시기 바랍니다
	//계좌비밀번호는 거래(주문)비밀번호와는 다릅니다. 거래비밀번호를 넣지 않도록 주의하시기 바랍니다.

	SetAccountIndexPwd(c8102inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8102inblock.issue_codez6 , sCode.c_str(), 6);
	strncpy(c8102inblock.order_qtyz12 , sVol.c_str(), 12);
	strncpy(c8102inblock.order_unit_pricez10 , sPrice.c_str(), 10);
	strncpy(c8102inblock.trade_typez2 , "00", 2);


	//아래 입력하는 거래비밀번호1, 2란에는 사용자의 거래비밀번호를 입력해야합니다.
	//거래(주문)비밀번호는 계좌비밀번호와는 다르며 계좌비밀번호를 넣지 않도록 주의하시기 바랍니다.
	SetOrderPwd(c8102inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8102inblock.trad_pswd_no_2z8,"########");

	//주식 주문
	Query(
			this->Handle,			//이 윈도우로 응답 메시지를 받겠습니다.
			TRID_c8102,				//이 서비스에 대해서 TRID_c8102 식별자를 붙이겠습니다. (예시일 뿐이며,다른 값을 넣어서 사용하셔도 됩니다)
			"c8102",				//호출하려는 서비스 코드는 c8102 입니다.
			(char*)&c8102inblock,	//c8102에서 요구하는 입력 구조체 포인터를 지정합니다.
			sizeof (Tc8102InBlock),	//입력 구조체 크기입니다
			1			//원하는 계좌번호 인덱스를 지정합니다.		(계좌번호는 '1'번부터 시작)
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

	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	//계좌비밀번호를 모의투자환경에서는 확인하지 않지만 실환경에서는 확인하므로 정확하게 입력하시기 바랍니다
	//계좌비밀번호는 거래(주문)비밀번호와는 다릅니다. 거래비밀번호를 넣지 않도록 주의하시기 바랍니다.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8101inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8101inblock.issue_codez6 , sCode.c_str(), 6);
	strncpy(c8101inblock.order_qtyz12 , sVol.c_str(), 12);
	strncpy(c8101inblock.order_unit_pricez10 , sPrice.c_str(), 10);
	strncpy(c8101inblock.trade_typez2 , "00", 2);


	//아래 입력하는 거래비밀번호1, 2란에는 사용자의 거래비밀번호를 입력해야합니다.
	//거래(주문)비밀번호는 계좌비밀번호와는 다르며 계좌비밀번호를 넣지 않도록 주의하시기 바랍니다.
	SetOrderPwd(c8101inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8101inblock.trad_pswd_no_2z8,"########");

	//주식 주문
	Query(
			this->Handle,			//이 윈도우로 응답 메시지를 받겠습니다.
			TRID_c8101,				//이 서비스에 대해서 TRID_c8102 식별자를 붙이겠습니다. (예시일 뿐이며,다른 값을 넣어서 사용하셔도 됩니다)
			"c8101",				//호출하려는 서비스 코드는 c8102 입니다.
			(char*)&c8101inblock,	//c8102에서 요구하는 입력 구조체 포인터를 지정합니다.
			sizeof (Tc8101InBlock),	//입력 구조체 크기입니다
			1			//원하는 계좌번호 인덱스를 지정합니다.		(계좌번호는 '1'번부터 시작)
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
	sVol = "0";//잔량
	sOrder = EditCode->Text;


	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	//계좌비밀번호를 모의투자환경에서는 확인하지 않지만 실환경에서는 확인하므로 정확하게 입력하시기 바랍니다
	//계좌비밀번호는 거래(주문)비밀번호와는 다릅니다. 거래비밀번호를 넣지 않도록 주의하시기 바랍니다.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8103inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8103inblock.issue_codez6 , sCode.c_str(), 6);

	//정정수량 잔량일경우 0
	strncpy(c8103inblock.crctn_qtyz12 , sVol.c_str(), 12);
	strncpy(c8103inblock.crctn_pricez10 , sPrice.c_str(), 10);

	//원주문번호
	strncpy(c8103inblock.orgnl_order_noz10 , sOrder.c_str(), 10);

	//정정구분 1:일부, 2:잔량
    strncpy(c8103inblock.all_part_typez1 , "2", 1);


	//아래 입력하는 거래비밀번호1, 2란에는 사용자의 거래비밀번호를 입력해야합니다.
	//거래(주문)비밀번호는 계좌비밀번호와는 다르며 계좌비밀번호를 넣지 않도록 주의하시기 바랍니다.
	SetOrderPwd(c8103inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8103inblock.trad_pswd_no_2z8,"########");

	//주식 주문
	Query(
			this->Handle,			//이 윈도우로 응답 메시지를 받겠습니다.
			TRID_c8103,				//이 서비스에 대해서 TRID_c8102 식별자를 붙이겠습니다. (예시일 뿐이며,다른 값을 넣어서 사용하셔도 됩니다)
			"c8103",				//호출하려는 서비스 코드는 c8102 입니다.
			(char*)&c8103inblock,	//c8102에서 요구하는 입력 구조체 포인터를 지정합니다.
			sizeof (Tc8103InBlock),	//입력 구조체 크기입니다
			1			//원하는 계좌번호 인덱스를 지정합니다.		(계좌번호는 '1'번부터 시작)
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
	sVol = "0";//잔량
	sOrder = EditCode->Text;

	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	//계좌비밀번호를 모의투자환경에서는 확인하지 않지만 실환경에서는 확인하므로 정확하게 입력하시기 바랍니다
	//계좌비밀번호는 거래(주문)비밀번호와는 다릅니다. 거래비밀번호를 넣지 않도록 주의하시기 바랍니다.
	//m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8,1,sPassword);


	SetAccountIndexPwd(c8104inblock.pswd_noz8,1,m_sAccountPass.c_str());


	sVol.printf("%012d", sVol.ToInt());
	sPrice.printf("%010d", sPrice.ToInt());

	strncpy(c8104inblock.issue_codez6 , sCode.c_str(), 6);

	//정정수량 잔량일경우 0
	strncpy(c8104inblock.canc_qtyz12 , sVol.c_str(), 12);

	//원주문번호
	strncpy(c8104inblock.orgnl_order_noz10 , sOrder.c_str(), 10);

	//정정구분 1:일부, 2:잔량
	strncpy(c8104inblock.all_part_typez1 , "2", 1);


	//아래 입력하는 거래비밀번호1, 2란에는 사용자의 거래비밀번호를 입력해야합니다.
	//거래(주문)비밀번호는 계좌비밀번호와는 다르며 계좌비밀번호를 넣지 않도록 주의하시기 바랍니다.
	SetOrderPwd(c8104inblock.trad_pswd_no_1z8,"########");
	SetOrderPwd(c8104inblock.trad_pswd_no_2z8,"########");

	//주식 주문
	Query(
			this->Handle,			//이 윈도우로 응답 메시지를 받겠습니다.
			TRID_c8104,				//이 서비스에 대해서 TRID_c8102 식별자를 붙이겠습니다. (예시일 뿐이며,다른 값을 넣어서 사용하셔도 됩니다)
			"c8104",				//호출하려는 서비스 코드는 c8102 입니다.
			(char*)&c8104inblock,	//c8102에서 요구하는 입력 구조체 포인터를 지정합니다.
			sizeof (Tc8104InBlock),	//입력 구조체 크기입니다
			1			//원하는 계좌번호 인덱스를 지정합니다.		(계좌번호는 '1'번부터 시작)
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
//선물 코드 조회


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
//선물 지수
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
//종목마스타기본자료

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

	count = count +100; //100개씩 요청

	//계속 요청하는 경우
	if(index >= g_StockList->objectList->Count){
		count = 0;
		index = 0;

        //FormMain->AddLog("request finish "+ IntToStr(index) );
	}


	/*
	//1번만 요청하는 경우
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


	//주식 현재가 조회
	Query(this->Handle, TRID_c1101 + iTRID, "c1101", (char*)&c1101inblock, sizeof( Tc1101InBlock));
}

//---------------------------------------------------------------------------

void __fastcall TFormNH::Button12Click(TObject *Sender)
{
//실시간

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
