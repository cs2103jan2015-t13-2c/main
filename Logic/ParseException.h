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
	inline string getMessage();
	inline int getErrorCode();
	inline string getInput();

};
