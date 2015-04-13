#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(TaskManagerTest){
	public:
		TEST_METHOD(ConstructorTest)
		{
			//checking both instances are the same, singleton class
			TaskManager* instance1 = TaskManager::getInstance();
			TaskManager* instance2 = TaskManager::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}
		TEST_METHOD(AddTest)
		{
			TaskManager* instance = TaskManager::getInstance();
			Task newFloating = Task::Task("Floating", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task newFloating2 = Task::Task("LaterFLoating", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			
			//testing the add function
			Assert::AreEqual<int>(0, instance->getNumberOfTasks());
			instance->addTask(newFloating2);
			instance->addTask(newFloating);
			//Checking if tasks are actually added in alphabetical order
			Assert::AreEqual<string>(newFloating.getTaskDetails(),instance->getTask(1).getTaskDetails());
			Assert::AreEqual<string>(newFloating2.getTaskDetails(), instance->getTask(2).getTaskDetails());
			Assert::AreEqual<int>(2, instance->getNumberOfTasks());

			//testing the remove function
			instance->removeTask(1);
			Assert::AreEqual<int>(1, instance->getNumberOfTasks());
			Assert::AreEqual<string>(newFloating2.getTaskDetails(), instance->getTask(1).getTaskDetails());



		}
	};
}