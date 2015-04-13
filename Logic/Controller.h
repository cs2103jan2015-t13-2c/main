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
<<<<<<< HEAD
#include "ErrorLogger.h"
=======
>>>>>>> origin/master

using namespace std;

class Controller
{
public:

	static Controller* getInstance();

	static vector<Command*>* getUndoStack();

<<<<<<< HEAD
=======
	static vector<Command*>* getRedoStack();

>>>>>>> origin/master
	static string processUserInput(string userInput);

	static void setTaskIndices(vector<int>* taskIndices);

	static vector<int>* getTaskIndices();

	static bool getIsSearchCommand();

private:

	//copy constructor is private
	Controller& operator=(Controller const&){};

	static Controller *_instance;

	static vector<Command*>* _undoStack;

<<<<<<< HEAD
=======
	static vector<Command*>* _redoStack;

>>>>>>> origin/master
	static vector<int>* _taskIndices;

	static bool _isSearchCommand;
	
	Controller();
	
};

