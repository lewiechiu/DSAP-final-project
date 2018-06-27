#include "timeNode.hpp"
#include <iostream>
using namespace std;

template<class Itemtype>
timeNode<Itemtype>::timeNode():status(0), occurrence(nullptr){}

/*not useful when creating an array of timeNode
template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus):status(theStatus), occurrence(nullptr){}

template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus, Itemtype *anOccurrence):status(theStatus), occurrence(anOccurrence){};
 */

template<class Itemtype>
void timeNode<Itemtype>::setStatus(int theStatus)
{
    status = theStatus;
}

template<class Itemtype>
void timeNode<Itemtype>::setOccurrence(Itemtype* anOccurrence)
{
    occurrence = anOccurrence;
}

template<class Itemtype>
int timeNode<Itemtype>::getStatus()
{
    return status;
}

template<class Itemtype>
Itemtype* timeNode<Itemtype>::getOccurrence()
{
    return occurrence;
}

template<class Itemtype>
void timeNode<Itemtype>::setEventIsScheduled(bool a)
{
    occurrence->setIsSchedule(a);
}
















