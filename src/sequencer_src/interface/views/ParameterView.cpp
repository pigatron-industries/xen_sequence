#include "ParameterView.h"
#include "../Hardware.h"
#include "../../model/AppData.h"
#include "../../lib/util/debug.h"

#include "Org_01.h"

ParameterView::ParameterView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView) :
    sequencer(_sequencer),
    sequenceMatrixView(_sequenceMatrixView) {
    barFields.add(&barLengthField);
    barFields.add(&barSpeedField);
    channelFields.add(&channelMuteField);
    eventFields.add(&eventNoteField);
    eventFields.add(&eventVelocityField);
    eventFields.add(&eventGateField);
    eventFields.add(&eventDelayField);
    Hardware::midiInputService.addEventHandler(this);
}

void ParameterView::init() {
    DEBUG("ParameterView::init")
    barIndex = sequencer.getBarIndex();
    updateSelectedBar();
    setParameterViewMode(parameterViewMode);
}

void ParameterView::render(GraphicsContext& g) {
    DEBUG("ParameterView::render");
    if(g.full) {
        setDirtyScreen();
    }
    renderMode();
    renderFields();

    sequenceMatrixView.render();

    dirtyScreen = false;
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    Hardware::display.setTextColour(Colour::WHITE);
    Hardware::display.setCursor(0, top+TEXT_HEIGHT);
    Hardware::display.print(parameterViewMode == PARAM_MODE_BAR ? "BAR" : parameterViewMode == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::renderFields() {
    for(uint8_t row = 0; row < visibleFields->size(); row++) {
        renderField(row);
    }
}

void ParameterView::renderField(uint8_t row) {
    visibleFields->get(row)->render(Hardware::display, row+1);
}

void ParameterView::setDirtyScreen() {
    dirtyScreen = true;
    for(int i = 0; i < visibleFields->size(); i++) {
        visibleFields->get(i)->setDirty();
    }
}

void ParameterView::handleMidiEvent(MidiMessage message) {
    if(recording && parameterViewMode == PARAM_MODE_EVENT) {
        DEBUG("ParameterView::handleMidiEvent");
        if(message.command == COMMAND_NOTEON) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
            if(selectedEvent == NULL) {
                addEvent();
            }
            eventNoteField.setValue(message.data1);
            eventVelocityField.setValue(message.data2);
            updateDataFromField(&eventNoteField);
            updateDataFromField(&eventVelocityField);
            View::render(false);
        } else if (message.command == COMMAND_NOTEOFF) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::RED);
        }
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

        case InterfaceEventType::DATA_PRESS:
            nextParameter();
            View::render();
            break;

        case InterfaceEventType::DATA_INCREMENT:
            fieldIncrement(event.data);
            break;

        case InterfaceEventType::DATA_DECREMENT:
            fieldDecrement(event.data);
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
                if(selectedEvent == NULL) {
                    addEvent();
                } else {
                    deleteEvent();
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

        default:
            break;
    }


    return InterfaceEvent::NONE;
}

void ParameterView::record(bool value) {
    recording = value;
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, value ? LedColour::RED : LedColour::OFF);
}

void ParameterView::cursorUp() {
    sequenceMatrixView.cursorUp();
    updateSelectedChannel();
    updateSelectedEvent();
    View::render();
}

void ParameterView::cursorDown() {
    sequenceMatrixView.cursorDown();
    updateSelectedChannel();
    updateSelectedEvent();
    View::render();
}

void ParameterView::cursorLeft() {
    sequenceMatrixView.cursorLeft();
    updateSelectedEvent();
    View::render();
}

void ParameterView::cursorRight() {
    sequenceMatrixView.cursorRight();
    updateSelectedEvent();
    View::render();
}

void ParameterView::nextBar() {
    barIndex = sequencer.nextBar();
    updateSelectedBar();
    updateSelectedEvent();
    queueRender();
}

void ParameterView::prevBar() {
    barIndex = sequencer.prevBar();
    updateSelectedBar();
    updateSelectedEvent();
    queueRender();
}

void ParameterView::fieldIncrement(int amount) {
    ParameterField* field = getSelectedField();
    if(field != NULL) {
        field->increment(amount);
        updateDataFromField(field);
        renderField(selectedFieldIndex);
    }
}

void ParameterView::fieldDecrement(int amount) {
    ParameterField* field = getSelectedField();
    if(field != NULL) {
        field->decrement(amount);
        updateDataFromField(field);
        renderField(selectedFieldIndex);
    }
}

void ParameterView::setSelectedField(int8_t fieldIndex) {
    selectedFieldIndex = fieldIndex;
    if(selectedField != NULL) {
        selectedField->setSelected(false);
    }
    if(selectedFieldIndex >= 0 && visibleFields->size() > selectedFieldIndex) {
        selectedField = visibleFields->get(selectedFieldIndex);
        selectedField->setSelected(true);
    } else {
        selectedField = NULL;
    }
}

ParameterField* ParameterView::getSelectedField() {
    if(selectedFieldIndex >= 0 && visibleFields->size() > selectedFieldIndex) {
        return visibleFields->get(selectedFieldIndex);
    } else {
        return NULL;
    }
}

void ParameterView::nextParameter() {
    int8_t newFieldIndex = selectedFieldIndex+1;
    if(newFieldIndex >= visibleFields->size()) {
        newFieldIndex = 0;
    }
    setSelectedField(newFieldIndex);
}

void ParameterView::prevParameter() {
    int8_t newFieldIndex = selectedFieldIndex-1;
    if(newFieldIndex < 0) {
        newFieldIndex = visibleFields->size()-1;
    }
    setSelectedField(newFieldIndex);
}

void ParameterView::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    sequenceMatrixView.setBar(barIndex);
    updateSelectedBar();
};

void ParameterView::cycleSelectionMode() {
    switch(parameterViewMode) {
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
    setParameterViewMode(parameterViewMode == PARAM_MODE_BAR ? PARAM_MODE_CHANNEL :
                         parameterViewMode == PARAM_MODE_CHANNEL ? PARAM_MODE_EVENT :
                         PARAM_MODE_BAR);
}

void ParameterView::setParameterViewMode(ParameterViewMode _parameterViewMode) {
    DEBUG("ParameterView::setParameterViewMode"); 
    DEBUG(_parameterViewMode);
    parameterViewMode = _parameterViewMode;
    switch(parameterViewMode) {
        case PARAM_MODE_BAR:
            visibleFields = &barFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_CHANNEL:
            visibleFields = &channelFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_CHANNEL);
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case PARAM_MODE_EVENT:
            visibleFields = &eventFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_EVENT);
            setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            updateSelectedEvent();
            break;
    };
    setSelectedField(visibleFields->size() == 0 ? -1 : 0);
    setDirtyScreen();
}

void ParameterView::updateSelectedBar() {
    bar = AppData::data.getBar(barIndex);
    barLengthField.setValue(bar->getLength());
    barSpeedField.setValue(bar->getSpeed());
    sequenceMatrixView.setBar(barIndex);
}

void ParameterView::updateSelectedChannel() {
    selectedPattern = bar->getPattern(sequenceMatrixView.getSelectCursorChannel());
    SequenceChannel selectedChannel = AppData::data.getChannel(sequenceMatrixView.getSelectCursorChannel());
    channelMuteField.setValue(selectedChannel.getMute());
}

void ParameterView::updateSelectedEvent() {
    updateSelectedChannel();
    if(selectedPattern != NULL) {
        selectedEvent = selectedPattern->getEvent(sequenceMatrixView.getSelectCursorTick());
    } else {
        selectedEvent = NULL;
    }
    if(selectedEvent != NULL) {
        eventNoteField.setValue(selectedEvent->getPitch());
        eventVelocityField.setValue(selectedEvent->getVelocity());
        eventGateField.setValue(selectedEvent->getGate());
        eventDelayField.setValue(selectedEvent->getDelay());
        for(int i = 0; i < eventFields.size(); i++) {
            eventFields.get(i)->setEnabled(true);
        }
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
    } else {
        for(int i = 0; i < eventFields.size(); i++) {
            eventFields.get(i)->setEnabled(false);
        }
        setDirtyScreen();
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::BLUE);
    }
    queueRender();
}

void ParameterView::updateDataFromField(ParameterField* field) {
    if(selectedEvent != NULL) {
        if(field == &eventNoteField) {
            selectedEvent->setPitch(eventNoteField.getValue());
        } else if(field == &eventVelocityField) {
            selectedEvent->setVelocity(eventVelocityField.getValue());
        } else if(field == &eventGateField) {
            selectedEvent->setGate(eventGateField.getValue());
        } else if(field == &eventDelayField) {
            selectedEvent->setDelay(eventDelayField.getValue());
        }
    }
    if(field == &barSpeedField) {
        bar->setSpeed(barSpeedField.getValue());
        if(sequencer.getBarIndex() == barIndex) {
            sequencer.setBar(barIndex);
        }
    }
}

void ParameterView::addEvent() {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEvent();
}

void ParameterView::addEvent(SequenceEvent* copy) {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), copy);
    updateSelectedEvent();
}

void ParameterView::deleteEvent() {
    AppData::data.deleteEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEvent();
}

void ParameterView::copy() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(selectedEvent != NULL) {
            if(copiedEvent != NULL) {
                delete copiedEvent;
            }
            copiedEvent = new SequenceEvent(selectedEvent);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PASTE, LedColour::BLUE);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
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