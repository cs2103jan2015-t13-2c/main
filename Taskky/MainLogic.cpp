#include "MainLogic.h"

/*******************
Message declarations
*******************/
const std::string MainLogic::MESSAGE_INVALID_FORMAT = "Invalid command format: %s";
char MainLogic::buffer[BUFFER_SIZE];
using namespace std;


/*********
Logic Main
*********/
void MainLogic::main(std::string command) {
	//determine which command
	while (command != ""){

		COMMAND_TYPE commandType = determineCommandType(getFirstWord(command));
		command = removeFirstWord(command);
		std::string content = determineContent(command);

		std::string result = processCommand(commandType, content);

		command = removeWords(command, content);

		cout << "leftover: " << command;
	}

}

std::string MainLogic::processCommand(MainLogic::COMMAND_TYPE commandType, std::string content){
	switch (commandType) {
	case CREATE:
		return addTask(content);
	case READ:
		return checkTask(content);
	case UPDATE:
		return updateTask(content);
	case DELETE:
		return deleteTask(content);
	case CLEAR:
		return clear();
	case SORT:
		return sortTask();
	case SEARCH:
		return searchTask(content);
	case INVALID:
	{
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), content.c_str()); //COME BACK TO THIS, I ANYHOW haha
		return buffer;
	}
	case EXIT:
		exit(0);
	}
}


/**************
Command Parsers
**************/
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
	else {
		return COMMAND_TYPE::INVALID;
	}
}

string MainLogic::determineContent(string command){
	ostringstream oss;
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

string MainLogic::removeWords(string command, string content){
	size_t pos;

	if ((pos = command.find(content)) != string::npos) {
		command.erase(pos, content.length());
	}

	return command;
}

/*******************
Processing Functions
*******************/
string MainLogic::addTask(string userCommand) {

	/* User can enter task in 3 different formats:

	1. timed tasks
	e.g. add 19 February, to 21 February, chinese new year

	2. tasks with deadlines
	e.g add 10 July, 5pm-6pm, project meeting

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

	return "0";
}

string MainLogic::checkTask(string userCommand) {
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