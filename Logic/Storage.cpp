#include "Storage.h"

Storage* Storage::_instance = NULL;

Storage::Storage()
{
}

Storage* Storage::getInstance(){
	if (!_instance)
		_instance = new Storage;
	return _instance;
}


void Storage::writeToFile(){

	vector<Task> TaskVector = *(TaskManager::getAllCurrentTasks());
	vector<Task>::iterator iter;

	rapidjson::Document document;

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value taskname;

	rapidjson::Value startTime;

	rapidjson::Value endTime;

	rapidjson::Value deadline;

	rapidjson::Value recurrence;

	rapidjson::Value priority;

	char buffer[1024];
	int len;

	if (TaskVector.empty()) {
		remove("Save.json");

		//write empty json
		FILE* fp = fopen("Save.json", "wb"); // non-Windows use "w"

		fclose(fp);

	}
	else {

		document.SetArray();

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

			//Check Recurrence
			if (iter->getTaskRecurrence() == Task::Recurrence::NONE) {
				char recur[1024];
				int length = sprintf(recur, "NONE");

				recurrence.SetString(recur, length, allocator);
			}
			else if (iter->getTaskRecurrence() == Task::Recurrence::DAY) {
				char recur[1024];
				int length = sprintf(recur, "DAY");

				recurrence.SetString(recur, length, allocator);
			}
			else if (iter->getTaskRecurrence() == Task::Recurrence::WEEK)	{
				char recur[1024];
				int length = sprintf(recur, "WEEK");

				recurrence.SetString(recur, length, allocator);
			}
			else if (iter->getTaskRecurrence() == Task::Recurrence::MONTH) {
				char recur[1024];
				int length = sprintf(recur, "MONTH");

				recurrence.SetString(recur, length, allocator);
			}
			else {
				char recur[1024];
				int length = sprintf(recur, "NONE");

				recurrence.SetString(recur, length, allocator);
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
			object.AddMember("recurrence", recurrence, allocator);
			object.AddMember("priority", priority, allocator);

			document.PushBack(object, document.GetAllocator());

			//writing to file
			FILE* fp = fopen("Save.json", "wb"); // non-Windows use "w"
			char writeBuffer[65536];

			rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
			rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
			document.Accept(writer);

			fclose(fp);

		}

		
	}
	return;
}

vector<Task> Storage::readFromFile() {

	if (FILE *file = fopen("Save.json", "r")) {
		fclose(file);
	}
	else {
		FILE* createFile = fopen("Save.json", "wb"); // non-Windows use "w"
		fclose(createFile);
	}

	//open file
	FILE* fp = fopen("Save.json", "rb"); // non-Windows use "r"
	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document d;
	d.ParseStream(is);

	fclose(fp);

	//variables
	vector<Task> TaskVector;

	string taskname;

	string startTime_str;
	Date* startTime = NULL;

	string endTime_str;
	Date* endTime = NULL;

	string deadline_str;
	Date* deadline = NULL;

	Task::Recurrence recurrence;
	string r_none = "NONE";
	string r_day = "DAY";
	string r_week = "WEEK";
	string r_month = "MONTH";

	Task::Priority priority;
	string p_low = "LOW";
	string p_normal = "NORMAL";
	string p_high = "HIGH";

	//check if empty
	if (d.IsNull()) {
		return TaskVector;
	}
	else {


		//Parse and construct Task Vector

		int i = 0;
		for (rapidjson::Value::ConstValueIterator itr = d.Begin(); itr != d.End(); ++itr) {


			//Task Details
			taskname = d[i]["taskname"].GetString();

			//Task Time
			if (d[i]["startTime"].IsNull()) {
				if (d[i]["deadline"].IsNull())
				{
					//startTime_str = "";
					startTime = NULL;
					//endTime_str = "";
					endTime = NULL;
					//deadline_str = "";
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




			//Task Recurrence
			if (d[i]["recurrence"].GetString() == r_none) {
				recurrence = Task::Recurrence::NONE;
			}
			else if (d[i]["recurrence"].GetString() == r_day) {
				recurrence = Task::Recurrence::DAY;
			}
			else if (d[i]["recurrence"].GetString() == r_week) {
				recurrence = Task::Recurrence::WEEK;
			}
			else if (d[i]["recurrence"].GetString() == r_month) {
				recurrence = Task::Recurrence::MONTH;
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
			Task task(taskname, startTime, endTime, deadline, recurrence, priority);

			//Push into taskVector
			TaskVector.push_back(task);

			++i;
		}



		return TaskVector;
	}
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
