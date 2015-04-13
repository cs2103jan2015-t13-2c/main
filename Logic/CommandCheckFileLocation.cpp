//@author A0094024M

/*
This class is to check the directory location of the save file for TASKKY.
Functionalities include showing the directory in which the save file will be written.
*/

#include "CommandCheckFileLocation.h"

/*
* ====================================================================
*  Constructors, Modifiers, Accessors and Destructors
* ====================================================================
*/

//Constructor
CommandCheckFileLocation::CommandCheckFileLocation()
{
}

//Destructor
CommandCheckFileLocation::~CommandCheckFileLocation()
{
}


/*
* ====================================================================
*  Inherited Functions
* ====================================================================
*/

//This function executes the checkfileloc command. It will access the file containing
//the directory and return the save file directory.
//
//@param: none
//@return: save file directory
string CommandCheckFileLocation::execute(){

	ostringstream oss;
	string currentName;

	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	currentName = getFileLocation();
	if (currentName == DEFAULT_STRING){
		return SAVE_FILE_AT_DEFAULT;
	} else {
		sprintf(buffer, SAVE_FILE_AT.c_str(), currentName.c_str());
		return buffer;
	}

}

//There is no undo function for check file location, hence this function returns a null pointer
//
//@param: none
//@return: null pointer
Command* CommandCheckFileLocation::getInverseCommand(){
	return nullptr;
}


/*
* ====================================================================
*  Second Abstractions
* ====================================================================
*/

//Opens the file location and returns the directory.
//
//@param: none
//@return: save file directory
string CommandCheckFileLocation::getFileLocation(){

	string currentName;
	checkDirectoryTXT();
	
	ifstream readFile(DIRECTORY_TXT.c_str());
	if (readFile.is_open()){
		getline(readFile, currentName);
		if (currentName.empty()) {
			return DEFAULT_STRING;
		}
		else {
			return currentName;
		}
	}
}

void CommandCheckFileLocation::checkDirectoryTXT(){
	if (FILE *file = fopen(DIRECTORY_TXT.c_str(), "r")) {
		fclose(file);
	}
	else {
		FILE* createFile = fopen(DIRECTORY_TXT.c_str(), "wb"); // non-Windows use "w"
		fclose(createFile);
	}
	return;
}

/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

char CommandCheckFileLocation::buffer[255];
const string CommandCheckFileLocation::DEFAULT_STRING = "default";
const string CommandCheckFileLocation::SAVE_FILE_AT_DEFAULT = "Save File is at default location.";
const string CommandCheckFileLocation::SAVE_FILE_AT = "Save File is at %s.";
const string CommandCheckFileLocation::DIRECTORY_TXT = "saveFileLocation.txt";