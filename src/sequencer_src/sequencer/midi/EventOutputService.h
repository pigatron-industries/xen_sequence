#ifndef EventOutputService_h
#define EventOutputService_h

#include <inttypes.h>
#include "MidiOutputService.h"
#include "model/SequenceTickEvents.h"

class EventOutputService {

public:
    EventOutputService();
    void init(MidiOutputService* midiOutputService);
    void event(uint8_t channel, uint16_t pulseCount, SequenceTickEvents* tickEvents);
    void system(uint8_t command);

private:
    MidiOutputService* midiOutputService;

};


#endif
