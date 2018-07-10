#include <iostream>
#include <string>
#include <time.h>
#include "OurTime.hpp"
#include "mission.h"
#include "fixedevent.h"

#include <SFML/Graphics.hpp>
#include "LinkedBag.h"
#include "Knapscak.h"
#include <fstream>
#include <math.h>
#include "Read_Load_Struct.cpp"
#include "Day.hpp"


#define weeks 10
#define aweek 7
using namespace std;





int main()
{
    int oper;
	FixedEventBag FEBag;
	MissionBag MBag,MFBag;
	MissionBag Done;
	OurTime today;
    OurTime start("201807080000");
	today.Current();
    today.setHour(0);
	today.setMinute(0);
    Day *year2018[weeks][aweek];
    Day *week[7];


    string MissionLocation = "Mission.txt";
    string MissionFinishedLocation = "MF.txt";
    string FixedLocation = "Fixed.txt";
    MBag.LoadFile(MissionLocation,false);
    MFBag.LoadFile(MissionFinishedLocation,true);
    FEBag.LoadFile(FixedLocation);

    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            year2018[i][j] = new Day(start);
            start = start + 1440;
        }
    }
    for(int i=0;i<aweek;i++)
    {
        week[i] = new Day(today);
        today = today +1440;
    }
    cout << "done initializing year2018" << endl;
    cout << "going into adding FE into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<FEBag.Bag.get_itemCount();k++)
            {
                string FEtime = FEBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(FEtime==cur)
                    year2018[i][j]->addFixedEvent(FEBag.Bag[k]);
                else
                    continue;
            }
            year2018[i][j]->showToday();
        }
    }
    cout << "finish adding FE into year2018" << endl;
    cout << "start adding mission into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<MBag.Bag.get_itemCount();k++)
            {
                string Mtime = MBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(Mtime==cur)
                    year2018[i][j]->RestoreMission(MBag.Bag[k]);
                else
                    continue;
            }
            year2018[i][j]->showToday();
        }
    }
    cout << "finish adding Mission into year2018" << endl;
    for(int i=0;i<FEBag.Bag.get_itemCount();i++)
    {
        week[0]->addFixedEvent(FEBag.Bag[i]);
    }
    for(int i=0;i<MBag.Bag.get_itemCount();i++)
    {
        week[0]->RestoreMission(MBag.Bag[i]);
    }

    while(1)
    {

	cout << "press 1 for showing the view eventlist" << endl;

	cout << "press 4 for showing the dash board" << endl;

	cout << "press  for exit" << endl;
    cin >> oper;
	//201804231934
/*

	Initialize an linklist of week pointer like 52 week
	With each of it being a pointer pointing to 7 days (an array)
	I have to initalize everyday and restart


	readin the event txt that includes info
	new mission or fixed event txt according to the infor
	ptr to the item i just create

	get start time and put it into the day


	Offline method would be right before closing

	mission name cannot be the same
*/






//					view past calendar
//						display the past calendar

	if(oper==1)
	{

		/*
		view list should be able to display past and current and future
		First display current week


		We should be able to display what is in a day with view point of a week
		on a certain time period
		e.g.
		2018/06/01
			Study Calculus xx hour yy minute from 9:00 to 11:00
			Play hoverboard xx hour yy minute from 20:00 to 23:05
		2018/06/02
			... and so on
		The schedule here should be able to display in chronological order
		*/
            cout << "press 1 for viewing what happened today" << endl;
            cout << "press 2 for adding a new Fixed event / Mission" << endl;
			cout << "press 3 for finishing a mission" << endl;
			cout << "press 4 for deleting a fixed event / Mission" << endl;
			cin >> oper;
			if(oper == 2)
			{
				/*
				Rule of thumbs to keep in mind:
				1. We do not determine whether the mission needs more time or not
				2. Once the event within three days have been made, no further changes should be made.
				2-1 Unless it is significantly import and of great urgency
				2-2 If we encounter running out of time, let the user decide what he/she should do either
					1. sleep less
					2. Abandon unimportant missions


				First, we require the uncompleted mission sorted list to give us a bag of mission.
				From the bag of mission we can
				*/
				cout << "press 1 for adding a fixed event" << endl;
				cout << "press 2 for adding a flexible mission" << endl;
				cin >> oper;
				if(oper==1)
				{
					string fixedEventName;
					string startTime;
					string endTime;
					string category;
					int duration;

					cout << "Please type fixedEventName" << endl;
					cin >> fixedEventName;

					cout << "Please type startTime in the form of: \n201806301125 " << endl;
					cin >> startTime;
					OurTime startT(startTime);

					cout << "end Time please keep this event in the same day" << endl;
					cin >> endTime;

					cout << "category" << endl;
					cin >> category;
					OurTime endT(endTime);
					duration = endT - startT;
					FixedEvent *one = new FixedEvent(fixedEventName,category,startT,endT,duration);
                    string moveto = startTime.substr(0,8);
                    for(int i=0;i<weeks;i++)
                    {
                        for(int j=0;j<aweek;j++)
                        {
                            string TD = year2018[i][j]->getToday().substr(0,8);
                            if(TD==moveto)
                            {
                                year2018[i][j]->addFixedEvent(one);
                                cout << TD << endl;
                            }

                        }
                    }
                    FEBag.Bag.add(one);
                    FEBag.SaveFile(FixedLocation);

					/*
					Now we would have a fixed event
					We need just passing the event into the Day class
					The Day class might need some function to help making the time occupied by fixed event be unavailable to use

					*/
				}
				else if(oper==2)
				{
					string MissionName;
					string Deadline;
					string StartTime;
					string category;
					string graph;
					int priority;
					double duration;
					double thresh;
					cout << "Please type mission Name" << endl;
					cin >> MissionName;
					//	total time to complete the mission
					cout << "Enter how long will you need to finish it (in minute) " << endl;
					cin >> duration;

					cout << "Maximum continuous minutes" << endl;
					cin >> thresh;

                    cout << "DeadLine?" << endl;
					cin >> Deadline;
					OurTime ddl(Deadline);

					double parts = ceil(duration/thresh);
					cout << "please type in priority\nwith least important:1 to utmost important:10" << endl;
					cin >> priority;

                    cout << "which type do you want this to graph???" << endl;
                    cin >> graph;

					cout << "category" << endl;
					cin >> category;
					for(int i=0;i<parts;i++)
                    {
                        Mission *a;
                        if(thresh < duration)
                            a = new Mission(MissionName,graph,category,i,parts,priority,ddl,thresh);
                        else
                            a = new Mission(MissionName,graph,category,i,parts,priority,ddl,duration);
                        MBag.Bag.add(a);
                        duration -= thresh;
                    }

                    OurTime doodle;
                    doodle.Current();
                    string cur = doodle.getTimeStr().substr(0,8);
                    int weekN,dayN;
                    for(int i=0;i<weeks;i++)
                    {
                        for(int j=0;j<aweek;j++)
                        {
                            string hello = year2018[i][j]->getToday().substr(0,8);
                            if(hello==cur)
                            {
                                weekN = i;
                                dayN = j;
                                break;
                            }
                            else
                                continue;
                        }
                    }
                    for(int i=weekN;i<weeks;i++)
                    {
                        for(int j=dayN;j<aweek;j++)
                        {
                            year2018[i][j]->deleteNonFixedEvent();
                        }
                    }

                    for(int i=weekN;i<weeks;i++)
                    {
                        for(int j=dayN;j<aweek;j++)
                        {
                            cout << "i:" << i << " j: " << j << endl;
                            year2018[i][j]->unCheck();
                            while(1)
                            {
                                int freeTime = year2018[i][j]->getDuration();
                                if(freeTime==-1)
                                    break;
//                                cout << "freetime: " << freeTime << endl;
                                MissionBag* chosen = KnapSack(MBag,freeTime);
                                cout <<"chosen item count: " <<  chosen->Bag.get_itemCount() << endl;
                                Event** fillin = new Event*[chosen->Bag.get_itemCount()];
                                for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                {
                                    fillin[k] = chosen->Bag[k];
                                }
//                                cout << "start filling Time" << endl;
                                year2018[i][j]->fillTime(fillin,chosen->Bag.get_itemCount());
                                year2018[i][j]->showToday();
//                                cout << "done filling Time" << endl;
//                                cout << "start updating Time" << endl;
                                for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                {
                                    MBag.Bag.remove(fillin[k]->GetName(),stoi(fillin[k]->GetMindex()),stoi(fillin[k]->GetMtotalCnt()));
                                    MBag.Bag.add(fillin[k]);
                                }
//                                cout << "done updating MBag" << endl;

                            }
                            year2018[i][j]->unCheck();
                        }
                    }

                    MBag.Bag.printBag();

                    MBag.SaveFile(MissionLocation);

                    /*
                        When I finish creating a or multiple series of mission
                        I need to put it into the mission bag
                        after that give it to knapsack and then it would return to me an array
                        after that

						Now that I can create a new flexible mission variable.
						We need to gain the access of the Uncompleted mission list
						We pass the list into
						Acquire how much time is available in a single day.
						Pass that amount, and the uncompleted mission list into the knapsack algorithm
						The algorithm should return an array containing
							1. Mission name
							2. Mission duration
						That array would be passed into the day class and be inserted.
					*/
				}
				else
					cout << "Enter something that is readable FOOL!!" << endl;
						/*
							add a mission event
								clear out all the mission
								add a new mission
								recalculate
								put it back into the day list
							add a fixed event
								if there is an overlapping
									not allowed

								clear out al the mission
								insert fixed event
								recalculate and then insert

							viewing style would be weekly
						*/
			}
			else if (oper == 1)
            {
                OurTime sony;
                sony.Current();
                string cur = sony.getTimeStr().substr(0,8);
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==cur)
                        {
                            year2018[i][j]->showToday();
                            break;
                        }
                        else
                            continue;
                    }
                }
            }
            else if (oper == 3)
            {
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                        year2018[i][j]->showToday();
                }
                cout << "enter event date" << endl;
                cout << "e.g. 20180720" << endl;
                string date;
                cin >> date;
                cout << "enter mission name within that day" << endl;
                int weekN,dayN;
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==date)
                        {
                            year2018[i][j]->showToday();
                            weekN = i;
                            dayN = j;
                            break;
                        }
                        else
                            continue;
                    }
                }
                string missionName;
                cin >> missionName;
                cout << "enter which part of the mission" << endl;
                int parr = 0;
                cin >> parr;
                year2018[weekN][dayN]->deleteSpecificEvent(missionName,parr,true);
                MBag.SaveFile(MissionLocation);
            }
            else if (oper == 4)
            {
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                        year2018[i][j]->showToday();
                }
                cout << "enter event date" << endl;
                cout << "e.g. 20180720" << endl;
                string date;
                cin >> date;
                cout << "enter mission / Fixed event name within that day" << endl;
                int weekN,dayN;
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==date)
                        {
                            year2018[i][j]->showToday();
                            weekN = i;
                            dayN = j;
                            break;
                        }
                        else
                            continue;
                    }
                }
                cout << "press 1 to delete mission" << endl;
                cout << "press 2 to delete Fixed Event" << endl;
                int FEorM=0;
                cin >> FEorM;
                if(FEorM==1)
                {
                    cout << "enter mission name within that day" << endl;
                    string missionName;
                    cin >> missionName;
                    cout << "enter which part of the mission" << endl;
                    int parr = 0;
                    cin >> parr;
                    year2018[weekN][dayN]->deleteSpecificEvent(missionName,parr,false);
                    MBag.SaveFile(MissionLocation);
                }
                else
                {
                    cout << "enter Fixed event name within that day" << endl;
                    string FixedName;
                    cin >> FixedName;
                    year2018[weekN][dayN]->deleteSpecificEvent(FixedName,-1,false);
                    FEBag.Bag.remove(FixedName);
                    FEBag.SaveFile(FixedLocation);
                }
            }
	}
	else if(oper==2)
	{

	}
	else if(oper==3)
	{

	}
	else if(oper==4)
	{
		/*
		We should be able to display a list showing the total amount of time contributed to each tag
		We may need some for loops to add up all of the time we used in the past week.
		Showing in the form of:
			Studying 5 hr 42 min ->20%
			Riding fixed gear 20 hr 30 min ->50%
			Facebook 3 hr 20 min ->30%
		*/
	}
	else
		cout << "Enter something that is readable FOOL!!" << endl;
    }

	return 0;
}
