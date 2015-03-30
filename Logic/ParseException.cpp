#include "ParseException.h"

ParseException::ParseException(std::string input){
	
	ParseException::input = input;
	message = "Input parsing error: ";
	errorCode = 1;
	
}

inline string ParseException::getMessage(){
	return message + getInput();
}

inline string ParseException::getInput(){
	return input;
}