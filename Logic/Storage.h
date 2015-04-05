#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#include <stdio.h>
#include "Task.h"
#include "TaskManager.h"
#include "CommandCheckFileLocation.h"
#include "CommandException.h"
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
	static string determineFileName();
	static string findProgramDirectory();
	static bool dirExists(const std::string& dirName_in);

	static const string DIRECTORY_ERROR;
	static const string FILENAME_NOT_FOUND;
	static const string FILE_LOCATION_INVALID;

private:
	Storage();



	//copy constructor is private
	Storage& operator=(Storage const&){};

	static Storage *_instance;
};

