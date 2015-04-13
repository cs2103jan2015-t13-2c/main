//@author A0122357L
#pragma once
#include <string>

using namespace std;
class Command
{
public:
	Command();
	~Command();
	virtual string execute()=0;
	virtual Command* getInverseCommand()=0;
};

