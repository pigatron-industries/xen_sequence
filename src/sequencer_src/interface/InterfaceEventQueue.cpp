#include "InterfaceEventQueue.h"
#include <Arduino.h>

InterfaceEventQueue InterfaceEventQueue::q;

void InterfaceEventQueue::pushEvent(InterfaceEvent event) { 
    size = 1; 
    this->event = event; 
}

InterfaceEvent& InterfaceEventQueue::popEvent() { 
    size = 0;
    return event;
}

void InterfaceEventQueue::doRender(bool full) { 
    if(size == 0) {
        pushEvent(InterfaceEvent(InterfaceEventType::RENDER, full));
    } else if(size == 1 && event.eventType == InterfaceEventType::RENDER && event.data == 0) {
        event.data = full;
    }
}
