#ifndef Sequence_h
#define Sequence_h

#include "SequenceChannel.h"

#define SEQUENCE_CHANNELS 8

class Sequence {

public:
    SequenceChannel& getChannel(uint8_t index) { return channels[index]; }

private:
    SequenceChannel channels[SEQUENCE_CHANNELS];

    void extendChannels();

};

#endif
