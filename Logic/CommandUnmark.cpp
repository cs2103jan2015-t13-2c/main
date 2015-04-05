#include "CommandUnmark.h"

const string CommandUnmark::MESSAGE_UNMARKED = "Unmarked Task #%d";
const string CommandUnmark::MESSAGE_NOT_UNMARKED = "Task #%d is already unmarked!";
char CommandUnmark::buffer[255];

CommandUnmark::CommandUnmark(int taskNumber)
{
	_taskNumber = taskNumber;
}

CommandUnmark::~CommandUnmark()
{
}

string CommandUnmark::execute(){

	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	//get the task to edit
	Task currentTask = TaskManager::getTask(_taskNumber);

	//only mark the task if not already marked
	if (currentTask.getTaskMarked() == false){
		sprintf_s(buffer, MESSAGE_NOT_UNMARKED.c_str(), _taskNumber);
		return buffer;
	}
	else{
		TaskManager::unmarkTask(_taskNumber);
		sprintf_s(buffer, MESSAGE_UNMARKED.c_str(), _taskNumber);
		return buffer;
	}

}

Command* CommandUnmark::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > taskManagerInstance->getNumberOfTasks()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}
	Task currentTask = TaskManager::getTask(_taskNumber);

	if (currentTask.getTaskMarked()){
		return new CommandMark(_taskNumber);
	}
	else{
		return nullptr;
	}
}

const string CommandUnmark::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";