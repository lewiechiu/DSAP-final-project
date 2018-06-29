#ifndef Day_hpp
#define Day_hpp
#include "timeNode.hpp"
#include <string>
using namespace std;
#define TIME_SIZE 1440
#include "OurTime.hpp"
#include "mission.h"
#include "FixedEvent.h"

template<typename fixedEvent, typename mission>
class Day
{
private:
    OurTime today;
    int timeLine_type[TIME_SIZE];//0:empty,1:mission,2:fixed event,3:checked
    timeNode<fixedEvent> timeLine_fixedEvent[TIME_SIZE];
    timeNode<mission> timeLine_mission[TIME_SIZE];
    int current;
    int duration;
public:
    Day();
    int getDuration();//return available time duration(the current period) in minutes
    void fillTime(Mission* missionToAllocate[], int numberOfMissions);//fill available time with missions passed by knapsack 
    void addFixedEvent(FixedEvent* fixedEventToAdd);
    void deleteNonFixedEvent();//when reallocating
    void setStatus(int minute,int theStatus);//set the status of the minute
    void setOccurrence_event(int minute, fixedEvent* anOccurrence);//set the occurrence of the minute
    void setOccurrence_mission(int minute, mission* anOccurrence);
    int getStatus(int minute);//get the status of the minute
    fixedEvent* getOccurrence_event(int minute);//get the occurrence of the minute
    mission* getOccurrence_mission(int minute);
    void deleteSpecificEvent(string str);
};

#endif /* Day_hpp */
