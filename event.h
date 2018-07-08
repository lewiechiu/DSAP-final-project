
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
    string GetName()const;
    string GettagForGraph()const;
    string GetstartTime()const;
    string GetendTime()const;
    string GetDuration() const;
    virtual bool GetMisDone()const;
    virtual string GetMindex()const;
    virtual string GetMtotalCnt()const;
    virtual string GetMpriority()const;
    virtual string GetMdeadline()const;
    virtual bool GetMisScheduled()const;
    virtual string GetMtagCategory()const;

};
#endif //EVENT



/*
Write+=Bag[i]->GetName();
            Write+=",";
            Write+=Bag[i]->GettagForGraph();
            Write+=",";
            Write+=Bag[i]->GetstartTime();
            Write+=",";
            Write+=Bag[i]->GetendTime();
            Write+=",";
            Write+=Bag[i]->GetDuration();
*/
