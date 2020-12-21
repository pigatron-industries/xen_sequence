#ifndef MidiEventHandler_h
#define MidiEventHandler_h

#include "MidiMessage.h"

class MidiEventHandler {
    public:
        virtual void handleMidiEvent(MidiMessage message) = 0;
};

#endif
