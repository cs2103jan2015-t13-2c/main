#include <iostream>
#include "Task.h"
#include "MainLogic.h"

using namespace std;

int main() {

	cout << "Welcome to Taskky!\n";
	string command;
	while (true) {
		getline(cin, command);
		cout << MainLogic::processUserInput(command);
	}
	cin.get();
	return 0;
}