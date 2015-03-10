#include "FloatingTask.h"

FloatingTask::FloatingTask(std::string taskDetails)
	:FloatingTask::Task(taskDetails)
{
}

FloatingTask::FloatingTask(std::string taskDetails, Task::Priority taskPriority)
	:FloatingTask::Task(taskDetails,taskPriority)
{
}

FloatingTask::~FloatingTask(void)
{
}