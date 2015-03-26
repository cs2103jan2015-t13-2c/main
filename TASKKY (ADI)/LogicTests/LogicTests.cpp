#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
#include "Date.cpp"
#include "TaskManager.cpp"
#include "Controller.cpp"
#include "CommandBuilder.cpp"
#include "CommandAdd.cpp"
#include "Command.cpp"
#include "CommandInvalid.cpp"
#include "CommandDisplay.cpp"
#include "Parser.cpp"
#include "CommandUpdate.cpp"
#include "CommandDelete.cpp"
#include "CommandExit.cpp"
#include "Storage.cpp"
#include "CommandUndo.cpp"
#include "CommandMark.cpp"
#include "CommandUnmark.cpp"

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
			Assert::AreEqual<int>(0, newTimedTask.getTaskStartTime()->isEarlierThan(*newTimedTask.getTaskStartTime()));
			Assert::AreEqual<int>(1, newTimedTask.getTaskStartTime()->isEarlierThan(*newTimedTask.getTaskEndTime()));
			Assert::AreEqual<int>(-1, newTimedTask.getTaskEndTime()->isEarlierThan(*newTimedTask.getTaskStartTime()));
		}

		TEST_METHOD(DateTest)
		{
			//constructor and toString test
			Date nowDate = Date(2015,9,13,17,00);
			Assert::AreEqual<std::string>("Tue Oct 13 17:00:00 2015", nowDate.toString());

			//comparator test
			Date earlierDate = Date(2015, 9, 13, 17, 00);
			Date middleDate = Date(2015, 9, 13, 18, 00);
			Date middleDate2 = Date(2015, 9, 13, 18, 00);
			Date laterDate = Date(2015, 9, 13, 19, 00);
			Assert::AreEqual<int>(60, middleDate.diffInMinutes(laterDate));
			Assert::AreEqual<int>(0, middleDate.isEarlierThan(middleDate2));
			Assert::AreEqual<int>(1, middleDate.isEarlierThan(laterDate));
			Assert::AreEqual<int>(-1, middleDate.isEarlierThan(earlierDate));

			//getting year, month, date test
			Assert::AreEqual<int>(2015, nowDate.getYear());
			Assert::AreEqual<int>(9, nowDate.getMonth());
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

		TEST_METHOD(ParserTest)
		{   /*-----------------------------------------------
			Floating Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");


			/*-----------------------------------------------
			Deadline Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task by 23 mar");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 00:00:00 2015");

			Parser::parseCommandAdd("add task by 23 mar 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 05:30:00 2015");

			Parser::parseCommandAdd("add task by 23 mar 2016");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 23 00:00:00 2016");

			Parser::parseCommandAdd("add task by 23 mar 2016 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 23 05:30:00 2016");

			Parser::parseCommandAdd("add task by 23 mar 2016 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 23 18:00:00 2016");

			Parser::parseCommandAdd("add task by 23 mar 2016 1830hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 23 18:30:00 2016");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task by this monday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 00:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task by this mon");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 00:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task by this mon 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 05:30:00 2015");


			/*-----------------------------------------------
			Timed Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task from 23 mar to 27 mar");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 00:00:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Fri Mar 27 00:00:00 2015");

			Parser::parseCommandAdd("add task from 23 mar 5.30am to 27 mar 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 05:30:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Fri Mar 27 18:00:00 2015");

			Parser::parseCommandAdd("add task from 23 mar 0530hrs to 27 mar 1800hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 05:30:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Fri Mar 27 18:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task from this monday to next tuesday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 00:00:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Tue Mar 31 00:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task from this monday to next tue");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 00:00:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Tue Mar 31 00:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task from this monday to next tues");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 00:00:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Tue Mar 31 00:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task from this mon 3.30pm to next tue 5pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 15:30:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Tue Mar 31 17:00:00 2015");

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task from this mon 0100hrs to next tue 2359hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 01:00:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Tue Mar 31 23:59:00 2015");


			/*-----------------------------------------------
			Recurring(DAY) Tasks
			-----------------------------------------------*/
			//This test will have to be updated each DAY
			Parser::parseCommandAdd("add task every day");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 25 00:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::DAY);

			//This test will have to be updated each DAY
			Parser::parseCommandAdd("add task every day at 8am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Wed Mar 25 08:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::DAY);


			/*-----------------------------------------------
			Recurring(WEEK) Tasks
			-----------------------------------------------*/
			//This test will have to be updated each week
			Parser::parseCommandAdd("add task every mon");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 00:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::WEEK);

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task every mon 8.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Mon Mar 23 08:30:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::WEEK);

			//This test will have to be updated each week
			Parser::parseCommandAdd("add task every mon 8.30am to fri 5pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "Mon Mar 23 08:30:00 2015");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "Fri Mar 27 17:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::WEEK);


			/*-----------------------------------------------
			Recurring(MONTH) Tasks
			-----------------------------------------------*/
			//This test will have to be updated each month
			Parser::parseCommandAdd("add task every nov");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Sun Nov 01 00:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::MONTH);

			//This test will have to be updated each month
			Parser::parseCommandAdd("add task every november");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "Sun Nov 01 00:00:00 2015");
			//Assert::AreEqual<Task::Recurrence>((Parser::getTaskRecurrence()), Task::MONTH);
		}
	};

}