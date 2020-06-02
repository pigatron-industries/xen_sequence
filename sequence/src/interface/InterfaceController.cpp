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
}

void InterfaceController::handleEvent(Event event) {
    //TODO forward to current page
    sequenceView.handleEvent(event);
}
