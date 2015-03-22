#include "CommandUpdate.h"


CommandUpdate::CommandUpdate(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Recurrence taskRecurrence,
	Task::Priority taskPriority,
	int taskNumber){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskRecurrence = taskRecurrence;
	_taskPriority = taskPriority;
	_taskNumber = taskNumber;
}


CommandUpdate::~CommandUpdate()
{
}

string CommandUpdate::execute(){

	//get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();
	//taskToUpdate = instance.getTask(_taskNumber);
	return "Task updated!";
}