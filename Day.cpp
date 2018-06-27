#include "Day.hpp"
#include <iostream>
#include <string>
using namespace std;

template<typename fixedEvent, typename mission>
Day<fixedEvent, mission>::Day()
{
    current = 0;
    duration = 0;
    for(int i = 0 ; i < TIME_SIZE ; i++)
        timeLine_type[i] = 0;
}

template<typename fixedEvent, typename mission>
int Day<fixedEvent, mission>::getDuration()
{
    duration = 0;
    
    for(int i = 0 ; i < TIME_SIZE ; i++)//find where the period starts
    {
        if(timeLine_type[i]==0)
        {
            current = i;
            duration = 1;
            break;
        }
    }
    for(int i = current ; i < TIME_SIZE ; i++)
    {
        if(timeLine_type[i]!=0)
            break;
        else
        {
            duration++;
            timeLine_type[i] = 3;
        }
    }
    
        return duration;
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::fillTime(Mission* missionToAllocate[], int numberOfMissions)
{
    if(numberOfMissions == 0)
    {
        for(int i = current ; i < current+duration ; i++)
            timeLine_type[i] = 0;
        current += duration;
    }
    else
    {
    int totalMissionTime = 0;
    for(int i = 0 ; i < numberOfMissions ; i++)
        totalMissionTime += missionToAllocate[i]->getDuration();
    int restTime = (duration-totalMissionTime)/(numberOfMissions+1);
    for(int i = 0 ; i < numberOfMissions ; i++)
    {
        int missionDurationLeft = missionToAllocate[i]->getDuration();
        int count = 0;
        for(int j = current+restTime ; j < current+duration ; j++)
        {
            if(missionDurationLeft > 0)
            {
                timeLine_mission[j].setOccurrence(missionToAllocate[i]);
                timeLine_mission[j].setStatus(1);
                timeLine_type[j] = 1;
                missionDurationLeft--;

                if(count == 0)
                {
                    Time startTime;
                    startTime.setYear(today.getYear());
                    startTime.setMonth(today.getMonth());
                    startTime.setDay(today.getDay());
                    startTime.setHour((current+restTime)/60);
                    startTime.setMinute((current+restTime)%60);
                    Time endTime;
                    endTime.setYear(today.getYear());
                    endTime.setMonth(today.getMonth());
                    endTime.setDay(today.getDay());
                    endTime.setHour((current+restTime+missionToAllocate[i]->getDuration())/60);
                    endTime.setMinute((current+restTime+missionToAllocate[i]->getDuration())%60);
                    timeLine_mission[j].getOccurrence()->setStartTime(startTime);
                    timeLine_mission[j].getOccurrence()->setEndTime(endTime);
                }
                count++;
                current++;
            }
            if(missionDurationLeft <= 0)
            {
                break;
            }
        }
    }
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::deleteNonFixedEvent()//in order to reschedule
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if(timeLine_type[i]!=2)//if status != fixedEvent
        {
            Time resetTime("000000000000");
            timeLine_mission[i].getOccurrence()->setStartTime(resetTime);
            timeLine_mission[i].getOccurrence()->setEndTime(resetTime);
            timeLine_type[i] = 0;//set status to not allocated
            timeLine_mission[i].setStatus(0);
            timeLine_mission[i].setOccurrence(nullptr);//set occurrence pointer to null
            timeLine_mission[i].setEventIsScheduled(0);
            current = 0;
        }
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::addFixedEvent(FixedEvent* fixedEventToAdd)
{
    bool available = 1;
    int start = fixedEventToAdd->getStartTime().getHour()*60+fixedEventToAdd->getStartTime().getMinute();
    for(int i = start ; i < start+fixedEventToAdd->getDuration() ; i++)
        if(timeLine_type[i] == 2)
            available = false;
    if(available == false)
        cout << "Error:the period has been occupied" <<endl;
    else
    {
        deleteNonFixedEvent();//之前排過的mission isScheduled變成0 knapsack重新丟
        for(int i = start ; i < start+fixedEventToAdd->getDuration() ; i++)
        {
            timeLine_type[i] = 2;
            timeLine_fixedEvent[i].setStatus(2);
            timeLine_fixedEvent[i].setOccurrence(fixedEventToAdd);
        }
        
    }
}

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::setStatus(int minute, int theStatus)
{
    if(timeLine_type[minute] == 1)
        timeLine_mission[minute].setStatus(theStatus);
    else if(timeLine_type[minute] == 2)
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

template<typename fixedEvent, typename mission>
void Day<fixedEvent, mission>::deleteSpecificEvent(string str)
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if(timeLine_fixedEvent[i].getOccurrence()->getName() == str)
        {
            timeLine_type[i] = 0;//set status to not allocated
            timeLine_fixedEvent[i].setStatus(0);
            timeLine_fixedEvent[i].setOccurrence(nullptr);//set occurrence pointer to null
            //how to delete event in the list?
        }
        else if(timeLine_mission[i].getOccurrence()->getName() == str)
        {
            timeLine_type[i] = 0;//set status to not allocated
            timeLine_mission[i].setStatus(0);
            timeLine_mission[i].setOccurrence(nullptr);//set occurrence pointer to null
            //how to delete mission in the list?
        }
    }
}












