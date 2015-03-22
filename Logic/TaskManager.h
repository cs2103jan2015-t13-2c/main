#pragma once
#include <string>
#include <vector>
#include "Task.h"

using namespace std;
class TaskManager
{
public:
	//static TaskManager getInstance();
	static vector<Task> getAllCurrentTasks();
	static int getNumberOfTasks();
	static TaskManager* getInstance();
	static void addTask(Task task);
	static Task getTask(int taskNumber);

private:
	TaskManager();

	static vector<Task> _allCurrentTasks;
	static void loadData();
	static void saveData();

	//copy constructor is private
	TaskManager& operator=(TaskManager const&){};

	static TaskManager *_instance;
	};


