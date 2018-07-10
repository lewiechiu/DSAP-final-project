

#ifndef FIXED_EVENT
#define FIXED_EVENT

#include <string>
#include "event.h"
#include "OurTime.hpp"
using namespace std;
class FixedEvent: public Event
{
private:
protected:
public:
    FixedEvent();
    FixedEvent(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration);
    OurTime getStartTime();
    int getDuration() const;
    bool operator==(const FixedEvent& FE)const;
};
#endif //FIXED_EVENT
