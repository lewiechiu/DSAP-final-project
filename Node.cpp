#include <stdio.h>
#include <iostream>
template <typename Type>
class Node
{
public:
    Type item;
    Node<Type>* next;
    Node();
    Node(Type anItem);
    Node(Type& anItem, Node<Type>* nextNodeprt);
    void setItem(const Type& anItem);
    void setNext(Node<Type>* nextNodeprt);
    Type getItem() const ;
    Node<Type>* getNext() const ;
};

template<typename Type>
Node<Type>::Node()
:next(nullptr)
{}

template<typename Type>
Node<Type>::Node(Type anItem)
:item(anItem), next(nullptr)
{}

template<typename Type>
Node<Type>::Node(Type& anItem, Node<Type>* nextNodeprt)
:item(anItem), next(nextNodeprt)
{}

template<typename Type>
void Node<Type>::setItem(const Type& anItem)
{this->item = anItem;}

template<typename Type>
void Node<Type>::setNext(Node<Type>* nextNodeprt)
{
    this->next = nextNodeprt;
}

template<typename Type>
Type Node<Type>::getItem() const
{
    return this->item;
}

template<typename Type>
Node<Type>* Node<Type>::getNext() const
{
    return this->next;
}
