#include "event.h"
#include "FixedEvent.h"
#include "Event.h"
#include <string>
using namespace std;
FixedEvent::FixedEvent(): Event()
{
}
FixedEvent::FixedEvent(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration)
                        :Event(name, tagForGraph, startTime, endTime, duration)
{
}
OurTime FixedEvent::getStartTime()
{
	return this->startTime;
}
int FixedEvent::getDuration() const
{
	return this->duration;
}
