#ifndef SequenceBar_h
#define SequenceBar_h

#include "SequencePattern.h"

#define SEQUENCE_CHANNELS 8

class SequenceBar {

public:
    SequencePattern* getPattern(uint8_t channel) { return patterns[channel]; }
    void setPattern(uint8_t channel, SequencePattern* pattern) { patterns[channel] = pattern; }
    uint8_t getLength() { return length; }
    uint8_t getSpeed() { return speed; }
    void setLength(uint8_t _length) { length = _length; }
    void setSpeed(uint8_t _speed) { speed = _speed; }

private:
    SequencePattern* patterns[SEQUENCE_CHANNELS];
    uint8_t length = 8;
    uint8_t speed = 120;

};

#endif
