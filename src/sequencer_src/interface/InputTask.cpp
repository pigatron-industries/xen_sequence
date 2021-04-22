#include "InputTask.h"

#include <Arduino.h>
#include "InterfaceEvent.h"

#include "hwconfig.h"
#include "lib/util/debug.h"

InputTask::InputTask(InterfaceController& _interface) :
    interface(_interface),
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
            interface.handleEvent(InterfaceEvent(STICK_LEFT, EVENT_KEY_PRESSED));
        } else if(analogStick.wasPushedRight()) {
            interface.handleEvent(InterfaceEvent(STICK_RIGHT, EVENT_KEY_PRESSED));
        }
        if(analogStick.wasPushedUp()) {
            interface.handleEvent(InterfaceEvent(STICK_UP, EVENT_KEY_PRESSED));
        } else if(analogStick.wasPushedDown()) {
            interface.handleEvent(InterfaceEvent(STICK_DOWN, EVENT_KEY_PRESSED));
        }
    }

    if(analogStickSwitch.update()) {
        if(analogStickSwitch.fell()) {
            interface.handleEvent(InterfaceEvent(STICK_PRESS, EVENT_KEY_PRESSED));
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
            interface.handleEvent(InterfaceEvent(DATA_PRESS, EVENT_KEY_PRESSED));
        }
    }

    if(Hardware::keyboard.update()) {
        for(int i = 0; i < Hardware::keyboard.getNumKeys(); i++) {
            Key key = Hardware::keyboard.getKeys()[i];
            if(key.stateChanged && key.kstate == PRESSED) {

                interface.handleEvent(InterfaceEvent(static_cast<InterfaceEventType>(key.kchar), function ? EVENT_KEY_FUNCTION : EVENT_KEY_PRESSED));
                if(key.kchar == InterfaceEventType::KEY_FUNCTION) {
                    function = true;
                    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_FUNCTION, LedColour::GREEN);
                }

            } else if (key.stateChanged && key.kstate == RELEASED) {

                if(key.kchar == InterfaceEventType::KEY_FUNCTION) {
                    function = false;
                    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_FUNCTION, LedColour::OFF);
                }
                interface.handleEvent(InterfaceEvent(static_cast<InterfaceEventType>(key.kchar), EVENT_KEY_RELEASED));

            }
        }
    }

    Hardware::midiInputService.update();

    interface.update();
}
