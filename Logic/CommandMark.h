//@author A0122357L
#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandUnmark.h"
#include "CommandException.h"

class CommandMark: public Command
{
public:
	CommandMark(int taskNumber);
	~CommandMark();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandMark::MESSAGE_MARKED;
	static const string CommandMark::MESSAGE_NOT_MARKED;
	static char CommandMark::buffer[255];

	static const string CommandMark::ERROR_MESSAGE_COMMAND_TASKNUM;

private:
	int _taskNumber;
};

