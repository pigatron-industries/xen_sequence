#ifndef EventOutputService_h
#define EventOutputService_h

#include <inttypes.h>
#include "midi/MidiOutputService.h"
#include "../model/SequenceEvent.h"

class EventOutputService {

public:
    EventOutputService(MidiOutputService& _midiOutputService);
    void event(uint8_t channel, uint16_t pulseCount, SequenceEvent* event);

private:
    MidiOutputService& midiOutputService;

};


#endif
