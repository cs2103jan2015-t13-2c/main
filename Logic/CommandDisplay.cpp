//@author generated
#include "CommandDisplay.h"

CommandDisplay::CommandDisplay(){
}


CommandDisplay::~CommandDisplay(){
}

//@author A0113716M
string CommandDisplay::execute(){
	ostringstream oss;
	vector<Task>::iterator iter;

	TaskManager* taskManagerInstance = TaskManager::getInstance();
	vector<Task>* allTasksPtr = taskManagerInstance->getAllCurrentTasks();
	if (allTasksPtr->size() == 0){
		return "There are no tasks to display!";
	}
	vector<Task> allTasks = *allTasksPtr;

	//Counts Task Number
	int taskNumber = 1;
	for (iter = allTasks.begin(); iter != allTasks.end(); ++iter) {
		oss << printTaskToUser(*iter, taskNumber);
		taskNumber++;
	}
	return oss.str();
}

Command* CommandDisplay::getInverseCommand(){
	return nullptr;
}

string CommandDisplay::printTaskToUser(Task toPrint, int taskNumber) {

	ostringstream oss;

	//Prints Task Number
	oss << "====================================================" << endl;
	oss << "Task #" << taskNumber << endl;
	oss << "====================================================" << endl;

	//Prints Task Details
	oss << "TASKNAME: ";
	oss << (toPrint).getTaskDetails() << endl;


	//Prints Task Start/End Time or Deadline (if any)
	Task::Type checkType = (toPrint).getTaskType();
	switch (checkType) {
	case Task::TIMED: {
		oss << "START: " << (toPrint).getTaskStartTime()->toString() << endl;
		oss << "END: " << (toPrint).getTaskEndTime()->toString() << endl;
		break;
	} case Task::DEADLINE: {
		oss << "DEADLINE: " << (toPrint).getTaskDeadline()->toString() << endl;
		break;
	} default:
		break;
	}

	//Prints Task Priority
	Task::Priority checkPri = (toPrint).getTaskPriority();
	switch (checkPri) {
	case Task::HIGH: {
		oss << "PRIORITY: HIGH" << endl;
		break;
	} default: {
		break;
	}
	}

	bool checkMarked = (toPrint).getTaskMarked();
	if (checkMarked) {
		oss << "DONE!" << endl;
	}

	return oss.str();
}