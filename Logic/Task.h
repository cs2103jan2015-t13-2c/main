#pragma once

#include <string>
#include <chrono>
#include "Date.h"

using namespace std;

class Task{

public:
	enum Type {
		TIMED, DEADLINE, FLOATING
	};

	enum Priority {
		LOW, NORMAL, HIGH
	};

	//Constructor
	Task::Task(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Priority taskPriority);

	//Destructor
	Task::~Task();

	//Modifiers
	void Task::setTaskDetails(string taskDetails);
	void Task::setTaskStartTime(Date* taskStartTime);
	void Task::setTaskEndTime(Date* taskEndTime);
	void Task::setTaskDeadline(Date* taskDeadline);
	void Task::setTaskPriority(Priority taskPriority);
	void Task::setTaskMarked(bool taskMarked);

	//Accessors
	Task::Type Task::getTaskType();
	string Task::getTaskDetails();
	Date* Task::getTaskStartTime();
	Date* Task::getTaskEndTime();
	Date* Task::getTaskDeadline();
	Task::Priority Task::getTaskPriority();
	bool Task::getTaskMarked();

private:
	Task::Type _taskType;
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Priority _taskPriority;
	bool _taskMarked;
};