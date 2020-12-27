#include "SequencePattern.h"

SequencePattern::~SequencePattern() {
    clear();
}

void SequencePattern::copy(SequencePattern* sourcePattern) {
    clear();
    for(int i = 0; i < sourcePattern->getEvents().size(); i++) {
        SequenceEvent* sourceEvent = sourcePattern->getEvent(i);
        if(sourceEvent != NULL) {
            SequenceEvent* newEvent = new SequenceEvent(sourceEvent);
            addEvent(i, newEvent);
        }
    }
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

void SequencePattern::serialize(JsonObject doc) {
    doc["id"] = id;
    JsonArray docEvents = doc.createNestedArray("events");
    for(int i = 0; i < events.size(); i++) {
        if(events[i] != NULL) {
            JsonObject docEvent = docEvents.createNestedObject();
            docEvent["pos"] = i;
            events[i]->serialize(docEvent);
        }
    }
}

void SequencePattern::deserialize(JsonObject doc) {
    id = doc["id"];
    JsonArray docEvents = doc["events"];
    for(JsonObject docEvent : docEvents) {
        int pos = docEvent["pos"];
        SequenceEvent* event = new SequenceEvent();
        addEvent(pos, event);
        event->deserialize(docEvent);
    }
}
