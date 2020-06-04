#include "SequenceMatrixView.h"


SequenceMatrixView::SequenceMatrixView(AppData& _appData, Matrix& _matrix):
    appData(_appData),
    matrix(_matrix) {
}

void SequenceMatrixView::render() {
    renderData();
    renderCursor();
    matrix.update();
}

void SequenceMatrixView::renderData() {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = appData.getSequence().getChannel(channel).getPatterns().get(bar);
        if(pattern != NULL) {
            for(uint8_t tick = 0; tick < MATRIX_COLS; tick++) {
                if(pattern->getEvents().get(tick) != NULL) {
                    matrix.setPixel(channel, tick, CRGB::Blue);
                } else {
                    matrix.setPixel(channel, tick, CRGB::Black);
                }
            }
        } else {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix.setPixel(channel, i, CRGB::Black);
            }
        }
    }
}

void SequenceMatrixView::renderCursor() {
    if(showCursor) {
        CRGB colour = matrix.getPixel(cursorChannel, cursorTick);
        colour += CRGB::Red;
        matrix.setPixel(cursorChannel, cursorTick, colour);
    }
}

void SequenceMatrixView::setBar(int _bar) {
    bar = _bar;
}

void SequenceMatrixView::setCursor(bool _showCursor) {
    showCursor = _showCursor;
}

void SequenceMatrixView::cursorUp() {
    if(cursorChannel > 0) {
        cursorChannel--;
        render();
    }
}

void SequenceMatrixView::cursorDown() {
    if(cursorChannel < SEQUENCE_CHANNELS-1) {
        cursorChannel++;
        render();
    }
}

void SequenceMatrixView::cursorLeft() {
    if(cursorTick > 0) {
        cursorTick--;
        render();
    }
}

void SequenceMatrixView::cursorRight() {
    if(cursorTick < MATRIX_COLS-1) {
        cursorTick++;
        render();
    }
}
