#ifndef Clock_h
#define Clock_h

#include <inttypes.h>

#include "lib/drivers/Timer.h"

#define PULSES_PER_TICK 24

class Clock {

public:
    Clock();
    bool update();
    bool tick();
    void stop();
    void start();
    void reset();
    void setTicksPerMinute(float tpm);
    void setPulsesPerTick(uint16_t pulsesPerTick);
    uint16_t getPulseCount() { return pulseCount; }

private:
    float ticksPerMinute;
    uint16_t pulsesPerTick = PULSES_PER_TICK;
    long pulseTime;

    Timer clockTimer;
    uint16_t pulseCount;

    bool running;

};


#endif
