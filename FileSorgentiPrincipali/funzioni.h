#pragma once

/*=======================================================================
*	File : funzioni.h
*
*	Descrizione :
*       Insieme di funzioni necessarie per l'oganizzazione e manimpolazione dei
*       dati gestiti dalle classi soggette al protocollo TRDP.
*
*	Data : 12/11/2020			Autore : Luca Gargiulo, Salvatore Testa
-----------------------------------------------------------------------*/

/*=====================================================
*   Copia il valore di una stringa A, in una stringa B,
*   indicando il massimo size dell'array, array di destinazione,
*   array di arrivo, indice di partenza, indicne di fine.
* 
*   int     From   [in]  -> Indice di partenza
*   int     To     [in]  -> Indice fino a dove copiare
*   char    *Dest  [out] -> Array di destinazione
*   char    *Input [in]  -> Array da cui copiare i caratteri
*   int     Max    [in]  -> Max size contemplato
--------------------------------------------------*/
void CopyCharArrayToChar(int From, int To, char Dest[], char Input[], int MAX)
{

	int i;
	for (i = From; i < To && Input[i - From] != 0 && i < MAX; i++)
		Dest[i] = Input[i - From];

	Dest[i] = 0;
}

/*=====================================================
*   Converte un array di char nel suo int rappresentativo.
*   Il seguente algoritmo utilizza la little indian notation.
* 
*   Ex:
*       String text             [in]  = {'A','A', 0, 0 }
*       String text (Binary)          = 01000001 01000001 00000000 00000000
*       Valore rispettivo       [out] = 1094778880
* 
*   std::string Text    [in] -> Testo da cui estrarre il numero
*   int         Size    [in] -> Size della stringa
* 
*   Return:
*       Valore del numero estratto
-----------------------------------------------------*/
int FromByteArrayToNumber(std::string Text, int Size)
{
    int Somma = 0;

    for (int i = 0; i < Size; i++)
        Somma += ((static_cast<int>(Text[i]) & 0xFF)) << i * 8;

    return Somma;
}

/*==============================================================================
*   Converte un int in un array di char.
*
*   Ex:
*       Valore rispettivo       [in]   = 1094778880
*       String text             [out]  = {'A','A', 0, 0 }
*       String text (Binary)           = 01000001 01000001 00000000 00000000
* 
*   int         Numero    [in]  -> Numero da convertire
*   std::string Stringa   [out] -> Testo in cui inserire il numero convertito
*   int         SizeChar  [in]  -> Size della stringa
------------------------------------------------------------------------------*/
void FromNumberToByteArray(int Numero, std::string &Stringa, int SizeChar)
{
    char Carattere = 0;
    int Scatola = -1;

    for(int i = 0; i < SizeChar; i++)
    {
        Scatola = Numero & 0xFF;

        Stringa[i] = char(Scatola);

        Numero = Numero >> 8;
    }
}

/*==============================================================================
*   Confronto di uguaglianza di due stringa, relative a una lunghezza MAX.
*
*   char    *FirstArray  [in] -> Primo array da confrontare
*   char    *SecondArray [in] -> Secondo array da confrontare
*   int      MaxSize     [in] -> Per quanti caratteri confrontarli
* 
*   Return:
*       True  -> Se le stringhe sono uguali
*       False -> Se le stringhe non sono uguali
------------------------------------------------------------------------------*/
bool arestreuqal(char FirstArray[], char SecondArray[], int MaxSize)
{
    bool Equal = true;

    for (int i = 0; i < MaxSize && Equal; i++)
        if (FirstArray[i] != SecondArray[i])
            Equal = false;

    return Equal;
}

/*==========================================================================================
*   Copia di un array in char in un ulteriore array di char
*   soggetto uniformandolo al protocollo NO0CHARARRAY (N0CA).
*   *Leggere la documentazione.
* 
*   Ex:
*	    Char array da inviare:
*           231,0,32,0
*
*	    Risultato:
*	        2,231 / 1,1 / 2,32 / 1,1
*   
*   char        *Dest   [out] -> Array in cui viene memorizzata la stringa con protocollo N0CA
*   std::string Input   [in]  -> Stringa da cui effettuare il protocollo
*   int         Size    [in]  -> Size della stringa da copiare
*
------------------------------------------------------------------------------------------*/
void ByteCharArrayToNO0CHARArray(char Dest[], std::string Input, int Size)
{
    for (int i = 0; i < 4; i++)
        if (Input[i] == 0)
            Dest[i * 2] = 1, Dest[i * 2 + 1] = 1;
        else
            Dest[i * 2] = 2, Dest[i * 2 + 1] = Input[i];

    Dest[Size * 2] = 0;
}

/*==========================================================================================
*   Converte un array di char soggetto al protocollo N0CA,
*   in una stringa filtrata dal protocollo N0CA.
*
*   Ex:
*	    Char array input:
*           2,231 / 1,1 / 2,32 / 1,1
*
*	    Risultato:
*	        231,0,32,0
*
*   char        *Input  [in] -> Array da cui effettuare la conversione
*   int         Size    [in]  -> Size della stringa da cui effettuare la conversione
* 
*   Return:
*       Stringa convertita da N0CA -> Normale
*
------------------------------------------------------------------------------------------*/
std::string NO0CHARTArrayToByteCharArray(char Input[],int Size)
{
    std::string Risposta;

    for(int i = 0; i < Size; i+=2)
    {
        if (Input[i] == 1)
            Risposta += '\0';
        else
            Risposta += Input[i + 1];
    }

    return Risposta;
}

/* Ottenimento del macaddress sulla macchina da cui viene eseguita la funzione */
char* getMAC()
{
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
    char* mac_addr = (char*)malloc(18);

    AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL)
    {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        free(mac_addr);
        return NULL; // it is safe to call free(NULL)
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(AdapterInfo);
        AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
        if (AdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            free(mac_addr);
            return NULL;
        }
    }

    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
    {
        // Contains pointer to current adapter info
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;

        //Scorre tutte le schede di rete del computer
        do
        {
            // technically should look at pAdapterInfo->AddressLength
            //   and not assume it is 6.
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
                pAdapterInfo->Address[0], pAdapterInfo->Address[1],
                pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
            printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
            // print them all, return the last one.
            // return mac_addr;

            printf("\n");
            pAdapterInfo = pAdapterInfo->Next;
        } while (false);//"while" è false perché vogliamo solo le informazioni della prima scheda di rete
        //altrimenti diventa while (pAdapterInfo)
    }
    free(AdapterInfo);

    return mac_addr; // caller must free.
}
