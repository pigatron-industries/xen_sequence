#include "InputTask.h"

#include <Arduino.h>


InputTask::InputTask(InterfaceController& _interface, uint8_t _stickXPin, uint8_t _stickYPin) :
    interface(_interface),
    analogStick(_stickXPin, _stickYPin) {
}

void InputTask::init() {
    Task::init();
}

void InputTask::execute() {
    if(analogStick.update()) {
        if(analogStick.wasPushedLeft()) {
            Serial.println("Left");
        } else if(analogStick.wasPushedRight()) {
            Serial.println("Right");
        }
        if(analogStick.wasPushedUp()) {
            Serial.println("Up");
        } else if(analogStick.wasPushedDown()) {
            Serial.println("Down");
        }
    }
}
