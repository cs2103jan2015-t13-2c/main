//@author A0122357L
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

	static string parseDateToDisplay(Task currentTasks);
};

