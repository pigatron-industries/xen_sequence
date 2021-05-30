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

void Clock::setPulsesPerTick(uint16_t pulsesPerTick) { 
    this->pulsesPerTick = pulsesPerTick;
    pulseTime = ((60/ticksPerMinute)*1000000)/pulsesPerTick;
    clockTimer.setWaitTime(pulseTime);
}

bool Clock::update() {
    pulseCount++;
    if(pulseCount >= PULSES_PER_TICK) {
        pulseCount = 0;
    }
    return true;
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
