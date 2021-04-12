#ifndef ControlEvent_h
#define ControlEvent_h

#include <inttypes.h>
#include <ArduinoJson.h>
#include "SequenceEvent.h"

enum MidiControl {
    C1_MODULATION,
    C2_BREATH,
    C7_VOLUME
};

class ControlEvent : public SequenceEvent {

public:

    ControlEvent();
    virtual SequenceEvent* clone() const;

    void setControl(uint8_t control) { this->control = control; }
    void setStart(uint8_t start) { this->start = start; }
    void setValue(uint16_t value) { this->value = value; }

    uint8_t getControl() { return control; }
    uint8_t getStart() { return start; }
    uint16_t getValue() { return value; }

    virtual void compile(CompiledEvents& messages, uint8_t channel);
    virtual void serialize(JsonObject doc);
    virtual void deserialize(JsonObject doc);

private:
    uint8_t control = 1; // 0 - 31
    uint8_t start = 0;
    uint16_t value = 0; // 14 bit value

};

#endif
