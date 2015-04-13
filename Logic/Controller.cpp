#include "Controller.h"


// Global static pointer used to ensure a single instance of the class.
Controller* Controller::_instance = NULL;
vector<Command*>* Controller::_undoStack = NULL;
vector<Command*>* Controller::_redoStack = NULL;
vector<int>* Controller::_taskIndices = NULL;
bool Controller::_isSearchCommand;


void Controller::setTaskIndices(vector<int>* taskIndices){
	_taskIndices = taskIndices;
}

vector<int>* Controller::getTaskIndices(){
	return _taskIndices;
}

bool Controller::getIsSearchCommand(){
	return _isSearchCommand;
}

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

vector<Command*>* Controller::getRedoStack(){
	if (!_redoStack)
		_redoStack = new vector<Command*>;
	return _redoStack;
}

string Controller::processUserInput(string userInput){

	string feedback;
	_isSearchCommand = false;

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

		CommandSearch* commandSearch = dynamic_cast<CommandSearch*>(command);

		if (commandSearch != NULL){
			setTaskIndices(commandSearch->getTasksIndices());
			_isSearchCommand = true;
		}

	}
	catch (ParseException& e){

		feedback = e.getMessage();

	}
	catch (CommandException& e){

		feedback = e.getMessage();

	}

	return feedback;
}

