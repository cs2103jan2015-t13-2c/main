#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(ParserTest){
	public:
		TEST_METHOD(ParserAddTest)
		{   /*-----------------------------------------------
			Floating Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
		} TEST_METHOD(DeadlineAdd1){

			/*-----------------------------------------------
			Deadline Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task by 23 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 12:00PM");
		} TEST_METHOD(DeadlineAdd2){
			Parser::parseCommandAdd("add task by 1 jan");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "01 Jan 2016 (Fri), 12:00PM");
		} TEST_METHOD(DeadlineAdd3){
			Parser::parseCommandAdd("add task by 23 dec 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 05:30AM");
		} TEST_METHOD(DeadlineAdd4){
			Parser::parseCommandAdd("add task by 23 dec 2016");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 12:00PM");
		} TEST_METHOD(DeadlineAdd5){
			Parser::parseCommandAdd("add task by 23 dec 2016 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 05:30AM");
		} TEST_METHOD(DeadlineAdd6){
			Parser::parseCommandAdd("add task by 23 dec 2016 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:00PM");
		} TEST_METHOD(DeadlineAdd7){
			Parser::parseCommandAdd("add task by 23 dec 2016 1830hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:30PM");


		} TEST_METHOD(DeadlineAdd8){
			//This input will change each week
			Parser::parseCommandAdd("add task by this monday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline1 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline1->toString());

		} TEST_METHOD(DeadlineAdd9){
			//This input will change each week
			Parser::parseCommandAdd("add task by this mon");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline2 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline2->toString());

		} TEST_METHOD(DeadlineAdd10){
			//This input will change each week
			Parser::parseCommandAdd("add task by this mon 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline3 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				05, 30);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline3->toString());

		} TEST_METHOD(DeadlineAdd11){
			//This input will change each day
			Parser::parseCommandAdd("add task by today 12pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Date *deadline4 = new Date(Date().getYear(),
				Date().getMonth(),
				Date().getDay(),
				12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline4->toString());

		} TEST_METHOD(TimedAdd1){
			/*-----------------------------------------------
			Timed Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 12:00PM");
		} TEST_METHOD(TimedAdd2){
			Parser::parseCommandAdd("add task from 23 dec 5.30am to 27 dec 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");
		} TEST_METHOD(TimedAdd3){
			Parser::parseCommandAdd("add task from 23 dec 0530hrs to 27 dec 1800hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");

		} TEST_METHOD(TimedAdd4){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tuesday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime1 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime1->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime1 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime1->toString());

		} TEST_METHOD(TimedAdd5){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tue");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime2 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime2->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime2 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime2->toString());


		} TEST_METHOD(TimedAdd6){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tues");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime3 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime3->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime3 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime3->toString());

		} TEST_METHOD(TimedAdd7){
			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 3.30pm to next tue 5pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime4 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 15, 30);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime4->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime4 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 17, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime4->toString());

		} TEST_METHOD(TimedAdd8){
			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 0100hrs to next tue 2359hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime5 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 01, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime5->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime5 = new Date(Date().getYear(),
				Date().getMonth(),
				day, 23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime5->toString());

		} TEST_METHOD(PriorityAdd1){
			/*-----------------------------------------------
			Priority Check
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task #impt");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::IsTrue(Parser::getTaskPriority() == Task::Priority::HIGH);

		} TEST_METHOD(PriorityAdd2){
			Parser::parseCommandAdd("add task by 23 dec #high");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::IsTrue(Parser::getTaskPriority() == Task::Priority::HIGH);

		} TEST_METHOD(PriorityAdd3){
			Parser::parseCommandAdd("add task from 23 dec to 27 dec #impt");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 12:00PM");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::Priority::HIGH);
		}
		TEST_METHOD(ParserUpdateTest) {
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");

			Parser::parseCommandUpdate("update 1 details new task");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "new task ");

			Parser::parseCommandUpdate("update 1 starttime 25 dec");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "25 Dec 2015 (Fri), 12:00PM");

			Parser::parseCommandUpdate("update 1 priority high");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::HIGH);
		}
	};
}