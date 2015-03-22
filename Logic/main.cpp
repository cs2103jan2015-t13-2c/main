#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Task.h"
#include "Taskky.h"
#include "Controller.h"

using namespace std;

const string WELCOME_MESSAGE = "Welcome to T.A.S.K.K.Y.";

char buffer[255];

void printWelcomeMessage() {
	sprintf_s(buffer, WELCOME_MESSAGE.c_str());
	cout << buffer << "\n";
}

void showToUser(string text) {
	cout << text << "\n";
}

void main() {
	printWelcomeMessage();

	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	cout << "\nWelcome back, " << userName << "!\n";

	string fileName = userName + "Save.txt";
	//vector<Task> tempSave;
	//loadfromFile(tempSave, fileName);

	cin.ignore();
	while (true) {
		cout << "command: ";
		string userCommand;
		getline(cin, userCommand);
		string feedback = Controller::processUserInput(userCommand);
		showToUser(feedback);
	}
}
