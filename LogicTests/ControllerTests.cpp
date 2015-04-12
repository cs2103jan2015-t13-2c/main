#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(ControllerTests)
	{
	public:
		
		TEST_METHOD(ControllerTest1)
		{
			//checking both instances are the same, singleton class
			Controller* instance1 = Controller::getInstance();
			Controller* instance2 = Controller::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}

	};
}