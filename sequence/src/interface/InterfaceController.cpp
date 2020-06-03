#include "InterfaceController.h"



InterfaceController::InterfaceController(AppData& _appData, Display& _display, Matrix& _matrix) :
    appData(_appData),
    display(_display),
    matrix(_matrix),
    sequenceMatrixView(_appData, _matrix),
    sequenceView(_appData, _display, sequenceMatrixView),
    parameterView(_appData, _display, sequenceMatrixView) {
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
