#ifndef Time_h
#define Time_h
#include <iostream>
#include <string>
using namespace std;

//Declaration of global functions
int monthDays(int mon, int year);
int yearDays(int year);

//Declaration of Time----------------------------------------------//
class Time{
    
    friend const Time operator+(const Time& t, int minute);
    friend ostream& operator<<(ostream& out, const Time& t);
    
private:
    string timeStr; //201808291503
    int year;       //2018
    int month;      //08
    int day;        //29
    int hour;       //15
    int minute;     //03
    
public:
    Time();
    Time(string timeStr);
    Time(const  Time& t);
    
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    void setHour(int h);
    void setMinute(int m);
    void setTimeStr();
    
    bool monthChanged(int addingDay);
    void newDate(int addingDay);
    
    const Time operator+(const Time& t);
    const int operator-(const Time& t);
};
const Time operator+(const Time& t, int minute);
ostream& operator<<(ostream& out, const Time& t);

#endif /* Time_h */
