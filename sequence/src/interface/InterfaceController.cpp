#include "InterfaceController.h"



InterfaceController::InterfaceController(AppData& _appData, Display& _display) :
    appData(_appData),
    display(_display),
    sequenceView(_appData, _display),
    parameterView(_appData, _display) {
}

void InterfaceController::init() {
    display.init();
    display.fillScreen(Colour(0, 0, 0));
    sequenceView.render();
    display.updateScreen();
}
