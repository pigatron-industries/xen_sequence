#include "InterfaceController.h"

#include "Hardware.h"
#include "InterfaceEventQueue.h"
#include "model/AppData.h"

#include "graphics/GraphicsContext.h"
#include "repository/DataRepository.h"
#include "lib/util/debug.h"

InterfaceController::InterfaceController() :
    sequenceMatrixView(),
    sequenceView(sequenceMatrixView),
    parameterView(sequenceMatrixView) {
      currentView = &sequenceView;
}

void InterfaceController::init() {
    Sequencer::sequencer.addEventListener(this);
    Hardware::display.fillScreen(Colour(0, 0, 0));
    sequenceView.init();
    render();
    setLoopMode(Sequencer::sequencer.getPlayMode());
}

void InterfaceController::render() {
    currentView->render();
}

void InterfaceController::update() {
    while(InterfaceEventQueue::q.getSize() > 0) {
        handleEvent(InterfaceEventQueue::q.popEvent());
    }
}

void InterfaceController::handleEvent(InterfaceEvent event) {
    DEBUG("InterfaceController::handleEvent")

    if(event.eventType == InterfaceEventType::RENDER) {
        currentView->render(event.data);

    } else if(isSequenceView()) {

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
                    if(Sequencer::sequencer.isPlaying()) {
                        stop();
                    } else {
                        play();
                    }
                }
                break;

            case InterfaceEventType::KEY_LOOP_MODE:
                if(event.data == EVENT_KEY_PRESSED) {
                    cycleLoopMode();
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
                    currentView->init();
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
    Sequencer::sequencer.play();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::GREEN);
}

void InterfaceController::stop() {
    Sequencer::sequencer.stop();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::OFF);
}

void InterfaceController::cycleLoopMode() {
    SequencePlayMode playMode = Sequencer::sequencer.getPlayMode();
    setLoopMode(playMode == PLAY_SONG ?           PLAY_LOOP_BAR :
                playMode == PLAY_LOOP_BAR ?       PLAY_LOOP_SELECTION :
                playMode == PLAY_LOOP_SELECTION ? PLAY_LOOP_SONG : 
                                                  PLAY_SONG);
}

void InterfaceController::setLoopMode(SequencePlayMode loopMode) {
    Sequencer::sequencer.setPlayMode(loopMode);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_LOOP_MODE, loopMode == PLAY_SONG ?           LedColour::GREEN :
                                                                    loopMode == PLAY_LOOP_BAR ?       LedColour::MAGENTA :
                                                                    loopMode == PLAY_LOOP_SELECTION ? LedColour::CYAN :
                                                                    loopMode == PLAY_LOOP_SONG ?      LedColour::YELLOW : 
                                                                                                      LedColour::OFF);
    InterfaceEventQueue::q.doRender();
}
