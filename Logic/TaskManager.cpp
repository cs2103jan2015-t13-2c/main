#include "TaskManager.h"


//This class is used to manage the program's internal representation of all current Tasks
//It is a singleton class, so that there will only be 1 instance of the tasks


/*
This class is to manipulate the internal task management for TASKKY.

Functionalities include loading the tasks saved in storage in chronological, and alphabetical order



@author: A0122357L Lee Kai Yi
*/

// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;

//vector representing all the tasks in order
vector<Task>* TaskManager::_allCurrentTasks = new vector<Task>;

//vectors representing the different categories of tasks
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


void TaskManager::addTask(Task task){

	int indexToInsert = getIndexToInsert(task);

	int timedTaskSize = _allTimedTasks->size();
	int floatingTaskSize = _allFloatingTasks->size();
	int markedTimedTaskSize = _allMarkedTimedTasks->size();
	int markedFloatingTaskSize = _allMarkedFloatingTasks->size();

	if (indexToInsert <= timedTaskSize){
		_allTimedTasks->insert(_allTimedTasks->begin() + indexToInsert, task);
	}
	else if (indexToInsert <= timedTaskSize + floatingTaskSize){
		int index = indexToInsert - timedTaskSize;
		_allFloatingTasks->insert(_allFloatingTasks->begin() + index, task);
	}
	else if (indexToInsert <= timedTaskSize + floatingTaskSize + markedTimedTaskSize){
		int index = indexToInsert - timedTaskSize - floatingTaskSize;
		_allMarkedTimedTasks->insert(_allMarkedTimedTasks->begin() + index, task);
	}
	else if (indexToInsert <= timedTaskSize + floatingTaskSize + markedTimedTaskSize +
		markedFloatingTaskSize){
		int index = indexToInsert - timedTaskSize - floatingTaskSize - markedTimedTaskSize;
		_allMarkedFloatingTasks->insert(_allMarkedFloatingTasks->begin() + index, task);
	}
	else{
		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);
	}

	setAllCurrentTasks();
}


//Finding the vector index to add this new Task
//
//@param the Task that you want to insert
//@return the index in _allCurrentTasks that you should insert the task in
int TaskManager::getIndexToInsert(Task task){

	int indexAddedTo = 0;

	//task should be added to the _allTimedTasks vector
	if ((task.getTaskType() == Task::DEADLINE || task.getTaskType() == Task::TIMED)
		&& !task.getTaskMarked()){
		
		indexAddedTo += getTimedIndexToInsert(task, _allTimedTasks);

	}

	//task should be added to the _allFloatingTasks vector
	else if ((task.getTaskType() == Task::FLOATING) && !task.getTaskMarked()){
		
		indexAddedTo += getFloatingIndexToInsert(task, _allFloatingTasks);
		//account for the fact that all floating tasks will be below in the vector
		indexAddedTo += _allTimedTasks->size();

	}

	//task should be added to the _allMarkedTimedTasks vector
	else if (task.getTaskType() == Task::DEADLINE || task.getTaskType() == Task::TIMED){
		
		indexAddedTo += getTimedIndexToInsert(task, _allMarkedTimedTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size();

	}

	//task should be added to the _allMarkedFloatingTasks vector
	else if (task.getTaskType() == Task::FLOATING){
		
		indexAddedTo += getFloatingIndexToInsert(task, _allMarkedFloatingTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size() +
			_allMarkedTimedTasks->size();

	}

	return indexAddedTo;
}


//Finding the vector index in the floating tasks vector to add this task
//The floating task vector is a subset of all current tasks
//
//@param the Task that you want to insert, the floating task vector you want to insert to
//@return the index in the floating task vector that you should add the task in
int TaskManager::getFloatingIndexToInsert(Task task, vector<Task>* floatingTasks){

	vector<Task>::iterator iterFloating;
	int addedIndex = 0;

	if (!floatingTasks->empty()) {

		for (iterFloating = floatingTasks->begin();
			iterFloating != floatingTasks->end(); ++iterFloating) {
			
			if (!isAlphabeticallyArranged(task, *iterFloating)) {
				break;
			}

			addedIndex++;
		}
	}

	return addedIndex;
}


//Finding the vector index in the timed tasks vector to add this task
//The timed task vector is a subset of all current tasks
//
//@param the Task that you want to insert
//@return the index in the timed task vector that you should insert the task in
int TaskManager::getTimedIndexToInsert(Task task, vector<Task>* timedTasks){

	vector<Task>::iterator iterTimed;
	int addedIndex = 0;

	if (!timedTasks->empty()) {

		for (iterTimed = timedTasks->begin();
			iterTimed != timedTasks->end(); ++iterTimed) {

			if (!isChronologicallyArranged(task, *iterTimed)){

				if (!isAlphabeticallyArranged(task, *iterTimed)){
					break;
				}
			}

			addedIndex++;
		}
	}

	return addedIndex;
}


//Finding out if first task and second task are arranged in alphabetical order
//
//@param the 2 tasks, firstTask and secondTask, that you want to compare in alphabetical order
//@return if the firstTask comes earlier alphabetically than the secondTask
bool TaskManager::isAlphabeticallyArranged(Task firstTask, Task secondTask){

	return firstTask.getTaskDetails().compare(secondTask.getTaskDetails()) > 0;

}


//Finding out if first task and second task are arranged in chronological order
//
//@param the 2 tasks, firstTask and secondTask, that you want to compare in chronological order
//		 both tasks can be either timed or deadline tasks
//@return if the firstTask comes earlier chronologically than the secondTask
bool TaskManager::isChronologicallyArranged(Task firstTask, Task secondTask){
	
	if (firstTask.getTaskType() == Task::TIMED) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskDeadline())) < 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskStartTime())) < 0) {
				return true;
			}
		}

		else{
			//throw TaskException
		}
	}

	else if (firstTask.getTaskType() == Task::DEADLINE) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskDeadline())) < 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskStartTime())) < 0) {
				return true;
			}
		}
	}
	
	return false;
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
}

void TaskManager::markTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(true);
	removeTask(taskNumber);
	addTask(task);
	setAllCurrentTasks();
}

void TaskManager::unmarkTask(int taskNumber){
	Task task = getTask(taskNumber);
	task.setTaskMarked(false);
	removeTask(taskNumber);
	addTask(task);
	setAllCurrentTasks();
}

void TaskManager::saveTasks(){
	Storage* storage = Storage::getInstance();
	storage->writeToFile();
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


const string TaskManager::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";