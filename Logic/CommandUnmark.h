//@author A0122357L
#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandMark.h"

class CommandUnmark: public Command
{
public:
	CommandUnmark(int taskNumber);
	~CommandUnmark();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandUnmark::MESSAGE_UNMARKED;
	static const string CommandUnmark::MESSAGE_NOT_UNMARKED;
	static char CommandUnmark::buffer[255];

	static const string CommandUnmark::ERROR_MESSAGE_COMMAND_TASKNUM;

private:
	int _taskNumber;
};

