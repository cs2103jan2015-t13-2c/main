#include "CommandExit.h"


CommandExit::CommandExit()
{
}


CommandExit::~CommandExit()
{
}

string CommandExit::execute(){
	//clear all temp files, etc
	exit(0);
	return "Exit with success!";
}

Command* CommandExit::getInverseCommand(){
	return nullptr;
}

