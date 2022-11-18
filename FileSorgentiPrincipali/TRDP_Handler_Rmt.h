#include "pch.h"

#pragma once

/*=======================================================================
*	File : TRDP_Handler_Rmt.h
*
*	Ereditata : TRDP_Handler.h
*
*	Descrizione :
*		La classe TRDP_Handler serve a gestire
*		la comunicazione basata sul protocollo TRDP,
*		utilizzando le sue librerie specifiche,
*		organizzate per il simulatore.
*
*	Data : 12/11/2020			Autore : Luca Gargiulo, Salvatore Testa
-----------------------------------------------------------------------*/
class TRDP_Handler_Rmt : public TRDP_Handler {
	public:
		std::string	ReciveMsg();
};

/*==================================================
	Ricezione messaggio

	Returna il Messaggio (string namespace standard),
	se nuovo, ricevuto dal destinatario D con i.
--------------------------------------------------*/
std::string TRDP_Handler_Rmt::ReciveMsg()
{
	std::string Answer = "";	//L'eventuale messaggio che la funzione returna
	TRDP_PD_INFO_T* pPdInfo;	//Informazioni sull'esito della ricezione messaggio
	pPdInfo = new TRDP_PD_INFO_T;

	/* Aggiorna datagram del mittente M[i] */
	memset(pData_in, 0, TRDP_MAX_PD_DATA_SIZE);
	TRDP_ERR_T Err = tlp_get(AppSession, SubHandle_s, pPdInfo, pData_in, &dataSize);	//Aggiorna datagram del mittente M[i]
	
	/* Ottieni il communication Type del messaggio ricevuto */
	TRDP_MESSAGE_TYPE State = pData_in[0];

	/* Controlla che non ci siano stati errori e il messaggio ed è arrivato e che sia uno dei cinque messaggi definiti dai protocolli */
	if (Err == TRDP_NO_ERR && pData_in[0] >= 251 && pData_in[0] <= 255)
	{
		/* Se l'ip non è del device corrente */
		if (pPdInfo->srcIpAddr != MyIp)
		{
			RCVH_RESULT_SEARCH Result = RCVH_FOUND_OLD_MSG;

			/* Controlla che il device abbia mandato un messaggio nuovo oppure se è il primo messaggio ricevuto da quest'host */
			Result = DeviceHandler.CheckMessage(pPdInfo->srcIpAddr, pData_in);

			/* Se il messaggio è nuovo oppure è nuovo l'host */
			if (Result == RCVH_FOUND_NEW_MSG || Result == RCVH_NOT_FOUND)
			{
				/* Se il pachetto è di tipo TRDP_PIS_Functional e questo ip, o meglio istanza della classe, è dedicato alla ricezione pacchetti TRDP_PIS_Functional */
				if (State == TRDP_PIS_Functional && CommunicationType == TRDP_PIS_Functional)
				{
					Answer += int(TRDP_PIS_Functional);
				}
				else if (State == TRDP_PIS_Diagnostic && CommunicationType == TRDP_PIS_Diagnostic)	// -- TRDP_PIS_Diagnostic
				{
					/* Prepara il pacchetto *Leggere documentazione */
					Answer += char(TRDP_PIS_Diagnostic); //Informa che il tipo di messaggio ricevuto è di tipo TRDP_TCMS_Common

					for (int i = 1; i < 9; i++)
						Answer += pData_in[i];
				}

				/* Se il mittente è nuovo */
				if(Result == RCVH_NOT_FOUND)
					DeviceHandler.InsertAddress(pPdInfo->srcIpAddr, (unsigned char*)pData_in); //Aggiungilo nella lista dei mittenti
			}
		}
	}

	delete pPdInfo;

	return Answer;
}