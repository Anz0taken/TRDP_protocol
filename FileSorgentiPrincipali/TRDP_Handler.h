#include "pch.h"
#include "Files\getopt.h"
#include "Files\trdp_types.h"
#include "Files\trdp_if_light.h"
#include "Files\vos_thread.h"
#include "Files\vos_utils.h"
#include "Files\tau_ctrl.c"
#include "Files\tau_dnr.c"
#include "Files\tau_marshall.c"
#include "Files\tau_so_if.c"
#include "Files\tau_tti.c"
#include "Files\tau_xml.c"
#include "Files\tlc_if.c"
#include "Files\tlm_if.c"
#include "Files\tlp_if.c"
#include "Files\trdp_dllmain.c"
#include "Files\trdp_mdcom.c"
#include "Files\trdp_pdcom.c"
#include "Files\trdp_pdindex.c"
#include "Files\trdp_stats.c"
#include "Files\trdp_utils.c"
#include "Files\trdp_xml.c"
#include "Files\vos_mem.c"
#include "Files\vos_shared_mem.c"
#include "Files\vos_sock.c"
#include "Files\vos_thread.c"
#include "Files\vos_utils.c"
#include "./Files/ReciverHandler.h"
#pragma once

/*=======================================================================
*	File : TRDP_Handler_CU.h
* 
*	Descrizione : 
*		La classe TRDP_Handler serve a gestire
*		la comunicazione basata sul protocollo TRDP,
*		utilizzando le sue librerie specifiche.
*	
*	Data : 12/11/2020			Autore : Luca Gargiulo, Salvatore Testa		
-----------------------------------------------------------------------*/
public class TRDP_Handler {
	protected:
		/* Classi gestione user connessi */
		ReciverHandler			DeviceHandler;

		/* Informazioni utente */
		TRDP_IP_ADDR_T			MyIp;
		TRDP_IP_ADDR_T			DestIp;

		/* Variabili per TRCP INIT */
		VOS_PRINT_DBG_T			Answer;
		TRDP_MEM_CONFIG_T		Mem_Config;
		TRDP_PROCESS_CONFIG_T	ConfigurazioneProc;

		/* Variabili per openSession */
		TRDP_APP_SESSION_T		AppSession;
		TRDP_PD_CONFIG_T		ConfigurazionePd;

		/* Variabili subscribe */
		void* UserRef;
		TRDP_SUB_T				SubHandle_s;
		TRDP_PD_CALLBACK_T      pfCbFunction;
		UINT32                  serviceId;
		UINT32                  comId;
		UINT32                  etbTopoCnt;
		UINT32                  opTrnTopoCnt;
		TRDP_IP_ADDR_T          srcIpAddr1;
		TRDP_IP_ADDR_T          srcIpAddr2;
		TRDP_IP_ADDR_T          destIpAddr;
		TRDP_FLAGS_T            pktFlags;
		const TRDP_COM_PARAM_T* pRecParams;
		UINT32                  timeout;
		TRDP_TO_BEHAVIOR_T      toBehavior;

		/* Variabili publish */
		TRDP_SUB_T				SubHandle_p;
		UINT32					redId;
		TRDP_SEND_PARAM_T* pSendParam;
		unsigned char			pData_in[TRDP_MAX_PD_DATA_SIZE];
		unsigned char			pData_out[TRDP_MAX_PD_DATA_SIZE];
		UINT32					dataSize;
		UINT32					Interval;

		/* Varie */
		unsigned char			IndirizzoIpDest[TRDP_MAX_PD_DATA_SIZE];	//Indirizzo Ip destinatario
		bool					AllGood;								//Flag utilizzato per determinare se ci sono stati errori nella stabilizzazione della comunicazione
		TRDP_MESSAGE_TYPE		CommunicationType;						//Il tipo di protocollo di cui ogni istanza oggetto deve gestire

	public:
		int* Port;	//Porta utilizzata dall'instanza oggetto

		TRDP_Handler();
		~TRDP_Handler();
		bool			StartTLC();														//Inizio comunicazione TLC
		void			SetSessionVars(int Port_);										//Settaggio variabili sessione
		void			SetIps(std::string MyIp_, std::string DestIp_);					//Settaggio variabili Ips
		void			SetCommunicationType(TRDP_MESSAGE_TYPE CmnT);					//Settaggio protocollo comunicazione
		bool			OpenSession();													//Apretura sessione
		void			SetSubscribeVars();												//Settaggio variabili subscribe
		bool			Subscribe();													//Apetura subscribe
		void			SetPublishVars();												//Settaggio variabili publish
		bool			Publish();														//Apertura publish
		TRDP_ERR_T		RefreshMsgs();													//Riaggiorna messaggi da ricevere e inviare nel buffer gestito dal protocollo TRDP
		bool			SendMsg(TRDP_MESSAGE_TYPE Protocoll,std::string MsgDaInviare);	//Manda un messaggio
		bool			IsStateGood() { return AllGood; }								//Returna lo stato dell'instanza
		void			ResetAll();														//Ripristina variabili di connessione
};


/* COSTRUTTORE : Settaggio variabili necessario per l'inizializzazione connessione */
TRDP_Handler::TRDP_Handler()
{
	Port = new int;
	*Port = 17544;
	AllGood = true;
	VOS_PRINT_DBG_T Answer = NULL;
	memset(&Mem_Config, 0, sizeof(Mem_Config));
	memset(&ConfigurazioneProc, 0, sizeof(ConfigurazioneProc));
}

/* DISTRUTTORE : Chiusura canale comunicazione TRDP e rilascio memoria */
TRDP_Handler::~TRDP_Handler()
{
	tlc_closeSession(AppSession);
	tlc_terminate();

	delete Port;
}

/*==================================================
	Inizio connessione TLC

		Returna:
			true  -> se tutto okay
			false -> se qualcosa è andato storto
--------------------------------------------------*/
bool TRDP_Handler::StartTLC()
{
	bool Done = false;

	TRDP_ERR_T Err;

	Err = tlc_init(Answer, NULL, &Mem_Config);

	if (!Err)
		Done = true;
	else if (Err == TRDP_INIT_ERR)
		AllGood = false;

	return AllGood;
}

/* Settaggio variabili sessione */
void TRDP_Handler::SetSessionVars(int Port_ = 17224)
{
	ConfigurazionePd.pfCbFunction = NULL;
	ConfigurazionePd.pRefCon = NULL;
	ConfigurazionePd.sendParam.qos = 5;
	ConfigurazionePd.sendParam.ttl = 64;
	ConfigurazionePd.flags = TRDP_FLAGS_NONE;
	ConfigurazionePd.timeout = 50000;
	ConfigurazionePd.toBehavior = TRDP_TO_SET_TO_ZERO;
	ConfigurazionePd.port = Port_;
	Port++;
}

/*==================================================
	Settaggio ip del mittente e destinatario

	std::string	MyIp_   [in] -> Ip localhost
	std::string	DestIp_ [in] -> Ip destinatario
--------------------------------------------------*/
void TRDP_Handler::SetIps(std::string MyIp_, std::string DestIp_)
{
	/* Conversione da string -> char array  */
	char* In;
	In = new char[MyIp_.size() + 1];
	strcpy(In, MyIp_.c_str());

	/* Conversione da char array -> int */
	MyIp = vos_dottedIP(In);

	delete In;

	/* Conversione da string -> char array  */
	In = new char[DestIp_.size() + 1];
	strcpy(In, DestIp_.c_str());
	strcpy((char*)IndirizzoIpDest, DestIp_.c_str());

	/* Conversione da char array -> int */
	DestIp = vos_dottedIP(In);

	delete In;
}

/* Settaggio protocollo di comunicazione */
void TRDP_Handler::SetCommunicationType(TRDP_MESSAGE_TYPE CmnT)
{
	CommunicationType = CmnT;
}

/*==================================================
	Inizio Session

		Returna:
			true  -> se tutto okay
			false -> se qualcosa è andato storto
--------------------------------------------------*/
bool TRDP_Handler::OpenSession()
{
	bool Done = false;

	TRDP_ERR_T Err;

	Err = tlc_openSession(&AppSession, MyIp, 0, NULL, &ConfigurazionePd, NULL, &ConfigurazioneProc);

	if (Err == TRDP_NO_ERR)
		Done = true;
	else
		AllGood = false;

	return Done;
}

/* Settaggio variabili subscribe */
void TRDP_Handler::SetSubscribeVars()
{
	UserRef = NULL;

	SubHandle_s;
	pfCbFunction = NULL;
	serviceId = 0;
	comId = 0;
	etbTopoCnt = 0;
	opTrnTopoCnt = 0;
	srcIpAddr1 = 0;
	srcIpAddr2 = 0;
	destIpAddr = DestIp;
	pktFlags = TRDP_FLAGS_MARSHALL;
	pRecParams = NULL;
	timeout = 100;
	toBehavior = TRDP_TO_DEFAULT;
}

/*==================================================
	Inizio Subscribe

		Returna:
			true  -> se tutto okay
			false -> se qualcosa è andato storto
--------------------------------------------------*/
bool TRDP_Handler::Subscribe()
{
	bool Done = false;

	if (!tlp_subscribe(AppSession, &SubHandle_s, UserRef, pfCbFunction, serviceId, comId, etbTopoCnt, opTrnTopoCnt, srcIpAddr1, srcIpAddr2, destIpAddr, pktFlags, pRecParams, timeout, toBehavior))
		Done = true;
	else
		AllGood = false;
	return Done;
}

/* Settaggio variabili publish */
void TRDP_Handler::SetPublishVars()
{
	redId = 0;
	pSendParam = NULL;
	dataSize = TRDP_MAX_PD_DATA_SIZE;
	Interval = 5000;
}

/*==================================================
	Inizio Publish

		Returna:
			true  -> se tutto okay
			false -> se qualcosa è andato storto
--------------------------------------------------*/
bool TRDP_Handler::Publish()
{
	bool Done = false;

	if (!tlp_publish(AppSession, &SubHandle_p, UserRef, pfCbFunction, serviceId, comId, etbTopoCnt, opTrnTopoCnt, MyIp, DestIp, Interval, redId, pktFlags, pSendParam, pData_out, dataSize))
		Done = true;
	else
		AllGood = false;

	return Done;
}

/*==================================================
	Refresh dei messaggi da mandare e in arrivo

	Returna TRDP_ERR_T
--------------------------------------------------*/
TRDP_ERR_T TRDP_Handler::RefreshMsgs()
{
	return tlc_process(AppSession, NULL, NULL);
}

/*==================================================
	Invio messaggio

	Invia un messaggio ad un indirizzo di rete.

	int			Protocoll	 [in] -> Protocollo Communication da utilizzare
	std::string	MsgDaInviare [in] -> Messaggio da inviare

	Return
		True  -> Se tutto è andato bene
		Flase -> Se c'è stato qualche errore
--------------------------------------------------*/
bool TRDP_Handler::SendMsg(TRDP_MESSAGE_TYPE Protocoll, std::string MsgDaInviare)
{
	bool Done = false;

	/* Copia il messaggio da inviare nell'array di char mirato, lasciando però il primo byte per la definizione del protocollo */
	CopyCharArrayToChar(1, TRDP_MAX_PD_DATA_SIZE, (char*)pData_out, (char*)MsgDaInviare.c_str(), TRDP_MAX_PD_DATA_SIZE);

	/* Definisci protocollo */
	pData_out[0] = Protocoll;

	/* Manda messaggio */
	if (!tlp_put(AppSession, SubHandle_p, pData_out, dataSize))
		Done = true;

	return Done;
}

/*==================================================
	Resetta tutte le variabili necessarie per
	un'eventuale riconnessione con indirizzi diversi.
--------------------------------------------------*/
void TRDP_Handler::ResetAll()
{
	/* Libera la memoria e chiudi canale di comunicazione */
	tlc_closeSession(AppSession);
	tlc_terminate();

	if (pSendParam)
		delete pSendParam, pSendParam = NULL;

	if (UserRef)
		delete UserRef, UserRef = NULL;

	if (pRecParams)
		delete pRecParams, pRecParams = NULL;

	memset(&Mem_Config, 0, sizeof(Mem_Config));
	memset(&ConfigurazioneProc, 0, sizeof(ConfigurazioneProc));
}