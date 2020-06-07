#ifndef SequenceBar_h
#define SequenceBar_h

#include "SequencePattern.h"

#define SEQUENCE_CHANNELS 8

class SequenceBar {

public:
    SequencePattern* getPattern(uint8_t channel) { return patterns[channel]; }
    void setPattern(uint8_t channel, SequencePattern* pattern) { patterns[channel] = pattern; }

private:
    SequencePattern* patterns[SEQUENCE_CHANNELS];

};

#endif
