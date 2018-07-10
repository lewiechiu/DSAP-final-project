#ifndef READ_LOAD_STRUCT_CPP
#define READ_LOAD_STRUCT_CPP

#include <sstream>
#include <fstream>
#include "LinkedBag.h"
#include "OurTime.hpp"
#include "event.h"
#include "FixedEvent.h"
#include "Mission.h"
using namespace std;
struct FixedEventBag
{
    LinkedBag<Event*> Bag;
//    Bag
//    void add(const Type &addItem );
//          add a Node into the LinkedBag with its <Type >item value
//    void remove(const Type& removeItem) ;
//          remove certain Node which has same <Type> item as the given one from the LinkedBag
//    bool isEmpty() const;
//          check if the LinkedBag is empty
//    bool contains(const Type& goalItem);
//          check if the LinkedBag contains the Node which has same <Type> item as the given one
//    void clearAll();
//          delete all the pointer between Nodes
//    int get_itemCount()const;

    void SaveFile(const string& FileName)
    {
        ofstream file;// declaration of file pointer named infile
        file.open(FileName, ios::out);// opens file named "filename" for input
        string Write="";

        //fixedEventName,category,startT.getTimeStr(),endT.getTimeStr(),to_string(duration)/n
        for(int i=0; i<Bag.get_itemCount(); i++)
        {
            Write+=Bag[i]->GetName();
            Write+=",";
            Write+=Bag[i]->GettagForGraph();
            Write+=",";
            Write+=Bag[i]->GetstartTime();
            Write+=",";
            Write+=Bag[i]->GetendTime();
            Write+=",";
            Write+=Bag[i]->GetDuration();
            Write+="\n";
        }
        file<<Write;
        file.close();//closes file
    }

    void LoadFile(const string& FileName)
    {
        ifstream file;// declaration of file pointer named infile
        file.open(FileName, ios::in);// opens file named "filename" for input
        string Read="";
        Event* newFE;
        string name="",tagForGraph="", starttime="", endtime="", duration="";
        //fixedEventName,category,startT.getTimeStr(),endT.getTimeStr(),to_string(duration)/n
        if(file.is_open())
            while(getline(file, Read))
            {
                size_t comma =  Read.find(",");
                name = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                tagForGraph = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                starttime = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                endtime = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find("\n");
                duration = Read.substr(0,comma);
                Read = Read.substr(comma+1);
                OurTime StartT(starttime);
                OurTime EndT(endtime);

                int duration_int=0;
                stringstream ss(duration);
                ss>>duration_int;
                newFE = new FixedEvent(name, tagForGraph, StartT, EndT, duration_int);
                this->Bag.add(newFE);
                //string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration);
            }
        file.close();//closes file
    }
};

struct MissionBag
{
    LinkedBag<Event*> Bag;
    //    Bag
    //    void add(const Type &addItem );
    //          add a Node into the LinkedBag with its <Type >item value
    //    void remove(const Type& removeItem) ;
    //          remove certain Node which has same <Type> item as the given one from the LinkedBag
    //    bool isEmpty() const;
    //          check if the LinkedBag is empty
    //    bool contains(const Type& goalItem);
    //          check if the LinkedBag contains the Node which has same <Type> item as the given one
    //    void clearAll();
    //          delete all the pointer between Nodes
    //    int get_itemCount()const;

    void SaveFile(const string& FileName)
    {
        ofstream file;// declaration of file pointer named infile
        file.open(FileName, ios::out);// opens file named "filename" for input
        string Write="";

        //MissionName,category,startT.getTimeStr(),endT.getTimeStr(),to_string(duration), isdone, index, totalCnt, tagCategort, priority, deadline, isSchedule
        for(int i=0; i<Bag.get_itemCount(); i++)
        {
            Write+=Bag[i]->GetName();
            Write+=",";
            Write+=Bag[i]->GettagForGraph();
            Write+=",";
            Write+=Bag[i]->GetstartTime();
            Write+=",";
            Write+=Bag[i]->GetendTime();
            Write+=",";
            Write+=Bag[i]->GetDuration();
            Write+=",";
            if(Bag[i]->GetMisDone())
                Write+="1";
            else
                Write+="0";
            Write+=",";
            Write+=Bag[i]->GetMindex();
            Write+=",";
            Write+=Bag[i]->GetMtotalCnt();
            Write+=",";
            Write+=Bag[i]->GetMtagCategory();
            Write+=",";
            Write+=Bag[i]->GetMpriority();
            Write+=",";
            Write+=Bag[i]->GetMdeadline();
            Write+=",";
            if(Bag[i]->GetMisScheduled())
                Write+="1";
            else
                Write+="0";
            Write+="\n";
        }
        file<<Write;
        file.close();//closes file
    }

    void LoadFile(const string& FileName, bool ISDONE)
    {
        ifstream file;// declaration of file pointer named infile
        file.open(FileName, ios::in);// opens file named "filename" for input
        string Read="";

        string name="",tagForGraph="", starttime="", endtime="", duration="", isDone="", index="", totalCnt="", tagCategory="", priority="", deadline="", isSchedule="";

//        File format
//        MissionName,category,startT.getTimeStr(),endT.getTimeStr(),to_string(duration), isdone, index, totalCnt, tagCategort, priority, deadline, isSchedule\n


        if(file.is_open())
            while(getline(file, Read))
            {
                size_t comma =  Read.find(",");
                name = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                tagForGraph = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                starttime = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                endtime = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                duration = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                isDone = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                index = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                totalCnt = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                tagCategory = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                priority = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find(",");
                deadline = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                comma =  Read.find("\n");
                isSchedule = Read.substr(0,comma);
                Read = Read.substr(comma+1);

                bool isDone_b;
                bool isScheduled_b;
                if(isDone=="1")
                    isDone_b=true;
                else
                    isDone_b = false;
                if(isSchedule=="1")
                    isScheduled_b = true;
                else
                    isScheduled_b = false;
                OurTime StartT(starttime);
                OurTime EndT(endtime);
                OurTime DeadT(deadline);

                int duration_int=0,index_int=0,totalCnt_int=0, priority_int=0;

                stringstream ss(duration);
                ss>>duration_int;
                ss.clear();
                ss.str(index);
                ss>>index_int;
                ss.clear();
                ss.str(totalCnt);
                ss>>totalCnt_int;
                ss.clear();
                ss.str(priority);
                ss>>priority_int;
                Event* newM;
                newM = new Mission(name, tagForGraph, StartT, EndT, duration_int, index_int, totalCnt_int, tagCategory,
                                   priority_int, DeadT, isDone_b, isScheduled_b);

                //you can pick which kind of bag you want either is a isDone one or a isNotDone one
                if(ISDONE==isDone_b)
                    this->Bag.add(newM);
            }

        file.close();//closes file
    }
};

#endif
