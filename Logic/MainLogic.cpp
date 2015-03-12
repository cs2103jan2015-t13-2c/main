#include "MainLogic.h"

using namespace std;

//boo

/*******************
Message declarations
*******************/
const string MainLogic::MESSAGE_INVALID_FORMAT = "Invalid command format.";
char MainLogic::buffer[BUFFER_SIZE];
vector<Task> MainLogic::TaskVector;


/**************
Command Parsers
**************/
string MainLogic::processUserInput(string command) {
	//determine which command

	COMMAND_TYPE commandType = determineCommandType(getFirstWord(command));
	return processCommand(commandType, command);

}



string MainLogic::processCommand(MainLogic::COMMAND_TYPE commandType, string command){
	switch (commandType) {
	case CREATE:
		return createTask(command);
	case READ:
		return readTask(command);
	case UPDATE:
		return updateTask(command);
	case DELETE:
		return deleteTask(command);
	case CLEAR:
		return clear();
	case SORT:
		return sortTask();
	case SEARCH:
		return searchTask(command);
	case INVALID:
	{
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str());
		return buffer;
	}
	case EXIT:
		exit(0);
	}
}



MainLogic::COMMAND_TYPE MainLogic::determineCommandType(string commandTypeString) {

	// In C++, we do not need to check if the string is null if it is not declare as a pointer
	if (equalsIgnoreCase(commandTypeString, "add")) {
		return COMMAND_TYPE::CREATE;
	}
	else if (equalsIgnoreCase(commandTypeString, "read")) {
		return COMMAND_TYPE::READ;
	}
	else if (equalsIgnoreCase(commandTypeString, "update")) {
		return COMMAND_TYPE::UPDATE;
	}
	else if (equalsIgnoreCase(commandTypeString, "exit")) {
		return COMMAND_TYPE::EXIT;
	}
	else if (equalsIgnoreCase(commandTypeString, "delete")) {
		return COMMAND_TYPE::DELETE;
	}
	else if (equalsIgnoreCase(commandTypeString, "clear")) {
		return COMMAND_TYPE::CLEAR;
	}
	else if (equalsIgnoreCase(commandTypeString, "sort")) {
		return COMMAND_TYPE::SORT;
	}
	else if (equalsIgnoreCase(commandTypeString, "search")) {
		return COMMAND_TYPE::SEARCH;
	}
	else if (equalsIgnoreCase(commandTypeString, "deadline")) {
		return COMMAND_TYPE::DEADLINE;
	}
	else if (equalsIgnoreCase(commandTypeString, "priority")) {
		return COMMAND_TYPE::PRIORITY;
	}
	else if (equalsIgnoreCase(commandTypeString, "recurrence")) {
		return COMMAND_TYPE::RECURRENCE;
	}
	else {
		return COMMAND_TYPE::INVALID;
	}
}

/*******************
Processing Functions
*******************/
string MainLogic::createTask(string command) {

	/* User can enter task in 3 different formats:

	1. timed tasks
	e.g. add chinese new year deadline from 19 February 2015 to 21 February 2015

	2. tasks with deadlines
	e.g add project meeting deadline 10 July 2015 5pm

	3. floating tasks
	e.g add finish coding assignment
	*/

	/*
	Task newTask;
	//newTask.setNumber(taskList.size());
	string text = Logic::removeFirstWord(userCommand);

	vector<string> info = Logic::splitParameters(text);

	vector<string>::iterator iter;
	for (iter = info.begin(); iter != info.end(); iter++) {
	string keyWord = Logic::getFirstWord(*iter);

	}
	*/

	command = removeFirstWord(command);
	string taskname = determineContent(command);
	command = removeWords(command, taskname);
	
	Task::Priority priority = Task::Priority::NORMAL;
	Task::Recurrence recurrence = Task::Recurrence::NONE;
	chrono::system_clock::time_point start_time = makeTimePoint(1111, 0, 0, 0, 0);
	chrono::system_clock::time_point end_time = makeTimePoint(1111, 0, 0, 0, 0);
	chrono::system_clock::time_point deadline_time = makeTimePoint(1111, 0, 0, 0, 0);
	chrono::system_clock::time_point time_reference = makeTimePoint(1111, 0, 0, 0, 0);

	while (command != "") {
		COMMAND_TYPE subCreate = determineCommandType(getFirstWord(command));
		switch (subCreate) {
		case PRIORITY:
		{
			Task::Priority priority = determinePriority(command);
			command = removeFirstWord(command);
			command = removeFirstWord(command);
		}
		case RECURRENCE:
		{
			Task::Recurrence recurrence = determineRecurrence(command);
			command = removeFirstWord(command);
			command = removeFirstWord(command);
		}
		case DEADLINE:
		{
			if (getFirstWord(command) == "from") {
				start_time = determineTime(command);
				while (getFirstWord(command) != "to") {
					removeFirstWord(command);
				}
				end_time = determineTime(command);
				command = removeFirstWord(command);
				command = removeWords(command, determineContent(command));
			}
			else {
				deadline_time = determineTime(command);
			}
		}
		}
	}

	if (start_time == time_reference) {
		if (deadline_time == time_reference) {
			Task newTask = Task::Task(taskname, priority);
			TaskVector.push_back(newTask);
		}
		else {
			Task newTask = Task::Task(taskname, priority, recurrence, deadline_time);
			TaskVector.push_back(newTask);
		}
	}
	else
	{
		Task newTask = Task::Task(taskname, priority, recurrence, start_time, end_time);
		TaskVector.push_back(newTask);
	}

	return "added task " + taskname + " to Taskky\n";
}

chrono::system_clock::time_point MainLogic::determineTime(string command) {
	command = removeFirstWord(command);
	string date_str = getFirstWord(command);
	int date_int = atoi(date_str.c_str());

	int month;
	command = removeFirstWord(command);
	if (getFirstWord(command) == "january") {
		month = 0;
	}
	else if (getFirstWord(command) == "february") {
		month = 1;
	}
	else if (getFirstWord(command) == "march") {
		month = 2;
	}
	else if(getFirstWord(command) == "april") {
		month = 3;
	}
	else if (getFirstWord(command) == "may") {
		month = 4;
	}
	else if (getFirstWord(command) == "june") {
		month = 5;
	}
	else if (getFirstWord(command) == "july") {
		month = 6;
	}
	else if (getFirstWord(command) == "august") {
		month = 7;
	}
	else if (getFirstWord(command) == "september") {
		month = 8;
	}
	else if (getFirstWord(command) == "october") {
		month = 9;
	}
	else if (getFirstWord(command) == "november") {
		month = 10;
	}
	else if (getFirstWord(command) == "december") {
		month = 11;
	}

	command = removeFirstWord(command);
	string year_str = getFirstWord(command);
	int year_int = atoi(year_str.c_str());

	command = removeFirstWord(command);
	string time_str = getFirstWord(command);
	int time_int = atoi(time_str.c_str());
	int hours = time_int / 100;
	int minutes = time_int % 100;

	chrono::system_clock::time_point timepoint = makeTimePoint(year_int, month, date_int, hours, minutes);
	return timepoint;

}

Task::Priority MainLogic::determinePriority(string command) {
	command = removeFirstWord(command);
	if (getFirstWord(command) == "high") {
		return Task::Priority::HIGH;
	}
	else if (getFirstWord(command) == "normal") {
		return Task::Priority::NORMAL;
	}
	else if (getFirstWord(command) == "low") {
		return Task::Priority::LOW;
	}
}

Task::Recurrence MainLogic::determineRecurrence(string command) {
	command = removeFirstWord(command);
	if (getFirstWord(command) == "day") {
		return Task::Recurrence::DAY;
	}
	else if (getFirstWord(command) == "week") {
		return Task::Recurrence::WEEK;
	}
	else if (getFirstWord(command) == "month") {
		return Task::Recurrence::MONTH;
	}
	else {
		return Task::Recurrence::NONE;
	}
}

string MainLogic::removeWords(string command, string content){
	size_t pos;

	if ((pos = command.find(content)) != string::npos) {
		command.erase(pos, content.length());
	}

	return command;
}

string MainLogic::determineContent(string command){
	ostringstream oss;

	command = removeFirstWord(command);

	bool isCommandWord = false;
	while (isCommandWord == false) {
		if (determineCommandType(getFirstWord(command)) == MainLogic::COMMAND_TYPE::INVALID) {
			oss << getFirstWord(command);
			command = removeFirstWord(command);
			if (command == "") {
				isCommandWord = true;
			}
			else if (determineCommandType(getFirstWord(command)) == MainLogic::COMMAND_TYPE::INVALID) {
				oss << " ";
			}
		}
		else {
			isCommandWord = true;
		}
	}

	return oss.str();
}

string MainLogic::readTask(string userCommand) {
	return "0";
}

string MainLogic::updateTask(string userCommand) {
	return "0";
}

string MainLogic::deleteTask(string userCommand) {
	return "0";
}

string MainLogic::clear() {
	return "0";
}

string MainLogic::sortTask() {
	return "0";
}

string MainLogic::searchTask(string userCommand) {
	return "0";
}

/***************
Useful Functions
***************/

string MainLogic::getFirstWord(string userCommand){
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

string MainLogic::removeFirstWord(string userCommand){
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

// This method only split string based on delimiter space
vector<string> MainLogic::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

bool MainLogic::equalsIgnoreCase(const string& str1, const string& str2) {
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

int MainLogic::parseInt(string str) {
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

string MainLogic::replace(string a, string b, string c) {
	int pos;
	do
	{
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}

inline string MainLogic::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string MainLogic::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string MainLogic::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		return trim_left(trim_right(s, delimiters), delimiters);
	else
		return s;
}

template <typename T, size_t N> inline size_t
MainLogic::sizeOfArray(const T(&)[N]) {
	return N;
}

/**********
Time Parser
**********/

std::string MainLogic::asString(const std::chrono::system_clock::time_point& tp)
{
	// convert to system time:
	std::time_t t = std::chrono::system_clock::to_time_t(tp);
	std::string ts = ctime(&t);   // convert to calendar time
	ts.resize(ts.size() - 1);       // skip trailing newline
	return ts;
}
// convert calendar time to timepoint of system clock
chrono::system_clock::time_point MainLogic::makeTimePoint(int year, int mon, int day, int hour, int min)
{
	int sec = 0;

	struct std::tm t;
	t.tm_sec = sec;        // second of minute (0 .. 59 and 60 for leap seconds)
	t.tm_min = min;        // minute of hour (0 .. 59)
	t.tm_hour = hour;      // hour of day (0 .. 23)
	t.tm_mday = day;       // day of month (0 .. 31)
	t.tm_mon = mon - 1;      // month of year (0 .. 11)
	t.tm_year = year - 1900; // year since 1900
	t.tm_isdst = -1;       // determine whether daylight saving time
	std::time_t tt = std::mktime(&t);
	if (tt == -1) {
		throw "no valid system time";
	}
	return std::chrono::system_clock::from_time_t(tt);
}