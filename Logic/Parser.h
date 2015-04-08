#pragma once
#include <string>
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "ParseException.h"
#include "CommandException.h"

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();

	static void clearPreviousParse();

	static void parseCommandAdd(string userCommand);
	static void parseCommandUpdate(string userCommand);
	static void parseCommandDelete(string userCommand);
	static void parseCommandMark(string userCommand);
	static void parseCommandUnmark(string userCommand);
	static void parseCommandSearch(string userCommand);
	static void parseCommandChangeFileLocation(string userCommand);

	static string getTaskDetails();
	static Date* getTaskStartTime();
	static Date* getTaskEndTime();
	static Date* getTaskDeadline();
	static Task::Priority getTaskPriority();
	static string getDuration();
	static bool getTaskMarked();
	static int Parser::getTaskNumber();
	static bool Parser::getFoundMarked();
	static bool Parser::getFoundPriority();

	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static unsigned int countWordsInString(const string& str);
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);
	static bool isKeyword(string word);
	static bool isSearchKeyword(string word);
	static Date* Parser::parseTimeString(string timeStr);
	static int parseDayName(string dayName);
	static int parseMonthName(string monthName);

	static char buffer[255];
	static const int INVALID_NUMBER_FORMAT = -1;
	static const string Parser::ERROR_MESSAGE_PARSING_ADD;
	static const string Parser::ERROR_MESSAGE_PARSING_UPDATEARGUMENTS;
	static const string Parser::ERROR_MESSAGE_PARSING_RECURRENCE;
	static const string Parser::ERROR_MESSAGE_PARSING_PRIORITY;
	static const string Parser::ERROR_MESSAGE_PARSING_DATEPASSED;
	static const string Parser::ERROR_MESSAGE_PARSING_DAYNAME;
	static const string Parser::ERROR_MESSAGE_PARSING_MONTHNAME;
	static const string Parser::ERROR_MESSAGE_COMMAND_ENDTIME;
	static const string Parser::ERROR_MESSAGE_PARSING_TASK;
	static const string Parser::ERROR_MESSAGE_DELETE_TASKNUM;

private:
	static int _taskNumber;
	static string _taskDetails;
	static Date *_taskStartTime;
	static Date *_taskEndTime;
	static Date *_taskDeadline;
	static Task::Priority _taskPriority;
	static string _duration;
	static bool _taskMarked;
	static bool _foundMarked;
	static bool _foundPriority;
};
