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

Date *Date::toDate(string date_str) {

	//e.g Thu Nov 05 00:00:00 2015
	date_str = removeFirstWord(date_str);

	//determine month
	int month = parseMonthName(getFirstWord(date_str));
	date_str = removeFirstWord(date_str);

	//determine day
	int day = parseInt(getFirstWord(date_str));
	date_str = removeFirstWord(date_str);

	//determine time
	string time_str = getFirstWord(date_str);
	string hours_str = date_str.substr(0, 2);
	string minutes_str = date_str.substr(3, 2);
	int hours = parseInt(hours_str);
	int minutes = parseInt(minutes_str);
	date_str = removeFirstWord(date_str);

	//determine year
	int year = parseInt(date_str);


	Date *date =  new Date (year, month, day, hours, minutes);

	return date;

}

bool Date::sameDate(Date dateToCompare){
	if (getYear() == dateToCompare.getYear() &&
		getMonth() == dateToCompare.getMonth() &&
		getDay() == dateToCompare.getDay()){
		return true;
	}
	return false;
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

//for toDate Parsing

string Date::removeFirstWord(string userCommand) {
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string Date::getFirstWord(string userCommand) {
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> Date::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string Date::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string Date::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string Date::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		return trim_left(trim_right(s, delimiters), delimiters);
	else
		return s;
}

bool Date::equalsIgnoreCase(const string& str1, const string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
		if (tolower(*c1) != tolower(*c2)) {
			return false;
		}
	}
	return true;
}

int Date::parseInt(string str) {
	char c;
	int i = 0;
	std::stringstream ss(str);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		return INVALID_NUMBER_FORMAT;
	}
	else {
		return i;
	}
}

string Date::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}

int Date::parseMonthName(string monthName) {
	int mon = 0;

	std::transform(monthName.begin(), monthName.end(), monthName.begin(), ::tolower);

	if (monthName == "january" || monthName == "jan") {
		mon = 0;
	}
	else if (monthName == "february" || monthName == "feb") {
		mon = 1;
	}
	else if (monthName == "march" || monthName == "mar") {
		mon = 2;
	}
	else if (monthName == "april" || monthName == "apr") {
		mon = 3;
	}
	else if (monthName == "may") {
		mon = 4;
	}
	else if (monthName == "june" || monthName == "jun") {
		mon = 5;
	}
	else if (monthName == "july" || monthName == "jul") {
		mon = 6;
	}
	else if (monthName == "august" || monthName == "aug") {
		mon = 7;
	}
	else if (monthName == "september" || monthName == "sep") {
		mon = 8;
	}
	else if (monthName == "october" || monthName == "oct") {
		mon = 9;
	}
	else if (monthName == "november" || monthName == "nov") {
		mon = 10;
	}
	else if (monthName == "december" || monthName == "dec") {
		mon = 11;
	} //else throw error

	return mon;
}