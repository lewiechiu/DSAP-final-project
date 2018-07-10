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
    return 0;
}
string Event::GetMindex()const
{
    return 0;
}
string Event::GetMtotalCnt()const
{
    return 0;
}
string Event::GetMpriority()const
{
    return 0;
}
string Event::GetMdeadline()const
{
    return 0;
}
bool Event::GetMisScheduled()const
{
    return 0;
}
string Event::GetMtagCategory()const
{
    return 0;
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


