#pragma once
#include "Command.h"
#include "Controller.h"

class CommandUndo: public Command
{
public:
	CommandUndo();
	~CommandUndo();
	virtual string execute();
	virtual Command* getInverseCommand();

	static const string CommandUndo::MESSAGE_NOTHING_TO_UNDO;
	static const string CommandUndo::MESSAGE_ACTION_UNDONE;
};

