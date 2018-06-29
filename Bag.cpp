
/*---------------------------------------------------NODE.cpp---------------------------------------------------------*/

#include <stdio.h>
#include <string>
#include <iostream>
/*
Node is used to store any types of variables and link them together by making everyone of them memorize the memory
location of their next Node and, eventually, form a "BAG" (Further implementation is class Linked Bag)
Solving memory problem in dynamic allocation
*/

template <class Type>
class Node
{
public:
    /*VARIABLES*/
    Type item;
    //value of the Node. deapand on the type we input
    Node<Type>* next;
    //save the memory location of next Node
    
    /*CONSTRUCTOR & DESSTRUCTOR*/
    Node();
    Node(const Type& anItem);   //copy constructor
    Node(const Type& anItem, const Node<Type>* nextNodeprt);    //copy constructor
    //@param: value of <Type> item
    //@param: pointer pointing to the next <Type> Node
    Node<Type>& operator=(const Node<Type> other);  //assignment operation overload
    
    /*FUNCTION*/
    void setItem(const Type& anItem);
    //set the value of the Node
    //@param:  <Type> item
    void setNext(Node<Type>* nextNodeprt);
    //let the next pointer point to the memory location of next Node
    //@param:  pointer pointing to the next <Type> item
    Type getItem() const ;
    //get the value of that Node
    Node<Type>* getNext() const ;
    //get the memory location of next Node
    bool operator==(const Node<Type> other) const;
    //equal comparison operation overload, comparing the value of Node and the memory location of next Node
    //@param: <Type> Node object
};

template<class Type>
Node<Type>::Node()
:next(nullptr)
{}

template<class Type>
Node<Type>::Node(const Type& anItem)
:item(anItem), next(nullptr)
{}

template<class Type>
Node<Type>::Node(const Type& anItem, const Node<Type>* nextNodeprt)
:item(anItem), next(nextNodeprt)
{}

template<class Type>
void Node<Type>::setItem(const Type& anItem)
{this->item = anItem;}

template<class Type>
void Node<Type>::setNext(Node<Type>* nextNodeprt)
{
    this->next = nextNodeprt;
}

template<class Type>
Type Node<Type>::getItem() const
{
    return this->item;
}

template<class Type>
Node<Type>* Node<Type>::getNext() const
{
    return this->next;
}

template<class Type>
bool Node<Type>::operator==(const Node<Type> other) const
{
    return (this->item==other && this->next==other.next);
}

template <class Type>
Node<Type>& Node<Type>::operator=(const Node<Type> other)
{
    return (this->next==other.next && this->item==other.item);
}

/*----------------------------------------------------Myexception.hpp--------------------------------------------------------*/

#ifndef Myexception_hpp
#define Myexception_hpp
#include <stdio.h>
using namespace std;
/*Myexception is used to throw exception in functions inside PlatForm and LinkedBag class.
  For example, wrong input format, index out of range*/
#include <stdexcept>
class Myexception: public logic_error
{
public:
    Myexception(const string& msg)
    : logic_error(msg){;}
};
#endif /* Myexception_hpp */

/*--------------------------------------------------------LinkedBag.cpp--------------------------------------------------------*/

//Bag is used to store any same type of Node
//EX: Car_Onlinebag, Passenger_Onlinebag, ALL_TAGS

template<typename Type>
class LinkedBag
{
protected:
/*----Protected Data-----*/
    Node<Type>* headptr;
    //indicate the head of the LinkedBag
    int item_count;
    //the total amount of Nodes inside the LinkedBag
    
/*----Protected Function-----*/
    Node<Type>* getPointer(const Type& goalItem) const ;
    //get the memory location of the Node which has the same <Type> item as the given one
    //@param: <Type> item
public:
/*-----Constructor-----*/
    LinkedBag();
    LinkedBag(const LinkedBag<Type>& abag); //copy constructor
    ~LinkedBag();
    
/*-----public function-----*/
    void add(const Type &addItem );
    //add a Node into the LinkedBag with its <Type >item value
    //@param: <Type> item
    void remove(const Type& removeItem) ;
    //remove certain Node which has same <Type> item as the given one from the LinkedBag
    //@param: <Type> Item
    int getSize() const;
    //get the size of the LinkedBag
    bool isEmpty() const;
    //check if the LinkedBag is empty
    bool contains(const Type& goalItem);
    //check if the LinkedBag contains the Node which has same <Type> item as the given one
    //@para: <Type> item
    void clearAll();
    //delete all the pointer between Nodes
    
    Type operator[](int index)const throw(Myexception);
    //if index out of range, it will throw Myexception
    
    LinkedBag<Type>& operator=(const LinkedBag<Type>& abag);
    //assignment operator. do a deep copy
};

template<typename Type>
LinkedBag<Type>::LinkedBag()
:headptr(nullptr), item_count(0){}

template<typename Type>
LinkedBag<Type>::LinkedBag(const LinkedBag<Type>& abag)
{
    this->item_count = abag.item_count;
    if(abag.headptr!=nullptr)
    {
        Node<Type>* oldDynamicPtr = abag.headptr;
        //dynamic pointer points the headptr of the old bag
        
        headptr = new Node<Type>();
        headptr->setItem(oldDynamicPtr->getItem());
        //initialize the new head
        
        Node<Type>* newDynamicPtr = headptr;
        oldDynamicPtr = oldDynamicPtr->getNext();
        //dynamic pointer to traverse the old/ new bag
        
        while(oldDynamicPtr!=nullptr)
        {
            Node<Type>* newNode = new Node<Type>(oldDynamicPtr->getItem());
            //create a new Node
            newDynamicPtr->setNext(newNode);
            //set the new Node as next in new bag
            newDynamicPtr = newDynamicPtr->getNext();
            //traverse to new Node in new bag
            oldDynamicPtr = oldDynamicPtr->getNext();
            //traverse to new Node in old bag
        }
        newDynamicPtr->setNext(nullptr);
    }
    else
        headptr = nullptr;
    
}

template<typename Type>
LinkedBag<Type>::~LinkedBag()
{
    this->clearAll();
}

template<typename Type>
LinkedBag<Type>& LinkedBag<Type>::operator=(const LinkedBag<Type>& abag)
{
    this->clearAll();
    this->item_count = abag.item_count;
    if(abag.headptr!=nullptr)
    {
        Node<Type>* oldDynamicPtr = abag.headptr;
        //dynamic pointer points the headptr of the old bag
        
        headptr = new Node<Type>();
        headptr->setItem(oldDynamicPtr->getItem());
        //initialize the new head
        
        Node<Type>* newDynamicPtr = headptr;
        oldDynamicPtr = oldDynamicPtr->getNext();
        //dynamic pointer to traverse the old/ new bag
        
        while(oldDynamicPtr!=nullptr)
        {
            Node<Type>* newNode = new Node<Type>(oldDynamicPtr->getItem());
            //create a new Node
            newDynamicPtr->setNext(newNode);
            //set the new Node as next in new bag
            newDynamicPtr = newDynamicPtr->getNext();
            //traverse to new Node in new bag
            oldDynamicPtr = oldDynamicPtr->getNext();
            //traverse to new Node in old bag
        }
        newDynamicPtr->setNext(nullptr);
    }
    else
        headptr = nullptr;
    return (*this);
}


template<typename Type>
void LinkedBag<Type>::add(const Type& addItem)
{
    Node<Type>* newNodeptr = new Node<Type>();
    //create a new node pointer
    newNodeptr ->setItem(addItem);
    //set the value
    newNodeptr ->setNext(this->headptr);
    //set the next pointer to the previoud first one
    this->headptr = newNodeptr;
    //set the current head to the new
    this->item_count++;
}

template<typename Type>
void LinkedBag<Type>::remove(const Type& removeItem)
{
    if(!this->isEmpty())
    {
        Node<Type>* goalPtr = this->getPointer(removeItem);
        goalPtr->setItem(headptr->getItem());
        //change the remove item to the first item
        Node<Type>* delFirst = headptr;
        headptr = headptr->getNext();
        delete delFirst;
        delFirst = nullptr;
        this->item_count--;
    }
}


template<typename Type>
Node<Type>* LinkedBag<Type>::getPointer(const Type& goalItem) const
{
    bool notfound = true;
    Node<Type>* nowPtr = this->headptr;
    //set a pointer to traverse the whole list
    while( (nowPtr!=nullptr) && notfound)
    {
        if(nowPtr->getItem()==goalItem)
        {
            notfound = false;
            return nowPtr;
        }
        else
            nowPtr = nowPtr->getNext();
    }
    return nowPtr;
    //return nullptr if nothing found
}

template<typename Type>
bool LinkedBag<Type>::isEmpty() const
{
    return this->item_count==0;
}

template<typename Type>
bool LinkedBag<Type>::contains(const Type& goalItem)
{
    return getPointer(goalItem)!=nullptr;
}

template<typename Type>
int LinkedBag<Type>:: getSize()const
{
    return this->item_count;
}

template<typename Type>
void LinkedBag<Type>::clearAll()
{
    Node<Type>* nowPtr = headptr;
    while(nowPtr!=nullptr)
    {
        headptr = headptr->getNext();
        //go to n+1
        delete nowPtr;
        //delete n
        nowPtr =  headptr;
    }
    this->item_count=0;
    headptr = nullptr;
}


template<typename Type>
Type LinkedBag<Type>::operator[](int index)const throw (Myexception)
{
    int time = index;
    Type objective;
    if(index<item_count)
    {
        /* head->tag1->tag2->nullptr */
        Node<Type>* loop = headptr;
        while(time>=0)
        {
            if(time!=index)
                loop = loop->getNext();
            objective = loop->getItem();
            //assign to the same address
            time--;
        }
        return objective;
    }
    throw Myexception("index is out of range in LinkedBag");
    //if index out of range exit
}
