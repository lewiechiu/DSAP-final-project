#ifndef Day_hpp
#define Day_hpp
#include "timeNode.hpp"
#include <string>
using namespace std;
#define TIME_SIZE 1440
#include "OurTime.hpp"
#include "mission.h"
#include "FixedEvent.h"

class Day
{
private:
    OurTime today;
    int timeLine_type[TIME_SIZE];//0:empty,1:mission,2:fixed event,3:checked
    timeNode timeLine[TIME_SIZE];
    int current;
    int duration;
public:
    Day();
    Day(OurTime& TD);
    int getDuration();//return available time duration(the current period) in minutes
    void fillTime(Event* missionToAllocate[], int numberOfMissions);//fill available time with missions passed by knapsack
    void addFixedEvent(Event* fixedEventToAdd);
    void RestoreMission(Event* MissionToAdd);
    void deleteNonFixedEvent();//when reallocating
    void setStatus(int minute,int theStatus);//set the status of the minute
    void setOccurrence_event(int minute, FixedEvent* anOccurrence);//set the occurrence of the minute
    void setOccurrence_mission(int minute, Mission* anOccurrence);
    int getStatus(int minute);//get the status of the minute
    Event* getOccurrence_event(int minute);//get the occurrence of the minute
    void deleteSpecificEvent(string str,int parts,bool complete);
    void showToday();
    string getToday()const;
    void unCheck();
};

#endif /* Day_hpp */
