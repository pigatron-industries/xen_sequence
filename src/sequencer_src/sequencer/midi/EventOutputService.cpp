#include "EventOutputService.h"

EventOutputService::EventOutputService() {
}

void EventOutputService::init(MidiOutputService* midiOutputService) {
    this->midiOutputService = midiOutputService;
}

void EventOutputService::event(uint8_t channel, uint16_t pulseCount, SequenceTickEvents* tickEvents) {
    CompiledEvents& compiledEvents = tickEvents->getCompiledEvents();
    if(pulseCount == 0) {
        compiledEvents.reset();
    }

    MidiMessage* message;
    while((message = compiledEvents.getNextMessageAtPulse(pulseCount)) != NULL) {
        midiOutputService->sendMessage(*message);
    }
}

void EventOutputService::system(uint8_t command) {
    MidiMessage message = MidiMessage(command);
    midiOutputService->sendMessage(message);
}
