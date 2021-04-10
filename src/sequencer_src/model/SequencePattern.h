#ifndef SequencePattern_h
#define SequencePattern_h

#include <LinkedList.h>
#include <inttypes.h>
#include <ArduinoJson.h>

#include "SequenceTickEvents.h"

#define MAX_PATTERN_ID 255

class SequencePattern {

public:
    SequencePattern(uint8_t _id) { id = _id; }
    ~SequencePattern();

    void copy(SequencePattern* event);

    uint8_t getId() { return id; }
    LinkedList<SequenceTickEvents*>& getEvents() { return events; }
    SequenceTickEvents* getTickEvents(uint8_t index) { return events.get(index); };
    void addEvent(uint8_t index, SequenceEvent* event);
    void deleteEvent(uint8_t tickIndex, uint8_t eventIndex);
    void setTickEvents(uint8_t index, SequenceTickEvents* event);
    void deleteTickEvents(uint8_t index);
    void clear();

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

private:
    uint8_t id;
    LinkedList<SequenceTickEvents*> events;

};

#endif
