
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
    virtual void setStartTime(OurTime& ST);
    virtual void setEndTime(OurTime& ET);
    virtual void setIsSchedule(bool isS);
    virtual double score()const;
    OurTime getStartTime()const;
    OurTime getEndTime()const;
    int getDuration()const;
    void setIsDone(bool isD);


};
#endif //EVENT

