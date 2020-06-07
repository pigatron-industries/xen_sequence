#ifndef SequencePattern_h
#define SequencePattern_h

#include <LinkedList.h>
#include <inttypes.h>

#include "SequenceEvent.h"

#define MAX_PATTERN_ID 255

class SequencePattern {

public:
    SequencePattern(uint8_t _id) { id = _id; }
    uint8_t getId() { return id; }
    LinkedList<SequenceEvent*>& getEvents() { return events; }
    SequenceEvent* getEvent(uint8_t index) { return events.get(index); };
    void addEvent(uint8_t index, SequenceEvent* event);

private:
    uint8_t id;
    LinkedList<SequenceEvent*> events;

};

#endif
