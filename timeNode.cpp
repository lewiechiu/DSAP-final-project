#include "timeNode.hpp"
#include <iostream>
using namespace std;

template<typename Itemtype>
timeNode<Itemtype>::timeNode():status(0), occurrence(nullptr){}

/*not useful when creating an array of timeNode
template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus):status(theStatus), occurrence(nullptr){}

template<class Itemtype>
timeNode<Itemtype>::timeNode(int theStatus, Itemtype *anOccurrence):status(theStatus), occurrence(anOccurrence){};
 */

template<typename  Itemtype>
void timeNode<Itemtype>::setStatus(int theStatus)
{
    status = theStatus;
}

template<typename  Itemtype>
void timeNode<Itemtype>::setOccurrence(Itemtype* anOccurrence)
{
    occurrence = anOccurrence;
}

template<typename  Itemtype>
int timeNode<Itemtype>::getStatus()
{
    return status;
}

template<typename Itemtype>
Itemtype* timeNode<Itemtype>::getOccurrence()
{
    return occurrence;
}

















