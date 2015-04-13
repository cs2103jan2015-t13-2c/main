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

private:
	static void checkDirectoryTXT();

	static char buffer[255];
	static const string DEFAULT_STRING;
	static const string SAVE_FILE_AT_DEFAULT;
	static const string SAVE_FILE_AT;
	static const string DIRECTORY_TXT;
};

