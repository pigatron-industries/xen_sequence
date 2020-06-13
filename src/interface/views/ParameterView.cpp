#include "ParameterView.h"

#include <Fonts/Org_01.h>

ParameterView::ParameterView(AppData& _appData, Sequencer& _sequencer, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    sequencer(_sequencer),
    display(_display),
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

void ParameterView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);
    renderMode();
    renderFields();
    display.updateScreen();

    sequenceMatrixView.render();
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    display.setTextColour(Colour(255, 255, 255));
    display.setCursor(0, top+TEXT_HEIGHT);
    display.print(parameterViewMode == PARAM_MODE_BAR ? "BAR" : parameterViewMode == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::renderFields() {
    for(uint8_t row = 0; row < visibleFields->size(); row++) {
        renderField(row);
    }
}

void ParameterView::renderField(uint8_t row) {
    bool selected = selectedFieldIndex == row;
    visibleFields->get(row)->render(display, row+1, selected);
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
        case InterfaceEventType::STICK_PRESS:
            cycleSelectionMode();
            render();
            break;
        case InterfaceEventType::DATA_INCREMENT:
            fieldIncrement(event.data);
            break;
        case InterfaceEventType::DATA_DECREMENT:
            fieldDecrement(event.data);
            break;
        case InterfaceEventType::DATA_PRESS:
            cycleParameterViewMode();
            render();
            break;
        case InterfaceEventType::KEY_ADD_DEL:
            if(selectedEvent == NULL) {
                addEvent();
            } else {
                deleteEvent();
            }
            render();
            break;
        default:
            break;
    }
}

void ParameterView::cursorUp() {
    switch(selectionMode) {
        case ParameterViewSelectionMode::SELECT_PARAMETER:
            prevParameter();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_EVENT:
            sequenceMatrixView.cursorUp();
            updateSelectedEvent();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_CHANNEL:
            sequenceMatrixView.cursorUp();
            updateSelectedChannel();
            render();
            break;
    }
}

void ParameterView::cursorDown() {
    switch(selectionMode) {
        case ParameterViewSelectionMode::SELECT_PARAMETER:
            nextParameter();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_EVENT:
            sequenceMatrixView.cursorDown();
            updateSelectedEvent();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_CHANNEL:
            sequenceMatrixView.cursorDown();
            updateSelectedChannel();
            render();
            break;
    }
}

void ParameterView::cursorLeft() {
    switch(selectionMode) {
        case ParameterViewSelectionMode::SELECT_PARAMETER:
            break;
        case ParameterViewSelectionMode::SELECT_EVENT:
            sequenceMatrixView.cursorLeft();
            updateSelectedEvent();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_CHANNEL:
            break;
    }
}

void ParameterView::cursorRight() {
    switch(selectionMode) {
        case ParameterViewSelectionMode::SELECT_PARAMETER:
            break;
        case ParameterViewSelectionMode::SELECT_EVENT:
            sequenceMatrixView.cursorRight();
            updateSelectedEvent();
            render();
            break;
        case ParameterViewSelectionMode::SELECT_CHANNEL:
            break;
    }
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

void ParameterView::nextParameter() {
    selectedFieldIndex++;
    if(selectedFieldIndex >= visibleFields->size()) {
        selectedFieldIndex = 0;
    }
}

void ParameterView::prevParameter() {
    selectedFieldIndex--;
    if(selectedFieldIndex < 0) {
        selectedFieldIndex = visibleFields->size()-1;
    }
}

void ParameterView::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    sequenceMatrixView.setBar(barIndex);
    updateSelectedBar();
};

ParameterField* ParameterView::getSelectedField() {
    if(selectedFieldIndex >= 0 && visibleFields->size() > selectedFieldIndex) {
        return visibleFields->get(selectedFieldIndex);
    } else {
        return NULL;
    }
}

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
    selectedFieldIndex = 0;
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
    if(visibleFields->size() == 0) {
        selectedFieldIndex = -1;
    }
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
        eventNoteField.setValue(selectedEvent->pitch);
        eventVelocityField.setValue(selectedEvent->velocity);
        eventGateField.setValue(selectedEvent->gate);
        eventDelayField.setValue(selectedEvent->delay);
        for(int i = 0; i < eventFields.size(); i++) {
            eventFields.get(i)->setEnabled(true);
        }
    } else {
        setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
        for(int i = 0; i < eventFields.size(); i++) {
            eventFields.get(i)->setEnabled(false);
        }
    }
}

void ParameterView::updateDataFromField(ParameterField* field) {
    if(selectedEvent != NULL) {
        if(field == &eventNoteField) {
            selectedEvent->pitch = eventNoteField.getValue();
        } else if(field == &eventVelocityField) {
            selectedEvent->velocity = eventVelocityField.getValue();
        } else if(field == &eventGateField) {
            selectedEvent->gate = eventGateField.getValue();
        } else if(field == &eventDelayField) {
            selectedEvent->delay = eventDelayField.getValue();
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
