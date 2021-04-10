#include "ParameterView.h"
#include "interface/Hardware.h"
#include "model/AppData.h"
#include "lib/util/debug.h"

#include "Org_01.h"

ParameterView::ParameterView(SequenceMatrixView& _sequenceMatrixView) :
    sequenceMatrixView(_sequenceMatrixView) {
    Hardware::midiInputService.addEventHandler(this);
}

void ParameterView::init() {
    DEBUG("ParameterView::init")
    barIndex = Sequencer::sequencer.getBarIndex();
    songParameterView.init();
    updateSelectedBarFields();
    setParameterViewMode(parameterViewMode);
}

void ParameterView::render(GraphicsContext& g) {
    DEBUG("ParameterView::render");
    renderMode();

    g.yPos += FIELD_HEIGHT;
    visibleParameterView->render(g);

    sequenceMatrixView.render();

    dirtyScreen = false;
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    Hardware::display.setTextColour(Colour::WHITE);
    Hardware::display.setCursor(0, top+TEXT_HEIGHT);
    Hardware::display.print(parameterViewMode == PARAM_MODE_SONG ? "SONG" : 
                            parameterViewMode == PARAM_MODE_BAR ? "BAR" : 
                            parameterViewMode == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::setDirtyScreen() {
    dirtyScreen = true;
    // for(int i = 0; i < visibleFields->size(); i++) {
    //     visibleFields->get(i)->setDirty();
    // }
}

void ParameterView::renderKeyLeds() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(tickEventsParameterView.getTickEvents() != NULL) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
        } else {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::BLUE);
        }
    } else if (selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
    }
}

void ParameterView::handleMidiEvent(MidiMessage message) {
    if(recording && parameterViewMode == PARAM_MODE_EVENT) {
        DEBUG("ParameterView::handleMidiEvent");
        //TODO advance to next tick depending on recoding mode

        if(message.command == COMMAND_NOTEON) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
            if(tickEventsParameterView.getTickEvents() == NULL) {
                addEvent();
            }
        } else if (message.command == COMMAND_NOTEOFF) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::RED);
        }

        tickEventsParameterView.handleMidiEvent(message);
        View::render();
    }
}

InterfaceEvent ParameterView::handleEvent(InterfaceEvent event) {
    DEBUG("ParameterView::handleEvent");
    switch(event.eventType) {
        case InterfaceEventType::STICK_UP:
            cursorUp();
            break;

        case InterfaceEventType::STICK_DOWN:
            cursorDown();
            break;

        case InterfaceEventType::STICK_LEFT:
            cursorLeft();
            break;

        case InterfaceEventType::STICK_RIGHT:
            cursorRight();
            break;

        //TODO allow queue render to work from sub components
        case InterfaceEventType::DATA_PRESS:
        case InterfaceEventType::DATA_INCREMENT:
        case InterfaceEventType::DATA_DECREMENT:
            queueRender();
            break;

        case InterfaceEventType::KEY_RECORD: 
            if(event.data == EVENT_KEY_PRESSED) {
                record(!recording);
            }
            break;

        case InterfaceEventType::KEY_SELECTION:
        case InterfaceEventType::STICK_PRESS:
            if(event.data == EVENT_KEY_PRESSED) {
                cycleParameterViewMode();
                View::render();
            }
            break;

        case InterfaceEventType::KEY_ADD_DEL:
            if(event.data == EVENT_KEY_PRESSED) {
                if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                    if(tickEventsParameterView.getTickEvents() == NULL) {
                        addEvent();
                    } else {
                        deleteEvent();
                    }
                } else if (selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
                    clearPattern();
                }
            }
            break;

        case InterfaceEventType::KEY_PREV:
            if(event.data == EVENT_KEY_PRESSED) {
                prevBar();
            }
            break;
        case InterfaceEventType::KEY_NEXT:
            if(event.data == EVENT_KEY_PRESSED) {
                nextBar();
            }
            break;

        case InterfaceEventType::KEY_COPY:
            if(event.data == EVENT_KEY_PRESSED) {
                copy();
            }
            break;

        case InterfaceEventType::KEY_PASTE:
            if(event.data == EVENT_KEY_PRESSED) {
                paste();
            }
            break;

        case InterfaceEventType::KEY_MOVE:
            if(event.data == EVENT_KEY_PRESSED) {
                drag();
            } else if(event.data == EVENT_KEY_RELEASED) {
                drop();
            }
            break;

        default:
            break;
    }

    visibleParameterView->handleEvent(event);
    return InterfaceEvent::NONE;
}

void ParameterView::record(bool value) {
    recording = value;
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, value ? LedColour::RED : LedColour::OFF);
}

void ParameterView::cursorUp() {
    sequenceMatrixView.cursorUp();
    updateSelectedChannelFields();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorDown() {
    sequenceMatrixView.cursorDown();
    updateSelectedChannelFields();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorLeft() {
    sequenceMatrixView.cursorLeft();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorRight() {
    sequenceMatrixView.cursorRight();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::nextBar() {
    barIndex = Sequencer::sequencer.nextBar();
    updateSelectedBarFields();
    updateSelectedEventFields();
    queueRender();
}

void ParameterView::prevBar() {
    barIndex = Sequencer::sequencer.prevBar();
    updateSelectedBarFields();
    updateSelectedEventFields();
    queueRender();
}

void ParameterView::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    sequenceMatrixView.setBar(barIndex);
    updateSelectedBarFields();
};

void ParameterView::cycleSelectionMode() {
    switch(parameterViewMode) {
        case PARAM_MODE_SONG:
        case PARAM_MODE_BAR:
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_CHANNEL:
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case PARAM_MODE_EVENT:
            setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            break;
    }
}

void ParameterView::setSelectionMode(ParameterViewSelectionMode _selectionMode) {
    selectionMode = _selectionMode;
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT || selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
        sequenceMatrixView.setSelectionActive(true);
    } else {
        sequenceMatrixView.setSelectionActive(false);
    }
}

void ParameterView::cycleParameterViewMode() {
    setParameterViewMode(parameterViewMode == PARAM_MODE_SONG ? PARAM_MODE_BAR :
                         parameterViewMode == PARAM_MODE_BAR ? PARAM_MODE_CHANNEL :
                         parameterViewMode == PARAM_MODE_CHANNEL ? PARAM_MODE_EVENT : PARAM_MODE_SONG);
}

void ParameterView::setParameterViewMode(ParameterViewMode parameterViewMode) {
    DEBUG("ParameterView::setParameterViewMode"); 
    DEBUG(parameterViewMode);
    this->parameterViewMode = parameterViewMode;
    switch(parameterViewMode) {
        case PARAM_MODE_SONG:
            visibleParameterView = &songParameterView;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_BAR:
            visibleParameterView = &barParameterView;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_CHANNEL:
            visibleParameterView = &channelParameterView;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_CHANNEL);
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case PARAM_MODE_EVENT:
            visibleParameterView = &tickEventsParameterView;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_EVENT);
            setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            updateSelectedEventFields();
            break;
    };
    renderKeyLeds();
    queueRender(true);
}

void ParameterView::updateSelectedBarFields() {
    SequenceBar* bar = AppData::data.getBar(barIndex);
    barParameterView.setBar(bar);
    sequenceMatrixView.setBar(barIndex);
}

void ParameterView::updateSelectedChannelFields() {
    selectedPattern = barParameterView.getBar()->getPattern(sequenceMatrixView.getSelectCursorChannel());
    SequenceChannel* selectedChannel = &AppData::data.getChannel(sequenceMatrixView.getSelectCursorChannel());
    channelParameterView.setChannel(selectedChannel);
}

void ParameterView::updateSelectedEventFields() {
    updateSelectedChannelFields();
    SequenceTickEvents* selectedTickEvents = NULL;
    if(selectedPattern != NULL) {
        selectedTickEvents = selectedPattern->getTickEvents(sequenceMatrixView.getSelectCursorTick());
    }
    
    tickEventsParameterView.setTickEvents(selectedTickEvents);
    renderKeyLeds();
    queueRender(true);
}

void ParameterView::addEvent() {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEventFields();
}

void ParameterView::addEvent(SequenceTickEvents* copy) {
    AppData::data.newTickEvents(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), copy);
    updateSelectedEventFields();
}

void ParameterView::deleteEvent() {
    AppData::data.deleteTickEvents(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEventFields();
}

void ParameterView::clearPattern() {
    if(selectedPattern != NULL) {
        selectedPattern->clear();
        queueRender();
    }
}

void ParameterView::copy() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(tickEventsParameterView.getTickEvents() != NULL) {
            if(copiedEvent != NULL) {
                delete copiedEvent;
            }
            copiedEvent = new SequenceTickEvents(tickEventsParameterView.getTickEvents());
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PASTE, LedColour::BLUE);
        }
    }
}

void ParameterView::paste() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(copiedEvent != NULL) {
            deleteEvent();
            addEvent(copiedEvent);
        }
    }
}

void ParameterView::drag() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT && tickEventsParameterView.getTickEvents() != NULL) {
        copiedEvent = new SequenceTickEvents(tickEventsParameterView.getTickEvents());
        dragging = true;
        draggingFromBar = barIndex;
        draggingFromChannel = sequenceMatrixView.getSelectCursorChannel();
        draggingFromTick = sequenceMatrixView.getSelectCursorTick();
        sequenceMatrixView.setMarker(draggingFromChannel, draggingFromTick);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::BLUE);
    }
}

void ParameterView::drop() {
    if(dragging) {
        if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT && copiedEvent != NULL) {
            AppData::data.deleteTickEvents(draggingFromBar, draggingFromChannel, draggingFromTick);
            addEvent(copiedEvent);
        }
    }

    sequenceMatrixView.clearMarker();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::OFF);
    dragging = false;
}