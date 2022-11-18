#pragma once

/*=======================================================================
*	File : INFO_TRAIN_HANDLER.h
*
*	Descrizione :
*		INFO_TRAIN_HANDLER è una classe utilizzata
*		Per una gestione mirata a tutte le informazioni
*		del treno che viaggiano da ControlUnit
*		a simulatore e viceversa.
*
*	Data : 12/11/2020			Autore : Luca Gargiulo, Salvatore Testa
-----------------------------------------------------------------------*/
class INFO_TRAIN_HANDLER
{
	private:
		int MetroDiPartenza;				//Indica in metri a quale distanza il treno ha iniziato la corsa sulla linea x
		int MetroAttuale;					//Indica in metri a quale distanza il treno si sulla corsia x
		int Velocita;						//Indica la velocità del treno attualmente (km/h)
		int StatoPorte;						//0 --> Chiuse, 1 -- > Aperte DX, 2 --> Aperte SX
		char ConsistID[16];					//Id della CU
		unsigned char SensoreAntiIncend;	//Sensore antiincendio
		int StatiDispositiviCU;				//Variabile utilizzata per la memorizzazzione dei 10 stati della CU (Utilizzo tecnologia bitmask)
		bool Display;						// ON/OFF

		bool GotSomethingState;
		/* Qualsiasi tra questi valori, se settato a -1 indica la non reperibilità dell'informazione, tranne StatiDispositiviCU */

	public:
		INFO_TRAIN_HANDLER();

		/* Funzioni Set */

		void SetMetroPartenza(int M);
		void SetMetroAttuale(int M);
		void SetVelocita(int KMH);
		void SetStatoPorte(int Stato);
		void SetConsistID(char ID[]);
		void SetSensoreAntiInc(unsigned char Stato);
		void SetDisplay(bool State);
		void SetGotSomething(bool State);
		void SettaDispSensCu(int Numero);

		/* Funzioni Get */

		bool GetSomethingState();
		int  GetDispSensCu();
};

/* Costruttore */

INFO_TRAIN_HANDLER::INFO_TRAIN_HANDLER()
{
	MetroDiPartenza		= -1;
	MetroAttuale		= -1;
	Velocita			= -1;
	StatoPorte			= -1;
	ConsistID[0]		=  0;
	SensoreAntiIncend	=  0;
	Display				= -1;
	StatiDispositiviCU  =  0;
	GotSomethingState	= false;
}

/* Funzioni set */

void INFO_TRAIN_HANDLER::SetMetroPartenza(int M)
{
	MetroDiPartenza = M;
}

void INFO_TRAIN_HANDLER::SetMetroAttuale(int M)
{
	MetroAttuale = M;
}

void INFO_TRAIN_HANDLER::SetVelocita(int KMH)
{
	Velocita = KMH;
}

void INFO_TRAIN_HANDLER::SetStatoPorte(int Stato)
{
	StatoPorte = Stato;
}

void INFO_TRAIN_HANDLER::SetConsistID(char ID[])
{
	strncpy(ConsistID, ID, 16);
}

void INFO_TRAIN_HANDLER::SetSensoreAntiInc(unsigned char Stato)
{
	SensoreAntiIncend = Stato;
}

void INFO_TRAIN_HANDLER::SetDisplay(bool State)
{
	Display = State;
}

void INFO_TRAIN_HANDLER::SetGotSomething(bool State)
{
	GotSomethingState = true;
}

void INFO_TRAIN_HANDLER::SettaDispSensCu(int Numero)
{
	StatiDispositiviCU += Numero;
}

int INFO_TRAIN_HANDLER::GetDispSensCu()
{
	return StatiDispositiviCU;
}

/* Funzioni get */

bool INFO_TRAIN_HANDLER::GetSomethingState()
{
	return GotSomethingState;
}