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
        event->compile(messages, channel);
    }

    messages.messages.sort(EventCompiler::comparator);

    tickEvents->setCompiled(true);
}

void EventCompiler::clearCompiledEvent(CompiledEvents& event) {
    while(event.messages.size() > 0) {
        MidiMessage* message = event.messages.pop();
        delete message;
    }
}

int EventCompiler::comparator(MidiMessage*& m1, MidiMessage*& m2) {
    return m1->pulse == m2->pulse ? 0 : m1->pulse > m2->pulse ? 1 : -1;
}