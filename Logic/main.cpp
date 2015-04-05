/*
* ====================================================================
*  Main program
* ====================================================================
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Task.h"
#include "Controller.h"
#include "Storage.h"
#include "TaskManager.h"
#include "SuggestionBuilder.h"

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

	//string userName;
	//cout << "Please enter your username: ";
	//cin >> userName;
	//cout << "\nWelcome back, " << userName << "!\n";
	//userName + 
	//string fileName = "Save.txt";
	//vector<Task> tempSave;
	TaskManager::loadAllCurrentTasks(Storage::readFromFile());

	//cin.ignore();
	while (true) {
		cout << "command: ";
		string userCommand;
		getline(cin, userCommand);
		string feedback = Controller::processUserInput(userCommand);
		showToUser(feedback);
	}
}
