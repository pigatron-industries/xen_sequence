#include "EventOutputService.h"

EventOutputService::EventOutputService(MidiOutputService& _midiOutputService) :
    midiOutputService(_midiOutputService) {
}

void EventOutputService::event(uint8_t channel, uint16_t pulseCount, SequenceEvent* event) {
    if(event->getFlag(SequenceEventFlag::NOTE_ON)) {
        
    }
}
