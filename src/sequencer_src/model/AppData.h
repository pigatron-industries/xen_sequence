#ifndef AppData_h
#define AppData_h

#include "Sequence.h"


class AppData {

public:
    static constexpr float DATA_VERSION = 0.2;
    static AppData data;

    Sequence& getSequence() { return sequence; }
    LinkedList<SequencePattern*>& getPatterns() { return patterns; }

    SequenceBar* getBar(int index);
    SequencePattern* getPatternById(uint8_t id);
    SequencePattern* getPattern(uint16_t barIndex, uint8_t channel);
    SequenceChannel& getChannel(uint8_t index);
    SequenceTickEvents* getTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);

    uint16_t getAbsoluteSpeed(SequenceBar* bar);
    uint8_t getAbsoluteSpeedMult(SequenceBar* bar);

    void setPattern(uint16_t barIndex, uint8_t channel, SequencePattern* pattern);

    SequenceBar* newBar(int index);
    SequencePattern* newPattern();
    SequencePattern* newPattern(uint16_t barIndex, uint8_t channel);
    SequenceEvent* newEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, EventType eventType);
    SequenceTickEvents* newTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);
    SequenceTickEvents* newTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, SequenceTickEvents* copy);

    void deleteTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);
    void deleteEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, uint8_t eventIndex);

    SequencePattern* copyPattern(SequencePattern* sourcePattern);
    SequenceBar* copyBar(SequenceBar* sourceBar, int newBarIndex);
    void copyBarPatterns(SequenceBar* fromBar, SequenceBar* toBar);

    void clear();

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

    void populateTestData();

private:
    AppData();

    Sequence sequence;
    LinkedList<SequencePattern*> patterns;

    uint8_t getUnusedPatternId();
    SequencePattern* getOrCreatePattern(uint16_t barIndex, uint8_t channelIndex);

};

#endif
