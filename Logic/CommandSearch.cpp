//@author A0094024M

/*
This class is to handle the search command. As an object of this class is constructed, it will
take in the specific attributes as the search objects and search accordingly (e.g. setting 
taskDetails will result in searching the TaskVector for a similar task details, etc).

Available searches:
1. Exact task details search
2. Near match search (including per word near match)
3. Search tasks within specified date range
4. Search tasks before specified date
5. Search tasks after specified date
6. Search tasks of specified priority
7. Search tasks that are done / undone (either)
8. Search next empty slot
*/

#include "CommandSearch.h"

/*
* ====================================================================
*  Constructors, Modifiers, Accessors and Destructors
* ====================================================================
*/

//Constructor
CommandSearch::CommandSearch(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority,
	string duration,
	bool taskMarked,
	bool foundMarked,
	bool foundPriority){

	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
	_duration = duration;
	_taskMarked = taskMarked;
	_foundMarked = foundMarked;
	_foundPriority = foundPriority;
	foundTasksIndices = new vector < int > ;
}

//Default destructor
CommandSearch::~CommandSearch()
{
}

//Returns the integer vector of the tasks found
vector<int>* CommandSearch::getTasksIndices(){
	return foundTasksIndices;
}

/*
* ====================================================================
*  Inherited Functions
* ====================================================================
*/

//This function executes the search function. It will check the object attributes and search
//the corresponding attributes that are not null. Returns the feedback for the search function
//as how many tasks are found, or for search next available slot, the earliest time point available.
//
//@param: none
//@return: feedback string
string CommandSearch::execute() {

	TaskManager instance = *TaskManager::getInstance();

	if (_taskDetails != "") {
		if (_taskStartTime != NULL || _taskEndTime != NULL || _foundPriority != false){
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

	return INVALID_SEARCH_FUNCTION;

}

//There is no undo function for search, hence this function returns a null pointer
//
//@param: none
//@return: null pointer
Command* CommandSearch::getInverseCommand() {
	return nullptr;
}

/*
* ====================================================================
*  Second Abstractions
* ====================================================================
*/

//This function iterates through the vector of Tasks an find match based on the Task details.
//Return the number of near match, updates the vector of found indices.
//
//@param: string to be searched
//@return: feedback on number of match found
string CommandSearch::searchByName(string taskname) {

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;
	ostringstream oss;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter){
		if (containExactMatch(taskname, iter->getTaskDetails())){
			++count;
			foundTasksIndices->push_back(position);
		} else if (containNearMatch(taskname, iter->getTaskDetails())){
			++count;
			foundTasksIndices->push_back(position);
		}
		++position;
	}

	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and find all Tasks that have deadline
//or start time within the range of dates specified.
//
//Only iterate through Timed Tasks and Deadline Tasks. Will not consider Floating Tasks
//
//@param: range of date (date from, date to)
//@return: feedback on number of match found
string CommandSearch::searchDateRange(Date dateFrom, Date dateTo) {

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); 
		iter != TaskVector.end() && iter->getTaskType() != Task::FLOATING;
		++iter){
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateFrom.isEarlierThan(*(iter->getTaskDeadline())) >= 0){
				if (dateTo.isEarlierThan(*(iter->getTaskDeadline())) <= 0){
					++count;
					foundTasksIndices->push_back(position);
				}
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateFrom.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				if (dateTo.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
					foundTasksIndices->push_back(position);
					++count;
				}
			}
		}
		++position;
	}


	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and find all Tasks that have deadline
//or start time after the date specified.
//
//Only iterate through Timed Tasks and Deadline Tasks. Will not consider Floating Tasks
//
//@param: minimum date
//@return: feedback on number of match found
string CommandSearch::searchAfterDate(Date dateAfter) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); 
		iter != TaskVector.end() && iter->getTaskType() != Task::FLOATING; 
		++iter){
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateAfter.isEarlierThan(*(iter->getTaskDeadline())) >= 0) {
				foundTasksIndices->push_back(position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateAfter.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				foundTasksIndices->push_back(position);
				++count;
			}
		}
		++position;
	}

	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and find all Tasks that have deadline
//or start time before the date specified.
//
//Only iterate through Timed Tasks and Deadline Tasks. Will not consider Floating Tasks
//
//@param: maximum date
//@return: feedback on number of match found
string CommandSearch::searchBeforeDate(Date dateBefore) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin();
		iter != TaskVector.end() && iter->getTaskType() != Task::FLOATING;
		++iter){
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateBefore.isEarlierThan(*(iter->getTaskDeadline())) <= 0) {
				foundTasksIndices->push_back(position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateBefore.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
				foundTasksIndices->push_back(position);
				++count;
			}
		}
		++position;
	}

	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and find all Tasks that matching priority
//
//@param: priority (high, normal, low)
//@return: feedback on number of match found
string CommandSearch::searchPriority(Task::Priority priority) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (priority == iter->getTaskPriority()) {
			foundTasksIndices->push_back(position);
			++count;
		}
		++position;
	}

	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and find all Tasks that are done/undone.
//
//@param: marked / not marked
//@return: feedback on number of match found
string CommandSearch::searchMarked(bool marked) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (marked == iter->getTaskMarked()) {
			foundTasksIndices->push_back(position);
			++count;
		}
		++position;
	}

	sprintf_s(buffer, MESSAGE_FOUND_TASKS.c_str(), count);
	return buffer;

}

//This function iterates through the vector of Tasks and determine the earliest time point 
//where a specified duration will not clash with any Timed Tasks.
//
//This function only considers the Timed Tasks. Deadline Tasks are assumed to only take up
//one point in time hence will not affect availability of free slot.
//
//@param: duration required
//Valid string inputs:
//1. xx day(s) yy hour(s) zz minute(s)	xx, yy, zz integers
//2. xx day(s) yy hour(s)				xx, yy integers
//3. xx day(s)							xx integer or float
//4. xx hour(s) yy minute(s)			xx, yy, zz integers
//5. xx hour(s)							xx integer or float
//6. xx minute(s)						xx integer
//Otherwise invalid
//
//@return: feedback on number of match found
string CommandSearch::searchNextEmptySlot(string duration){
	
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

/*
* ====================================================================
*  Third Abstractions
* ====================================================================
*/

//This function parse the duration (in string) into the equivalent number of minutes.
//
//@param: duration string
//@return: number of minutes
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

//This function checks if the string contains an exact line of another string
//
//@param: two strings, one to search and one as reference
//@return: boolean (true/false)
bool CommandSearch::containExactMatch(string searchName, string taskName){
	if (taskName.find(searchName) != string::npos){
		return true;
	} else {
		return false;
	}
}

//This function checks if the string contains a near match of another string
//
//@param: two strings, one to search and one as reference
//@return: boolean (true/false)
bool CommandSearch::containNearMatch(string searchName, string taskName){
	int numWords = countWordsInString(searchName);
	bool nearMatch = false;

	if (StringDistance::LD(searchName.c_str(), taskName.c_str()) <=
		CommandSearch::ACCEPTABLE_DISTANCE){
		nearMatch = true;
	}
	
	if (!nearMatch){
		vector<string> textVec = splitParameters(taskName);
		vector<string>::iterator iter;
		vector<string>::iterator iterToCompare;

		for (iter = textVec.begin(); iter != textVec.end() && nearMatch == false; ++iter){
			iterToCompare = iter;
			ostringstream temp;
			for (int i = 0; i < numWords && iterToCompare != textVec.end(); ++i){
				temp << *iterToCompare << " ";
				++iterToCompare;
			}
			if (StringDistance::LD(searchName.c_str(), temp.str().c_str()) <=
				CommandSearch::ACCEPTABLE_DISTANCE - 1){
				nearMatch = true;
			}
		}
	}
	return nearMatch;
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

//@author A0094024 -reused
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

/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

char CommandSearch::buffer[255];
const string CommandSearch::ERROR_TOOMANY_SEARCH_ARGUMENTS = "Enter only 1 search argument!";
const string CommandSearch::INVALID_DURATION = "Invalid search duration input. Please input in the following format:\n1. __ day(s) __ hour(s) __ minute(s) (all numbers are integers)\n2. __ day(s) __ hour(s) (all numbers are integers)\n3. __ days (number can be  integer or with decimal)\n4. __ hour(s) __ minute(s) (all numbers are integers)\n5. __ hour(s) (number can be integer or with decimals)\n6. __ minute(s) (number can only be integer)\nNOTE: smallest valid duration is 1 minute";
const string CommandSearch::MESSAGE_NEXT_AVAILABLE_SLOT = "Next available %sis from %s.";
const string CommandSearch::MESSAGE_FOUND_TASKS = "There are %d tasks found.";
const string CommandSearch::INVALID_SEARCH_FUNCTION = "Invalid search function.";