#include "event.h"
#include "OurTime.hpp"
#include <string>
using namespace std;
Event::Event(): duration(-1), name(""), tagForGraph(""), isDone(false)
{
    /*
    initializers for startTime and endTime not implemented yet
    */
}
Event::Event(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration)
            :name(name), tagForGraph(tagForGraph), startTime(startTime),
            endTime(endTime), duration(duration), isDone(false)
{
}

string Event::GetName()const
{
    return this->name;
}
string Event::GettagForGraph()const
{
    return this->tagForGraph;
}
string Event::GetstartTime()const
{
    return this->startTime.getTimeStr();
}
string Event::GetendTime()const
{
    return this->endTime.getTimeStr();
}
string Event::GetDuration()const
{
    return to_string(this->duration);
}
bool Event::GetMisDone()const
{
}
string Event::GetMindex()const
{
}
string Event::GetMtotalCnt()const
{
}
string Event::GetMpriority()const
{
}
string Event::GetMdeadline()const
{
}
bool Event::GetMisScheduled()const
{
}
string Event::GetMtagCategory()const
{
}
void Event::setStartTime(OurTime& ST)
{
    this->startTime = ST;
}
void Event::setEndTime(OurTime& ET)
{
    this->endTime = ET;
}
void Event::setIsSchedule(bool isS)
{
}
double Event::score()const
{
}
OurTime Event::getStartTime()const
{
    return this->startTime;
}
int Event::getDuration()const
{
    return this->duration;
}
void Event::setIsDone(bool isD)
{
    this->isDone = isD;
}


