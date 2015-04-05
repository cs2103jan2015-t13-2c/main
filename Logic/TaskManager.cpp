#include "TaskManager.h"


// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;
vector<Task>* TaskManager::_allCurrentTasks;

TaskManager::TaskManager()
{
}

TaskManager* TaskManager::getInstance(){
	if (!_instance)
		_instance = new TaskManager;
	return _instance;
}

int TaskManager::getNumberOfTasks(){
	if (_allCurrentTasks == nullptr){
		return 0;
	}
	else{
		return _allCurrentTasks->size();
	}
}

vector<Task>* TaskManager::getAllCurrentTasks(){
	return _allCurrentTasks;
}

void TaskManager::setAllCurrentTasks(vector<Task> allCurrentTasks){
	if (_allCurrentTasks == nullptr){
		_allCurrentTasks = new vector < Task > ;
	}
	for (unsigned int i = 0; i < allCurrentTasks.size(); i++){
		_allCurrentTasks->push_back(allCurrentTasks[i]);
	}
	//*_allCurrentTasks = allCurrentTasks;
}

void TaskManager::addTask(Task task){
	if (_allCurrentTasks == nullptr){
		_allCurrentTasks = new vector < Task > ;
	}
	_allCurrentTasks->push_back(task);
	saveTasks();
}

Task TaskManager::getTask(int taskNumber){
	return _allCurrentTasks->at(taskNumber - 1);
}

void TaskManager::removeTask(int taskNumber){
	_allCurrentTasks->erase(_allCurrentTasks->begin() + taskNumber - 1);
	saveTasks();
}

void TaskManager::markTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(true);
	removeTask(taskNumber);
	insertTask(taskNumber, task);
	saveTasks();
}

void TaskManager::unmarkTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(false);
	removeTask(taskNumber);
	insertTask(taskNumber, task);
	saveTasks();
}

void TaskManager::insertTask(int taskNumber, Task task){
	std::vector<Task>::iterator taskIterator;
	taskIterator = _allCurrentTasks->begin();
	if (_allCurrentTasks->size() == 0){
		_allCurrentTasks->push_back(task);
	}
	else if (taskNumber == _allCurrentTasks->size() +1){
		_allCurrentTasks->push_back(task);
	}else{
		_allCurrentTasks->insert(taskIterator + taskNumber - 1, task);
	}
	saveTasks();
}

void TaskManager::saveTasks(){
	Storage* storage = Storage::getInstance();
	storage->writeToFile();
}

void TaskManager::sortTasksAccordingToDate(){
	
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
}

/*
//structure for sorting
struct TaskSortClass {
	bool operator() (Task taskA, Task taskB) { 
		if (taskA.getTaskType == Task::Type::FLOATING && taskB.getTaskType == Task::Type::FLOATING){
			return true;
		}
		else if (taskA.getTaskType == Task::Type::DEADLINE && taskB.getTaskType == Task::Type::FLOATING){
			return true;
		}
		else if (taskA.getTaskType == Task::Type::FLOATING && taskB.getTaskType == Task::Type::DEADLINE){
			return false;
		}
	}
} taskSortObject;

void TaskManager::sortTasks(){
	std::sort(_allCurrentTasks->begin(), _allCurrentTasks->end(), taskSortObject);
}*/

