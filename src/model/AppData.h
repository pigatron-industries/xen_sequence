#ifndef AppData_h
#define AppData_h

#include "Sequence.h"


class AppData {

public:
    Sequence& getSequence() { return sequence; }
    LinkedList<SequencePattern*>& getPatterns() { return patterns; }

    SequencePattern* newPattern();
    uint8_t getUnusedPatternId();
    SequencePattern* getPatternById(uint8_t id);

    void populateTestData();

private:
    Sequence sequence;
    LinkedList<SequencePattern*> patterns;

};

#endif
