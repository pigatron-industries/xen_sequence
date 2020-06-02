#ifndef AppData_h
#define AppData_h

#include "Sequence.h"


class AppData {

public:
    Sequence sequence;
    LinkedList<SequencePattern*> patterns;

    uint8_t getUnusedPatternId();

    void populateTestData();

};

#endif
