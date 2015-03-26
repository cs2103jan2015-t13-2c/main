#pragma once
#include <string>
#include <vector>
#include "Command.h"

using namespace std;

class CommandInvalid: public Command
{
public:
	CommandInvalid(string userInput);
	~CommandInvalid();
	virtual string execute();
	virtual Command* getInverseCommand();

	static char CommandInvalid::buffer[255];
	static const string CommandInvalid::INVALID_MESSAGE_FORMAT;
private:
	string _userInput;
};

