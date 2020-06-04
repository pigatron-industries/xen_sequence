#include "ParameterView.h"

#include <Fonts/Org_01.h>

#include "../Events.h"

ParameterView::ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    display(_display),
    sequenceMatrixView(_sequenceMatrixView) {
}

void ParameterView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);

    display.updateScreen();
}

void ParameterView::handleEvent(Event event) {
    switch(event) {
        case STICK_UP:
            break;
        case STICK_DOWN:
            break;
        case STICK_LEFT:
            break;
        case STICK_RIGHT:
            break;
        default:
            break;
    }
}

void ParameterView::setBar(uint16_t _bar) {
    _bar = bar;
    render();
};
