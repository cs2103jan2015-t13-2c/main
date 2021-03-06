//@author A0113716M
/*
This class is to parse the command line for TASKKY.

The parser will parse the user command differently depending on the 
keyword(ADD, UPDATE, DELETE, etc.), and return the necessary parameters 
to the Command Builder. 

For example, calling "add task by 10 may" will return _taskDetails = "task" 
and _taskDeadline = "10 may" to the Command Builder, which will create a 
task based on these parameters.
*/

#include "Parser.h"

int Parser::_taskNumber;
string Parser::_taskDetails;
Date* Parser::_taskStartTime = nullptr;
Date* Parser::_taskEndTime = nullptr;
Date* Parser::_taskDeadline = nullptr;
Task::Priority Parser::_taskPriority = Task::NORMAL;
string Parser::_duration;
bool Parser::_taskMarked;
bool Parser::_foundMarked;
bool Parser::_foundPriority;

/*
* ====================================================================
*  Parser for Command Add
* ====================================================================
*/
void Parser::parseCommandAdd(string userCommand){
	Parser::clearPreviousParse();
	TaskManager* taskManagerInstance = TaskManager::getInstance();

	string text = removeFirstWord(userCommand);
	if (text == ""){
		throw ParseException(ERROR_MESSAGE_PARSING_ADD);
	}
	vector<string> textVec = splitParameters(text);
	textVec.push_back("\n");	//Represents the end of vector

	string timeString;
	ostringstream temp;
	vector<string>::iterator iter = textVec.begin();


	//Adding task details
	while (!isKeyword(*iter)){
		temp << *iter << " ";
		iter++;
	};
	if (temp.str() == ""){
		throw ParseException(ERROR_MESSAGE_PARSING_TASK);
	}
	_taskDetails = temp.str();
	temp.str("");

	//Adding task deadline (if it is deadline task)
	if (equalsIgnoreCase(*iter, "by")){
		iter++;
		while (!isKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskDeadline = parseTimeString(timeString);
		temp.str("");
	}

	//Adding task start time (if it is timed task)
	if (equalsIgnoreCase(*iter, "from")){
		iter++;
		while (!equalsIgnoreCase(*iter, "to")){
			if (iter == textVec.end()){
				throw CommandException(ERROR_MESSAGE_NOENDTIME);
			}
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskStartTime = parseTimeString(timeString);
		temp.str("");

		//Adding task end time
		iter++;
		while (!isKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskEndTime = parseTimeString(timeString);
		if (_taskEndTime->isEarlierThan(*(_taskStartTime)) == 1){
			throw CommandException(ERROR_MESSAGE_INVALIDENDTIME);
		}
		temp.str("");
	}

	//Adding task priority
	if (equalsIgnoreCase(*iter, "#impt") || equalsIgnoreCase(*iter, "#high")){
		_taskPriority = Task::Priority::HIGH;
	} 
}

/*
* ====================================================================
*  Parser for Command Update
* ====================================================================
*/
void Parser::parseCommandUpdate(string userCommand){
	Parser::clearPreviousParse();

	ostringstream oss;
	string text = removeFirstWord(userCommand);
	if (text == ""){
		throw ParseException(ERROR_MESSAGE_PARSING_UPDATE);
	}

	//Getting the task to change
	string taskNumberStr = getFirstWord(text);
	Parser::_taskNumber = atoi(taskNumberStr.c_str());
	Task taskToChange = TaskManager::getTask(Parser::_taskNumber);

	_taskDetails = taskToChange.getTaskDetails();
	_taskDeadline = taskToChange.getTaskDeadline();
	_taskStartTime = taskToChange.getTaskStartTime();
	_taskEndTime = taskToChange.getTaskEndTime();
	_taskPriority = taskToChange.getTaskPriority();

	//Getting the attribute to change
	text = removeFirstWord(text);
	toLowerCase(text);
	if (text == ""){
		throw ParseException(ERROR_MESSAGE_PARSING_UPDATEARGUMENTS);
	}
	string attributeToChange = getFirstWord(text);

	//Getting the details to change
	string updatedStr;
	text = removeFirstWord(text);
	if (text == ""){
		throw ParseException(ERROR_MESSAGE_PARSING_MISSINGDETAILS);
	}
	updatedStr = text;


	//Changes are made here
	if (attributeToChange == "details"){
		_taskDetails = updatedStr+" ";
	} 
	else if (attributeToChange == "deadline"){
		_taskDeadline = (parseTimeString(updatedStr+" "));
	} 
	else if (attributeToChange == "starttime"){
		_taskStartTime = (parseTimeString(updatedStr+" "));
	} 
	else if (attributeToChange == "endtime"){
		_taskEndTime = (parseTimeString(updatedStr+" "));
	} 
	else if (attributeToChange == "priority"){
		if (updatedStr == "normal"){
			_taskPriority = Task::Priority::NORMAL;
		} else if (updatedStr == "high"){
			_taskPriority = Task::Priority::HIGH;
		} else{
			throw ParseException(ERROR_MESSAGE_PARSING_PRIORITY);
		}
	}
	else {
		throw ParseException(ERROR_MESSAGE_PARSING_UPDATEARGUMENTS);
	}
}

/*
* ====================================================================
*  Parser for Command Delete
* ====================================================================
*/
void Parser::parseCommandDelete(string userCommand){
	Parser::clearPreviousParse();

	string text = removeFirstWord(userCommand);
// -------------------------Error Catching-------------------------------
	if (text == "")
		throw ParseException(ERROR_MESSAGE_DELETE_TASKNUM);
// ----------------------------------------------------------------------

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

/*
* ====================================================================
*  Parser for Command Mark
* ====================================================================
*/
void Parser::parseCommandMark(string userCommand){
	Parser::clearPreviousParse();

	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

/*
* ====================================================================
*  Parser for Command Unmark
* ====================================================================
*/
void Parser::parseCommandUnmark(string userCommand){
	Parser::clearPreviousParse();

	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

//@author A0122357L
/*
* ====================================================================
*  Parser for Command Search
* ====================================================================
*/
void Parser::parseCommandSearch(string userCommand){

	string text = removeFirstWord(userCommand);
	toLowerCase(text);
	vector<string> textVec = splitParameters(text);
	textVec.push_back("\n");	//Represents the end of vector

	string timeString;
	ostringstream temp;
	vector<string>::iterator iter = textVec.begin();

	//Search using task details
	while (!isSearchKeyword(*iter)){
		temp << *iter << " ";
		iter++;
	};
	_taskDetails = temp.str();
	temp.str("");

	//Search using task start time 
	if (equalsIgnoreCase(*iter, "from")){
		iter++;
		while (!equalsIgnoreCase(*iter, "to")){
			temp << *iter << " ";
			iter++;

			if (iter == textVec.end()){
				throw CommandException(ERROR_MESSAGE_NOENDTIME);
			}
		};
		timeString = temp.str();
		_taskStartTime = parseTimeString(timeString);
		temp.str("");

		//Search using task end time
		iter++;
		while (!isSearchKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskEndTime = parseTimeString(timeString);
		temp.str("");
	}

	//Search for tasks before a certain date
	if (equalsIgnoreCase(*iter, "before")){
		iter++;
		while (!isSearchKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskEndTime = parseTimeString(timeString);
		temp.str("");
	}

	//Search for tasks after a certain date
	if (equalsIgnoreCase(*iter, "after")){
		iter++;
		while (!isSearchKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		};
		timeString = temp.str();
		_taskStartTime = parseTimeString(timeString);
		temp.str("");
	}

	//Search for marked/unmarked tasks
	if (equalsIgnoreCase(*iter, "done")){
		_taskMarked = true;
		_foundMarked = true;
	} else if (equalsIgnoreCase(*iter, "undone")){
		_taskMarked = false;
		_foundMarked = true;
	}

	//Search using priority
	if (equalsIgnoreCase(*iter, "#impt") || equalsIgnoreCase(*iter, "#high")){
		_taskPriority = Task::Priority::HIGH;
		_foundPriority = true;
	} 

	//Search for next available timeslot
	if (equalsIgnoreCase(*iter, "next")){
		iter++;
		if (equalsIgnoreCase(*iter, "available")) {
			iter++;
		}
		while (!isSearchKeyword(*iter)){
			temp << *iter << " ";
			iter++;
		}
		_duration = temp.str();
	}
}

/*
* ====================================================================
*  Parser for Command Changefileloc
* ====================================================================
*/
void Parser::parseCommandChangeFileLocation(string userCommand){
	Parser::clearPreviousParse();

	string text = removeFirstWord(userCommand);
	_taskDetails = text;
}


//@author A0113716M -reused
/*
* ====================================================================
*  Additional functions
* ====================================================================
*/
string Parser::removeFirstWord(string userCommand){
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string Parser::getFirstWord(string userCommand){
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

void Parser::toLowerCase(string &text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
}

// This method only split string based on delimiter space
vector<string> Parser::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string Parser::trim_right(const string& s, const string& delimiters){
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string Parser::trim_left(const string& s, const string& delimiters){
	if (countWordsInString(s) == 0){
		return "";
	}
	return s.substr(s.find_first_not_of(delimiters));
}

unsigned int Parser::countWordsInString(const string& str)
{
	std::stringstream stream(str);
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

inline string Parser::trim(const string& s, const string& delimiters){
	if (!s.empty()){
		return trim_left(trim_right(s, delimiters), delimiters);
	} else{
		return s;
	}
}

bool Parser::equalsIgnoreCase(const string& str1, const string& str2){
	if (str1.size() != str2.size()){
		return false;
	}
	for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2){
		if (tolower(*c1) != tolower(*c2)){
			return false;
		}
	}
	return true;
}

int Parser::parseInt(string str){
	char c;
	int i = 0;
	std::stringstream ss(str);
	ss >> i;
	if (ss.fail() || ss.get(c)){
		return INVALID_NUMBER_FORMAT;
	} else{
		return i;
	}
}

string Parser::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}

//@author A0113716M
bool Parser::isKeyword(string word){
	return (equalsIgnoreCase(word, "by") || equalsIgnoreCase(word, "from") || 
			equalsIgnoreCase(word, "#impt") || equalsIgnoreCase(word, "#high") ||
			word == "\n");
}

bool Parser::isSearchKeyword(string word){
	return (equalsIgnoreCase(word, "by") || equalsIgnoreCase(word, "from") ||
			equalsIgnoreCase(word, "#impt") || equalsIgnoreCase(word, "#high") ||
			equalsIgnoreCase(word, "before") || equalsIgnoreCase(word, "after") ||
			equalsIgnoreCase(word, "done") || equalsIgnoreCase(word, "undone") ||
			equalsIgnoreCase(word, "next") || word == "\n");
}

Date* Parser::parseTimeString(string timeStr){
	if (timeStr == ""){
		throw CommandException(ERROR_MESSAGE_PARSING_INVALIDTIME);
	}
	toLowerCase(timeStr);
		
	int year = Date().getYear();
	int mon(0); 
	int day(0); 
	int hour(12);
	int minute(0);
	string temp;

	temp = getFirstWord(timeStr);

	//E.g. User types in "today"
	if (temp == "today"){
		mon = Date().getMonth();
		day = Date().getDay();
	}

	//E.g. User types in "tomorrow"
	else if (temp == "tomorrow"){
		mon = Date().getMonth();
		day = Date().getDay() + 1;
	}

	//E.g. User types in "this thursday"
	else if (temp == "this"){
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		temp = (getFirstWord(timeStr));
		int taskDay = parseDayName(temp);
		int diffinDays = taskDay - Date().getDayName();
		//If date has passed, refer to next week
		if (diffinDays < 0){
			diffinDays = diffinDays + 7;
		}

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;
	}

	//E.g. User types in "next thursday"
	else if (temp == "next"){
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		temp = (getFirstWord(timeStr));
		int taskDay = parseDayName(temp);
		int diffinDays = taskDay - Date().getDayName() + 7;

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;
	}

	//E.g. User types in "9 apr"
	else {
		day = parseInt(temp);

		if (day > 31 || day < 0){
			throw CommandException(ERROR_MESSAGE_PARSING_INVALIDTIME);
		}

		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		if (timeStr == ""){
			throw CommandException(ERROR_MESSAGE_PARSING_INVALIDTIME);
		}

		temp = (getFirstWord(timeStr));
		mon = parseMonthName(temp);
	}

	timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
	if (timeStr != "") {
		temp = getFirstWord(timeStr);
	} else {
		if (mon < Date().getMonth()){
			++year;
		}
		else if (mon == Date().getMonth()){
			if (day < Date().getDay()){
				++year;
			}
		}
		return (new Date(year, mon, day, hour, minute));
	}

	//Checks if user keyed in a year (Default is set to current year)
	if (parseInt(temp) != -1) {
		year = parseInt(temp);

		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		if (timeStr != "") {
			temp = getFirstWord(timeStr);
		} else{
			return (new Date(year, mon, day, hour, minute));
		}
	}

	bool isTime = parseTime(temp, hour, minute);
	if (!isTime){
		throw ParseException(ERROR_MESSAGE_PARSING_INVALIDTIME);
	}
	return (new Date(year, mon, day, hour, minute));
}

int Parser::parseDayName(string dayName) {
	int day = 0;

	if (dayName == "sunday" || dayName == "sun") {
		day = 0;
	} else if (dayName == "monday" || dayName == "mon") {
		day = 1;
	} else if (dayName == "tuesday" || dayName == "tue" || dayName == "tues") {
		day = 2;
	} else if (dayName == "wednesday" || dayName == "wed") {
		day = 3;
	} else if (dayName == "thursday" || dayName == "thu" || dayName == "thurs") {
		day = 4;
	} else if (dayName == "friday" || dayName == "fri") {
		day = 5;
	} else if (dayName == "saturday" || dayName == "sat") {
		day = 6;
	} else {
		throw ParseException(ERROR_MESSAGE_PARSING_DAYNAME);
	}
	return day;
}

int Parser::parseMonthName(string monthName) {
	int mon = 0;

	if (monthName == "january" || monthName == "jan") {
		mon = 0;
	} else if (monthName == "february" || monthName == "feb") {
		mon = 1;
	} else if (monthName == "march" || monthName == "mar") {
		mon = 2;
	} else if (monthName == "april" || monthName == "apr") {
		mon = 3;
	} else if (monthName == "may") {
		mon = 4;
	} else if (monthName == "june" || monthName == "jun") {
		mon = 5;
	} else if (monthName == "july" || monthName == "jul") {
		mon = 6;
	} else if (monthName == "august" || monthName == "aug") {
		mon = 7;
	} else if (monthName == "september" || monthName == "sep") {
		mon = 8;
	} else if (monthName == "october" || monthName == "oct") {
		mon = 9;
	} else if (monthName == "november" || monthName == "nov") {
		mon = 10;
	} else if (monthName == "december" || monthName == "dec") {
		mon = 11;
	} else {
		throw ParseException(ERROR_MESSAGE_PARSING_MONTHNAME);
	}
	return mon;
}

bool Parser::parseTime(string time, int &hour, int &minute){
	hour = 0;
	minute = 0;

	//Checks if time is in AM/PM 
	bool afterNoon = false;
	if (time.find("pm") != string::npos) {
		afterNoon = true;
	}

	char chars[] = ".:apmhrs";
	for (unsigned int i = 0; i < strlen(chars); ++i) {
		time.erase(remove(time.begin(), time.end(), chars[i]), time.end());
	}
	int t = parseInt(time);
	if (t == -1){
		return false;
	}

	//Checks if time is in format 12pm or 12:00pm
	if (t / 100 == 0) {
		hour = t % 100;
	} else {
		hour = t / 100;
		minute = t % 100;
	}

	if (hour < 12 && afterNoon){
		hour += 12;
	}
	if (hour == 12 && !afterNoon){
		hour = 0;
	}

	return true;
}


/*
* ====================================================================
*  Parser Initialization
* ====================================================================
*/
Parser::Parser(){
	clearPreviousParse();
}

void Parser::clearPreviousParse(){
	_taskDetails = "";
	_taskStartTime = 0;
	_taskEndTime = 0;
	_taskDeadline = 0;
	_taskPriority = Task::NORMAL;
	_taskMarked = false;
	_taskNumber = -1;
	_foundMarked = false;
	_foundPriority = false;
}

string Parser::getTaskDetails(){
	return _taskDetails;
}

Date* Parser::getTaskStartTime(){
	return _taskStartTime;
}

Date* Parser::getTaskEndTime(){
	return _taskEndTime;
}

Date* Parser::getTaskDeadline(){
	return _taskDeadline;
}

Task::Priority Parser::getTaskPriority(){
	return _taskPriority;
}

string Parser::getDuration(){
	return _duration;
}

bool Parser::getTaskMarked(){
	return _taskMarked;
}

int Parser::getTaskNumber(){
	return _taskNumber;
}

bool Parser::getFoundMarked(){
	return _foundMarked;
}

bool Parser::getFoundPriority(){
	return _foundPriority;
}

Parser::~Parser(){
}


/*
* ====================================================================
*  Error Messages
* ====================================================================
*/
const string Parser::ERROR_MESSAGE_PARSING_ADD = "There is no task to add"; 
const string Parser::ERROR_MESSAGE_PARSING_UPDATE = "Please enter a task number to update";
const string Parser::ERROR_MESSAGE_PARSING_UPDATEARGUMENTS = "There are no arguments to update";
const string Parser::ERROR_MESSAGE_PARSING_MISSINGDETAILS = "Task details cannot be empty";
const string Parser::ERROR_MESSAGE_PARSING_PRIORITY = "Please enter a valid Priority (LOW, NORMAL, HIGH)";
const string Parser::ERROR_MESSAGE_PARSING_DATEPASSED = "This date has already passed";
const string Parser::ERROR_MESSAGE_PARSING_DAYNAME = "Day is invalid";
const string Parser::ERROR_MESSAGE_PARSING_MONTHNAME = "Month is invalid";
const string Parser::ERROR_MESSAGE_PARSING_INVALIDTIME = "Time is invalid";
const string Parser::ERROR_MESSAGE_NOENDTIME = "Please enter the ending time!";
const string Parser::ERROR_MESSAGE_INVALIDENDTIME = "End time must be after start time!";
const string Parser::ERROR_MESSAGE_PARSING_TASK = "Please enter a task to add!";
const string Parser::ERROR_MESSAGE_DELETE_TASKNUM = "Please enter a task number to delete";