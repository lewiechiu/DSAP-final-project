#include "timeNode.hpp"
#include "event.h"
#include "Mission.h"
#include "FixedEvent.h"
#include <iostream>
using namespace std;

timeNode::timeNode():status(0), occurrence(nullptr){}

/*not useful when creating an array of timeNode
template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus):status(theStatus), occurrence(nullptr){}

template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus, Itemtype *anOccurrence):status(theStatus), occurrence(anOccurrence){};
 */


void timeNode::setStatus(int theStatus)
{
    status = theStatus;
}


void timeNode::setOccurrence(Event* anOccurrence)
{
    occurrence = anOccurrence;
}


int timeNode::getStatus()
{
    return status;
}


Event* timeNode::getOccurrence()
{
    return occurrence;
}



void timeNode::setEventIsScheduled(bool a)
{
    occurrence->setIsSchedule(a);
}

















