#pragma once
#include <string>
#include <vector>
#include "Task.h"
#include "Storage.h"
#include <algorithm>

using namespace std;
class TaskManager
{
public:
	static vector<Task>* getAllCurrentTasks();
	static int getNumberOfTasks();
	static TaskManager* getInstance();
	static void addTask(Task task);
	static Task getTask(int taskNumber);
	static void removeTask(int taskNumber);
	static void TaskManager::saveTasks();
	static void TaskManager::markTask(int taskNumber);
	static void TaskManager::insertTask(int taskNumber, Task task);
	static void TaskManager::unmarkTask(int taskNumber);
	static void TaskManager::sortTasks();
	static void setAllCurrentTasks(vector<Task> allCurrentTasks);

private:
	TaskManager();

	static vector<Task>* _allCurrentTasks;

	//copy constructor is private
	TaskManager& operator=(TaskManager const&){};

	static TaskManager *_instance;
	};


