//@author A0094024M
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(SystemTest){
public:
	TEST_METHOD(SystemTest01AddFloatingTask){
		//Test Case: code can "add a FLOATING TASK"
		clearTasks();

		TaskManager::addTask(Task("test_add_floating_task_1",NULL, NULL, NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("test_add_floating_task_1", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest02AddDeadline){
		//Test Case: code can "add a Deadline"
		TaskManager::addTask(Task("test_add_deadline_1", NULL, NULL, new Date(2015, 5, 7, 10, 0), Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("test_add_deadline_1", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::IsTrue(Date(2015, 5, 7, 10, 0).sameDate(*(iter->getTaskDeadline())));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest03AddTimedTask){
		//Test Case: code can "add a Timed Task"
		TaskManager::addTask(Task("test_add_timed_task_1", new Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 0), new Date(Date().getYear(), Date().getMonth(), Date().getDay() + 1, 12, 0), NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("test_add_timed_task_1", iter->getTaskDetails());
		Assert::IsTrue(Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 0).sameDate(*(iter->getTaskStartTime())));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest04MarkTaskAsDone){
		//Test Case: code can mark tasks as done
		TaskManager::addTask(Task("test_add_floating_task_1", NULL, NULL, NULL, Task::Priority::NORMAL));
		TaskManager::addTask(Task("test_add_deadline_1", NULL, NULL, new Date(2015, 5, 7, 10, 0), Task::Priority::NORMAL));
		TaskManager::addTask(Task("test_add_timed_task_1", new Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 0), new Date(Date().getYear(), Date().getMonth(), Date().getDay() + 1, 12, 0), NULL, Task::Priority::NORMAL));

		TaskManager::markTask(2);
		TaskManager::markTask(3);
		TaskManager::markTask(4);

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter;
		for (iter = myVec.begin() + 3; iter != myVec.end(); ++iter){
			Assert::IsTrue(iter->getTaskMarked());
		}
	}
	TEST_METHOD(SystemTest05AutoSort){
		//Test Case: code automatically sort tasks in order of due date / start date, 
		//then alphabetical order based on task details
		//*NOTE*: dated tasks - floating tasks - dated tasks marked - floating tasks marked
		clearTasks();
		addStandardTasks();

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("Deadline Task - will be indexed as 1", iter->getTaskDetails());
		++iter;
		Assert::AreEqual<string>("Timed Task - will be indexed as 2", iter->getTaskDetails());
		++iter;
		Assert::AreEqual<string>("Normal Floating Task - will be indexed as 3", iter->getTaskDetails());
		++iter;
		Assert::AreEqual<string>("Marked Task - will be indexed as 4", iter->getTaskDetails());
	}
	TEST_METHOD(SystemTest06UpdateDetails){
		//Test Case: code can update task details
		clearTasks();

		TaskManager::addTask(Task("old name", NULL, NULL, NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("old name", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

		
		myVec = *(TaskManager::getAllCurrentTasks());
		iter = myVec.begin();
		iter->setTaskDetails("new name");
		Assert::AreEqual<string>("new name", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest07UpdateDeadline){
		//Test Case: code can update task deadline
		clearTasks();

		TaskManager::addTask(Task("deadline", NULL, NULL, today(), Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("deadline", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::IsTrue(iter->getTaskDeadline()->sameDate(*(today())));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

		
		myVec = *(TaskManager::getAllCurrentTasks());
		iter = myVec.begin();
		iter->setTaskDeadline(tomorrow());
		Assert::AreEqual<string>("deadline", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::IsTrue(iter->getTaskDeadline()->sameDate(*(tomorrow())));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest09UpdateEndTime){
		//Test Case: code can update task end time
		clearTasks();

		TaskManager::addTask(Task("timed", today(), new Date(Date().getYear(), 11, 25, 12, 0), NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("timed", iter->getTaskDetails());
		Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
		Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(), 11, 25, 12, 0)));
		Assert::IsTrue(iter->getTaskDeadline() == nullptr);
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

		
		myVec = *(TaskManager::getAllCurrentTasks());
		iter = myVec.begin();
		iter->setTaskEndTime(tomorrow());
		Assert::AreEqual<string>("timed", iter->getTaskDetails());
		Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
		Assert::IsTrue(iter->getTaskEndTime()->sameDate(*(tomorrow())));
		Assert::IsTrue(iter->getTaskDeadline() == nullptr);
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest08UpdateStartTime){
		//Test Case: code can update task start time
		clearTasks();

		TaskManager::addTask(Task("timed", today(), new Date(Date().getYear(), 11, 25, 12, 0), NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("timed", iter->getTaskDetails());
		Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(today()))));
		Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(), 11, 25, 12, 0)));
		Assert::IsTrue(iter->getTaskDeadline() == nullptr);
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

		
		myVec = *(TaskManager::getAllCurrentTasks());
		iter = myVec.begin();
		iter->setTaskStartTime(tomorrow());
		Assert::AreEqual<string>("timed", iter->getTaskDetails());
		Assert::IsTrue((iter->getTaskStartTime()->sameDate(*(tomorrow()))));
		Assert::IsTrue(iter->getTaskEndTime()->sameDate(Date(Date().getYear(), 11, 25, 12, 0)));
		Assert::IsTrue(iter->getTaskDeadline() == nullptr);
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);
	}
	TEST_METHOD(SystemTest10UpdatePriority){
		//Test Case: code can update task priority
		clearTasks();

		TaskManager::addTask(Task("task", NULL, NULL, NULL, Task::Priority::NORMAL));

		vector<Task> myVec = *(TaskManager::getAllCurrentTasks());
		vector<Task>::iterator iter = myVec.begin();
		Assert::AreEqual<string>("task", iter->getTaskDetails());
		Assert::AreEqual<bool>(true, (iter->getTaskStartTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskEndTime() == nullptr));
		Assert::AreEqual<bool>(true, (iter->getTaskDeadline() == nullptr));
		Assert::IsTrue(iter->getTaskPriority() == Task::Priority::NORMAL);

		
		myVec = *(TaskManager::getAllCurrentTasks());
		iter = myVec.begin();
		iter->setTaskPriority(Task::Priority::HIGH);
		Assert::AreEqual<string>("task", iter->getTaskDetails());
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
		TaskManager::removeTask(1);
		Assert::AreEqual<int>(3, TaskManager::getAllCurrentTasks()->size());
		TaskManager::removeTask(1);
		Assert::AreEqual<int>(2, TaskManager::getAllCurrentTasks()->size());
		TaskManager::removeTask(1);
		Assert::AreEqual<int>(1, TaskManager::getAllCurrentTasks()->size());
		TaskManager::removeTask(1);
		Assert::AreEqual<int>(0, TaskManager::getAllCurrentTasks()->size());
	}
	TEST_METHOD(SystemTest12SimpleSearch){
		//Test Case: code can do a simple keyword search
		clearTasks();
		addStandardTasks();
		CommandSearch a = CommandSearch("task", NULL, NULL, NULL, Task::Priority::NORMAL, "", false, false, false);
		a.execute();
		vector<int> myVec = *(a.getTasksIndices());
		Assert::AreEqual<int>(4, myVec.size());
	}
	TEST_METHOD(SystemTest13SpecifySaveLocation){
		//Test Case: code can specify a specific folder as the data storage location
		//NOTE: THIS TEST WILL FAIL WHEN THIS CODE IS RUN ON A DIFFERENT COMPUTER.
		//      ADJUST LOCATION ACCORDINGLY
		clearTasks();
		addStandardTasks();
		Assert::AreEqual<string>("File location changed successfully", Controller::processUserInput("changefileloc default"));
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