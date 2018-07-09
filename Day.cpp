#include "Day.hpp"
#include "timeNode.hpp"
#include <iostream>
#include <string>
using namespace std;


Day::Day()
{
    current = 0;
    duration = 0;
    for(int i = 0 ; i < TIME_SIZE ; i++)
        timeLine_type[i] = 0;
}

Day::Day(OurTime& TD)
{
    current = 0;
    duration = 0;
    for(int i = 0 ; i < TIME_SIZE ; i++)
        timeLine_type[i] = 0;
    this->today = TD;
}

int Day::getDuration()
{
    duration = 0;

    for(int i = 0 ; i < TIME_SIZE ; i++)//find where the period starts
    {
        if(timeLine_type[i]==0)
        {
            current = i;
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


void Day::fillTime(Mission* missionToAllocate[], int numberOfMissions)
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
                timeLine[j].setOccurrence(missionToAllocate[i]);
                timeLine[j].setStatus(1);
                timeLine_type[j] = 1;
                missionDurationLeft--;

                if(count == 0)
                {
                    OurTime startTime;
                    startTime.setYear(today.getYear());
                    startTime.setMonth(today.getMonth());
                    startTime.setDay(today.getDay());
                    startTime.setHour((current+restTime)/60);
                    startTime.setMinute((current+restTime)%60);
                    OurTime endTime;
                    endTime.setYear(today.getYear());
                    endTime.setMonth(today.getMonth());
                    endTime.setDay(today.getDay());
                    endTime.setHour((current+restTime+missionToAllocate[i]->getDuration())/60);
                    endTime.setMinute((current+restTime+missionToAllocate[i]->getDuration())%60);
                    timeLine[j].getOccurrence()->setStartTime(startTime);
                    timeLine[j].getOccurrence()->setEndTime(endTime);
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

void Day::deleteNonFixedEvent()//in order to reschedule
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if((timeLine_type[i]!=2)&&(timeLine_type[i]!=0))//if status != fixedEvent
        {
            OurTime resetTime("000000000000");
            timeLine[i].getOccurrence()->setStartTime(resetTime);
            timeLine[i].getOccurrence()->setEndTime(resetTime);
            timeLine_type[i] = 0;//set status to not allocated
            timeLine[i].setStatus(0);
            timeLine[i].setOccurrence(nullptr);//set occurrence pointer to null
            timeLine[i].setEventIsScheduled(0);
            current = 0;
        }
    }
}


void Day::addFixedEvent(FixedEvent* fixedEventToAdd)
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
        cout << fixedEventToAdd->getDuration() << endl;
        deleteNonFixedEvent();//之前排過的mission isScheduled變成0 knapsack重新丟
        for(int i = start ; i < start+fixedEventToAdd->getDuration() ; i++)
        {
            timeLine_type[i] = 2;
            timeLine[i].setStatus(2);
            timeLine[i].setOccurrence(fixedEventToAdd);
        }

    }
}


void Day::setStatus(int minute, int theStatus)
{
    if(timeLine_type[minute] == 1)
        timeLine[minute].setStatus(theStatus);
    else if(timeLine_type[minute] == 2)
        timeLine[minute].setStatus(theStatus);
}


void Day::setOccurrence_event(int minute, FixedEvent *anOccurrence)
{
    timeLine[minute].setOccurrence(anOccurrence);
}


void Day::setOccurrence_mission(int minute, Mission *anOccurrence)
{
    timeLine[minute].setOccurrence(anOccurrence);
}


int Day::getStatus(int minute)
{
    return timeLine_type[minute];
}


Event* Day::getOccurrence_event(int minute)
{
    return timeLine[minute].getOccurrence();
}

void Day::deleteSpecificEvent(string str)
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if(timeLine[i].getOccurrence()->GetName() == str)
        {
            timeLine_type[i] = 0;//set status to not allocated
            timeLine[i].setStatus(0);
            timeLine[i].setOccurrence(nullptr);//set occurrence pointer to null
            //how to delete event in the list?
        }
        else if(timeLine[i].getOccurrence()->GetName() == str)
        {
            timeLine_type[i] = 0;//set status to not allocated
            timeLine[i].setStatus(0);
            timeLine[i].setOccurrence(nullptr);//set occurrence pointer to null
            //how to delete mission in the list?
        }
    }
}
void Day::showToday()
{
    for(int i=0;i<TIME_SIZE;i++)
    {
        if(timeLine[i].getOccurrence() != nullptr)
        {
            cout << timeLine[i].getOccurrence()->GetName() << "  " << i << endl;
        }
    }
}











