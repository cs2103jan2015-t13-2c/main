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
}

void TaskManager::saveTasks(){
	Storage* storage = Storage::getInstance();
	storage->writeToFile();
}