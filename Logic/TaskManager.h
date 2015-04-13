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
<<<<<<< HEAD

	enum TaskType {
		Timed, Floating, MarkedTimed, MarkedFloating
	};

=======
>>>>>>> origin/master
	static vector<Task>* getAllCurrentTasks();
	static vector<Task>* getAllTimedTasks();
	static vector<Task>* getAllFloatingTasks();
	static vector<Task>* getAllMarkedTimedTasks();
	static vector<Task>* getAllMarkedFloatingTasks();

	static int getNumberOfTasks();
	static TaskManager* getInstance();

<<<<<<< HEAD
	static void addTask(Task task);
=======
	//return int value of the index the task was added to
	static int addTask(Task task);
>>>>>>> origin/master
	static int addFloatingTask(Task task, vector<Task>* floatingTasks);
	static int addTimedTask(Task task, vector<Task>* timedTasks);

	static Task getTask(int taskNumber);
	static void removeTask(int taskNumber);
	static void TaskManager::saveTasks();
	static void TaskManager::markTask(int taskNumber);
	static void TaskManager::unmarkTask(int taskNumber);
<<<<<<< HEAD
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
=======
	static void TaskManager::sortTasks();
	static void setAllCurrentTasks();
	static void loadAllCurrentTasks(vector<Task> allCurrentTasks);
>>>>>>> origin/master

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


