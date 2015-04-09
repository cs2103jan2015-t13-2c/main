#pragma once
#include <string>
#include "Date.h"
#include <fstream>

using namespace std;

class ErrorLogger
{
public:

	static const string ErrorLogger::ERROR_TEXT_FILE;
	static const string ErrorLogger::ERROR_MESSAGE_RESET;
	static const string ErrorLogger::ERROR_MESSAGE_DELIMITER;

	static ErrorLogger* getInstance();

	static string getDate();

	static void resetLog();

	static void logError(string error);


private:

	ErrorLogger();

	//copy constructor is private
	ErrorLogger& operator=(ErrorLogger const&){};

	static ErrorLogger *_instance;
};

