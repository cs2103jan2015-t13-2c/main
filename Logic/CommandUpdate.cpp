#include "CommandUpdate.h"

const string CommandUpdate::MESSAGE_UPDATED = "Updated Task #%d!";
char CommandUpdate::buffer[255];

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
	
	//get the task to edit, remove it from vector.
	Task currentTask = TaskManager::getTask(_taskNumber);
	TaskManager::removeTask(_taskNumber);
	
	//editing task to add back to vector
	currentTask.setTaskDetails(_taskDetails);
	currentTask.setTaskStartTime(_taskStartTime);
	currentTask.setTaskEndTime(_taskEndTime);
	currentTask.setTaskDeadline(_taskDeadline);
	currentTask.setTaskRecurrence(_taskRecurrence);
	currentTask.setTaskPriority(_taskPriority);

	//adding task back to vector (but at the back, not fixed)
	instance.addTask(currentTask);

	sprintf_s(buffer, MESSAGE_UPDATED.c_str(), _taskNumber);

	return buffer;
}

Command* CommandUpdate::getInverseCommand(){
	TaskManager* taskManagerInstance = TaskManager::getInstance();
	Task currentTask = TaskManager::getTask(_taskNumber);

	string taskDetails = currentTask.getTaskDetails();
	Date* taskStartTime = currentTask.getTaskStartTime();
	Date* taskEndTime = currentTask.getTaskEndTime();
	Date* taskDeadline = currentTask.getTaskDeadline();
	Task::Recurrence taskRecurrence = currentTask.getTaskRecurrence();
	Task::Priority taskPriority = currentTask.getTaskPriority();

	//no logic for undoing task marked!
	return new CommandUpdate(taskDetails, taskStartTime, taskEndTime, taskDeadline, taskRecurrence, taskPriority,_taskNumber);
}