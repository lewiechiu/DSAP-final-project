

#ifndef FIXED_EVENT
#define FIXED_EVENY

#include <string>
#include"event.h"
#include "Time.h"
using namespace std;
class FixedEvent: public Event
{
private:
protected:
public:
    FixedEvent();
    FixedEvent(string name, string tagForGraph, Time startTime, Time endTime, int duration);
};
#endif //FIXED_EVENT
