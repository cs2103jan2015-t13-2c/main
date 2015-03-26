#include "CommandMark.h"

const string CommandMark::MESSAGE_MARKED = "Marked Task #%d";
const string CommandMark::MESSAGE_NOT_MARKED = "Task #%d is already marked!";
char CommandMark::buffer[255];

CommandMark::CommandMark(int taskNumber)
{
	_taskNumber = taskNumber;
	_hasInverseCommand = false;
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
		_hasInverseCommand = false;
		sprintf_s(buffer, MESSAGE_NOT_MARKED.c_str(), _taskNumber);
		return buffer;
	}
	else{
		_hasInverseCommand = true;
		TaskManager::markTask(_taskNumber);
		sprintf_s(buffer, MESSAGE_MARKED.c_str(), _taskNumber);
		return buffer;
	}
	
}

Command* CommandMark::getInverseCommand(){
	if (_hasInverseCommand){
		return new CommandUnmark(_taskNumber);
	}
	else{
		return nullptr;
	}
}