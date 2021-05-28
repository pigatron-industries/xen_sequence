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
    void deleteBar(uint16_t index);
    void clear();

    int getLength();
    uint16_t getSpeed() { return speed; }
    uint8_t getSpeedMult() { return speedMult; }

    void setSpeed(uint16_t speed) { this->speed = speed; }
    void setSpeedMult(uint8_t speedMult) { this->speedMult = speedMult; }

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

private:
    LinkedList<SequenceBar*> bars;
    SequenceChannel channels[SEQUENCE_CHANNELS];

    uint16_t speed = 120;
    uint8_t speedMult = 1;

};

#endif
