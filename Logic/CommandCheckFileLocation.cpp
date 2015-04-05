#include "CommandCheckFileLocation.h"


CommandCheckFileLocation::CommandCheckFileLocation()
{
}


CommandCheckFileLocation::~CommandCheckFileLocation()
{
}

string CommandCheckFileLocation::execute(){

	ostringstream oss;
	string currentName;

	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	currentName = getFileLocation();

	if (currentName == "default"){
		oss << "Save file is at default location";
	} else {
		oss << "Save file is at " << currentName;
	}

	return oss.str();

}

Command* CommandCheckFileLocation::getInverseCommand(){
	return nullptr;
}

string CommandCheckFileLocation::getFileLocation(){
	
	ostringstream oss;
	string currentName;

	if (FILE *file = fopen("saveFileLocation.txt", "r")) {
		fclose(file);
	}
	else {
		FILE* createFile = fopen("saveFileLocation.txt", "wb"); // non-Windows use "w"
		fclose(createFile);

	}

	ifstream readFile("saveFileLocation.txt");
	if (readFile.is_open()){
		getline(readFile, currentName);
		if (currentName.empty()) {
			oss << "default";
		}
		else {
			oss << currentName;
		}
	}

	return oss.str();
}