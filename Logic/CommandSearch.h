#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include "StringDistance.h"
#include "CommandException.h"

using namespace std;

class CommandSearch : public Command
{
public:
	CommandSearch(string taskDetails,
		Date *taskStartTime,
		Date *taskEndTime,
		Date *taskDeadline,
		Task::Recurrence taskRecurrence,
		Task::Priority taskPriority,
		bool marked,
		bool foundMarked,
		bool foundPriority);
	~CommandSearch();

	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandSearch::ERROR_TOOMANY_SEARCH_ARGUMENTS;

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Recurrence _taskRecurrence;
	Task::Priority _taskPriority;
	bool _taskMarked;
	bool _foundMarked;
	bool _foundPriority;

	static const int ACCEPTABLE_DISTANCE = 3;

	string searchByName(string taskname);
	string searchDateRange(Date dateFrom, Date dateTo);
	string searchBeforeDate(Date dateBefore);
	string searchAfterDate(Date dateAfter);
	string searchPriority(Task::Priority priority);
	string searchMarked(bool marked);

	string printTask(Task toPrint, int taskNumber);
};