//@author A0094024M

/*
This class is to manipulate the location of the save file for TASKKY.

Functionalities include changing the directory in which the save file will be written. Doing
so will result in the save file being physically moved to a new location as well.

The file location can also be change to "default", in which it will move the save file location
to the original directory (same directory as the .exe file).

Save.json should not be tampered by user manually, as editing it may cause error in parsing
should the format of the document does not match the JSON Object standard.
*/

#include "CommandChangeFileLocation.h"

/*
* ====================================================================
*  Constructors, Modifiers, Accessors and Destructors
* ====================================================================
*/

//Constructor
CommandChangeFileLocation::CommandChangeFileLocation(string filename)
{
	_prevName = CommandCheckFileLocation::CommandCheckFileLocation().getFileLocation();
	_filename = filename;
}

//Default Destructor
CommandChangeFileLocation::~CommandChangeFileLocation()
{
}


/*
* ====================================================================
*  Inherited Functions
* ====================================================================
*/

//This function executes the Change File Location function. Change the save directory
//and physically move the save file into the new directory
//
//@param: none
//@return: feedback string
string CommandChangeFileLocation::execute(){
	
	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();
	
	if (_filename == ""){
		throw CommandException(MESSAGE_NO_FILE_NAME);
	} else if (dirExists(_filename) || _filename == "default"){		//check if file exists or directory is at default location
		checkFileDirectory();
		extractDirectoryInformation();
		moveSaveFile();
		return MESSAGE_FILE_LOCATION_CHANGED;
	} else if (!dirExists(_filename)){
		throw CommandException(MESSAGE_FILE_LOCATION_INVALID);
	} else {
		throw CommandException(UNKOWN_ERROR);
	}
}

//Create a new CommandChangeFileLocation object for undo with the previous directory
//
//@param: previous file directory
//@return: pointer for the new CommandChangeFileLocation object
Command* CommandChangeFileLocation::getInverseCommand(){
	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	return new CommandChangeFileLocation(_prevName);
}

/*
* ====================================================================
*  Second Abstractions
* ====================================================================
*/

//This function checks if the directory exists.
//
//@param = directory to be checked
//@return = boolean value (true/false)
bool CommandChangeFileLocation::dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

//This function checks if the file that contains the directory exists. If it doesn't exist,
//create a new file that will contain the save directory.
//
//@param = none
//@return = none
void CommandChangeFileLocation::checkFileDirectory(){
	if (FILE *file = fopen("saveFileLocation.txt", "r")) {
		fclose(file);
	}
	else {
		FILE* createFile = fopen("saveFileLocation.txt", "wb"); // non-Windows use "w"
		fclose(createFile);
	}
	return;
}

//This function saves the information from the previous directory (for undo function).
//
//@param = none
//@return = none
void CommandChangeFileLocation::extractDirectoryInformation(){
	string currentName;
	ifstream readFile("saveFileLocation.txt");
	if (readFile.is_open()){
		getline(readFile, currentName);
		if (currentName.empty()) {
			_prevName = "default";
		}
		else {
			_prevName = currentName;
		}
	}
	return;
}

//This function changes that directory information contained in the file. After which it
//will delete the old save file and create a new save file in the new location.
//
//@param = none
//@return = none
void CommandChangeFileLocation::moveSaveFile(){
	string toRemove = _prevName + "/Save.json";
	remove(toRemove.c_str());

	ofstream writeFile("saveFileLocation.txt");
	if (writeFile.is_open()){
		writeFile << _filename;
		writeFile.close();
	}

	TaskManager::saveTasks();

	return;
}

/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_CHANGED = "File location changed successfully";
const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_INVALID = "Invalid file location, directory doesn't exist!";
const string CommandChangeFileLocation::MESSAGE_NO_FILE_NAME = "Please specify file location after the command 'changefileloc'";
const string CommandChangeFileLocation::UNKOWN_ERROR = "The program has encountered unknown error, please contact program developers. In the meantime you can try the following:\n1. Change command parameters";