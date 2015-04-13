//@author A0122357L
#pragma once

#include "Command.h"
#include "Controller.h"

class CommandRedo : public Command
{
public:
	CommandRedo();
	~CommandRedo();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandRedo::MESSAGE_NOTHING_TO_REDO;
	static const string CommandRedo::MESSAGE_ACTION_REDONE;
};