#include "CommandDisplay.h"


CommandDisplay::CommandDisplay()
{
}


CommandDisplay::~CommandDisplay()
{
}

string CommandDisplay::execute(){
	ostringstream oss;
	vector<Task>::iterator iter;
	
	TaskManager* taskManagerInstance = TaskManager::getInstance();
	vector<Task>* allTasksPtr = taskManagerInstance->getAllCurrentTasks();
	vector<Task> allTasks = *allTasksPtr;

	//Prints Task Number
	int taskNumber=1;
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
	oss << "=============================" << endl;
	oss << "Task #" << setw(8) << setfill('0') << taskNumber << endl;
	oss << "=============================" << endl;

	oss << (toPrint).getTaskDetails() << endl;

	//Prints Task Start/End Time or Deadline (if any)
	Task::Type checkType = (toPrint).getTaskType();
	switch (checkType) {
	case Task::TIMED: {
		oss << "START: " << (toPrint).getTaskStartTime()->toString() << endl;
		oss << "END: " << (toPrint).getTaskEndTime()->toString() << endl;
		break;
	}
	case Task::DEADLINE: {
		oss << "DEADLINE: " << (toPrint).getTaskDeadline()->toString() << endl;
		break;
	}
	default:
		break;
	}

	//Prints Task Recurrence (if any)
	Task::Recurrence checkRec = (toPrint).getTaskRecurrence();
	switch (checkRec) {
	case Task::DAY: {
		oss << "EVERY DAY" << endl;
		break;
	}
	case Task::WEEK: {
		oss << "EVERY WEEK" << endl;
		break;
	}
	case Task::MONTH: {
		oss << "EVERY MONTH" << endl;
		break;
	}
	default:
		break;
	}

	//Prints Task Priority
	Task::Priority checkPri = (toPrint).getTaskPriority();
	switch (checkPri) {
	case Task::LOW: {
		oss << "PRIORITY: LOW" << endl;
		break;
	}
	case Task::HIGH: {
		oss << "PRIORITY: HIGH" << endl;
		break;
	}
	default: {
		oss << "PRIORITY: NORMAL" << endl;
		break;
	}
	}

	bool checkMarked = (toPrint).getTaskMarked();
	switch (checkMarked) {
	case true: {
		oss << "MARKED: " << "YES" << endl;
		break;
	}
	case false: {
		oss << "MARKED: " << "NO" << endl;
		break;
	}
	default:
		break;
	}

	return oss.str();

}