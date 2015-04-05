#include "TaskManager.h"


// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;
vector<Task>* TaskManager::_allCurrentTasks = new vector<Task>;

vector<Task>* TaskManager::_allTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allFloatingTasks= new vector<Task>;
vector<Task>* TaskManager::_allMarkedTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allMarkedFloatingTasks = new vector<Task>;


TaskManager::TaskManager()
{
}

TaskManager* TaskManager::getInstance(){
	if (!_instance)
		_instance = new TaskManager;
	return _instance;
}

int TaskManager::getNumberOfTasks(){
	if (_allCurrentTasks->size() == 0){
		return 0;
	}
	else{
		return _allCurrentTasks->size();
	}
}

vector<Task>* TaskManager::getAllCurrentTasks(){
	return _allCurrentTasks;
}

vector<Task>* TaskManager::getAllTimedTasks(){
	return _allTimedTasks;
}

vector<Task>* TaskManager::getAllFloatingTasks(){
	return _allFloatingTasks;
}

vector<Task>* TaskManager::getAllMarkedTimedTasks(){
	return _allMarkedTimedTasks;
}

vector<Task>* TaskManager::getAllMarkedFloatingTasks(){
	return _allMarkedFloatingTasks;
}

void TaskManager::setAllCurrentTasks(){
	
	//reset all current tasks
	_allCurrentTasks->clear();
	
	//iterate through _allTimedTasks first
	for (unsigned int i = 0; i < _allTimedTasks->size(); i++){
		_allCurrentTasks->push_back(_allTimedTasks->at(i));
	}

	//iterate through _allFloatingTasks next
	for (unsigned int i = 0; i < _allFloatingTasks->size(); i++){
		_allCurrentTasks->push_back(_allFloatingTasks->at(i));
	}

	//iterate through _allMarkedTimedTasks next
	for (unsigned int i = 0; i < _allMarkedTimedTasks->size(); i++){
		_allCurrentTasks->push_back(_allMarkedTimedTasks->at(i));
	}

	//iterate through _allMarkedFloatingTasks next
	for (unsigned int i = 0; i < _allMarkedFloatingTasks->size(); i++){
		_allCurrentTasks->push_back(_allMarkedFloatingTasks->at(i));
	}
}


void TaskManager::loadAllCurrentTasks(vector<Task> allCurrentTasks){
	vector<Task>::iterator iterTasks;
	for (iterTasks = allCurrentTasks.begin(); 
		iterTasks != allCurrentTasks.end(); ++iterTasks){
		addTask(*iterTasks);
	}
}

int TaskManager::addTask(Task task){

	int indexAddedTo=0;

	//adding to vector _allTimedTasks
	if ((task.getTaskType() == Task::DEADLINE || task.getTaskType() == Task::TIMED)
		&& !task.getTaskMarked()){
		indexAddedTo += addTimedTask(task, _allTimedTasks);
	}

	//adding to vector _allFloatingTasks
	else if ((task.getTaskType() == Task::FLOATING) && !task.getTaskMarked()){
		indexAddedTo += addFloatingTask(task, _allFloatingTasks);
		//account for the fact that all floating tasks will be below in the vector
		indexAddedTo += _allTimedTasks->size();
	}

	//adding to vector _allMarkedTimedTasks
	else if (task.getTaskType() == Task::DEADLINE || task.getTaskType() == Task::TIMED){
		indexAddedTo += addTimedTask(task, _allMarkedTimedTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size();
	}

	//adding to vector _allMarkedFloatingTasks
	else if (task.getTaskType() == Task::FLOATING){
		indexAddedTo += addFloatingTask(task, _allMarkedFloatingTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size()+ 
			_allMarkedTimedTasks->size();

	}

	else{
		assert("Task is not timed, deadline nor floating!");
	}

	//sets _allCurrentTasks to an addition of the 4 vectors
	setAllCurrentTasks();

	//saves _allCurrentTasks
	saveTasks();

	return indexAddedTo;
}

int TaskManager::addFloatingTask(Task task, vector<Task>* floatingTasks){

	vector<Task>::iterator iterFloating;
	vector <Task> tempFloating;
	int addedIndex=0;

	if (floatingTasks->empty()) {
		tempFloating.push_back(task);
	}
	else {
		for (iterFloating = floatingTasks->begin();
			iterFloating != floatingTasks->end(); ++iterFloating) {
			if (task.getTaskDetails().compare(iterFloating->getTaskDetails()) <= 0) {
				tempFloating.push_back(task);
				break;
			}
			else{
				tempFloating.push_back(*iterFloating);
			}
			addedIndex++;
		}

		if (iterFloating == floatingTasks->end()){
			tempFloating.push_back(task);
		}
		else{
			while (iterFloating != floatingTasks->end()){
				tempFloating.push_back(*iterFloating);
				++iterFloating;
			}
		}
	}

	//adding to floatingTasks
	floatingTasks->clear();
	for (unsigned int i = 0; i < tempFloating.size(); i++){
		floatingTasks->push_back(tempFloating[i]);
	}

	return addedIndex;
}

int TaskManager::addTimedTask(Task task, vector<Task>* timedTasks){

	vector<Task>::iterator iterTimed;
	vector <Task> tempTimed;
	int addedIndex = 0;

	if (task.getTaskType() == Task::TIMED) {
		if (timedTasks->empty()) {
			tempTimed.push_back(task);
		}
		else {
			for (iterTimed = timedTasks->begin(); iterTimed != timedTasks->end(); ++iterTimed) {
				if (iterTimed->getTaskType() == Task::DEADLINE) {
					if (task.getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) > 0) {
						tempTimed.push_back(task);
						break;
					}
					else if (task.getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskDeadline())) == 0) {
						if (task.getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
							tempTimed.push_back(task);
							break;
						}
					}
				}
				else if (iterTimed->getTaskType() == Task::TIMED) {
					if (task.getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) > 0) {
						tempTimed.push_back(task);
						break;
					}
					else if (task.getTaskStartTime()->isEarlierThan(*(iterTimed->getTaskStartTime())) == 0) {
						if (task.getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
							tempTimed.push_back(task);
							break;
						}
					}
				}
				tempTimed.push_back(*iterTimed);
				++addedIndex;
			}

			if (iterTimed == timedTasks->end()){
				tempTimed.push_back(task);
			}
			else{
				while (iterTimed != timedTasks->end()){
					tempTimed.push_back(*iterTimed);
					++iterTimed;
				}
			}
		}
	} else if (task.getTaskType() == Task::DEADLINE) {
		if (timedTasks->empty()) {
			tempTimed.push_back(task);
		}
		else {
			for (iterTimed = timedTasks->begin(); iterTimed != timedTasks->end(); ++iterTimed) {
				if (iterTimed->getTaskType() == Task::DEADLINE) {
					if (task.getTaskDeadline()->isEarlierThan(*(iterTimed->getTaskDeadline())) > 0) {
						tempTimed.push_back(task);
						break;
					}
					else if (task.getTaskDeadline()->isEarlierThan(*(iterTimed->getTaskDeadline())) == 0) {
						if (task.getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
							tempTimed.push_back(task);
							break;
						}
					}
				}
				else if (iterTimed->getTaskType() == Task::TIMED) {
					if (task.getTaskDeadline()->isEarlierThan(*(iterTimed->getTaskStartTime())) > 0) {
						tempTimed.push_back(task);
						break;
					}
					else if (task.getTaskDeadline()->isEarlierThan(*(iterTimed->getTaskStartTime())) == 0) {
						if (task.getTaskDetails().compare(iterTimed->getTaskDetails()) <= 0) {
							tempTimed.push_back(task);
							break;
						}
					}
				}
				tempTimed.push_back(*iterTimed);
				++addedIndex;
			}

			if (iterTimed == timedTasks->end()){
				tempTimed.push_back(task);
			}
			else{
				while (iterTimed != timedTasks->end()){
					tempTimed.push_back(*iterTimed);
					++iterTimed;
				}
			}
		}
	}

	timedTasks->clear();
	for (unsigned int i = 0; i < tempTimed.size(); i++){
		timedTasks->push_back(tempTimed[i]);
	}

	return addedIndex;
}


Task TaskManager::getTask(int taskNumber){
	if (taskNumber>_allCurrentTasks->size()){
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}
	return _allCurrentTasks->at(taskNumber - 1);
}

void TaskManager::removeTask(int taskNumber){

	int timedTaskSize = _allTimedTasks->size();
	int floatingTaskSize = _allFloatingTasks->size();
	int markedTimedTaskSize = _allMarkedTimedTasks->size();
	int markedFloatingTaskSize = _allMarkedFloatingTasks->size();
	
	if (taskNumber <= timedTaskSize){
		_allTimedTasks->erase(_allTimedTasks->begin() + taskNumber - 1);
	}
	else if (taskNumber <= timedTaskSize + floatingTaskSize){
		int index = taskNumber - 1 - timedTaskSize;
		_allFloatingTasks->erase(_allFloatingTasks->begin() + index);
	}
	else if (taskNumber <= timedTaskSize + floatingTaskSize + markedTimedTaskSize){
		int index = taskNumber - 1 - timedTaskSize - floatingTaskSize;
		_allMarkedTimedTasks->erase(_allMarkedTimedTasks->begin() + index);
	}
	else if (taskNumber <= timedTaskSize + floatingTaskSize + markedTimedTaskSize + 
		markedFloatingTaskSize){
		int index = taskNumber - 1 - timedTaskSize - floatingTaskSize - markedTimedTaskSize;
		_allMarkedFloatingTasks->erase(_allMarkedFloatingTasks->begin() + index);
	}
	else{
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}

	setAllCurrentTasks();
	
	saveTasks();
}

void TaskManager::markTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(true);
	removeTask(taskNumber);
	addTask(task);
	setAllCurrentTasks();
	saveTasks();
}

void TaskManager::unmarkTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(false);
	removeTask(taskNumber);
	addTask(task);
	setAllCurrentTasks();
	saveTasks();
}

void TaskManager::saveTasks(){
	Storage* storage = Storage::getInstance();
	storage->writeToFile();
}


const string TaskManager::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";