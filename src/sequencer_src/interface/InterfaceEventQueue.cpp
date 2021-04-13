#include "InterfaceEventQueue.h"

InterfaceEventQueue InterfaceEventQueue::q;

void InterfaceEventQueue::pushEvent(InterfaceEvent event) { 
    size = 1; 
    this->event = event; 
}

InterfaceEvent& InterfaceEventQueue::popEvent() { 
    size = 0;
    return event;
}