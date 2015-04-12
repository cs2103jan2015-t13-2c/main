/*
This class contains code that can execute the command "Undo",
which undoes the previous Command that can be undone

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class

@author: A0122357L Lee Kai Yi
*/

#include "CommandUndo.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method will undo the previous undoable command
//
//@return feedback to user
string CommandUndo::execute(){

	Controller* instance = Controller::getInstance();

	vector<Command*>* undoStack = instance->getUndoStack();

	if (undoStack->size() == 0){

		return MESSAGE_NOTHING_TO_UNDO;

	}

	else{

		Command* undoCommand = (*undoStack)[undoStack->size() - 1];

		undoStack->pop_back();

		undoCommand->execute();

		return MESSAGE_ACTION_UNDONE;

	}
}

//There is no Command to undo the undo command!
Command* CommandUndo::getInverseCommand(){

	return nullptr;

}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

//Default constructor for undo
CommandUndo::CommandUndo()
{
}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandUndo::MESSAGE_NOTHING_TO_UNDO = "There is nothing to undo!";
const string CommandUndo::MESSAGE_ACTION_UNDONE = "Action has been undone!";




