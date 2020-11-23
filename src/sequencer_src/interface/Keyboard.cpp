#include "Keyboard.h"
#include "../hwconfig.h"

const LedColour LedColour::OFF = LedColour(0, 0, 0);
const LedColour LedColour::RED = LedColour(1, 0, 0);
const LedColour LedColour::GREEN = LedColour(0, 1, 0);
const LedColour LedColour::BLUE = LedColour(0, 0, 1);

uint8_t rowPins[KEY_ROWS] = KEY_ROW_PINS;
uint8_t colPins[KEY_COLS] = KEY_COL_PINS;
char keys[KEY_ROWS][KEY_COLS] = {
    {KEY_RECORD, KEY_PLAY_STOP, KEY_PREV, KEY_NEXT},       // Sequence Playback/Navigation
    {KEY_LOOP, KEY_PLACE_2, KEY_PLACE_3, KEY_PLACE_4},     
    {KEY_VIEW, KEY_SELECTION, KEY_PLACE_5, KEY_PLACE_6}, // UI Navigation
    {KEY_ADD_DEL, KEY_COPY, KEY_PASTE, KEY_PLACE_8},
    {KEY_PLACE_9, KEY_PLACE_10, KEY_PLACE_11, KEY_PLACE_12},
    {KEY_PLACE_13, KEY_PLACE_14, KEY_FILE, KEY_HELP}
};


Keypad Keyboard::keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS);

Keyboard::Keyboard() {
}

bool Keyboard::update() {
    return keypad.getKeys();
}

Key* Keyboard::getKeys() {
    return keypad.key;
}

int Keyboard::getNumKeys() {
    return keypad.numKeys();
}

void Keyboard::setKeyLed(InterfaceEventType key, LedColour colour) {
    for(int x = 0; x < KEY_ROWS; x++) {
        for(int y = 0; y < KEY_COLS; y++) {
            if(key == static_cast<InterfaceEventType>(keys[x][y])) {
                keyboardLedMatrix.setLedValueAt(y*3, x, colour.red);
                keyboardLedMatrix.setLedValueAt(y*3+1, x, colour.green);
                keyboardLedMatrix.setLedValueAt(y*3+2, x, colour.blue);
                return;
            }
        }
    }
}