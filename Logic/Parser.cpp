#include "Parser.h"

int Parser::_taskNumber;
string Parser::_taskDetails;
Date* Parser::_taskStartTime = nullptr;
Date* Parser::_taskEndTime = nullptr;
Date* Parser::_taskDeadline = nullptr;
Task::Recurrence Parser::_taskRecurrence;
Task::Priority Parser::_taskPriority;
bool Parser::_taskMarked;

Parser::Parser(){
	clearPreviousParse();
}

void Parser::clearPreviousParse(){
	_taskDetails = "";
	_taskStartTime = 0;
	_taskEndTime = 0;
	_taskDeadline = 0;
	_taskRecurrence = Task::NONE;
	_taskPriority = Task::NORMAL;
	_taskMarked = false;
	_taskNumber = -1;
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

Task::Recurrence Parser::getTaskRecurrence(){
	return _taskRecurrence;
}

Task::Priority Parser::getTaskPriority(){
	return _taskPriority;
}

bool Parser::getTaskMarked(){
	return _taskMarked;
}

int Parser::getTaskNumber(){
	return _taskNumber;
}

Parser::~Parser(){
}

void Parser::parseCommandAdd(string userCommand){
	Parser::clearPreviousParse();
	TaskManager* taskManagerInstance = TaskManager::getInstance();

	string text = removeFirstWord(userCommand);
	string timeString;
	ostringstream temp;

	vector<string> textVec = splitParameters(text);
	textVec.push_back("\n");	//Represents the end of vector
	vector<string>::iterator iter = textVec.begin();

	//Adding task details
	while (!isKeyword(*iter)){
		temp << *iter << " ";
		iter++;
	};
	_taskDetails = temp.str();
	temp.str("");

	//Adding task deadline (if it is deadline task)
	if (*iter == "by"){
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
	if (*iter == "from"){
		iter++;
		while (*iter != "to"){
			temp << *iter << " ";
			iter++;

			if (*iter != "\n"){
				//throw error "enter end time"
			}
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
		temp.str("");
	}

	//Adding task recurrence
	if (*iter == "every"){
		iter++;
		if (*iter == "day"){
			_taskRecurrence = Task::Recurrence::DAY;
		}
		else if (*iter == "sunday" || *iter == "sun" ||
				*iter == "monday" || *iter == "mon" ||
				*iter == "tuesday" || *iter == "tue" || *iter == "tues" ||
				*iter == "wednesday" || *iter == "wed" ||
				*iter == "thursday" || *iter == "thu" || *iter == "thurs" ||
				*iter == "friday" || *iter == "fri" ||
				*iter == "saturday" || *iter == "sat") {
			_taskRecurrence = Task::Recurrence::WEEK;
		}
		else if (*iter == "january" || *iter == "jan" ||
				*iter == "february" || *iter == "feb" ||
				*iter == "march" || *iter == "mar" ||
				*iter == "april" || *iter == "apr" ||
				*iter == "may" ||
				*iter == "june" || *iter == "jun" ||
				*iter == "july" || *iter == "jul" ||
				*iter == "august" || *iter == "aug" ||
				*iter == "september" || *iter == "sep" ||
				*iter == "october" || *iter == "oct" ||
				*iter == "november" || *iter == "nov" ||
				*iter == "december" || *iter == "dec") {
			_taskRecurrence = Task::Recurrence::MONTH;
		}
		else{
			//throw error;
		}
		iter++;
	}

	//Adding task priority
	if (*iter == "#impt" || *iter == "#high"){
		_taskPriority = Task::Priority::HIGH;
	} else if (*iter == "#low"){
		_taskPriority = Task::Priority::LOW;
	}
}


void Parser::parseCommandUpdate(string userCommand){
	Parser::clearPreviousParse();

	ostringstream oss;
	string text = removeFirstWord(userCommand);

	//Getting the task to change
	string taskNumberStr = getFirstWord(text);
	Parser::_taskNumber = atoi(taskNumberStr.c_str());
	Task taskToChange = TaskManager::getTask(Parser::_taskNumber);

	_taskDetails = taskToChange.getTaskDetails();
	_taskDeadline = taskToChange.getTaskDeadline();
	_taskStartTime = taskToChange.getTaskStartTime();
	_taskEndTime = taskToChange.getTaskEndTime();
	_taskRecurrence = taskToChange.getTaskRecurrence();
	_taskPriority = taskToChange.getTaskPriority();

	//Getting the attribute to change
	text = removeFirstWord(text);
	string attributeToChange = getFirstWord(text);

	//User can either type in the changed version or program will prompt
	string updatedStr;
	text = removeFirstWord(text);

	if (text == ""){
		cout << "Enter new " << attributeToChange << ": ";
		getline(cin, updatedStr);
	}
	else{
		updatedStr = text;
	}

	//Changes are made here
	if (attributeToChange == "details"){
		_taskDetails = updatedStr;
	} 
	else if (attributeToChange == "deadline"){
		_taskDeadline = (parseTimeString(updatedStr));
	} 
	else if (attributeToChange == "starttime"){
		_taskStartTime = (parseTimeString(updatedStr));
	} 
	else if (attributeToChange == "endtime"){
		_taskEndTime = (parseTimeString(updatedStr));
	} 
	else if (attributeToChange == "recurrence"){
		if (updatedStr == "day" || updatedStr == "every day"){
			_taskRecurrence = Task::Recurrence::DAY;
		} else if (updatedStr == "week" || updatedStr == "every week"){
			_taskRecurrence = Task::Recurrence::WEEK;
		} else if (updatedStr == "month" || updatedStr == "every month"){
			_taskRecurrence = Task::Recurrence::MONTH;
		} else{
			//throw error
		}
	}
	else if (attributeToChange == "priority"){
		if (updatedStr == "low"){
			_taskPriority = Task::Priority::LOW;
		} else if (updatedStr == "normal"){
			_taskPriority = Task::Priority::NORMAL;
		} else if (updatedStr == "high"){
			_taskPriority = Task::Priority::HIGH;
		} else{
			//throw error
		}
	}
	else {
		//throw error
	}
}


void Parser::parseCommandDelete(string userCommand){
	Parser::clearPreviousParse();

	//get usercommand without the first word
	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

void Parser::parseCommandMark(string userCommand){
	Parser::clearPreviousParse();

	//get usercommand without the first word
	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

void Parser::parseCommandUnmark(string userCommand){
	Parser::clearPreviousParse();

	//get usercommand without the first word
	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	_taskNumber = atoi(task_number_str.c_str());
}

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
	return s.substr(s.find_first_not_of(delimiters));
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

bool Parser::isKeyword(string word){
	return (word == "by" || word == "from" || word == "every" || word == "#impt" ||
			word == "#high" || word == "#low" || word == "\n");
}

Date* Parser::parseTimeString(string timeStr){
	if (timeStr == ""){
		//throw error
	}
	
	int year = Date().getYear(),
		mon(0), day(0), hour(0), min(0);
	string temp;

	temp = getFirstWord(timeStr);

	//E.g. User types in "this thursday"
	if (temp == "this"){
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		temp = (getFirstWord(timeStr));
		int taskDay = parseDayName(temp);
		int diffinDays = taskDay - Date().getDayName();
		//throw error if negative

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;
	}

	//E.g. User types in "next thursday"
	else if (temp == "next"){
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		temp = (getFirstWord(timeStr));
		int taskDay = parseDayName(temp);
		int diffinDays = taskDay - Date().getDayName() + 7;
		//throw error if negative

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;
	}

	//E.g. User types in "9 apr"
	else {
		day = parseInt(temp);
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		temp = (getFirstWord(timeStr));
		mon = parseMonthName(temp);
	}

	timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
	if (timeStr != "") {
		temp = getFirstWord(timeStr);
	} else {
		return (new Date(year, mon, day, hour, min));
	}

	//Checks if user keyed in a year (Default is set to current year)
	if (parseInt(temp) != -1) {
		year = parseInt(temp);

		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);
		if (timeStr != "") {
			temp = getFirstWord(timeStr);
		} else {
			return (new Date(year, mon, day, hour, min));
		}
	}

	//Checks if time is in AM/PM 
	bool afterNoon = false;
	int amFound = temp.find("am");
	int pmFound = temp.find("pm");
	if (amFound < 0) {
		if (pmFound >= 0) {
			afterNoon = true;
		}
	}

	char chars[] = ".:apmhrs";
	for (int i = 0; i < strlen(chars); ++i) {
		temp.erase(remove(temp.begin(), temp.end(), chars[i]), temp.end());
	}
	int time = parseInt(temp);

	//Checks if time is in format 12pm or 12:00pm
	if (time / 100 == 0) {
		hour = time % 100;
	} else {
		hour = time / 100;
		min = time % 100;
	}

	if (hour < 12 && afterNoon)
		hour += 12;

	return (new Date(year, mon, day, hour, min));
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
		//throw error
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
		//throw error
	}
	return mon;
}