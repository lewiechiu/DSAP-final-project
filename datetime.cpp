#include <iostream>
#include "datetime.h"
#include <time.h>
using namespace std;

datetime::datetime()
{
	time_t now = time(NULL);

}

datetime::datetime(string* str)
{
	string eventtime = str;
	int year = stoi(eventtime.substr(0,4));
	eventtime.erase(0,1);
	int month =  stoi(eventtime.substr(0,2));
	eventtime.erase(0,1);
	int day =  stoi(eventtime.substr(0,2));
	eventtime.erase(0,1);
	int hour =  stoi(eventtime.substr(0,2));
	eventtime.erase(0,1);
	int minute =  stoi(eventtime.substr(0,2));
}
datetime datetime::operator+(const datetime& tar)
{
	int biggermonth[] = {1,3,5,7,8,10,11};
	this->minute += tar.minute;
	if(this->minute>=60)
	{
		this->minute -= 60;
		this->hour++;
	}
	this->hour += tar.hour;
	if(this->hour>=24)
	{
		this->hour -= 24;
		this->day++;
	}
	this->day += tar.day;
	this->month += tar.month;
	while(1)
	{
		if(this->day>28&&this->month == 2)
		{
			this->month++;
			this->day -= 28;

		}
		else if(this->day>30&&(this->month == 4||this->month == 6
							||this->month == 9||this->month == 11))
		{
			this->month++;
			this->day -=30;
		}
		else if(this->day>31&&(this->month == 1||this->month == 3
							||this->month == 5||this->month == 7
							||this->month == 8||this->month == 10
							||this->month == 12))
		{
			this->month++;
			this->day -=31;
		}
		if(this->month>12)
		{
			this->year++;
			this->month -=12;
		}
		else
			break;
	}
}
bool datetime::operator>(const datetime& tar)
{
	bool larger = false;
	if(this->year == tar.year)
	{
		if(this->month == tar.month)
		{
			if(this->day == tar.day)
			{
				if(this->hour == tar.hour)
				{
					if(this->minute == tar.minute)
						return true;
					else
						return false;
				}
				else if(this->hour > tar.hour)
					return true;
			}
			else if(this->day > tar.day)
				return true;
		}
		else if(this->month > tar.month)
			return true;
	}
	else if(this->year > tar.year)
		return true;
}

bool datetime::operator==(const datetime& tar)
{
		bool Equal = false;
	if(this->year == tar.year && this->month == tar.month
		&& this->day == tar.day && this->hour == tar.hour
		&& this->minute == tar.minute)
	{
		return true;
	}
}
