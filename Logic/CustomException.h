//@author A0122357L
#pragma once
#include <string>

using namespace std;

class CustomException
{

protected:

	std::string message;
	int errorCode;
	bool fatal;

public:
	CustomException();
	CustomException(std::string message);
	std::string getMessage();
	int getErrorCode();
	bool isFatal();

};

