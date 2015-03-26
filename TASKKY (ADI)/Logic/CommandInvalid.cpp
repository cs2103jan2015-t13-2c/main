#include "CommandInvalid.h"


CommandInvalid::CommandInvalid(string userInput)
{
	_userInput = userInput;
}


CommandInvalid::~CommandInvalid()
{
}

string CommandInvalid::execute(){
	sprintf_s(buffer, INVALID_MESSAGE_FORMAT.c_str(), _userInput.c_str());
	return buffer;
}

Command* CommandInvalid::getInverseCommand(){
	return nullptr;
}

char CommandInvalid::buffer[255];
const string CommandInvalid::INVALID_MESSAGE_FORMAT = "Invalid command format: %s";