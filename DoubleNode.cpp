#include <stdio.h>
#include <iostream>
template <typename Type>
class DoubleNode
{
public:
    Type item;
    DoubleNode<Type>* next;
    DoubleNode<Type>* previous;
    DoubleNode();
    DoubleNode(Type anItem);
    DoubleNode(DoubleNode<Type>* otherPtr);
    DoubleNode(Type& anItem, DoubleNode<Type>* previousDoubleNodeprt, DoubleNode<Type>* nextDoubleNodeprt);
    
    void setItem(const Type& anItem);
    void setNext(DoubleNode<Type>* nextDoubleNodeprt);
    void setPrevious(DoubleNode<Type>* previousDoubleNodeprt);
    Type getItem() const ;
    DoubleNode<Type>* getNext() const ;
    DoubleNode<Type>* getPrevious() const;
};

template<typename Type>
DoubleNode<Type>::DoubleNode()
:next(nullptr),previous(nullptr)
{}

template<typename Type>
DoubleNode<Type>::DoubleNode(Type anItem)
:item(anItem), next(nullptr), previous(nullptr)
{}

template<typename Type>
DoubleNode<Type>::DoubleNode(DoubleNode<Type>* otherPtr)
:item(otherPtr->getItem()),next(nullptr), previous(nullptr)
{}

template<typename Type>
DoubleNode<Type>::DoubleNode(Type& anItem, DoubleNode<Type>* previousDoubleNodeprt, DoubleNode<Type>* nextDoubleNodeprt)
:item(anItem), next(nextDoubleNodeprt), previous(previousDoubleNodeprt)
{}

template<typename Type>
void DoubleNode<Type>::setItem(const Type& anItem)
{this->item = anItem;}

template<typename Type>
void DoubleNode<Type>::setNext(DoubleNode<Type>* nextDoubleNodeprt)
{
    this->next = nextDoubleNodeprt;
}

template<typename Type>
void DoubleNode<Type>::setPrevious(DoubleNode<Type>* previousDoubleNodeprt)
{
    this->previous = previousDoubleNodeprt;
}

template<typename Type>
Type DoubleNode<Type>::getItem() const
{
    return this->item;
}

template<typename Type>
DoubleNode<Type>* DoubleNode<Type>::getNext() const
{
    return this->next;
}

template<typename Type>
DoubleNode<Type>* DoubleNode<Type>::getPrevious() const
{
    return this->previous;
}




