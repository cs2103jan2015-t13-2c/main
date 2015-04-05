#include "CommandSort.h"


CommandSort::CommandSort()
{
}


CommandSort::~CommandSort()
{
}

string CommandSort::execute(){

	vector <Task> temp = *(TaskManager::getAllCurrentTasks());
	vector <Task> tempTimed;
	vector <Task> tempFloating;
	vector <Task> toReturn;


	vector<Task>::iterator iterTemp;
	vector<Task>::iterator iterFloating;
	vector<Task>::iterator iterTimed;

	for (iterTemp = temp.begin(); iterTemp != temp.end(); ++iterTemp) {
		if (iterTemp->getTaskType() == Task::FLOATING) {
			if (tempFloating.empty()) {
				tempFloating.push_back(*iterTemp);
			}
			else {
				for (iterFloating = tempFloating.begin(); iterFloating != tempFloating.end(); ++iterFloating) {
					if (iterTemp->getTaskDetails().compare(iterFloating->getTaskDetails()) <= 0) {
						tempFloating.insert(iterFloating, *iterTemp);
					}
				}
			}
		}
		else if (iterTemp->getTaskType() == Task::TIMED) {
			if (tempTimed.empty()) {
				tempTimed.push_back(*iterTemp);
			}
			else {
				for (iterTimed = tempTimed.begin(); iterTimed != tempTimed.end(); ++iterTimed) {
					if (iterTimed->getTaskType() == Task::DEADLINE) {
						if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) < 0) {
							tempTimed.insert(iterTimed, *iterTemp);
						}
						else if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) == 0) {
							if (iterTemp->getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
								tempTimed.insert(iterTimed, *iterTemp);
							}
						}
					}
					else if (iterTimed->getTaskType() == Task::TIMED) {
						if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) < 0) {
							tempTimed.insert(iterTimed, *iterTemp);
						}
						else if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) == 0) {
							if (iterTemp->getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
								tempTimed.insert(iterTimed, *iterTemp);
							}
						}
					}
				}
			}
		}
		else if (iterTimed->getTaskType() == Task::DEADLINE) {
			if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) < 0) {
				tempTimed.insert(iterTimed, *iterTemp);
			}
			else if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) == 0) {
				if (iterTemp->getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
					tempTimed.insert(iterTimed, *iterTemp);
				}
			}
		}
		else if (iterTimed->getTaskType() == Task::TIMED) {
			if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) < 0) {
				tempTimed.insert(iterTimed, *iterTemp);
			}
			else if (iterTemp->getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) == 0) {
				if (iterTemp->getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
					tempTimed.insert(iterTimed, *iterTemp);
				}
			}
		}
	}

	//iterate through, get index of where each task has been sorted as compared to the original
	//push all these indexes into my undoIndex vector

	return "Task has been sorted\n";
}

Command* CommandSort::getInverseCommand(){
	//pop all the indexes from my undoIndex vector
	//1 by 1, insert all these tasks back into those indexes
	return new CommandSort();
}