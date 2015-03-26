#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>

class CommandUpdate: public Command
{
public:
	CommandUpdate(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Recurrence taskRecurrence,
		Task::Priority taskPriority,
		int taskNumber);
	~CommandUpdate();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandUpdate::MESSAGE_UPDATED;
	static char CommandUpdate::buffer[255];

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Recurrence _taskRecurrence;
	Task::Priority _taskPriority;
	int _taskNumber;
};

