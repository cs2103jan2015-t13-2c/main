#include "CommandChangeFileLocation.h"

const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_CHANGED = "File location changed succesfully";


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
		} else {
			_prevName = currentName;
		}
	}

	ofstream writeFile("saveFileLocation.txt");
	if (writeFile.is_open()){
		writeFile << _filename;
		writeFile.close();
	}

	return MESSAGE_FILE_LOCATION_CHANGED;
}

Command* CommandChangeFileLocation::getInverseCommand(){
	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	return new CommandChangeFileLocation(_prevName);
}