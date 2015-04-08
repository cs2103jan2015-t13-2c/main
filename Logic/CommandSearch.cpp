#include "CommandSearch.h"


CommandSearch::CommandSearch(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority,
	string duration,
	bool taskMarked,
	bool foundMarked,
	bool foundPriority) {

	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
	_duration = duration;
	_taskMarked = taskMarked;
	_foundMarked = foundMarked;
	_foundPriority = foundPriority;
}


CommandSearch::~CommandSearch()
{
}

string CommandSearch::execute() {

	TaskManager instance = *TaskManager::getInstance();

	if (_taskDetails != "") {
		if (_taskStartTime != NULL || _taskEndTime != NULL || _taskPriority != NULL){
			throw CommandException(ERROR_TOOMANY_SEARCH_ARGUMENTS);
		}
		return searchByName(_taskDetails);
	}
	else if (_taskStartTime != NULL) {
		if (_taskEndTime != NULL) {
			return searchDateRange(*_taskStartTime, *_taskEndTime);
		}
		else if (_taskEndTime == NULL) {
			return searchAfterDate(*_taskStartTime);
		}
	}
	else if (_taskStartTime == NULL) {
		if (_taskEndTime != NULL) {
			return searchBeforeDate(*_taskEndTime);
		}
	}
	
	if (_foundPriority == true) {
		return searchPriority(_taskPriority);
	}
	if (_foundMarked == true) {
		return searchMarked(_taskMarked);
	}
	if (_duration != ""){
		return searchNextEmptySlot(_duration);
	}

	return "Invalid search funtion\n";

}

Command* CommandSearch::getInverseCommand() {
	return nullptr;
}

string CommandSearch::searchByName(string taskname) {

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;
	ostringstream oss;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskDetails().find(taskname.c_str()) != string::npos) {
			if (count == 0) {
				oss << "Similar results:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
		}
		else if (StringDistance::LD(taskname.c_str(), iter->getTaskDetails().c_str()) <= CommandSearch::ACCEPTABLE_DISTANCE) {
			if (count == 0) {
				oss << "Similar results:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			count++;
		}
		++position;
	}

	if (count == 0) {
		oss << "No similar results found!\n";
	}

	return oss.str();

}

string CommandSearch::searchDateRange(Date dateFrom, Date dateTo) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateFrom.isEarlierThan(*(iter->getTaskDeadline())) >= 0) {
				if (dateTo.isEarlierThan(*(iter->getTaskDeadline())) <= 0) {
					if (count == 0) {
						oss << "List of Tasks:\n";
					}
					oss << CommandSearch::printTask(*iter, position);
					++count;
				}
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateFrom.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				if (dateTo.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
					if (count == 0) {
						oss << "List of Tasks:\n";
					}
					oss << CommandSearch::printTask(*iter, position);
					++count;
				}
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Task within date range!\n";
	}

	return oss.str();

}

string CommandSearch::searchAfterDate(Date dateAfter) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateAfter.isEarlierThan(*(iter->getTaskDeadline())) >= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateAfter.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Tasks after specified date!\n";
	}

	return oss.str();

}

string CommandSearch::searchBeforeDate(Date dateBefore) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateBefore.isEarlierThan(*(iter->getTaskDeadline())) <= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateBefore.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Tasks before specified date!\n";
	}

	return oss.str();

}

string CommandSearch::searchPriority(Task::Priority priority) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (priority == iter->getTaskPriority()) {
			if (count == 0) {
				oss << "List of Tasks:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			++count;
		}
		++position;
	}

	if (count == 0) {
		oss << "No Task with specified priority found!\n";
	}

	return oss.str();

}

string CommandSearch::searchMarked(bool marked) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (marked == iter->getTaskMarked()) {
			if (count == 0) {
				oss << "List of Tasks:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			++count;
		}
		++position;
	}

	if (count == 0) {
		if (marked){
			oss << "No done tasks!\n";
		}
		else{
			oss << "No undone tasks!\n";
		}
		
	}

	return oss.str();

}

string CommandSearch::searchNextEmptySlot(string duration){
	/*
	Valid string inputs:
	1. xx day(s) yy hour(s) zz minute(s)	xx, yy, zz integers
	2. xx day(s) yy hour(s)					xx, yy integers
	3. xx day(s)							xx integer or float
	4. xx hour(s) yy minute(s)				xx, yy, zz integers
	5. xx hour(s)							xx integer or float
	6. xx minute(s)							xx integer
	Otherwise invalid
	*/

	int durationInMinutes = parseDurationToMinutes(duration);

	vector<Task> TaskVector = *TaskManager::getAllCurrentTasks();
	vector<Task>::iterator iter = TaskVector.begin();
	bool found = false;
	Date toCompare = Date::Date();

	for (iter = TaskVector.begin(); 
		iter != TaskVector.end() && iter->getTaskType() != Task::FLOATING && found == false; 
		++iter){
		
		if (iter->getTaskType() == Task::TIMED) {
			if (toCompare.isEarlierThan(*(iter->getTaskStartTime())) == 1){
				int freeTime = toCompare.diffInMinutes(*(iter->getTaskStartTime()));
				if (freeTime >= durationInMinutes){
					found = true;
				}
				else {
					toCompare = *(iter->getTaskEndTime());
				}
			}
		}

	}

	
	if (toCompare.isEarlierThan(Date::Date()) == 0) {
		sprintf_s(buffer, MESSAGE_NEXT_AVAILABLE_SLOT.c_str(), duration.c_str(), "now!");
	}
	else {
		sprintf_s(buffer, MESSAGE_NEXT_AVAILABLE_SLOT.c_str(), duration.c_str(), toCompare.toString().c_str());
	}
	return buffer;
	
}

int CommandSearch::parseDurationToMinutes(string duration){
	int numberOfWords = countWordsInString(duration);

	if (numberOfWords == 6){						//assumed format = __ days __ hours __ minutes
		int days = stoi(getFirstWord(duration));
		duration = removeFirstWord(duration);

		//check if parameter is correct
		if (getFirstWord(duration) != "day" && getFirstWord(duration) != "days"){
			throw CommandException(INVALID_DURATION);
		}
		else {
			duration = removeFirstWord(duration);
		}

		int hours = stoi(getFirstWord(duration));
		duration = removeFirstWord(duration);

		//check if parameter is correct
		if (getFirstWord(duration) != "hour" && getFirstWord(duration) != "hours"){
			throw CommandException(INVALID_DURATION);
		}
		else {
			duration = removeFirstWord(duration);
		}

		int minutes = stoi(getFirstWord(duration));
		duration = removeFirstWord(duration);

		//check if parameter is correct
		if (getFirstWord(duration) != "minute" && getFirstWord(duration) != "minutes"){
			throw CommandException(INVALID_DURATION);
		}

		return (days * DAYS_TO_MINUTES + hours * HOURS_TO_MINUTES + minutes);

	}

	if (numberOfWords == 4){
		/*
		Possible formats:
		1. xx days yy hours
		2. xx hours yy minutes
		*/

		int firstNumber = stoi(getFirstWord(duration));
		duration = removeFirstWord(duration);
		if (getFirstWord(duration) == "day" || getFirstWord(duration) == "days"){
			int days = firstNumber;
			duration = removeFirstWord(duration);
			
			int hours = stoi(getFirstWord(duration));
			duration = removeFirstWord(duration);
			if (getFirstWord(duration) != "hour" && getFirstWord(duration) != "hours"){
				throw CommandException(INVALID_DURATION);
			}

			return (days * DAYS_TO_MINUTES + hours * HOURS_TO_MINUTES);
		}
		else if (getFirstWord(duration) == "hour" || getFirstWord(duration) == "hours"){
			int hours = firstNumber;
			duration = removeFirstWord(duration);
			int minutes = stoi(getFirstWord(duration));
			duration = removeFirstWord(duration);
			if (getFirstWord(duration) != "minutes" && getFirstWord(duration) != "minute"){
				throw CommandException(INVALID_DURATION);
			}

			return (hours * DAYS_TO_MINUTES + minutes * HOURS_TO_MINUTES);
		}
		else {
			throw CommandException(INVALID_DURATION);
		}

	}

	if (numberOfWords == 2){
		/*
		Possible formats:
		1. __ days
		2. __ hours
		3. __ minutes
		*/

		float firstNumber = stof(getFirstWord(duration));
		duration = removeFirstWord(duration);
		if (getFirstWord(duration) == "day" || getFirstWord(duration) == "days"){
			return firstNumber * DAYS_TO_MINUTES;
		}
		else if (getFirstWord(duration) == "hours" || getFirstWord(duration) == "hour"){
			return firstNumber * HOURS_TO_MINUTES;
		}
		else if (getFirstWord(duration) == "minutes" || getFirstWord(duration) == "minute"){
			return firstNumber;
		} else {
			throw CommandException(INVALID_DURATION);
		}

	}

	throw CommandException(INVALID_DURATION);
	return 0;
}

string CommandSearch::printTask(Task toPrint, int taskNumber) {
	ostringstream oss;

	//Prints Task Number
	oss << "=============================" << endl;
	oss << "Task #" << setw(8) << setfill('0') << taskNumber << endl;
	oss << "=============================" << endl;

	oss << (toPrint).getTaskDetails() << endl;

	//Prints Task Start/End Time or Deadline (if any)
	Task::Type checkType = (toPrint).getTaskType();
	switch (checkType) {
	case Task::TIMED: {
		oss << "START: " << (toPrint).getTaskStartTime()->toString() << endl;
		oss << "END: " << (toPrint).getTaskEndTime()->toString() << endl;
		break;
	}
	case Task::DEADLINE: {
		oss << "DEADLINE: " << (toPrint).getTaskDeadline()->toString() << endl;
		break;
	}
	default:
		break;
	}

	//Prints Task Priority
	Task::Priority checkPri = (toPrint).getTaskPriority();
	switch (checkPri) {
	case Task::LOW: {
		oss << "PRIORITY: LOW" << endl;
		break;
	}
	case Task::HIGH: {
		oss << "PRIORITY: HIGH" << endl;
		break;
	}
	default: {
		oss << "PRIORITY: NORMAL" << endl;
		break;
	}
	}

	bool checkMarked = (toPrint).getTaskMarked();
	switch (checkMarked) {
	case true: {
		oss << "MARKED: " << "YES" << endl;
		break;
	}
	case false: {
		oss << "MARKED: " << "NO" << endl;
		break;
	}
	}

	return oss.str();
}

/*
* ====================================================================
*  Additional functions
* ====================================================================
*/

string CommandSearch::removeFirstWord(string userCommand){

	
	size_t firstSpace = userCommand.find_first_of(' ');
	return userCommand.substr(firstSpace + 1, userCommand.npos);

	//old function
	//return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string CommandSearch::getFirstWord(string userCommand){
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> CommandSearch::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string CommandSearch::trim_right(const string& s, const string& delimiters){
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string CommandSearch::trim_left(const string& s, const string& delimiters){
	if (countWordsInString(s) == 0){
		return "";
	}
	return s.substr(s.find_first_not_of(delimiters));
}

unsigned int CommandSearch::countWordsInString(const string& str)
{
	std::stringstream stream(str);
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

inline string CommandSearch::trim(const string& s, const string& delimiters){
	if (!s.empty()){
		return trim_left(trim_right(s, delimiters), delimiters);
	}
	else{
		return s;
	}
}

bool CommandSearch::equalsIgnoreCase(const string& str1, const string& str2){
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

int CommandSearch::parseInt(string str){
	char c;
	int i = 0;
	std::stringstream ss(str);
	ss >> i;
	if (ss.fail() || ss.get(c)){
		return INVALID_NUMBER_FORMAT;
	}
	else{
		return i;
	}
}

string CommandSearch::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}

char CommandSearch::buffer[255];
const string CommandSearch::ERROR_TOOMANY_SEARCH_ARGUMENTS = "Enter only 1 search argument!";
const string CommandSearch::INVALID_DURATION = "Invalid search duration input. Please input in the following format:\n1. __ day(s) __ hour(s) __ minute(s) (all numbers are integers)\n2. __ day(s) __ hour(s) (all numbers are integers)\n3. __ days (number can be  integer or with decimal)\n4. __ hour(s) __ minute(s) (all numbers are integers)\n5. __ hour(s) (number can be integer or with decimals)\n6. __ minute(s) (number can only be integer)\nNOTE: smallest valid duration is 1 minute";
const string CommandSearch::MESSAGE_NEXT_AVAILABLE_SLOT = "Next available %sis from %s.";