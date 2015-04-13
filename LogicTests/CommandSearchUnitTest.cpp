#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{
	TEST_CLASS(CommandSearchUnitTest)
	{
	public:
		/*
		TEST_METHOD(searchExactName1)
		{
			clearTasks();
			addStandardTasks();
			CommandSearch test1("name", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 0 tasks found.", test1.execute());
			Assert::AreEqual<bool>(true, test1.getTasksIndices()->empty());
		}
		TEST_METHOD(searchExactName2){
			CommandSearch test2("Task", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 4 tasks found.", test2.execute());
			Assert::AreEqual<bool>(false, test2.getTasksIndices()->empty());
			vector<int> myVec = *(test2.getTasksIndices());
			vector<int>::iterator iter;
			int i = 1;
			for (iter = myVec.begin(); iter != myVec.end(); ++iter){
				Assert::AreEqual<int>(i, *iter);
				++i;
			}
		}
		TEST_METHOD(searchExactName3){
			CommandSearch test3("deadline", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);
			Assert::AreEqual<string>("There are 1 tasks found.", test3.execute());
			Assert::AreEqual<bool>(false, test3.getTasksIndices()->empty());
			Assert::AreEqual<int>(1, test3.getTasksIndices()->front());
		}
		TEST_METHOD(searchNearMatch1){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deadline Task - will be indexed as 1", TaskManager::getAllCurrentTasks()->front().getTaskDetails());
			CommandSearch test4("task", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 4 tasks found.", test4.execute());
			Assert::AreEqual<bool>(false, test4.getTasksIndices()->empty());
			Assert::AreEqual<int>(4, test4.getTasksIndices()->size());
			vector<int> myVec = *(test4.getTasksIndices());
			vector<int>::iterator iter;
			int i = 1;
			for (iter = myVec.begin(); iter != myVec.end(); ++iter){
				Assert::AreEqual<int>(i, *iter);
				++i;
			}
		}
		TEST_METHOD(searchNearMatch2){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deadline Task - will be indexed as 1", TaskManager::getAllCurrentTasks()->front().getTaskDetails());
			CommandSearch test5("Normak", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test5.execute());
			Assert::AreEqual<bool>(false, test5.getTasksIndices()->empty());
			Assert::AreEqual<int>(1, test5.getTasksIndices()->size());
			Assert::AreEqual<int>(3, test5.getTasksIndices()->front());
		}
		TEST_METHOD(searchDateRange1){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test6("", new Date(), new Date(2016,1,2,0,0), NULL, 
				Task::Priority::NORMAL, "", false,false, false);

			Assert::AreEqual<string>("There are 2 tasks found.", test6.execute());
			
			
			Assert::AreEqual<int>(2, test6.getTasksIndices()->size());
			vector<int> myVec = *(test6.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(1, *iter);
			++iter;
			Assert::AreEqual<int>(2, *iter);
		}
		TEST_METHOD(searchDateRange2){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test7("", new Date(), new Date(2015, 11, 1, 0, 0), NULL,
				Task::Priority::NORMAL, "", false, false, false);
			
			Assert::AreEqual<string>("There are 1 tasks found.", test7.execute());


			Assert::AreEqual<int>(1, test7.getTasksIndices()->size());
			vector<int> myVec = *(test7.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(1, *iter);
		}
		TEST_METHOD(searchDateRange3){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test8("", new Date(2015,11,1,0,0), new Date(2016, 0, 1, 0, 0), NULL,
				Task::Priority::NORMAL, "", false, false, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test8.execute());


			Assert::AreEqual<int>(1, test8.getTasksIndices()->size());
			vector<int> myVec = *(test8.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(2, *iter);
		}
		TEST_METHOD(searchAfter){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test9("", new Date(2015, 11, 1, 0, 0), NULL, NULL,
				Task::Priority::NORMAL, "", false, false, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test9.execute());


			Assert::AreEqual<int>(1, test9.getTasksIndices()->size());
			vector<int> myVec = *(test9.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(2, *iter);
		}
		TEST_METHOD(searchBefore){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test10("", NULL, new Date(2015, 11, 1, 0, 0), NULL,
				Task::Priority::NORMAL, "", false, false, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test10.execute());


			Assert::AreEqual<int>(1, test10.getTasksIndices()->size());
			vector<int> myVec = *(test10.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(1, *iter);
		}
		TEST_METHOD(searchPriority){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test11("", NULL, NULL, NULL,
				Task::Priority::HIGH, "", false, false, true);

			Assert::AreEqual<string>("There are 2 tasks found.", test11.execute());

			Assert::AreEqual<int>(2, test11.getTasksIndices()->size());
			vector<int> myVec = *(test11.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(2, *iter);
			++iter;
			Assert::AreEqual<int>(4, *iter);
		}
		TEST_METHOD(searchMarked){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test12("", NULL, NULL, NULL,
				Task::Priority::HIGH, "", true, true, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test12.execute());

			Assert::AreEqual<int>(1, test12.getTasksIndices()->size());
			vector<int> myVec = *(test12.getTasksIndices());
			vector<int>::iterator iter = myVec.begin();
			Assert::AreEqual<int>(4, *iter);
		}
		TEST_METHOD(searchEmptySlot1){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test13("", NULL, NULL, NULL,
				Task::Priority::NORMAL, "1 day 5 hours", false, false, false);

			Assert::AreEqual<string>("Next available 1 day 5 hoursis from now!.", test13.execute());
		}
		TEST_METHOD(searchEmptySlot2){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			CommandSearch test14("", NULL, NULL, NULL,
				Task::Priority::NORMAL, "365 days", false, false, false);

			Assert::AreEqual<string>("Next available 365 daysis from 01 Jan 2016 (Fri), 10:00AM.", test14.execute());
		}
		*/
	private:
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
		void clearTasks(){
			while (!TaskManager::getAllCurrentTasks()->empty()){
				TaskManager::removeTask(1);
			}
		}
	};
}