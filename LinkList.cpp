#include "DoubleNode.cpp"
#include <iostream>
#include <string>
using namespace std;
template <typename Type>
class LinkList
{
    friend class Polynomial;
public:
    LinkList();
    ~LinkList(){};
    /*---copy constructor---*/
    LinkList(const Type& Item1);
    LinkList(const LinkList<Type>& other);
    LinkList(DoubleNode<Type>* other, int count);
    LinkList<Type>& operator=(LinkList<Type>& other);
    /*---set and get---*/
    void insertAtBack(DoubleNode<Type>* otherDoubleNode);
    void insertAtFront(DoubleNode<Type>* otherDoubleNode);
    void clear();
    DoubleNode<Type>* operator[](int order);
//protected:
    DoubleNode<Type>* head;
    int count;
    void copy(const LinkList<Type>& other);
};

template <typename Type>
LinkList<Type>::LinkList()
:head(nullptr), count(0)
{
}

template <typename Type>
LinkList<Type>::LinkList(const Type& Item1)
{
    this->head = new DoubleNode<Type>(Item1);
    count = 1;
}

template <typename Type>
LinkList<Type>::LinkList(const LinkList<Type>& other)
{
    copy(other);
}

template <typename Type>
LinkList<Type>::LinkList(DoubleNode<Type>* other, int count)
{
    this->count = count;
    if(other==nullptr)
        this->head = nullptr;
    else
    {
        this->head = new DoubleNode<Type>(other);
        DoubleNode<Type>* cur = this->head;
        other = other->getNext();
        while(other!=nullptr)
        {
            DoubleNode<Type>* newDoubleNode = new DoubleNode<Type>(other);
            cur ->setNext(newDoubleNode);
            newDoubleNode->setPrevious(cur);
            cur = cur->getNext();
            other = other->getNext();
        }
        cur->setNext(nullptr);
    }
}


template <typename Type>
void LinkList<Type>::copy(const LinkList<Type>& other)
{
    this->count = other.count;
    if(other.head==nullptr)
        this->head = nullptr;
    else
    {
        this->head = new DoubleNode<Type>(other.head);
        DoubleNode<Type>* otherHead = other.head;
        DoubleNode<Type>* selfHead = this->head;
        otherHead = otherHead->getNext();
        while(otherHead!=nullptr)
        {
            DoubleNode<Type>* newDoubleNode = new DoubleNode<Type>(otherHead);
            selfHead -> setNext(newDoubleNode);
            newDoubleNode->setPrevious(selfHead);
            selfHead = selfHead->getNext();
            otherHead = otherHead->getNext();
        }
        selfHead->setNext(nullptr);
    }
}




template <typename Type>
void LinkList<Type>::clear()
{
    count = 0;
    DoubleNode<Type>* curPtr = this->head;
    if(curPtr!=nullptr)
    {
        while(curPtr!=nullptr)
        {
            DoubleNode<Type>* nextPtr = curPtr->getNext();
            delete curPtr;
            curPtr = nextPtr;
        }
        this->head =nullptr;
    }
}

template <typename Type>
LinkList<Type>& LinkList<Type>::operator=(LinkList<Type>& other)
{
    if(this->head!=nullptr)
        this->clear();
    copy(other);
    return *this;
}


template <typename Type>
void LinkList<Type>::insertAtBack(DoubleNode<Type>* otherDoubleNode)
{
    if(this->head==nullptr)
    {
        this->head  = new DoubleNode<Type>(otherDoubleNode);
        this->count++;
    }
    else
    {
        DoubleNode<Type>* curPtr = this->head;
        DoubleNode<Type>* next=curPtr->getNext();
        while(next!=nullptr)
        {
            curPtr = next;
            next = next->getNext();
        }
        DoubleNode<Type>* newDoubleNode =  new DoubleNode<Type>(otherDoubleNode);
        curPtr->setNext(newDoubleNode);
        newDoubleNode->setPrevious(curPtr);
        this->count++;
    }
}

template <typename Type>
void LinkList<Type>::insertAtFront(DoubleNode<Type>* otherDoubleNode)
{
    if(this->head==nullptr)
    {
        this->head  = new DoubleNode<Type>(otherDoubleNode);
        this->count++;
    }
    else
    {
        DoubleNode<Type>* newDoubleNode = new DoubleNode<Type>(otherDoubleNode);
        DoubleNode<Type>* curPtr = this->head;
        newDoubleNode->setNext(curPtr);
        curPtr->setPrevious(newDoubleNode);
        this->head = newDoubleNode;
        this->count++;
    }
}
