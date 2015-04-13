//@author A0122357L
#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandException.h"

class CommandUpdate: public Command
{
public:

	CommandUpdate(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Priority taskPriority,
		int taskNumber);

	virtual string execute();

	virtual Command* getInverseCommand();

	static const string CommandUpdate::MESSAGE_UPDATED;
	static char CommandUpdate::buffer[255];
	static const string CommandUpdate::ERROR_MESSAGE_COMMAND_TASKNUM;

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Priority _taskPriority;
	int _taskNumber;
};

