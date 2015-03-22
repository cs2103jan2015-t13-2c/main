#include "Date.h"

//Default is construct current date
Date::Date(){
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	_currentDate = today;
}

Date::Date(int year, int mon, int day, int hour, int min){
	struct std::tm t;
	t.tm_sec = 0;        // second of minute (0 .. 59 and 60 for leap seconds)
	t.tm_min = min;        // minute of hour (0 .. 59)
	t.tm_hour = hour;      // hour of day (0 .. 23)
	t.tm_mday = day;       // day of month (0 .. 31)
	t.tm_mon = mon;      // month of year (0 .. 11)
	t.tm_year = year - 1900; // year since 1900
	t.tm_isdst = -1;       // determine whether daylight saving time
	std::time_t tt = std::mktime(&t);
	if (tt == -1) {
		throw "no valid system time";
	}
	_currentDate = std::chrono::system_clock::from_time_t(tt);
}

string Date::toString(){
	std::time_t t = std::chrono::system_clock::to_time_t(_currentDate);
	std::string ts = ctime(&t);   // convert to calendar time
	ts.resize(ts.size() - 1);       // skip trailing newline
	return ts;
}

std::chrono::system_clock::time_point Date::getTimePoint(){
	return _currentDate;
}


//process difference between timepoints, looking at minute scale
//if earlier, return 1
//if same, return 0
//if later, return -1
int Date::isEarlierThan(Date dateToCompare){
	chrono::time_point<chrono::system_clock> tp;
	tp = dateToCompare.getTimePoint();
	std::chrono::minutes dateMinutes = std::chrono::duration_cast<std::chrono::minutes>(getTimePoint() - tp);
	std::chrono::minutes date2Minutes = std::chrono::duration_cast<std::chrono::minutes>(dateToCompare.getTimePoint() - tp);
	int numMinutes = date2Minutes.count() - dateMinutes.count();
	if (numMinutes==0){
		return 0;
	}
	else if (numMinutes>0){
		return 1;
	}
	else{
		return -1;
	}
}

int Date::diffInMinutes(Date dateToCompare){
	chrono::time_point<chrono::system_clock> tp;
	tp = dateToCompare.getTimePoint();
	std::chrono::minutes dateMinutes = std::chrono::duration_cast<std::chrono::minutes>(getTimePoint() - tp);
	std::chrono::minutes date2Minutes = std::chrono::duration_cast<std::chrono::minutes>(dateToCompare.getTimePoint() - tp);
	int numMinutes = date2Minutes.count() - dateMinutes.count();
	return numMinutes;
}

int Date::getYear(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_year+1900;
}

int Date::getMonth(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mon;
}

int Date::getDay(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mday;
}


int Date::getDayName(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_wday;
	/*int day = local_tm.tm_wday;
	string temp = "";
	switch (day){
		case 0: temp = "Sun";
		case 1: temp = "Mon";
		case 2: temp = "Tue";
		case 3: temp = "Wed";
		case 4: temp = "Thu";
		case 5: temp = "Fri";
		case 6: temp = "Sat";
		default: temp = "Error String!";
	}
	return temp;*/
}

int Date::getHour(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_hour;
}

int Date::getMinute(){
	time_t tt = std::chrono::system_clock::to_time_t(getTimePoint());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_min;
}