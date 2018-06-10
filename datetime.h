#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include <iostream>
using namespace std;
class datetime
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;

public:
    datetime();
    datetime(string* eventtime);
    // be of the form ->1999/04/04 19:53<-
    datetime operator+(const datetime& tar);
//    you would be passing in a time period
//    for example:
//        1999/04/04 19:53 + 0/0/30 21:15
//    time period in the latter one should thought of as
//    how many days, how many hours, how many minutes
    bool operator>(const datetime& tar);
    bool operator==(const datetime &tar);

};

#endif // TIME_H_INCLUDED
