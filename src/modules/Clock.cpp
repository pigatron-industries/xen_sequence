#include "Clock.h"

Clock::Clock() {
    setTicksPerMinute(120);
    pulseCount = 0;
    running = false;
}

void Clock::setTicksPerMinute(float tpm) {
    ticksPerMinute = tpm;
    pulseTime = ((60/ticksPerMinute)*1000000)/pulsesPerTick;
    clockTimer.setWaitTime(pulseTime);
}

bool Clock::update() {
    if(running && !clockTimer.isRunning()) {
        clockTimer.start();
        pulseCount++;
        if(pulseCount == pulsesPerTick) {
            pulseCount = 0;
        }
        return true;
    }

    return false;
}

bool Clock::tick() {
    return pulseCount == 0;
}

void Clock::stop() {
    running = false;
}

void Clock::start() {
    running = true;
}

void Clock::reset() {
    pulseCount = 0;
}
