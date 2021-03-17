#include "RotaryEncoder.h"

RotaryEncoder* RotaryEncoder::encoderPtr = NULL;

void RotaryEncoder::interruptCallback() {
    unsigned char result = encoderPtr->rotary.process();
    if (result == DIR_CW) {
        encoderPtr->position++;
    } else if (result == DIR_CCW) {
        encoderPtr->position--;
    }
}