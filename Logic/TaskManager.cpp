#include "TaskManager.h"


// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;
vector<Task> TaskManager::_allCurrentTasks;

TaskManager::TaskManager()
{
}

TaskManager* TaskManager::getInstance(){
	if (!_instance)
		_instance = new TaskManager;
	return _instance;
}

int TaskManager::getNumberOfTasks(){
	return _allCurrentTasks.size();
}

vector<Task> TaskManager::getAllCurrentTasks(){
	return _allCurrentTasks;
}

void TaskManager::addTask(Task task){
	_allCurrentTasks.push_back(task);
}

Task TaskManager::getTask(int taskNumber){
	return _allCurrentTasks[taskNumber - 1];
}