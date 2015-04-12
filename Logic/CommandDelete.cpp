/*
This class contains code that can execute the command "Delete",
which deletes a task by its displayed task number

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class

@author: A0122357L Lee Kai Yi
*/

#include "CommandDelete.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method will delete a task which is accessed by its task number 
//It will then give feedback to the user accordingly
//
//@return feedback to user
string CommandDelete::execute(){

	// get the instance of the Task from task manager
	TaskManager instance = *TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > instance.getNumberOfTasks()){

		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);

	}

	//get the task to edit, remove it from vector.
	Task currentTask = TaskManager::getTask(_taskNumber);

	TaskManager::removeTask(_taskNumber);

	sprintf_s(buffer, MESSAGE_DELETED.c_str(), _taskNumber);

	return buffer;
}


//This method will create the Command to undo this delete command
//
//@return Command* that undoes the current command
Command* CommandDelete::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > 
		taskManagerInstance->getNumberOfTasks()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}

	//getting the task to add back 
	Task currentTask = TaskManager::getTask(_taskNumber);
	string taskDetails = currentTask.getTaskDetails();
	Date* taskStartTime = currentTask.getTaskStartTime();
	Date* taskEndTime = currentTask.getTaskEndTime();
	Date* taskDeadline = currentTask.getTaskDeadline();
	Task::Priority taskPriority = currentTask.getTaskPriority();

	return new CommandAdd(taskDetails, taskStartTime, 
		taskEndTime, taskDeadline, taskPriority);
}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

//Default constructor for creating a new Command Delete
CommandDelete::CommandDelete(int taskNumber){

	_taskNumber = taskNumber;

}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandDelete::ERROR_MESSAGE_COMMAND_TASKNUM 
	= "Invalid task number!";
const string CommandDelete::MESSAGE_DELETED = "Deleted Task #%d";
char CommandDelete::buffer[255];