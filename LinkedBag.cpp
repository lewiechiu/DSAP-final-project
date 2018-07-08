#include "LinkedBag.h"
#include "mission.h"
#include "FixedEvent.h"
using namespace std;
/*---------------------------------------------------NODE.cpp---------------------------------------------------------*/

/*
Node is used to store any types of variables and link them together by making everyone of them memorize the memory
location of their next Node and, eventually, form a "BAG" (Further implementation is class Linked Bag)
Solving memory problem in dynamic allocation
*/



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
/*--------------------------------------------------------LinkedBag.cpp--------------------------------------------------------*/

//Bag is used to store any same type of Node
//EX: Car_Onlinebag, Passenger_Onlinebag, ALL_TAGS

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
Type LinkedBag<Type>::operator[](int index)const
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
    //if index out of range exit
}

template<typename Type>
int LinkedBag<Type>::get_itemCount()
{
    return this->item_count;
}

template class LinkedBag<Mission>;
template class LinkedBag<FixedEvent>;
