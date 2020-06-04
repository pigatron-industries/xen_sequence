#include "InterfaceController.h"



InterfaceController::InterfaceController(AppData& _appData, Display& _display, Matrix& _matrix) :
    appData(_appData),
    display(_display),
    matrix(_matrix),
    sequenceMatrixView(_appData, _matrix),
    sequenceView(_appData, _display, sequenceMatrixView),
    parameterView(_appData, _display, sequenceMatrixView) {
      currentView = &sequenceView;
}

void InterfaceController::init() {
    display.init();
    display.fillScreen(Colour(0, 0, 0));
    currentView->render();
}

void InterfaceController::handleEvent(Event event) {
    switch(event) {
        case STICK_PRESS:
            if(currentView == &sequenceView) {
                switchToParameterView();
            } else {
                switchToSequenceView();
            }
            break;
        default:
            break;
    }

    currentView->handleEvent(event);
}

void InterfaceController::switchToParameterView() {
    currentView = &parameterView;
    uint16_t bar = sequenceView.getCursorBar();
    parameterView.setBar(bar);
}

void InterfaceController::switchToSequenceView() {
    currentView = &sequenceView;
    currentView->render();
}
