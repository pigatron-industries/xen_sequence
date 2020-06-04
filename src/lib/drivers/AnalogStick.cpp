#include "AnalogStick.h"

#include <Arduino.h>

AnalogStick::AnalogStick(uint8_t _stickXPin, uint8_t _stickYPin, int _pressTime, int _repeatPressTime) :
    stickXPin(_stickXPin),
    stickYPin(_stickYPin),
    pressTime(_pressTime),
    repeatPressTime(_repeatPressTime) {
}

bool AnalogStick::update() {
    pushedLeft = false;
    pushedRight = false;
    pushedUp = false;
    pushedDown = false;

    xValue = analogRead(stickXPin);
    yValue = analogRead(stickYPin);

    if(xValue < xLeftThreshold || xValue > xRightThreshold) {
        if(xTimer.isFinished()) {
            xTimer.start(repeatPressTime);
            if(xValue < xLeftThreshold) {
                pushedLeft = true;
            } else {
                pushedRight = true;
            }
        }
        if(!xTimer.isRunning()) {
            xTimer.start(pressTime);
        }
    } else {
        xTimer.stop();
    }

    if(yValue < yDownThreshold || yValue > yUpThreshold) {
        if(yTimer.isFinished()) {
            yTimer.start(repeatPressTime);
            if(yValue < yDownThreshold) {
                pushedDown = true;
            } else {
                pushedUp = true;
            }
        }
        if(!yTimer.isRunning()) {
            yTimer.start(pressTime);
        }
    } else {
        yTimer.stop();
    }

    return pushedUp || pushedDown || pushedLeft || pushedRight;
}
