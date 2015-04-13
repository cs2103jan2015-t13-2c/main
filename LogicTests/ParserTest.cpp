//@author A0113716M
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest{
	TEST_CLASS(ParserTest){
	public:
		/*
		* ====================================================================
		*  Floating Tasks
		* ====================================================================
		*/
		TEST_METHOD(addFloatingTaskTest){  
			Parser::parseCommandAdd("add task");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
		} 
		
		/*
		* ====================================================================
		*  Deadline Tasks
		* ====================================================================
		*/
		TEST_METHOD(addDeadlineTaskTest01){
			Parser::parseCommandAdd("add task by 23 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 12:00PM");

		} TEST_METHOD(addDeadlineTaskTest02){
			Parser::parseCommandAdd("add task by 1 jan");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "01 Jan 2016 (Fri), 12:00PM");

		} TEST_METHOD(addDeadlineTaskTest03){
			Parser::parseCommandAdd("add task by 23 dec 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 05:30AM");

		} TEST_METHOD(addDeadlineTaskTest04){
			Parser::parseCommandAdd("add task by 23 dec 2016");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 12:00PM");

		} TEST_METHOD(addDeadlineTaskTest05){
			Parser::parseCommandAdd("add task by 23 dec 2016 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 05:30AM");

		} TEST_METHOD(addDeadlineTaskTest06){
			Parser::parseCommandAdd("add task by 23 dec 2016 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:00PM");

		} TEST_METHOD(addDeadlineTaskTest07){
			Parser::parseCommandAdd("add task by 23 dec 2016 1830hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:30PM");

		} TEST_METHOD(addDeadlineTaskTest08){
			//This input will change each week
			Parser::parseCommandAdd("add task by this monday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline1 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline1->toString());

		} TEST_METHOD(addDeadlineTaskTest09){
			//This input will change each week
			Parser::parseCommandAdd("add task by this mon");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline2 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline2->toString());

		} TEST_METHOD(addDeadlineTaskTest10){
			//This input will change each week
			Parser::parseCommandAdd("add task by this mon 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline3 = new Date(Date().getYear(), Date().getMonth(), day, 05, 30);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline3->toString());

		} TEST_METHOD(addDeadlineTaskTest11){
			//This input will change each day
			Parser::parseCommandAdd("add task by today 12pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Date *deadline4 = new Date(Date().getYear(), Date().getMonth(), Date().getDay(), 12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline4->toString());
		} 
		
		/*
		* ====================================================================
		*  Timed Tasks
		* ====================================================================
		*/
		TEST_METHOD(addTimedTaskTest01){		
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 12:00PM");
		} TEST_METHOD(addTimedTaskTest02){
			Parser::parseCommandAdd("add task from 23 dec 5.30am to 27 dec 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");
		} TEST_METHOD(addTimedTaskTest03){
			Parser::parseCommandAdd("add task from 23 dec 0530hrs to 27 dec 1800hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");

		} TEST_METHOD(addTimedTaskTest04){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tuesday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime1 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime1->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime1 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime1->toString());

		} TEST_METHOD(addTimedTaskTest05){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tue");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime2 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime2->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime2 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime2->toString());


		} TEST_METHOD(addTimedTaskTest06){
			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tues");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime3 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime3->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime3 = new Date(Date().getYear(), Date().getMonth(), day, 12, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime3->toString());

		} TEST_METHOD(addTimedTaskTest07){
			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 3.30pm to next tue 5pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime4 = new Date(Date().getYear(), Date().getMonth(), day, 15, 30);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime4->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime4 = new Date(Date().getYear(), Date().getMonth(), day, 17, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime4->toString());

		} TEST_METHOD(addTimedTaskTest08){
			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 0100hrs to next tue 2359hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			int day;
			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			} else{
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime5 = new Date(Date().getYear(), Date().getMonth(), day, 01, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime5->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime5 = new Date(Date().getYear(), Date().getMonth(), day, 23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime5->toString());
		} 
		
		/*
		* ====================================================================
		*  Priority Check
		* ====================================================================
		*/
		TEST_METHOD(addPriorityTest01){
			Parser::parseCommandAdd("add task #impt");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::IsTrue(Parser::getTaskPriority() == Task::Priority::HIGH);

		} TEST_METHOD(addPriorityTest02){
			Parser::parseCommandAdd("add task by 23 dec #high");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::IsTrue(Parser::getTaskPriority() == Task::Priority::HIGH);

		} TEST_METHOD(addPriorityTest03){
			Parser::parseCommandAdd("add task from 23 dec to 27 dec #impt");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 12:00PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 12:00PM");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::Priority::HIGH);
		}

		/*
		* ====================================================================
		*  Updating of Tasks
		* ====================================================================
		*/
		TEST_METHOD(updateTaskDetailsTest){
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Parser::parseCommandUpdate("update 1 details new task");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "new task ");

		} TEST_METHOD(updateTaskStartTimeTest){
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Parser::parseCommandUpdate("update 1 starttime 25 dec");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "25 Dec 2015 (Fri), 12:00PM");

		} TEST_METHOD(updateTaskPriorityTest){
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Parser::parseCommandUpdate("update 1 priority high");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::HIGH);
		}
	};
}