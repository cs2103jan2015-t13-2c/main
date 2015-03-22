#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
#include "Taskky.cpp"
#include "Date.cpp"
#include "TaskManager.cpp"
#include "Controller.cpp"
#include "CommandBuilder.cpp"
#include "CommandAdd.cpp"
#include "Command.cpp"
#include "CommandInvalid.cpp"
#include "CommandDisplay.cpp"
#include "Parser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{		
	TEST_CLASS(TasksTest)
	{
	public:
		
		TEST_METHOD(TaskTest)
		{
			//testing floating task
			Task newFloatingTask = Task::Task("Do Something", NULL, NULL, NULL, Task::Recurrence::NONE, Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newFloatingTask.getTaskDetails());
			//Assert::AreEqual<bool>(true, &newFloatingTask.getTaskStartTime() == NULL);
			//Assert::AreEqual<bool>(true, &newFloatingTask.getTaskEndTime() == NULL);
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskType() == Task::FLOATING);
			Assert::AreEqual<bool>(true, Task::Priority::HIGH == newFloatingTask.getTaskPriority());
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskRecurrence() == Task::NONE);
		
			//testing timed tasks
			Date earlierDate = Date(2015, 10, 13, 17, 00);
			Date laterDate = Date(2015, 10, 13, 18, 00);
			Task newTimedTask = Task::Task("Do Something", &earlierDate, &laterDate, NULL, Task::Recurrence::NONE, Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newTimedTask.getTaskDetails());
			Assert::AreEqual<bool>(true, newTimedTask.getTaskType() == Task::TIMED);
			Assert::AreEqual<int>(0, newTimedTask.getTaskStartTime().isEarlierThan(newTimedTask.getTaskStartTime()));
			Assert::AreEqual<int>(1, newTimedTask.getTaskStartTime().isEarlierThan(newTimedTask.getTaskEndTime()));
			Assert::AreEqual<int>(-1, newTimedTask.getTaskEndTime().isEarlierThan(newTimedTask.getTaskStartTime()));
		}

		TEST_METHOD(DateTest)
		{
			//constructor and toString test
			Date nowDate = Date(2015,10,13,17,00);
			Assert::AreEqual<std::string>("Tue Oct 13 17:00:00 2015", nowDate.toString());

			//comparator test
			Date earlierDate = Date(2015, 10, 13, 17, 00);
			Date middleDate = Date(2015, 10, 13, 18, 00);
			Date middleDate2 = Date(2015, 10, 13, 18, 00);
			Date laterDate = Date(2015, 10, 13, 19, 00);
			Assert::AreEqual<int>(60, middleDate.diffInMinutes(laterDate));
			Assert::AreEqual<int>(0, middleDate.isEarlierThan(middleDate2));
			Assert::AreEqual<int>(1, middleDate.isEarlierThan(laterDate));
			Assert::AreEqual<int>(-1, middleDate.isEarlierThan(earlierDate));

			//getting year, month, date test
			Assert::AreEqual<int>(2015, nowDate.getYear());
			Assert::AreEqual<int>(10, nowDate.getMonth());
			Assert::AreEqual<int>(13, nowDate.getDay());
			Assert::AreEqual<int>(17, nowDate.getHour());
			Assert::AreEqual<int>(00, nowDate.getMinute());
			//Assert::AreEqual<string>("Tue", nowDate.getDayName());


		}
		TEST_METHOD(TaskManagerTest)
		{
			//checking both instances are the same, singleton class
			TaskManager* instance1 = TaskManager::getInstance();
			TaskManager* instance2 = TaskManager::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}
		
		TEST_METHOD(ControllerTest)
		{
			//checking both instances are the same, singleton class
			Controller* instance1 = Controller::getInstance();
			Controller* instance2 = Controller::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}

		TEST_METHOD(CommandBuilderTest)
		{
		}

		TEST_METHOD(CommandAddTest)
		{

		}


	};
}