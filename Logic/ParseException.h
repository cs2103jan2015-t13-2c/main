//@author A0122357L
#pragma once
#include <string>
#include "CustomException.h"

using namespace std;

class ParseException: public CustomException
{

private:

	std::string input;

public:

	ParseException(std::string input);
	string getMessage();
	int getErrorCode();
	string getInput();

	static const string ParseException::ERROR_MESSAGE_PARSING;
	static const int ParseException::ERROR_CODE_PARSING;

};
