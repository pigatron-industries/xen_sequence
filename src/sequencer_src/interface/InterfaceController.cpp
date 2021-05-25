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
    setLoopMode(Sequencer::sequencer.getPlayMode());
    render();
    renderKeyLeds(false);
}

void InterfaceController::render() {
    currentView->render();
}

void InterfaceController::renderKeyLeds(bool mode) {
    renderPlayModeKeyLeds(mode);
}

void InterfaceController::renderPlayModeKeyLeds(bool mode) {
    if(Sequencer::sequencer.isPlaying() || mode) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, Sequencer::sequencer.getPlayMode() == PLAY_SONG ?           LedColour::GREEN :
                                                                        Sequencer::sequencer.getPlayMode() == PLAY_LOOP_BAR ?       LedColour::MAGENTA :
                                                                        Sequencer::sequencer.getPlayMode() == PLAY_LOOP_SELECTION ? LedColour::CYAN :
                                                                        Sequencer::sequencer.getPlayMode() == PLAY_LOOP_SONG ?      LedColour::YELLOW : 
                                                                                                                                     LedColour::OFF);
    } else {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::OFF);
    }
}

void InterfaceController::update() {
    while(InterfaceEventQueue::q.getSize() > 0) {
        handleEvent(InterfaceEventQueue::q.popEvent());
    }
}

void InterfaceController::handleEvent(InterfaceEvent event) {
    DEBUGINFO

    if(event.eventType == InterfaceEventType::RENDER) {
        currentView->render(event.data);

    } else if(isSequenceView()) {

        switch(event.eventType) {

            case InterfaceEventType::KEY_FUNCTION:
                if(event.data == EVENT_KEY_PRESSED) {
                    renderKeyLeds(true);
                } else {
                    renderKeyLeds(false);
                }
                break;

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
                if(event.data == EVENT_KEY_FUNCTION) {
                    cycleLoopMode();
                } else if(event.data == EVENT_KEY_PRESSED) {
                    if(Sequencer::sequencer.isPlaying()) {
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
                    currentView->init();
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
    DEBUGINFO
    currentView = &parameterView;
    parameterView.init();
    render();
}

void InterfaceController::switchToSequenceView() {
    DEBUGINFO
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
    renderPlayModeKeyLeds(true);
    InterfaceEventQueue::q.doRender();
}
