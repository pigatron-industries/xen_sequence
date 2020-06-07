#ifndef Sequence_h
#define Sequence_h

#include "SequenceBar.h"

class Sequence {

public:
    LinkedList<SequenceBar*>& getBars() { return bars; }
    SequenceBar* getBar(uint16_t index) { return bars.get(index); }

private:
    LinkedList<SequenceBar*> bars;

};

#endif
