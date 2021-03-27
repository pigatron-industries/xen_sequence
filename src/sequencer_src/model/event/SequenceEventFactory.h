#ifndef SequenceEventFactory_h
#define SequenceEventFactory_h

#include <inttypes.h>
#include <ArduinoJson.h>
#include "SequenceEvent.h"

class SequenceEventFactory {
public:
    static SequenceEvent* create(EventType eventType);
};

#endif
