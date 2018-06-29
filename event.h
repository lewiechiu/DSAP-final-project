
#ifndef EVENT_h
#define EVENT_h

#include <string>
#include "OurTime.hpp"
using namespace std;
class Event
{
private:
protected:
    int duration; //unit: minute
    string name;
    string tagForGraph;
    OurTime startTime;
    OurTime endTime;
    bool isDone;
public:
    Event();
    Event(string name, string tagForGraph, OurTime startTime,OurTime endTime, int duration);
};
#endif //EVENT
