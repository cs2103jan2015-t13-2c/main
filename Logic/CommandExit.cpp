//@author generated
#include "CommandExit.h"


CommandExit::CommandExit()
{
}


CommandExit::~CommandExit()
{
}

//@author A0122357L
string CommandExit::execute(){
	//clear all temp files, etc
	exit(0);
	return "Exit with success!";
}

Command* CommandExit::getInverseCommand(){
	return nullptr;
}

