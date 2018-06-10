#include "event.h"
#include "mission.h"
#include<string>
using namespace std;
Mission::Mission():Event(), index(0), totalCnt(0), tagForCategory(""), priority(-1), isScheduled(false)
{
    /*
    deadline not initialized yet
    */
}
Mission::Mission(string name, string tagForGraph, Time startTime, Time endTime, int duration,
                int index, int totalCnt, string tagForCategory, int priority, Time deadline)
                :Event(name, tagForGraph, startTime, endTime, duration), index(index), totalCnt(totalCnt), tagForCategory(tagForCategory), priority(priority), deadline(deadline)
{
}
double Mission::score() const
{
    int timeLeft = this->deadline - now();
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
