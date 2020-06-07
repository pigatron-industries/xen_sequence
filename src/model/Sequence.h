#ifndef Sequence_h
#define Sequence_h

#include "SequenceBar.h"
#include "SequenceChannel.h"

class Sequence {

public:
    LinkedList<SequenceBar*>& getBars() { return bars; }
    SequenceBar* getBar(uint16_t index) { return bars.get(index); }
    SequenceChannel& getChannel(uint8_t index) { return channels[index]; }

private:
    LinkedList<SequenceBar*> bars;
    SequenceChannel channels[SEQUENCE_CHANNELS];

};

#endif
