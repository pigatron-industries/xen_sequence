#include "SequenceTickEvents.h"

SequenceTickEvents::~SequenceTickEvents() {
    //TODO delete all events
}

SequenceTickEvents::SequenceTickEvents(SequenceTickEvents* tickEvents) {
    copy(tickEvents);
}

void copy(SequenceTickEvents* tickEvents) {

}

void addEvent(SequenceEvent* event) {
    //TODO
}

void deleteEvent(int index) {
    //TODO
}

void serialize(JsonArray doc) {
    //TODO
}

void deserialize(JsonArray doc) {
    ///TODO
}
