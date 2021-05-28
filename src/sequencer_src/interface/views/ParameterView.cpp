#include "ParameterView.h"
#include "interface/Hardware.h"
#include "model/AppData.h"
#include "sequencer/midi/MidiState.h"
#include "lib/util/debug.h"

#include "Org_01.h"

ParameterView::ParameterView(SequenceMatrixView& _sequenceMatrixView) :
    sequenceMatrixView(_sequenceMatrixView) {
    tickEventsParameterView.setHeight(DISPLAY_HEIGHT - FIELD_HEIGHT);
    tickEventsParameterView.setWidth(DISPLAY_WIDTH);
    songParameterView.setHeight(DISPLAY_HEIGHT - FIELD_HEIGHT);
    barParameterView.setHeight(DISPLAY_HEIGHT - FIELD_HEIGHT);
    channelParameterView.setHeight(DISPLAY_HEIGHT - FIELD_HEIGHT);
    Hardware::midiInputService.addEventHandler(this);
    parameterViewMode.value = ParameterViewMode::PARAM_MODE_EVENT;
}

void ParameterView::init() {
    DEBUGINFO
    barIndex = Sequencer::sequencer.getBarIndex();
    songParameterView.init();
    updateSelectedBarFields();
    setParameterViewMode(parameterViewMode.value);
}

void ParameterView::render(GraphicsContext& g) {
    DEBUGINFO
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
    Hardware::display.print(parameterViewMode.value == PARAM_MODE_SONG ? "SONG" : 
                            parameterViewMode.value == PARAM_MODE_BAR ? "BAR" : 
                            parameterViewMode.value == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::setDirtyScreen() {
    dirtyScreen = true;
}

void ParameterView::renderKeyLeds(bool mode) {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD, LedColour::BLUE);
        if(tickEventsParameterView.getTickEvents() != NULL) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_DEL, LedColour::RED);
        } else {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_DEL, LedColour::OFF);
        }
    } else if (selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_DEL, LedColour::RED);
    } else {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_DEL, LedColour::OFF);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD, LedColour::OFF);
    }

    renderRecordModeKeyLeds(mode);
}

void ParameterView::renderRecordModeKeyLeds(bool mode) {
    if(recording || mode) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, recordMode.value == RecordMode::STATIC ? LedColour::YELLOW : 
                                                                     recordMode.value == RecordMode::ADVANCE_ON_MESSAGE ? LedColour::MAGENTA : LedColour::RED);
    } else {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
    }
}

void ParameterView::handleMidiEvent(MidiMessage message) {
    DEBUGINFO
    if(recording && parameterViewMode.value == PARAM_MODE_EVENT) {

        if(tickEventsParameterView.handleMidiEvent(message)) {
            updateSelectedEventFields();
        } else {
            InterfaceEventQueue::q.doRender(false);
        }

        if(recordMode.value == RecordMode::ADVANCE_ON_MESSAGE && message.command == COMMAND_NOTEOFF && 
           MidiState::midiState.getChannelState(message.channel).getNoteOnCount() == 0) {
            cursorRight();
            InterfaceEventQueue::q.doRender(true);
        }
    }
}

void ParameterView::handleEvent(InterfaceEvent event) {
    DEBUGINFO
    switch(event.eventType) {
        case InterfaceEventType::KEY_FUNCTION:
            if(event.data == EVENT_KEY_PRESSED) {
                renderKeyLeds(true);
            } else {
                renderKeyLeds(false);
            }
            break;

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

        case InterfaceEventType::KEY_RECORD: 
            if(event.data == EVENT_KEY_PRESSED) {
                record(!recording);
            } else if(event.data == EVENT_KEY_FUNCTION) {
                cycleRecordMode();
            }
            break;

        case InterfaceEventType::KEY_SELECTION:
        case InterfaceEventType::STICK_PRESS:
            if(event.data == EVENT_KEY_PRESSED) {
                cycleParameterViewMode();
                View::render();
            }
            break;

        case InterfaceEventType::KEY_ADD:
            if(event.data == EVENT_KEY_PRESSED) {
                if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                    addEvent();
                }
            }
            break;

        case InterfaceEventType::KEY_DEL:
            if(event.data == EVENT_KEY_PRESSED) {
                if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                    deleteEvent();
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
}

void ParameterView::record(bool value) {
    recording = value;
    renderRecordModeKeyLeds();
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
    InterfaceEventQueue::q.doRender();
}

void ParameterView::prevBar() {
    barIndex = Sequencer::sequencer.prevBar();
    updateSelectedBarFields();
    updateSelectedEventFields();
    InterfaceEventQueue::q.doRender();
}

void ParameterView::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    sequenceMatrixView.setBar(barIndex);
    updateSelectedBarFields();
};

void ParameterView::cycleSelectionMode() {
    switch(parameterViewMode.value) {
        case ParameterViewMode::PARAM_MODE_SONG:
        case ParameterViewMode::PARAM_MODE_BAR:
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case ParameterViewMode::PARAM_MODE_CHANNEL:
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case ParameterViewMode::PARAM_MODE_EVENT:
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
    parameterViewMode.cycle(1);
    setParameterViewMode(parameterViewMode.value);
}

void ParameterView::setParameterViewMode(ParameterViewMode parameterViewMode) {
    DEBUGINFO
    this->parameterViewMode.value = parameterViewMode;
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
    InterfaceEventQueue::q.doRender(true);
}

void ParameterView::cycleRecordMode() {
    recordMode.cycle(1);
    setRecordMode(recordMode.value);
}

void ParameterView::setRecordMode(RecordMode recordMode) {
    this->recordMode.value = recordMode;
    renderRecordModeKeyLeds(true);
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
    
    tickEventsParameterView.setTickEvents(selectedTickEvents, barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    renderKeyLeds();
    InterfaceEventQueue::q.doRender(true);
}

void ParameterView::addEvent() {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), EventType::NOTE_EVENT);
    updateSelectedEventFields();
}

void ParameterView::addEvent(SequenceTickEvents* copy) {
    AppData::data.newTickEvents(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), copy);
    updateSelectedEventFields();
}

void ParameterView::addTickEvents() {
    AppData::data.newTickEvents(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEventFields();
}

void ParameterView::deleteEvent() {
    int eventIndex = tickEventsParameterView.getSelectedEventIndex();
    AppData::data.deleteEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), eventIndex);
    updateSelectedEventFields();
}

void ParameterView::clearPattern() {
    if(selectedPattern != NULL) {
        selectedPattern->clear();
        InterfaceEventQueue::q.doRender();
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