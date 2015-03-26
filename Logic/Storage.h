#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include "Task.h"
#include "TaskManager.h"
#include "document.h"
#include "filereadstream.h"
#include "filewritestream.h"
#include "writer.h"

using namespace std;

class Storage
{
public:

	static Storage* getInstance();
	//void Storage::loadfromFile(vector<Task> &tempSave, string fileName);
	//void Storage::writetoFile(vector<Task> tempSave, string fileName);
	void writeToFile();
	static vector<Task> readFromFile();

	static string _filename;

private:
	Storage();



	//copy constructor is private
	Storage& operator=(Storage const&){};

	static Storage *_instance;
};

