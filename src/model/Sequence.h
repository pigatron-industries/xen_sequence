#ifndef Sequence_h
#define Sequence_h

#include "SequenceBar.h"
#include "SequenceChannel.h"

class Sequence {

public:
    LinkedList<SequenceBar*>& getBars() { return bars; }
    SequenceChannel& getChannel(uint8_t index) { return channels[index]; }
    SequenceBar* getBar(uint16_t index) { return bars.get(index); }
    void addBar(uint16_t index, SequenceBar* bar) { bars.set(index, bar); }

private:
    LinkedList<SequenceBar*> bars;
    SequenceChannel channels[SEQUENCE_CHANNELS];

};

#endif
