#include "Day.hpp"
#include "timeNode.hpp"
#include "mission.h"
#include <iostream>
#include <string>
#include <typeinfo>
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
    this->today.setTimeStr();
}

int Day::getDuration()
{
    duration = 0;

    for(int i = current ; i < TIME_SIZE ; i++)//find where the period starts
    {
        if((timeLine_type[i]==0))
        {
            current = i;
            cout << "current " << current << endl;
            break;
        }
        if(i==1439)
            return -1;
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
    cout << "free time length: "<< duration << endl;
        return duration;
}


void Day::fillTime(Event* missionToAllocate[], int numberOfMissions)
{
    if(numberOfMissions == 0)
    {
        return ;
    }
    else
    {
        int totalMissionTime = 0;
        for(int i = 0 ; i < numberOfMissions ; i++)
        {
            if(missionToAllocate[i]->GetMisScheduled())
                continue;
            totalMissionTime += missionToAllocate[i]->getDuration();
        }

        int restTime = (duration-totalMissionTime)/(numberOfMissions+1);
        for(int i = 0 ; i < numberOfMissions ; i++)
        {
            if(missionToAllocate[i]->GetMisScheduled())
                continue;
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
                        startTime.setTimeStr();
                        OurTime endTime;
                        endTime.setYear(today.getYear());
                        endTime.setMonth(today.getMonth());
                        endTime.setDay(today.getDay());
                        endTime.setHour((current+restTime+missionToAllocate[i]->getDuration())/60);
                        endTime.setMinute((current+restTime+missionToAllocate[i]->getDuration())%60);
                        endTime.setTimeStr();
                        timeLine[j].getOccurrence()->setStartTime(startTime);
                        timeLine[j].getOccurrence()->setEndTime(endTime);
                        missionToAllocate[i]->setStartTime(startTime);
                        missionToAllocate[i]->setEndTime(endTime);
                        missionToAllocate[i]->setIsSchedule(true);
                        missionToAllocate[i]->setIsDone(false);
                    }
                    count++;
                    current++;
                }
                if(missionDurationLeft <= 0)
                    break;
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


void Day::addFixedEvent(Event* fixedEventToAdd)
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

void Day::RestoreMission(Event* MissionToAdd)
{
    int start = MissionToAdd->getStartTime().getHour()*60+MissionToAdd->getStartTime().getMinute();
    for(int i = start ; i < start+MissionToAdd->getDuration() ; i++)
    {
        timeLine_type[i] = 2;
        timeLine[i].setStatus(2);
        timeLine[i].setOccurrence(MissionToAdd);
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

void Day::deleteSpecificEvent(string str,int parts=-1,bool complete = false)
{
    for(int i = 0 ; i < TIME_SIZE ; i++)
    {
        if(parts!=-1)
        {
            if(dynamic_cast<Mission*>(timeLine[i].getOccurrence())==nullptr)
                continue;
            if((timeLine[i].getOccurrence()->GetName() == str)&&
                (stoi(timeLine[i].getOccurrence()->GetMindex())==parts))
            {
                if(complete)
                    timeLine[i].getOccurrence()->setIsDone(true);
                timeLine_type[i] = 0;//set status to not allocated
                timeLine[i].setStatus(0);
                timeLine[i].setOccurrence(nullptr);//set occurrence pointer to null

            }
        }
        else
        {
            if(dynamic_cast<FixedEvent*>(timeLine[i].getOccurrence())==nullptr)
                continue;
            if(timeLine[i].getOccurrence()->GetName()== str)
            {
                timeLine_type[i] = 0;//set status to not allocated
                timeLine[i].setStatus(0);
                timeLine[i].setOccurrence(nullptr);//set occurrence pointer to null
            }
        }

    }
}
void Day::showToday()
{
    cout << today.getYear() << "/" <<today.getMonth() << "/" << today.getDay() << endl;
    for(int i=0;i<TIME_SIZE;i++)
    {
        if(timeLine[i].getOccurrence() != nullptr)
        {
            if(dynamic_cast<Mission*>(timeLine[i].getOccurrence())!=nullptr)
            {
                cout << timeLine[i].getOccurrence()->GetName() << "part:";
                cout << timeLine[i].getOccurrence()->GetMindex() << " total:";
                cout << timeLine[i].getOccurrence()->GetMtotalCnt() << "  \n   S:";
                cout << timeLine[i].getOccurrence()->GetstartTime() << endl;
                cout << "   E:" << timeLine[i].getOccurrence()->GetendTime() << endl;
            }
            else
            {
                cout << timeLine[i].getOccurrence()->GetName() << "  \n   S:";
                cout << timeLine[i].getOccurrence()->GetstartTime() << endl;
                cout << "   E:" << timeLine[i].getOccurrence()->GetendTime() << endl;
            }
            i += timeLine[i].getOccurrence()->getDuration() -1;
        }
    }
}

string Day:: getToday() const
{
    return this->today.getTimeStr();
}

void Day::unCheck()
{
    for(int i=0;i<TIME_SIZE;i++)
    {
        if((timeLine_type[i]!=1)&&(timeLine_type[i]!=2))
            timeLine_type[i]==0;
    }
}











