#include "InterfaceController.h"

#include "Hardware.h"
#include "../model/AppData.h"

#include "graphics/GraphicsContext.h"
#include "../repository/DataRepository.h"

InterfaceController::InterfaceController(Sequencer& _sequencer) :
    sequencer(_sequencer),
    sequenceMatrixView(_sequencer),
    sequenceView(sequenceMatrixView),
    parameterView(_sequencer, sequenceMatrixView) {
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
    if(isSequenceView()) {

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
                    render();
                }
                break;
            case InterfaceEventType::KEY_RECORD: 
                if(event.data == EVENT_KEY_PRESSED) {
                    record(!recording);
                }
                break;
            case InterfaceEventType::KEY_PLAY_STOP:
                if(event.data == EVENT_KEY_PRESSED) {
                    if(sequencer.isPlaying()) {
                        stop();
                    } else {
                        play();
                    }
                }
                break;
            case InterfaceEventType::KEY_FILE:
                if(event.data == EVENT_KEY_PRESSED) {
                    stop();
                    fileView.init();
                    previousView = currentView;
                    currentView = &fileView;
                    render();
                }
                break;
            case InterfaceEventType::SEQUENCER_TICK:
                sequenceMatrixView.render();
            default:
                break;
        }

    } else if (isHelpView()) {

        if(event.eventType == InterfaceEventType::KEY_HELP && event.data == EVENT_KEY_RELEASED) {
            currentView = previousView;
            render();
        }

    } else if (isFileView()) {

        switch(event.eventType) {
            case InterfaceEventType::KEY_FILE:
                if(event.data == EVENT_KEY_PRESSED) {
                    currentView = previousView;
                    render();
                }
                break;
            default:
                break;
        }

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
    render();
}

void InterfaceController::switchToSequenceView() {
    currentView = &sequenceView;
    render();
}

void InterfaceController::play() {
    sequencer.play();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::GREEN);
}

void InterfaceController::stop() {
    sequencer.stop();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::OFF);
}

void InterfaceController::record(bool value) {
    recording = value;
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, value ? LedColour::RED : LedColour::OFF);
}
