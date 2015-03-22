#pragma once
#ifndef TASK_H_
#define TASK_H_

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

	enum Recurrence {
		NONE, DAY, WEEK, MONTH
	};

	//Constructor
	Task::Task(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Recurrence taskRecurrence,
		Task::Priority taskPriority);

	//Destructor
	Task::~Task();

	//Modifiers
	void Task::setTaskDetails(string taskDetails);
	void Task::setTaskStartTime(Date taskStartTime);
	void Task::setTaskEndTime(Date taskEndTime);
	void Task::setTaskDeadline(Date taskDeadline);
	void Task::setTaskRecurrence(Task::Recurrence taskRecurrence);
	void Task::setTaskPriority(Priority taskPriority);
	void Task::setTaskMarked(bool taskMarked);

	//Accessors
	Task::Type Task::getTaskType();
	string Task::getTaskDetails();
	Date Task::getTaskStartTime();
	Date Task::getTaskEndTime();
	Date Task::getTaskDeadline();
	Task::Recurrence Task::getTaskRecurrence();
	Task::Priority Task::getTaskPriority();
	bool Task::getTaskMarked();

private:
	Task::Type _taskType;
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Recurrence _taskRecurrence;
	Task::Priority _taskPriority;
	bool _taskMarked;
};

#endif