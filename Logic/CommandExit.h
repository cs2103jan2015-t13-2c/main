//@author A0122357L
#pragma once
#include "Command.h"

class CommandExit: public Command
{
public:
	CommandExit();
	~CommandExit();
	virtual string execute();
	virtual Command* getInverseCommand();
};

