#pragma once

#include <string>
#include <vector>
#include "Task.h"
#include "Command.h"
#include "TaskManager.h"

using namespace std;

class CommandSort: public Command
{
public:
	CommandSort();
	~CommandSort();

	virtual string execute();
	virtual Command* getInverseCommand();

private:
	vector<int> undoIndexes;
};

