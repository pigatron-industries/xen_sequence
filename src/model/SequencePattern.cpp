#include "SequencePattern.h"

void SequencePattern::addEvent(uint8_t index, SequenceEvent* event) {
    while(events.size() <= index) {
        events.add(NULL);
    }
    SequenceEvent* existingEvent = events.get(index);
    if(existingEvent != NULL) {
        delete existingEvent;
    }
    events.set(index, event);
}
