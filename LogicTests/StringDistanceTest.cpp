//@author A0122357L
#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(SuggestionBuilderTest){
	public:
		TEST_METHOD(StringDistanceTest1){
			Assert::AreEqual<int>(0, StringDistance::LD("hello", "hello"));
			Assert::AreEqual<int>(1, StringDistance::LD("hello", "hell"));
			Assert::AreEqual<int>(2, StringDistance::LD("hello", "helol"));
			Assert::AreEqual<int>(2, StringDistance::LD("hello", "hlo"));
		}
	};
}