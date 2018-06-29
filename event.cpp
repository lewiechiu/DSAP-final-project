#include "event.h"
#include "OurTime.hpp"
#include <string>
using namespace std;
Event::Event(): duration(-1), name(""), tagForGraph(""), isDone(false)
{
    /*
    initializers for startTime and endTime not implemented yet
    */
}
Event::Event(string name, string tagForGraph, OurTime startTime, OurTime endTime, int duration)
            :name(name), tagForGraph(tagForGraph), startTime(startTime), 
            endTime(endTime), duration(duration), isDone(false)
{
}

