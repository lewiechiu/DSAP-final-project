//
//  Bags&List.cpp
//  SFML
//
//  Created by Nicksome on 2018/7/12.
//  Copyright © 2018 Nicksome. All rights reserved.
//

#include "Bags&List.hpp"
List::List()
:Count(0)
{
    for (int i=0; i<CAPACITY; i++)
        list[i] = nullptr;
}

List::List(const List& other)
{
    Count = other.Count;
    for (int i=0; i<CAPACITY; i++)
    {
        if(other.list[i]!=nullptr)
            list[i] = new Hash_Node(*other.list[i]);
        else
            list[i] = nullptr;
    }
}
void List::Table2List(Hash_Table& HT)
{
    string* allKeys = HT.getKeys();
    Count =HT.getCount();
    for(int i=0; i<HT.getCount(); i++)
        list[i] = new Hash_Node(allKeys[i], HT[allKeys[i]]);
    quickSort(list, 0, Count-1);
}

void List::print()const
{
    for(int i=0; i<Count; i++)
        cout<<list[i]->key<<" "<<list[i]->value<<endl;
}

List::~List()
{
    for (int i=0; i<CAPACITY; i++)
        delete list[i];
}
void List::add(Hash_Node newNode)
{
    list[Count] = new Hash_Node(newNode);
    Count++;
}
int List::getCount()const
{return Count;}

Hash_Node* List::operator[](int index)
{
    return list[index];
}
void List::quickSort(Hash_Node* arr[], int left, int right)
{
    
    int i = left, j = right;
    
    Hash_Node* tmp =nullptr;
    
    Hash_Node* pivot = arr[(left + right) / 2];
    
    /* partition */
    while (i <= j)
    {
        while (*arr[i] > *pivot)
            i++;
        while (*arr[j] < *pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}


List Merge_Bag2List(FixedEventBag& FEBag, MissionBag& MBag )
{
    Hash_Table HT;
    List L;
    for(int i=0; i<FEBag.Bag.get_itemCount(); i++)
    {
        if(HT.inTable(FEBag.Bag[i]->GettagForGraph()))//already has a previous key
        {
            HT[FEBag.Bag[i]->GettagForGraph()] += FEBag.Bag[i]->getDuration();
        }
        else
        {
            HT.put(FEBag.Bag[i]->GettagForGraph(), FEBag.Bag[i]->getDuration());
        }
    }
    for(int i=0; i<MBag.Bag.get_itemCount(); i++)
    {
        if(HT.inTable(MBag.Bag[i]->GettagForGraph()))//already has a previous key
        {
            HT[MBag.Bag[i]->GettagForGraph()] += MBag.Bag[i]->getDuration();
        }
        else
        {
            HT.put(MBag.Bag[i]->GettagForGraph(), MBag.Bag[i]->getDuration());
        }
    }
    L.Table2List(HT);
    return L;
}

