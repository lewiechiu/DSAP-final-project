#include "mission.h"
#include "time.h"
#include<string>
using namespace std;
Mission::Mission():Event(), index(0), totalCnt(0), tagForCategory(""), priority(-1), isScheduled(false)
{
    /*
    deadline not initialized yet
    */
}
Mission::Mission(string name,string tagForGraph,string tagForC,int index,int totalCnt,int priority,OurTime deadline,int duration) :index(index),totalCnt(totalCnt)
,priority(priority),deadline(deadline),tagForCategory(tagForC)
{
    this->name = name;
    this->tagForGraph = tagForGraph;
    this->duration = duration;
    this->isScheduled = false;
    this->isDone = false;
}

Mission::Mission(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration,
                int index, int totalCnt, string tagForCategory, int priority, OurTime deadline)
                :Event(name, tagForGraph, startTime, endTime, duration), index(index), totalCnt(totalCnt), tagForCategory(tagForCategory), priority(priority), deadline(deadline)
{
}

Mission::Mission(string name,string tagForGraph,OurTime StartT,OurTime EndT,int duration_int,int index_int,
            int totalCnt_int,string tagCategory,int priority_int,OurTime DeadT,bool isDone_b,bool isScheduled_b)
            :Event(name, tagForGraph, StartT, EndT, duration_int), index(index_int), totalCnt(totalCnt_int),
            tagForCategory(tagCategory), priority(priority_int), deadline(DeadT),isScheduled(isScheduled_b)
            {
                this->isDone = isDone_b;
            }


double Mission::score() const
{
    OurTime tem;
    tem.Current();
    int timeLeft = this->deadline - tem;

    return (static_cast<double>(priority) / static_cast<double>(timeLeft));
}
bool Mission::operator<(Mission toCompare) const
{
    return (this->score() < toCompare.score());
}
bool Mission::operator==(Mission toCompare) const
{
    return (this->score()== toCompare.score());
}
bool Mission::operator>(Mission toCompare) const
{
    return (this->score() > toCompare.score());
}
bool Mission::operator>=(Mission toCompare) const
{
    return (this->score() >= toCompare.score());
}
bool Mission::operator<=(Mission toCompare) const
{
    return (this->score() <= toCompare.score());
}
int Mission::getDuration() const
{
    return this->duration;
}

bool Mission::GetMisDone()const
{
    return this->isDone;
}
string Mission::GetMindex()const
{
    return to_string(this->index);
}
string Mission::GetMtotalCnt()const
{
    return to_string(this->totalCnt);
}
string Mission::GetMpriority()const
{
    return to_string(this->priority);
}
string Mission::GetMdeadline()const
{
    return this->deadline.getTimeStr();
}
bool Mission::GetMisScheduled()const
{
    return this->isScheduled;
}
string Mission::GetMtagCategory()const
{
    return this->tagForCategory;
}
void Mission::setStartTime(OurTime& ST)
{
    this->startTime = ST;
}
void Mission::setEndTime(OurTime& ET)
{
    this->endTime = ET;
}
void Mission::setIsSchedule(bool isS)
{
    this->isScheduled = isS;
}
