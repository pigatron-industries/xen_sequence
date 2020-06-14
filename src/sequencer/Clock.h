#ifndef Clock_h
#define Clock_h

#include <inttypes.h>

#include "../lib/drivers/Timer.h"


class Clock {

public:
    Clock();
    bool update();
    bool tick();
    void stop();
    void start();
    void reset();
    void setTicksPerMinute(float tpm);

private:
    float ticksPerMinute;
    uint16_t pulsesPerTick = 96;
    long pulseTime;

    Timer clockTimer;
    uint16_t pulseCount;

    bool running;

};


#endif
