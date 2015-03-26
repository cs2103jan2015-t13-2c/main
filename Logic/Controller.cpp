#include "Controller.h"


// Global static pointer used to ensure a single instance of the class.
Controller* Controller::_instance = NULL;
vector<Command*>* Controller::_undoStack = NULL;

Controller::Controller()
{
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

string Controller::processUserInput(string userInput){

	TaskManager* taskManager = TaskManager::getInstance();
	CommandBuilder commandBuilder = CommandBuilder();
	Command* command = commandBuilder.parseCommand(userInput);
	
	Command* undoCommand = command->getInverseCommand();
	if (undoCommand != nullptr){
		getUndoStack()->push_back(undoCommand);
	}

	

	string feedback = command->execute();
	return feedback;
}

