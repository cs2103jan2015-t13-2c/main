#include "CommandUnmark.h"

const string CommandUnmark::MESSAGE_UNMARKED = "Unmarked Task #%d";
const string CommandUnmark::MESSAGE_NOT_UNMARKED = "Task #%d is already unmarked!";
char CommandUnmark::buffer[255];

CommandUnmark::CommandUnmark(int taskNumber)
{
	_taskNumber = taskNumber;
	_hasInverseCommand = false;
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
		_hasInverseCommand = false;
		sprintf_s(buffer, MESSAGE_NOT_UNMARKED.c_str(), _taskNumber);
		return buffer;
	}
	else{
		_hasInverseCommand = true;
		TaskManager::unmarkTask(_taskNumber);
		sprintf_s(buffer, MESSAGE_UNMARKED.c_str(), _taskNumber);
		return buffer;
	}

}

Command* CommandUnmark::getInverseCommand(){
	if (_hasInverseCommand){
		return new CommandMark(_taskNumber);
	}
	else{
		return nullptr;
	}
}