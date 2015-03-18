#include "stdafx.h"
#include "CppUnitTest.h"
#include "Task.cpp"
#include "Taskky.cpp"
#include "Date.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{
	TEST_CLASS(TasksTest)
	{
	public:

		TEST_METHOD(TaskTest)
		{
			std::chrono::system_clock::time_point timepoint;
			timepoint += std::chrono::hours(23) + std::chrono::minutes(55);
			Task newFloatingTask = Task::Task(1, "Do Something", timepoint, timepoint,
				timepoint, Task::Recurrence::NONE, Task::Priority::HIGH);
			Assert::AreEqual<std::string>("Do Something", newFloatingTask.getTaskDetails());

			// need more testing 



			//dunno how to check priority
			//Assert::AreEqual<Task::Priority>(Task::Priority::HIGH, newTask.getTaskPriority());
			//Assert::AreEqual<bool>(true, newFloatingTask.isFloatingTask());
		}

		TEST_METHOD(DateTest)
		{
			//constructor and toString test
			Date nowDate = Date(2015, 10, 13, 17, 00);
			Assert::AreEqual<std::string>("Tue Oct 13 17:00:00 2015", nowDate.toString());

			//comparator test
			Date earlierDate = Date(2015, 10, 13, 17, 00);
			Date middleDate = Date(2015, 10, 13, 18, 00);
			Date middleDate2 = Date(2015, 10, 13, 18, 00);
			Date laterDate = Date(2015, 10, 13, 19, 00);
			Assert::AreEqual<int>(60, middleDate.diffInMinutes(laterDate));
			Assert::AreEqual<int>(0, middleDate.isEarlierThan(middleDate2));
			Assert::AreEqual<int>(1, middleDate.isEarlierThan(laterDate));
			Assert::AreEqual<int>(-1, middleDate.isEarlierThan(earlierDate));

			//getting year, month, date test
			Assert::AreEqual<int>(2015, nowDate.getYear());
			Assert::AreEqual<int>(10, nowDate.getMonth());
			Assert::AreEqual<int>(13, nowDate.getDay());
			Assert::AreEqual<int>(17, nowDate.getHour());
			Assert::AreEqual<int>(00, nowDate.getMinute());
			//Assert::AreEqual<string>("Tue", nowDate.getDayName());


		}

	};
}