//
//  Hash_Table.hpp
//  SFML
//
//  Created by Nicksome on 2018/7/9.
//  Copyright © 2018 Nicksome. All rights reserved.
//

#ifndef Hash_Table_hpp
#define Hash_Table_hpp
#include <string>
#include <stdio.h>
#include <bitset>
#include <cmath>
#include <iostream>

//Hash_Table
//void print()
//  print each key and value
//string* getKeys()
//  get all the keys in the table
//void put(key, value)
//  add a new pair into the table
//int operator [](string)
//  input a key, return its value
//bool inTable(const string& Key)
//  check if the key is inside the table
using namespace std;
struct Hash_Node
{
    Hash_Node(const string& Category, int Sum_Time)
    :key(Category), value(Sum_Time)
    {}
    Hash_Node(const Hash_Node& other)
    {
        key= other.key;
        value = other.value;
    }
    bool operator>(Hash_Node& other)
    {return value>other.value;}
    bool operator<(Hash_Node& other)
    {return value<other.value;}
    string key;
    int value;
};

class Hash_Table
{
public:
    Hash_Table()
    :Count(0)
    {
        keys = new string[CAPACITY];
        for(int i=0; i<CAPACITY; i++)
        {
            Dict[i] = nullptr;
        }
    }
    Hash_Table(const Hash_Table& other)
    {
        Count = other.Count;
        for(int i=0; i<CAPACITY; i++)
        {
            if(other.Dict[i]!=nullptr)
            {
                keys[i] = other.Dict[i]->key;
                Dict[i] = new Hash_Node(*other.Dict[i]);
            }
            else
                Dict[i] = nullptr;
        }
    }
    ~Hash_Table()
    {
        for(int i=0; i<Count; i++)
            delete Dict[i];
        delete [] keys;
    }
    
    void print ()const
    {
        for(int i=0; i<Count; i++)
            cout<<Dict[get(keys[i])]->key<<" "<<Dict[get(keys[i])]->value<<endl;
    }
    
    string* getKeys()const
    {return this->keys;}
    
    int getCount()const
    {return this->Count;}
    
    bool inTable(const string& Key)
    {
        for(int i=0; i<Count; i++)
            if(keys[i]==Key)
                return true;
        return false;
    }
    
    int& operator[](const string& Key)
    {return Dict[get(Key)]->value;}
    
    void put(const string& Key, int Value)
    {
        int collision_num = 1;
        bool success=false;
        int key = HashFn(Key);
        if(key<0)
        {
            cout<<"Hash Fun out of index\n";
            system("Pause");
        }
        if (Dict[key]==nullptr)
        {
            Dict[key] = new Hash_Node(Key, Value);
            keys[Count] = Key;
            Count++;
        }
        else
        {
            
            while(!success && key<CAPACITY)
            {
                key+=pow(collision_num, 2);
                if(Dict[key]==nullptr)
                {
                    Dict[key] = new Hash_Node(Key, Value);
                    keys[Count] = Key;
                    success = true;
                    Count++;
                    break;
                }
                else
                    collision_num++;
            }
            if(!success)
            {
                cout<<"No room in Hash table\n";
                system("pause");
            }
        }
    }

private:
    Hash_Node* Dict[101];
    string* keys;
    const static int CAPACITY =101;
    int Count;
    int get(const string& Key)const
    {
        int key = HashFn(Key);
        if(Dict[key]->key == Key)
            return key;
        else
        {
            int collision_num = 1;
            bool success=false;
            while(!success && key<CAPACITY)
            {
                key =key+pow(collision_num, 2);
                if(Dict[key]->key == Key)
                {
                    success = true;
                    return key;
                }
                else
                    collision_num++;
            }
            return -1;
        }
    }
    int HashFn(const string& Key) const
    {
        int Val[50] = {0};
        long long SUM=0;
        for(size_t i=0; i<Key.size(); i++)
        {
            //turn to 1~26
            Val[i] = Key[i]-31;
            //val*32^i
            SUM += Val[i]*pow(3, i);
        }
        cout<<Key<<" "<<SUM<<endl;
        return SUM%CAPACITY;
    }

};


#endif /* Hash_Table_hpp */
