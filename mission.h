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
    double score() const;
public:
    Mission();
    Mission(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration,
            int index, int totalCnt, string tagForCategory, int priority, OurTime deadline);
    bool operator<(Mission toCompare) const;
    bool operator==(Mission toCompare) const;
    bool operator>(Mission toCompare) const;
    bool operator>=(Mission toCompare) const;
    bool operator<=(Mission toCompare) const;
    int getDuration() const;
};

#endif // MISSION
