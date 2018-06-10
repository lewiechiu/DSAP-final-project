#include "event.h"
#include "FixedEvent.h"
#include "Event.h"
#include "Time.h"
#include <string>
using namespace std;
FixedEvent::FixedEvent(): Event()
{
}
FixedEvent::FixedEvent(string name, string tagForGraph, Time startTime, Time endTime, int duration)
                        :Event(name, tagForGraph, startTime, endTime, duration)
{
}
