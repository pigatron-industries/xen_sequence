#include "SequenceTickEvents.h"

SequenceTickEvents::~SequenceTickEvents() {
    clearEvents();
}

SequenceTickEvents::SequenceTickEvents(SequenceTickEvents* sourceTickEvents) {
    copy(sourceTickEvents);
}

void SequenceTickEvents::copy(SequenceTickEvents* sourceTickEvents) {
    clearEvents();
    for(int i = 0; i < sourceTickEvents->getSize(); i++) {
        SequenceEvent* sourceEvent = sourceTickEvents->getEvent(i);
        SequenceEvent* newEvent = new SequenceEvent(sourceEvent);
        events.add(newEvent);
    }
    compiled = false;
}

void SequenceTickEvents::addEvent(SequenceEvent* event) {
    events.add(event);
    compiled = false;
}

void SequenceTickEvents::deleteEvent(int index) {
    delete events.remove(index);
    compiled = false;
}

void SequenceTickEvents::clearEvents() {
    for(int i = 0; i < events.size(); i++) {
        delete events.get(i);
    }
    events.clear();
    compiled = false;
}

void SequenceTickEvents::serialize(JsonArray doc) {
    for(int i = 0; i < events.size(); i++) {
        JsonObject docEvent = doc.createNestedObject();
        events.get(i)->serialize(docEvent);
    }
}

void SequenceTickEvents::deserialize(JsonArray doc) {
    for(JsonObject docEvent : doc) {
        SequenceEvent* event = new SequenceEvent();
        addEvent(event);
        event->deserialize(docEvent);
    }
}
