#include "Task.h"


Task::Task(string taskDetails,
	Date *taskStartTime,
	Date *taskEndTime,
	Date *taskDeadline,
	Task::Recurrence taskRecurrence,
	Task::Priority taskPriority){
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskRecurrence = taskRecurrence;
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

void Task::setTaskRecurrence(Task::Recurrence taskRecurrence){
	_taskRecurrence = taskRecurrence;
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

Task::Recurrence Task::getTaskRecurrence(){
	return _taskRecurrence;
}

Task::Priority Task::getTaskPriority(){
	return _taskPriority;
}

bool Task::getTaskMarked(){
	return _taskMarked;
}