#include "Taskky.h"

/*
Need addtional things to handle:
1. task does not differentiate floating, timed, deadline task
2. print to user also does not differentiate the different types of tasks
3. tolower everything?
4. error messages - wrong command lines?


*/

/*
 * ====================================================================
 *  Command line parse
 * ====================================================================
 */

void Taskky::showToUser(string text) {
	cout << text << "\n";	
}

string Taskky::executeCommand(string userCommand, vector<Task> &tempSave, string fileName) {
	if (trim(userCommand) == "") {
		sprintf_s(buffer, INVALID_MESSAGE_FORMAT.c_str(), "");
		return buffer;	
	}
	
	string commandTypeString = getFirstWord(userCommand);
	
	CommandType commandType = determineCommandType(commandTypeString);
	
	switch (commandType) {
		case Add:
			return addTask(userCommand, tempSave);
		case Display:
			return displayTask(userCommand, tempSave);
		case Update:
			return updateTask(userCommand, tempSave);
		case Delete:
			return deleteTask(userCommand, tempSave);
		case Invalid: {
			sprintf_s(buffer, INVALID_MESSAGE_FORMAT.c_str(), userCommand.c_str());
			return buffer;
		}
		case Exit: {
			writetoFile(tempSave, fileName);
			exit(0);
		}

		default: {
			//Generates an error message and terminates the program
			showToUser(ERROR_UNRECOGNISED_COMMAND_TYPE);
			showToUser(MESSAGE_PROGRAM_TERMINATION);
						
			getchar();
			exit(EXIT_FAILURE);
		}
	}
}

/*
 * ====================================================================
 *  Main functions
 * ====================================================================
 */

 //This operation determines which of the supported command types the user
 //wants to perform (commandTypeString is the first word of the user command)
 Taskky::CommandType Taskky::determineCommandType(string commandTypeString) {
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
	else {
		return CommandType::Invalid;	
	}
}

 string Taskky::addTask(string userCommand, vector<Task> &tempSave) {
	
/* User can enter task in 3 different formats:

	 1. timed tasks
	 e.g. add chinese new year from 19 february to 21 February 

	 2. tasks with deadlines
	 e.g add finish CS2103 project by 10 july 2359hrs

	 3. floating tasks
	 e.g add finish coding assignment
*/
	 int taskNumber = tempSave.size()+1;
	 string taskDetails = "";
	 Date taskStartTime = Date(1971, 1, 1, 0, 0);
	 Date taskEndTime = Date(1971, 1, 1, 0, 0);
	 Date taskDeadline = Date(1971, 1, 1, 0, 0);
	 Task::Recurrence taskRecurrence = Task::Recurrence::NONE;
	 Task::Priority taskPriority = Task::Priority::NORMAL;

	 string text = removeFirstWord(userCommand);
	 vector<string> textVec = splitParameters(text);
	 ostringstream temp;

	 vector<string>::iterator iter = textVec.begin();
	 
	 while (*iter != "from" && *iter != "by") {
		 temp << *iter << " ";
		 iter++;
		 if (iter == textVec.end())
			 break;
	 }
	taskDetails = temp.str();
	temp.str("");
	
	iter--;	//Note to self(Kelvin): To streamline
	if (*iter == "from") {
		while (*iter != "to") {
			temp << *iter << " ";
			iter++;	
		if (iter == textVec.end())
			break;
		}
		taskStartTime = parseTime(temp.str());
		temp.str("");

		while (*iter != "every" && *iter != "priority") {
			temp << *iter << " ";
			iter++;
			if (iter == textVec.end())
				break;
		}
		taskEndTime = parseTime(temp.str());
		temp.str("");
	}

	else if (*iter == "by") {
		while (*iter != "every" && *iter != "priority") {
			temp << *iter << " ";
			iter++;
			if (iter == textVec.end())
				break;
		}
		taskDeadline = parseTime(temp.str());
		temp.str("");
	}

	Task newTask = Task::Task(taskDetails, &taskStartTime, &taskEndTime, &taskDeadline,
							  taskRecurrence, taskPriority);
	
	tempSave.push_back(newTask);

	sprintf_s(buffer, MESSAGE_ADDED.c_str());
	return buffer;
}

 string Taskky::displayTask(string userCommand, vector<Task> &tempSave) {

	 ostringstream oss;
	 vector<Task>::iterator iter;

	 //Prints Task Number
	 for (iter = tempSave.begin(); iter != tempSave.end(); ++iter) {
		 oss << printTaskToUser(*iter);
	}
	return oss.str();
}

 /*
 PRINT TASK TO USE BUGGY!!!
 */

 string Taskky::printTaskToUser(Task toPrint) {
	 
	 ostringstream oss;
	 
	 //Prints Task Number
	 oss << "=============================" << endl;
	 oss << "Task #" << setw(8) << setfill('0') << 1 << endl;
	 oss << "=============================" << endl;

	 oss << (toPrint).getTaskDetails() << endl;

	 //Prints Task Start/End Time or Deadline (if any)
	 Task::Type checkType = (toPrint).getTaskType();
	 switch (checkType) {
	 case Task::TIMED: {
		 oss << "START: " << (toPrint).getTaskStartTime().toString() << endl;
		 oss << "END: " << (toPrint).getTaskEndTime().toString() << endl;
		 break;
	 }
	 case Task::DEADLINE: {
		 oss << "DEADLINE: " << (toPrint).getTaskDeadline().toString() << endl;
		 break;
	 }
	 default:
		 break;
	 }

	 //Prints Task Recurrence (if any)
	 Task::Recurrence checkRec = (toPrint).getTaskRecurrence();
	 switch (checkRec) {
	 case Task::DAY: {
		 oss << "EVERY DAY" << endl;
		 break;
	 }
	 case Task::WEEK: {
		 oss << "EVERY WEEK" << endl;
		 break;
	 }
	 case Task::MONTH: {
		 oss << "EVERY MONTH" << endl;
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
	 
	 return oss.str();

 }

string Taskky::updateTask(string userCommand, vector<Task> &tempSave) {
	/*
	command for update will be:
	"update _tasknumber detail (change task details) from (change start time) to (change end time) 
	 by (change deadline time) every (change recurrence) priority (change priority)"
	 hence keywords:
	 1. details
	 2. from - to
	 3. by
	 4. every / no recurrence
	 5. priority

	 each info can be omitted, whichever included will be changed, otherwise it will remain the same
	*/

	ostringstream oss;
	string text = removeFirstWord(userCommand);

	string task_number_str = getFirstWord(text);
	text = removeFirstWord(text);
	int task_number_int = atoi(task_number_str.c_str());

	vector<string> textVec = splitParameters(text);
	vector<Task>::iterator toUpdate = tempSave.begin() + task_number_int - 1;
	vector<string>::iterator iter = textVec.begin();

	//Check for details
	iter = textVec.begin();
	string details = (*toUpdate).getTaskDetails();
	while (iter != textVec.end()) {
		if (*iter == "details") {
			details = "";
			++iter;
			while (*iter != "from" && *iter != "by" && *iter != "every" && *iter != "priority") {
				details = details + " " + *iter;
				++iter;
			}
		}
		++iter;
	}
	(*toUpdate).setTaskDetails(details);

	//Check for start time
	iter = textVec.begin();
	Date start_time = (*toUpdate).getTaskStartTime();
	string time_str = start_time.toString();
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
	(*toUpdate).setTaskStartTime(start_time);

	//Check for end time
	iter = textVec.begin();
	Date end_time = (*toUpdate).getTaskEndTime();
	time_str = end_time.toString();
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
	(*toUpdate).setTaskEndTime(end_time);

	//Check for deadline
	iter = textVec.begin();
	Date deadline = (*toUpdate).getTaskDeadline();
	time_str = deadline.toString();
	if (*iter == "by") {
		while (*iter != "from" && *iter != "details" && *iter != "every" && *iter != "priority") {
			time_str = time_str + " " + *iter;
			++iter;
		}
		++iter;
	}
	deadline = parseTime(time_str);
	(*toUpdate).setTaskDeadline(deadline);

	//Check for recurrence
	iter = textVec.begin();
	Task::Recurrence recurrence = (*toUpdate).getTaskRecurrence();
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
	(*toUpdate).setTaskRecurrence(recurrence);

	//Check for priority
	iter = textVec.begin();
	Task::Priority priority = (*toUpdate).getTaskPriority();
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
	(*toUpdate).setTaskPriority(priority);


	return "Task Updated\n";	
}

string Taskky::deleteTask(string userCommand, vector<Task> &tempSave) {
	/*
	command for delete will be "delete /task_name"
	keep as comment in case we wanna change to this kind of delete ^^
	-adi-
	*/
	
	/*
	string text = removeFirstWord(userCommand);
	ostringstream oss;

	vector<Task>::iterator toDelete = determineTaskPosition(text, tempSave);
	if (toDelete != tempSave.end()) {
		tempSave.erase(toDelete);
		oss << "Deleted task " << (*toDelete).getTaskDetails << "from Taskky.\n";
	}
	else {
		oss << "Task not Found.\n";
	}


	return oss.str();
	*/

	/*
	for delete command "delete /task_number"
	*/

	ostringstream oss;

	string task_number_str = removeFirstWord(userCommand);
	int task_number_int = atoi(task_number_str.c_str());

	vector<Task>::iterator iter = tempSave.begin();
	iter = iter + task_number_int - 1;
	string deleted_task_name = (*iter).getTaskDetails();
	tempSave.erase(iter);

	oss << "Deleted task " << task_number_int << " (" << deleted_task_name << ") from Taskky.\n";

	return oss.str();

}
/*

//This function only useful for the other kind of delete command line,so only implement this with the other delete function
vector<Task>::iterator Taskky::determineTaskPosition(string taskname, vector<Task> &tempSave) {

	vector<Task>::iterator iter;
	bool isPresent = false;

	for (iter = tempSave.begin(); iter != tempSave.end(); ++iter) {
		string item = (*iter).getTaskDetails;
		size_t found = item.find(taskname);
		if (found != string::npos) {
			isPresent = true;
			return iter;
		}
	}

	if (isPresent == false) {
		return tempSave.end();
	}

}
*/
void Taskky::loadfromFile(vector<Task> &tempSave, string fileName) {
	 ifstream file;
	 file.open(fileName.c_str());

	 int taskNumber;
	 string taskDetails;
	 chrono::system_clock::time_point taskStartTime;
	 chrono::system_clock::time_point taskEndTime;
	 chrono::system_clock::time_point taskDeadline;
	 Task::Recurrence taskRecurrence;
	 Task::Priority taskPriority;

	 while (!file.eof()) {
	//Will do this part after our time problem is solved
	 }
 }

void Taskky::writetoFile(vector<Task> tempSave, string fileName) {
	 ofstream file;
	 file.open(fileName.c_str(), fstream::trunc);

	 vector<Task>::iterator iter;

	 for (iter = tempSave.begin(); iter != tempSave.end(); ++iter) {
		 int taskNumber = 1;
		 file << "=============================" << endl;
		 file << "Task #" << setw(8) << setfill('0') << taskNumber << endl;
		 file << "=============================" << endl;
		 file << (*iter).getTaskType() << endl;
		 file << (*iter).getTaskDetails() << endl;
		 file << ((*iter).getTaskStartTime()).toString() << endl;
		 file << ((*iter).getTaskEndTime()).toString() << endl;
		 file << ((*iter).getTaskDeadline()).toString() << endl;
		 file << (*iter).getTaskRecurrence() << endl;
		 file << (*iter).getTaskPriority() << endl;
		 file << "\n\n";
		 taskNumber++;
	 }

	 file.close();
	 return;
 }

/*
 * ====================================================================
 *  Additional functions
 * ====================================================================
 */
string Taskky::removeFirstWord(string userCommand) {
	return trim(replace(userCommand, getFirstWord(userCommand), ""));	
}

string Taskky::getFirstWord(string userCommand) {
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> Taskky::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string Taskky::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);	
}

inline string Taskky::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string Taskky::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		 return trim_left(trim_right(s, delimiters), delimiters);
	else
		 return s;	
}

bool Taskky::equalsIgnoreCase(const string& str1, const string& str2) {
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

int Taskky::parseInt(string str) {
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

string Taskky::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);		
	}
	while (pos != -1);
	return a;
}

Date Taskky::parseTime(string timeStr) {
	int mon(0), day(0), hour(0), min(0);
	string temp;

	day = parseInt(getFirstWord(timeStr));
	removeFirstWord(timeStr);

	temp = (getFirstWord(timeStr));
	if (temp == "january" || temp == "jan") {
		mon = 1;
	}
	else if (temp == "february" || temp == "feb") {
		mon = 2;
	}
	else if (temp == "march" || temp == "mar") {
		mon = 3;
	}
	else if (temp == "april" || temp == "apr") {
		mon = 4;
	}
	else if (temp == "may") {
		mon = 5;
	}
	else if (temp == "june" || temp == "jun") {
		mon = 6;
	}
	else if (temp == "july" || temp == "jul") {
		mon = 7;
	}
	else if (temp == "august" || temp == "aug") {
		mon = 8;
	}
	else if (temp == "september" || temp == "sep") {
		mon = 9;
	}
	else if (temp == "october" || temp == "oct") {
		mon = 10;
	}
	else if (temp == "november" || temp == "nov") {
		mon = 11;
	}
	else if (temp == "december" || temp == "dec") {
		mon = 12;
	}
	removeFirstWord(timeStr);

	temp = getFirstWord(timeStr);
	if (timeStr != "") {
		int time = parseInt(timeStr);
		hour = time / 100;
		min = time % 100;
	}

	cout << day << " " << mon;
	return (Date(2015, mon, day, hour, min));
}

/*
 * ====================================================================
 *  Program Messages
 * ====================================================================
 */
// These are the static variables that cannot be initialized in header file
const string Taskky::WELCOME_MESSAGE = "Welcome to T.A.S.K.K.Y.";
const string Taskky::MESSAGE_ADDED = "Task Added";
const string Taskky::MESSAGE_UPDATED = "Updated Task #%d: \n%s";
const string Taskky::MESSAGE_DELETED = "Deleted Task #%d";
const string Taskky::INVALID_MESSAGE_FORMAT = "Invalid command format: %s";
const string Taskky::MESSAGE_PROGRAM_TERMINATION = "Press any key to terminate the program . . .";

const string Taskky::ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type";

char Taskky::buffer[255];
