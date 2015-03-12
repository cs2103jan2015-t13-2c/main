#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Task.h"

using namespace std;

class MainLogic {
public:
	enum COMMAND_TYPE {
		CREATE, READ, UPDATE, DELETE, CLEAR, SORT, SEARCH, EXIT, INVALID,	//Main commands
		DEADLINE, PRIORITY, RECURRENCE										//Create sub-commands
	};


	static string processUserInput(string command);

	static vector<Task> TaskList;

private:
	//The Vector
	static vector<Task> TaskVector;

	//Command Parsers
	static COMMAND_TYPE determineCommandType(string commandTypeString);
	static string determineContent(string command);
	static string removeWords(string command, string content);
	static string getFirstWord(string userCommand);
	static string removeFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);

	static string processCommand(COMMAND_TYPE commandType, string content);

	//Processing Functions
	static string createTask(string userCommand);
	static Task::Priority determinePriority(string command);
	static Task::Recurrence determineRecurrence(string command);
	static chrono::system_clock::time_point determineTime(string command);
	static string readTask(string userCommand);
	static string updateTask(string userCommand);
	static string deleteTask(string userCommand);
	static string clear();
	static string sortTask();
	static string searchTask(string userCommand);

	//This is to indicate wrong user input
	static const string MESSAGE_INVALID_FORMAT;

	static const int INVALID_NUMBER_FORMAT = -1;

	static const int BUFFER_SIZE = 255;
	static char buffer[BUFFER_SIZE];

	//Useful functions
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);
	template <typename T, size_t N> inline static size_t sizeOfArray(const T(&)[N]);

	static string asString(const std::chrono::system_clock::time_point& tp);
	static chrono::system_clock::time_point makeTimePoint(int year, int mon, int day, int hour, int min);

};

