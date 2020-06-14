#ifndef SequenceEvent_h
#define SequenceEvent_h

#include <inttypes.h>

enum SequenceEventFlag {
    NOTE_ON = 1,
    NOTE_OFF = 2,
    CTRL1 = 4,
    CTRL2 = 8
};


class SequenceEvent {

public:
    uint8_t eventFlags;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t gate;
    uint8_t delay;

    void setFlag(SequenceEventFlag flag, bool value) {
        if(value) {
            eventFlags |= flag;
        } else {
            eventFlags &= ~flag;
        }
    }

    bool getFlag(SequenceEventFlag flag) {
        return eventFlags & flag;
    }

};

#endif
