//
//  Bags&List.hpp
//  SFML
//
//  Created by Nicksome on 2018/7/12.
//  Copyright © 2018 Nicksome. All rights reserved.
//

#ifndef Bags_List_hpp
#define Bags_List_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include "LinkedBag.h"
#include "OurTime.hpp"
#include "event.h"
#include "FixedEvent.h"
#include "mission.h"
#include "Hash_Table.hpp"
using namespace std;

class List
{
public:
    List();
    List(const List& other);
    void Table2List(Hash_Table& HT);
    void print()const;
    ~List();
    void add(Hash_Node newNode);
    int getCount()const;
    Hash_Node* operator[](int index);
    
protected:
    int Count;
    Hash_Node* list[101];
    const static int CAPACITY=101;
    void quickSort(Hash_Node* arr[], int left, int right);
};


struct FixedEventBag
{
    ~FixedEventBag()
    {
        for(int i=0; i<Bag.get_itemCount(); i++)
            delete Bag[i];
    }
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
    //    Hash_Table Bag2Table()const;
    
    void SaveFile(const string& FileName)
    {
        ofstream file;// declaration of file pointer named infile
        file.open(FileName, ios::out);// opens file named "filename" for input
        string Write="";
        
        //fixedEventName,category,startT.getTimeStr(),endT.getTimeStr(),to_string(duration)/n
        for(int i=0; i<Bag.get_itemCount() ; i++)
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
    ~MissionBag()
    {
        for(int i=0; i<Bag.get_itemCount(); i++)
            delete Bag[i];
    }
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
            Write+=Bag[i]->GetMisDone_Str();
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
            Write+=Bag[i]->GetMisScheduled_Str();
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
                this->Bag.add(newM);
            }
        
        file.close();//closes file
    }
    Hash_Table Bag2Table()
    {
        Hash_Table HT;
        for(int i=0; i<Bag.get_itemCount(); i++)
        {
            if(HT.inTable(Bag[i]->GettagForGraph()))//already has a previous key
            {
                HT[Bag[i]->GettagForGraph()] += Bag[i]->getDuration();
            }
            else
            {
                HT.put(Bag[i]->GettagForGraph(), Bag[i]->getDuration());
            }
        }
        return HT;
    }
};

List Merge_Bag2List(FixedEventBag& FEBag, MissionBag& MBag );
#endif /* Bags_List_hpp */
