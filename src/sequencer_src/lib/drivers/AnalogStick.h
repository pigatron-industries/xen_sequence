#ifndef AnalogStick_h
#define AnalogStick_h

#include <inttypes.h>
#include "Timer.h"

#define THRESHOLD 300
#define STICK_MAX_VALUE 1024

class AnalogStick {

public:
    AnalogStick(uint8_t _stickXPin, uint8_t _stickYPin, int _pressTime = 100000, int _repeatPressTime = 400000);
    bool update();

    bool wasPushedLeft() { return pushedLeft; };
    bool wasPushedRight() { return pushedRight; };
    bool wasPushedUp() { return pushedUp; };
    bool wasPushedDown() { return pushedDown; };

private:
    uint8_t stickXPin;
    uint8_t stickYPin;

    int xValue;
    int yValue;

    bool pushedLeft;
    bool pushedRight;
    bool pushedUp;
    bool pushedDown;

    int xLeftThreshold = THRESHOLD;
    int xRightThreshold = STICK_MAX_VALUE - THRESHOLD;
    int yDownThreshold = THRESHOLD;
    int yUpThreshold = STICK_MAX_VALUE - THRESHOLD;
    int pressTime;
    int repeatPressTime;

    Timer xTimer;
    Timer yTimer;

};

#endif
