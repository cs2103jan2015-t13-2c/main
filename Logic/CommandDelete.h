#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandAdd.h"
#include "CommandException.h"

using namespace std;

class CommandDelete: public Command
{
public:

	CommandDelete(int taskNumber);

	virtual string execute();

	virtual Command* getInverseCommand();

	static const string CommandDelete::MESSAGE_DELETED;
	static char CommandDelete::buffer[255];
	static const string CommandDelete::ERROR_MESSAGE_COMMAND_TASKNUM;

private:
	int _taskNumber;
};

