#pragma once


#include "Parser.h"
#include "Controller.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include "CommandDisplay.h"
#include "Task.h"
#include "CommandBuilder.h"
#include "CommandMark.h"

namespace TaskkyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	string command, result, taskdisplay;

	/// <summary>
	/// Summary for TaskkyGUIContent
	/// </summary>



	public ref class TaskkyGUIContent : public System::Windows::Forms::Form
	{
	public:
		TaskkyGUIContent(void)
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
		~TaskkyGUIContent()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	private: System::Windows::Forms::Label^  label3;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TaskkyGUIContent::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Snow;
			this->label1->Location = System::Drawing::Point(131, 46);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(150, 29);
			this->label1->TabIndex = 2;
			this->label1->Text = L"WELCOME TO";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Snow;
			this->label2->Location = System::Drawing::Point(131, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(151, 39);
			this->label2->TabIndex = 5;
			this->label2->Text = L"T.A.S.K.K.Y";
			this->label2->Click += gcnew System::EventHandler(this, &TaskkyGUIContent::label2_Click);
			// 
			// textBox1
			// 
			this->textBox1->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(3) { L"add", L"delete", L"display" });
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBox1->Location = System::Drawing::Point(58, 111);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(306, 23);
			this->textBox1->TabIndex = 6;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUIContent::textBox1_TextChanged_1);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUIContent::textBox1_KeyPress);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(58, 160);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(306, 184);
			this->richTextBox1->TabIndex = 11;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUIContent::richTextBox1_TextChanged_1);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->ForeColor = System::Drawing::Color::Snow;
			this->label3->Location = System::Drawing::Point(59, 140);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 13;
			this->label3->Click += gcnew System::EventHandler(this, &TaskkyGUIContent::label3_Click);
			// 
			// TaskkyGUIContent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(408, 379);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->DoubleBuffered = true;
			this->Name = L"TaskkyGUIContent";
			this->Text = L"TaskkyGUIContent";
			this->Load += gcnew System::EventHandler(this, &TaskkyGUIContent::TaskkyGUIContent_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TaskkyGUIContent_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
public: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	
	}
private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

	if (e->KeyChar == (char)13){
		//get data from the textbox
		if (command == "clr"){
			//clear screen
			return;
		}


		result = Controller::processUserInput(command);
	    
		//listView1->Items->Add(gcnew String(result.c_str()));
		label3->Text = gcnew String(result.c_str());
		//TaskManager::getInstance();
			
			if (command == "display"){
			
			label3->Visible = false;
			richTextBox1->Text = gcnew String(result.c_str());

		}

		//Console::WriteLine(listView2->Items->Add(gcnew String(taskname.c_str())) + "is" + "Added");
		textBox1->Clear();
	}


	}
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	command = msclr::interop::marshal_as< std::string >(textBox1->Text);
	//textBox1->Text = "test";
	}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void richTextBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
};
}
