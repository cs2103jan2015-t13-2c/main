#include <string>
#include "Task.h"

//Constructing floating task
Task::Task(std::string taskDetails){
	_taskDetails=taskDetails;
	_taskPriority=Priority::NORMAL;
	_taskDeadline=std::chrono::system_clock::time_point();
	_taskRecurrence=Recurrence::NONE;
	_taskStartTime=std::chrono::system_clock::time_point();
	_taskEndTime=std::chrono::system_clock::time_point();
}

Task::Task(std::string taskDetails, Task::Priority taskPriority){
	_taskDetails=taskDetails;
	_taskPriority=taskPriority;
	_taskDeadline=std::chrono::system_clock::time_point();
	_taskRecurrence=Recurrence::NONE;
	_taskStartTime=std::chrono::system_clock::time_point();
	_taskEndTime=std::chrono::system_clock::time_point();
}

//Constructing Deadline tasks
Task::Task(std::string taskDetails, Task::Priority taskPriority, 
		Task::Recurrence taskRecurrence, std::chrono::system_clock::time_point taskDeadline){
	_taskDetails=taskDetails;
	_taskPriority=taskPriority;
	_taskDeadline=taskDeadline;
	_taskRecurrence=taskRecurrence;
	_taskStartTime=std::chrono::system_clock::time_point();
	_taskEndTime=std::chrono::system_clock::time_point();
}

//Constructing Timed Task
Task::Task(std::string taskDetails, 
					 Task::Priority taskPriority, 
					 Task::Recurrence taskRecurrence, 
					 std::chrono::system_clock::time_point taskStartTime,
					 std::chrono::system_clock::time_point taskEndTime){
	_taskDetails=taskDetails;
	_taskPriority=taskPriority;
	_taskDeadline=std::chrono::system_clock::time_point();
	_taskRecurrence=taskRecurrence;
	_taskStartTime=taskStartTime;
	_taskEndTime=taskEndTime;
}

//Destructor
Task::~Task()
{
}

//Modifiers
void Task::setTaskDetails(std::string taskDetails){
	_taskDetails=taskDetails;
}

void Task::setTaskPriority(Priority taskPriority){
	_taskPriority=taskPriority;
}

void Task::setTaskDeadline(std::chrono::system_clock::time_point taskDeadline){
	_taskDeadline=taskDeadline;
}

void Task::setTaskRecurrence(Task::Recurrence taskRecurrence){
	_taskRecurrence=taskRecurrence;
}

void Task::setTaskStartTime(std::chrono::system_clock::time_point taskStartTime){
	_taskStartTime=taskStartTime;
}

void Task::setTaskEndTime(std::chrono::system_clock::time_point taskEndTime){
	_taskEndTime=taskEndTime;
}

std::string Task::getTaskDetails(){
	return _taskDetails;
}

Task::Priority Task::getTaskPriority(){
	return _taskPriority;
}

std::chrono::system_clock::time_point Task::getTaskDeadline(){
	return _taskDeadline;
}

Task::Recurrence Task::getTaskRecurrence(){
	return _taskRecurrence;
}

std::chrono::system_clock::time_point Task::getTaskStartTime(){
	return _taskStartTime;
}

std::chrono::system_clock::time_point Task::getTaskEndTime(){
	return _taskEndTime;
}

//if no deadline, no start time and end time, no recurrence, it is floating task
bool Task::isFloatingTask(){
	if((_taskDeadline==std::chrono::system_clock::time_point())&&
		(_taskRecurrence==Recurrence::NONE)&&
		(_taskStartTime==std::chrono::system_clock::time_point())&&
		(_taskEndTime==std::chrono::system_clock::time_point())){
			return true;
	}else{
		return false;
	}
}

bool Task::isDeadlineTask(){
	if((_taskDeadline!=std::chrono::system_clock::time_point())&&
		(_taskStartTime==std::chrono::system_clock::time_point())&&
		(_taskEndTime==std::chrono::system_clock::time_point())){
			return true;
	}else{
		return false;
	}
}

bool Task::isTimedTask(){
	if((_taskDeadline==std::chrono::system_clock::time_point())&&
		(_taskStartTime!=std::chrono::system_clock::time_point())&&
		(_taskEndTime!=std::chrono::system_clock::time_point())){
			return true;
	}else{
		return false;
	}
}

bool Task::isValidTask(){
	if(isFloatingTask()||isDeadlineTask()||isTimedTask()){
		return true;
	}else{
		return false;
	}
}