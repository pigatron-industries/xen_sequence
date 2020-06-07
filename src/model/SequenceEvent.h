#ifndef SequenceEvent_h
#define SequenceEvent_h

#include <inttypes.h>

enum SequenceEventType {
    NOTE,
    NOTE_ON,
    NOTE_OFF,
    CTRL
};

class SequenceEvent {

public:
    SequenceEventType eventType = NOTE;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t gate;
    uint8_t delay;

};

#endif
