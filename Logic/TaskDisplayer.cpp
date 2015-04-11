#include "TaskDisplayer.h"


TaskDisplayer::TaskDisplayer()
{
}


TaskDisplayer::~TaskDisplayer()
{
}

string TaskDisplayer::parseAllTasksToDisplay(){
	
	TaskManager* instance = TaskManager::getInstance();

	vector<Task>* allCurrentTasks = instance->getAllCurrentTasks();
	vector<Task>* allTimedTasks = instance->getAllTimedTasks();
	vector<Task>* allFloatingTasks = instance->getAllFloatingTasks();
	vector<Task>* allMarkedTimedTasks = instance->getAllMarkedTimedTasks();
	vector<Task>* allMarkedFloatingTasks = instance->getAllMarkedFloatingTasks();

	ostringstream allTasksToDisplay;

	vector<Task>::iterator iterTemp;

	//takes care of the case where there is only 0 task
	if (allCurrentTasks->size() == 0){
		return "There are no current tasks, add a task!";
	}

	//iterating through the timed / deadline tasks
	for (iterTemp = allTimedTasks->begin(); iterTemp != allTimedTasks->end(); ++iterTemp) {

		Task currentTask = *iterTemp;

		if (currentTask.getTaskType() == Task::TIMED){

			allTasksToDisplay << parseTimedTaskToDisplay(currentTask);

		}
		else{

			allTasksToDisplay << parseDeadlineTaskToDisplay(currentTask);

		}
	}

	//iterating through floating task
	for (iterTemp = allFloatingTasks->begin(); iterTemp != allFloatingTasks->end(); ++iterTemp) {

		Task currentTask = *iterTemp;

		allTasksToDisplay << parseFloatingTaskToDisplay(currentTask);

	}

	//iterating through marked deadline tasks

	for (iterTemp = allMarkedTimedTasks->begin(); iterTemp != allMarkedTimedTasks->end(); ++iterTemp) {

		Task currentTask = *iterTemp;

		if (currentTask.getTaskType() == Task::TIMED){

			allTasksToDisplay << parseTimedTaskToDisplay(currentTask);

		}
		else{

			allTasksToDisplay << parseDeadlineTaskToDisplay(currentTask);

		}
	}

	//iterating through marked floating task
	for (iterTemp = allMarkedFloatingTasks->begin(); iterTemp != allMarkedFloatingTasks->end(); ++iterTemp) {

		Task currentTask = *iterTemp;

		allTasksToDisplay << parseFloatingTaskToDisplay(currentTask);

	}
	

	return allTasksToDisplay.str();
}

string TaskDisplayer::parseTimedTaskToDisplay(Task timedTask){

	ostringstream taskToDisplay;

	string startDate = parseDateToDisplay(timedTask.getTaskStartTime());
	string endDate = parseDateToDisplay(timedTask.getTaskEndTime());
	string task = timedTask.getTaskDetails();

	taskToDisplay << startDate << " to " << endDate << ": " << task;

	return taskToDisplay.str();

}

string TaskDisplayer::parseDeadlineTaskToDisplay(Task deadlineTask){

	ostringstream taskToDisplay;

	string deadlineDate = parseDateToDisplay(deadlineTask.getTaskDeadline());
	string task = deadlineTask.getTaskDetails();

	taskToDisplay << deadlineDate << " by: " << task;

	return taskToDisplay.str();

}

string TaskDisplayer::parseFloatingTaskToDisplay(Task floatingTask){

	ostringstream taskToDisplay;

	string task = floatingTask.getTaskDetails();

	taskToDisplay << "No deadline! | " <<task;

	return taskToDisplay.str();

}

//assuming passing in a deadline task OR timed task
string TaskDisplayer::parseDateToDisplay(Date* date){

	ostringstream dateToDisplay;

	Date* currentDate = date; 

	dateToDisplay << currentDate->getDay() << "/" << currentDate->getMonth()
		<< "/" << currentDate->getYear() << " " << currentDate->getHour() << ":" << 
		currentDate->getMinute();

	return dateToDisplay.str();
}
