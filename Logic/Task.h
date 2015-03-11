#pragma once
#pragma once

#include <string>
#include <chrono>

class Task{

public:

	enum Priority {
		LOW, NORMAL, HIGH
	};

	enum class Recurrence {
		NONE, DAY, WEEK, MONTH
	};

	//Constructing Floating tasks
	Task::Task(std::string taskDetails);
	Task::Task(std::string taskDetails, Task::Priority taskPriority);

	//Constructing Deadline tasks
	Task::Task(std::string taskDetails, Task::Priority taskPriority, 
		Task::Recurrence taskRecurrence, std::chrono::system_clock::time_point taskDeadline);

	//Constructing Timed Task
	Task::Task(std::string taskDetails, 
					 Task::Priority taskPriority, 
					 Task::Recurrence taskRecurrence, 
					 std::chrono::system_clock::time_point taskStartTime,
					 std::chrono::system_clock::time_point taskEndTime);

	//Destructor
	Task::~Task();

	//Modifiers
	void Task::setTaskDetails(std::string taskDetails);
	void Task::setTaskPriority(Priority taskPriority);
	void Task::setTaskDeadline(std::chrono::system_clock::time_point taskDeadline);
	void Task::setTaskRecurrence(Task::Recurrence taskRecurrence);
	void Task::setTaskStartTime(std::chrono::system_clock::time_point taskStartTime);
	void Task::setTaskEndTime(std::chrono::system_clock::time_point taskEndTime);

	//Accessors
	std::string Task::getTaskDetails();
	Task::Priority Task::getTaskPriority();
	std::chrono::system_clock::time_point Task::getTaskDeadline();
	Task::Recurrence Task::getTaskRecurrence();
	std::chrono::system_clock::time_point Task::getTaskStartTime();
	std::chrono::system_clock::time_point Task::getTaskEndTime();

	//checking type of task
	bool Task::isFloatingTask();
	bool Task::isDeadlineTask();
	bool Task::isTimedTask();
	bool Task::isValidTask();

private:
	//Default initialize time_point to epoch values
	std::string _taskDetails;
	Task::Priority _taskPriority;
	std::chrono::system_clock::time_point _taskDeadline;
	Task::Recurrence _taskRecurrence;
	std::chrono::system_clock::time_point _taskStartTime;
	std::chrono::system_clock::time_point _taskEndTime;
};