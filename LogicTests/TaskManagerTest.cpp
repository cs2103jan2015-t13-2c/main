#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(TaskManagerTest){
	public:
		TEST_METHOD(TaskManagerTest1)
		{
			//checking both instances are the same, singleton class
			TaskManager* instance1 = TaskManager::getInstance();
			TaskManager* instance2 = TaskManager::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}
	};
}