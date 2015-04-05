#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Command.h"
#include "TaskManager.h"

class CommandCheckFileLocation: public Command
{
public:
	CommandCheckFileLocation();
	~CommandCheckFileLocation();
	virtual string execute();
	virtual Command* getInverseCommand();

	static string getFileLocation();
};

