#include "CommandAdd.h"


CommandAdd::CommandAdd(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Recurrence taskRecurrence,
	Task::Priority taskPriority){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskRecurrence = taskRecurrence;
	_taskPriority = taskPriority;
}


CommandAdd::~CommandAdd(){
}

string CommandAdd::execute(){
	TaskManager instance = *TaskManager::getInstance();
	Task taskToAdd = Task(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline,
		_taskRecurrence, _taskPriority);
	instance.addTask(taskToAdd);
	return "Task has been added!";
}

Command* CommandAdd::getInverseCommand(){
	TaskManager* taskManagerInstance = TaskManager::getInstance();
	//no logic to add tasks in chronological order yet, just adding tasks to the bottom
	//thats why i just delete task from the bottom
	int taskNumber = taskManagerInstance->getNumberOfTasks();
	return new CommandDelete(taskNumber+1);
}