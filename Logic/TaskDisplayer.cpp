//@author A0122357L
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

	ostringstream taskToDisplay;

	vector<Task>::iterator iterTemp;

	//takes care of the case where there is only 0 task
	if (allCurrentTasks->size() == 0){
		return "";
	}

	//should already be arranged in order
	//this takes care of the case where by all current tasks has no deadline or timed task at all!
	Task firstTask = allCurrentTasks->at(0);
	if (!(firstTask.getTaskType() == Task::FLOATING)){
		taskToDisplay << parseDateToDisplay(firstTask) << "\n";
	}

	//takes care of the case where there is only 1 task
	if (allCurrentTasks->size() == 1){
		taskToDisplay << parseOneTaskToDisplay(firstTask);
	}

	//iterating through 2 or more tasks to display
	for (iterTemp = allCurrentTasks->begin(); iterTemp != allCurrentTasks->end(); ++iterTemp) {

		//if ();

	}

	return "hello";
}

string TaskDisplayer::parseOneTaskToDisplay(Task currentTask){
	
	ostringstream taskToDisplay;
	
	taskToDisplay << "get stuff from display!";
	
	return "hello";
}

//assuming passing in a deadline task OR timed task
string TaskDisplayer::parseDateToDisplay(Task currentTask){

	ostringstream dateToDisplay;

	Date* currentDate = currentTask.getTaskDeadline();
	currentDate = currentTask.getTaskStartTime();

	dateToDisplay << "[" << currentDate->getDay() << "/" << currentDate->getMonth()
		<< "/" << currentDate->getYear() << "] " << currentDate->getDayName();

	return dateToDisplay.str();
}
