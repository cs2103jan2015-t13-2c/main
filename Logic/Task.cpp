#include "Task.h"


Task::Task(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Priority taskPriority){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskPriority = taskPriority;
	_taskMarked = false;

	if (_taskStartTime == NULL && _taskEndTime == NULL && _taskDeadline == NULL) {
		_taskType = FLOATING;
	}

	else if (_taskDeadline == NULL) {
		_taskType = TIMED;
	}

	else {
		_taskType = DEADLINE;
	}
}

Task Task::clone(){
	Task task = Task(_taskDetails, _taskStartTime, 
		_taskEndTime, _taskDeadline, _taskPriority);
	task.setTaskMarked(getTaskMarked());
	return task;
}

//Destructor
Task::~Task(){
}

//Modifiers
void Task::setTaskDetails(string taskDetails){
	_taskDetails = taskDetails;
}

void Task::setTaskStartTime(Date* taskStartTime){
	_taskStartTime = taskStartTime;
}

void Task::setTaskEndTime(Date* taskEndTime){
	_taskEndTime = taskEndTime;
}

void Task::setTaskDeadline(Date* taskDeadline){
	_taskDeadline = taskDeadline;
}

void Task::setTaskPriority(Priority taskPriority){
	_taskPriority = taskPriority;
}

void Task::setTaskMarked(bool taskMarked){
	_taskMarked = taskMarked;
}

//Accessors
Task::Type Task::getTaskType(){
	return _taskType;
}

string Task::getTaskDetails(){
	return _taskDetails;
}

Date* Task::getTaskStartTime(){
	return _taskStartTime;
}

Date* Task::getTaskEndTime(){
	return _taskEndTime;
}

Date* Task::getTaskDeadline(){
	return _taskDeadline;
}

Task::Priority Task::getTaskPriority(){
	return _taskPriority;
}

bool Task::getTaskMarked(){
	return _taskMarked;
}