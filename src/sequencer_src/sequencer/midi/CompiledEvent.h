#ifndef CompiledEvent_h
#define CompiledEvent_h

#include <inttypes.h>
#include <LinkedList.h>

#include "MidiMessage.h"

class CompiledEvent {

public:
    uint8_t pointerIndex = 0;
    LinkedList<MidiMessage*> messages;

    void reset() { pointerIndex = 0; }
    MidiMessage* getNextMessageAtPulse(uint8_t pulse) {
        if(pointerIndex >= messages.size()) {
            return NULL;
        } else {
            MidiMessage* message = messages.get(pointerIndex);
            if(message->pulse == pulse) {
                pointerIndex++;
                return message;
            } else {
                return NULL;
            }
        }
    }

};

#endif
