
#pragma once

#include "Parser.h"
#include "Controller.h"
#include <string>
#include <msclr\marshal_cppstd.h>


namespace TaskkyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	string command, result, taskname;


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class TaskkyGUI : public System::Windows::Forms::Form
	{
	public:
		TaskkyGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::Label^  label1;
	protected:

	protected:

	protected:

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;



	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(148, 40);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(150, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"WELCOME TO";
			this->label1->Click += gcnew System::EventHandler(this, &TaskkyGUI::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::MenuText;
			this->textBox1->Location = System::Drawing::Point(70, 110);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(306, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::textBox1_TextChanged);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUI::textBox1_KeyPress);
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->listView1->Location = System::Drawing::Point(70, 177);
			this->listView1->Margin = System::Windows::Forms::Padding(2);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(306, 166);
			this->listView1->TabIndex = 3;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &TaskkyGUI::listView1_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(146, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(151, 39);
			this->label2->TabIndex = 4;
			this->label2->Text = L"T.A.S.K.K.Y";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(70, 177);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(306, 177);
			this->textBox2->TabIndex = 8;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::textBox2_TextChanged_1);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::SystemColors::Menu;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Location = System::Drawing::Point(70, 144);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(306, 13);
			this->textBox3->TabIndex = 9;
			// 
			// TaskkyGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(460, 366);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"TaskkyGUI";
			this->Text = L"TaskkyGUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		command = msclr::interop::marshal_as< std::string >(textBox1->Text);
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {



	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		// try only		
		//	label1->Text = gcnew String(MainLogic::processUserInput("display").c_str());
	}


	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		if (e->KeyChar == (char)13){
			//get data from the textbox
			if (command == "clr"){
				//clear screen
				listView1->Clear();
				return;
			}

			result = Controller::processUserInput(command);
			//taskname = Parser::determineContent(command);
			//label1->Text = gcnew String(result.c_str());
			//listView1->Items->Add(gcnew String(result.c_str()));
			textBox3->Text = gcnew String(result.c_str());
			if (command == "display"){
				textBox3->Clear();
				textBox2->Text = gcnew String(result.c_str());
			}
			//listView1->Items->Add(gcnew String(result.c_str()));
			//listView2->Items->Add(gcnew String(taskname.c_str()));
			//listView2->Items->Add(gcnew String("is Added"));

			//Console::WriteLine(listView2->Items->Add(gcnew String(taskname.c_str())) + "is" + "Added");
			textBox1->Clear();
		}


	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}



	private: System::Void dateTimePicker1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void listView2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}


	private: System::Void textBox2_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	}
}
	;
}