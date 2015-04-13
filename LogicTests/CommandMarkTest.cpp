#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{
	TEST_CLASS(CommandMarkTest)
	{
	public:

		TEST_METHOD(MarkTaskTest)
		{

			//reseting instance
			TaskManager* instance = TaskManager::getInstance();
			instance->clearAllCurrentTasks();

			//setting up 5 and adding 5 tasks
			Date* earlyDate = new Date(2015, 9, 13, 17, 00);
			Date* middleDate = new Date(2015, 9, 13, 18, 00);
			Date* lateDate = new Date(2015, 9, 13, 19, 00);
			Task firstTask = Task::Task("AAAA", nullptr, nullptr, earlyDate, Task::Priority::HIGH);
			Task secondTask = Task::Task("BBBB", nullptr, nullptr, middleDate, Task::Priority::HIGH);
			Task thirdTask = Task::Task("CCCC", nullptr, nullptr, lateDate, Task::Priority::HIGH);
			Task forthTask = Task::Task("DDDD", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task fifthTask = Task::Task("EEEE", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			instance->addTask(fifthTask);
			instance->addTask(forthTask);
			instance->addTask(thirdTask);
			instance->addTask(secondTask);
			instance->addTask(firstTask);

			//Checking if tasks are actually added in order
			vector<Task>* allTimedTasks = instance->getAllTimedTasks();
			vector<Task>* allFloatingTasks = instance->getAllFloatingTasks();
			vector<Task>* allMarkedTimedTasks = instance->getAllMarkedTimedTasks();
			vector<Task>* allMarkedFloatingTasks = instance->getAllMarkedFloatingTasks();

			//current order
			//1. allTimedTasks - firstTask
			//2. allTimedTasks - secondTask
			//3. allTimedTasks - thirdTask
			//4. allFloatingTasks - forthTask
			//5. allFloatingTasks - fifthTask

			//accessing the actual vector it is updated at
			Assert::AreEqual<string>(firstTask.getTaskDetails(), allTimedTasks->at(0).getTaskDetails());
			Assert::AreEqual<string>(secondTask.getTaskDetails(), allTimedTasks->at(1).getTaskDetails());
			Assert::AreEqual<string>(thirdTask.getTaskDetails(), allTimedTasks->at(2).getTaskDetails());
			Assert::AreEqual<string>(forthTask.getTaskDetails(), allFloatingTasks->at(0).getTaskDetails());
			Assert::AreEqual<string>(fifthTask.getTaskDetails(), allFloatingTasks->at(1).getTaskDetails());

			//accessing the allcurrenttask vector to check
			Assert::AreEqual<string>(firstTask.getTaskDetails(), instance->getTask(1).getTaskDetails());
			Assert::AreEqual<string>(secondTask.getTaskDetails(), instance->getTask(2).getTaskDetails());
			Assert::AreEqual<string>(thirdTask.getTaskDetails(), instance->getTask(3).getTaskDetails());
			Assert::AreEqual<string>(forthTask.getTaskDetails(), instance->getTask(4).getTaskDetails());
			Assert::AreEqual<string>(fifthTask.getTaskDetails(), instance->getTask(5).getTaskDetails());

			CommandMark* command = new CommandMark(1);
			command->execute();


			//current order
			//1. allTimedTasks - secondTask
			//2. allTimedTasks - thirdTask
			//3. allFloatingTasks - forthTask
			//4. allFloatingTasks - fifthTask
			//5. allMarkedTimedTasks - firstTask

			//accessing the actual vector it is updated at
			Assert::AreEqual<string>(secondTask.getTaskDetails(), allTimedTasks->at(0).getTaskDetails());
			Assert::AreEqual<string>(thirdTask.getTaskDetails(), allTimedTasks->at(1).getTaskDetails());
			Assert::AreEqual<string>(forthTask.getTaskDetails(), allFloatingTasks->at(0).getTaskDetails());
			Assert::AreEqual<string>(fifthTask.getTaskDetails(), allFloatingTasks->at(1).getTaskDetails());
			Assert::AreEqual<string>(firstTask.getTaskDetails(), allMarkedTimedTasks->at(0).getTaskDetails());

		}

	};
}