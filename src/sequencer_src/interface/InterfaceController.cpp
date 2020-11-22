#include "InterfaceController.h"
#include "Hardware.h"

InterfaceController::InterfaceController(AppData& _appData, Sequencer& _sequencer, Keyboard& _keyboard) :
    appData(_appData),
    sequencer(_sequencer),
    keyboard(_keyboard),
    sequenceMatrixView(_appData, _sequencer),
    sequenceView(_appData, sequenceMatrixView),
    parameterView(_appData, _sequencer, sequenceMatrixView) {
      currentView = &sequenceView;
      sequencer.addEventListener(this);
}

void InterfaceController::init() {
    Hardware::display.fillScreen(Colour(0, 0, 0));
    render();
}

void InterfaceController::render() {
    currentView->render();
}

void InterfaceController::handleEvent(InterfaceEvent event) {
    if(currentView != &helpView) {
        switch(event.eventType) {
            case InterfaceEventType::STICK_PRESS:
                if(currentView == &sequenceView) {
                    switchToParameterView();
                }
                break;
            case InterfaceEventType::KEY_VIEW:
                if(event.data == EVENT_KEY_PRESSED) {
                    if(currentView == &parameterView) {
                        switchToSequenceView();
                    } else {
                        switchToParameterView();
                    }
                }
                break;
            case InterfaceEventType::KEY_HELP:
                if(event.data == EVENT_KEY_PRESSED) {
                    previousView = currentView;
                    currentView = &helpView;
                    currentView->render(true);
                }
                break;
            case InterfaceEventType::KEY_RECORD: 
                if(event.data == EVENT_KEY_PRESSED) {
                    if(recording) {
                        recording = false;
                        keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
                    } else {
                        recording = true;
                        keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::RED);
                    }
                }
                break;
            case InterfaceEventType::KEY_PLAY_STOP:
                if(event.data == EVENT_KEY_PRESSED) {
                    if(sequencer.isPlaying()) {
                        sequencer.stop();
                        keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::OFF);
                    } else {
                        sequencer.play();
                        keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::GREEN);
                    }
                }
                break;
            case InterfaceEventType::SEQUENCER_TICK:
                sequenceMatrixView.render();
            default:
                break;
        }
    } else if (event.eventType == InterfaceEventType::KEY_HELP && event.data == EVENT_KEY_RELEASED) {
        currentView = previousView;
        currentView->render(true);
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
