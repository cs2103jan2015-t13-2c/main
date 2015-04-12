#include "Controller.h"


// Global static pointer used to ensure a single instance of the class.
Controller* Controller::_instance = NULL;
vector<Command*>* Controller::_undoStack = NULL;
vector<Command*>* Controller::_redoStack = NULL;

Controller::Controller()
{
	ErrorLogger* errorLogger = ErrorLogger::getInstance();
}

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

vector<Command*>* Controller::getRedoStack(){
	if (!_redoStack)
		_redoStack = new vector<Command*>;
	return _redoStack;
}

string Controller::processUserInput(string userInput){

	ErrorLogger* errorLogger = ErrorLogger::getInstance();
	string feedback;

	try{

		TaskManager* taskManager = TaskManager::getInstance();
		CommandBuilder commandBuilder = CommandBuilder();
		Command* command = commandBuilder.parseCommand(userInput);

		Command* undoCommand = command->getInverseCommand();
		
		if (undoCommand != nullptr){
			getUndoStack()->push_back(undoCommand);
			getRedoStack()->clear();
		}

		feedback = command->execute();

		taskManager->saveTasks();

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

