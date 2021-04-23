#include "NoteEvent.h"

NoteEvent::NoteEvent() : SequenceEvent(EventType::NOTE_EVENT) {
    start = 0;
    stop = 48;
    pitch = 64;
    velocity = 64;
}

SequenceEvent* NoteEvent::clone() const {
    NoteEvent* event = new NoteEvent();
    event->start = start;
    event->stop = stop;
    event->pitch = pitch;
    event->velocity = velocity;
    return event;
}

bool NoteEvent::matchMessage(const MidiMessage& message) {
    return message.command == COMMAND_NOTEON;
}

void NoteEvent::compile(CompiledEvents& messages, uint8_t channel) {
    uint8_t startPulse = start;
    messages.add(new MidiMessage(startPulse, channel, COMMAND_NOTEON, pitch, velocity));
    uint8_t stopPulse = stop;
    messages.add(new MidiMessage(stopPulse, channel, COMMAND_NOTEOFF, pitch, 0));
}

void NoteEvent::serialize(JsonObject doc) {
    doc["start"] = start;
    doc["stop"] = stop;
    doc["pitch"] = pitch;
    doc["velocity"] = velocity;
}

void NoteEvent::deserialize(JsonObject doc) {
    start = doc["start"];
    stop = doc["stop"];
    pitch = doc["pitch"];
    velocity = doc["velocity"];
}