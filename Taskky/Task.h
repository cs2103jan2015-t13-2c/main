#pragma once
#pragma once

#include <string>
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\date_time\posix_time\posix_time.hpp"
#include "boost\algorithm\string\split.hpp"
#include "boost\algorithm\string\classification.hpp"


using namespace std;


class Task
{
public:
	//Enumerations
	enum RECURRENCE {
		NONE,	//One-time task
		DAY,	//Daily task
		WEEK,	//Weekly task - will happen on the same DAY of the week (every monday, every tuesday, etc)
		MONTH,	//Monthly task - will happen on the same DATE of the week (every 20th of the month). Will disregard the ones with date more than the date of the month. E.g. Task on 31st of each month
		YEAR	//Yearly task - will happen on the same DATE of the year (date and month)
	};

	enum PRIORITY {	//for user's preference only
		LOW,
		NORMAL,
		HIGH
	};

	//Constructors
	Task();
	Task(std::string name);

	//Destructor
	~Task();

	//Modifiers
	void setTaskName(std::string name);
	void setTaskDetails(std::string details);
	void setStartTime(boost::posix_time::ptime startTime);
	void setEndTime(boost::posix_time::ptime endTime);
	void setReminder(boost::posix_time::ptime reminder);
	void setRecurrence(RECURRENCE recurrence);
	void setPriority(PRIORITY priority);

	//Accessors
	std::string getTaskName();
	std::string getTaskDetails();
	boost::posix_time::ptime getStartTime();
	boost::posix_time::ptime getEndTime();
	boost::posix_time::ptime getReminder();
	RECURRENCE getRecurrence();
	PRIORITY setPriority();

	//Other Functions
	bool isFloatingTask();
	bool isTimedTask();
	bool isRecurringTask();

private:
	std::string _taskName;
	std::string _details;
	boost::posix_time::ptime _startTime;
	boost::posix_time::ptime _endTime;
	boost::posix_time::ptime _reminder;
	RECURRENCE _recurrence;
	PRIORITY _priority;
};