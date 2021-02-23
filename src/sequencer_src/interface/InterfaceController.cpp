#include "InterfaceController.h"

#include "Hardware.h"
#include "model/AppData.h"

#include "graphics/GraphicsContext.h"
#include "repository/DataRepository.h"
#include "lib/util/debug.h"

InterfaceController::InterfaceController(Sequencer& _sequencer) :
    sequencer(_sequencer),
    sequenceMatrixView(_sequencer),
    sequenceView(_sequencer, sequenceMatrixView),
    parameterView(_sequencer, sequenceMatrixView) {
      currentView = &sequenceView;
      sequencer.addEventListener(this);
}

void InterfaceController::init() {
    Hardware::display.fillScreen(Colour(0, 0, 0));
    sequenceView.init();
    render();
}

void InterfaceController::render() {
    currentView->render();
}

void InterfaceController::handleEvent(InterfaceEvent event) {
    DEBUG("InterfaceController::handleEvent")
    DEBUG(event.eventType)
    
    if(isSequenceView()) {

        switch(event.eventType) {

            case InterfaceEventType::STICK_PRESS:
                if(currentView == &sequenceView) {
                    switchToParameterView();
                    return;
                }
                break;

            case InterfaceEventType::KEY_VIEW:
                if(event.data == EVENT_KEY_PRESSED) {
                    if(currentView == &parameterView) {
                        switchToSequenceView();
                    } else {
                        switchToParameterView();
                    }
                    return;
                }
                break;

            case InterfaceEventType::KEY_HELP:
                if(event.data == EVENT_KEY_PRESSED) {
                    previousView = currentView;
                    currentView = &helpView;
                    render();
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
            case InterfaceEventType::KEY_VIEW:
                if(event.data == EVENT_KEY_PRESSED) {
                    currentView = previousView;
                    Hardware::keyboard.clear();
                    render();
                }
                break;
            default:
                break;
        }

    }

    InterfaceEvent responseEvent = currentView->handleEvent(event);
    if(responseEvent.eventType != InterfaceEventType::NONE) {
        handleEvent(responseEvent); //TODO push event onto queue instead of calling recursively
    }

    if(currentView->rerender) {
        currentView->render(currentView->rerenderFull);
        currentView->rerender = false;
        currentView->rerenderFull = false;
    }
}

void InterfaceController::onTick() {
    handleEvent(InterfaceEvent(SEQUENCER_TICK));
}

void InterfaceController::switchToParameterView() {
    DEBUG("InterfaceController::switchToParameterView");
    currentView = &parameterView;
    parameterView.init();
    render();
}

void InterfaceController::switchToSequenceView() {
    DEBUG("InterfaceController::switchToSequenceView");
    currentView = &sequenceView;
    sequenceView.init();
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
