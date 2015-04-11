#pragma once
#include "TaskManager.h"
#include "Task.h"
#include <string>
#include <vector>

using namespace std;

class TaskDisplayer
{
public:
	TaskDisplayer();
	~TaskDisplayer();

	static string parseAllTasksToDisplay();

	static string parseOneTaskToDisplay(Task currentTasks);

	static string TaskDisplayer::parseDateToDisplay(Date* date);

	static string TaskDisplayer::parseTimedTaskToDisplay(Task timedTask);
	static string TaskDisplayer::parseDeadlineTaskToDisplay(Task deadlineTask);
	static string TaskDisplayer::parseFloatingTaskToDisplay(Task floatingTask);

};

