#include "CommandUndo.h"

const string CommandUndo::MESSAGE_NOTHING_TO_UNDO = "There is nothing to undo!";
const string CommandUndo::MESSAGE_ACTION_UNDONE = "Action has been undone!";

CommandUndo::CommandUndo()
{
}


CommandUndo::~CommandUndo()
{
}

string CommandUndo::execute(){
	
	Controller* instance = Controller::getInstance();
	vector<Command*>* undoStack = instance->getUndoStack();

	if (undoStack->size() == 0){
		return MESSAGE_NOTHING_TO_UNDO;
	}

	else{
		Command* undoCommand = (*undoStack)[undoStack->size()-1];
		undoStack->pop_back();
		undoCommand->execute();
		return MESSAGE_ACTION_UNDONE;
	}

}

Command* CommandUndo::getInverseCommand(){
	return nullptr;
}
