#include "ParameterView.h"

#include <Fonts/Org_01.h>

#include "../Events.h"

ParameterView::ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
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
    setParameterViewMode(PARAM_MODE_CHANNEL);
}

void ParameterView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);
    renderMode();
    renderFields();
    display.updateScreen();

    sequenceMatrixView.setBar(bar);
    sequenceMatrixView.render();
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    display.setTextColour(Colour(255, 255, 255));
    display.setCursor(0, top+TEXT_HEIGHT);
    display.print(parameterViewMode == PARAM_MODE_BAR ? "BAR" : parameterViewMode == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::renderFields() {
    for(int row = 0; row < visibleFields->size(); row++) {
        bool selected = selectedFieldIndex == row;
        visibleFields->get(row)->render(display, row+1, selected);
    }
}

void ParameterView::handleEvent(Event event) {
    ParameterField* field = getSelectedField();
    switch(event) {
        case STICK_UP:
            if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT || selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
                sequenceMatrixView.cursorUp();

            } else {
                prevParameter();
            }
            break;
        case STICK_DOWN:
            if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT || selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
                sequenceMatrixView.cursorDown();
            } else {
                nextParameter();
            }
            break;
        case STICK_LEFT:
            if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                sequenceMatrixView.cursorLeft();
            }
            break;
        case STICK_RIGHT:
            if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                sequenceMatrixView.cursorRight();
            }
            break;
        case STICK_PRESS:
            cycleSelectionMode();
            render();
            break;
        case DATA_INCREMENT:
            if(field != NULL) {
                field->increment();
                render();
            }
            break;
        case DATA_DECREMENT:
            if(field != NULL) {
                field->decrement();
                render();
            }
            break;
        case DATA_PRESS:
            cycleParameterViewMode();
            render();
            break;
        default:
            break;
    }
}

void ParameterView::nextParameter() {
    selectedFieldIndex++;
    if(selectedFieldIndex >= visibleFields->size()) {
        selectedFieldIndex = 0;
    }
    render();
}

void ParameterView::prevParameter() {
    selectedFieldIndex--;
    if(selectedFieldIndex < 0) {
        selectedFieldIndex = visibleFields->size()-1;
    }
    render();
}

void ParameterView::setBar(uint16_t _bar) {
    bar = _bar;
};

ParameterField* ParameterView::getSelectedField() {
    if(selectedFieldIndex >= 0) {
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
            break;
    };
    if(visibleFields->size() == 0) {
        selectedFieldIndex = -1;
    }
}

void ParameterView::updateFieldData() {

}
