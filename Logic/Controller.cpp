#include "Controller.h"


// Global static pointer used to ensure a single instance of the class.
Controller* Controller::_instance = NULL;

Controller::Controller()
{
}

Controller* Controller::getInstance(){
	if (!_instance)
		_instance = new Controller;
	return _instance;
}

string Controller::processUserInput(string userInput){
	TaskManager* taskManager = TaskManager::getInstance();
	CommandBuilder commandBuilder = CommandBuilder();
	Command *command = commandBuilder.parseCommand(userInput);
	string feedback = command->execute();
	return feedback;
}

