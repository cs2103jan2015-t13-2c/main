#include "DeadlineTask.h"


DeadlineTask::DeadlineTask(std::string taskDetails)
	:DeadlineTask::Task(taskDetails)
{
}

DeadlineTask::DeadlineTask(std::string taskDetails, Task::Priority taskPriority, 
		DeadlineTask::Recurrance taskRecurrance, std::chrono::system_clock::time_point taskDeadline)
:DeadlineTask::Task(taskDetails,taskPriority){
	_taskRecurrance=taskRecurrance;
	_taskDeadline=taskDeadline;
}

DeadlineTask::~DeadlineTask(void)
{
}

void DeadlineTask::setTaskDeadline(std::chrono::system_clock::time_point taskDeadline){
	_taskDeadline=taskDeadline;
}

void DeadlineTask::setTaskRecurrance(DeadlineTask::Recurrance taskRecurrance){
	_taskRecurrance=taskRecurrance;
}

std::chrono::system_clock::time_point DeadlineTask::getTaskDeadline(){
	return _taskDeadline;
}

DeadlineTask::Recurrance DeadlineTask::getTaskRecurrance(){
	return _taskRecurrance;
}
