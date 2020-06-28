#include "EventCompiler.h"

#include "MidiConstants.h"

#include <Arduino.h>

EventCompiler::EventCompiler() {
}

void EventCompiler::compileEvent(SequenceEvent* event, uint8_t channel) {
    Serial.println("compileEvent 1");
    clearCompiledEvent(event->getCompiledEvent());
Serial.println("compileEvent 2");
    if(event->getFlag(SequenceEventFlag::NOTE_ON)) {
        MidiMessage* message = new MidiMessage(event->getDelay(),
            channel, COMMAND_NOTEON, event->getPitch(), event->getVelocity());
        event->getCompiledEvent().messages.add(message);
    }
Serial.println("compileEvent 3");
    if(event->getFlag(SequenceEventFlag::NOTE_OFF)) {
        MidiMessage* message = new MidiMessage(event->getDelay() + event->getGate(),
            channel, COMMAND_NOTEOFF, event->getPitch(), 0);
        event->getCompiledEvent().messages.add(message);
    }
Serial.println("compileEvent 4");
    event->setCompiled();
}

void EventCompiler::clearCompiledEvent(CompiledEvent& event) {
    while(event.messages.size() > 0) {
        MidiMessage* message = event.messages.pop();
        delete message;
    }
}
