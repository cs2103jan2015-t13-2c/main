#include "CommandAdd.h"


CommandAdd::CommandAdd(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
}


CommandAdd::~CommandAdd(){
}

string CommandAdd::execute(){
	TaskManager instance = *TaskManager::getInstance();
	Task taskToAdd = Task(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline,
		_taskPriority);
	instance.addTask(taskToAdd);
	return "Task has been added!";
}

Command* CommandAdd::getInverseCommand(){
	TaskManager* taskManagerInstance = TaskManager::getInstance();
	
	//getting index to delete
	Task taskToAdd = Task(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline,
		_taskPriority);
	int indexToDelete = TaskManager::getIndexToInsert(taskToAdd);

	return new CommandDelete(indexToDelete+1);
}