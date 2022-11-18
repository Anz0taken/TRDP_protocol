#pragma once
#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;

namespace CppCLRWinformsProjekt
{
	TRDP_Handler_Rmt ConnectionHandlerRmt[5];		//Gestore connessioni per ogni indirizzo IP
	bool StartReciving = false;						//Flag per iniziare a ricevere

	/* Funzioni per l'update grafico dei dati */
	static void MessageChecker_Rmt();
	void UpdatePISStat_CU(System::String^ Testo);
	void UpdatePISStat_CAB_RMT(System::String^ Testo);
	void UpdatePISStat_MIC(System::String^ Testo);
	void UpdatePISStat_GPS(System::String^ Testo);
	void UpdatePISStat_DISPLAY_OUT(System::String^ Testo);
	void UpdatePISStat_DISPLAY_IN(System::String^ Testo);
	void UpdatePISStat_SWITCH(System::String^ Testo);
	void UpdatePISStat_PEI(System::String^ Testo);
	void UpdatePISStat_PAI(System::String^ Testo);
	void UpdatePISStat_CAM(System::String^ Testo);
	void UpdatePISStat_NVR(System::String^ Testo);

	/* Variabile utilizzata per la regolazione del thread utilizzato per la ricezione messaggi */
	std::atomic<bool> Mutex_Rmt = true;

	public ref class SimulatorForm : public System::Windows::Forms::Form {
		public:
			SimulatorForm(void)
			{
				InitializeComponent();
			}

		protected:
			~SimulatorForm()
			{
				/* Termina il thread per la ricezione */
				ReciverMsgsThread_Rmt->Abort();

				if (components)
				{
					/* Libera dalla memoria tutti i componenti grafici */
					delete components;
				}

				/* Termina l'applicazione */
				System::Windows::Forms::Application::Exit();
			}

		/* Variabili puntatori grafici all'interfaccia GUI  */
		System::Threading::Thread^ ReciverMsgsThread_Rmt = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(MessageChecker_Rmt));
		public: static System::Windows::Forms::TextBox^ DialogBox_;
		public: static System::Windows::Forms::Label^ StateCU;
		public: static System::Windows::Forms::Label^ STATE_MIC;
		public: static System::Windows::Forms::Label^ STATE_GPS;
		public: static System::Windows::Forms::Label^ STATE_DISPLAY_OUT;
		public: static System::Windows::Forms::Label^ STATE_DISPLAY_IN;
		public: static System::Windows::Forms::Label^ STATE_SWITCH;
		public: static System::Windows::Forms::Label^ STATE_PAI;
		public: static System::Windows::Forms::Label^ STATE_PEI;
		public: static System::Windows::Forms::Label^ STATE_CAM;
		public: static System::Windows::Forms::Label^ STATE_NVR_RMT;
		public: static System::Windows::Forms::Label^ STATE_NVR;
		private: System::Windows::Forms::Label^ label28;
		public:  System::Windows::Forms::TextBox^ IndirizzoIpD_5;
		private: System::Windows::Forms::Label^ label27;
		public:  System::Windows::Forms::TextBox^ IndirizzoIpD_4;
		private: System::Windows::Forms::Label^ label26;
		public:  System::Windows::Forms::TextBox^ IndirizzoIpD_3;
		private: System::Windows::Forms::Label^ label25;
		public:  System::Windows::Forms::TextBox^ IndirizzoIpD_2;
		private: System::Windows::Forms::Label^ label23;
		public:  System::Windows::Forms::TextBox^ IndirizzoIpD_1;
		private: System::Windows::Forms::Label^ label1;
		public:  System::Windows::Forms::TextBox^ MyIp;
		private: System::Windows::Forms::Button^ button1;
		private: System::Windows::Forms::Button^ Shutdown;
		private: System::Windows::Forms::Button^ Reset;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::Label^ label7;
		public:  System::Windows::Forms::TextBox^ PIS_CST_ID;
		private: System::Windows::Forms::Label^ label8;
		private: System::Windows::Forms::Label^ label9;
		private: System::Windows::Forms::NumericUpDown^ PIS_DISTP;
		private: System::Windows::Forms::NumericUpDown^ PIS_DISTT;
		private: System::Windows::Forms::NumericUpDown^ PIS_KMH;
		private: System::Windows::Forms::NumericUpDown^ PIS_STAT_PORT;
		private: System::Windows::Forms::NumericUpDown^ PIS_STAT_CAB;
		private: System::Windows::Forms::NumericUpDown^ PIS_STAT_DIS;
		private: System::Windows::Forms::NumericUpDown^ PIS_STAT_FIRARM;
		private: System::Windows::Forms::Button^ button3;
		private: System::Windows::Forms::Button^ button4;

		private: System::Windows::Forms::Label^ label;
		private: System::Windows::Forms::Label^ label12;
		private: System::Windows::Forms::Label^ label10;
		private: System::Windows::Forms::Label^ label11;
		private: System::Windows::Forms::Label^ STATE_PAI_LAB;
		private: System::Windows::Forms::Label^ STATE_PEI_LAB;
		private: System::Windows::Forms::Label^ STATE_CAM_LAB;
		private: System::Windows::Forms::Label^ label13;
		private: System::Windows::Forms::Label^ label14;
		private: System::ComponentModel::Container^ components;

		#pragma region Windows Form Designer generated code

		/* Inizializzazione componenti grafici */
		void InitializeComponent(void)
		{
			this->DialogBox_ = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->IndirizzoIpD_5 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->IndirizzoIpD_4 = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->IndirizzoIpD_3 = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->IndirizzoIpD_2 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->IndirizzoIpD_1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->MyIp = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Shutdown = (gcnew System::Windows::Forms::Button());
			this->Reset = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->PIS_CST_ID = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->PIS_DISTP = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_DISTT = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_KMH = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_STAT_PORT = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_STAT_CAB = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_STAT_DIS = (gcnew System::Windows::Forms::NumericUpDown());
			this->PIS_STAT_FIRARM = (gcnew System::Windows::Forms::NumericUpDown());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->STATE_MIC = (gcnew System::Windows::Forms::Label());
			this->STATE_GPS = (gcnew System::Windows::Forms::Label());
			this->STATE_DISPLAY_OUT = (gcnew System::Windows::Forms::Label());
			this->STATE_DISPLAY_IN = (gcnew System::Windows::Forms::Label());
			this->STATE_SWITCH = (gcnew System::Windows::Forms::Label());
			this->STATE_PAI = (gcnew System::Windows::Forms::Label());
			this->STATE_PEI = (gcnew System::Windows::Forms::Label());
			this->STATE_CAM = (gcnew System::Windows::Forms::Label());
			this->STATE_NVR_RMT = (gcnew System::Windows::Forms::Label());
			this->StateCU = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->STATE_NVR = (gcnew System::Windows::Forms::Label());
			this->label = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->STATE_PAI_LAB = (gcnew System::Windows::Forms::Label());
			this->STATE_PEI_LAB = (gcnew System::Windows::Forms::Label());
			this->STATE_CAM_LAB = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_DISTP))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_DISTT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_KMH))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_PORT))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_CAB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_DIS))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_FIRARM))->BeginInit();
			this->SuspendLayout();
			// 
			// DialogBox_
			// 
			this->DialogBox_->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DialogBox_->Location = System::Drawing::Point(12, 274);
			this->DialogBox_->Multiline = true;
			this->DialogBox_->Name = L"DialogBox_";
			this->DialogBox_->ReadOnly = true;
			this->DialogBox_->Size = System::Drawing::Size(596, 85);
			this->DialogBox_->TabIndex = 3;
			this->DialogBox_->Text = L"> Inserire proprio indirizzo IP e IP destinatario per stabilire la comunicazione."
				L"";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(12, 203);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(150, 13);
			this->label28->TabIndex = 58;
			this->label28->Text = L"Indirizzo IP IS_Diagnostic  (IN)";
			// 
			// IndirizzoIpD_5
			// 
			this->IndirizzoIpD_5->Location = System::Drawing::Point(15, 219);
			this->IndirizzoIpD_5->Name = L"IndirizzoIpD_5";
			this->IndirizzoIpD_5->Size = System::Drawing::Size(194, 20);
			this->IndirizzoIpD_5->TabIndex = 57;
			this->IndirizzoIpD_5->Text = L"224.0.0.4";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(12, 164);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(156, 13);
			this->label27->TabIndex = 56;
			this->label27->Text = L"Indirizzo IP PIS_Functional  (IN)";
			// 
			// IndirizzoIpD_4
			// 
			this->IndirizzoIpD_4->Location = System::Drawing::Point(15, 180);
			this->IndirizzoIpD_4->Name = L"IndirizzoIpD_4";
			this->IndirizzoIpD_4->Size = System::Drawing::Size(194, 20);
			this->IndirizzoIpD_4->TabIndex = 55;
			this->IndirizzoIpD_4->Text = L"224.0.0.3";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(12, 125);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(155, 13);
			this->label26->TabIndex = 54;
			this->label26->Text = L"Indirizzo IP TCMS_Config  (OU)";
			// 
			// IndirizzoIpD_3
			// 
			this->IndirizzoIpD_3->Location = System::Drawing::Point(15, 141);
			this->IndirizzoIpD_3->Name = L"IndirizzoIpD_3";
			this->IndirizzoIpD_3->Size = System::Drawing::Size(194, 20);
			this->IndirizzoIpD_3->TabIndex = 53;
			this->IndirizzoIpD_3->Text = L"224.0.0.2";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(12, 86);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(146, 13);
			this->label25->TabIndex = 52;
			this->label25->Text = L"Indirizzo IP TCMS_PIS (OUT)";
			// 
			// IndirizzoIpD_2
			// 
			this->IndirizzoIpD_2->Location = System::Drawing::Point(15, 102);
			this->IndirizzoIpD_2->Name = L"IndirizzoIpD_2";
			this->IndirizzoIpD_2->Size = System::Drawing::Size(194, 20);
			this->IndirizzoIpD_2->TabIndex = 51;
			this->IndirizzoIpD_2->Text = L"224.0.0.1";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(12, 48);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(170, 13);
			this->label23->TabIndex = 50;
			this->label23->Text = L"Indirizzo IP TCMS_Common (OUT)";
			// 
			// IndirizzoIpD_1
			// 
			this->IndirizzoIpD_1->Location = System::Drawing::Point(15, 64);
			this->IndirizzoIpD_1->Name = L"IndirizzoIpD_1";
			this->IndirizzoIpD_1->Size = System::Drawing::Size(194, 20);
			this->IndirizzoIpD_1->TabIndex = 49;
			this->IndirizzoIpD_1->Text = L"224.0.0.0";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 13);
			this->label1->TabIndex = 48;
			this->label1->Text = L"Indirizzo IP macchina corrente";
			// 
			// MyIp
			// 
			this->MyIp->Location = System::Drawing::Point(15, 25);
			this->MyIp->Name = L"MyIp";
			this->MyIp->Size = System::Drawing::Size(194, 20);
			this->MyIp->TabIndex = 47;
			this->MyIp->Text = L"192.168.10.000";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 245);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(194, 23);
			this->button1->TabIndex = 46;
			this->button1->Text = L"Set and Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SimulatorForm::SetAddress_MouseClick);
			// 
			// Shutdown
			// 
			this->Shutdown->Location = System::Drawing::Point(215, 61);
			this->Shutdown->Name = L"Shutdown";
			this->Shutdown->Size = System::Drawing::Size(96, 23);
			this->Shutdown->TabIndex = 59;
			this->Shutdown->Text = L"Shutdown";
			this->Shutdown->UseVisualStyleBackColor = true;
			this->Shutdown->Click += gcnew System::EventHandler(this, &SimulatorForm::Shutdown_click);
			// 
			// Reset
			// 
			this->Reset->Location = System::Drawing::Point(315, 60);
			this->Reset->Name = L"Reset";
			this->Reset->Size = System::Drawing::Size(94, 23);
			this->Reset->TabIndex = 60;
			this->Reset->Text = L"Reset";
			this->Reset->UseVisualStyleBackColor = true;
			this->Reset->Click += gcnew System::EventHandler(this, &SimulatorForm::Reset_click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(212, 85);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 13);
			this->label2->TabIndex = 64;
			this->label2->Text = L"Dist. parziale (km)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(312, 85);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(80, 13);
			this->label3->TabIndex = 65;
			this->label3->Text = L"Dist. totale (km)";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(415, 85);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 13);
			this->label4->TabIndex = 66;
			this->label4->Text = L"Velocità (km)";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(512, 85);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(100, 13);
			this->label5->TabIndex = 68;
			this->label5->Text = L"Porte (0, 1SX, 2DX)";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(612, 85);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(99, 13);
			this->label6->TabIndex = 70;
			this->label6->Text = L"Cabina attiva (0 , 1)";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(712, 85);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(88, 13);
			this->label7->TabIndex = 72;
			this->label7->Text = L"ConstId (16 char)";
			// 
			// PIS_CST_ID
			// 
			this->PIS_CST_ID->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PIS_CST_ID->Location = System::Drawing::Point(715, 101);
			this->PIS_CST_ID->MaxLength = 16;
			this->PIS_CST_ID->Name = L"PIS_CST_ID";
			this->PIS_CST_ID->Size = System::Drawing::Size(94, 19);
			this->PIS_CST_ID->TabIndex = 71;
			this->PIS_CST_ID->Text = L"XXXXXXXXXXXXXXXX";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(812, 85);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(68, 13);
			this->label8->TabIndex = 74;
			this->label8->Text = L"Display (0, 1)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(912, 85);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(92, 13);
			this->label9->TabIndex = 76;
			this->label9->Text = L"Antiincendio (0, 1)";
			// 
			// PIS_DISTP
			// 
			this->PIS_DISTP->Location = System::Drawing::Point(215, 102);
			this->PIS_DISTP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200000000, 0, 0, 0 });
			this->PIS_DISTP->Name = L"PIS_DISTP";
			this->PIS_DISTP->Size = System::Drawing::Size(96, 20);
			this->PIS_DISTP->TabIndex = 77;
			// 
			// PIS_DISTT
			// 
			this->PIS_DISTT->Location = System::Drawing::Point(317, 101);
			this->PIS_DISTT->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000000, 0, 0, 0 });
			this->PIS_DISTT->Name = L"PIS_DISTT";
			this->PIS_DISTT->Size = System::Drawing::Size(92, 20);
			this->PIS_DISTT->TabIndex = 78;
			// 
			// PIS_KMH
			// 
			this->PIS_KMH->Location = System::Drawing::Point(418, 101);
			this->PIS_KMH->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->PIS_KMH->Name = L"PIS_KMH";
			this->PIS_KMH->Size = System::Drawing::Size(92, 20);
			this->PIS_KMH->TabIndex = 79;
			// 
			// PIS_STAT_PORT
			// 
			this->PIS_STAT_PORT->Location = System::Drawing::Point(516, 102);
			this->PIS_STAT_PORT->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->PIS_STAT_PORT->Name = L"PIS_STAT_PORT";
			this->PIS_STAT_PORT->Size = System::Drawing::Size(92, 20);
			this->PIS_STAT_PORT->TabIndex = 80;
			// 
			// PIS_STAT_CAB
			// 
			this->PIS_STAT_CAB->Location = System::Drawing::Point(614, 102);
			this->PIS_STAT_CAB->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PIS_STAT_CAB->Name = L"PIS_STAT_CAB";
			this->PIS_STAT_CAB->Size = System::Drawing::Size(92, 20);
			this->PIS_STAT_CAB->TabIndex = 81;
			// 
			// PIS_STAT_DIS
			// 
			this->PIS_STAT_DIS->Location = System::Drawing::Point(815, 102);
			this->PIS_STAT_DIS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PIS_STAT_DIS->Name = L"PIS_STAT_DIS";
			this->PIS_STAT_DIS->Size = System::Drawing::Size(92, 20);
			this->PIS_STAT_DIS->TabIndex = 82;
			// 
			// PIS_STAT_FIRARM
			// 
			this->PIS_STAT_FIRARM->Location = System::Drawing::Point(915, 102);
			this->PIS_STAT_FIRARM->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PIS_STAT_FIRARM->Name = L"PIS_STAT_FIRARM";
			this->PIS_STAT_FIRARM->Size = System::Drawing::Size(92, 20);
			this->PIS_STAT_FIRARM->TabIndex = 83;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(215, 245);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(194, 23);
			this->button3->TabIndex = 85;
			this->button3->Text = L"Send TCMS_PIS";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SimulatorForm::Send_PIS);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(415, 245);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(194, 23);
			this->button4->TabIndex = 86;
			this->button4->Text = L"Send TCMS_Config";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// STATE_MIC
			// 
			this->STATE_MIC->AutoSize = true;
			this->STATE_MIC->BackColor = System::Drawing::Color::Gray;
			this->STATE_MIC->Location = System::Drawing::Point(978, 346);
			this->STATE_MIC->Name = L"STATE_MIC";
			this->STATE_MIC->Size = System::Drawing::Size(27, 13);
			this->STATE_MIC->TabIndex = 106;
			this->STATE_MIC->Text = L"N/A";
			// 
			// STATE_GPS
			// 
			this->STATE_GPS->AutoSize = true;
			this->STATE_GPS->BackColor = System::Drawing::Color::Gray;
			this->STATE_GPS->Location = System::Drawing::Point(978, 329);
			this->STATE_GPS->Name = L"STATE_GPS";
			this->STATE_GPS->Size = System::Drawing::Size(27, 13);
			this->STATE_GPS->TabIndex = 105;
			this->STATE_GPS->Text = L"N/A";
			// 
			// STATE_DISPLAY_OUT
			// 
			this->STATE_DISPLAY_OUT->AutoSize = true;
			this->STATE_DISPLAY_OUT->BackColor = System::Drawing::Color::Gray;
			this->STATE_DISPLAY_OUT->Location = System::Drawing::Point(978, 312);
			this->STATE_DISPLAY_OUT->Name = L"STATE_DISPLAY_OUT";
			this->STATE_DISPLAY_OUT->Size = System::Drawing::Size(27, 13);
			this->STATE_DISPLAY_OUT->TabIndex = 104;
			this->STATE_DISPLAY_OUT->Text = L"N/A";
			// 
			// STATE_DISPLAY_IN
			// 
			this->STATE_DISPLAY_IN->AutoSize = true;
			this->STATE_DISPLAY_IN->BackColor = System::Drawing::Color::Gray;
			this->STATE_DISPLAY_IN->Location = System::Drawing::Point(978, 295);
			this->STATE_DISPLAY_IN->Name = L"STATE_DISPLAY_IN";
			this->STATE_DISPLAY_IN->Size = System::Drawing::Size(27, 13);
			this->STATE_DISPLAY_IN->TabIndex = 103;
			this->STATE_DISPLAY_IN->Text = L"N/A";
			// 
			// STATE_SWITCH
			// 
			this->STATE_SWITCH->AutoSize = true;
			this->STATE_SWITCH->BackColor = System::Drawing::Color::Gray;
			this->STATE_SWITCH->Location = System::Drawing::Point(978, 278);
			this->STATE_SWITCH->Name = L"STATE_SWITCH";
			this->STATE_SWITCH->Size = System::Drawing::Size(27, 13);
			this->STATE_SWITCH->TabIndex = 102;
			this->STATE_SWITCH->Text = L"N/A";
			// 
			// STATE_PAI
			// 
			this->STATE_PAI->AutoSize = true;
			this->STATE_PAI->BackColor = System::Drawing::Color::Gray;
			this->STATE_PAI->Location = System::Drawing::Point(773, 346);
			this->STATE_PAI->Name = L"STATE_PAI";
			this->STATE_PAI->Size = System::Drawing::Size(27, 13);
			this->STATE_PAI->TabIndex = 101;
			this->STATE_PAI->Text = L"N/A";
			// 
			// STATE_PEI
			// 
			this->STATE_PEI->AutoSize = true;
			this->STATE_PEI->BackColor = System::Drawing::Color::Gray;
			this->STATE_PEI->Location = System::Drawing::Point(773, 329);
			this->STATE_PEI->Name = L"STATE_PEI";
			this->STATE_PEI->Size = System::Drawing::Size(27, 13);
			this->STATE_PEI->TabIndex = 100;
			this->STATE_PEI->Text = L"N/A";
			// 
			// STATE_CAM
			// 
			this->STATE_CAM->AutoSize = true;
			this->STATE_CAM->BackColor = System::Drawing::Color::Gray;
			this->STATE_CAM->Location = System::Drawing::Point(773, 312);
			this->STATE_CAM->Name = L"STATE_CAM";
			this->STATE_CAM->Size = System::Drawing::Size(27, 13);
			this->STATE_CAM->TabIndex = 99;
			this->STATE_CAM->Text = L"N/A";
			// 
			// STATE_NVR_RMT
			// 
			this->STATE_NVR_RMT->AutoSize = true;
			this->STATE_NVR_RMT->BackColor = System::Drawing::Color::Gray;
			this->STATE_NVR_RMT->Location = System::Drawing::Point(773, 295);
			this->STATE_NVR_RMT->Name = L"STATE_NVR_RMT";
			this->STATE_NVR_RMT->Size = System::Drawing::Size(27, 13);
			this->STATE_NVR_RMT->TabIndex = 98;
			this->STATE_NVR_RMT->Text = L"N/A";
			// 
			// StateCU
			// 
			this->StateCU->AutoSize = true;
			this->StateCU->BackColor = System::Drawing::Color::Gray;
			this->StateCU->Location = System::Drawing::Point(773, 276);
			this->StateCU->Name = L"StateCU";
			this->StateCU->Size = System::Drawing::Size(27, 13);
			this->StateCU->TabIndex = 97;
			this->StateCU->Text = L"N/A";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(821, 342);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(107, 17);
			this->label12->TabIndex = 96;
			this->label12->Text = L"Stato Microfono";
			// 
			// STATE_NVR
			// 
			this->STATE_NVR->AutoSize = true;
			this->STATE_NVR->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->STATE_NVR->Location = System::Drawing::Point(821, 325);
			this->STATE_NVR->Name = L"STATE_NVR";
			this->STATE_NVR->Size = System::Drawing::Size(74, 17);
			this->STATE_NVR->TabIndex = 95;
			this->STATE_NVR->Text = L"Stato GPS";
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label->Location = System::Drawing::Point(821, 308);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(135, 17);
			this->label->TabIndex = 94;
			this->label->Text = L"Stato Display (OUT)";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(821, 291);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(118, 17);
			this->label10->TabIndex = 93;
			this->label10->Text = L"Stato Display (IN)";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(821, 274);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(85, 17);
			this->label11->TabIndex = 92;
			this->label11->Text = L"Stato Switch";
			// 
			// STATE_PAI_LAB
			// 
			this->STATE_PAI_LAB->AutoSize = true;
			this->STATE_PAI_LAB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->STATE_PAI_LAB->Location = System::Drawing::Point(616, 342);
			this->STATE_PAI_LAB->Name = L"STATE_PAI_LAB";
			this->STATE_PAI_LAB->Size = System::Drawing::Size(66, 17);
			this->STATE_PAI_LAB->TabIndex = 91;
			this->STATE_PAI_LAB->Text = L"Stato PAI";
			// 
			// STATE_PEI_LAB
			// 
			this->STATE_PEI_LAB->AutoSize = true;
			this->STATE_PEI_LAB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->STATE_PEI_LAB->Location = System::Drawing::Point(616, 325);
			this->STATE_PEI_LAB->Name = L"STATE_PEI_LAB";
			this->STATE_PEI_LAB->Size = System::Drawing::Size(66, 17);
			this->STATE_PEI_LAB->TabIndex = 90;
			this->STATE_PEI_LAB->Text = L"Stato PEI";
			// 
			// STATE_CAM_LAB
			// 
			this->STATE_CAM_LAB->AutoSize = true;
			this->STATE_CAM_LAB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->STATE_CAM_LAB->Location = System::Drawing::Point(616, 308);
			this->STATE_CAM_LAB->Name = L"STATE_CAM_LAB";
			this->STATE_CAM_LAB->Size = System::Drawing::Size(94, 17);
			this->STATE_CAM_LAB->TabIndex = 89;
			this->STATE_CAM_LAB->Text = L"Stato Camere";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(616, 291);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(74, 17);
			this->label13->TabIndex = 88;
			this->label13->Text = L"Stato NVR";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(616, 274);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(64, 17);
			this->label14->TabIndex = 87;
			this->label14->Text = L"Stato CU";
			// 
			// SimulatorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1017, 370);
			this->Controls->Add(this->STATE_MIC);
			this->Controls->Add(this->STATE_GPS);
			this->Controls->Add(this->STATE_DISPLAY_OUT);
			this->Controls->Add(this->STATE_DISPLAY_IN);
			this->Controls->Add(this->STATE_SWITCH);
			this->Controls->Add(this->STATE_PAI);
			this->Controls->Add(this->STATE_PEI);
			this->Controls->Add(this->STATE_CAM);
			this->Controls->Add(this->STATE_NVR_RMT);
			this->Controls->Add(this->StateCU);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->STATE_NVR);
			this->Controls->Add(this->label);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->STATE_PAI_LAB);
			this->Controls->Add(this->STATE_PEI_LAB);
			this->Controls->Add(this->STATE_CAM_LAB);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->PIS_STAT_FIRARM);
			this->Controls->Add(this->PIS_STAT_DIS);
			this->Controls->Add(this->PIS_STAT_CAB);
			this->Controls->Add(this->PIS_STAT_PORT);
			this->Controls->Add(this->PIS_KMH);
			this->Controls->Add(this->PIS_DISTT);
			this->Controls->Add(this->PIS_DISTP);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->PIS_CST_ID);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Reset);
			this->Controls->Add(this->Shutdown);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->IndirizzoIpD_5);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->IndirizzoIpD_4);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->IndirizzoIpD_3);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->IndirizzoIpD_2);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->IndirizzoIpD_1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->MyIp);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->DialogBox_);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"SimulatorForm";
			this->Text = L"TCMS Simulator V1.1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_DISTP))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_DISTT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_KMH))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_PORT))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_CAB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_DIS))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIS_STAT_FIRARM))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	#pragma endregion

	private:

		/*==========================================================================================================================
		*	La funzione sottostante serve a configurare gli indirizzi IP inseriti, uno per ogni task, al suo rispettivo oggetto
		*	ConnectionHandlerRmt[i], inizializzare TLC, configurare variabili per funzioni publish, subscribe TRDP
		*	e iniziare l'ascolto per la ricezione dei messaggi.
		---------------------------------------------------------------------------------------------------------------------------*/
		System::Void SetAddress_MouseClick(System::Object^ sender, System::EventArgs^ e)
		{
			/* Se il thread non è attivo */
			if ((int)ReciverMsgsThread_Rmt->ThreadState != 0 || !Mutex_Rmt)
			{
				this->DialogBox_->AppendText("\r\n> Settando gli indirizzi ip... (Aspettare qualche secondo)");

				/* Tempo di attesa necessario per prevenire la chiusura e il riutilizzo istantaneo dell'applicazione che potrebbe creare conflitti. */
				Sleep(RCVH_TTL + 200);

				/* Ottenimento indirizzi IP */
				std::string ipd[5];
				ipd[0] = msclr::interop::marshal_as<std::string>(IndirizzoIpD_1->Text);
				ipd[1] = msclr::interop::marshal_as<std::string>(IndirizzoIpD_2->Text);
				ipd[2] = msclr::interop::marshal_as<std::string>(IndirizzoIpD_3->Text);
				ipd[3] = msclr::interop::marshal_as<std::string>(IndirizzoIpD_4->Text);
				ipd[4] = msclr::interop::marshal_as<std::string>(IndirizzoIpD_5->Text);

				std::string ips = msclr::interop::marshal_as<std::string>(MyIp->Text);

				/* Configurazione protocolli e dati comunicazione */
				int CommunicationTypes[5];
				CommunicationTypes[0] = TRDP_TCMS_Common;
				CommunicationTypes[1] = TRDP_TCMS_PIS;
				CommunicationTypes[2] = TRDP_TCMS_Config;
				CommunicationTypes[3] = TRDP_PIS_Functional;
				CommunicationTypes[4] = TRDP_PIS_Diagnostic;

				/* Porta principale utilizzata per la connessione */
				int Port_ = 17224;

				/* Quante connessioni inizializzate hanno avuto successo */
				int ConnessioniSuccesso = 0;

				/* Per ogni indirizzo IP */
				for (int i = 0; i < 5; i++)
				{
					/*	Nel blocco di codice sottostante, è stato effettuato un "S + 1" => 1, questo perchè nelle librerie
					*	TRDP, una volta inizializzata una connessione, una variabile di controllo è tale che ci dà errore se si prova
					*	inizializzare una nuova connessione.
					* 
					*	Ciò implica che, nel caso ci fosse un errore nell'inizializzazione TLC e si ha il sospetto, bisogna rimuovere l'OR con true.
					*/
					if (ConnectionHandlerRmt[i].StartTLC() || true)	//starta il TCL
					{
						ConnectionHandlerRmt[i].SetIps(ips, ipd[i]);							//Setta gli indirizzi IP (Host, Indirizzo IP mirato per la task)
						ConnectionHandlerRmt[i].SetCommunicationType(CommunicationTypes[i]);	//Setta il protocollo comunicazione
						ConnectionHandlerRmt[i].SetSessionVars(Port_++);

						/* Apertura sessione */
						if (ConnectionHandlerRmt[i].OpenSession())
						{
							/* Settaggio varabili subscribe */
							ConnectionHandlerRmt[i].SetSubscribeVars();

							/* Subscribe */
							if (ConnectionHandlerRmt[i].Subscribe())
							{
								/* Settaggio varabili publish */
								ConnectionHandlerRmt[i].SetPublishVars();

								/* Publish */
								if (ConnectionHandlerRmt[i].Publish())
								{
									/* Se tutto ha avuto successo, allora aumentiamo il contatore */
									ConnessioniSuccesso++;
								}
							}
						}
					}
				}

				this->DialogBox_->AppendText("\r\n> Software in ascolto (" + ConnessioniSuccesso + "/5)");

				//Se almeno una connessione ha avuto successo e il thread ricezione non è stato già startato
				if (ConnessioniSuccesso && Mutex_Rmt)
				{
					ReciverMsgsThread_Rmt->Start();	//Inizia l'ascolto
					Mutex_Rmt = false;				//Thread già in ascolto
				}
			}
		}

		/*==========================================================================================================================
		*	La funzione sottostante serve a mandare un messaggio di tipo TRDP_TCMS_Common in cui comunichiamo la richiesta di shutdown
		---------------------------------------------------------------------------------------------------------------------------*/
		private: System::Void Shutdown_click(System::Object^ sender, System::EventArgs^ e)
		{
			ConnectionHandlerRmt[255 - TRDP_TCMS_Common].SendMsg(TRDP_TCMS_Common, "\0");
		}

		/*==========================================================================================================================
		*	La funzione sottostante serve a mandare un messaggio di tipo TRDP_TCMS_Common in cui comunichiamo la richiesta di reset
		---------------------------------------------------------------------------------------------------------------------------*/
		private: System::Void Reset_click(System::Object^ sender, System::EventArgs^ e)
		{
			ConnectionHandlerRmt[255 - TRDP_TCMS_Common].SendMsg(TRDP_TCMS_Common, "\1");
		}

		/*==========================================================================================================================
		*	La funzione sottostante serve a mandare un messaggio di tipo TRDP_TCMS_PIS in cui comunichiamo tutte le informazioni del
		*	protocollo conosciuto.
		---------------------------------------------------------------------------------------------------------------------------*/
		private: System::Void Send_PIS(System::Object^ sender, System::EventArgs^ e)
		{
			/*===========================================================================================================
			*	FORMATTAZIONE INVIO BYTE ARRAY (NO0CHARPROTOCOL).
			*
			*	Ogni byte di informazione utile deve essere preceduto da un altro byte che indicherà
			*	se il byte successivo ha valore zero. Questo perché nel pacchetto non può esserci alcun carattere
			*	uguale a zero.
			*
			*	Il byte che precede è 1 se indica che il prossimo byte ha valore 0,
			*	2 se il byte ha valore prorio. Se il byte di informazione prossimo è uguale a uno, quello di valore
			*	zero deve (Quello che segue dopo) deve essere 1.
			*
			*	Ex:
			*		char array da inviare :
			*			231,0,32,0
			*
			*		Risultato:
			*			2,231 / 1,1 / 2,32 / 1,1
			*
			------------------------------------------------------------------------------------------------------------*/

			std::string Message = "";	//Stringa contenente volta per volta le informazioni dei protocolli descritti necessaria per la conversione da int a CHAR0PROTOCOL
			std::string Tutto = "";		//Tutto il messaggio da inviare
			int DatoIntero;				//Volta per volta contenente il numero intero del dato da inviare
			char Array[9];				//Char array utilizzato per la conversione in CHAR0PROTOCOL

			/* Estrapolazione, rielaborazione e inclusione dato -> Km Partenza */
			DatoIntero = System::Int32::Parse(PIS_DISTP->Text);
			FromNumberToByteArray(DatoIntero, Message, 4);
			ByteCharArrayToNO0CHARArray(Array, Message, 4);
			Tutto += Array;

			/* Estrapolazione, rielaborazione e inclusione dato -> Km Totale */
			DatoIntero = System::Int32::Parse(PIS_DISTT->Text);
			FromNumberToByteArray(DatoIntero, Message, 4);
			ByteCharArrayToNO0CHARArray(Array, Message, 4);
			Tutto += Array;

			/* Estrapolazione, rielaborazione e inclusione dato -> Velocità */
			DatoIntero = System::Int32::Parse(PIS_KMH->Text);
			FromNumberToByteArray(DatoIntero, Message, 2);
			ByteCharArrayToNO0CHARArray(Array, Message, 2);
			Tutto += Array;

			/*===========================================================================================
			*	Estrapolazione, rielaborazione e inclusione dato -> Stato porte
			*	Essendo che vogliamo passare un dato cui può avere <=255 tipi diversi di informazione,
			*	basta un byte di rappresentazione
			-------------------------------------------------------------------------------------------*/
			DatoIntero = System::Int32::Parse(PIS_STAT_PORT->Text);
			DatoIntero++;					//Escludiamo il caso in cui il dato è zero.
			Tutto += char(DatoIntero);		//Inclusione nella stringa finale da mandare

			/*===========================================================================================
			*	Estrapolazione, rielaborazione e inclusione dato -> Stato cabina
			*	Essendo che vogliamo passare un dato cui può avere <=255 tipi diversi di informazione,
			*	basta un byte di rappresentazione
			-------------------------------------------------------------------------------------------*/
			DatoIntero = System::Int32::Parse(PIS_STAT_CAB->Text);
			DatoIntero++;					//Escludiamo il caso in cui il dato è zero.
			Tutto += char(DatoIntero);		//Inclusione nella stringa finale da mandare

			/*===========================================================================================
			*	Estrapolazione, rielaborazione e inclusione dato -> ConstId
			*	Essendo ConstId una stringa di massimo 16 caratteri, vogliamo assicurarci che l'utente
			*	abbia inserito una stringa di tale lnghezza e aggiunta al messaggio da inviare.
			*	
			*	Nel caso in cui la stringa dovessere risultare minore di 16 caratteri, c'è un rempimento
			*	di ( 16 - ConstId->Length) caratteri di 1.
			* 
			*	Nel caso in cui la stringa termina quindi prima, la end of string, di valore 0, viene
			*	convertita a 1 che, successivamente dal ricevitore viene riconvertito.
			-------------------------------------------------------------------------------------------*/
			System::String^ ConstId = PIS_CST_ID->Text;	//Ottenimento ConstId
			for (int i = 0; i < ConstId->Length; i++)	//Per tutta la sua lughezza
				if (ConstId[i] != 0)					//Se il carattere non è 0
					Tutto += ConstId[i];				//Aggiungi il suo valore alla stringa finale da inviare
				else
					Tutto += char(1);					//Aggiungi 1 (che come semantica è l'end of string)

			/* Rempimento del size<16 */
			if(ConstId->Length<16)
				for(int i = 16 - ConstId->Length; i>0; i--)
					Tutto += char(1);

			/*===========================================================================================
			*	Estrapolazione, rielaborazione e inclusione dato -> Stato DIS
			*	Essendo che vogliamo passare un dato cui può avere <=255 tipi diversi di informazione,
			*	basta un byte di rappresentazione
			-------------------------------------------------------------------------------------------*/
			DatoIntero = System::Int32::Parse(PIS_STAT_DIS->Text);
			DatoIntero++;					//Escludiamo il caso in cui il dato è zero.
			Tutto += char(DatoIntero);		//Inclusione nella stringa finale da mandare

			/*===========================================================================================
			*	Estrapolazione, rielaborazione e inclusione dato -> Stato allarme antiincendio
			*	Essendo che vogliamo passare un dato cui può avere <=255 tipi diversi di informazione,
			*	basta un byte di rappresentazione
			-------------------------------------------------------------------------------------------*/
			DatoIntero = System::Int32::Parse(PIS_STAT_FIRARM->Text);
			DatoIntero++;					//Escludiamo il caso in cui il dato è zero.
			Tutto += char(DatoIntero);		//Inclusione nella stringa finale da mandare

			/* Manda messaggio PIS */
			ConnectionHandlerRmt[255 - TRDP_TCMS_PIS].SendMsg(TRDP_TCMS_PIS, Tutto);
		}
	};

	/*=================================================================
	*	Funzione utilizzata come thread per la ricezione dei messaggi
	*	del simulatore.
	-----------------------------------------------------------------*/
	static void MessageChecker_Rmt()
	{
		/* Messaggio ricevuto */
		std::string Response = "";

		while (true)
		{
			if (!Mutex_Rmt)
			{
				/* Per ogni connessione stabilita */
				for (int i = 0; i < 5; i++)
				{
					ConnectionHandlerRmt[i].RefreshMsgs();				//Aggiornamento coda dei messaggi in arrivo e da mandare
					Response += ConnectionHandlerRmt[i].ReciveMsg();	//Ottieni il messaggio ricevuto dal mittente M[i] (Il metodo è incaricato di stampare su schermo il messaggio in caso di messaggio nuovo)

					/* Se abbiamo ricevuto un messaggio */
					if (Response != "")
					{
						/* Se il messaggio in arrivo è TRDP_PIS_Diagnostic */
						if (Response.at(0) == char(TRDP_PIS_Diagnostic))
						{
							std::string trueCharArray = NO0CHARTArrayToByteCharArray((char*)Response.c_str() + 1, 8);	//Ottieni la stringa di tipo NO0CHAR rappresentate gli stati della CU
							int Numero = FromByteArrayToNumber(trueCharArray, sizeof(int));								//Ottieni il suo reciproco numero

							/* Puntatore di funzioni in cui ogni funzione è mirata all'aggiornamento grafico di uno stato definito */
							void (*foo[10])(System::String ^ Testo);
							foo[0] = UpdatePISStat_NVR;					//bit 1 valore(1)
							foo[1] = UpdatePISStat_CAM;					//bit 2 valore(2)
							foo[2] = UpdatePISStat_PEI;					//bit 3 valore(4)
							foo[3] = UpdatePISStat_PAI;					//bit 4 valore(8)
							foo[4] = UpdatePISStat_SWITCH;				//bit 5 valore(16)
							foo[5] = UpdatePISStat_DISPLAY_IN;			//bit 6 valore(32)
							foo[6] = UpdatePISStat_DISPLAY_OUT;			//bit 7 valore(64)
							foo[7] = UpdatePISStat_GPS;					//bit 8 valore(128)
							foo[8] = UpdatePISStat_MIC;					//bit 9 valore(256)

							/* Essendo che abbiamo ricevuto un messaggio, questo implica che la CU è attiva */
							UpdatePISStat_CU("1");

							/*=================================================
							*	Estrapolazione informazione
							*	Avendo ricevuto un intero,
							*	viene utilizzata la tecnologia bitmask per
							*	la memorizzazione degli stati per intero.
							--------------------------------------------------*/
							for (int i = 0; i < 9; i++)
								if (Numero & (1 << i))
									foo[i]("1");		//Aggiorna lo stato corrispondente a quel bit (ON)
								else
									foo[i]("0");		//Aggiorna lo stato corrispondente a quel bit (OFF)
						}

						Response = "";
					}
				}
			}
		}
	}

	/*=================================================================
	*	Funzione utilizzata come thread per la ricezione dei messaggi
	*	del simulatore.
	-----------------------------------------------------------------*/
	void UpdateTextBox_Rmt(System::String^ Testo)
	{
		System::Windows::Forms::TextBox^ TextBox = CppCLRWinformsProjekt::SimulatorForm::DialogBox_;

		if (TextBox->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;


			TextBox->Invoke(gcnew System::Action<System::String^>(UpdateTextBox_Rmt), strarray);
			return;
		}

		TextBox->AppendText("\r\n>" + Testo);
	}

	/*============================================================================================================================================
	*	INIZIO CODICE GENERATO IN PHP
	*	Ogni funzione tra queste sottoelencate serve ad aggiornare lo stato di un elemento "Label" del form controlUnit.
	*	Essendo che ogni funzione si differenzia sull'id del label in cui cambiare il contenuto Text e il suo colore, le funzioni sottostanti
	*	sono state generate automaticamente da uno script in php.
	*
	*	Ogni funzione è differenziata per Nome "CppCLRWinformsProjekt::SimulatorForm::X".
	--------------------------------------------------------------------------------------------------------------------------------------------*/

	void UpdatePISStat_CAB_RMT(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::StateCU;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_CAB_RMT), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}
	}

	void UpdatePISStat_MIC(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_MIC;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_MIC), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_GPS(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_GPS;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_GPS), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_DISPLAY_OUT(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_DISPLAY_OUT;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_DISPLAY_OUT), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_DISPLAY_IN(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_DISPLAY_IN;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_DISPLAY_IN), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_SWITCH(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_SWITCH;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_SWITCH), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_PAI(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_PAI;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_PAI), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_CAM(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_CAM;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_CAM), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_NVR(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_NVR_RMT;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_NVR), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_PEI(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::STATE_PEI;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_PEI), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	void UpdatePISStat_CU(System::String^ Testo)
	{
		System::Windows::Forms::Label^ Label = CppCLRWinformsProjekt::SimulatorForm::StateCU;

		if (Label->InvokeRequired)
		{
			array<System::String^>^ strarray = gcnew array<System::String^>(1);
			strarray[0] = Testo;

			Label->Invoke(gcnew System::Action<System::String^>(UpdatePISStat_CU), strarray);
			return;
		}

		if (Testo == "1")
		{
			Label->Text = "ON ";
			Label->BackColor = System::Drawing::Color::Green;
		}
		else
		{
			Label->Text = "OFF";
			Label->BackColor = System::Drawing::Color::Red;
		}

	}

	/*==================================================================================================================
	*	FINE CODICI GENERATI CON PHP
	------------------------------------------------------------------------------------------------------------------*/
}
