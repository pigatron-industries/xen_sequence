#include "InterfaceController.h"



InterfaceController::InterfaceController(AppData& _appData, Sequencer& _sequencer, Display& _display, LedMatrix& _ledMatrix, Keyboard& _keyboard) :
    appData(_appData),
    sequencer(_sequencer),
    display(_display),
    ledMatrix(_ledMatrix),
    keyboard(_keyboard),
    sequenceMatrixView(_appData, _sequencer, _ledMatrix),
    sequenceView(_appData, _display, sequenceMatrixView),
    parameterView(_appData, _sequencer, _display, sequenceMatrixView) {
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

void InterfaceController::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::STICK_PRESS:
            if(currentView == &sequenceView) {
                switchToParameterView();
            }
            break;
        case InterfaceEventType::KEY_BACK:
            if(currentView == &parameterView) {
                switchToSequenceView();
            }
            break;
        case InterfaceEventType::KEY_RECORD: 
            if(recording) {
                recording = false;
                keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
            } else {
                recording = true;
                keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::RED);
            }
            break;
        case InterfaceEventType::KEY_PLAY_STOP:
            if(sequencer.isPlaying()) {
                sequencer.stop();
                keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::OFF);
            } else {
                sequencer.play();
                keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::GREEN);
            }
            break;
        case InterfaceEventType::SEQUENCER_TICK:
            sequenceMatrixView.render();
        default:
            break;
    }

    currentView->handleEvent(event);
}

void InterfaceController::onTick() {
    handleEvent(InterfaceEvent(SEQUENCER_TICK));
}

void InterfaceController::switchToParameterView() {
    currentView = &parameterView;
    uint16_t bar = sequenceView.getCursorBar();
    parameterView.setBar(bar);
    currentView->render(true);
}

void InterfaceController::switchToSequenceView() {
    currentView = &sequenceView;
    currentView->render(true);
}
