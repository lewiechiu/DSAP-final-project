#include <stdio.h>
#include "Time.h"
#include <iostream>
#include <string>
using namespace std;

//Implementation of Time----------------------------------------------//
Time::Time():year(0), month(0), day(0), hour(0), minute(0){}
Time::Time(string timeStr)
{
    //string form : 201808291503
    this->timeStr = timeStr;
    this->year = stoi(timeStr.substr(0, 4));
    this->month = stoi(timeStr.substr(4, 2));
    this->day = stoi(timeStr.substr(6, 2));
    this->hour =stoi(timeStr.substr(8, 2));
    this->minute = stoi(timeStr.substr(10, 2));
}
Time::Time(const Time& t)
{
    this->timeStr = t.timeStr;
    this->year = t.year;
    this->month = t.month;
    this->day = t.day;
    this->hour =t.hour;
    this->minute = t.minute;
}
void Time::setYear(int y)
{
    this->year = y;
}
void Time::setMonth(int m)
{
    this->month = m;
}
void Time::setDay(int d)
{
    this->day = d;
}
void Time::setHour(int h)
{
    this->hour = h;
}
void Time::setMinute(int m)
{
    this->minute = m;
}
void Time::setTimeStr()
{
    string newTimeStr;
    newTimeStr += to_string(this->year);
    if(this->month < 10)
        newTimeStr += to_string(0);
    newTimeStr += to_string(this->month);
    if(this->day < 10)
        newTimeStr += to_string(0);
    newTimeStr += to_string(this->day);
    if(this->hour < 10)
        newTimeStr += to_string(0);
    newTimeStr += to_string(this->hour);
    if(this->minute < 10)
        newTimeStr += to_string(0);
    newTimeStr += to_string(this->minute);
    
    this->timeStr = newTimeStr;
}
bool Time::monthChanged(int addingDay)
{
    if((monthDays(this->month, this->year) - this->day) < addingDay)
        return true;
    return false;
}
void Time::newDate(int addingDay)
{
    int mon = this->month;
    int date = this->day;
    int daysOfMonth = 0;
    int aNewYear  = 0;
    while(addingDay != 0)
    {
        daysOfMonth = monthDays(mon, (this->year + aNewYear));
        if((daysOfMonth - date) < addingDay)//01/20 + 15days = 02/04
        {
            addingDay -= (daysOfMonth - date);//15 - (31 - 20) = 4, already added days = 11 days
            if((month + 1 )!= 13)
                mon++;//not for recording the real month, but for determing days of next month
            else
            {
                mon = 1;
                aNewYear++;
            }
            date = 0;
        }
        else
        {
            date += addingDay;
        }
    }
    if(date != 0)
    {
        this->day = date;
        this->month = mon;
        this->year += aNewYear;
    }
    else
    {
        if(mon != 1)
        {
            this->month--;
            this->day = monthDays(this->month, (this->year + aNewYear));
            this->year += aNewYear;
        }
        else
        {
            aNewYear--;
            this->month = 12;
            this->day = 31;
            this->year += aNewYear;
        }
    }
}
const Time Time::operator+(const Time& t)
{
    Time sum(*this);
    int timeTemp = 0;
    
    timeTemp = sum.minute + t.minute;
    if(timeTemp < 60)
        sum.minute = timeTemp;
    else//hour is carried
    {
        sum.minute = timeTemp % 60;
        
        timeTemp = timeTemp / 60 + sum.hour;
        if(timeTemp < 24)
            sum.hour = timeTemp;
        else//day is carried
        {
            sum.hour = timeTemp % 24;
            
            timeTemp = timeTemp / 24;//number of days that is going to be added
            if(!monthChanged(timeTemp))
                sum.day += timeTemp;
            else//month is carried
                newDate(timeTemp);
        }
    }
    sum.setTimeStr();
    return sum;
}

const int Time::operator-(const Time& t)
{
    Time minus(*this);
    int period = 0;
    //hour, minute
    if(this->year == t.year && this->month == t.month && this->day == t.day
       && this->hour == t.hour)
    {
        period += this->minute - t.minute;
    }
    else if(this->year == t.year && this->month == t.month && this->day == t.day
            && this->hour != t.hour)
    {
        if(this->minute >= t.minute)
        {
            period += this->minute - t.minute;
            period += (this->hour - t.hour) * 60;
        }
        else
        {
            period += t.minute - this->minute;
            period += (this->hour - t.hour - 1) * 60;
        }
    }
    else if(this->year == t.year && this->month == t.month && this->day != t.day)
    {
        if(this->minute >= t.minute)
        {
            period += this->minute - t.minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour) * 60;
                period += (this->day - t.day) * 60 * 24;
            }
            else
            {
                period += (t.hour - this->hour) * 60;
                period += (this->day - t.day - 1) * 60;
            }
        }
        else
        {
            period += t.minute - this->minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour - 1) * 60;
                period += (this->day - t.day) * 60 * 24;
                
            }
            else
            {
                period += (t.hour - this->hour - 1) * 60;
                period += (this->day - t.day - 1) * 60;
            }
        }
    }
    else if(this->year == t.year && this->month != t.month)
    {
        if(this->minute >= t.minute)
        {
            period += this->minute - t.minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour) * 60;
            }
            else
            {
                period += (t.hour - this->hour) * 60;
            }
        }
        else
        {
            period += t.minute - this->minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour - 1) * 60;
            }
            else
            {
                period += (t.hour - this->hour - 1) * 60;
            }
        }
        int dayCntL = 0, dayCntR = 0;
        for(int i = 1; i < this->month; i++)
        {
            dayCntL += monthDays(i, this->year);
        }
        for(int i = 1; i < t.month; i++)
        {
            dayCntR += monthDays(i, t.year);
        }
        dayCntL += this->day;
        dayCntR += t.day;
        
        period += (dayCntL - dayCntR) * 60 * 24;
    }
    else if(this->year != t.year)
    {
        if(this->minute >= t.minute)
        {
            period += this->minute - t.minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour) * 60;
            }
            else
            {
                period += (t.hour - this->hour) * 60;
            }
        }
        else
        {
            period += t.minute - this->minute;
            if(this->hour >= t.hour)
            {
                period += (this->hour - t.hour - 1) * 60;
            }
            else
            {
                period += (t.hour - this->hour - 1) * 60;
            }
        }
        int dayCntL = 0, dayCntR = 0, dayCntYear = 0;
        for(int i = this->month + 1; i <= 12; i++)
        {
            dayCntL += monthDays(i, this->year);
        }
        for(int i = 1; i < t.month; i++)
        {
            dayCntR += monthDays(i, t.year);
        }
        for(int i = this->year + 1; i < t.year; i++)
        {
            dayCntYear += yearDays(i);
        }
        dayCntL += monthDays(this->month, this->year) - this->day;
        dayCntR += t.day;
        
        period += (dayCntL + dayCntYear + dayCntR) * 60 * 24;
    }
    return period;
}
const Time operator+(const Time& t, int minute)
{
    Time sum(t);
    int timeTemp = 0;
    
    timeTemp = sum.minute + minute;
    if(timeTemp < 60)
        sum.minute = timeTemp;
    else//hour is carried
    {
        sum.minute = timeTemp % 60;
        
        timeTemp = timeTemp / 60 + sum.hour;
        if(timeTemp < 24)
            sum.hour = timeTemp;
        else//day is carried
        {
            sum.hour = timeTemp % 24;
            
            timeTemp = timeTemp / 24;//number of days that is going to be added
            if(!sum.monthChanged(timeTemp))
                sum.day += timeTemp;
            else//month is carried
            {
                sum.newDate(timeTemp);
            }
        }
    }
    sum.setTimeStr();
    return sum;
}
ostream& operator<<(ostream& out, const Time& t)
{
    out << t.timeStr;
    return out;
}

//Definition of global functions
int monthDays(int mon, int year)
{
    int monDays = 0;
    switch (mon)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            monDays = 31;
            break;
        case 2:
            if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                monDays = 29;
            else
                monDays = 28;//閏年問題
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            monDays = 30;
            break;
    }
    return monDays;
}
int yearDays(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 366;
    else
        return 365;
}
















