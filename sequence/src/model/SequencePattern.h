#ifndef SequencePattern_h
#define SequencePattern_h

#include <LinkedList.h>
#include <inttypes.h>

#include "SequenceEvent.h"

class SequencePattern {

public:
    uint8_t id;
    LinkedList<SequenceEvent*> events;
  
    SequencePattern(uint8_t _id) {
        id = _id;
    }

};

#endif
