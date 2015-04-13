//@author A0122357L

#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandDelete.h"

using namespace std;
class CommandAdd: public Command
{
public:

	CommandAdd(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Priority taskPriority);

	virtual string execute();
<<<<<<< HEAD
	
	virtual Command* getInverseCommand();

	static const string CommandAdd::MESSAGE_ADDED;
=======
	virtual Command* getInverseCommand();
>>>>>>> origin/master

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Priority _taskPriority;
};

