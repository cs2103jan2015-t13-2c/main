#include "CommandSearch.h"


CommandSearch::CommandSearch(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority,
	bool taskMarked,
	bool foundMarked,
	bool foundPriority) {

	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
	_taskMarked = taskMarked;
	_foundMarked = foundMarked;
	_foundPriority = foundPriority;
}


CommandSearch::~CommandSearch()
{
}

string CommandSearch::execute() {

	TaskManager instance = *TaskManager::getInstance();

	if (_taskDetails != "") {
		if (_taskStartTime != NULL || _taskEndTime != NULL || _taskPriority != NULL){
			throw CommandException(ERROR_TOOMANY_SEARCH_ARGUMENTS);
		}
		return searchByName(_taskDetails);
	}
	else if (_taskStartTime != NULL) {
		if (_taskEndTime != NULL) {
			return searchDateRange(*_taskStartTime, *_taskEndTime);
		}
		else if (_taskEndTime == NULL) {
			return searchAfterDate(*_taskStartTime);
		}
	}
	else if (_taskStartTime == NULL) {
		if (_taskEndTime != NULL) {
			return searchBeforeDate(*_taskEndTime);
		}
	}
	if (_foundPriority == true) {
		return searchPriority(_taskPriority);
	}
	if (_foundMarked == true) {
		return searchMarked(_taskMarked);
	}

	return "Invalid search funtion\n";

}

Command* CommandSearch::getInverseCommand() {
	return nullptr;
}

string CommandSearch::searchByName(string taskname) {

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;
	ostringstream oss;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskDetails().find(taskname.c_str()) != string::npos) {
			if (count == 0) {
				oss << "Similar results:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
		}
		else if (StringDistance::LD(taskname.c_str(), iter->getTaskDetails().c_str()) <= CommandSearch::ACCEPTABLE_DISTANCE) {
			if (count == 0) {
				oss << "Similar results:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			count++;
		}
		++position;
	}

	if (count == 0) {
		oss << "No similar results found!\n";
	}

	return oss.str();

}

string CommandSearch::searchDateRange(Date dateFrom, Date dateTo) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateFrom.isEarlierThan(*(iter->getTaskDeadline())) >= 0) {
				if (dateTo.isEarlierThan(*(iter->getTaskDeadline())) <= 0) {
					if (count == 0) {
						oss << "List of Tasks:\n";
					}
					oss << CommandSearch::printTask(*iter, position);
					++count;
				}
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateFrom.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				if (dateTo.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
					if (count == 0) {
						oss << "List of Tasks:\n";
					}
					oss << CommandSearch::printTask(*iter, position);
					++count;
				}
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Task within date range!\n";
	}

	return oss.str();

}

string CommandSearch::searchAfterDate(Date dateAfter) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateAfter.isEarlierThan(*(iter->getTaskDeadline())) >= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateAfter.isEarlierThan(*(iter->getTaskStartTime())) >= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Tasks after specified date!\n";
	}

	return oss.str();

}

string CommandSearch::searchBeforeDate(Date dateBefore) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (iter->getTaskType() == Task::DEADLINE) {
			if (dateBefore.isEarlierThan(*(iter->getTaskDeadline())) <= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		else if (iter->getTaskType() == Task::TIMED) {
			if (dateBefore.isEarlierThan(*(iter->getTaskStartTime())) <= 0) {
				if (count == 0) {
					oss << "List of Tasks:\n";
				}
				oss << CommandSearch::printTask(*iter, position);
				++count;
			}
		}
		++position;
	}

	if (count == 0) {
		oss << "No Tasks before specified date!\n";
	}

	return oss.str();

}

string CommandSearch::searchPriority(Task::Priority priority) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (priority == iter->getTaskPriority()) {
			if (count == 0) {
				oss << "List of Tasks:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			++count;
		}
		++position;
	}

	if (count == 0) {
		oss << "No Task with specified priority found!\n";
	}

	return oss.str();

}

string CommandSearch::searchMarked(bool marked) {

	ostringstream oss;

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;
	int count = 0;
	int position = 1;

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		if (marked == iter->getTaskMarked()) {
			if (count == 0) {
				oss << "List of Tasks:\n";
			}
			oss << CommandSearch::printTask(*iter, position);
			++count;
		}
		++position;
	}

	if (count == 0) {
		if (marked){
			oss << "No done tasks!\n";
		}
		else{
			oss << "No undone tasks!\n";
		}
		
	}

	return oss.str();

}

string CommandSearch::printTask(Task toPrint, int taskNumber) {
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
	}

	return oss.str();
}

const string CommandSearch::ERROR_TOOMANY_SEARCH_ARGUMENTS = "Enter only 1 search argument!";