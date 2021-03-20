#include "EventOutputService.h"

EventOutputService::EventOutputService() {
}

void EventOutputService::init(MidiOutputService* midiOutputService) {
    this->midiOutputService = midiOutputService;
}

void EventOutputService::event(uint8_t channel, uint16_t pulseCount, SequenceEvent* event) {
    CompiledEvent& compiledEvent = event->getCompiledEvent();
    if(pulseCount == 0) {
        compiledEvent.reset();
    }

    MidiMessage* message;
    while((message = compiledEvent.getNextMessageAtPulse(pulseCount)) != NULL) {
        midiOutputService->sendMessage(*message);
    }
}

void EventOutputService::system(uint8_t command) {
    MidiMessage message = MidiMessage(command);
    midiOutputService->sendMessage(message);
}
