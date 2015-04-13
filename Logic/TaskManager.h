//@author A0122357L
#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "Task.h"
#include "Storage.h"
#include "CommandException.h"

using namespace std;
class TaskManager
{
public:

	enum TaskType {
		Timed, Floating, MarkedTimed, MarkedFloating
	};

	static vector<Task>* getAllCurrentTasks();
	static vector<Task>* getAllTimedTasks();
	static vector<Task>* getAllFloatingTasks();
	static vector<Task>* getAllMarkedTimedTasks();
	static vector<Task>* getAllMarkedFloatingTasks();

	static int getNumberOfTasks();
	static TaskManager* getInstance();

	static void addTask(Task task);
	static int addFloatingTask(Task task, vector<Task>* floatingTasks);
	static int addTimedTask(Task task, vector<Task>* timedTasks);

	static Task getTask(int taskNumber);
	static void removeTask(int taskNumber);
	static void TaskManager::saveTasks();
	static void TaskManager::markTask(int taskNumber);
	static void TaskManager::unmarkTask(int taskNumber);
	static void setAllCurrentTasks();
	static void loadAllCurrentTasks(vector<Task> allCurrentTasks);
	static void clearAllCurrentTasks();

	static TaskType determineTaskType(Task task);

	static int TaskManager::getIndex(Task task);
	static vector<Task>* TaskManager::getVector(Task task);

	static int getIndexToInsert(Task task);
	static int getFloatingIndexToInsert(Task task, vector<Task>* floatingTasks);
	static int getTimedIndexToInsert(Task task, vector<Task>* timedTasks);
	static bool isAlphabeticallyArranged(Task firstTask, Task secondTask);
	static bool isChronologicallyArranged(Task firstTask, Task secondTask);
	static bool isChronologicallySame(Task firstTask, Task secondTask);

	static const string TaskManager::ERROR_MESSAGE_COMMAND_TASKNUM;

private:
	TaskManager();

	static vector<Task>* _allCurrentTasks;
	static vector<Task>* TaskManager::_allFloatingTasks;
	static vector<Task>* TaskManager::_allTimedTasks;
	static vector<Task>* TaskManager::_allMarkedFloatingTasks;
	static vector<Task>* TaskManager::_allMarkedTimedTasks;

	//copy constructor is private
	TaskManager& operator=(TaskManager const&){};

	static TaskManager *_instance;
};


