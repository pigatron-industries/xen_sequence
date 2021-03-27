#ifndef SequenceEventList_h
#define SequenceEventList_h

#include <LinkedList.h>
#include <inttypes.h>
#include <ArduinoJson.h>

#include "SequenceEvent.h"

class SequenceTickEvents {

public:
    SequenceTickEvents() {}
    SequenceTickEvents(SequenceTickEvents* tickEvents);
    ~SequenceTickEvents();

    SequenceEvent* getEvent(int index) { return events.get(index); }
    int getSize() { return events.size(); }

    void addEvent(SequenceEvent* event);
    void deleteEvent(int index);

    void serialize(JsonArray doc);
    void deserialize(JsonArray doc);

private:
    LinkedList<SequenceEvent*> events;

    void copy(SequenceTickEvents* tickEvents);

};

#endif
