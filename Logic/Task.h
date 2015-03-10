#pragma once
#pragma once

#include <string>

class Task{

public:

	enum Priority {
		LOW, NORMAL, HIGH
	};

	//Constructors
	Task::Task(std::string taskDetails);
	Task::Task(std::string taskDetails, Task::Priority taskPriority);

	//Destructor
	Task::~Task();

	//Modifiers
	void Task::setTaskDetails(std::string taskDetails);
	void Task::setTaskPriority(Priority taskPriority);

	//Accessors
	std::string Task::getTaskDetails();
	Task::Priority Task::getTaskPriority();

protected:
	std::string _taskDetails;
	Task::Priority _taskPriority;
};