#include "pch.h"

#pragma once

/*=======================================================================
*	File : TRDP_Handler_CU.h
*
*	Ereditata : TRDP_Handler.h
* 
*	Descrizione :
*		La classe TRDP_Handler serve a gestire
*		la comunicazione basata sul protocollo TRDP,
*		utilizzando le sue librerie specifiche, 
*		organizzate per la ControlUnit.
*
*	Data : 12/11/2020			Autore : Luca Gargiulo, Salvatore Testa
-----------------------------------------------------------------------*/
class TRDP_Handler_CU : public TRDP_Handler {
	public:
		std::string	ReciveMsg(); //Ricevi messaggio
};

/*==================================================
	Ricezione messaggio

	Returna il Messaggio (string namespace standard),
	se nuovo, ricevuto dal destinatario D con i.
--------------------------------------------------*/
std::string TRDP_Handler_CU::ReciveMsg()
{
	std::string Answer = "";		//L'eventuale messaggio che la funzione returna
	TRDP_PD_INFO_T* pPdInfo;		//Informazioni sull'esito della ricezione messaggio
	pPdInfo = new TRDP_PD_INFO_T;

	/* Aggiorna datagram del mittente M[i] */
	memset(pData_in, 0, TRDP_MAX_PD_DATA_SIZE);
	TRDP_ERR_T Err = tlp_get(AppSession, SubHandle_s, pPdInfo, pData_in, &dataSize);

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
				/* Se il pachetto è di tipo Common e questo ip, o meglio istanza della classe, è dedicato alla ricezione pacchetti Common */
				if (State == TRDP_TCMS_Common && CommunicationType == TRDP_TCMS_Common)
				{
					/* Prepara il pacchetto *Leggere documentazione */
					Answer += int(TRDP_TCMS_Common);	//Informa che il tipo di messaggio ricevuto è di tipo TRDP_TCMS_Common
					Answer += pData_in[1];
				}
				else if (State == TRDP_TCMS_PIS && CommunicationType == TRDP_TCMS_PIS)	// -- TRDP_TCMS_PIS
				{
					/* Prepara il pacchetto *Leggere documentazione */
					Answer += char(TRDP_TCMS_PIS);

					for (int i = 1; i < 45; i++)
						Answer += pData_in[i];
				}
				else if (State == TRDP_TCMS_Config && CommunicationType == TRDP_TCMS_Config)	// -- TRDP_TCMS_Config
				{
					/* Prepara il pacchetto *Leggere documentazione */
					Answer += char(TRDP_TCMS_Config);
					for (int i = 1; i < 31; i++)
						Answer += pData_in[i];
				}

				/* Se il mittente è nuovo */
				if (Result == RCVH_NOT_FOUND)
					DeviceHandler.InsertAddress(pPdInfo->srcIpAddr, (unsigned char*)pData_in);	//Aggiungilo nella lista dei mittenti
			}
		}
	}

	delete pPdInfo;

	return Answer;
}