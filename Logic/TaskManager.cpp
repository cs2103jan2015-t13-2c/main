//@author A0122357L
<<<<<<< HEAD

/*
This class is used to manage Taskky's representation of all current Tasks
It is a singleton class, so that there will only be 1 instance of the tasks

When a task is added, it is auto sorted following this method:
1. Timed tasks come first, in chronological then alphabetical order
2. Floating tasks come next, in alphabetical order
3. Marked timed tasks come next, in chronological then alphabetical order
4. Marked floating tasks come last

This class also has functions to supports mark, unmark, deletion and finding 
the insertion point of tasks into Taskky's internal representation of Tasks
*/

#include "TaskManager.h"


/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//Loading all the current tasks into Taskky from a vector<Task>
//
//@param the vector of tasks you want to load from
void TaskManager::loadAllCurrentTasks(vector<Task> allCurrentTasks){

	vector<Task>::iterator iterTasks;

	clearAllCurrentTasks();

	for (iterTasks = allCurrentTasks.begin();
		iterTasks != allCurrentTasks.end(); ++iterTasks){

		addTask(*iterTasks);

	}
}


//Adds a task into the appropriate vector, based on its type
//
//@param the task you want to add into Taskky
void TaskManager::addTask(Task task){

	int indexToInsert = getIndex(task);

	vector<Task>* vectorToInsert = getVector(task);

	vectorToInsert->insert(vectorToInsert->begin() 
		+ indexToInsert, task);

	setAllCurrentTasks();
}


//Accesses and gets a task based on its task number displayed on screen
//
//@param the task number on screen to get the task from
Task TaskManager::getTask(int taskNumber){

	if (taskNumber>_allCurrentTasks->size()){

		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);

	}

	return _allCurrentTasks->at(taskNumber - 1);
}


//Removes a task based on its task number displayed on screen
//
//@param the task number on screen you want to remove
void TaskManager::removeTask(int taskNumber){

	//Getting the sizes of all the vectors
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

	else if (taskNumber <= timedTaskSize + 
		floatingTaskSize + markedTimedTaskSize){

		int index = taskNumber - 1 - timedTaskSize - floatingTaskSize;

		_allMarkedTimedTasks->erase(_allMarkedTimedTasks->begin() + index);

	}

	else if (taskNumber <= timedTaskSize + floatingTaskSize + markedTimedTaskSize +
		markedFloatingTaskSize){
		
		int index = taskNumber - 1 - timedTaskSize - 
			floatingTaskSize - markedTimedTaskSize;

		_allMarkedFloatingTasks->erase(_allMarkedFloatingTasks->begin() + index);

	}

	else{

		throw CommandException(ERROR_MESSAGE_COMMAND_TASKNUM);

	}

	setAllCurrentTasks();
}


//Marks a task based on its task number displayed on screen
//
//@param the task number on screen you want to mark
void TaskManager::markTask(int taskNumber){

	Task task = getTask(taskNumber);

	task.setTaskMarked(true);

	removeTask(taskNumber);

	addTask(task);

	setAllCurrentTasks();

}


//Unmarks a task based on its task number displayed on screen
//
//@param the task number on screen you want to unmark
void TaskManager::unmarkTask(int taskNumber){

	Task task = getTask(taskNumber);

	task.setTaskMarked(false);

	removeTask(taskNumber);

	addTask(task);

	setAllCurrentTasks();
}


//Writes the task storage to file
void TaskManager::saveTasks(){

	Storage* storage = Storage::getInstance();

	storage->writeToFile();

}


//Gets the number of task internally
int TaskManager::getNumberOfTasks(){

	if (_allCurrentTasks->size() == 0){

		return 0;

	}

	else{

		return _allCurrentTasks->size();

	}
}

void TaskManager::clearAllCurrentTasks(){

	_allTimedTasks = new vector<Task>;
	_allFloatingTasks = new vector<Task>;
	_allMarkedTimedTasks = new vector<Task>;
	_allMarkedFloatingTasks = new vector<Task>;
	setAllCurrentTasks();

}



/*
* ====================================================================
*  Second Level of Abstraction
* ====================================================================
*/

//Updating the allCurrentTasks vector to reflect an addition of the 4 
//other vector<task> that stores my data
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







int TaskManager::getIndex(Task task){

	TaskType taskType = determineTaskType(task);

	//task should be added to the _allTimedTasks vector
	if (taskType == TaskType::Timed){

		return getTimedIndexToInsert(task, _allTimedTasks);

	}

	//task should be added to the _allFloatingTasks vector
	else if (taskType == TaskType::Floating){

		return getFloatingIndexToInsert(task, _allFloatingTasks);

	}

	//task should be added to the _allMarkedTimedTasks vector
	else if (taskType == TaskType::MarkedTimed){

		return getTimedIndexToInsert(task, _allMarkedTimedTasks);

	}

	//task should be added to the _allMarkedFloatingTasks vector
	else{

		return getFloatingIndexToInsert(task, _allMarkedFloatingTasks);

	}

}


//Finding the vector to add this new Task
//
//@param the Task that you want to insert
//@return the vector in _allCurrentTasks that you should insert the task in
vector<Task>* TaskManager::getVector(Task task){

	TaskType taskType = determineTaskType(task);

	//task should be added to the _allTimedTasks vector
	if (taskType == TaskType::Timed){

		return _allTimedTasks;

	}

	//task should be added to the _allFloatingTasks vector
	else if (taskType == TaskType::Floating){

		return _allFloatingTasks;

	}

	//task should be added to the _allMarkedTimedTasks vector
	else if (taskType == TaskType::MarkedTimed){

		return _allMarkedTimedTasks;

	}

	//task should be added to the _allMarkedFloatingTasks vector
	else{

		return _allMarkedFloatingTasks;

	}
}


//Finding the vector index to add this new Task
//
//@param the Task that you want to insert
//@return the index in _allCurrentTasks that you should insert the task in
int TaskManager::getIndexToInsert(Task task){

	int indexAddedTo = 0;

	TaskType taskType = determineTaskType(task);

	//task should be added to the _allTimedTasks vector
	if (taskType==TaskType::Timed){
		
		indexAddedTo += getTimedIndexToInsert(task, _allTimedTasks);

	}

	//task should be added to the _allFloatingTasks vector
	else if (taskType == TaskType::Floating){
		
		indexAddedTo += getFloatingIndexToInsert(task, _allFloatingTasks);
		//account for the fact that all floating tasks will be below in the vector
		indexAddedTo += _allTimedTasks->size();

	}

	//task should be added to the _allMarkedTimedTasks vector
	else if (taskType == TaskType::MarkedTimed){
		
		indexAddedTo += getTimedIndexToInsert(task, _allMarkedTimedTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size();

	}

	//task should be added to the _allMarkedFloatingTasks vector
	else{
		
		indexAddedTo += getFloatingIndexToInsert(task, _allMarkedFloatingTasks);
		indexAddedTo += _allTimedTasks->size() + _allFloatingTasks->size() +
			_allMarkedTimedTasks->size();

	}

	return indexAddedTo;
}


//Determining the task type of the task that you want to insert
//
//@param the Task that you want to insert
//@return the TaskType of the Task you want to insert
TaskManager::TaskType TaskManager::determineTaskType(Task task){
	
	if ((task.getTaskType() == Task::DEADLINE ||
		task.getTaskType() == Task::TIMED) && !task.getTaskMarked()){

		return TaskType::Timed;

	}

	else if ((task.getTaskType() == Task::FLOATING) &&
		!task.getTaskMarked()){

		return TaskType::Floating;

	}

	else if (task.getTaskType() == Task::DEADLINE ||
		task.getTaskType() == Task::TIMED){

		return TaskType::MarkedTimed;

	}

	else{

		return TaskType::MarkedFloating;

	}
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
			
			if (isAlphabeticallyArranged(task, *iterFloating)) {
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

			if (isChronologicallyArranged(task, *iterTimed)){

				if (isChronologicallySame(task, *iterTimed)){

					if (isAlphabeticallyArranged(task, *iterTimed)){
						break;
					}
					else{
						addedIndex++;
						continue;
					}

				}

				break;
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

	return firstTask.getTaskDetails().compare(secondTask.getTaskDetails()) < 0;

}


//Finding out if first task and second task are arranged in chronological order
//
//@param the 2 tasks, firstTask and secondTask, that you want to compare in chronological order
//		 both tasks can be either timed or deadline tasks
//@return if the firstTask comes earlier chronologically than the secondTask
bool TaskManager::isChronologicallyArranged(Task firstTask, Task secondTask){
	
	if (firstTask.getTaskType() == Task::TIMED) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskDeadline())) >= 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskStartTime())) >= 0) {
				return true;
			}
		}

		else{
			//throw TaskException
		}
	}

	else if (firstTask.getTaskType() == Task::DEADLINE) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskDeadline())) >= 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskStartTime())) >= 0) {
				return true;
			}
		}
	}
	
	return false;
}



bool TaskManager::isChronologicallySame(Task firstTask, Task secondTask){

	if (firstTask.getTaskType() == Task::TIMED) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskDeadline())) == 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskStartTime()->isEarlierThan(*(secondTask.getTaskStartTime())) == 0) {
				return true;
			}
		}

		else{
			//throw TaskException
		}
	}

	else if (firstTask.getTaskType() == Task::DEADLINE) {

		if (secondTask.getTaskType() == Task::DEADLINE) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskDeadline())) == 0) {
				return true;
			}
		}

		else if (secondTask.getTaskType() == Task::TIMED) {

			if (firstTask.getTaskDeadline()->isEarlierThan(*(secondTask.getTaskStartTime())) == 0) {
				return true;
			}
		}
	}

	return false;

}









/*
* ====================================================================
*  Constructor, Getters and Setters
* ====================================================================
*/
=======
#include "TaskManager.h"


// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;
vector<Task>* TaskManager::_allCurrentTasks = new vector<Task>;

vector<Task>* TaskManager::_allTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allFloatingTasks= new vector<Task>;
vector<Task>* TaskManager::_allMarkedTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allMarkedFloatingTasks = new vector<Task>;

>>>>>>> origin/master

TaskManager::TaskManager()
{
}

//Ensures the Singleton pattern is adhered to
TaskManager* TaskManager::getInstance(){
	if (!_instance)
		_instance = new TaskManager;
	return _instance;
}

<<<<<<< HEAD
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


/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

// Global static pointer used to ensure a single instance of the class.
TaskManager* TaskManager::_instance = NULL;

//vector representing all the tasks in order
vector<Task>* TaskManager::_allCurrentTasks = new vector<Task>;

//vectors representing the different categories of tasks
vector<Task>* TaskManager::_allTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allFloatingTasks = new vector<Task>;
vector<Task>* TaskManager::_allMarkedTimedTasks = new vector<Task>;
vector<Task>* TaskManager::_allMarkedFloatingTasks = new vector<Task>;
=======
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

>>>>>>> origin/master

const string TaskManager::ERROR_MESSAGE_COMMAND_TASKNUM = "Invalid task number!";