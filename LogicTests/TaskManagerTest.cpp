//@author A0122357L
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(TaskManagerTest){
	public:
<<<<<<< HEAD
		TEST_METHOD(TaskManagerConstructorTest)
=======
		TEST_METHOD(TaskManagerTest1)
>>>>>>> origin/master
		{
			//checking both instances are the same, singleton class
			TaskManager* instance1 = TaskManager::getInstance();
			TaskManager* instance2 = TaskManager::getInstance();
			Assert::AreEqual<bool>(true, typeid(*instance1) == typeid(*instance2));
		}
<<<<<<< HEAD
		TEST_METHOD(TaskManagerAddTest)
		{
			TaskManager* instance = TaskManager::getInstance();
			instance->clearAllCurrentTasks();
			Assert::AreEqual<int>(0, instance->getNumberOfTasks());

			//tasks to be added
			Date* earlyDate = new Date(2015, 9, 13, 17, 00);
			Date* middleDate = new Date(2015, 9, 13, 18, 00);
			Date* lateDate = new Date(2015, 9, 13, 19, 00);
			Task firstTask = Task::Task("AAAA", nullptr, nullptr, earlyDate, Task::Priority::HIGH);
			Task secondTask = Task::Task("BBBB", nullptr, nullptr, middleDate, Task::Priority::HIGH);
			Task thirdTask = Task::Task("CCCC", nullptr, nullptr, lateDate, Task::Priority::HIGH);
			Task forthTask = Task::Task("DDDD", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task fifthTask = Task::Task("EEEE", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			
			//testing the add function
			Assert::AreEqual<int>(0, instance->getNumberOfTasks());
			instance->addTask(fifthTask);
			instance->addTask(forthTask);
			instance->addTask(thirdTask);
			instance->addTask(secondTask);
			instance->addTask(firstTask);
			Assert::AreEqual<int>(5, instance->getNumberOfTasks());

			//Checking if tasks are actually added in order
			vector<Task>* allTimedTasks = instance->getAllTimedTasks();
			vector<Task>* allFloatingTasks = instance->getAllFloatingTasks();
			
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
		}

		TEST_METHOD(TaskManagerSequenceTest)
		{
			//reseting all entered tasks
			TaskManager* instance = TaskManager::getInstance();
			instance->clearAllCurrentTasks();

			//testing alphabet sorting
			Task earlierAlphabet = Task::Task("AAAA", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task laterAlphabet = Task::Task("BBBB", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isAlphabeticallyArranged(earlierAlphabet, laterAlphabet));

			//testing date sorting with 2 deadline
			Date earlierDate = Date(2015, 9, 13, 17, 00);
			Date laterDate = Date(2015, 9, 13, 18, 00);
			Task earlierTask = Task::Task("AAAA", nullptr, nullptr, &earlierDate, Task::Priority::HIGH);
			Task laterTask = Task::Task("BBBB", nullptr, nullptr, &laterDate, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(earlierTask, laterTask));
			Assert::AreEqual<bool>(false, instance->isChronologicallyArranged(laterTask, earlierTask));

			//testing date sorting with 2 timed
			Date earlierDate2 = Date(2015, 9, 13, 18, 00);
			Date laterDate2 = Date(2015, 9, 13, 19, 00);
			earlierTask = Task::Task("AAAA", &earlierDate, &earlierDate2, nullptr, Task::Priority::HIGH);
			laterTask = Task::Task("BBBB", &laterDate, &laterDate2, nullptr, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(earlierTask, laterTask));
			Assert::AreEqual<bool>(false, instance->isChronologicallyArranged(laterTask, earlierTask));
				
			//testing date sorting with 1 deadline 1 timed
			earlierTask = Task::Task("AAAA", nullptr, nullptr, &earlierDate, Task::Priority::HIGH);
			laterTask = Task::Task("BBBB", &laterDate, &laterDate2, nullptr, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(earlierTask, laterTask));
			Assert::AreEqual<bool>(false, instance->isChronologicallyArranged(laterTask, earlierTask));

			//testing date sorting with 1 timed 1 deadline
			earlierTask = Task::Task("AAAA", &earlierDate, &earlierDate2, nullptr, Task::Priority::HIGH);
			laterTask = Task::Task("BBBB", nullptr, nullptr, &laterDate, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(earlierTask, laterTask));
			Assert::AreEqual<bool>(false, instance->isChronologicallyArranged(laterTask, earlierTask));

			//testing date sorting with 2 same deadline
			earlierTask = Task::Task("AAAA", nullptr, nullptr, &laterDate, Task::Priority::HIGH);
			laterTask = Task::Task("BBBB", nullptr, nullptr, &laterDate, Task::Priority::HIGH);
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(earlierTask, laterTask));
			Assert::AreEqual<bool>(true, instance->isChronologicallyArranged(laterTask, earlierTask));


			//setting up floating vector to insert 
			vector<Task>* floatingVector = new vector < Task > ;
			Task earlierAlphabetTask = Task::Task("AAAA", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task middleAlphabetTask = Task::Task("BBBB", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			Task laterAlphabetTask = Task::Task("CCC", nullptr, nullptr, nullptr, Task::Priority::HIGH);
			
			//testing getting later alphabet insert index
			floatingVector->push_back(earlierAlphabetTask);
			floatingVector->push_back(middleAlphabetTask);
			Assert::AreEqual<int>(2, floatingVector->size());
			Assert::AreEqual<int>(2, TaskManager::getFloatingIndexToInsert(laterAlphabetTask, floatingVector));

			//testing getting middle alphabet insert index
			floatingVector->clear();
			floatingVector->push_back(earlierAlphabetTask);
			floatingVector->push_back(laterAlphabetTask);
			Assert::AreEqual<int>(2, floatingVector->size());
			Assert::AreEqual<int>(1, TaskManager::getFloatingIndexToInsert(middleAlphabetTask, floatingVector));

			//testing getting earlier alphabet insert index
			floatingVector->clear();
			floatingVector->push_back(middleAlphabetTask);
			floatingVector->push_back(laterAlphabetTask);
			Assert::AreEqual<int>(2, floatingVector->size());
			Assert::AreEqual<int>(0, TaskManager::getFloatingIndexToInsert(earlierAlphabetTask, floatingVector));


			//setting up timed vector to insert 
			vector<Task>* timedVector = new vector < Task >;
			Date* earlyDate = new Date(2015, 9, 13, 17, 00);
			Date* middleDate = new Date(2015, 9, 13, 18, 00);
			Date* lateDate = new Date(2015, 9, 13, 19, 00);
			Task earlierTimedTask = Task::Task("AAAA", nullptr, nullptr, earlyDate, Task::Priority::HIGH);
			Task middleTimedTask = Task::Task("BBBB", nullptr, nullptr, middleDate, Task::Priority::HIGH);
			Task laterTimedTask = Task::Task("CCC", nullptr, nullptr, lateDate, Task::Priority::HIGH);
			Task middleTimedTaskBeta = Task::Task("DDD", nullptr, nullptr, middleDate, Task::Priority::HIGH);

			//testing getting later timing insert index
			timedVector->push_back(earlierTimedTask);
			timedVector->push_back(middleTimedTask);
			Assert::AreEqual<int>(2, timedVector->size());
			Assert::AreEqual<int>(2, TaskManager::getTimedIndexToInsert(laterTimedTask, timedVector));

			//testing getting middle timing insert index
			timedVector->clear();
			timedVector->push_back(earlierTimedTask);
			timedVector->push_back(laterTimedTask);
			Assert::AreEqual<int>(2, timedVector->size());
			Assert::AreEqual<int>(1, TaskManager::getTimedIndexToInsert(middleTimedTask, timedVector));

			//testing getting earlier timing insert index
			timedVector->clear();
			timedVector->push_back(middleTimedTask);
			timedVector->push_back(laterTimedTask);
			Assert::AreEqual<int>(2, timedVector->size());
			Assert::AreEqual<int>(0, TaskManager::getTimedIndexToInsert(earlierTimedTask, timedVector));

			//testing inserting same deadline tasks into the vector
			timedVector->clear();
			timedVector->push_back(earlierTimedTask);
			timedVector->push_back(middleTimedTask);
			timedVector->push_back(laterTimedTask);
			Assert::AreEqual<int>(3, timedVector->size());
			Assert::AreEqual<int>(2, TaskManager::getTimedIndexToInsert(middleTimedTaskBeta, timedVector));

			//testing inserting same deadline tasks into the vector
			timedVector->clear();
			timedVector->push_back(earlierTimedTask);
			timedVector->push_back(middleTimedTaskBeta);
			timedVector->push_back(laterTimedTask);
			Assert::AreEqual<int>(3, timedVector->size());
			Assert::AreEqual<int>(1, TaskManager::getTimedIndexToInsert(middleTimedTask, timedVector));
			
			//testing getIndexToInsert
			vector<Task>* allFloatingTasks = instance->getAllFloatingTasks();
			vector<Task>* allTimedTasks = instance->getAllTimedTasks();
			vector<Task>* allMarkedFloatingTasks = instance->getAllMarkedFloatingTasks();
			vector<Task>* allMarkedTimedTasks = instance->getAllMarkedTimedTasks();

		}
=======
>>>>>>> origin/master
	};
}