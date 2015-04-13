//@author A0122357L

/*
This class contains code that can execute the command "Unmark",
which unmarks a done task

When a marked task is unmarked, it will be shifted in TaskManager
from a task vector containing all the marked tasks to a task
vector containing all the unmarked tasks
This is to support easy display to the UI

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
*/

#include "CommandUnmark.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method will unmark a done task
//The task to be unmarked will be accessed by its task number 
//It will then give feedback to the user accordingly
//
//@return feedback to user
string CommandUnmark::execute(){

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


//This method will create the Command to undo this unmark command
//
//@return Command* that undoes the current command
Command* CommandUnmark::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > taskManagerInstance->getNumberOfTasks()){

		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);

	}

	Task currentTask = TaskManager::getTask(_taskNumber);

	//only has an inverse command if task not already unmarked
	if (currentTask.getTaskMarked()){

		//preparing unmarked task to add
		Task currentTask = TaskManager::getTask(_taskNumber);
		string taskDetails = currentTask.getTaskDetails();
		Date* taskStartTime = currentTask.getTaskStartTime();
		Date* taskEndTime = currentTask.getTaskEndTime();
		Date* taskDeadline = currentTask.getTaskDeadline();
		Task::Priority taskPriority = currentTask.getTaskPriority();
		Task taskToAdd = Task(taskDetails, taskStartTime, taskEndTime, taskDeadline, taskPriority);

		//deleting marked task
		TaskManager::removeTask(_taskNumber);

		//getting index to add new updated task to
		int indexToMark = TaskManager::getIndexToInsert(taskToAdd);

		//adding back marked task
		taskToAdd.setTaskMarked(true);
		TaskManager::addTask(taskToAdd);

		return new CommandMark(indexToMark + 1);
	}

	else{

		return nullptr;

	}
}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

CommandUnmark::CommandUnmark(int taskNumber){

	_taskNumber = taskNumber;

}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandUnmark::MESSAGE_UNMARKED = "Unmarked Task #%d";
const string CommandUnmark::MESSAGE_NOT_UNMARKED = "Task #%d is already unmarked!";
const string CommandUnmark::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";
char CommandUnmark::buffer[255];
