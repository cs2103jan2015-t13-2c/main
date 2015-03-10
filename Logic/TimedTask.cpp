#include "TimedTask.h"

//Default Constructor only initializes taskDetails
TimedTask::TimedTask(std::string taskDetails)
	:TimedTask::Task(taskDetails)
{
}

TimedTask::TimedTask(std::string taskDetails, 
					 Task::Priority taskPriority, 
					 TimedTask::Recurrance taskRecurrance, 
					 std::chrono::system_clock::time_point taskStartTime,
					 std::chrono::system_clock::time_point taskEndTime)
					 :TimedTask::Task(taskDetails,taskPriority){
						 _taskRecurrance=taskRecurrance;
						 _taskStartTime=taskStartTime;
						 _taskEndTime=taskEndTime;
}

TimedTask::~TimedTask(void)
{
}

void TimedTask::setTaskStartTime(std::chrono::system_clock::time_point taskStartTime){
	_taskStartTime=taskStartTime;
}

void TimedTask::setTaskEndTime(std::chrono::system_clock::time_point taskEndTime){
	_taskEndTime=taskEndTime;
}

void TimedTask::setTaskRecurrance(TimedTask::Recurrance taskRecurrance){
	_taskRecurrance=taskRecurrance;
}

std::chrono::system_clock::time_point TimedTask::getTaskStartTime(){
	return _taskStartTime;
}

std::chrono::system_clock::time_point TimedTask::getTaskEndTime(){
	return _taskEndTime;
}

TimedTask::Recurrance TimedTask::getTaskRecurrance(){
	return _taskRecurrance;
}