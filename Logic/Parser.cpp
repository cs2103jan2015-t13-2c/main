#include "Parser.h"

int Parser::_taskNumber;
string Parser::_taskDetails;
Date* Parser::_taskStartTime = nullptr;
Date* Parser::_taskEndTime = nullptr;
Date* Parser::_taskDeadline = nullptr;
Task::Recurrence Parser::_taskRecurrence;
Task::Priority Parser::_taskPriority;
bool Parser::_taskMarked;

Parser::Parser()
{
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


Parser::~Parser()
{
}

void Parser::parseCommandAdd(string userCommand) {

	//Parser to update
	//Error catching: Adding without text; Wrong date format (e.g. 30 Feb)
	//Streamline code: Use helper functions, OOP; Null iter problem


	/* User can enter task in 3 different formats:
	1. timed tasks
	e.g. add chinese new year from 19 february to 21 February
	2. tasks with deadlines
	e.g add finish CS2103 project by 10 july 2359hrs
	3. floating tasks
	e.g add finish coding assignment
	*/
	Parser::clearPreviousParse();

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	string text = removeFirstWord(userCommand);
	ostringstream temp;

	vector<string> textVec = splitParameters(text);
	vector<string>::iterator iter = textVec.begin();

	while (*iter != "from" && *iter != "by" && *iter != "every") {
		temp << *iter << " ";
		iter++;
		if (iter == textVec.end())
			break;
	}
	_taskDetails = temp.str();
	temp.str("");

	if (iter == textVec.end())
		return;

	if (*iter == "from") {
		//If keyword "from" is found, task is a timed task
		iter++;
		while (*iter != "to") {
			temp << *iter << " ";
			iter++;
			if (iter == textVec.end())
				break;
		}
		_taskStartTime = (parseTime(temp.str()));
		temp.str("");

		iter++;
		while (*iter != "#impt") {
			temp << *iter << " ";
			iter++;
			if (iter == textVec.end())
				break;
		}
		_taskEndTime = (parseTime(temp.str()));
		temp.str("");
	}

	else if (*iter == "by") {
		//If keyword "by" is found, task is a deadline task
		iter++;
		while (*iter != "#impt") {
			temp << *iter << " ";
			iter++;
			if (iter == textVec.end())
				break;
		}
		_taskDeadline = (parseTime(temp.str()));
		temp.str("");
	}

	else if (*iter == "every") {
		//If keyword "every" is found, task is a recurring task
		iter++;

		//Recurs every day
		if (*iter == "day") {
			_taskRecurrence = Task::Recurrence::DAY;
			int hour = 0, min = 0;

			iter++;
			if (iter == textVec.end()) {
				_taskDeadline = new Date(Date().getYear(),
					Date().getMonth(),
					Date().getDay() + 1, 0, 0);
				return;
			}

			if (*iter == "at") {
				iter++;
				string temp = *iter;

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

				if (time / 100 == 0) {
					hour = time % 100;
				}
				else {
					hour = time / 100;
					min = time % 100;
				}

				if (hour < 12 && afterNoon)
					hour += 12;
			}

			_taskDeadline = new Date(Date().getYear(),
				Date().getMonth(),
				Date().getDay() + 1, hour, min);
		}

		//Recurs every week
		else if (*iter == "sunday" || *iter == "sun" ||
			*iter == "monday" || *iter == "mon" ||
			*iter == "tuesday" || *iter == "tue" || *iter == "tues" ||
			*iter == "wednesday" || *iter == "wed" ||
			*iter == "thursday" || *iter == "thu" || *iter == "thur" ||
			*iter == "friday" || *iter == "fri" ||
			*iter == "saturday" || *iter == "sat") {
			_taskRecurrence = Task::Recurrence::WEEK;

			iter--;
			while (*iter != "to" && *iter != "#impt") {
				temp << *iter << " ";
				iter++;
				if (iter == textVec.end())
					break;
			}

			if (iter == textVec.end()) {
				_taskDeadline = (parseTime(temp.str()));
				return;
			}

			if (*iter == "to") {
				_taskStartTime = (parseTime(temp.str()));
				temp.str("");
				temp << "every ";

				iter++;
				while (*iter != "#impt") {
					temp << *iter << " ";
					iter++;
					if (iter == textVec.end())
						break;
				}
				_taskEndTime = (parseTime(temp.str()));
			}
		}

		//Recurs every month
		else if (*iter == "january" || *iter == "jan" ||
			*iter == "february" || *iter == "feb" ||
			*iter == "march" || *iter == "mar" ||
			*iter == "april" || *iter == "apr" ||
			*iter == "may" || *iter == "may" ||
			*iter == "june" || *iter == "jun" ||
			*iter == "july" || *iter == "jul" ||
			*iter == "august" || *iter == "aug" ||
			*iter == "september" || *iter == "sep" ||
			*iter == "october" || *iter == "oct" ||
			*iter == "november" || *iter == "nov" ||
			*iter == "december" || *iter == "dec") {
			_taskRecurrence = Task::Recurrence::MONTH;

			int taskMonth = parseMonthName(*iter);
			int diffinMonths = taskMonth - Date().getMonth();

			_taskDeadline = new Date(Date().getYear(),
				Date().getMonth() + diffinMonths,
				1, 0, 0);
		}
	}

	if (iter == textVec.end())
		return;

	if (*iter == "#impt") {
		_taskPriority = Task::Priority::HIGH;
	}
}

void Parser::parseCommandUpdate(string userCommand){
	Parser::clearPreviousParse();
	
	ostringstream oss;
	//get usercommand without the first word
	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	Parser::_taskNumber = atoi(task_number_str.c_str());

	//getting the task to edit from the taskmanager
	Task currentTask = TaskManager::getTask(Parser::_taskNumber);

	vector<string> textVec = splitParameters(text);
	vector<string>::iterator iter = textVec.begin();

	ostringstream temp;

	//Check for details
	iter = textVec.begin();
	temp<<currentTask.getTaskDetails();
	while (iter != textVec.end()) {
		if (*iter == "details") {
			temp.str("");
			++iter;
			while (iter != textVec.end() && *iter != "from" && *iter != "by" && *iter != "every" && *iter != "priority") {
				temp << *iter << " ";
				++iter;
			}
		}
		//++iter;
	}
	_taskDetails = temp.str();



	//Check for start time
	temp.clear();
	iter = textVec.begin();
	Date* start_time = currentTask.getTaskStartTime();
	string time_str;
	if (start_time == nullptr){
		time_str = "";
	}
	else{
		time_str = start_time->toString();
	}
	while (iter != textVec.end()) {
		if (*iter == "from") {
			while (*iter != "to") {
				time_str = time_str + " " + *iter;
				++iter;
			}
		}
		++iter;
	}
	start_time = parseTime(time_str);
	_taskStartTime=start_time;

	//Check for end time
	iter = textVec.begin();
	Date* end_time = (currentTask).getTaskEndTime();
	if (end_time == nullptr){
		time_str = "";
	}
	else{
		time_str = end_time->toString();
	}
	while (iter != textVec.end()) {
		if (*iter == "to") {
			while (*iter != "details" && *iter != "by" && *iter != "every" && *iter != "priority") {
				time_str = time_str + " " + *iter;
				++iter;
			}
		}
		++iter;
	}
	end_time = parseTime(time_str);
	_taskEndTime=end_time;

	//Check for deadline
	iter = textVec.begin();
	Date* deadline = currentTask.getTaskDeadline();
	if (deadline == nullptr){
		time_str = "";
	}
	else{
		time_str = deadline->toString();
	}
	if (*iter == "by") {
		while (*iter != "from" && *iter != "details" && *iter != "every" && *iter != "priority") {
			time_str = time_str + " " + *iter;
			++iter;
		}
		++iter;
	}
	deadline = parseTime(time_str);
	_taskDeadline=deadline;

	//Check for recurrence
	iter = textVec.begin();
	Task::Recurrence recurrence = currentTask.getTaskRecurrence();
	while (iter != textVec.end()) {
		if (*iter == "every") {
			++iter;
			if (*iter == "day") {
				recurrence = Task::Recurrence::DAY;
			}
			else if (*iter == "week") {
				recurrence = Task::Recurrence::WEEK;
			}
			else if (*iter == "month") {
				recurrence = Task::Recurrence::MONTH;
			}
		}
		else if (*iter == "everyday") {
			recurrence = Task::Recurrence::DAY;
		}
		else if (*iter == "no" || *iter == "not") {
			++iter;
			if (*iter == "recurrence" || *iter == "recurring" || *iter == "repeating") {
				recurrence = Task::Recurrence::NONE;
			}
		}
		++iter;
	}
	_taskRecurrence=recurrence;

	//Check for priority
	iter = textVec.begin();
	Task::Priority priority = currentTask.getTaskPriority();
	while (iter != textVec.end()) {
		if (*iter == "priority") {
			++iter;
			if (*iter == "high") {
				priority = Task::Priority::HIGH;
			}
			else if (*iter == "normal") {
				priority = Task::Priority::NORMAL;
			}
			else if (*iter == "low") {
				priority = Task::Priority::LOW;
			}
		}
		++iter;
	}
	_taskPriority=priority;
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
string Parser::removeFirstWord(string userCommand) {
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string Parser::getFirstWord(string userCommand) {
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

inline string Parser::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string Parser::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string Parser::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		return trim_left(trim_right(s, delimiters), delimiters);
	else
		return s;
}

bool Parser::equalsIgnoreCase(const string& str1, const string& str2) {
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

int Parser::parseInt(string str) {
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

string Parser::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}

Date* Parser::parseTime(string timeStr) {
	if (timeStr == ""){
		return nullptr;
	}
	
	int year = Date().getYear(),
		mon(0),
		day(0),
		hour(0),
		min(0);
	string temp;

	temp = getFirstWord(timeStr);

	//E.g. User types in "this thursday"
	if (temp == "this" || temp == "every") {
		int taskDay;
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);

		temp = (getFirstWord(timeStr));
		taskDay = parseDayName(temp);
		int diffinDays = taskDay - Date().getDayName();
		//throw error if negative

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;
	}

	else if (temp == "next") {
		int taskDay;
		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);

		temp = (getFirstWord(timeStr));
		taskDay = parseDayName(temp);

		int diffinDays = taskDay - Date().getDayName() + 7;
		//throw error if negative

		mon = Date().getMonth();
		day = Date().getDay() + diffinDays;

	}

	else {
		day = parseInt(temp);

		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);

		temp = (getFirstWord(timeStr));
		mon = parseMonthName(temp);
	}
	timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);

	if (timeStr != "") {
		temp = getFirstWord(timeStr);
	}
	else {
		return (new Date(year, mon, day, hour, min));
	}

	//Checks if user keyed in a year (Default is set to current year)
	if (parseInt(temp) != -1) {
		year = parseInt(temp);

		timeStr = timeStr.substr(timeStr.find_first_of(' ') + 1);

		if (timeStr != "") {
			temp = getFirstWord(timeStr);
		}
		else {
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

	if (time / 100 == 0) {
		hour = time % 100;
	}
	else {
		hour = time / 100;
		min = time % 100;
	}

	if (hour < 12 && afterNoon)
		hour += 12;

	//cout << day << " " << mon;
	return (new Date(year, mon, day, hour, min));
}

int Parser::parseDayName(string dayName) {
	int day = 0;

	if (dayName == "sunday" || dayName == "sun") {
		day = 0;
	}
	else if (dayName == "monday" || dayName == "mon") {
		day = 1;
	}
	else if (dayName == "tuesday" || dayName == "tue" || dayName == "tues") {
		day = 2;
	}
	else if (dayName == "wednesday" || dayName == "wed") {
		day = 3;
	}
	else if (dayName == "thursday" || dayName == "thu" || dayName == "thurs") {
		day = 4;
	}
	else if (dayName == "friday" || dayName == "fri") {
		day = 5;
	}
	else if (dayName == "saturday" || dayName == "sat") {
		day = 6;
	} //else throw error

	return day;
}

int Parser::parseMonthName(string monthName) {
	int mon = 0;

	if (monthName == "january" || monthName == "jan") {
		mon = 0;
	}
	else if (monthName == "february" || monthName == "feb") {
		mon = 1;
	}
	else if (monthName == "march" || monthName == "mar") {
		mon = 2;
	}
	else if (monthName == "april" || monthName == "apr") {
		mon = 3;
	}
	else if (monthName == "may") {
		mon = 4;
	}
	else if (monthName == "june" || monthName == "jun") {
		mon = 5;
	}
	else if (monthName == "july" || monthName == "jul") {
		mon = 6;
	}
	else if (monthName == "august" || monthName == "aug") {
		mon = 7;
	}
	else if (monthName == "september" || monthName == "sep") {
		mon = 8;
	}
	else if (monthName == "october" || monthName == "oct") {
		mon = 9;
	}
	else if (monthName == "november" || monthName == "nov") {
		mon = 10;
	}
	else if (monthName == "december" || monthName == "dec") {
		mon = 11;
	} //else throw error

	return mon;
}