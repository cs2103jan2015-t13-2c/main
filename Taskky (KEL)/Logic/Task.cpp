#include "Task.h"

//Constructor
Task::Task(int taskNumber,
	string taskDetails,
	chrono::system_clock::time_point taskStartTime,
	chrono::system_clock::time_point taskEndTime,
	chrono::system_clock::time_point taskDeadline,
	Task::Recurrence taskRecurrence,
	Task::Priority taskPriority){
	_taskNumber = taskNumber;
	_taskDetails = taskDetails;
	_taskStartTime = taskStartTime;
	_taskEndTime = taskEndTime;
	_taskDeadline = taskDeadline;
	_taskRecurrence = taskRecurrence;
	_taskPriority = taskPriority;

	if (_taskStartTime == chrono::system_clock::time_point() &&
		_taskEndTime == chrono::system_clock::time_point() &&
		_taskDeadline == chrono::system_clock::time_point()) {
		_taskType = FLOATING;
	}

	else if (_taskDeadline == chrono::system_clock::time_point()) {
		_taskType = TIMED;
	}

	else {
		_taskType = DEADLINE;
	}
}

//Destructor
Task::~Task()
{
}

//Modifiers
void Task::setTaskNumber(int taskNumber) {
	_taskNumber = taskNumber;
}

void Task::setTaskDetails(std::string taskDetails){
	_taskDetails=taskDetails;
}

void Task::setTaskStartTime(std::chrono::system_clock::time_point taskStartTime){
	_taskStartTime = taskStartTime;
}

void Task::setTaskEndTime(std::chrono::system_clock::time_point taskEndTime){
	_taskEndTime = taskEndTime;
}

void Task::setTaskDeadline(std::chrono::system_clock::time_point taskDeadline){
	_taskDeadline=taskDeadline;
}

void Task::setTaskRecurrence(Task::Recurrence taskRecurrence){
	_taskRecurrence = taskRecurrence;
}

void Task::setTaskPriority(Priority taskPriority){
	_taskPriority = taskPriority;
}

//Accessors
int Task::getTaskNumber(){
	return _taskNumber;
}

Task::Type Task::getTaskType(){
	return _taskType;
}

std::string Task::getTaskDetails(){
	return _taskDetails;
}

std::chrono::system_clock::time_point Task::getTaskStartTime(){
	return _taskStartTime;
}

std::chrono::system_clock::time_point Task::getTaskEndTime(){
	return _taskEndTime;
}

std::chrono::system_clock::time_point Task::getTaskDeadline(){
	return _taskDeadline;
}

Task::Recurrence Task::getTaskRecurrence(){
	return _taskRecurrence;
}

Task::Priority Task::getTaskPriority(){
	return _taskPriority;
}
