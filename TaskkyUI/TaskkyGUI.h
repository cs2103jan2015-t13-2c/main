#pragma once
#include "Date.h"
#include <msclr\marshal_cppstd.h>
#include <string>
#include "TaskkyGUI.h"
#include "TaskkyGUIContent.h"


namespace TaskkyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	string test;
	string username, setvaluefortest;
	int test2;

	/// <summary>
	/// Summary for TaskkyGUI
	/// </summary>
	public ref class TaskkyGUI : public System::Windows::Forms::Form
	{
		Timer^ t = gcnew Timer();
	public:
		TaskkyGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			t->Interval = 1000;
			t->Tick += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);


			//Starts time when form loads
			t->Start(); //This will use timer1_Tick method
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TaskkyGUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;

	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TaskkyGUI::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Snow;
			this->label1->Location = System::Drawing::Point(73, 123);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(199, 73);
			this->label1->TabIndex = 0;
			this->label1->Text = L"00:00";
			this->label1->Click += gcnew System::EventHandler(this, &TaskkyGUI::label1_Click);
			// 
			// textBox2
			// 
			this->textBox2->AcceptsReturn = true;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(59, 231);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(239, 21);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::textBox2_TextChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Transparent;
			this->button1->ForeColor = System::Drawing::Color::Transparent;
			this->button1->Location = System::Drawing::Point(223, 232);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 20);
			this->button1->TabIndex = 3;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &TaskkyGUI::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Linen;
			this->label2->Location = System::Drawing::Point(81, 205);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(206, 26);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Enter Your Username: ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Snow;
			this->label4->Location = System::Drawing::Point(102, 59);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(150, 29);
			this->label4->TabIndex = 6;
			this->label4->Text = L"WELCOME TO";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Calibri", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Snow;
			this->label3->Location = System::Drawing::Point(100, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(151, 39);
			this->label3->TabIndex = 7;
			this->label3->Text = L"T.A.S.K.K.Y";
			// 
			// TaskkyGUI
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(334, 330);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->DoubleBuffered = true;
			this->Name = L"TaskkyGUI";
			this->Text = L"TaskkyGUI";
			this->Load += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	public: System::Void Test_Load(System::Object^  sender, System::EventArgs^  e) {

		//timer interval
		t->Interval = 1000;
		t->Tick += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);


		//Starts time when form loads
		t->Start(); //This will use timer1_Tick method

	}

			//time event handler
	public: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		//get current time
		DateTime^ MyDate = gcnew DateTime();

		//int hh, mm, ss;

		//int hh = 10;
		//long mm = 8;
		//long ss = 6;


		int hh = Date().getHour();
		int mm = Date().getMinute();
		//int ss = 00;
		//int ToInt32(DateTime::Now::Hour);
		//Convert ToInt32(System::DateTime::Now)

		/*int hh = DateTime->Now->Hour;
		int mm = DateTime.Now.Minute;
		int ss = DateTime.Now.Second;*/

		//time

		System::String^ time = "";

		//Padding leading zero
		if (hh < 10)
		{
			time += "0" + hh;
		}
		else
		{
			time += hh;
		}
		time += ":";

		if (mm < 10)
		{
			time += "0" + mm;
		}
		else
		{
			time += mm;
		}
		//time += ":";

		/*if (ss < 10)
		{
		time += "0" + ss;
		}
		else
		{
		time += ss;
		}
		time += ":"; */

		//Update label 
		label1->Text = time;


		//System::DateTime::Now::Hour

		//textBox1->Text = gcnew String(Date::Date().c_str());
		//label1->Text = gcnew String(MainLogic::processUserInput("display").c_str());
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

		test2 = Date().getHour();



	}
	public: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {


		username = msclr::interop::marshal_as< std::string >(textBox2->Text);

	}

	private: System::Void textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		if (e->KeyChar == (char)13){
			//textBox1->AppendText("test");
			return;
		}



		/*TaskkyGUI ^form2 = gcnew TaskkyGUI();
		form2->Show();
		this->Hide();*/


		//textBox1->Text = "TESTTESTTEST";
		//textBox1->Text = gcnew String(username.c_str());
	}
	public: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		setvaluefortest = msclr::interop::marshal_as< std::string >(textBox2->Text);

		TaskkyGUIContent ^taskkyguicontent = gcnew TaskkyGUIContent();
		taskkyguicontent->Show();
		this->Hide();
		/*Test2 ^test2 = gcnew Test2();
		test2->Show();
		this->Hide();*/


	}


	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
