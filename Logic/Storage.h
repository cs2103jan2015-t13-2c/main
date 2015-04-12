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

//using namespace std;

class Storage
{
public:

	static Storage* getInstance();

	void writeToFile();
	static vector<Task> readFromFile();


	//Smaller functions used for the two main function above
	static string _filename;
	static string determineFileName();
	static string findProgramDirectory();
	static bool dirExists(const std::string& dirName_in);
	static void setLocationAsDefault();
	static void checkSaveFile(string filename);
	static vector<Task> parseSaveFileToVector(string filename);
	static void clearSaveFile(string filename);
	static rapidjson::Document parseVectorToJSON(vector<Task> TaskVector);
	static void writeJSONtoFile(string filename, rapidjson::Document document);
	static rapidjson::Value convertTaskToJSON(Task task, rapidjson::Document::AllocatorType& allocator);

private:
	Storage();

	static const string DIRECTORY_ERROR;
	static const string FILENAME_NOT_FOUND;
	static const string FILE_LOCATION_INVALID;

	Storage& operator=(Storage const&){};

	static Storage *_instance;
};

