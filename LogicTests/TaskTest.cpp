#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
#include "FloatingTask.cpp"
#include "DeadlineTask.cpp"
#include <chrono>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//template<> static std::wstring ToString<Task::Priority>(const Task::Priority& taskPriority) 
//    { 
  //     return taskPriority == Task::Priority::LOW ? L"F" : L"R"; 
    //};

namespace LogicTests
{
	

	TEST_CLASS(TasksTest)
	{

	public:
		
		TEST_METHOD(TaskTest)
		{

			Task newTask = Task::Task("Do Something",Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
			//Assert::AreEqual<Task::Priority>(Task::Priority::HIGH, newTask.getTaskPriority());
		}

		TEST_METHOD(FloatingTaskTest)
		{
			FloatingTask newTask = FloatingTask::FloatingTask("Do Something",Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
			//Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
		}

		TEST_METHOD(DeadlineTaskTest)
		{
			DeadlineTask newTask = DeadlineTask::DeadlineTask("Do Something");
			Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());

			// define type for durations that represent day(s):
			typedef std::chrono::duration<int,std::ratio<3600*24>> Days;
			//getting the epoch of system_clock, January 1, 1970
			std::chrono::system_clock::time_point tp;
			//adding to the epoch
			tp+= Days(1) + std::chrono::hours(23) + std::chrono::minutes(55);

			auto timeDifference = tp - std::chrono::system_clock::time_point();
			int hours = std::chrono::duration_cast<std::chrono::hours>(timeDifference).count();

			//getting time duration
			//std::chrono::system_clock::duration timeDuration = tp.time_since_epoch();


			DeadlineTask newerTask = DeadlineTask::DeadlineTask("Do Something",
				DeadlineTask::Priority::HIGH,DeadlineTask::Recurrance::NONE,tp);
			Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
			Assert::AreEqual<int>(47, hours);
		}

		TEST_METHOD(TimedTaskTest)
		{
			//TimedTask newTask = TimedTask::TimedTask("Do Something",Task::Priority::HIGH);
			//Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
			//Assert::AreEqual<std::string>("Do Something", newTask.getTaskDetails());
		}

	};
}