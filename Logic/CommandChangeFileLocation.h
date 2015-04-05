#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "Command.h"
#include "TaskManager.h"
#include "Storage.h"
#include "CommandCheckFileLocation.h"
#include "CommandException.h"

using namespace std;

class CommandChangeFileLocation : public Command
{
public:
	CommandChangeFileLocation(string filename);
	~CommandChangeFileLocation();
	virtual string execute();
	virtual Command* getInverseCommand();

	static bool dirExists(const std::string& dirName_in);
	
	static const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_CHANGED;
	static const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_INVALID;
	static const string CommandChangeFileLocation::MESSAGE_NO_FILE_NAME;
	static const string CommandChangeFileLocation::UNKOWN_ERROR;

private:
	string _filename;
	string _prevName;

	
};

