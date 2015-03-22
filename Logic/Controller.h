#pragma once
#include <string>

#include "Command.h"
#include "CommandBuilder.h"
#include "TaskManager.h"

using namespace std;

class Controller
{
public:

	static Controller* getInstance();

	static string processUserInput(string userInput);

private:

	//copy constructor is private
	Controller& operator=(Controller const&){};

	static Controller *_instance;
	
	Controller();
	
};

