#include <iostream>
#include "Task.h"
#include "MainLogic.h"

using namespace std;

int main() {

	string command;
	getline(cin, command);
	MainLogic::processUserInput(command);
	cin.get();
	return 0;
}