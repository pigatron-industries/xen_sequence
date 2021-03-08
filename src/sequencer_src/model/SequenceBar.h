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
        empty = true;
    }

    SequencePattern* getPattern(uint8_t channel) { return patterns[channel]; }
    uint8_t getLength() { return length; }
    uint16_t getSpeedDiff() { return speedDiff; }
    uint8_t getSpeedMult() { return speedMult; }
    bool isEmpty() { return empty; }

    void setPattern(uint8_t channel, SequencePattern* pattern) { patterns[channel] = pattern; empty = false; }
    void setLength(uint16_t length) { this->length = length; }
    void setSpeedDiff(uint16_t speedDiff) { this->speedDiff = speedDiff; }
    void setSpeedMult(uint8_t speedMult) { this->speedMult = speedMult; }

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

private:
    SequencePattern* patterns[SEQUENCE_CHANNELS];
    uint8_t length = 16;
    uint16_t speedDiff = 0;
    uint8_t speedMult = 1;
    bool empty;

};

#endif
