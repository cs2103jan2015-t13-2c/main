#include "CommandBuilder.h"



CommandBuilder::CommandBuilder()
{
	clearPreviousCommand();
}


CommandBuilder::~CommandBuilder()
{
}

void CommandBuilder::clearPreviousCommand(){
	_taskDetails = "";
	_taskStartTime = NULL;
	_taskEndTime = NULL;
	_taskDeadline = NULL;
	_taskRecurrence = Task::NONE;
	_taskPriority = Task::NORMAL;
	_taskMarked = false;
	_taskNumber = -1;
}

string CommandBuilder::getTaskDetails(){
	return _taskDetails;
}

Date* CommandBuilder::getTaskStartTime(){
	return _taskStartTime;
}

Date* CommandBuilder::getTaskEndTime(){
	return _taskEndTime;
}

Date* CommandBuilder::getTaskDeadline(){
	return _taskDeadline;
}

Task::Recurrence CommandBuilder::getTaskRecurrence(){
	return _taskRecurrence;
}

Task::Priority CommandBuilder::getTaskPriority(){
	return _taskPriority;
}

bool CommandBuilder::getTaskMarked(){
	return _taskMarked;
}

int CommandBuilder::getTaskNumber(){
	return _taskNumber;
}

void CommandBuilder::setAttributesFromParser(Parser parser){
	_taskDetails = parser.getTaskDetails();
	_taskStartTime = parser.getTaskStartTime();
	_taskEndTime = parser.getTaskEndTime();
	_taskDeadline = parser.getTaskDeadline();
	_taskRecurrence = parser.getTaskRecurrence();
	_taskPriority = parser.getTaskPriority();
	_taskMarked = parser.getTaskMarked();
	_taskNumber = parser.getTaskNumber();
}


Command* CommandBuilder::parseCommand(string userInput){
	if (trim(userInput) == "") {
		return new CommandInvalid(userInput);
	}

	string commandTypeString = getFirstWord(userInput);

	CommandType commandType = determineCommandType(commandTypeString);
	
	Parser parser = Parser::Parser();

	switch (commandType){

	case CommandType::Add:{

		//parser parses in the userInput into its attributes
		parser.parseCommandAdd(userInput);

		//command builder takes these from parser attributes and sets them as its own
		CommandBuilder::setAttributesFromParser(parser);

		return new CommandAdd(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline,
			_taskRecurrence, _taskPriority);
	}

	case CommandType::Display:{
		return new CommandDisplay();
	}

	case CommandType::Update:{

		parser.parseCommandUpdate(userInput);

		CommandBuilder::setAttributesFromParser(parser);

		return new CommandUpdate(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline,
			_taskRecurrence, _taskPriority, _taskNumber);
	}

	case CommandType::Delete:{

		parser.parseCommandDelete(userInput);

		CommandBuilder::setAttributesFromParser(parser);

		return new CommandDelete(_taskNumber);
	}

	case CommandType::Undo:

		return new CommandUndo();

	case CommandType::Mark:

		parser.parseCommandMark(userInput);

		CommandBuilder::setAttributesFromParser(parser);

		return new CommandMark(_taskNumber);

	case CommandType::Unmark:

		parser.parseCommandUnmark(userInput);

		CommandBuilder::setAttributesFromParser(parser);

		return new CommandUnmark(_taskNumber);

	case CommandType::Exit:

		return new CommandExit();

	case CommandType::Search:

		//return new CommandSort();

	default:
		return new CommandInvalid(userInput);
	}
}


//This operation determines which of the supported command types the user
//wants to perform (commandTypeString is the first word of the user command)
CommandBuilder::CommandType CommandBuilder::determineCommandType(string commandTypeString) {
	if (equalsIgnoreCase(commandTypeString, "add")) {
		return CommandType::Add;
	}
	else if (equalsIgnoreCase(commandTypeString, "display")) {
		return CommandType::Display;
	}
	else if (equalsIgnoreCase(commandTypeString, "update")) {
		return CommandType::Update;
	}
	else if (equalsIgnoreCase(commandTypeString, "delete")) {
		return CommandType::Delete;
	}
	else if (equalsIgnoreCase(commandTypeString, "exit")) {
		return CommandType::Exit;
	}
	else if (equalsIgnoreCase(commandTypeString, "undo")) {
		return CommandType::Undo;
	}
	else if (equalsIgnoreCase(commandTypeString, "mark")) {
		return CommandType::Mark;
	}
	else if (equalsIgnoreCase(commandTypeString, "unmark")) {
		return CommandType::Unmark;
	}
	else if (equalsIgnoreCase(commandTypeString, "sort")) {
		return CommandType::Unmark;
	}
	else if (equalsIgnoreCase(commandTypeString, "search")) {
		return CommandType::Unmark;
	}
	else {
		return CommandType::Invalid;
	}
}

/*
* ====================================================================
*  Additional functions
* ====================================================================
*/
string CommandBuilder::removeFirstWord(string userCommand) {
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string CommandBuilder::getFirstWord(string userCommand) {
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> CommandBuilder::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string CommandBuilder::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string CommandBuilder::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string CommandBuilder::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		return trim_left(trim_right(s, delimiters), delimiters);
	else
		return s;
}

bool CommandBuilder::equalsIgnoreCase(const string& str1, const string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
		if (tolower(*c1) != tolower(*c2)) {
			return false;
		}
	}
	return true;
}

int CommandBuilder::parseInt(string str) {
	char c;
	int i = 0;
	std::stringstream ss(str);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		return INVALID_NUMBER_FORMAT;
	}
	else {
		return i;
	}
}

string CommandBuilder::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}


char CommandBuilder::buffer[255];
const string CommandBuilder::INVALID_MESSAGE_FORMAT = "Invalid command format: %s";
const string CommandBuilder::MESSAGE_PROGRAM_TERMINATION = "Press any key to terminate the program . . .";
const string CommandBuilder::ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type";
