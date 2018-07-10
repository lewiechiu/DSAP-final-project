#ifndef mission_h
#define mission_h
#include<string>
#include "event.h"
using namespace std;

class Mission : public Event
{
private:
                            //take "Calculus 1/5" for example
    int index;              //ex: 1
    int totalCnt;           //ex: 5
    string tagForCategory;  //ex: Calculus
    int priority; //0-10, 0 indicates that the mission can be ignored if needed
    OurTime deadline;
    bool isScheduled;

public:
    Mission();
    Mission(string name,string tagForGraph,string tagForC,int index,int totalCnt,int priority,OurTime deadline,int duration);
    Mission(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration,
            int index, int totalCnt, string tagForCategory, int priority, OurTime deadline);
    Mission(string name,string tagForGraph,OurTime StartT,OurTime EndT,int duration_int,int index_int,
            int totalCnt_int,string tagCategory,int priroty_int,OurTime DeadT,bool isDone_b,bool isScheduled_b);
    bool operator<(Mission toCompare) const;
    bool operator==(Mission toCompare) const;
    bool operator>(Mission toCompare) const;
    bool operator>=(Mission toCompare) const;
    bool operator<=(Mission toCompare) const;
    int getDuration() const;
    bool GetMisDone()const;
    string GetMindex()const;
    string GetMtotalCnt()const;
    string GetMpriority()const;
    string GetMdeadline()const;
    bool GetMisScheduled()const;
    string GetMtagCategory()const;
    void setStartTime(OurTime& ST);
    void setEndTime(OurTime& ET);
    void setIsSchedule(bool isS);
    double score() const;
};

#endif // MISSION
