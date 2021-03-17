#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "Rotary.h"

class RotaryEncoder {

public:
    RotaryEncoder(uint8_t pin1, uint8_t pin2) :
        rotary(pin1, pin2) {
        encoderPtr = this;
        attachInterrupt(pin1, RotaryEncoder::interruptCallback, CHANGE);
        attachInterrupt(pin2, RotaryEncoder::interruptCallback, CHANGE);
    }

    static void interruptCallback();

    bool update() {
        movement = position;
        position = 0; 
        return movement != 0;
    }

    long getMovement() {
        return movement;
    }

private:
    static RotaryEncoder* encoderPtr;

    Rotary rotary;
    long position = 0;
    long movement = 0;

};

#endif
