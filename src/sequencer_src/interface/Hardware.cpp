#include "Hardware.h"


Display Hardware::display;
LedMatrix Hardware::ledMatrix;
Keyboard Hardware::keyboard;
MidiInputService Hardware::midiInputService(Serial3);
Time Hardware::time;

void Hardware::init() {
    display.init();
    ledMatrix.init();
    keyboard.clear();
    midiInputService.init();
    time.init();
}
