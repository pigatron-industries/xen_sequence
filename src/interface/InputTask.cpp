#include "InputTask.h"

#include <Arduino.h>
#include "Events.h"

#include "../hwconfig.h"

InputTask::InputTask(InterfaceController& _interface) :
    interface(_interface),
    analogStick(STICK_X_PIN, STICK_Y_PIN),
    analogStickSwitch(STICK_SWITCH_PIN),
    encoder(ENCODER_PIN1, ENCODER_PIN2),
    encoderSwitch(ENCODER_SWITCH_PIN) {
      pinMode(STICK_SWITCH_PIN, INPUT_PULLUP);
}

void InputTask::init() {
    Task::init();
}

void InputTask::execute() {
    if(analogStick.update()) {
        if(analogStick.wasPushedLeft()) {
            interface.handleEvent(STICK_LEFT);
        } else if(analogStick.wasPushedRight()) {
            interface.handleEvent(STICK_RIGHT);
        }
        if(analogStick.wasPushedUp()) {
            interface.handleEvent(STICK_UP);
        } else if(analogStick.wasPushedDown()) {
            interface.handleEvent(STICK_DOWN);
        }
    }

    if(analogStickSwitch.update()) {
        if(analogStickSwitch.fell()) {
            interface.handleEvent(STICK_PRESS);
        }
    }

    if(encoder.update()) {
        if(encoder.getMovement() > 0) {
            interface.handleEvent(DATA_INCREMENT);
        } else {
            interface.handleEvent(DATA_DECREMENT);
        }
    }

    if(encoderSwitch.update()) {
      if(encoderSwitch.fell()) {
          interface.handleEvent(DATA_PRESS);
      }
    }
}
