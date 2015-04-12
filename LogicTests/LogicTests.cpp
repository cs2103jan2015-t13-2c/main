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
#include "SuggestionBuilder.cpp"
#include "StringDistance.cpp"
#include "ParseException.cpp"
#include "CustomException.cpp"
#include "TaskDisplayer.cpp"
#include "CommandSearch.cpp"
#include "CommandException.cpp"
#include "CommandRedo.cpp"
#include "CommandChangeFileLocation.cpp"
#include "CommandCheckFileLocation.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{		
	TEST_CLASS(TasksTest)
	{
	public:

		TEST_METHOD(SystemTest){
			
			TaskManager* instance = TaskManager::getInstance();
			vector<Task>* allCurrentTasks = TaskManager::getAllCurrentTasks();

			//making sure task has been added to the back of the task vector
			Assert::AreEqual<bool>(true, Controller::processUserInput("add hello") == "Task has been added!");
			int numOfTasks = instance->getNumberOfTasks();
			Assert::AreEqual<bool>(true, allCurrentTasks->at(numOfTasks - 1).getTaskDetails() == "hello");
			
			//add tasks by today test

			Assert::AreEqual<bool>(true, Controller::processUserInput("delete 1") == "Deleted Task #1");
			Assert::AreEqual<bool>(true, Controller::processUserInput("undo") == "Action has been undone!");
		}
		
		TEST_METHOD(TaskTest)
		{
			//testing floating task
			Task newFloatingTask = Task::Task("Do Something", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newFloatingTask.getTaskDetails());
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskDeadline() == nullptr);
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskStartTime() == nullptr);
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskEndTime() == nullptr);
			Assert::AreEqual<bool>(true, newFloatingTask.getTaskType() == Task::FLOATING);
			Assert::AreEqual<bool>(true, Task::Priority::HIGH == newFloatingTask.getTaskPriority());
		
			//testing timed tasks
			Date earlierDate = Date(2015, 10, 13, 17, 00);
			Date laterDate = Date(2015, 10, 13, 18, 00);
			Task newTimedTask = Task::Task("Do Something", &earlierDate, &laterDate, NULL, Task::Priority::HIGH);
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
			Assert::AreEqual<std::string>("13 Oct 2015 (Tue), 05:00PM", nowDate.toString());

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

			//same Date test
			Date tmrDate = Date(2015, 9, 14, 17, 00);
			Assert::AreEqual<bool>(true, earlierDate.sameDate(laterDate));
			Assert::AreEqual<bool>(false, earlierDate.sameDate(tmrDate));
			
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
			//checking that commandBuilder is cleared properly to be used by the next iteration
			CommandBuilder commandBuilder = CommandBuilder::CommandBuilder();
			Assert::AreEqual<bool>(true, commandBuilder.getTaskDetails() == "");
			Assert::AreEqual<bool>(true, commandBuilder.getTaskDeadline() == nullptr);
			Assert::AreEqual<bool>(true, commandBuilder.getTaskStartTime() == nullptr);
			Assert::AreEqual<bool>(true, commandBuilder.getTaskEndTime() == nullptr);
			Assert::AreEqual<bool>(true, commandBuilder.getTaskPriority() == Task::NORMAL);
			Assert::AreEqual<bool>(true, commandBuilder.getTaskMarked() == false);
			Assert::AreEqual<bool>(true, commandBuilder.getTaskNumber() == -1);

			//Checking constructing of a add command properly
			Command* addCommand = commandBuilder.parseCommand("add hello");
			//Assert::AreEqual<std::string>("CommandAdd", typeid(addCommand).name());
			Assert::AreEqual<std::string>("Task has been added!", addCommand->execute());

			//Checking constructing of a delete command properly
			//Command* deleteCommand = commandBuilder.parseCommand("delete 1");
			//Assert::AreEqual<std::string>("Deleted Task #%d", deleteCommand->execute());
			
			//Checking constructing of an update command properly
			//Command* updateCommand = commandBuilder.parseCommand("update 1");
			//Assert::AreEqual<std::string>("Deleted Task #%d", updateCommand->execute());
		}

		TEST_METHOD(SuggestionBuilderTest)
		{
			//Testing extreme cases of suggested command types
			//Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("") == "");
			
			//Testing parsing of suggested command types for add, different extreme cases
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType(" a") == "add");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("a") == "add");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("a ") == "add");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("ad") == "add");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("add") == "add");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("add hello ") == "add");

			//Testing parsing of suggested command types for all other command types
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("del") == "delete");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("disp") == "display");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("exit") == "exit");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("mar") == "mark");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("und") == "undo");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("upd") == "update");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandType("unm") == "unmark");

			//Testing parsing of suggested command arguments
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("delete","nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("display", "nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("exit", "nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("mark", "nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("undo", "nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("unmark", "nil") == "");
			Assert::AreEqual<bool>(true, SuggestionBuilder::suggestCommandArguments("update", "nil") == "");

			//Testing parsing of suggested command arguments
			Assert::AreEqual<bool>(true, SuggestionBuilder::predictedString("fr") == "from");

			//Testing prediction of command arguments for add, "from"
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add","add hello") == " hello");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add","add hello f") == " hello from ");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello fr ") == " hello from ");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello fr mon") == " hello from monday to ");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello fr mon t") == " hello from monday to ");
			//was thinking to fix this, if there are more words than suggestions, dun return anything!
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello fr mon t tue") == " hello from monday to ");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add tue hello fr") == " tue hello from ");
			
			//Testing prediction of command arguments for add, "by"
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello b sat") == " hello by saturday");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello mummy b sun") == " hello mummy by sunday");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestCommandArguments("add", "add hello mummy bye b sun") == " hello mummy bye by sunday");

			//Testing suggestion of entire user input
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestUserInput("add hello b sat") == "add hello by saturday");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestUserInput("add hello fr sat t") == "add hello from saturday to ");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestUserInput("del ") == "delete");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestUserInput("del 1") == "delete");
			Assert::AreEqual<bool>(true, SuggestionBuilder::
				suggestUserInput("dis") == "display");

		}

		TEST_METHOD(StringDistanceTest)
		{
			Assert::AreEqual<int>(0,StringDistance::LD("hello","hello"));
			Assert::AreEqual<int>(1, StringDistance::LD("hello", "hell"));
			Assert::AreEqual<int>(2, StringDistance::LD("hello", "helol"));
			Assert::AreEqual<int>(2, StringDistance::LD("hello", "hlo"));


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
			Parser::parseCommandAdd("add task by 23 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 11:59PM");

			Parser::parseCommandAdd("add task by 1 jan");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "01 Jan 2016 (Fri), 11:59PM");

			Parser::parseCommandAdd("add task by 23 dec 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 05:30AM");

			Parser::parseCommandAdd("add task by 23 dec 2016");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 11:59PM");

			Parser::parseCommandAdd("add task by 23 dec 2016 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 05:30AM");

			Parser::parseCommandAdd("add task by 23 dec 2016 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:00PM");

			Parser::parseCommandAdd("add task by 23 dec 2016 1830hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2016 (Fri), 06:30PM");



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
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline1->toString());


			//This input will change each week
			Parser::parseCommandAdd("add task by this mon");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *deadline2 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline2->toString());

			//This input will change each week
			Parser::parseCommandAdd("add task by this mon 5.30am");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

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

			//This input will change each day
			Parser::parseCommandAdd("add task by today 12pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Date *deadline4 = new Date(Date().getYear(),
				Date().getMonth(),
				Date().getDay(),
				12, 00);
			Assert::AreEqual<string>(Parser::getTaskDeadline()->toString(), deadline4->toString());


			/*-----------------------------------------------
			Timed Tasks
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task from 23 dec to 27 dec");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 11:59PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 11:59PM");

			Parser::parseCommandAdd("add task from 23 dec 5.30am to 27 dec 6pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");

			Parser::parseCommandAdd("add task from 23 dec 0530hrs to 27 dec 1800hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 05:30AM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 06:00PM");


			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tuesday");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime1 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime1->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime1 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime1->toString());


			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tue");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime2 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime2->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime2 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime2->toString());



			//This input will change each week
			Parser::parseCommandAdd("add task from this monday to next tues");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime3 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime3->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime3 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime3->toString());


			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 3.30pm to next tue 5pm");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime4 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				15, 30);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime4->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime4 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				17, 00);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime4->toString());


			//This input will change each week
			Parser::parseCommandAdd("add task from this mon 0100hrs to next tue 2359hrs");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");

			if (1 - Date().getDayName() >= 0){
				day = 1 - Date().getDayName() + Date().getDay();
			}
			else {
				day = 8 - Date().getDayName() + Date().getDay();
			};
			Date *starttime5 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				01, 00);
			Assert::AreEqual<string>(Parser::getTaskStartTime()->toString(), starttime5->toString());

			day = 9 - Date().getDayName() + Date().getDay();
			Date *endtime5 = new Date(Date().getYear(),
				Date().getMonth(),
				day,
				23, 59);
			Assert::AreEqual<string>(Parser::getTaskEndTime()->toString(), endtime5->toString());


			/*-----------------------------------------------
			Priority Check
			-----------------------------------------------*/
			Parser::parseCommandAdd("add task #impt");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::HIGH);


			Parser::parseCommandAdd("add task by 23 dec #high");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskDeadline())->toString(), "23 Dec 2015 (Wed), 11:59PM");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::HIGH);


			Parser::parseCommandAdd("add task from 23 dec to 27 dec #low");
			Assert::AreEqual<string>(Parser::getTaskDetails(), "task ");
			Assert::AreEqual<string>((Parser::getTaskStartTime())->toString(), "23 Dec 2015 (Wed), 11:59PM");
			Assert::AreEqual<string>((Parser::getTaskEndTime())->toString(), "27 Dec 2015 (Sun), 11:59PM");
			Assert::AreEqual<bool>(true, Parser::getTaskPriority() == Task::LOW);
		}


		TEST_METHOD(DirExistTest){
			/*
			Assert::AreEqual<bool>(true, CommandChangeFileLocation::dirExists("C:\\Users\\Adi!/Desktop\\CS2103\\Taskky"));
			Assert::AreEqual<bool>(false, CommandChangeFileLocation::dirExists("C:/Users/Adi!/Desktop/CS03/Taskky"));
			*/
		}

		TEST_METHOD(StorageTest) {

			//Assert::AreEqual<string>("C:\\Users\\Adi!\\Desktop\\CS2103\\Taskky\\Debug", Storage::findProgramDirectory());
		}
	};

}