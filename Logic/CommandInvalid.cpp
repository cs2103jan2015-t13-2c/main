//@author A0122357L
<<<<<<< HEAD
=======
#include "CommandInvalid.h"
>>>>>>> origin/master

/*
This class contains code that can execute the command "Invalid",
which shows feedback to the user that the Command he entered is invalid

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
*/

#include "CommandInvalid.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method shows feedback to the user that the Command he entered
//was invalid
//
//@return feedback to user
string CommandInvalid::execute(){

	sprintf_s(buffer, INVALID_MESSAGE_FORMAT.c_str(), _userInput.c_str());

	return buffer;

}

<<<<<<< HEAD

//No undo Command exists for the Command
Command* CommandInvalid::getInverseCommand(){

	return nullptr;

}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

//Default constructor to create a new Command Invalid
CommandInvalid::CommandInvalid(string userInput){

	_userInput = userInput;

}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

=======
Command* CommandInvalid::getInverseCommand(){
	return nullptr;
}

>>>>>>> origin/master
char CommandInvalid::buffer[255];
const string CommandInvalid::INVALID_MESSAGE_FORMAT 
	= "Invalid command format: %s";
