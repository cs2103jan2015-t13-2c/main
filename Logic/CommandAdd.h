#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>

using namespace std;
class CommandAdd: public Command
{
public:
	CommandAdd(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Recurrence taskRecurrence,
		Task::Priority taskPriority);

	~CommandAdd();
	virtual string execute();

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Recurrence _taskRecurrence;
	Task::Priority _taskPriority;
};

