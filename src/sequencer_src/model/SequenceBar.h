#ifndef SequenceBar_h
#define SequenceBar_h

#include "SequencePattern.h"

#define SEQUENCE_CHANNELS 8

class SequenceBar {

public:
    SequenceBar() {
        for(int i = 0; i < SEQUENCE_CHANNELS; i++) {
            patterns[i] = NULL;
        }
    }
    SequencePattern* getPattern(uint8_t channel) { return patterns[channel]; }
    void setPattern(uint8_t channel, SequencePattern* pattern) { patterns[channel] = pattern; }
    uint8_t getLength() { return length; }
    uint16_t getSpeed() { return speed; }
    void setLength(uint16_t _length) { length = _length; }
    void setSpeed(uint16_t _speed) { speed = _speed; }

    void serialize(JsonObject doc);

private:
    SequencePattern* patterns[SEQUENCE_CHANNELS];
    uint8_t length = 16;
    uint16_t speed = 120;

};

#endif
