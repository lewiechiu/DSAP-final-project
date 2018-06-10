#include "Day.hpp"
#include <iostream>
#include <string>
using namespace std;

template<typename fixedEvent, typename mission>
Day<fixedEvent, mission>::Day()
{
    current = -1;
    duration = 0;
    for(int i = 0 ; i < TIME_SIZE ; i++)
        timeLine_type[i] = 0;
}

template<typename fixedEvent, typename mission>
int Day<fixedEvent, mission>::getDuration()
{
    int startTime = -1;
    duration = 0;
    
    for(int i = 0 ; i < TIME_SIZE ; i++)//find where the period starts
    {
        if(timeLine_type[i]==0)
        {
            startTime = i;
            break;
        }
    }
    for(int i = startTime ; i < TIME_SIZE ; i++)
    {
        if(timeLine_type[i]!=0)
            break;
        else
        {
            duration++;
            timeLine_type[i] = 3;
            if(i == startTime)
                current = i;
        }
    }
    if(duration >= 30)
        return duration;
    else
    {
        for(int i = startTime ; i < startTime+duration ; i++)
            timeLine_type[i] = 4;//4:duration less than 30 minutes
        current = -1;
        return 0;
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::fillTime(Mission* missionToAllocate[], int numberOfMissions)
{
    for(int i = 0 ; i < numberOfMissions ; i++)
    {
        int missionDurationLeft = missionToAllocate[i].duration;
        for(int j = current ; j < current+duration ; j++)
        {
            if(missionDurationLeft > 0)
            {
                timeLine_mission[j] = missionToAllocate[i];
                missionDurationLeft--;
                current++;
            }
            if(missionDurationLeft <= 0)
            {
                break;
            }
        }
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::deleteNonFixedEvent()
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if(timeLine_type[i]==1)//if status == mission
        {
            timeLine_type[i] = 0;//set status to not allocated
            timeLine_mission[i].setStatus(0);
            timeLine_mission[i].setOccurrence(nullptr);//set occurrence pointer to null
        }
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::setStatus(int minute, int theStatus)
{
    if(timeLine_type[minute] == 1)
        timeLine_mission[minute].setStatus(theStatus);
    if(timeLine_type[minute] == 2)
        timeLine_fixedEvent[minute].setStatus(theStatus);
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::setOccurrence_event(int minute, fixedEvent *anOccurrence)
{
    timeLine_fixedEvent[minute].setOccurrence(anOccurrence);
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::setOccurrence_mission(int minute, mission *anOccurrence)
{
    timeLine_mission[minute].setOccurrence(anOccurrence);
}

template<typename fixedEvent, typename mission>
int Day<fixedEvent, mission>::getStatus(int minute)
{
    return timeLine_type[minute];
}

template<typename fixedEvent, typename mission>
fixedEvent* Day<fixedEvent, mission>::getOccurrence_event(int minute)
{
    return timeLine_fixedEvent[minute].getOccurrence();
}

template<typename fixedEvent, typename mission>
mission* Day<fixedEvent, mission>::getOccurrence_mission(int minute)
{
    return timeLine_mission[minute].getOccurrence();
}













