#include "ParameterView.h"

#include <Fonts/Org_01.h>

#include "../Events.h"
#include "../components/IntegerParameterField.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7
#define FIELD_NAME_WIDTH 45
#define FIELD_VALUE_WIDTH 30

ParameterView::ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    display(_display),
    sequenceMatrixView(_sequenceMatrixView) {
    barFields.add(new IntegerParameterField("LENGTH", 16));
    barFields.add(new IntegerParameterField("BPM", 120));
    channelFields.add(new IntegerParameterField("MUTE", 0));
    eventFields.add(new IntegerParameterField("NOTE", 84));
    eventFields.add(new IntegerParameterField("GATE", 50));
    eventFields.add(new IntegerParameterField("DELAY", 0));
    eventFields.add(new IntegerParameterField("RATCHET", 0));
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
            if(selectionMode == SELECT_EVENT) {
                sequenceMatrixView.cursorUp();
            } else if(selectionMode == SELECT_CHANNEL) {
            } else {
                prevParameter();
            }
            break;
        case STICK_DOWN:
            if(selectionMode == SELECT_EVENT) {
                sequenceMatrixView.cursorDown();
            } else if(selectionMode == SELECT_CHANNEL) {
            } else {
                nextParameter();
            }
            break;
        case STICK_LEFT:
            if(selectionMode == SELECT_EVENT) {
                sequenceMatrixView.cursorLeft();
            }
            break;
        case STICK_RIGHT:
            if(selectionMode == SELECT_EVENT) {
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
            setSelectionMode(SELECT_PARAMETER);
            break;
        case PARAM_MODE_CHANNEL:
            setSelectionMode(selectionMode == SELECT_PARAMETER ? SELECT_CHANNEL : SELECT_PARAMETER);
            break;
        case PARAM_MODE_EVENT:
            setSelectionMode(selectionMode == SELECT_PARAMETER ? SELECT_EVENT : SELECT_PARAMETER);
            break;
    }
}

void ParameterView::setSelectionMode(SelectionMode _selectionMode) {
    selectionMode = _selectionMode;
    if(selectionMode == SELECT_EVENT) {
        sequenceMatrixView.setSelectCursor(true);
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
            setSelectionMode(SELECT_PARAMETER);
            break;
        case PARAM_MODE_CHANNEL:
            visibleFields = &channelFields;
            if(selectionMode != SELECT_PARAMETER) {
                setSelectionMode(SELECT_CHANNEL);
            }
            break;
        case PARAM_MODE_EVENT:
            visibleFields = &eventFields;
            if(selectionMode != SELECT_PARAMETER) {
                setSelectionMode(SELECT_EVENT);
            }
            break;
    };
    if(visibleFields->size() == 0) {
        selectedFieldIndex = -1;
    }
}
