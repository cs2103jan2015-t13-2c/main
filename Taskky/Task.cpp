#include <string>
#include "Task.h"

Task::Task() {
	Task::_taskName = "";
	Task::_details = "";
	//Task::_startTime;
	//Task::_endTime;
	//Task::_reminder;
	Task::_recurrence = Task::RECURRENCE::NONE;
	Task::_priority = Task::PRIORITY::NORMAL;
}

Task::Task(string name) {
	Task::_taskName = name;
	Task::_details = "";
	//Task::_startTime;
	//Task::_endTime;
	//Task::_reminder;
	Task::_recurrence = Task::RECURRENCE::NONE;
	Task::_priority = Task::PRIORITY::NORMAL;
}

//Modifiers
void Task::setTaskName(string name){
	Task::_taskName = name;
}

void Task::setTaskDetails(string details){
	Task::_details = details;
}
void Task::setStartTime(boost::posix_time::ptime startTime){	//I think in the end we should input text, then constructor into ptime object. Also for the other two ptime related functions
	Task::_startTime = startTime;
}
void Task::setEndTime(boost::posix_time::ptime endTime){
	Task::_endTime = endTime;
}
void Task::setReminder(boost::posix_time::ptime reminder){
	Task::_reminder = reminder;
}
void Task::setRecurrence(Task::RECURRENCE recurrence) {
	Task::_recurrence = recurrence;
}
void Task::setPriority(Task::PRIORITY priority){
	Task::_priority = priority;
}

//Accessors
string Task::getTaskName(){
	return Task::_taskName;
}
string Task::getTaskDetails(){
	return Task::_details;
}
boost::posix_time::ptime Task::getStartTime(){
	return Task::_startTime;
}
boost::posix_time::ptime Task::getEndTime(){
	return Task::_endTime;
}
boost::posix_time::ptime Task::getReminder(){
	return Task::_reminder;
}
Task::RECURRENCE Task::getRecurrence(){
	return Task::_recurrence;
}
Task::PRIORITY Task::setPriority(){
	return Task::_priority;
}

//Other Functions
bool Task::isFloatingTask(){
	if (Task::_endTime == boost::posix_time::not_a_date_time) {
		return true;
	}
	else {
		return false;
	}
}

bool Task::isTimedTask(){
	if (Task::_startTime == boost::posix_time::not_a_date_time) {
		return true;
	}
	else {
		return false;
	}
}
bool Task::isRecurringTask(){
	if (Task::_recurrence == Task::RECURRENCE::NONE){
		return false;
	}
	else {
		return true;
	}
}