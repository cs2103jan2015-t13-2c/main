#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(SystemTest){
	public:
		TEST_METHOD(SystemTest1){
			TaskManager* instance = TaskManager::getInstance();
			vector<Task>* allCurrentTasks = TaskManager::getAllCurrentTasks();

			//making sure task has been added to the back of the task vector
			Assert::AreEqual<bool>(true, Controller::processUserInput("add hello") == "Task has been added!");
		} TEST_METHOD(SystemTest2){
			//add tasks by today test

			Assert::AreEqual<bool>(true, Controller::processUserInput("delete 1") == "Deleted Task #1");
			Assert::AreEqual<bool>(true, Controller::processUserInput("undo") == "Action has been undone!");
		}
	};
}