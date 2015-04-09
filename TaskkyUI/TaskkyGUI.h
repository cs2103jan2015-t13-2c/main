#pragma once


#include "Parser.h"
#include "Controller.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include "CommandDisplay.h"
#include "Task.h"
#include "CommandBuilder.h"
#include "CommandMark.h"
#include "TaskkyGUI.h"
#include "Storage.h"

namespace TaskkyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	string command, result, taskdisplay, result2;
	string usernamedisplay;

	/// <summary>
	/// Summary for TaskkyGUI
	/// </summary>



	public ref class TaskkyGUI : public System::Windows::Forms::Form
	{
	public:
		TaskkyGUI()
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			TaskManager::loadAllCurrentTasks(Storage::readFromFile());
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

	protected:

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Label^  label6;

	private:

	public:





	private:



	private: System::ComponentModel::IContainer^  components;



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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(3) { L"add", L"delete", L"display" });
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->Location = System::Drawing::Point(62, 357);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(306, 30);
			this->textBox1->TabIndex = 6;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::textBox1_TextChanged_1);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUI::textBox1_KeyPress);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->richTextBox1->ForeColor = System::Drawing::Color::White;
			this->richTextBox1->Location = System::Drawing::Point(429, 70);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(459, 405);
			this->richTextBox1->TabIndex = 11;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::richTextBox1_TextChanged_1);
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
			this->label3->Click += gcnew System::EventHandler(this, &TaskkyGUI::label3_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", 42, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->label1->Location = System::Drawing::Point(18, 93);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(369, 83);
			this->label1->TabIndex = 14;
			this->label1->Text = L"T.A.S.K.K.Y";
			this->label1->Click += gcnew System::EventHandler(this, &TaskkyGUI::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Snow;
			this->label2->Location = System::Drawing::Point(65, 153);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(289, 108);
			this->label2->TabIndex = 15;
			this->label2->Text = L"00:00";
			this->label2->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(56, 389);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 18);
			this->label4->TabIndex = 16;
			this->label4->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::label4_TextChanged);
			this->label4->Click += gcnew System::EventHandler(this, &TaskkyGUI::label4_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(59, 341);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 13);
			this->label6->TabIndex = 18;
			// 
			// TaskkyGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(960, 540);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"TaskkyGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TaskkyGUI";
			this->Load += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TaskkyGUIContent_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	public: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		if (e->KeyChar == (char)13){
			//get data from the textbox

			result = Controller::processUserInput(command);
			result2 = Controller::processUserInput("display");

			label6->Text = gcnew String(result.c_str());

			if (command == "display"){

				label6->Visible = false;
			}
			richTextBox1->Text = gcnew String(result2.c_str());
			

			//listView1->Groups->Insert(1, gcnew String(result2.c_str()));
			

			
			//Task::Type checkType = (toPrint).getTaskType();
			//string CommandDisplay::printTaskToUser(Task toPrint, int taskNumber);



			//listView1->Groups->AddRange
			/*ListViewGroup^ group1 = gcnew ListViewGroup("Group 01");
			ListViewGroup^ group2 = gcnew ListViewGroup("Group 02");
			//listView1->Groups->AddRange(new ListViewGroup[] {group1, group2});
			group1->Items->Add("lalala");*/
			

			textBox1->Clear();
		}


		if (e->KeyChar == (char)32){
			if (command == "add"){
				label4->Text = "e.g: add cs2103 from 2 may to 5 may";
			}
			//label4->Text = "e.g: lalalalala";
			//label4->ForeColor = System::Drawing::Color::FromArgb(255, 98, 48);
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
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		//usernamedisplay = TaskkyUI::

		//textBox2->Text = gcnew String(username.c_str());
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {


		int hh = Date().getHour();
		int mm = Date().getMinute();


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

		label2->Text = time;

		/*if (6 < Date().getHour() <= 13){
			label4->Text = "Good Afternoon,";
		}
		else {
			label4->Text = "Good Afternoon,";
		}*/
		


	}

	private: System::Void label4_TextChanged(System::Object^ sender, System::EventArgs^ e){

	}
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {


}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
}
};
}
