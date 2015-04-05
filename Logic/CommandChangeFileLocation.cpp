#include "CommandChangeFileLocation.h"

const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_CHANGED = "File location changed succesfully";
const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_INVALID = "Invalid file location, directory doesn't exist!";
const string CommandChangeFileLocation::MESSAGE_NO_FILE_NAME = "Please specify file location after the command 'changefileloc'";
const string CommandChangeFileLocation::UNKOWN_ERROR = "The program has encountered unknown error, please contact program developers. In the meantime you can try the following:\n1. Change command parameters";

CommandChangeFileLocation::CommandChangeFileLocation(string filename)
{
	_prevName = CommandCheckFileLocation::CommandCheckFileLocation().getFileLocation();
	_filename = filename;
}


CommandChangeFileLocation::~CommandChangeFileLocation()
{
}

string CommandChangeFileLocation::execute(){
	
	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();
	
	if (_filename == ""){
		throw CommandException(MESSAGE_NO_FILE_NAME);
	} else if (dirExists(_filename) || _filename == "default"){

		if (FILE *file = fopen("saveFileLocation.txt", "r")) {
			fclose(file);
		}
		else {
			FILE* createFile = fopen("saveFileLocation.txt", "wb"); // non-Windows use "w"
			fclose(createFile);

		}

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

		string toRemove = _prevName + "/Save.json";
		remove(toRemove.c_str());

		ofstream writeFile("saveFileLocation.txt");
		if (writeFile.is_open()){
			writeFile << _filename;
			writeFile.close();
		}

		TaskManager::saveTasks();

		return MESSAGE_FILE_LOCATION_CHANGED;
	} else if (!dirExists(_filename)){
		throw CommandException(MESSAGE_FILE_LOCATION_INVALID);
	} else {
		throw CommandException(UNKOWN_ERROR);
	}
}

Command* CommandChangeFileLocation::getInverseCommand(){
	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	return new CommandChangeFileLocation(_prevName);
}


bool CommandChangeFileLocation::dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
