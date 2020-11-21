#include "InputTask.h"

#include <Arduino.h>
#include "InterfaceEvent.h"

#include "../hwconfig.h"

InputTask::InputTask(InterfaceController& _interface, Keyboard& _keyboard) :
    interface(_interface),
    keyboard(_keyboard),
    analogStick(STICK_X_PIN, STICK_Y_PIN),
    analogStickSwitch(STICK_SWITCH_PIN),
    encoder(ENCODER_PIN1, ENCODER_PIN2),
    encoderSwitch(ENCODER_SWITCH_PIN) {
}

void InputTask::init() {
    Task::init();
}

void InputTask::execute() {
    if(analogStick.update()) {
        if(analogStick.wasPushedLeft()) {
            interface.handleEvent(InterfaceEvent(STICK_LEFT));
        } else if(analogStick.wasPushedRight()) {
            interface.handleEvent(InterfaceEvent(STICK_RIGHT));
        }
        if(analogStick.wasPushedUp()) {
            interface.handleEvent(InterfaceEvent(STICK_UP));
        } else if(analogStick.wasPushedDown()) {
            interface.handleEvent(InterfaceEvent(STICK_DOWN));
        }
    }

    if(analogStickSwitch.update()) {
        if(analogStickSwitch.fell()) {
            interface.handleEvent(InterfaceEvent(STICK_PRESS));
        }
    }

    if(encoder.update()) {
        if(encoder.getMovement() > 0) {
            interface.handleEvent(InterfaceEvent(DATA_INCREMENT, encoder.getMovement()));
        } else {
            interface.handleEvent(InterfaceEvent(DATA_DECREMENT, -encoder.getMovement()));
        }
    }

    if(encoderSwitch.update()) {
        if(encoderSwitch.fell()) {
            interface.handleEvent(InterfaceEvent(DATA_PRESS));
        }
    }

    if(keyboard.update()) {
        // Serial.println("================");
        for(int i = 0; i < keyboard.getNumKeys(); i++) {
            Key key = keyboard.getKeys()[i];
            if(key.stateChanged && key.kstate == PRESSED) {
                interface.handleEvent(InterfaceEvent(static_cast<InterfaceEventType>(key.kchar), EVENT_KEY_PRESSED));
            } else if (key.stateChanged && key.kstate == RELEASED) {
                interface.handleEvent(InterfaceEvent(static_cast<InterfaceEventType>(key.kchar), EVENT_KEY_RELEASED));
            }
        }
    }
}
