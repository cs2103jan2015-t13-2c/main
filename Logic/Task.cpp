#include <string>
#include "Task.h"

Task::Task(std::string taskDetails){
	_taskDetails = taskDetails;
	_taskPriority = Priority::NORMAL;
}
	
Task::Task(std::string taskDetails, Task::Priority taskPriority){
	_taskDetails = taskDetails;
	_taskPriority = taskPriority;
}

//Destructor
Task::~Task(){}

//Modifiers
void Task::setTaskDetails(std::string taskDetails){
	_taskDetails=taskDetails;
}
	
void Task::setTaskPriority(Task::Priority taskPriority){
	_taskPriority=taskPriority;
}

//Accessors
std::string Task::getTaskDetails(){
	return _taskDetails;
}
Task::Priority Task::getTaskPriority(){
	return _taskPriority;
}