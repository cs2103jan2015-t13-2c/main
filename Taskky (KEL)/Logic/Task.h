#pragma once
#ifndef TASK_H_
#define TASK_H_

#include <string>
#include <chrono>

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
	Task::Task(int taskNumber,
		string taskDetails,
		chrono::system_clock::time_point taskStartTime,
		chrono::system_clock::time_point taskEndTime,
		chrono::system_clock::time_point taskDeadline,
		Task::Recurrence taskRecurrence,
		Task::Priority taskPriority);

	//Destructor
	Task::~Task();

	//Modifiers
	void Task::setTaskNumber(int taskNumber);
	void Task::setTaskDetails(string taskDetails);
	void Task::setTaskStartTime(chrono::system_clock::time_point taskStartTime);
	void Task::setTaskEndTime(chrono::system_clock::time_point taskEndTime);
	void Task::setTaskDeadline(chrono::system_clock::time_point taskDeadline);
	void Task::setTaskRecurrence(Task::Recurrence taskRecurrence);
	void Task::setTaskPriority(Priority taskPriority);

	//Accessors
	int Task::getTaskNumber();
	Task::Type Task::getTaskType();
	string Task::getTaskDetails();
	chrono::system_clock::time_point Task::getTaskStartTime();
	chrono::system_clock::time_point Task::getTaskEndTime();
	chrono::system_clock::time_point Task::getTaskDeadline();
	Task::Recurrence Task::getTaskRecurrence();
	Task::Priority Task::getTaskPriority();

private:
	int _taskNumber;
	Task::Type _taskType;
	string _taskDetails;
	chrono::system_clock::time_point _taskStartTime;
	chrono::system_clock::time_point _taskEndTime;
	chrono::system_clock::time_point _taskDeadline;
	Task::Recurrence _taskRecurrence;
	Task::Priority _taskPriority;
};

#endif