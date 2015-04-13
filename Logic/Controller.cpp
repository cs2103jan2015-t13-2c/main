//@author A0122357L

/*
This class is used to manage Taskky's logic flow to process the user input,
and execute the command parsed
It is a singleton class, so that there will only be 1 instance of the tasks

It also supports the passing of a vector<int> of found tasks when a user 
searches for tasks, that indicated the indexes the tasks are found
*/

#include "Controller.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This operation processes the user input and executes the user input
//
//@param the user input string
//@return the feedback string to display to the user
string Controller::processUserInput(string userInput){

	ErrorLogger* errorLogger = ErrorLogger::getInstance();

	string feedback;

	_isSearchCommand = false;

	try{

		TaskManager* taskManager = TaskManager::getInstance();

		CommandBuilder commandBuilder = CommandBuilder();

		Command* command = commandBuilder.parseCommand(userInput);

		Command* undoCommand = command->getInverseCommand();

		if (undoCommand != nullptr){

			getUndoStack()->push_back(undoCommand);

		}

		feedback = command->execute();

		taskManager->saveTasks();

		CommandSearch* commandSearch = dynamic_cast<CommandSearch*>(command);

		if (commandSearch != NULL){

			setTaskIndices(commandSearch->getTasksIndices());

			_isSearchCommand = true;

		}

	}

	catch (ParseException& e){

		feedback = e.getMessage();

		errorLogger->logError(feedback);

	}

	catch (CommandException& e){

		feedback = e.getMessage();

		errorLogger->logError(feedback);

	}

	return feedback;
}


/*
* ====================================================================
*  Constructor, Getters and Setters
* ====================================================================
*/

void Controller::setTaskIndices(vector<int>* taskIndices){

	_taskIndices = taskIndices;

}


vector<int>* Controller::getTaskIndices(){

	return _taskIndices;

}

//returns the boolean containing information 
//if the current command is search
bool Controller::getIsSearchCommand(){

	return _isSearchCommand;

}


//The default constructor instantiates a new error logger
Controller::Controller(){

	ErrorLogger* errorLogger = ErrorLogger::getInstance();

}


//Ensures the singleton pattern is followed
Controller* Controller::getInstance(){

	if (!_instance)

		_instance = new Controller;

	return _instance;
}


vector<Command*>* Controller::getUndoStack(){

	if (!_undoStack)

		_undoStack = new vector<Command*>;

	return _undoStack;
}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

// Global static pointer used to ensure a single instance of the class.
Controller* Controller::_instance = NULL;
vector<Command*>* Controller::_undoStack = NULL;
bool Controller::_isSearchCommand;

//Task indices are used to indicate the indexes of tasks found
//using the command Search
vector<int>* Controller::_taskIndices = NULL;
