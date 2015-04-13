//@author A0113716M
#pragma once
#include <string>
#include <vector>
#include "TaskManager.h"
#include "Command.h"
#include <sstream>
#include "Task.h"
#include <iomanip>

using namespace std;

class CommandDisplay: public Command
{
public:
	CommandDisplay();
	~CommandDisplay();
	virtual string execute();
	virtual Command* getInverseCommand();
	string CommandDisplay::printTaskToUser(Task toPrint, int taskNumber);
};

