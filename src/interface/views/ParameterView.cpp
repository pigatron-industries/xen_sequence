#include "ParameterView.h"

#include <Fonts/Org_01.h>

#include "../Events.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7
#define FIELD_NAME_WIDTH 45
#define FIELD_VALUE_WIDTH 30

ParameterView::ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    display(_display),
    sequenceMatrixView(_sequenceMatrixView) {
    setMode(PARAM_MODE_BAR);
}

void ParameterView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);
    switch(mode) {
        case PARAM_MODE_BAR:
            renderBarParameters();
            break;
        case PARAM_MODE_CHANNEL:
            renderChannelParameters();
            break;
        case PARAM_MODE_EVENT:
            renderEventParameters();
            break;
    }
    renderEventParameters();
    display.updateScreen();

    if(mode == PARAM_MODE_EVENT) {
        sequenceMatrixView.setSelectCursor(true);
    }
    sequenceMatrixView.setPlayCursor(false);
    sequenceMatrixView.setBar(bar);
    sequenceMatrixView.render();
}

void ParameterView::renderBarParameters() {
    renderTextField(0, Parameter::PARAM_SELECT, "SELECT:", "BAR");
    renderTextField(1, Parameter::PARAM_BAR_LENGTH, "LENGTH:", "16");
    renderTextField(2, Parameter::PARAM_BAR_BPM, "BPM:", "120");
}

void ParameterView::renderChannelParameters() {

}

void ParameterView::renderEventParameters() {
    // int row = 0;
    // display.setTextColour(Colour(255, 255, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("EVENT");

    // row = 1;
    // display.setTextColour(Colour(0, 128, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("TYPE:");
    // display.setTextColour(Colour(255, 255, 0));
    // display.setCursor(50, (row*FIELD_HEIGHT)+12);
    // display.print("NOTE");
    //
    // row = 2;
    // display.setTextColour(Colour(0, 128, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("PITCH:");
    // display.setTextColour(Colour(0, 0, 0));
    // display.setCursor(50, (row*FIELD_HEIGHT)+12);
    // display.fillRect(49, (row*FIELD_HEIGHT)+6, 30, 9, Colour(255, 255, 0));
    // display.print("A#4");
    //
    // row = 3;
    // display.setTextColour(Colour(0, 128, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("GATE:");
    // display.setTextColour(Colour(255, 255, 0));
    // display.setCursor(50, (row*FIELD_HEIGHT)+12);
    // display.print("25%");
    //
    // row = 4;
    // display.setTextColour(Colour(0, 128, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("DELAY:");
    // display.setTextColour(Colour(255, 255, 0));
    // display.setCursor(50, (row*FIELD_HEIGHT)+12);
    // display.print("0%");
    //
    // row = 5;
    // display.setTextColour(Colour(0, 128, 255));
    // display.setCursor(0, (row*FIELD_HEIGHT)+12);
    // display.print("RATCHET:");
    // display.setTextColour(Colour(255, 255, 0));
    // display.setCursor(50, (row*FIELD_HEIGHT)+12);
    // display.print("0 1 1");
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
    selectedParameterIndex++;
    if(selectedParameterIndex >= visibleParameters.size()) {
        selectedParameterIndex = 0;
    }
    selectedParameter = visibleParameters.get(selectedParameterIndex);
    render();
}

void ParameterView::prevParameter() {
    selectedParameterIndex--;
    if(selectedParameterIndex < 0) {
        selectedParameterIndex = visibleParameters.size()-1;
    }
    selectedParameter = visibleParameters.get(selectedParameterIndex);
    render();
}

void ParameterView::setBar(uint16_t _bar) {
    bar = _bar;
};

void ParameterView::setMode(ParameterViewMode _mode) {
    mode = _mode;
    visibleParameters.clear();
    selectedParameterIndex = 0;
    switch(mode) {
        case PARAM_MODE_BAR:
            visibleParameters.add(PARAM_SELECT);
            visibleParameters.add(PARAM_BAR_LENGTH);
            visibleParameters.add(PARAM_BAR_BPM);
            break;
        case PARAM_MODE_CHANNEL:
            visibleParameters.add(PARAM_SELECT);
            visibleParameters.add(PARAM_CHANNEL_MUTE);
            break;
        case PARAM_MODE_EVENT:
            visibleParameters.add(PARAM_SELECT);
            visibleParameters.add(PARAM_EVENT_PITCH);
            visibleParameters.add(PARAM_EVENT_GATE);
            visibleParameters.add(PARAM_EVENT_DELAY);
            visibleParameters.add(PARAM_EVENT_RATCHET);
            break;
    };
}

void ParameterView::renderTextField(uint8_t row, Parameter param, const char* name, const char* value) {
    uint8_t top = row*FIELD_HEIGHT;

    display.setTextColour(Colour(0, 128, 255));
    display.setCursor(0, top+TEXT_HEIGHT);
    display.print(name);

    if(selectedParameter == param) {
        display.fillRect(FIELD_NAME_WIDTH-2, top+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, Colour(255, 255, 0));
        display.setTextColour(Colour(0, 0, 0));
    } else {
        display.setTextColour(Colour(255, 255, 0));
    }

    display.setCursor(FIELD_NAME_WIDTH, top+TEXT_HEIGHT);
    display.print(value);
}
