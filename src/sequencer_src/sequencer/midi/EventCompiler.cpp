#include "EventCompiler.h"

#include "model/midi/MidiMessage.h"

#include <Arduino.h>

EventCompiler::EventCompiler() {
}

void EventCompiler::compileTickEvents(SequenceTickEvents* tickEvents, uint8_t channel) {
    CompiledEvents& messages = tickEvents->getCompiledEvents();
    clearCompiledEvent(messages);

    for(int i = 0 ; i < tickEvents->getSize(); i++) {
        SequenceEvent* event = tickEvents->getEvent(i);
        compileEvent(messages, event, channel);
    }

    tickEvents->setCompiled(true);
}

void EventCompiler::compileEvent(CompiledEvents& messages, SequenceEvent* event, uint8_t channel) {
    
    if(event->getFlag(SequenceEventFlag::NOTE_ON)) {
        // TODO decouple gate and delay times from pulse count
        uint8_t pulse = event->getDelay();
        MidiMessage* message = new MidiMessage(pulse,
            channel, COMMAND_NOTEON, event->getPitch(), event->getVelocity());
        messages.add(message);
    }

    if(event->getFlag(SequenceEventFlag::NOTE_OFF)) {
        uint8_t pulse = event->getDelay() + event->getGate();
        MidiMessage* message = new MidiMessage(pulse, channel, COMMAND_NOTEOFF, event->getPitch(), 0);
        messages.add(message);
    }
}

void EventCompiler::clearCompiledEvent(CompiledEvents& event) {
    while(event.messages.size() > 0) {
        MidiMessage* message = event.messages.pop();
        delete message;
    }
}
