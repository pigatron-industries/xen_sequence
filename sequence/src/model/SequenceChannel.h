#ifndef SequenceChannel_h
#define SequenceChannel_h

#include "SequencePattern.h"

class SequenceChannel {

public:
    LinkedList<SequencePattern*>& getPatterns() { return patterns; };

private:
    LinkedList<SequencePattern*> patterns;

};

#endif
