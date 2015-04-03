#pragma once
#include <chrono>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class Date
{
public:
	Date();
	Date(int year, int mon, int day, int hour, int min);
	
	int isEarlierThan(Date dateToCompare);
	int Date::diffInMinutes(Date dateToCompare);

	bool sameDate(Date dateToCompare);

	std::chrono::system_clock::time_point getTimePoint();

	string toString();
	static Date *toDate(string date_str);

	int getYear();
	int getMonth();
	int getDay();
	int getDayName();
	int getHour();
	int getMinute();

private:
	std::chrono::system_clock::time_point _currentDate;
	//For toDate time-date Parsing
	static string removeFirstWord(string userCommand);
	static string getFirstWord(string userCommand);
	static vector<string> splitParameters(string commandParametersString);
	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	static string trim(const string& s, const string& delimiters = " \f\n\r\t\v");
	static bool equalsIgnoreCase(const string& str1, const string& str2);
	static int parseInt(string str);
	static string replace(string a, string b, string c);
	static int parseMonthName(string monthName);

	static char buffer[255];
	static const int INVALID_NUMBER_FORMAT = -1;

};

