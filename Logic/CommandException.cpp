#include "CommandException.h"

CommandException::CommandException(std::string command){

	CommandException::command = command;
	message = ERROR_MESSAGE_COMMAND;
	errorCode = ERROR_CODE_COMMAND;

}

string CommandException::getMessage(){
	return message + getCommand();
}

string CommandException::getCommand(){
	return command;
}

const string CommandException::ERROR_MESSAGE_COMMAND = "Invalid Command: ";
const int CommandException::ERROR_CODE_COMMAND = 2;