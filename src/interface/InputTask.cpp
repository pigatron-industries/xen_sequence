#include "InputTask.h"

#include <Arduino.h>
#include "InterfaceEvent.h"

#include "../hwconfig.h"

uint8_t rowPins[KEY_ROWS] = KEY_ROW_PINS;
uint8_t colPins[KEY_COLS] = KEY_COL_PINS;
char keys[KEY_ROWS][KEY_COLS] = {
    {KEY_BACK, KEY_ADD_DEL, KEY_PLAY_STOP, KEY_RECORD}
};

InputTask::InputTask(InterfaceController& _interface) :
    interface(_interface),
    analogStick(STICK_X_PIN, STICK_Y_PIN),
    analogStickSwitch(STICK_SWITCH_PIN),
    encoder(ENCODER_PIN1, ENCODER_PIN2),
    encoderSwitch(ENCODER_SWITCH_PIN),
    keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS) {
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

    char key = keypad.getKey();
    if (key != NO_KEY) {
        interface.handleEvent(InterfaceEvent(static_cast<InterfaceEventType>(key)));
    }
}
