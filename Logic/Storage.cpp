#include "Storage.h"

Storage* Storage::_instance = NULL;
const string Storage::DIRECTORY_ERROR = "Directory not found";
const string Storage::FILENAME_NOT_FOUND = "New User detected. To help you get started, type help";
const string Storage::FILE_LOCATION_INVALID = "File location invalid, save file location restored to default.";

Storage::Storage()
{
}

Storage* Storage::getInstance(){
	if (!_instance)
		_instance = new Storage;
	return _instance;
}


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

vector<Task> Storage::readFromFile() {
	//check valid directory for save file location
	if (!dirExists(CommandCheckFileLocation::getFileLocation())){
		if (CommandCheckFileLocation::getFileLocation() != "default"){
			setLocationAsDefault();
			std::cout << FILE_LOCATION_INVALID << endl; //Print error message: save file location invalid
		}
	}
	std::string filename = determineFileName();
	checkSaveFile(filename); //if file doesn't exist assume new user and create new saveFile.
	return parseSaveFileToVector(filename); //Parse saveFile document into TaskVector
}


string Storage::findProgramDirectory(){
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << DIRECTORY_ERROR << endl;
	}

	return cCurrentPath;
}

string Storage::determineFileName(){
	std::string filename;
	std::string fileDirectory = CommandCheckFileLocation::getFileLocation();
	if (fileDirectory == "default") {
		filename = findProgramDirectory() + "/Save.json";
	}
	else {
		filename = fileDirectory + "/Save.json";
	}

	return filename;
}

bool Storage::dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

void Storage::setLocationAsDefault(){
	remove("saveFileLocation.txt");
	ofstream writeFile("saveFileLocation.txt");
	if (writeFile.is_open()){
		writeFile << "default";
		writeFile.close();
	}
	return;
}

void Storage::checkSaveFile(string filename){
	if (FILE *file = fopen(filename.c_str(), "r")) {
		fclose(file);
	}
	else {
		std::cout << FILENAME_NOT_FOUND << endl;
		FILE* createFile = fopen(filename.c_str(), "wb"); // non-Windows use "w"
		fclose(createFile);
	}
}

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
				else if (d[i]["deadline"].IsObject()) {
					int day = d[i]["deadline"]["day"].GetInt();
					int month = d[i]["deadline"]["month"].GetInt();
					int year = d[i]["deadline"]["year"].GetInt();
					int hour = d[i]["deadline"]["hour"].GetInt();
					int minutes = d[i]["deadline"]["minutes"].GetInt();

					deadline = new Date(year, month, day, hour, minutes);
				}
			}
			else if (d[i]["startTime"].IsObject()) {
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
			if (d[i]["priority"].GetString() == p_low) {
				priority = Task::Priority::LOW;
			}
			else if (d[i]["priority"].GetString() == p_normal) {
				priority = Task::Priority::NORMAL;
			}
			else if (d[i]["priority"].GetString() == p_high) {
				priority = Task::Priority::HIGH;
			}


			//construct task object
			Task task(taskname, startTime, endTime, deadline, priority);

			//Push into taskVector
			TaskVector.push_back(task);

			++i;
		}
		return TaskVector;
	}
}

void Storage::clearSaveFile(string filename){
	remove(filename.c_str());

	//write empty json
	FILE* fp = fopen(filename.c_str(), "wb"); // non-Windows use "w"

	fclose(fp);
}

rapidjson::Document Storage::parseVectorToJSON(vector<Task> TaskVector){
	vector<Task>::iterator iter;
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value taskname;
	rapidjson::Value startTime;
	rapidjson::Value endTime;
	rapidjson::Value deadline;
	rapidjson::Value priority;
	char buffer[1024];
	int len;

	document.SetArray();

	//Parse vector of Tasks into JSON object
	for (iter = TaskVector.begin(); iter != TaskVector.end(); ++iter) {

		//Check Task Details
		len = sprintf(buffer, iter->getTaskDetails().c_str());
		taskname.SetString(buffer, len, allocator);

		//Check Task Type and Time
		if (iter->getTaskType() == Task::FLOATING) {
			startTime.SetNull();
			endTime.SetNull();
			deadline.SetNull();
		}
		else if (iter->getTaskType() == Task::TIMED) {
			Date time = *(iter->getTaskStartTime());

			startTime.SetObject();
			startTime.AddMember("day", time.getDay(), allocator);
			startTime.AddMember("month", time.getMonth(), allocator);
			startTime.AddMember("year", time.getYear(), allocator);
			startTime.AddMember("hour", time.getHour(), allocator);
			startTime.AddMember("minutes", time.getMinute(), allocator);

			time = *(iter->getTaskEndTime());

			endTime.SetObject();
			endTime.AddMember("day", time.getDay(), allocator);
			endTime.AddMember("month", time.getMonth(), allocator);
			endTime.AddMember("year", time.getYear(), allocator);
			endTime.AddMember("hour", time.getHour(), allocator);
			endTime.AddMember("minutes", time.getMinute(), allocator);

			deadline.SetNull();
		}
		else if (iter->getTaskType() == Task::DEADLINE) {
			startTime.SetNull();
			endTime.SetNull();

			Date time = *(iter->getTaskDeadline());

			deadline.SetObject();
			deadline.AddMember("day", time.getDay(), allocator);
			deadline.AddMember("month", time.getMonth(), allocator);
			deadline.AddMember("year", time.getYear(), allocator);
			deadline.AddMember("hour", time.getHour(), allocator);
			deadline.AddMember("minutes", time.getMinute(), allocator);
		}

		//Check Task Priority
		if (iter->getTaskPriority() == Task::Priority::HIGH) {
			char prior[1024];
			int leng = sprintf(prior, "HIGH");

			priority.SetString(prior, leng, allocator);
		}
		else if (iter->getTaskPriority() == Task::Priority::NORMAL) {
			char prior[1024];
			int leng = sprintf(prior, "NORMAL");

			priority.SetString(prior, leng, allocator);
		}
		else if (iter->getTaskPriority() == Task::Priority::LOW) {
			char prior[1024];
			int leng = sprintf(prior, "LOW");

			priority.SetString(prior, leng, allocator);
		}
		else {
			char prior[1024];
			int leng = sprintf(prior, "NORMAL");

			priority.SetString(prior, leng, allocator);
		}

		//Convert to json values
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("taskname", taskname, allocator);
		object.AddMember("startTime", startTime, allocator);
		object.AddMember("endTime", endTime, allocator);
		object.AddMember("deadline", deadline, allocator);
		object.AddMember("priority", priority, allocator);

		document.PushBack(object, document.GetAllocator());
	}

	return document;
}

void Storage::writeJSONtoFile(string filename, rapidjson::Document document){
	FILE* fp = fopen(filename.c_str(), "wb"); // non-Windows use "w"
	char writeBuffer[65536];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	document.Accept(writer);

	fclose(fp);

	return;
}

/*
void Storage::loadfromFile(vector<Task> &tempSave, string fileName) {
ifstream file;
file.open(fileName.c_str());

int taskNumber;
string taskDetails;
Date taskStartTime;
Date taskEndTime;
Date taskDeadline;
Task::Recurrence taskRecurrence;
Task::Priority taskPriority;
bool taskMarked;

while (!file.eof()) {
//Will do this part after our time problem is solved
}
}

void Storage::writetoFile(vector<Task> tempSave, string fileName) {
ofstream file;
file.open(fileName.c_str(), fstream::trunc);

vector<Task>::iterator iter;

for (iter = tempSave.begin(); iter != tempSave.end(); ++iter) {
int taskNumber = 1;
file << "=============================" << endl;
file << "Task #" << setw(8) << setfill('0') << taskNumber << endl;
file << "=============================" << endl;
file << (*iter).getTaskType() << endl;
file << (*iter).getTaskDetails() << endl;
file << (*(*iter).getTaskStartTime()).toString() << endl;
file << (*(*iter).getTaskEndTime()).toString() << endl;
file << (*(*iter).getTaskDeadline()).toString() << endl;
file << (*iter).getTaskRecurrence() << endl;
file << (*iter).getTaskPriority() << endl;
file << "\n\n";
taskNumber++;
}

file.close();
return;
}
*/
