//@author A0114084N
#pragma once
#include <string>
#include <algorithm>
#include "CommandBuilder.h"
#include "ParseException.h"
#include "StringDistance.h"

using namespace std;

class SuggestionBuilder
{
public:
	SuggestionBuilder();
	~SuggestionBuilder();

	static string suggestUserInput(string userInput);
	static string suggestCommandType(string userInput);
	
	//static string commandToString(CommandBuilder::CommandType commandType);


	static bool isPredictedCommandAdd(string userInput);
	static bool isPredictedCommandDelete(string userInput);
	static bool isPredictedCommandDisplay(string userInput);
	static bool isPredictedCommandExit(string userInput);
	static bool isPredictedCommandMark(string userInput);
	static bool isPredictedCommandUndo(string userInput);
	static bool isPredictedCommandUnmark(string userInput);
	static bool isPredictedCommandUpdate(string userInput);
	static bool isPredictedCommandCheckSavedFileLocation(string userInput);
	static bool isPredictedChangeFileLocation(string userInput);
	static bool isPredictedCommandSearch(string userInput);
	static bool isPredictedCommandHelp(string userInput);


	//getting predicted keywords
	static string predictedKeyword(string text);
	static bool isPredictedFrom(string userInput);
	static bool isPredictedTo(string userInput);
	static bool isPredictedNext(string userInput);
	static bool isPredictedBy(string userInput);
	static bool isPredictedThis(string userInput);
	static bool isPredictedEvery(string userInput);


	static string predictedDate(string text);

	/*
	static const string TASK_NUMBER_SUGGESTION;
	static const string TASK_DETAILS_SUGGESTION;
	static const string TASK_DATE_SUGGESTION;
	static const string TASK_DATE_SUGGESTION;
	*/

	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);

};

