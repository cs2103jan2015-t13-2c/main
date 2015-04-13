//@author A0122357L

/*
This class contains code that can execute the command "Mark",
which marks a task as done

When a task is marked as done, it will be shifted in TaskManager
to another task vector which contain all the marked tasks. This 
is to support easy display to the UI

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
*/

#include "CommandMark.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method will mark a task as done 
//The task to be marked will be accessed by its task number 
//It will then give feedback to the user accordingly
//
//@return feedback to user
string CommandMark::execute(){

	TaskManager instance = *TaskManager::getInstance();

	//get the task to edit
	Task currentTask = TaskManager::getTask(_taskNumber);

	//only mark the task if not already marked
	if (currentTask.getTaskMarked() == true){

		sprintf_s(buffer, MESSAGE_NOT_MARKED.c_str(), _taskNumber);

		return buffer;

	}

	else{

		TaskManager::markTask(_taskNumber);

		sprintf_s(buffer, MESSAGE_MARKED.c_str(), _taskNumber);

		return buffer;
	}
}


//This method will create the Command to undo this mark command
//
//@return Command* that undoes the current command
Command* CommandMark::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();

	if (_taskNumber <= 0 || _taskNumber > taskManagerInstance->getNumberOfTasks()){

		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);

	}

	Task currentTask = TaskManager::getTask(_taskNumber);

	//only has an inverse command if task not already marked
	if (!currentTask.getTaskMarked()){

		//preparing marked task to add
		Task currentTask = TaskManager::getTask(_taskNumber);
		string taskDetails = currentTask.getTaskDetails();
		Date* taskStartTime = currentTask.getTaskStartTime();
		Date* taskEndTime = currentTask.getTaskEndTime();
		Date* taskDeadline = currentTask.getTaskDeadline();
		Task::Priority taskPriority = currentTask.getTaskPriority();
		Task taskToAdd = Task(taskDetails, taskStartTime, 
			taskEndTime, taskDeadline, taskPriority);
		taskToAdd.setTaskMarked(true);

		vector<Task> allCurr = *TaskManager::getAllCurrentTasks();
		//deleting unmarked task
		TaskManager::removeTask(_taskNumber);
		//allCurr = *TaskManager::getAllCurrentTasks();

		//getting index to add new updated task to
		int indexToUnmark = TaskManager::getIndexToInsert(taskToAdd);

		//adding back unmarked task
		taskToAdd.setTaskMarked(false);

		TaskManager::addTask(taskToAdd);
		
		return new CommandUnmark(indexToUnmark + 1);
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

//Default constructor for creating a new Command Mark
//
//@param task number to mark
CommandMark::CommandMark(int taskNumber){

	_taskNumber = taskNumber;

}


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandMark::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";
const string CommandMark::MESSAGE_MARKED = "Marked Task #%d";
const string CommandMark::MESSAGE_NOT_MARKED = "Task #%d is already marked!";
char CommandMark::buffer[255];