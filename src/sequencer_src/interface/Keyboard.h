#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <Keypad.h>

#include "InterfaceEvent.h"
#include "lib/drivers/KeyboardLedMatrix.h"


class LedColour {
public:
    static const LedColour OFF;
    static const LedColour RED;
    static const LedColour GREEN;
    static const LedColour BLUE;
    static const LedColour YELLOW;
    static const LedColour MAGENTA;
    static const LedColour CYAN;
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
        KeyState getKeyState(char key);

        void clear();
        void setKeyLed(InterfaceEventType key, LedColour colour);

    private:
        static Keypad keypad;
        KeyboardLedMatrix keyboardLedMatrix;

        static void handleKeypadEvent(Key key);

};

#endif
