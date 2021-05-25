#include "Keyboard.h"
#include "hwconfig.h"

const LedColour LedColour::OFF = LedColour(0, 0, 0);
const LedColour LedColour::RED = LedColour(1, 0, 0);
const LedColour LedColour::GREEN = LedColour(0, 1, 0);
const LedColour LedColour::BLUE = LedColour(0, 0, 1);
const LedColour LedColour::YELLOW = LedColour(1, 1, 0);
const LedColour LedColour::MAGENTA = LedColour(1, 0, 1);
const LedColour LedColour::CYAN = LedColour(0, 1, 1);

uint8_t rowPins[KEY_ROWS] = KEY_ROW_PINS;
uint8_t colPins[KEY_COLS] = KEY_COL_PINS;
char keys[KEY_ROWS][KEY_COLS] = {
    {KEY_RECORD, KEY_PLAY_STOP, KEY_PREV, KEY_NEXT}, // Sequence Playback/Navigation
    {KEY_LOOP_START, KEY_LOOP_END, KEY_PLACE_1, KEY_PLACE_2},
    {KEY_VIEW, KEY_SELECTION, KEY_FILE, KEY_HELP}, // UI Navigation
    {KEY_ADD, KEY_DEL, KEY_PLACE_3, KEY_PLACE_4},
    {KEY_FUNCTION, KEY_PLACE_5, KEY_PLACE_6, KEY_PLACE_7},
    {KEY_MOVE, KEY_COPY, KEY_PASTE, KEY_PLACE_8}
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

KeyState Keyboard::getKeyState(char key) {
    for(int i = 0; i < getNumKeys(); i++) {
        Key thisKey = getKeys()[i];
        if(thisKey.kchar == key) {
            return thisKey.kstate;
        }
    }
    return KeyState::IDLE;
}

void Keyboard::clear() {
    for(int x = 0; x < KEY_ROWS; x++) {
        for(int y = 0; y < KEY_COLS; y++) {
            keyboardLedMatrix.setLedValueAt(y*3, x, false);
            keyboardLedMatrix.setLedValueAt(y*3+1, x, false);
            keyboardLedMatrix.setLedValueAt(y*3+2, x, false);
        }
    }
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