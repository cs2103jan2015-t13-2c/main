//@author A0122357L

/*
This class contains code that can execute the command "Exit",
which exits the program

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
*/

#include "CommandExit.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method exits the program, with success
string CommandExit::execute(){

	exit(0);

	return "Exit with success!";

}


//No undo Command exists for the Command
Command* CommandExit::getInverseCommand(){

	return nullptr;

}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

CommandExit::CommandExit()
{
}

