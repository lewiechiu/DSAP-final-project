#include "Node.cpp"
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
    LinkList(Node<Type>* other, int count);
    LinkList<Type>& operator=(LinkList<Type>& other);
    /*---set and get---*/
    void insertAtBack(Node<Type>* otherNode);
    void insertAtFront(Node<Type>* otherNode);
    void clear();
    Node<Type>* operator[](int order);
protected:
    Node<Type>* head;
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
    this->head = new Node<Type>(Item1);
    count = 1;
}

template <typename Type>
LinkList<Type>::LinkList(const LinkList<Type>& other)
{
    copy(other);
}

template <typename Type>
LinkList<Type>::LinkList(Node<Type>* other, int count)
{
    this->count = count;
    if(other==nullptr)
        this->head = nullptr;
    else
    {
        this->head = new Node<Type>(other);
        Node<Type>* cur = this->head;
        other = other->getNext();
        while(other!=nullptr)
        {
            Node<Type>* newNode = new Node<Type>(other);
            cur ->setNext(newNode);
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
        this->head = new Node<Type>(other.head);
        Node<Type>* otherHead = other.head;
        Node<Type>* selfHead = this->head;
        otherHead = otherHead->getNext();
        while(otherHead!=nullptr)
        {
            Node<Type>* newNode = new Node<Type>(otherHead);
            selfHead -> setNext(newNode);
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
    Node<Type>* curPtr = this->head;
    if(curPtr!=nullptr)
    {
        while(curPtr!=nullptr)
        {
            Node<Type>* nextPtr = curPtr->getNext();
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
void LinkList<Type>::insertAtBack(Node<Type>* otherNode)
{
    if(this->head==nullptr)
    {
        this->head  = new Node<Type>(otherNode);
        this->count++;
    }
    else
    {
        Node<Type>* curPtr = this->head;
        Node<Type>* next=curPtr->getNext();
        while(next!=nullptr)
        {
            curPtr = next;
            next = next->getNext();
        }
        Node<Type>* newNode =  new Node<Type>(otherNode);
        curPtr->setNext(newNode);
        this->count++;
    }
}

template <typename Type>
void LinkList<Type>::insertAtFront(Node<Type>* otherNode)
{
    if(this->head==nullptr)
    {
        this->head  = new Node<Type>(otherNode);
        this->count++;
    }
    else
    {
        Node<Type>* newNode = new Node<Type>(otherNode);
        Node<Type>* curPtr = this->head;
        newNode->setNext(curPtr);
        this->head = newNode;
        this->count++;
    }
}
