//@author A0122357L
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(CommandBuilderTests)
	{
	public:
		
		TEST_METHOD(CommandBuilderTest1)
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

	};
}