#include "ParameterView.h"
#include "../Hardware.h"

#include "Org_01.h"

ParameterView::ParameterView(AppData& _appData, Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    sequencer(_sequencer),
    sequenceMatrixView(_sequenceMatrixView) {
    barFields.add(&barLengthField);
    barFields.add(&barSpeedField);
    channelFields.add(&channelMuteField);
    eventFields.add(&eventNoteField);
    eventFields.add(&eventVelocityField);
    eventFields.add(&eventGateField);
    eventFields.add(&eventDelayField);

    sequenceMatrixView.setPlayCursor(false);
    setParameterViewMode(PARAM_MODE_BAR);
}

void ParameterView::render(bool full) {
    if(full) {
        setDirtyScreen();
    }
    if(dirtyScreen) {
        Hardware::display.fillScreen(Colour(0, 0, 0));
    }
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);
    renderMode();
    renderFields();

    sequenceMatrixView.render();

    dirtyScreen = false;
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    Hardware::display.setTextColour(Colour(255, 255, 255));
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

void ParameterView::handleEvent(InterfaceEvent event) {
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
            render();
            break;
        case InterfaceEventType::DATA_INCREMENT:
            fieldIncrement(event.data);
            break;
        case InterfaceEventType::DATA_DECREMENT:
            fieldDecrement(event.data);
            break;
        case InterfaceEventType::KEY_SELECTION:
            if(event.data == EVENT_KEY_PRESSED) {
                cycleParameterViewMode();
                render();
            }
            break;
        case InterfaceEventType::KEY_ADD_DEL:
            if(event.data == EVENT_KEY_PRESSED) {
                if(selectedEvent == NULL) {
                    addEvent();
                } else {
                    deleteEvent();
                }
                render();
            }
            break;
        default:
            break;
    }
}

void ParameterView::cursorUp() {
    sequenceMatrixView.cursorUp();
    updateSelectedChannel();
    render();
}

void ParameterView::cursorDown() {
    sequenceMatrixView.cursorDown();
    updateSelectedChannel();
    render();
}

void ParameterView::cursorLeft() {
    sequenceMatrixView.cursorLeft();
    updateSelectedEvent();
    render();
}

void ParameterView::cursorRight() {
    sequenceMatrixView.cursorRight();
    updateSelectedEvent();
    render();
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
            setSelectionMode(ParameterViewSelectionMode::SELECT_PARAMETER);
            break;
        case PARAM_MODE_CHANNEL:
            setSelectionMode(selectionMode == ParameterViewSelectionMode::SELECT_PARAMETER ?
                             ParameterViewSelectionMode::SELECT_CHANNEL : ParameterViewSelectionMode::SELECT_PARAMETER);
            break;
        case PARAM_MODE_EVENT:
            setSelectionMode(selectionMode == ParameterViewSelectionMode::SELECT_PARAMETER ?
                             ParameterViewSelectionMode::SELECT_EVENT : ParameterViewSelectionMode::SELECT_PARAMETER);
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
    parameterViewMode = _parameterViewMode;
    switch(parameterViewMode) {
        case PARAM_MODE_BAR:
            visibleFields = &barFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_PARAMETER);
            break;
        case PARAM_MODE_CHANNEL:
            visibleFields = &channelFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_CHANNEL);
            if(selectionMode != ParameterViewSelectionMode::SELECT_PARAMETER) {
                setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            }
            break;
        case PARAM_MODE_EVENT:
            visibleFields = &eventFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_EVENT);
            if(selectionMode != ParameterViewSelectionMode::SELECT_PARAMETER) {
                setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            }
            updateSelectedEvent();
            break;
    };
    setSelectedField(visibleFields->size() == 0 ? -1 : 0);
    setDirtyScreen();
}

void ParameterView::updateSelectedBar() {
    bar = appData.getBar(barIndex);
    barLengthField.setValue(bar->getLength());
    barSpeedField.setValue(bar->getSpeed());
}

void ParameterView::updateSelectedChannel() {
    selectedPattern = bar->getPattern(sequenceMatrixView.getSelectCursorChannel());
    SequenceChannel selectedChannel = appData.getChannel(sequenceMatrixView.getSelectCursorChannel());
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
    } else {
        setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
        for(int i = 0; i < eventFields.size(); i++) {
            eventFields.get(i)->setEnabled(false);
        }
        setDirtyScreen();
    }
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
    appData.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEvent();
}

void ParameterView::deleteEvent() {
    appData.deleteEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEvent();
}
