
#ifndef EVENT
#define EVENT

#include<string>
#include "Time.h"
using namespace std;
class Event
{
private:
protected:
    int duration; //unit: minute
    string name;
    string tagForGraph;
    Time startTime;
    Time endTime;
    bool isDone;
public:
    Event();
    Event(string name, string tagForGraph, Time startTime, Time endTime, int duration);
};
#endif //EVENT
