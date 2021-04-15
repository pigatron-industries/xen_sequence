#ifndef EventCompiler_h
#define EventCompiler_h

#include <inttypes.h>

#include "model/SequenceTickEvents.h"

class EventCompiler {

public:
    EventCompiler();
    void compileTickEvents(SequenceTickEvents* event, uint8_t channel);

private:
    void clearCompiledEvent(CompiledEvents& event);
    static int comparator(MidiMessage*& m1, MidiMessage*& m2);

};

#endif
