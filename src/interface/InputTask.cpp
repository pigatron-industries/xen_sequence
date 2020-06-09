#include "InputTask.h"

#include <Arduino.h>
#include "Events.h"

#include "../hwconfig.h"

#define KEY_ROWS 1
#define KEY_COLS 4

char keys[KEY_ROWS][KEY_COLS] = {
    {KEY_BACK, KEY_ADD_DEL, KEY_COPY, KEY_PASTE}
};

uint8_t rowPins[KEY_ROWS] = {28};
uint8_t colPins[KEY_COLS] = {24, 25, 26, 27};


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
            interface.handleEvent(Event::STICK_LEFT);
        } else if(analogStick.wasPushedRight()) {
            interface.handleEvent(Event::STICK_RIGHT);
        }
        if(analogStick.wasPushedUp()) {
            interface.handleEvent(Event::STICK_UP);
        } else if(analogStick.wasPushedDown()) {
            interface.handleEvent(Event::STICK_DOWN);
        }
    }

    if(analogStickSwitch.update()) {
        if(analogStickSwitch.fell()) {
            interface.handleEvent(Event::STICK_PRESS);
        }
    }

    if(encoder.update()) {
        if(encoder.getMovement() > 0) {
            interface.handleEvent(Event::DATA_INCREMENT);
        } else {
            interface.handleEvent(Event::DATA_DECREMENT);
        }
    }

    if(encoderSwitch.update()) {
        if(encoderSwitch.fell()) {
            interface.handleEvent(Event::DATA_PRESS);
        }
    }

    char key = keypad.getKey();
    if (key != NO_KEY) {
        Serial.println(static_cast<int>(key));
        interface.handleEvent(static_cast<Event>(key));
    }
}
