//@author A0114084N
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
#include "TaskManager.h"
#include "TaskDisplayer.h"
#include "Date.h"
#include <shellapi.h>

namespace TaskkyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	string command, result, taskdisplay, result2, result3;
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

	public: System::Windows::Forms::TextBox^  textBox1;
			



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

	


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;



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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
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
			this->textBox1->Location = System::Drawing::Point(29, 155);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(696, 30);
			this->textBox1->TabIndex = 6;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::textBox1_TextChanged_1);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &TaskkyGUI::textBox1_KeyDown);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUI::textBox1_KeyPress);
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
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->label1->Location = System::Drawing::Point(19, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(323, 58);
			this->label1->TabIndex = 14;
			this->label1->Text = L"T.A.S.K.K.Y";
			this->label1->Click += gcnew System::EventHandler(this, &TaskkyGUI::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Snow;
			this->label2->Location = System::Drawing::Point(81, 58);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(179, 78);
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
			this->label4->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(23, 187);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 15);
			this->label4->TabIndex = 16;
			this->label4->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::label4_TextChanged);
			this->label4->Click += gcnew System::EventHandler(this, &TaskkyGUI::label4_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(26, 139);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 13);
			this->label6->TabIndex = 18;
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3, this->columnHeader4
			});
			this->listView1->Location = System::Drawing::Point(29, 221);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(696, 307);
			this->listView1->TabIndex = 19;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &TaskkyGUI::listView1_SelectedIndexChanged_1);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"No";
			this->columnHeader1->Width = 30;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"StartTime";
			this->columnHeader2->Width = 182;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"EndTime";
			this->columnHeader3->Width = 161;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"TaskDetails";
			this->columnHeader4->Width = 274;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(489, 101);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(203, 39);
			this->label5->TabIndex = 20;
			this->label5->Text = L"Urgent Task!";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label7
			// 
			this->label7->BackColor = System::Drawing::Color::White;
			this->label7->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::Black;
			this->label7->Location = System::Drawing::Point(465, 101);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(28, 39);
			this->label7->TabIndex = 21;
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label7->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::label7_TextChanged);
			this->label7->Click += gcnew System::EventHandler(this, &TaskkyGUI::label7_Click);
			// 
			// label8
			// 
			this->label8->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(489, 62);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(203, 39);
			this->label8->TabIndex = 22;
			this->label8->Text = L"Due Today!";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label9
			// 
			this->label9->BackColor = System::Drawing::Color::White;
			this->label9->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::Black;
			this->label9->Location = System::Drawing::Point(465, 62);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(28, 39);
			this->label9->TabIndex = 23;
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(489, 25);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(203, 39);
			this->label10->TabIndex = 24;
			this->label10->Text = L"Overdue Task";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label11
			// 
			this->label11->BackColor = System::Drawing::Color::White;
			this->label11->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::Black;
			this->label11->Location = System::Drawing::Point(465, 25);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(28, 39);
			this->label11->TabIndex = 25;
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(682, 196);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(29, 13);
			this->label12->TabIndex = 26;
			this->label12->Text = L"Hide";
			this->label12->Click += gcnew System::EventHandler(this, &TaskkyGUI::label12_Click);
			this->label12->DoubleClick += gcnew System::EventHandler(this, &TaskkyGUI::label12_DoubleClick);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(633, 196);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(41, 13);
			this->label13->TabIndex = 27;
			this->label13->Text = L"Unhide";
			this->label13->Click += gcnew System::EventHandler(this, &TaskkyGUI::label13_Click);
			// 
			// TaskkyGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(758, 556);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox1);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"TaskkyGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TaskkyGUI";
			this->Load += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUI::TaskkyGUI_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TaskkyGUIContent_Load(System::Object^  sender, System::EventArgs^  e) {
		
	}

	public: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}

	public: System::Windows::Forms::ListViewItem^ addNewItem(int taskNumber, 
		string startDate, string endDate, string taskDetails, int taskPriority,
		bool taskMarked) {
		
		ListViewItem^ newItem;

		//adding first item of the row
		newItem = gcnew ListViewItem(Convert::ToString(taskNumber));

		//adding second, third and forth item of the row
		newItem->SubItems->Add(gcnew String(startDate.c_str()));
		newItem->SubItems->Add(gcnew String(endDate.c_str()));
		newItem->SubItems->Add(gcnew String(taskDetails.c_str()));
		newItem->SubItems->Add(Convert::ToString(taskPriority));

		if (taskMarked){

			newItem->ForeColor = Color::DarkGray;
		}

		else{

			if (taskPriority == Task::HIGH){

				newItem->ForeColor = Color::DarkRed;

			}

		}

		return newItem;
	}




	public: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		//When Enter is pressed
		if (e->KeyChar == (char)13){

			//get data from the textbox

			Controller* controllerInstance = Controller::getInstance();

			result = controllerInstance->processUserInput(command);

			label6->Text = gcnew String(result.c_str());
			if (command == "display"){
				label6->Visible = false;
			}

			listView1->Items->Clear();


			if (controllerInstance->getIsSearchCommand()){

				vector<int>* taskIndices = controllerInstance->getTaskIndices();

				vector<Task>* allCurrentTasks = TaskManager::getAllCurrentTasks();

				for (int i = 0; i != taskIndices->size(); i++){

					int index = (*taskIndices)[i];

					Task task = (*allCurrentTasks)[index - 1];

					ListViewItem^ newEntry;

					if (task.getTaskType() == Task::FLOATING){

						ListViewItem^ newEntry = addNewItem(index, "--------",
							"--------", task.getTaskDetails(),
							task.getTaskPriority(), task.getTaskMarked());

						array<ListViewItem^>^FloatingTasks = { newEntry };
						listView1->Items->AddRange(FloatingTasks);

					}

					else if (task.getTaskType() == Task::DEADLINE){
						ListViewItem^ newEntry = addNewItem(index,
							task.getTaskDeadline()->parseDateToDisplay(),
							"--------", task.getTaskDetails(),
							task.getTaskPriority(), task.getTaskMarked());

						array<ListViewItem^>^DeadlineTasks = { newEntry };
						listView1->Items->AddRange(DeadlineTasks);

					}

					else{

						ListViewItem^ newEntry = addNewItem(index,
							task.getTaskStartTime()->parseDateToDisplay(),
							task.getTaskEndTime()->parseDateToDisplay(),
							task.getTaskDetails(), task.getTaskPriority(),
							task.getTaskMarked());

						array<ListViewItem^>^TimedTasks = { newEntry };
						listView1->Items->AddRange(TimedTasks);
					}
				}
				textBox1->Clear();
			}

			else{

				TaskManager *taskManager = TaskManager::getInstance();
				int taskNumber = 0;
				int taskUrgent = 0;
				int taskDueToday = 0;
				int taskOverdue = 0;

				//adding all current timed tasks

				vector<Task> *allTimedTasks;
				allTimedTasks = taskManager->getAllTimedTasks();

				for (int i = 0; i != allTimedTasks->size(); i++){

					Task task = (*allTimedTasks)[i];

					if (task.getTaskType() == Task::TIMED)

					{
						if (task.getTaskPriority() == Task::HIGH){
							taskUrgent += 1;
						}

						//setting new parameters to add next task

						taskNumber += 1;
						string startDate = task.getTaskStartTime()->toString();
						string endDate = task.getTaskEndTime()->toString();
						string taskDetails = task.getTaskDetails();
						int taskPriority = task.getTaskPriority();
						bool markedTask = {};

						ListViewItem^ newEntry = addNewItem(taskNumber,
							startDate, endDate, taskDetails, taskPriority, markedTask);

						array<ListViewItem^>^TimedTasks = { newEntry };
						listView1->Items->AddRange(TimedTasks);
					}


					if (task.getTaskType() == Task::DEADLINE)

					{
						if (task.getTaskPriority() == Task::HIGH){
							taskUrgent += 1;
						}

						//setting new parameters to add next task

						taskNumber += 1;
						string startDate = task.getTaskDeadline()->toString();
						string endDate = "----------";
						string taskDetails = task.getTaskDetails();
						int taskPriority = task.getTaskPriority();
						bool markedTask = {};

						if (task.getTaskDeadline()->sameDate(Date::Date())){

							taskDueToday += 1;
						}

						if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())<0){
							
							taskOverdue += 1;
						}

						//}

						ListViewItem^ newEntry = addNewItem(taskNumber,
							startDate, endDate, taskDetails, taskPriority, markedTask);


						array<ListViewItem^>^TimedTaskswithDeadline = { newEntry };
						listView1->Items->AddRange(TimedTaskswithDeadline);

						if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())<0){

						newEntry->ForeColor = Color::DarkGoldenrod;
						}
					}


				}

				//adding all current floating tasks

				vector<Task> *allFloatingTasks;
				allFloatingTasks = taskManager->getAllFloatingTasks();

				for (int i = 0; i != allFloatingTasks->size(); i++){
					Task task = (*allFloatingTasks)[i];

					if (task.getTaskPriority() == Task::HIGH){
						taskUrgent += 1;
					}


					//setting new parameters to add next task

					taskNumber += 1;
					string startDate = "----------";
					string endDate = "----------";
					string taskDetails = task.getTaskDetails();
					int taskPriority = task.getTaskPriority();
					bool markedTask = {};


					ListViewItem^ newEntry = addNewItem(taskNumber,
						startDate, endDate, taskDetails, taskPriority, markedTask);

					array<ListViewItem^>^FloatingTasks = { newEntry };
					listView1->Items->AddRange(FloatingTasks);

				}

				//adding all marked timed task
				vector<Task> *allMarkedTimedTask;
				allMarkedTimedTask = taskManager->getAllMarkedTimedTasks();


				for (int i = 0; i != allMarkedTimedTask->size(); i++){
					Task task = (*allMarkedTimedTask)[i];

					//set type

					if (task.getTaskType() == Task::TIMED){

						//setting new parameters to add next task

						taskNumber += 1;
						string startDate = task.getTaskStartTime()->toString();
						string endDate = task.getTaskEndTime()->toString();
						string taskDetails = task.getTaskDetails();
						int TaskPriority;
						bool markedTask = 1;


						ListViewItem^ newEntry = addNewItem(taskNumber,
							startDate, endDate, taskDetails, TaskPriority, markedTask);


						array<ListViewItem^>^MarkedTimedTasks = { newEntry };
						listView1->Items->AddRange(MarkedTimedTasks);
					}

					if (task.getTaskType() == Task::DEADLINE){

						//setting new parameters to add next task
						taskNumber += 1;
						string startDate = task.getTaskDeadline()->toString();
						string endDate = "";
						string taskDetails = task.getTaskDetails();
						int TaskPriority;
						bool markedTask = 1;


						ListViewItem^ newEntry = addNewItem(taskNumber,
							startDate, endDate, taskDetails, TaskPriority, markedTask);


						array<ListViewItem^>^MarkedTimedTasksWithDeadline = { newEntry };
						listView1->Items->AddRange(MarkedTimedTasksWithDeadline);

					}

				}

				//adding all marked floating task

				vector<Task> *allMarkedFloatingTask;
				allMarkedFloatingTask = taskManager->getAllMarkedFloatingTasks();


				for (int i = 0; i != allMarkedFloatingTask->size(); i++){

					//setting new parameters to add next task
					Task task = (*allMarkedFloatingTask)[i];
					taskNumber += 1;
					string startDate = "";
					string endDate = "";
					string taskDetails = task.getTaskDetails();
					int TaskPriority;
					bool markedTask = 1;


					ListViewItem^ newEntry = addNewItem(taskNumber,
						startDate, endDate, taskDetails, TaskPriority, markedTask);


					array<ListViewItem^>^MarkedFloatingTasks = { newEntry };
					listView1->Items->AddRange(MarkedFloatingTasks);

				}

				label7->Text = Convert::ToString(taskUrgent);
				label9->Text = Convert::ToString(taskDueToday);
				label11->Text = Convert::ToString(taskOverdue);

				textBox1->Clear();

			}

		}

		label4->Text = "e.g: add, delete, update, search, mark, unmark, undo, checkfilelocation, changefilelocation, help";


		label4->Text = gcnew String(SuggestionBuilder::suggestUserInput(command).c_str());

		/*
		if (e->KeyChar == (char)32){
				if (command == "add"){
					label4->Text = "e.g: add cs2103 from 2 may 18:00 to 5 may 20:00 #high";
				}
				if (command == "update"){
					label4->Text = "e.g: update [#oftask] [categories: deadline/priority]";
				}
				if (command == "delete"){
					label4->Text = "e.g: delete [#oftask]";
				}
				if (command == "search"){
					label4->Text = "e.g: search [keywords]";
				}
<<<<<<< HEAD
		}
=======
		}*/

		
		


		//listView1->Groups->Add(gcnew ListViewGroup("test"));

		
		//listView1->Items->Add(gcnew String(result2.c_str()));
		
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
private: System::Void listView1_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void label7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void TaskkyGUI_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	
	
		
}
private: System::Void label12_Click(System::Object^  sender, System::EventArgs^  e) {
	listView1->Items->Clear();


	TaskManager *taskManager = TaskManager::getInstance();
	int taskNumber = 0;
	int taskUrgent = 0;
	int taskDueToday = 0;
	int taskOverdue = 0;

	//adding all current timed tasks
	vector<Task> *allTimedTasks;
	allTimedTasks = taskManager->getAllTimedTasks();

	for (int i = 0; i != allTimedTasks->size(); i++){
		Task task = (*allTimedTasks)[i];
		//check here


		if (task.getTaskType() == Task::TIMED)

		{
			if (task.getTaskPriority() == Task::HIGH){
				taskUrgent += 1;
			}

			//setting new parameters to add next task

			taskNumber += 1;
			string startDate = task.getTaskStartTime()->toString();
			string endDate = task.getTaskEndTime()->toString();

			string taskDetails = task.getTaskDetails();

			int taskPriority = task.getTaskPriority();


			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row


			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(Convert::ToString(taskPriority));


			if (task.getTaskPriority() == Task::HIGH)
			{
				defaultEntry->ForeColor = Color::DarkRed;
			}



			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);



			//else{
			//defaultEntry->ForeColor = Color::White;
			//}
		}


		if (task.getTaskType() == Task::DEADLINE)

		{
			if (task.getTaskPriority() == Task::HIGH){
				taskUrgent += 1;
			}

			//setting new parameters to add next task

			taskNumber += 1;
			string startDate = task.getTaskDeadline()->toString();
			string endDate = "----------";


			if (task.getTaskDeadline()->sameDate(Date::Date())){
				taskDueToday += 1;
			}

			//if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())){

			//	taskOverdue += 1;
			//}


			//}

			string taskDetails = task.getTaskDetails();
			int taskPriority = task.getTaskPriority();
			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row


			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(Convert::ToString(taskPriority));

			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);
			if (task.getTaskPriority() == Task::HIGH)
			{

				defaultEntry->ForeColor = Color::DarkRed;
			}
			//if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())){

			//defaultEntry->ForeColor = Color::DarkGoldenrod;
			//}
		}


	}



	//adding all current floating tasks
	vector<Task> *allFloatingTasks;
	allFloatingTasks = taskManager->getAllFloatingTasks();

	for (int i = 0; i != allFloatingTasks->size(); i++){
		Task task = (*allFloatingTasks)[i];

		if (task.getTaskPriority() == Task::HIGH){
			taskUrgent += 1;
		}


		//setting new parameters to add next task

		taskNumber += 1;
		string startDate = "----------";
		string endDate = "----------";
		string taskDetails = task.getTaskDetails();
		int taskPriority = task.getTaskPriority();


		ListViewItem^ defaultEntry;

		//adding first item of the row
		defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

		//adding second, third and forth item of the row
		defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
		defaultEntry->SubItems->Add(Convert::ToString(taskPriority));

		array<ListViewItem^>^temp1 = { defaultEntry };
		listView1->Items->AddRange(temp1);
		if (task.getTaskPriority() == Task::HIGH)
		{

			defaultEntry->ForeColor = Color::DarkRed;
		}

	}
}
private: System::Void label13_Click(System::Object^  sender, System::EventArgs^  e) {
		
	System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

}
private: System::Void label12_DoubleClick(System::Object^  sender, System::EventArgs^  e) {

	System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	/*listView1->Items->Clear();

	TaskManager *taskManager = TaskManager::getInstance();
	int taskNumber = 0;
	int taskUrgent = 0;
	int taskDueToday = 0;
	int taskOverdue = 0;

	//adding all current timed tasks
	vector<Task> *allTimedTasks;
	allTimedTasks = taskManager->getAllTimedTasks();

	for (int i = 0; i != allTimedTasks->size(); i++){
		Task task = (*allTimedTasks)[i];
		//check here


		if (task.getTaskType() == Task::TIMED)

		{
			if (task.getTaskPriority() == Task::HIGH){
				taskUrgent += 1;
			}

			//setting new parameters to add next task

			taskNumber += 1;
			string startDate = task.getTaskStartTime()->toString();
			string endDate = task.getTaskEndTime()->toString();

			string taskDetails = task.getTaskDetails();

			int taskPriority = task.getTaskPriority();


			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row


			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(Convert::ToString(taskPriority));


			if (task.getTaskPriority() == Task::HIGH)
			{
				defaultEntry->ForeColor = Color::DarkRed;
			}



			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);



			//else{
			//defaultEntry->ForeColor = Color::White;
			//}
		}


		if (task.getTaskType() == Task::DEADLINE)

		{
			if (task.getTaskPriority() == Task::HIGH){
				taskUrgent += 1;
			}

			//setting new parameters to add next task

			taskNumber += 1;
			string startDate = task.getTaskDeadline()->toString();
			string endDate = "----------";


			if (task.getTaskDeadline()->sameDate(Date::Date())){
				taskDueToday += 1;
			}

			//if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())){

			//	taskOverdue += 1;
			//}


			//}

			string taskDetails = task.getTaskDetails();
			int taskPriority = task.getTaskPriority();
			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row


			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(Convert::ToString(taskPriority));

			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);
			if (task.getTaskPriority() == Task::HIGH)
			{

				defaultEntry->ForeColor = Color::DarkRed;
			}
			//if ((Date::Date()).isEarlierThan(*task.getTaskDeadline())){

			//defaultEntry->ForeColor = Color::DarkGoldenrod;
			//}
		}


	}



	//adding all current floating tasks
	vector<Task> *allFloatingTasks;
	allFloatingTasks = taskManager->getAllFloatingTasks();

	for (int i = 0; i != allFloatingTasks->size(); i++){
		Task task = (*allFloatingTasks)[i];

		if (task.getTaskPriority() == Task::HIGH){
			taskUrgent += 1;
		}


		//setting new parameters to add next task

		taskNumber += 1;
		string startDate = "----------";
		string endDate = "----------";
		string taskDetails = task.getTaskDetails();
		int taskPriority = task.getTaskPriority();


		ListViewItem^ defaultEntry;

		//adding first item of the row
		defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

		//adding second, third and forth item of the row
		defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
		defaultEntry->SubItems->Add(Convert::ToString(taskPriority));

		array<ListViewItem^>^temp1 = { defaultEntry };
		listView1->Items->AddRange(temp1);
		if (task.getTaskPriority() == Task::HIGH)
		{

			defaultEntry->ForeColor = Color::DarkRed;
		}

	}

	//adding all marked timed task
	vector<Task> *allMarkedTimedTask;
	allMarkedTimedTask = taskManager->getAllMarkedTimedTasks();


	for (int i = 0; i != allMarkedTimedTask->size(); i++){
		Task task = (*allMarkedTimedTask)[i];

		//set type

		if (task.getTaskType() == Task::TIMED){

			//setting new parameters to add next task

			taskNumber += 1;
			string startDate = task.getTaskStartTime()->toString();
			string endDate = task.getTaskEndTime()->toString();
			string taskDetails = task.getTaskDetails();
			string marked;
			if (task.getTaskMarked()){
				marked = "YES";
			}
			//string marked = task.getTaskMarked()->toString();


			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row
			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(gcnew String(marked.c_str()));

			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);
			defaultEntry->ForeColor = Color::DarkGray;
		}


		if (task.getTaskType() == Task::DEADLINE){

			//setting new parameters to add next task
			taskNumber += 1;
			string startDate = task.getTaskDeadline()->toString();
			string endDate = "";
			string taskDetails = task.getTaskDetails();
			string marked;
			if (task.getTaskMarked()){
				marked = "YES";
			}
			//string marked = task.getTaskMarked()->toString();


			ListViewItem^ defaultEntry;

			//adding first item of the row
			defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

			//adding second, third and forth item of the row
			defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
			defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
			defaultEntry->SubItems->Add(gcnew String(marked.c_str()));

			array<ListViewItem^>^temp1 = { defaultEntry };
			listView1->Items->AddRange(temp1);
			defaultEntry->ForeColor = Color::DarkGray;

		}

	}

	//adding all marked floating task

	vector<Task> *allMarkedFloatingTask;
	allMarkedFloatingTask = taskManager->getAllMarkedFloatingTasks();


	for (int i = 0; i != allMarkedFloatingTask->size(); i++){

		//setting new parameters to add next task
		Task task = (*allMarkedFloatingTask)[i];
		taskNumber += 1;
		string startDate = "";
		string endDate = "";
		string taskDetails = task.getTaskDetails();
		string marked;
		if (task.getTaskMarked()){
			marked = "YES";
		}
		//string marked = task.getTaskMarked()->toString();


		ListViewItem^ defaultEntry;

		//adding first item of the row
		defaultEntry = gcnew ListViewItem(Convert::ToString(taskNumber));

		//adding second, third and forth item of the row
		defaultEntry->SubItems->Add(gcnew String(startDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(endDate.c_str()));
		defaultEntry->SubItems->Add(gcnew String(taskDetails.c_str()));
		defaultEntry->SubItems->Add(gcnew String(marked.c_str()));
		defaultEntry->ForeColor = Color::DarkGray;

		array<ListViewItem^>^temp1 = { defaultEntry };
		listView1->Items->AddRange(temp1);

	}*/
}
private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::PageDown){
		listView1->Focus();
		SendKeys::SendWait("{PGDN}");
		textBox1->Focus();
	}
	else if (e->KeyCode == Keys::PageUp){
		listView1->Focus();
		SendKeys::SendWait("{PGUP}");
		textBox1->Focus();
	}

	if (e->KeyCode == Keys::F1){
		ShellExecuteA(NULL, "open", "..\\help.pdf", NULL, NULL, 0);
	}
}
};
}
