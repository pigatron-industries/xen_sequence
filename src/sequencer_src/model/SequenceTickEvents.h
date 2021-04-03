#ifndef SequenceTickEvents_h
#define SequenceTickEvents_h

#include <LinkedList.h>
#include <inttypes.h>
#include <ArduinoJson.h>

#include "event/SequenceEvent.h"
#include "midi/CompiledEvents.h"

class SequenceTickEvents {

public:
    SequenceTickEvents() {}
    SequenceTickEvents(SequenceTickEvents* sourceTickEvents);
    ~SequenceTickEvents();

    SequenceEvent* getEvent(int index);
    int getSize() { return events.size(); }

    void addEvent(SequenceEvent* event);
    void deleteEvent(int index);
    void clearEvents();

    CompiledEvents& getCompiledEvents() { return compiledEvents; }
    bool isCompiled() { return compiled; }
    void setCompiled(bool compiled) { this->compiled = compiled; }

    void serialize(JsonArray doc);
    void deserialize(JsonArray doc);

private:
    LinkedList<SequenceEvent*> events;
    CompiledEvents compiledEvents;
    bool compiled = false;

    void copy(SequenceTickEvents* sourceTickEvents);

};

#endif
