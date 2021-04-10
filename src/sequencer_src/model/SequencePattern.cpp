#include "SequencePattern.h"
#include "model/event/SequenceEventFactory.h"

SequencePattern::~SequencePattern() {
    clear();
}

void SequencePattern::copy(SequencePattern* sourcePattern) {
    clear();
    for(int i = 0; i < sourcePattern->getEvents().size(); i++) {
        SequenceTickEvents* sourceTickEvents = sourcePattern->getTickEvents(i);
        if(sourceTickEvents != NULL) {
            SequenceTickEvents* tickEvents = new SequenceTickEvents(sourceTickEvents);
            setTickEvents(i, tickEvents);
        }
    }
}

void SequencePattern::addEvent(uint8_t index, SequenceEvent* event) {
    while(events.size() <= index) {
        events.add(NULL);
    }
    SequenceTickEvents* tickEvents = events.get(index);
    if(tickEvents == NULL) {
        tickEvents = new SequenceTickEvents();
        events.set(index, tickEvents);
    }

    tickEvents->addEvent(event);
}

void SequencePattern::deleteEvent(uint8_t tickIndex, uint8_t eventIndex) {
    SequenceTickEvents* tickEvents = events.get(tickIndex);
    if(tickEvents != NULL) {
        tickEvents->deleteEvent(eventIndex);
        if(tickEvents->getSize() == 0) {
            deleteTickEvents(tickIndex);
        }
    }
}

void SequencePattern::setTickEvents(uint8_t index, SequenceTickEvents* tickEvents) {
    while(events.size() <= index) {
        events.add(NULL);
    }
    if(events.get(index) != NULL) {
        delete events.get(index);
    }
    events.set(index, tickEvents);
}

void SequencePattern::deleteTickEvents(uint8_t index) {
    SequenceTickEvents* tickEvents = events.get(index);
    if(tickEvents != NULL) {
        events.set(index, NULL);
        delete tickEvents;
    }
}

void SequencePattern::clear() {
    for(int i = 0; i < events.size(); i++) {
        SequenceTickEvents* tickEvents = events.get(i);
        if(tickEvents != NULL) {
            delete tickEvents;
        }
    }
    events.clear();
}

void SequencePattern::serialize(JsonObject doc) {
    doc["id"] = id;
    JsonArray docTicks = doc.createNestedArray("ticks");
    for(int i = 0; i < events.size(); i++) {
        if(events[i] != NULL) {
            JsonObject docTick = docTicks.createNestedObject();
            docTick["pos"] = i;
            JsonArray docEvents = docTick.createNestedArray("events");
            events[i]->serialize(docEvents);
        }
    }
}

void SequencePattern::deserialize(JsonObject doc) {
    id = doc["id"];

    // old version
    JsonArray docEvents = doc["events"];
    for(JsonObject docEvent : docEvents) {
        int pos = docEvent["pos"];
        SequenceEvent* event = SequenceEventFactory::create(docEvent["type"]);
        addEvent(pos, event);
        event->deserialize(docEvent);
    }

    //new version
    JsonArray docTicks = doc["ticks"];
    for(JsonObject docTick : docTicks) {
        int pos = docTick["pos"];
        SequenceTickEvents* tickEvents = new SequenceTickEvents();
        setTickEvents(pos, tickEvents);
        tickEvents->deserialize(docTick["events"]);
    }
}
