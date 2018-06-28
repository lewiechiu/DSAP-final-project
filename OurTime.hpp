#ifndef Time_h
#define Time_h
#include <iostream>
#include <string>
using namespace std;

//Declaration of global functions
int monthDays(int mon, int year);
int yearDays(int year);

//Declaration of Time----------------------------------------------//
class OurTime{
    
    friend const OurTime operator+(const OurTime& t, int minute);
    friend ostream& operator<<(ostream& out, const OurTime& t);
    
private:
    string timeStr; //201808291503
    int year;       //2018
    int month;      //08
    int day;        //29
    int hour;       //15
    int minute;     //03
    
public:
    OurTime();
    OurTime(string timeStr);
    OurTime(const OurTime& t);
    
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    void setHour(int h);
    void setMinute(int m);
    void setTimeStr();
    int getYear();
    int getMonth();
    
    bool monthChanged(int addingDay);
    void newDate(int addingDay);
    
    const int operator-(const OurTime& t);
};
const OurTime operator+(const OurTime& t, int minute);
ostream& operator<<(ostream& out, const OurTime& t);

#endif /* Time_h */
