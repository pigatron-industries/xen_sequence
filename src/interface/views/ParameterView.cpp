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

    sequenceMatrixView.setCursor(true);
    sequenceMatrixView.setBar(bar);
    sequenceMatrixView.render();
}

void ParameterView::handleEvent(Event event) {
    switch(event) {
        case STICK_UP:
            sequenceMatrixView.cursorUp();
            break;
        case STICK_DOWN:
            sequenceMatrixView.cursorDown();
            break;
        case STICK_LEFT:
            sequenceMatrixView.cursorLeft();
            break;
        case STICK_RIGHT:
            sequenceMatrixView.cursorRight();
            break;
        default:
            break;
    }
}

void ParameterView::setBar(uint16_t _bar) {
    bar = _bar;
};
