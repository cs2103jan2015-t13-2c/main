//@author A0122357L
#include "CommandRedo.h"

CommandRedo::CommandRedo()
{
}


CommandRedo::~CommandRedo()
{
}

string CommandRedo::execute(){

	Controller* instance = Controller::getInstance();
	vector<Command*>* redoStack = instance->getRedoStack();

	if (redoStack->size() == 0){
		return MESSAGE_NOTHING_TO_REDO;
	}

	else{
		Command* redoCommand = (*redoStack)[redoStack->size() - 1];
		redoStack->pop_back();
		redoCommand->execute();
		return MESSAGE_ACTION_REDONE;
	}

}

Command* CommandRedo::getInverseCommand(){
	return nullptr;
}

const string CommandRedo::MESSAGE_NOTHING_TO_REDO = "There is nothing to redo!";
const string CommandRedo::MESSAGE_ACTION_REDONE = "Action has been redone!";