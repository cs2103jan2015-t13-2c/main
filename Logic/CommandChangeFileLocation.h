#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Command.h"
#include "TaskManager.h"
#include "CommandCheckFileLocation.h"

using namespace std;

class CommandChangeFileLocation : public Command
{
public:
	CommandChangeFileLocation(string filename);
	~CommandChangeFileLocation();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandChangeFileLocation::MESSAGE_FILE_LOCATION_CHANGED;

private:
	string _filename;
	string _prevName;

	
};

