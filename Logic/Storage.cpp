//@author A0094024M
/*
This class is to manipulate the save file for TASKKY.

Functionalities include writing the vector of Tasks into the save file and parsing the saved 
file into a vector of Tasks.

The save file has to be named "Save.json", but location of the file can be anywhere, handled
by the CommandChangeFileLocation and CommandCheckFileLocation classes.

Save.json should not be tampered by user manually, as editing it may cause error in parsing
should the format of the document does not match the JSON Object standard.
*/

#include "Storage.h"

/*
* ====================================================================
*  Constructors
* ====================================================================
*/

//Default Constructor
Storage::Storage()
{
}

//Returns an instance of Storage class
Storage* Storage::getInstance(){
	if (!_instance)
		_instance = new Storage;
	return _instance;
}

/*
* ====================================================================
*  Main Program
* ====================================================================
*/

//This function access the current TaskVector from TaskManager class and writes it to
//JSON file. If TaskVector is empty, it will replace the save file with an empty JSON
//file.
//
//@param = none
//@return = none
void Storage::writeToFile(){
	std::string filename = determineFileName();
	if ((TaskManager::getAllCurrentTasks())->empty()){
		clearSaveFile(filename);
	}
	else {
		writeJSONtoFile(filename, parseVectorToJSON(*(TaskManager::getAllCurrentTasks())));
	}
	return;
}

//This function checks if the save file is valid, access the save file, parse it into a 
//JSON object and build into a TaskVector. Return the TaskVector to TaskManager for it to 
//build into the vector that the code will access. If save file location is invalid, it will
//point back to the default save file location and access the save file there.
//
//@param = none
//@return = vector of Tasks.
vector<Task> Storage::readFromFile(){
	if (!dirExists(CommandCheckFileLocation::getFileLocation())){
		if (CommandCheckFileLocation::getFileLocation() != "default"){
			setLocationAsDefault();
			std::cout << FILE_LOCATION_INVALID << endl;
		}
	}
	std::string filename = determineFileName();
	checkSaveFile(filename);
	return parseSaveFileToVector(filename);
}


/*
* ====================================================================
*  Second Abstraction
* ====================================================================
*/

//This function replaces the save file with an empty JSON file
//
//@param = save file name
//@return = none
void Storage::clearSaveFile(string filename){
	remove(filename.c_str());

	//write empty json
	FILE* fp = fopen(filename.c_str(), "wb"); // non-Windows use "w"

	fclose(fp);
}

//This function converts the vector of tasks into a JSON object, preparing it to be written
//into a file. It takes in the vector of tasks to be converted and return the equivalent 
//JSON object.
//
//@param = vector of Tasks
//@return = equivalent JSON object
rapidjson::Document Storage::parseVectorToJSON(vector<Task> TaskVector){
	vector<Task>::iterator iter;
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.SetArray();

	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {
		rapidjson::Value object = convertTaskToJSON(*iter, allocator); //Process each Task into a JSON object
		document.PushBack(object, allocator); //Add JSON object into JSON array
	}

	return document;
}

//This function actually writes the JSON object into a JSON file. This function takes in
//the save file name and the JSON object to be written.
//
//@param = save file name, JSON object to be written
//@return = none
void Storage::writeJSONtoFile(string filename, rapidjson::Document document){
	FILE* fp = fopen(filename.c_str(), "wb"); // non-Windows use "w"
	char writeBuffer[65536];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	document.Accept(writer);

	fclose(fp);

	return;
}

//This function changes the save file location to the default location.
//
//@param = none
//@return = none
void Storage::setLocationAsDefault(){
	remove("saveFileLocation.txt");
	ofstream writeFile("saveFileLocation.txt");
	if (writeFile.is_open()){
		writeFile << "default";
		writeFile.close();
	}
	return;
}

//This function concatenates the file directory and save file name. The full path will be the
//one used by the code to save, load, etc.
//
//@param = none
//@return = save file full path name
string Storage::determineFileName(){
	std::string filename;
	std::string fileDirectory = CommandCheckFileLocation::getFileLocation();
	if (fileDirectory == "default"){
		filename = findProgramDirectory() + "/Save.json";
	} else {
		filename = fileDirectory + "/Save.json";
	}

	return filename;
}

//This function checks if the full path of the save file exists. If it does not exist, we
//assume a new user and create the new save file.
//
//@param = save file full path name
//@return = none
void Storage::checkSaveFile(string filename){
	if (FILE *file = fopen(filename.c_str(), "r")) {
		fclose(file);
	}
	else {
		std::cout << FILENAME_NOT_FOUND << endl;
		FILE* createFile = fopen(filename.c_str(), "wb"); // non-Windows use "w"
		fclose(createFile);
	}
	return;
}

//This function iterate through the save file, convert the text into a JSON object and construct
//a vector of Tasks from the JSON object.
//
//@param = save file full path name
//@return = vector of Tasks
vector<Task> Storage::parseSaveFileToVector(string filename){
	//open file
	FILE* fp = fopen(filename.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document d;
	d.ParseStream(is);

	fclose(fp);

	//variables declarations
	vector<Task> TaskVector;

	std::string taskname;

	std::string startTime_str;
	Date* startTime = NULL;

	std::string endTime_str;
	Date* endTime = NULL;

	std::string deadline_str;
	Date* deadline = NULL;

	Task::Priority priority;
	std::string p_low = "LOW";
	std::string p_normal = "NORMAL";
	std::string p_high = "HIGH";

	bool marked = false;

	//check if empty
	if (d.IsNull()) {
		return TaskVector;
	}
	else {
		//Parse and construct Task Vector
		int i = 0;
		for (rapidjson::Value::ConstValueIterator itr = d.Begin(); itr != d.End(); ++itr){


			//Task Details
			if (d[i].HasMember("taskname")){
				taskname = d[i]["taskname"].GetString();
			}

			//Task Time
			if (d[i]["startTime"].IsNull()) {
				if (d[i]["deadline"].IsNull())
				{
					startTime = NULL;
					endTime = NULL;
					deadline = NULL;
				}
				else if (d[i]["deadline"].IsObject()){
					startTime = NULL;
					endTime = NULL;

					int day = d[i]["deadline"]["day"].GetInt();
					int month = d[i]["deadline"]["month"].GetInt();
					int year = d[i]["deadline"]["year"].GetInt();
					int hour = d[i]["deadline"]["hour"].GetInt();
					int minutes = d[i]["deadline"]["minutes"].GetInt();

					deadline = new Date(year, month, day, hour, minutes);
				}
			}
			else if (d[i]["startTime"].IsObject()) {
				deadline = NULL;

				int day = d[i]["startTime"]["day"].GetInt();
				int month = d[i]["startTime"]["month"].GetInt();
				int year = d[i]["startTime"]["year"].GetInt();
				int hour = d[i]["startTime"]["hour"].GetInt();
				int minutes = d[i]["startTime"]["minutes"].GetInt();

				startTime = new Date(year, month, day, hour, minutes);

				day = d[i]["endTime"]["day"].GetInt();
				month = d[i]["endTime"]["month"].GetInt();
				year = d[i]["endTime"]["year"].GetInt();
				hour = d[i]["endTime"]["hour"].GetInt();
				minutes = d[i]["endTime"]["minutes"].GetInt();

				endTime = new Date(year, month, day, hour, minutes);
			}

			//Task Priority
			if (d[i]["priority"].GetString() == p_normal) {
				priority = Task::Priority::NORMAL;
			}
			else if (d[i]["priority"].GetString() == p_high) {
				priority = Task::Priority::HIGH;
			}

			//Task Marked
			if (d[i]["marked"].GetBool() == true){
				marked = true;
			}
			else if (d[i]["marked"].GetBool() == false){
				marked = false;
			}

			//construct task object
			Task task(taskname, startTime, endTime, deadline, priority);
			task.setTaskMarked(marked);

			//Push into taskVector
			TaskVector.push_back(task);

			++i;
		}
		return TaskVector;
	}
}



/*
* ====================================================================
*  Third Abstraction
* ====================================================================
*/

//This function converts one Task object into a JSON object.
//
//@param = Task object, JSON object allocator
//@return = JSON object
rapidjson::Value Storage::convertTaskToJSON(Task task, rapidjson::Document::AllocatorType& allocator){
	rapidjson::Value taskname;
	rapidjson::Value startTime;
	rapidjson::Value endTime;
	rapidjson::Value deadline;
	rapidjson::Value priority;
	rapidjson::Value marked;
	char buffer[1024];
	int len;
	
	//Check Task Details
	len = sprintf(buffer, task.getTaskDetails().c_str());
	taskname.SetString(buffer, len, allocator);

	//Check Task Type and Time
	if (task.getTaskType() == Task::FLOATING) {
		startTime.SetNull();
		endTime.SetNull();
		deadline.SetNull();
	}
	else if (task.getTaskType() == Task::TIMED) {
		Date time = *(task.getTaskStartTime());

		startTime.SetObject();
		startTime.AddMember("day", time.getDay(), allocator);
		startTime.AddMember("month", time.getMonth(), allocator);
		startTime.AddMember("year", time.getYear(), allocator);
		startTime.AddMember("hour", time.getHour(), allocator);
		startTime.AddMember("minutes", time.getMinute(), allocator);

		time = *(task.getTaskEndTime());

		endTime.SetObject();
		endTime.AddMember("day", time.getDay(), allocator);
		endTime.AddMember("month", time.getMonth(), allocator);
		endTime.AddMember("year", time.getYear(), allocator);
		endTime.AddMember("hour", time.getHour(), allocator);
		endTime.AddMember("minutes", time.getMinute(), allocator);

		deadline.SetNull();
	}
	else if (task.getTaskType() == Task::DEADLINE) {
		startTime.SetNull();
		endTime.SetNull();

		Date time = *(task.getTaskDeadline());

		deadline.SetObject();
		deadline.AddMember("day", time.getDay(), allocator);
		deadline.AddMember("month", time.getMonth(), allocator);
		deadline.AddMember("year", time.getYear(), allocator);
		deadline.AddMember("hour", time.getHour(), allocator);
		deadline.AddMember("minutes", time.getMinute(), allocator);
	}

	//Check Task Priority
	if (task.getTaskPriority() == Task::Priority::HIGH) {
		char prior[1024];
		int leng = sprintf(prior, "HIGH");

		priority.SetString(prior, leng, allocator);
	} else if (task.getTaskPriority() == Task::Priority::NORMAL) {
		char prior[1024];
		int leng = sprintf(prior, "NORMAL");

		priority.SetString(prior, leng, allocator);
	} else {
		char prior[1024];
		int leng = sprintf(prior, "NORMAL");

		priority.SetString(prior, leng, allocator);
	}

	//Check if task is marked
	if (task.getTaskMarked()){
		marked.SetBool(true);
	} else {
		marked.SetBool(false);
	}

	//Convert to json values
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("taskname", taskname, allocator);
	object.AddMember("startTime", startTime, allocator);
	object.AddMember("endTime", endTime, allocator);
	object.AddMember("deadline", deadline, allocator);
	object.AddMember("priority", priority, allocator);
	object.AddMember("marked", marked, allocator);

	return object;
}

//This function checks the location/directory of the .exe file
//
//@param = none
//@return = directory of the .exe file
string Storage::findProgramDirectory(){
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << DIRECTORY_ERROR << endl;
	}

	return cCurrentPath;
}

//This function checks if the directory exists.
//
//@param = directory to be checked
//@return = boolean value (true/false)
bool Storage::dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

/*
* ====================================================================
*  Variables and Messages Declaration
* ====================================================================
*/

Storage* Storage::_instance = NULL;
const string Storage::DIRECTORY_ERROR = "Directory not found";
const string Storage::FILENAME_NOT_FOUND = "New User detected. To help you get started, type help";
const string Storage::FILE_LOCATION_INVALID = "File location invalid, save file location restored to default.";
