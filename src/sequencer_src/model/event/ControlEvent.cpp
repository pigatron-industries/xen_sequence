#include "ControlEvent.h"

ControlEvent::ControlEvent() : SequenceEvent(EventType::CONTROL_EVENT) {
    start = 0;
    value = 0;
}

SequenceEvent* ControlEvent::clone() const {
    ControlEvent* event = new ControlEvent();
    event->start = start;
    event->control = control;
    event->value = value;
    return event;
}

void ControlEvent::compile(CompiledEvents& messages, uint8_t channel) {
    uint8_t startPulse = start;
    messages.add(new MidiMessage(startPulse, channel, COMMAND_CONTROL_CHANGE, control, value));
    // TODO split into MSB and LSB
    //messages.add(new MidiMessage(startPulse, channel, COMMAND_CONTROL_CHANGE, control+32, valueLsb));
}

void ControlEvent::serialize(JsonObject doc) {
    doc["start"] = start;
    doc["control"] = control;
    doc["value"] = value;
}

void ControlEvent::deserialize(JsonObject doc) {
    start = doc["start"];
    control = doc["control"];
    value = doc["value"];
}