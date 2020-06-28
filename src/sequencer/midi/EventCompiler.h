#ifndef EventCompiler_h
#define EventCompiler_h

#include <inttypes.h>

#include "../../model/SequenceEvent.h"

class EventCompiler {

public:
    EventCompiler();
    void compileEvent(SequenceEvent* event, uint8_t channel);

private:
    void clearCompiledEvent(CompiledEvent& event);

};

#endif
