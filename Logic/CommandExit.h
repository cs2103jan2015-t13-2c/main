#pragma once
#include "Command.h"

class CommandExit: public Command
{
public:

	CommandExit();

	virtual string execute();

	virtual Command* getInverseCommand();

};

