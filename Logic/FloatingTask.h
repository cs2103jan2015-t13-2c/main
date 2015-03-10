#pragma once
#include "Task.h"
#include <string>

class FloatingTask: public Task
{
public:
	
	//Constructors
	FloatingTask::FloatingTask(std::string taskDetails);
	FloatingTask::FloatingTask(std::string taskDetails, Task::Priority taskPriority);

	//Destructors
	FloatingTask::~FloatingTask(void);
};

