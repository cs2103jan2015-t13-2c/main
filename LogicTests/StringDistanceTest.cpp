//@author A0122357L
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(SuggestionBuilderTest){
	public:
		TEST_METHOD(SuggestionBuilderTest1){
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
	};
}