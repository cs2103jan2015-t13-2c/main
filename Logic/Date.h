#pragma once
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

class Date
{
public:
	Date();
	Date(int year, int mon, int day, int hour, int min);
	
	int isEarlierThan(Date dateToCompare);
	int Date::diffInMinutes(Date dateToCompare);

	std::chrono::system_clock::time_point getTimePoint();

	string toString();

	int getYear();
	int getMonth();
	int getDay();
	int getDayName();
	int getHour();
	int getMinute();

private:
	std::chrono::system_clock::time_point _currentDate;
};

