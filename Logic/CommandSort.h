#pragma once

#include <string>
#include <vector>
#include "Task.h"
#include "TaskManager.h"

using namespace std;

class CommandSort
{
public:
	CommandSort();
	~CommandSort();

	string execute();
};

