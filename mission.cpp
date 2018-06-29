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
Mission::Mission(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration,
                int index, int totalCnt, string tagForCategory, int priority, OurTime deadline)
                :Event(name, tagForGraph, startTime, endTime, duration), index(index), totalCnt(totalCnt), tagForCategory(tagForCategory), priority(priority), deadline(deadline)
{
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
