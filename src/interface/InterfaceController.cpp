#include "InterfaceController.h"



InterfaceController::InterfaceController(AppData& _appData, Sequencer& _sequencer, Display& _display, LedMatrix& _ledMatrix) :
    appData(_appData),
    sequencer(_sequencer),
    display(_display),
    ledMatrix(_ledMatrix),
    sequenceMatrixView(_appData, _sequencer, _ledMatrix),
    sequenceView(_appData, _display, sequenceMatrixView),
    parameterView(_appData, _display, sequenceMatrixView) {
      currentView = &sequenceView;
      sequencer.addEventListener(this);
}

void InterfaceController::init() {
    display.init();
    display.fillScreen(Colour(0, 0, 0));
    render();
}

void InterfaceController::render() {
    currentView->render();
}

void InterfaceController::handleEvent(Event event) {
    switch(event) {
        case Event::STICK_PRESS:
            if(currentView == &sequenceView) {
                switchToParameterView();
            }
            break;
        case Event::KEY_BACK:
            if(currentView == &parameterView) {
                switchToSequenceView();
            }
        case Event::KEY_PLAY_STOP:
            if(sequencer.isPlaying()) {
                sequencer.stop();
            } else {
                sequencer.play();
            }
        case Event::SEQUENCER_TICK:
            sequenceMatrixView.render();
        default:
            break;
    }

    currentView->handleEvent(event);
}

void InterfaceController::onTick() {
    handleEvent(Event::SEQUENCER_TICK);
}

void InterfaceController::switchToParameterView() {
    currentView = &parameterView;
    uint16_t bar = sequenceView.getCursorBar();
    parameterView.setBar(bar);
    currentView->render();
}

void InterfaceController::switchToSequenceView() {
    currentView = &sequenceView;
    currentView->render();
}
