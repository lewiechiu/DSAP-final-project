#include <iostream>
#include <string>
#include <time.h>
#include "OurTime.hpp"
#include "mission.h"
#include "fixedevent.h"
using namespace std;


int main()
{

	cout << "press 1 for showing the view eventlist" << endl;

	cout << "press 4 for showing the dash board" << endl;

	cout << "press  for exit" << endl;
	int oper;
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




	cin >> oper;

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
			cout << "press 3 for finishing an event" << endl;
			cout << "press 5 for event deletion" << endl;
			cout << "press 2 for adding a new event" << endl;
			cin >> oper;
			if(oper == 2)
			{
				Mission a;
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

					cout << "Please type fixedEventName" << endl;
					cin >> fixedEventName;
					cout << "Please type startTime" << endl;
					cout << "in the form of: \n 201806301125 " << endl;
					cin >> startTime;
					OurTime start;
					start.setYear(stoi(startTime.substr(0,4)));
					cout << "Please type end time or deadline" << endl;
					cin >> startTime;
					OurTime endT(startTime);
					cin >> endTime;

					/*
					Now we would have a fixed event
					We need just passing the event into the Day class
					The Day class might need some function to help making the time occupied by fixed event be unavailable to use

					*/
				}
				else if(oper==2)
				{
					string EventName;
					string DDL;
					int priority;
					cout << "Please type EventName" << endl;
					cin >> EventName;
					//	total time to complete the mission
					cout << "Please type Deadline time in the following format:" << endl;
					//	longest period of continuous doing
					cout << "2016/06/30 19:00" << endl;
					cin >> DDL;
					cout << "please type in priority" << endl;
					cout << "with least important:1 to utmost important:10" << endl;
					cin >> priority;


					/*
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
	return 0;
}
