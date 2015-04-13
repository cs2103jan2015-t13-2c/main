#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{
	TEST_CLASS(CommandSearchUnitTest)
	{
	public:
		
		TEST_METHOD(searchExactName1)
		{
			TaskManager::removeTask(1);
			addStandardTasks();
			CommandSearch test1("name", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 0 tasks found.", test1.execute());
			Assert::AreEqual<bool>(true, test1.getTasksIndices().empty());
		}
		TEST_METHOD(searchExactName2){
			CommandSearch test2("Task", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 4 tasks found.", test2.execute());
			Assert::AreEqual<bool>(false, test2.getTasksIndices().empty());
			Assert::AreEqual<int>(1, test2.getTasksIndices()[0]);
			Assert::AreEqual<int>(2, test2.getTasksIndices()[1]);
			Assert::AreEqual<int>(3, test2.getTasksIndices()[2]);
		}
		TEST_METHOD(searchExactName3){
			CommandSearch test3("deadline", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);
			Assert::AreEqual<string>("There are 1 tasks found.", test3.execute());
			Assert::AreEqual<bool>(false, test3.getTasksIndices().empty());
			Assert::AreEqual<int>(1, test3.getTasksIndices().front());
		}
		TEST_METHOD(searchNearMatch1){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deadline Task - will be indexed as 1", TaskManager::getAllCurrentTasks()->front().getTaskDetails());
			CommandSearch test4("task", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 4 tasks found.", test4.execute());
			Assert::AreEqual<bool>(false, test4.getTasksIndices().empty());
			Assert::AreEqual<int>(4, test4.getTasksIndices().size());
			Assert::AreEqual<int>(1, test4.getTasksIndices()[0]);
			Assert::AreEqual<int>(2, test4.getTasksIndices()[1]);
			Assert::AreEqual<int>(3, test4.getTasksIndices()[2]);
			Assert::AreEqual<int>(4, test4.getTasksIndices()[3]);
		}
		TEST_METHOD(searchNearMatch2){
			Assert::AreEqual<int>(4, TaskManager::getAllCurrentTasks()->size());
			Assert::AreEqual<string>("Deadline Task - will be indexed as 1", TaskManager::getAllCurrentTasks()->front().getTaskDetails());
			CommandSearch test5("notmal", NULL, NULL, NULL, Task::Priority::NORMAL, "", false,
				false, false);

			Assert::AreEqual<string>("There are 1 tasks found.", test5.execute());
			Assert::AreEqual<bool>(false, test5.getTasksIndices().empty());
			Assert::AreEqual<int>(1, test5.getTasksIndices().size());
			Assert::AreEqual<int>(3, test5.getTasksIndices()[0]);
		}
	private:
		void addStandardTasks(){
			TaskManager::addTask(Task("Marked Task - will be indexed as 4", NULL, NULL, NULL,
				Task::Priority::HIGH));
			TaskManager::markTask(1);
			TaskManager::addTask(Task("Normal Floating Task - will be indexed as 3", NULL, NULL, NULL,
				Task::Priority::NORMAL));
			TaskManager::addTask(Task("Timed Task - will be indexed as 2", new Date(2015, 12, 25, 12, 0),
				new Date(2016, 1, 1, 0, 0), NULL, Task::Priority::HIGH));
			TaskManager::addTask(Task("Deadline Task - will be indexed as 1", NULL, NULL,
				new Date(2015, 9, 19, 10, 0), Task::Priority::NORMAL));
		}
	};
}