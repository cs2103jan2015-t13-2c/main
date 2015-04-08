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
		Task::Priority taskPriority,
		string duration,
		bool marked,
		bool foundMarked,
		bool foundPriority);
	~CommandSearch();

	virtual string execute();
	virtual Command* getInverseCommand();

	static const int INVALID_NUMBER_FORMAT = -1;
	static const int DAYS_TO_MINUTES = 1440;
	static const int HOURS_TO_MINUTES = 60;
	static const string CommandSearch::ERROR_TOOMANY_SEARCH_ARGUMENTS;
	static const string CommandSearch::INVALID_DURATION;
	static const string CommandSearch::MESSAGE_NEXT_AVAILABLE_SLOT;
	static char CommandSearch::buffer[255];

	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static unsigned int countWordsInString(const string& str);
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);

private:
	string _taskDetails;
	Date *_taskStartTime;
	Date *_taskEndTime;
	Date *_taskDeadline;
	Task::Priority _taskPriority;
	string _duration;
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
	string searchNextEmptySlot(string duration);

	string printTask(Task toPrint, int taskNumber);
	int parseDurationToMinutes(string duration);
};