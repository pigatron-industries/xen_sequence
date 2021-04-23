#ifndef SequenceEvent_h
#define SequenceEvent_h

#include <inttypes.h>
#include <ArduinoJson.h>
#include "model/midi/CompiledEvents.h"

enum EventType {
    NOTE_EVENT,
    CONTROL_EVENT
};

class SequenceEvent {

public:
    SequenceEvent(EventType eventType) { this->eventType = eventType; }
    virtual ~SequenceEvent() {}
    virtual SequenceEvent* clone() const = 0;
    EventType getEventType() { return eventType; }

    virtual bool matchMessage(const MidiMessage& message) = 0;

    virtual void compile(CompiledEvents& messages, uint8_t channel) = 0;
    virtual void serialize(JsonObject doc) = 0;
    virtual void deserialize(JsonObject doc) = 0;

private:
    EventType eventType;

};

#endif
