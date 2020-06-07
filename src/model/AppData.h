#ifndef AppData_h
#define AppData_h

#include "Sequence.h"


class AppData {

public:
    Sequence& getSequence() { return sequence; }
    LinkedList<SequencePattern*>& getPatterns() { return patterns; }

    SequencePattern* newPattern();

    SequenceBar* getBar(int index);
    SequenceBar* newBar(int index);

    SequencePattern* getPatternById(uint8_t id);
    SequencePattern* getPattern(uint16_t barIndex, uint8_t channel);

    void populateTestData();

private:
    Sequence sequence;
    LinkedList<SequencePattern*> patterns;

    uint8_t getUnusedPatternId();

};

#endif
