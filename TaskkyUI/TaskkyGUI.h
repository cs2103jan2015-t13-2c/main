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

	public ref class TaskkyGUI : public System::Windows::Forms::Form
	{
	public:
		TaskkyGUI()
		{
			InitializeComponent();

			Controller::initializeComponent();

			vector<Task>* allCurrentTasks = TaskManager::getAllCurrentTasks();

			for (int i = 0; i != allCurrentTasks->size(); i++){

				Task task = (*allCurrentTasks)[i];

				ListViewItem^ newEntry;

				if (task.getTaskType() == Task::FLOATING){

					ListViewItem^ newEntry = addNewItem(i + 1, "--------",
						"--------", task.getTaskDetails(),
						task.getTaskPriority(), task.getTaskMarked());

					array<ListViewItem^>^FloatingTasks = { newEntry };
					listView1->Items->AddRange(FloatingTasks);

				}

				else if (task.getTaskType() == Task::DEADLINE){
					ListViewItem^ newEntry = addNewItem(i + 1,
						task.getTaskDeadline()->toString(),
						"--------", task.getTaskDetails(),
						task.getTaskPriority(), task.getTaskMarked());

					array<ListViewItem^>^DeadlineTasks = { newEntry };
					listView1->Items->AddRange(DeadlineTasks);

				}

				else{

					ListViewItem^ newEntry = addNewItem(i + 1,
						task.getTaskStartTime()->toString(),
						task.getTaskEndTime()->toString(),
						task.getTaskDetails(), task.getTaskPriority(),
						task.getTaskMarked());

					array<ListViewItem^>^TimedTasks = { newEntry };
					listView1->Items->AddRange(TimedTasks);
				}
			}

		}
	private: System::Windows::Forms::Label^  label12;

	public: System::Windows::Forms::TextBox^  UserInput;
	private:
	public:

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





	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  CurrentTime;

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  SuggestionBuilder;
	private: System::Windows::Forms::Label^  FeedbackUserInput;



	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  TaskNumber;
	private: System::Windows::Forms::ColumnHeader^  StartTime;
	private: System::Windows::Forms::ColumnHeader^  EndTime;
	private: System::Windows::Forms::ColumnHeader^  TaskDetails;




	private: System::Windows::Forms::Label^  UrgentTask;

	private: System::Windows::Forms::Label^  NumberOfUrgentTask;
	private: System::Windows::Forms::Label^  DueToday;


	private: System::Windows::Forms::Label^  NumberOfTaskDueToday;
	private: System::Windows::Forms::Label^  OverdueTask;


	private: System::Windows::Forms::Label^  NumberOfOverdueTask;






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
			this->UserInput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->CurrentTime = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuggestionBuilder = (gcnew System::Windows::Forms::Label());
			this->FeedbackUserInput = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->TaskNumber = (gcnew System::Windows::Forms::ColumnHeader());
			this->StartTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->EndTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->TaskDetails = (gcnew System::Windows::Forms::ColumnHeader());
			this->UrgentTask = (gcnew System::Windows::Forms::Label());
			this->NumberOfUrgentTask = (gcnew System::Windows::Forms::Label());
			this->DueToday = (gcnew System::Windows::Forms::Label());
			this->NumberOfTaskDueToday = (gcnew System::Windows::Forms::Label());
			this->OverdueTask = (gcnew System::Windows::Forms::Label());
			this->NumberOfOverdueTask = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// UserInput
			// 
			this->UserInput->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(3) { L"add", L"delete", L"display" });
			this->UserInput->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->UserInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->UserInput->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->UserInput->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UserInput->ForeColor = System::Drawing::Color::White;
			this->UserInput->Location = System::Drawing::Point(26, 155);
			this->UserInput->Margin = System::Windows::Forms::Padding(2);
			this->UserInput->Name = L"UserInput";
			this->UserInput->Size = System::Drawing::Size(687, 30);
			this->UserInput->TabIndex = 6;
			this->UserInput->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::UserInputTextBox_TextChanged_1);
			this->UserInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &TaskkyGUI::UserInputTextBox_KeyDown);
			this->UserInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TaskkyGUI::UserInputTextBox_KeyPress);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", 39.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->label1->Location = System::Drawing::Point(51, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(366, 58);
			this->label1->TabIndex = 14;
			this->label1->Text = L"T.A.S.K.K.Y";
			this->label1->Click += gcnew System::EventHandler(this, &TaskkyGUI::label1_Click);
			// 
			// CurrentTime
			// 
			this->CurrentTime->AutoSize = true;
			this->CurrentTime->BackColor = System::Drawing::Color::Transparent;
			this->CurrentTime->Font = (gcnew System::Drawing::Font(L"Calibri", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CurrentTime->ForeColor = System::Drawing::Color::Snow;
			this->CurrentTime->Location = System::Drawing::Point(130, 51);
			this->CurrentTime->Name = L"CurrentTime";
			this->CurrentTime->Size = System::Drawing::Size(178, 78);
			this->CurrentTime->TabIndex = 15;
			this->CurrentTime->Text = L"00:00";
			this->CurrentTime->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			this->CurrentTime->Click += gcnew System::EventHandler(this, &TaskkyGUI::label2_Click_1);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &TaskkyGUI::timer1_Tick);
			// 
			// SuggestionBuilder
			// 
			this->SuggestionBuilder->AutoSize = true;
			this->SuggestionBuilder->BackColor = System::Drawing::Color::Transparent;
			this->SuggestionBuilder->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SuggestionBuilder->ForeColor = System::Drawing::Color::White;
			this->SuggestionBuilder->Location = System::Drawing::Point(26, 187);
			this->SuggestionBuilder->Name = L"SuggestionBuilder";
			this->SuggestionBuilder->Size = System::Drawing::Size(0, 15);
			this->SuggestionBuilder->TabIndex = 16;
			this->SuggestionBuilder->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::label4_TextChanged);
			this->SuggestionBuilder->Click += gcnew System::EventHandler(this, &TaskkyGUI::label4_Click);
			// 
			// FeedbackUserInput
			// 
			this->FeedbackUserInput->AutoSize = true;
			this->FeedbackUserInput->BackColor = System::Drawing::Color::Transparent;
			this->FeedbackUserInput->ForeColor = System::Drawing::Color::White;
			this->FeedbackUserInput->Location = System::Drawing::Point(26, 140);
			this->FeedbackUserInput->Name = L"FeedbackUserInput";
			this->FeedbackUserInput->Size = System::Drawing::Size(0, 13);
			this->FeedbackUserInput->TabIndex = 18;
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::Color::White;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->TaskNumber, this->StartTime,
					this->EndTime, this->TaskDetails
			});
			this->listView1->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView1->ForeColor = System::Drawing::Color::Black;
			this->listView1->Location = System::Drawing::Point(29, 209);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(684, 335);
			this->listView1->TabIndex = 19;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &TaskkyGUI::listView1_SelectedIndexChanged_1);
			// 
			// TaskNumber
			// 
			this->TaskNumber->Text = L"No";
			this->TaskNumber->Width = 33;
			// 
			// StartTime
			// 
			this->StartTime->Text = L"Start Time / Deadline";
			this->StartTime->Width = 182;
			// 
			// EndTime
			// 
			this->EndTime->Text = L"End Time";
			this->EndTime->Width = 173;
			// 
			// TaskDetails
			// 
			this->TaskDetails->Text = L"Task Details";
			this->TaskDetails->Width = 286;
			// 
			// UrgentTask
			// 
			this->UrgentTask->BackColor = System::Drawing::Color::Transparent;
			this->UrgentTask->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->UrgentTask->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UrgentTask->ForeColor = System::Drawing::Color::Red;
			this->UrgentTask->Location = System::Drawing::Point(518, 101);
			this->UrgentTask->Name = L"UrgentTask";
			this->UrgentTask->Size = System::Drawing::Size(148, 39);
			this->UrgentTask->TabIndex = 20;
			this->UrgentTask->Text = L"Urgent Task!";
			this->UrgentTask->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// NumberOfUrgentTask
			// 
			this->NumberOfUrgentTask->BackColor = System::Drawing::Color::Transparent;
			this->NumberOfUrgentTask->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NumberOfUrgentTask->ForeColor = System::Drawing::Color::White;
			this->NumberOfUrgentTask->Location = System::Drawing::Point(492, 100);
			this->NumberOfUrgentTask->Name = L"NumberOfUrgentTask";
			this->NumberOfUrgentTask->Size = System::Drawing::Size(28, 39);
			this->NumberOfUrgentTask->TabIndex = 21;
			this->NumberOfUrgentTask->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumberOfUrgentTask->TextChanged += gcnew System::EventHandler(this, &TaskkyGUI::label7_TextChanged);
			this->NumberOfUrgentTask->Click += gcnew System::EventHandler(this, &TaskkyGUI::label7_Click);
			// 
			// DueToday
			// 
			this->DueToday->BackColor = System::Drawing::Color::Transparent;
			this->DueToday->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DueToday->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->DueToday->Location = System::Drawing::Point(518, 62);
			this->DueToday->Name = L"DueToday";
			this->DueToday->Size = System::Drawing::Size(148, 39);
			this->DueToday->TabIndex = 22;
			this->DueToday->Text = L"Due Today!";
			this->DueToday->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// NumberOfTaskDueToday
			// 
			this->NumberOfTaskDueToday->BackColor = System::Drawing::Color::Transparent;
			this->NumberOfTaskDueToday->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NumberOfTaskDueToday->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->NumberOfTaskDueToday->Location = System::Drawing::Point(492, 61);
			this->NumberOfTaskDueToday->Name = L"NumberOfTaskDueToday";
			this->NumberOfTaskDueToday->Size = System::Drawing::Size(28, 39);
			this->NumberOfTaskDueToday->TabIndex = 23;
			this->NumberOfTaskDueToday->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// OverdueTask
			// 
			this->OverdueTask->BackColor = System::Drawing::Color::Transparent;
			this->OverdueTask->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OverdueTask->ForeColor = System::Drawing::Color::Gold;
			this->OverdueTask->Location = System::Drawing::Point(518, 23);
			this->OverdueTask->Name = L"OverdueTask";
			this->OverdueTask->Size = System::Drawing::Size(148, 39);
			this->OverdueTask->TabIndex = 24;
			this->OverdueTask->Text = L"Overdue Task";
			this->OverdueTask->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// NumberOfOverdueTask
			// 
			this->NumberOfOverdueTask->BackColor = System::Drawing::Color::Transparent;
			this->NumberOfOverdueTask->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NumberOfOverdueTask->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->NumberOfOverdueTask->Location = System::Drawing::Point(492, 24);
			this->NumberOfOverdueTask->Name = L"NumberOfOverdueTask";
			this->NumberOfOverdueTask->Size = System::Drawing::Size(28, 39);
			this->NumberOfOverdueTask->TabIndex = 25;
			this->NumberOfOverdueTask->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(630, 553);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(67, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Hide/Unhide";
			// 
			// TaskkyGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(735, 575);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->FeedbackUserInput);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->NumberOfOverdueTask);
			this->Controls->Add(this->OverdueTask);
			this->Controls->Add(this->NumberOfTaskDueToday);
			this->Controls->Add(this->DueToday);
			this->Controls->Add(this->NumberOfUrgentTask);
			this->Controls->Add(this->UrgentTask);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->SuggestionBuilder);
			this->Controls->Add(this->CurrentTime);
			this->Controls->Add(this->UserInput);
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

	public: System::Void UserInputTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {

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

				newItem->ForeColor = Color::Red;

			}

		}

		return newItem;
	}




	public: System::Void UserInputTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

		//When Enter is pressed

		if (e->KeyChar == (char)13){

			//get data from the textbox

			Controller* controllerInstance = Controller::getInstance();

			result = controllerInstance->processUserInput(command);

			FeedbackUserInput->Text = gcnew String(result.c_str());

			if (command == "display"){

				FeedbackUserInput->Text = "";

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
							task.getTaskDeadline()->toString(),
							"--------", task.getTaskDetails(),
							task.getTaskPriority(), task.getTaskMarked());

						array<ListViewItem^>^DeadlineTasks = { newEntry };
						listView1->Items->AddRange(DeadlineTasks);

					}

					else{

						ListViewItem^ newEntry = addNewItem(index,
							task.getTaskStartTime()->toString(),
							task.getTaskEndTime()->toString(),
							task.getTaskDetails(), task.getTaskPriority(),
							task.getTaskMarked());

						array<ListViewItem^>^TimedTasks = { newEntry };
						listView1->Items->AddRange(TimedTasks);
					}
				}
				UserInput->Clear();
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

				NumberOfUrgentTask->Text = Convert::ToString(taskUrgent);
				NumberOfTaskDueToday->Text = Convert::ToString(taskDueToday);
				NumberOfOverdueTask->Text = Convert::ToString(taskOverdue);

				UserInput->Clear();

			}

		}
	}

	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void UserInputTextBox_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
		command = msclr::interop::marshal_as< std::string >(UserInput->Text);

	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void richTextBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	public: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {



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

		CurrentTime->Text = time;


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

		System::Void UserInputTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

	}
	private: System::Void label12_DoubleClick(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void UserInputTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::PageDown){
			listView1->Focus();
			SendKeys::SendWait("{PGDN}");
			UserInput->Focus();
		}
		else if (e->KeyCode == Keys::PageUp){
			listView1->Focus();
			SendKeys::SendWait("{PGUP}");
			UserInput->Focus();
		}

		if (e->KeyCode == Keys::F1){
			ShellExecuteA(NULL, "open", "..\\help.pdf", NULL, NULL, 0);
		}
	}
	private: System::Void label2_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
