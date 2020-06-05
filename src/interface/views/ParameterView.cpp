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
    setMode(PARAM_MODE_BAR);
}

void ParameterView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);
    renderFields();
    display.updateScreen();

    if(mode == PARAM_MODE_EVENT) {
        sequenceMatrixView.setSelectCursor(true);
    }
    sequenceMatrixView.setPlayCursor(false);
    sequenceMatrixView.setBar(bar);
    sequenceMatrixView.render();
}

void ParameterView::renderFields() {
    for(int row = 0; row < visibleFields->size(); row++) {
        bool selected = selectedFieldIndex == row;
        barFields.get(row)->render(display, row, selected);
    }
}

void ParameterView::handleEvent(Event event) {
    switch(event) {
        case STICK_UP:
            prevParameter();
            // if(mode == PARAM_MODE_EVENT) {
            //     sequenceMatrixView.cursorUp();
            // }
            break;
        case STICK_DOWN:
            nextParameter();
            // if(mode == PARAM_MODE_EVENT) {
            //     sequenceMatrixView.cursorDown();
            // }
            break;
        case STICK_LEFT:
            // if(mode == PARAM_MODE_EVENT) {
            //     sequenceMatrixView.cursorLeft();
            // }
            break;
        case STICK_RIGHT:
            // if(mode == PARAM_MODE_EVENT) {
            //     sequenceMatrixView.cursorRight();
            // }
            break;
        case STICK_PRESS:
            // if(mode == PARAM_MODE_EVENT) {
            //
            // }
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

void ParameterView::setMode(ParameterViewMode _mode) {
    mode = _mode;
    switch(mode) {
        case PARAM_MODE_BAR:
            visibleFields = &barFields;
            break;
        case PARAM_MODE_CHANNEL:
            visibleFields = &channelFields;
            break;
        case PARAM_MODE_EVENT:
            visibleFields = &eventFields;
            break;
    };
}
