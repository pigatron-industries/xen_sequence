#include "KeyboardLedMatrix.h"

#include <Arduino.h>

#define COMMAND_OFF 0xF0
#define COMMAND_ON 0xFF

KeyboardLedMatrix::KeyboardLedMatrix() {
    Serial8.begin(9600);
}

void KeyboardLedMatrix::setLedValueAt(uint8_t x, uint8_t y, bool value) {
    values[x + y*X_LED_SIZE] = value;
    Serial8.write(value ? COMMAND_ON : COMMAND_OFF);
    Serial8.write(x);
    Serial8.write(y);
}
