#ifndef AppData_h
#define AppData_h

#include "Sequence.h"


class AppData {

public:
    static constexpr float DATA_VERSION = 0.1;
    static AppData data;

    Sequence& getSequence() { return sequence; }
    LinkedList<SequencePattern*>& getPatterns() { return patterns; }

    SequenceBar* getBar(int index);
    SequenceBar* newBar(int index);

    SequencePattern* getPatternById(uint8_t id);
    SequencePattern* getPattern(uint16_t barIndex, uint8_t channel);
    SequencePattern* newPattern();
    SequencePattern* newPattern(uint16_t barIndex, uint8_t channel);
    void setPattern(uint16_t barIndex, uint8_t channel, SequencePattern* pattern);

    SequenceEvent* newEvent(uint8_t tick, SequencePattern* pattern);
    SequenceEvent* newEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);
    SequenceEvent* newEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, SequenceEvent* copy);
    void deleteEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);

    SequenceChannel& getChannel(uint8_t index);

    void clear();

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

    void populateTestData();

private:
    AppData();

    Sequence sequence;
    LinkedList<SequencePattern*> patterns;

    uint8_t getUnusedPatternId();

};

#endif
