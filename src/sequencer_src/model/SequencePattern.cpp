#include "SequencePattern.h"

void SequencePattern::addEvent(uint8_t index, SequenceEvent* event) {
    while(events.size() <= index) {
        events.add(NULL);
    }
    deleteEvent(index);
    events.set(index, event);
}

void SequencePattern::deleteEvent(uint8_t index) {
    SequenceEvent* existingEvent = events.get(index);
    if(existingEvent != NULL) {
        events.set(index, NULL);
        delete existingEvent;
    }
}
