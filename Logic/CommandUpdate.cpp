#include "CommandUpdate.h"

const string CommandUpdate::MESSAGE_UPDATED = "Updated Task #%d!";
char CommandUpdate::buffer[255];

CommandUpdate::CommandUpdate(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority,
	int taskNumber){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
	_taskNumber = taskNumber;
}


CommandUpdate::~CommandUpdate()
{
}

string CommandUpdate::execute(){

	//get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();
	
	if (_taskNumber <= 0 || _taskNumber > instance.getNumberOfTasks()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}

	//get the task to edit, remove it from vector.
	Task currentTask = TaskManager::getTask(_taskNumber);
	TaskManager::removeTask(_taskNumber);
	
	//editing task to add back to vector
	currentTask.setTaskDetails(_taskDetails);
	currentTask.setTaskStartTime(_taskStartTime);
	currentTask.setTaskEndTime(_taskEndTime);
	currentTask.setTaskDeadline(_taskDeadline);
	currentTask.setTaskPriority(_taskPriority);

	//adding task back to vector (but at the back, not fixed)
	instance.addTask(currentTask);

	sprintf_s(buffer, MESSAGE_UPDATED.c_str(), _taskNumber);

	return buffer;
}

Command* CommandUpdate::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();
	
	if (_taskNumber <= 0 || _taskNumber > taskManagerInstance->getNumberOfTasks()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}

	//preparing old task to update
	Task currentTask = TaskManager::getTask(_taskNumber);
	string taskDetails = currentTask.getTaskDetails();
	Date* taskStartTime = currentTask.getTaskStartTime();
	Date* taskEndTime = currentTask.getTaskEndTime();
	Date* taskDeadline = currentTask.getTaskDeadline();
	Task::Priority taskPriority = currentTask.getTaskPriority();

	//preparing new task to add
	Task taskToAdd = Task(_taskDetails, _taskStartTime, _taskEndTime, _taskDeadline, _taskPriority);
	taskToAdd.setTaskMarked(currentTask.getTaskMarked());

	//deleting old task
	TaskManager::removeTask(_taskNumber);

	//adding and deleting new task to get index
	int indexToUpdate = TaskManager::addTask(taskToAdd);
	TaskManager::removeTask(indexToUpdate + 1);

	//adding back old task
	TaskManager::addTask(currentTask);

	//undoing task
	return new CommandUpdate(taskDetails, taskStartTime, taskEndTime, taskDeadline, taskPriority, indexToUpdate+1);
}

const string CommandUpdate::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";