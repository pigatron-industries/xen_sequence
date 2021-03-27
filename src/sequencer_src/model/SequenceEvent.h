#ifndef SequenceEvent_h
#define SequenceEvent_h

#include <inttypes.h>
#include <ArduinoJson.h>

enum SequenceEventFlag {
    NOTE_ON = 1,
    NOTE_OFF = 2,
    CONTROL1 = 4,
    CONTROL2 = 8
};


class SequenceEvent {

public:
    SequenceEvent();
    SequenceEvent(SequenceEvent* event);
    void copy(SequenceEvent* event);

    void setFlag(SequenceEventFlag flag, bool value) {
        if(value) {
            eventFlags |= flag;
        } else {
            eventFlags &= ~flag;
        }
    }

    void setPitch(uint8_t _pitch) { pitch = _pitch; }
    void setVelocity(uint8_t _velocity) { velocity = _velocity; }
    void setGate(uint8_t _gate) { gate = _gate; }
    void setDelay(uint8_t _delay) { delay = _delay; }

    bool getFlag(SequenceEventFlag flag) { return eventFlags & flag; }
    uint8_t getPitch() { return pitch; }
    uint8_t getVelocity() { return velocity; }
    uint8_t getGate() { return gate; }
    uint8_t getDelay() { return delay; }

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

private:
    uint8_t eventFlags = NOTE_ON | NOTE_OFF;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t gate = 48;
    uint8_t delay;

};

#endif
