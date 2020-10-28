#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <Keypad.h>

// #include "../lib/drivers/Keypad.h"
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

        bool update();
        Key* getKeys();
        int getNumKeys();

        void setKeyLed(InterfaceEventType key, LedColour colour);

    private:
        static Keypad keypad;
        KeyboardLedMatrix keyboardLedMatrix;

        static void handleKeypadEvent(Key key);

};

#endif
