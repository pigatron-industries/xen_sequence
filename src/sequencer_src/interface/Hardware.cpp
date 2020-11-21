#include "Hardware.h"


Display Hardware::display;
LedMatrix Hardware::ledMatrix;


void Hardware::init() {
    display.init();
    ledMatrix.init();
}
