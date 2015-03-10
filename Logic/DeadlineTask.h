#pragma once
#include "Task.h"
#include <string>
#include <chrono>

class DeadlineTask: public Task
{

public:
	
	enum class Recurrance {
		NONE, DAY, WEEK, MONTH
	};

	//Constructors
	DeadlineTask::DeadlineTask(std::string taskDetails);
	DeadlineTask::DeadlineTask(std::string taskDetails, Task::Priority taskPriority, 
		DeadlineTask::Recurrance taskRecurrance, std::chrono::system_clock::time_point taskDeadline);

	//Destructors
	DeadlineTask::~DeadlineTask(void);

	void DeadlineTask::setTaskDeadline(std::chrono::system_clock::time_point taskDeadline);
	void DeadlineTask::setTaskRecurrance(DeadlineTask::Recurrance taskRecurrance);

	//Accessors
	std::chrono::system_clock::time_point DeadlineTask::getTaskDeadline();
	DeadlineTask::Recurrance DeadlineTask::getTaskRecurrance();


private:
	std::chrono::system_clock::time_point _taskDeadline;
	DeadlineTask::Recurrance _taskRecurrance;
};

