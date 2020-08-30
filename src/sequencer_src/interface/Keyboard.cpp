#include "Keyboard.h"
#include "../hwconfig.h"

const LedColour LedColour::OFF = LedColour(0, 0, 0);
const LedColour LedColour::RED = LedColour(1, 0, 0);
const LedColour LedColour::GREEN = LedColour(0, 1, 0);
const LedColour LedColour::BLUE = LedColour(0, 0, 1);

uint8_t rowPins[KEY_ROWS] = KEY_ROW_PINS;
uint8_t colPins[KEY_COLS] = KEY_COL_PINS;
char keys[KEY_ROWS][KEY_COLS] = {
    {KEY_RECORD, KEY_PLAY_STOP, KEY_ADD_DEL, KEY_BACK}
};

Keyboard::Keyboard():
    keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS) {
}

char Keyboard::getKey() {
    return keypad.getKey();
}

void Keyboard::setKeyLed(InterfaceEventType key, LedColour colour) {
    for(int x = 0; x < KEY_ROWS; x++) {
        for(int y = 0; y < KEY_COLS; y++) {
            if(key == static_cast<InterfaceEventType>(keys[x][y])) {
                keyboardLedMatrix.setLedValueAt(y*3, x, colour.red);
                keyboardLedMatrix.setLedValueAt(y*3+1, x, colour.green);
                keyboardLedMatrix.setLedValueAt(y*3+2, x, colour.blue);
            }
        }
    }
}