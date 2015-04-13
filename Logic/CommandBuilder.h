//@author A0122357L

#pragma once
#include <string>
#include "Command.h"
#include "Task.h"
#include <vector>
#include <sstream>
#include "CommandAdd.h"
#include "CommandInvalid.h"
#include "CommandDisplay.h"
#include "Parser.h"
#include "CommandUpdate.h"
#include "CommandDelete.h"
#include "CommandExit.h"
#include "CommandUndo.h"
#include "CommandMark.h"
#include "CommandUnmark.h"
#include "CommandSearch.h"
#include "CommandChangeFileLocation.h"
#include "CommandCheckFileLocation.h"

using namespace std;

class CommandBuilder
{
public:

	enum CommandType {
		Add, Display, Update, Delete, Exit, Invalid, Undo, Mark, Unmark,
		Search, Sort, CheckFileLocation, ChangeFileLocation
	};

	CommandBuilder();

	void clearPreviousCommand();

	Command* parseCommand(string userInput);

	static CommandBuilder::CommandType determineCommandType(string commandTypeString);

	string getTaskDetails();
	Date* getTaskStartTime();
	Date* getTaskEndTime();
	Date* getTaskDeadline();
	Task::Priority getTaskPriority();
	string getDuration();
	bool getTaskMarked();
	int getTaskNumber();

	void setAttributesFromParser(Parser parser);


	//helper functions
	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);

	static char buffer[255];
	static const string CommandBuilder::INVALID_MESSAGE_FORMAT;
	static const int INVALID_NUMBER_FORMAT = -1;
	static const string MESSAGE_PROGRAM_TERMINATION;
	static const string ERROR_UNRECOGNISED_COMMAND_TYPE;


private:
	int _taskNumber;
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Priority _taskPriority;
	string _duration;
	bool _taskMarked;
	bool _foundMarked;
	bool _foundPriority;
};

