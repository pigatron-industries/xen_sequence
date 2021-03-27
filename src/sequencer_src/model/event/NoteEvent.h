#ifndef NoteEvent_h
#define NoteEvent_h

#include <inttypes.h>
#include <ArduinoJson.h>
#include "SequenceEvent.h"

class NoteEvent : public SequenceEvent {

public:
    NoteEvent();
    virtual SequenceEvent* clone() const;

    void setStart(uint8_t start) { this->start = start; }
    void setStop(uint8_t stop) { this->stop = stop; }
    void setPitch(uint8_t pitch) { this->pitch = pitch; }
    void setVelocity(uint8_t velocity) { this->velocity = velocity; }

    uint8_t getStart() { return start; }
    uint8_t getStop() { return stop; }
    uint8_t getPitch() { return pitch; }
    uint8_t getVelocity() { return velocity; }

    virtual void compile(CompiledEvents& messages, uint8_t channel);
    virtual void serialize(JsonObject doc);
    virtual void deserialize(JsonObject doc);


private:
    EventType eventType;
    uint8_t start = 0;
    uint8_t stop;
    uint8_t pitch;
    uint8_t velocity;

};

#endif
