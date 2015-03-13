#ifndef MAINLOGIC_H_
#define MAINLOGIC_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "Task.h"

using namespace std;

class Taskky {
public:
	// These are the possible command types
	enum CommandType {
		Add, Display, Update, Delete, Exit, Invalid
	};
	
	static void Taskky::main();
	static string executeCommand(string userCommand, vector<Task> &tempSave, string fileName);

	static string asString(const std::chrono::system_clock::time_point& tp);
	static chrono::system_clock::time_point makeTimePoint(int year, int mon, int day, int hour, int min);
	
private:
	static CommandType determineCommandType(string commandTypeString);
	static string addTask(string userCommand, vector<Task> &tempSave);
	static string displayTask(string userCommand, vector<Task> &tempSave);
	static string updateTask(string userCommand, vector<Task> &tempSave);
	static string deleteTask(string userCommand, vector<Task> &tempSave);
	static void loadfromFile(vector<Task> &tempSave, string fileName);
	static void writetoFile(vector<Task> tempSave, string fileName);
			
	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);
	static chrono::system_clock::time_point parseTime(string timeStr);
	
	static const string WELCOME_MESSAGE;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_UPDATED;
	static const string MESSAGE_DELETED;
	static const string INVALID_MESSAGE_FORMAT;
	static const string MESSAGE_PROGRAM_TERMINATION;
	
	static const string ERROR_UNRECOGNISED_COMMAND_TYPE;
	static const int INVALID_NUMBER_FORMAT = -1;
			
	static void printWelcomeMessage();
	static void showToUser(string text);
			
	static char buffer[255];
	};












#endif