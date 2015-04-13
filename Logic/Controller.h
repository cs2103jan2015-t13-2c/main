//@author A0122357L
#pragma once
#include <string>

#include "Command.h"
#include "CommandBuilder.h"
#include "TaskManager.h"
#include "Storage.h"
#include "SuggestionBuilder.h"
#include "ParseException.h"
#include "CommandException.h"
#include "ErrorLogger.h"

using namespace std;

class Controller
{
public:

	static Controller* getInstance();

	static vector<Command*>* getUndoStack();

	static string processUserInput(string userInput);

	static void setTaskIndices(vector<int>* taskIndices);

	static vector<int>* getTaskIndices();

	static bool getIsSearchCommand();

private:

	//copy constructor is private
	Controller& operator=(Controller const&){};

	static Controller *_instance;

	static vector<Command*>* _undoStack;

	static vector<int>* _taskIndices;

	static bool _isSearchCommand;
	
	Controller();
	
};

