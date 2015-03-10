#pragma once
#include "Task.h"
#include <string>
#include <chrono>

class TimedTask: public Task
{
public:

	enum class Recurrance {
		NONE, DAY, WEEK, MONTH
	};
	
	//Constructors
	
	TimedTask::TimedTask(std::string taskDetails);

	TimedTask::TimedTask(std::string taskDetails, 
					 Task::Priority taskPriority, 
					 TimedTask::Recurrance taskRecurrance, 
					 std::chrono::system_clock::time_point taskStartTime,
					 std::chrono::system_clock::time_point taskEndTime);

	//Destructors
	TimedTask::~TimedTask(void);

	void TimedTask::setTaskStartTime(std::chrono::system_clock::time_point taskStartTime);
	void TimedTask::setTaskEndTime(std::chrono::system_clock::time_point taskEndTime);
	void TimedTask::setTaskRecurrance(TimedTask::Recurrance taskRecurrance);

	//Accessors
	std::chrono::system_clock::time_point TimedTask::getTaskStartTime();
	std::chrono::system_clock::time_point TimedTask::getTaskEndTime();
	TimedTask::Recurrance TimedTask::getTaskRecurrance();


private:
	std::chrono::system_clock::time_point _taskStartTime;
	std::chrono::system_clock::time_point _taskEndTime;
	TimedTask::Recurrance _taskRecurrance;
};

