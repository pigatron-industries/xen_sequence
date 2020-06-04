#include "InputTask.h"

#include <Arduino.h>
#include "Events.h"


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
            interface.handleEvent(STICK_LEFT);
        } else if(analogStick.wasPushedRight()) {
            Serial.println("Right");
            interface.handleEvent(STICK_RIGHT);
        }
        if(analogStick.wasPushedUp()) {
            Serial.println("Up");
            interface.handleEvent(STICK_UP);
        } else if(analogStick.wasPushedDown()) {
            Serial.println("Down");
            interface.handleEvent(STICK_DOWN);
        }
    }
}
