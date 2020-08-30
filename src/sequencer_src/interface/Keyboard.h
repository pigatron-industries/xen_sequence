#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>

#include "Keypad.h"
#include "InterfaceEvent.h"
#include "../lib/drivers/KeyboardLedMatrix.h"


class LedColour {
public:
    static const LedColour OFF;
    static const LedColour RED;
    static const LedColour GREEN;
    static const LedColour BLUE;
    LedColour(bool _red, bool _green, bool _blue) :
        red(_red), green(_green), blue(_blue) {}
    bool red;
    bool green;
    bool blue;
};

class Keyboard {

public:
    Keyboard();

    char getKey();
    void setKeyLed(InterfaceEventType key, LedColour colour);

private:
    Keypad keypad;
    KeyboardLedMatrix keyboardLedMatrix;

};

#endif
