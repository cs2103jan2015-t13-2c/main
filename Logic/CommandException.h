//@author A0122357L
#pragma once
#include <string>
#include "CustomException.h"

using namespace std;

class CommandException : public CustomException
{

private:

	std::string command;

public:

	CommandException(std::string command);
	string getMessage();
	int getErrorCode();
	string getCommand();

	static const string CommandException::ERROR_MESSAGE_COMMAND;
	static const int CommandException::ERROR_CODE_COMMAND;

};
