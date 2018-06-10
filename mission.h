#ifndef MISSION
#define MISSION
#include<string>
#include "event.h"
#include "Time.h"
using namespace std;

class Mission:public Event
{
private:
                            //take "Calculus 1/5" for example
    int index;              //ex: 1
    int totalCnt;           //ex: 5
    string tagForCategory;  //ex: Calculus
    int priority; //0-10, 0 indicates that the mission can be ignored if needed
    Time deadline;
    bool isScheduled;
    double score() const;
public:
    Mission();
    Mission(string name, string tagForGraph, Time startTime, Time endTime, int duration,
            int index, int totalCnt, string tagForCategory, int priority, Time deadline);
    bool operator<(Mission toCompare) const;
    bool operator==(Mission toCompare) const;
    bool operator>(Mission toCompare) const;
    bool operator>=(Mission toCompare) const;
    bool operator<=(Mission toCompare) const;
};
#endif // MISSION
