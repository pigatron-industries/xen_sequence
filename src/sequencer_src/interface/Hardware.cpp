#include "Hardware.h"


Display Hardware::display;
LedMatrix Hardware::ledMatrix;
Keyboard Hardware::keyboard;

void Hardware::init() {
    display.init();
    ledMatrix.init();
}
