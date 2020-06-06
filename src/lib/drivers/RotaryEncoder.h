#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Encoder.h>

class RotaryEncoder {

public:
    RotaryEncoder(uint8_t pin1, uint8_t pin2) :
        encoder(pin1, pin2) {
    }

    bool update() {
        rawMovement += encoder.readAndReset();
        if(rawMovement != 0 && rawMovement%4 == 0) {
            movement = rawMovement/4;
            rawMovement = 0;
            return true;
        } else {
            return false;
        }
    }

    long getMovement() { return movement; }

private:
    Encoder encoder;
    long rawMovement;
    long movement;

};

#endif
