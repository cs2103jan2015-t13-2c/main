//@author A0122357L

/*
This class contains code that can execute the command "Delete",
which deletes a task by its displayed task number

This class is part of the Command Pattern through abstraction of
the implementation of the Command from the person that uses it,
in the Controller class
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

	return new CommandAdd(taskDetails, taskStartTime, taskEndTime, taskDeadline, taskPriority);
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


//@author A0094024M -unused
//Unused due to code restructuring. Logic of the new Command Delete was intially derived from the code below
/*
command for delete will be "delete /task_name"
keep as comment in case we wanna change to this kind of delete ^^
-adi-
*/

/*
string text = removeFirstWord(userCommand);
ostringstream oss;

vector<Task>::iterator toDelete = determineTaskPosition(text, tempSave);
if (toDelete != tempSave.end()) {
tempSave.erase(toDelete);
oss << "Deleted task " << (*toDelete).getTaskDetails << "from Taskky.\n";
}
else {
oss << "Task not Found.\n";
}


return oss.str();
*/

/*
for delete command "delete /task_number"
*/

/*
ostringstream oss;

string task_number_str = removeFirstWord(userCommand);
int task_number_int = atoi(task_number_str.c_str());

vector<Task>::iterator iter = tempSave.begin();
iter = iter + task_number_int - 1;
string deleted_task_name = (*iter).getTaskDetails();
tempSave.erase(iter);

oss << "Deleted task " << task_number_int << " (" << deleted_task_name << ") from Taskky.\n";

return oss.str();
*/

/*

//This function only useful for the other kind of delete command line,so only implement this with the other delete function
vector<Task>::iterator Taskky::determineTaskPosition(string taskname, vector<Task> &tempSave) {

vector<Task>::iterator iter;
bool isPresent = false;

for (iter = tempSave.begin(); iter != tempSave.end(); ++iter) {
string item = (*iter).getTaskDetails;
size_t found = item.find(taskname);
if (found != string::npos) {
isPresent = true;
return iter;
}
}

if (isPresent == false) {
return tempSave.end();
}

}
*/