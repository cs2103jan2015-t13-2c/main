//@author A0122357L
<<<<<<< HEAD

/*
This class contains code that can execute the command "Add",
which adds a new Task into the application

When a task is added, it will be autosorted based on its attributes

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
*/

=======
>>>>>>> origin/master
#include "CommandAdd.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This method will create a new task object, with the attributes given 
//from the Parser and CommandBuilder classes. 
//It will then give feedback to the user accordingly
//
//@return feedback to user
string CommandAdd::execute(){

	TaskManager instance = *TaskManager::getInstance();

	Task taskToAdd = Task(_taskDetails, _taskStartTime, 
		_taskEndTime, _taskDeadline, _taskPriority);

	instance.addTask(taskToAdd);

	return MESSAGE_ADDED;
}


//This method will create the Command to undo this add command
//
//@return Command* that undoes the current command
Command* CommandAdd::getInverseCommand(){

	TaskManager* taskManagerInstance = TaskManager::getInstance();
	
	//getting index to delete
	Task taskToAdd = Task(_taskDetails, _taskStartTime, 
		_taskEndTime, _taskDeadline, _taskPriority);

	int indexToDelete = TaskManager::getIndexToInsert(taskToAdd);

	return new CommandDelete(indexToDelete+1);
}


/*
* ====================================================================
*  Constructors
* ====================================================================
*/

//Default constuctor for creating a new Command Add
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


<<<<<<< HEAD
/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

const string CommandAdd::MESSAGE_ADDED = "Task has been added!";
=======
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
	int indexToDelete = TaskManager::addTask(taskToAdd);
	TaskManager::removeTask(indexToDelete+1);

	return new CommandDelete(indexToDelete+1);
}
>>>>>>> origin/master
