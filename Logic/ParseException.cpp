#include "ParseException.h"

ParseException::ParseException(std::string input){
	
	ParseException::input = input;
	message = ERROR_MESSAGE_PARSING;
	errorCode = ERROR_CODE_PARSING;
	
}

string ParseException::getMessage(){
	return message + getInput();
}

string ParseException::getInput(){
	return input;
}

const string ParseException::ERROR_MESSAGE_PARSING = "Input parsing error: ";
const int ParseException::ERROR_CODE_PARSING = 1;