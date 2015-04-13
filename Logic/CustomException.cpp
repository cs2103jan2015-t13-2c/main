//@author A0122357L

#include "CustomException.h"

CustomException::CustomException(){
	message = "Error!";
	errorCode = 0;
	fatal = false;
}

CustomException::CustomException(string message){
	CustomException::message = message;
	errorCode = 0;
	fatal = false;
}
string CustomException::getMessage() {
	return message;
}

int CustomException::getErrorCode() {
	return errorCode;
}

bool CustomException::isFatal() {
	return fatal;
}
