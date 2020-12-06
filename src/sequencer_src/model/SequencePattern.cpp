#include "SequencePattern.h"

SequencePattern::~SequencePattern() {
    clear();
}

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

void SequencePattern::clear() {
    for(int i = 0; i < events.size(); i++) {
        SequenceEvent* event = events.get(i);
        if(event != NULL) {
            delete event;
        }
    }
    events.clear();
}