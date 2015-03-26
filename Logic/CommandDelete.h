#pragma once
#include <string>
#include "Command.h"
#include "Date.h"
#include "Task.h"
#include "TaskManager.h"
#include <vector>
#include "CommandAdd.h"

using namespace std;

class CommandDelete: public Command
{
public:
	CommandDelete(int taskNumber);
	~CommandDelete();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandDelete::MESSAGE_DELETED;
	static char CommandDelete::buffer[255];
private:
	int _taskNumber;
};

