#include "CommandMark.h"

CommandMark::CommandMark(int taskNumber)
{
	_taskNumber = taskNumber;
}


CommandMark::~CommandMark()
{
}

string CommandMark::execute(){

	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	//get the task to edit
	Task currentTask = TaskManager::getTask(_taskNumber);
	
	//only mark the task if not already marked
	if (currentTask.getTaskMarked()==true){
		sprintf_s(buffer, MESSAGE_NOT_MARKED.c_str(), _taskNumber);
		return buffer;
	}
	else{
		TaskManager::markTask(_taskNumber);
		sprintf_s(buffer, MESSAGE_MARKED.c_str(), _taskNumber);
		return buffer;
	}
	
}

Command* CommandMark::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > taskManagerInstance->getNumberOfTasks()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}
	Task currentTask = TaskManager::getTask(_taskNumber);

	if (!currentTask.getTaskMarked()){

		//preparing marked task to add
		Task currentTask = TaskManager::getTask(_taskNumber);
		string taskDetails = currentTask.getTaskDetails();
		Date* taskStartTime = currentTask.getTaskStartTime();
		Date* taskEndTime = currentTask.getTaskEndTime();
		Date* taskDeadline = currentTask.getTaskDeadline();
		Task::Priority taskPriority = currentTask.getTaskPriority();
		Task taskToAdd = Task(taskDetails, taskStartTime, taskEndTime, taskDeadline, taskPriority);
		taskToAdd.setTaskMarked(true);

		//deleting unmarked task
		TaskManager::removeTask(_taskNumber);

		//adding and deleting marked task to get index
		int indexToUnmark = TaskManager::addTask(taskToAdd);
		TaskManager::removeTask(indexToUnmark + 1);

		//adding back unmarked task
		taskToAdd.setTaskMarked(false);
		TaskManager::addTask(taskToAdd);

		return new CommandUnmark(indexToUnmark + 1);
	}
	else{
		return nullptr;
	}
}

const string CommandMark::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";
const string CommandMark::MESSAGE_MARKED = "Marked Task #%d";
const string CommandMark::MESSAGE_NOT_MARKED = "Task #%d is already marked!";
char CommandMark::buffer[255];