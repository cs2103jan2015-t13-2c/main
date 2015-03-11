#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
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
		
		TEST_METHOD(FloatingTaskTest)
		{

			Task newFloatingTask = Task::Task("Do Something",Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newFloatingTask.getTaskDetails());
			//dunno how to check priority
			//Assert::AreEqual<Task::Priority>(Task::Priority::HIGH, newTask.getTaskPriority());
			Assert::AreEqual<bool>(true,newFloatingTask.isFloatingTask());

		}

		TEST_METHOD(DeadlineTaskTest)
		{

			// define type for durations that represent day(s):
			typedef std::chrono::duration<int,std::ratio<3600*24>> Days;
			//getting the epoch of system_clock, January 1, 1970
			std::chrono::system_clock::time_point timepoint;
			//adding to the epoch
			timepoint += Days(1) + std::chrono::hours(23) + std::chrono::minutes(55);


			Task newDeadlineTask = Task::Task("Do Something",Task::Priority::NORMAL,
				Task::Recurrence::NONE, timepoint);
			Assert::AreEqual<std::string>("Do Something", newDeadlineTask.getTaskDetails());

			std::chrono::system_clock::time_point tp = newDeadlineTask.getTaskDeadline();
			auto timeDifference = tp - std::chrono::system_clock::time_point();
			int hours = std::chrono::duration_cast<std::chrono::hours>(timeDifference).count();
			Assert::AreEqual<int>(47, hours);

			//getting time duration
			//std::chrono::system_clock::duration timeDuration = tp.time_since_epoch();

		}

	};
}