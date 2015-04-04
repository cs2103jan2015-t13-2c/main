#pragma once
#include <string>

#include "Command.h"
#include "CommandBuilder.h"
#include "TaskManager.h"
#include "Storage.h"
#include "SuggestionBuilder.h"
#include "ParseException.h"
#include "CommandException.h"

using namespace std;

class Controller
{
public:

	static Controller* getInstance();

	static vector<Command*>* getUndoStack();

	static string processUserInput(string userInput);

private:

	//copy constructor is private
	Controller& operator=(Controller const&){};

	static Controller *_instance;

	static vector<Command*>* _undoStack;
	
	Controller();
	
};

