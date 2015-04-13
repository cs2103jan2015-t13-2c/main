//@author A0094024M
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(SystemTest){
	public:
		TEST_METHOD(SystemTest1AddFloatingTask){
			//Test Case: code can "add a FLOATING TASK"
			clearTasks();
			
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_floating_task_1"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("test_add_floating_task_1 ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest2AddDeadline){
			//Test Case: code can "add a Deadline"
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_deadline_1 by 7 june 10am"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("test_add_deadline_1 ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::IsTrue(Date(2015,5,7,10,0).sameDate(*(iter->getTaskDeadline())));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest3AddTimedTask){
			//Test Case: code can "add a Timed Task"
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_timed_task_1 from today to tomorrow"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("test_add_timed_task_1 ", iter->getTaskDetails());
			Assert::IsTrue(Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 0).sameDate(*(iter->getTaskStartTime())));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest4MarkTaskAsDone){
			//Test Case: code can mark tasks as done
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_floating_task_2"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_deadline_2 by 7 june 10am"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_add_timed_task_2 from today to tomorrow"));

			Assert::AreEqual<string>("Marked Task #2", Controller::processUserInput("mark 2"));
			Assert::AreEqual<string>("Marked Task #3", Controller::processUserInput("mark 3"));
			Assert::AreEqual<string>("Marked Task #4", Controller::processUserInput("mark 4"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter;
			for (iter = myVec.begin() + 3; iter != myVec.end(); ++iter){
				Assert::IsTrue(iter->getTaskMarked());
			}
		}
		TEST_METHOD(SystemTest5AutoSort){
			//Test Case: code automatically sort tasks in order of due date / start date, 
			//then alphabetical order based on task details
			//*NOTE*: dated tasks - floating tasks - dated tasks marked - floating tasks marked
			clearTasks();
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_1_floating"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_2_floating"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_1_deadline by 25 dec"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_2_deadline by this saturday"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_1_timed from today to tomorrow"));
			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add test_2_timed from 27 nov to 29 dec"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("test_1_timed ", iter->getTaskDetails());
			++iter;
			Assert::AreEqual<string>("test_2_deadline ", iter->getTaskDetails());
			++iter;
			Assert::AreEqual<string>("test_2_timed ", iter->getTaskDetails());
			++iter;
			Assert::AreEqual<string>("test_1_deadline ", iter->getTaskDetails());
			++iter;
			Assert::AreEqual<string>("test_1_floating ", iter->getTaskDetails());
			++iter;
			Assert::AreEqual<string>("test_2_floating ", iter->getTaskDetails());
			++iter;
		}
		TEST_METHOD(SystemTest6UpdateDetails){
			//Test Case: code can update task details
			clearTasks();

			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add old name"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("old name ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

			Assert::AreEqual<string>("Updated Task #1!", Controller::processUserInput("update 1 details new name"));
			myVec = *(TaskManager::getAllCurrentTasks());
			iter = myVec.begin();
			Assert::AreEqual<string>("new name ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest7UpdateDeadline){
			//Test Case: code can update task deadline
			clearTasks();

			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add deadline by today"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("deadline ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::IsTrue(iter->getTaskDeadline()->sameDate(*(today())));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

			Assert::AreEqual<string>("Updated Task #1!", Controller::processUserInput("update 1 deadline tomorrow"));
			myVec = *(TaskManager::getAllCurrentTasks());
			iter = myVec.begin();
			Assert::AreEqual<string>("deadline ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::IsTrue(iter->getTaskDeadline()->sameDate(*(tomorrow())));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest9UpdateEndTime){
			//Test Case: code can update task end time
			clearTasks();

			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add timed from today to 25 dec"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("timed ", iter->getTaskDetails());
			Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
			Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(),11,25,12,0)));
			Assert::IsTrue(iter->getTaskDeadline() == nullptr);
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

			Assert::AreEqual<string>("Updated Task #1!", Controller::processUserInput("update 1 endtime tomorrow"));
			myVec = *(TaskManager::getAllCurrentTasks());
			iter = myVec.begin();
			Assert::AreEqual<string>("timed ", iter->getTaskDetails());
			Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
			Assert::IsTrue(iter->getTaskEndTime()->sameDate(*(tomorrow())));
			Assert::IsTrue(iter->getTaskDeadline() == nullptr);
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest8UpdateStartTime){
			//Test Case: code can update task start time
			clearTasks();

			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add timed from today to 25 dec"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("timed ", iter->getTaskDetails());
			Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
			Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(), 11, 25, 12, 0)));
			Assert::IsTrue(iter->getTaskDeadline() == nullptr);
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

			Assert::AreEqual<string>("Updated Task #1!", Controller::processUserInput("update 1 starttime tomorrow"));
			myVec = *(TaskManager::getAllCurrentTasks());
			iter = myVec.begin();
			Assert::AreEqual<string>("timed ", iter->getTaskDetails());
			Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(tomorrow()))));
			Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(), 11, 25, 12, 0)));
			Assert::IsTrue(iter->getTaskDeadline() == nullptr);
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
		}
		TEST_METHOD(SystemTest10UpdatePriority){
			//Test Case: code can update task priority
			clearTasks();

			Assert::AreEqual<string>("Task has been added!", Controller::processUserInput("add task"));

			vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
			vector<Task>::iterator iter = myVec.begin();
			Assert::AreEqual<string>("task ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

			Assert::AreEqual<string>("Updated Task #1!", Controller::processUserInput("update 1 priority high"));
			myVec = *(TaskManager::getAllCurrentTasks());
			iter = myVec.begin();
			Assert::AreEqual<string>("task ", iter->getTaskDetails());
			Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
			Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
			Assert::IsTrue(iter->getTaskPriority() == Task::Priority::HIGH);
		}
		TEST_METHOD(SystemTest11Delete){
			//Test Case: code can delete added task
			clearTasks();
			addStandardTasks();
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deleted Task #1", Controller::processUserInput("delete 1"));
			Assert::AreEqual<int>(3, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deleted Task #1", Controller::processUserInput("delete 1"));
			Assert::AreEqual<int>(2, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deleted Task #1", Controller::processUserInput("delete 1"));
			Assert::AreEqual<int>(1, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deleted Task #1", Controller::processUserInput("delete 1"));
			Assert::AreEqual<int>(0, TaskManager::getAllCurrentTasks()->size());
		}
		TEST_METHOD(SystemTest12SimpleSearch){
			//Test Case: code can do a simple keyword search
			clearTasks();
			addStandardTasks();
			Assert::AreEqual<string>("There are 4 tasks found.", Controller::processUserInput("search Task"));
		}
		TEST_METHOD(SystemTest13SpecifySaveLocation){
			//Test Case: code can specify a specific folder as the data storage location
			//NOTE: THIS TEST WILL FAIL WHEN THIS CODE IS RUN ON A DIFFERENT COMPUTER.
			//      ADJUST LOCATION ACCORDINGLY
			clearTasks();
			addStandardTasks();
<<<<<<< HEAD
			//Assert::AreEqual<string>("File location changed successfully", Controller::processUserInput("changefileloc C:\\Users\\Adi!\\Desktop"));
=======
			Assert::AreEqual<string>("File location changed successfully", Controller::processUserInput("changefileloc C:\\Users\\Adi!\\Desktop"));
>>>>>>> origin/master
		}
	private:
		void clearTasks(){
			while (!TaskManager::getAllCurrentTasks()->empty()){
				TaskManager::removeTask(1);
			}
		}

		Date* today(){
			return new Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 0);
		}

		Date* tomorrow(){
			return new Date(Date().getYear(), Date().getMonth(), Date().getDay() + 1, 12, 0);
		}
		void addStandardTasks(){
			TaskManager::addTask(Task("Marked Task - will be indexed as 4", NULL, NULL, NULL,
				Task::Priority::HIGH));
			TaskManager::markTask(1);
			TaskManager::addTask(Task("Normal Floating Task - will be indexed as 3", NULL, NULL, NULL,
				Task::Priority::NORMAL));
			TaskManager::addTask(Task("Timed Task - will be indexed as 2", new Date(2015, 11, 25, 12, 0),
				new Date(2016, 0, 1, 10, 0), NULL, Task::Priority::HIGH));
			TaskManager::addTask(Task("Deadline Task - will be indexed as 1", NULL, NULL,
				new Date(2015, 9, 19, 10, 0), Task::Priority::NORMAL));
		}
	};
}