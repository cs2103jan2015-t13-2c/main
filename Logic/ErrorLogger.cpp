//@author A0122357L

#include "ErrorLogger.h"

ErrorLogger* ErrorLogger::_instance = NULL;

ErrorLogger::ErrorLogger()
{
	resetLog();
}

ErrorLogger* ErrorLogger::getInstance(){
	if (!_instance)
		_instance = new ErrorLogger;
	return _instance;
}

//Gets the date so that it can be logged down
string ErrorLogger::getDate(){

	return Date().toString();

}

void ErrorLogger::resetLog(){

	ofstream errorLog(ERROR_TEXT_FILE.c_str());
	errorLog << ERROR_MESSAGE_RESET << getDate();
	errorLog << endl << endl;
	errorLog.close();

}

void ErrorLogger::logError(string error){

	ofstream errorLog(ERROR_TEXT_FILE.c_str(), fstream::app);
	errorLog << getDate();
	errorLog << ERROR_MESSAGE_DELIMITER << error << ERROR_MESSAGE_DELIMITER;
	errorLog << endl << endl;
	errorLog.close();

}

const string ErrorLogger::ERROR_TEXT_FILE = "ErrorLog.txt";
const string ErrorLogger::ERROR_MESSAGE_RESET = "Error Log Resetted on: ";
const string ErrorLogger::ERROR_MESSAGE_DELIMITER = " | ";