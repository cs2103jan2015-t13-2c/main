//@author A0114084N
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(UtilityTest){
public:

	TEST_METHOD(DateTest)
	{
		Date nowDate = Date(2015, 9, 13, 17, 00);
		Assert::AreEqual<std::string>("13 Oct 2015 (Tue), 05:00PM", nowDate.toString());

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

	TEST_METHOD(StringDistanceTest)
	{
		Assert::AreEqual<int>(0, StringDistance::LD("hello", "hello"));
		Assert::AreEqual<int>(1, StringDistance::LD("hello", "hell"));
		Assert::AreEqual<int>(2, StringDistance::LD("hello", "helol"));
		Assert::AreEqual<int>(2, StringDistance::LD("hello", "hlo"));
	}
	};
}