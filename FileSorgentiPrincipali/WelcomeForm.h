#pragma once

namespace CppCLRWinformsProjekt {

	/// <summary>
	/// Riepilogo per MyForm
	/// </summary>
	public ref class WelcomeForm : public System::Windows::Forms::Form
	{
		public:
			System::Windows::Forms::Form^ SimulatorForm, ^ControlUnitForm;
			WelcomeForm(void)
			{
				InitializeComponent();
				//
				//TODO: aggiungere qui il codice del costruttore.
				//
				SimulatorForm = gcnew CppCLRWinformsProjekt::SimulatorForm();
				ControlUnitForm = gcnew CppCLRWinformsProjekt::ControlUnitForm();
			}

		protected:
			/// <summary>
			/// Pulire le risorse in uso.
			/// </summary>
			~WelcomeForm()
			{
				if (components)
				{
					delete components;
				}
			}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	protected:

		private:
			/// <summary>
			/// Variabile di progettazione necessaria.
			/// </summary>
			System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 43);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(160, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ControlUnit";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &WelcomeForm::ChangeFormCU);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(180, 43);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(160, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Simulator";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &WelcomeForm::ChangeFormSimulator);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(77, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(198, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Definire la finalità del dispositivo corrente";
			// 
			// WelcomeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(352, 78);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"WelcomeForm";
			this->Text = L"TRDP - Welcome";
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		#pragma endregion

		private: System::Void ChangeFormCU(System::Object^ sender, System::EventArgs^ e)
		{
			ControlUnitForm->Show();
			this->Hide();
		}

		private: System::Void ChangeFormSimulator(System::Object^ sender, System::EventArgs^ e)
		{
			SimulatorForm->Show();
			this->Hide();
		}
	};
}
