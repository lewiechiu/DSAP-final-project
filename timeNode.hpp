#ifndef timeNode_hpp
#define timeNode_hpp
//#include "Time"
//a node for each minute
using namespace std;
template<typename Itemtype>
class timeNode
{
private:
    //  Time time;
    int status;//0:not allocated 1:mission 2:fixed event 3:has been checked,wait for allocation 4:less than 30 minutes
    Itemtype* occurrence;//a pointer to the event or mission
public:
    timeNode();
    /*
    not useful when creating an array of timeNode
    timeNode(int theStatus);
    timeNode(int theStatus, Itemtype *anOccurrence);
     */
    void setStatus(int theStatus);//reset the status for this minute
    void setOccurrence(Itemtype* anOccurrence);//reallocate an event or mission to this minute
    int getStatus();
    Itemtype* getOccurrence();
};

#endif /* timeNode_hpp */
