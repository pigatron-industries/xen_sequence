#include "SequenceMatrixView.h"

#define OFF_PIXEL CRGB::Black
#define DATA_PIXEL CRGB(0x000088)
#define SELECT_CURSOR_PIXEL CRGB(0x880000)
#define SELECT_CURSOR_ACTIVE_PIXEL CRGB(0xFF0000)
#define PLAY_CURSOR_PIXEL CRGB(0x008800)



SequenceMatrixView::SequenceMatrixView(AppData& _appData, Matrix& _matrix):
    appData(_appData),
    matrix(_matrix) {
}

void SequenceMatrixView::render() {
    renderData();
    renderSelectCursor();
    renderPlayCursor();
    matrix.update();
}

void SequenceMatrixView::renderData() {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = appData.getSequence().getChannel(channel).getPatterns().get(bar);
        if(pattern != NULL) {
            for(uint8_t tick = 0; tick < MATRIX_COLS; tick++) {
                if(pattern->getEvents().get(tick) != NULL) {
                    matrix.setPixel(channel, tick, DATA_PIXEL);
                } else {
                    matrix.setPixel(channel, tick, OFF_PIXEL);
                }
            }
        } else {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix.setPixel(channel, i, OFF_PIXEL);
            }
        }
    }
}

void SequenceMatrixView::renderSelectCursor() {
    if(selectionMode == SequenceMatrixSelectionMode::SELECT_EVENT) {
        CRGB colour = matrix.getPixel(selectCursorChannel, selectCursorTick);
        colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
        matrix.setPixel(selectCursorChannel, selectCursorTick, colour);
    } else if(selectionMode == SequenceMatrixSelectionMode::SELECT_CHANNEL) {
        for(int i = 0; i < MATRIX_COLS; i++) {
            CRGB colour = matrix.getPixel(selectCursorChannel, i);
            colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
            matrix.setPixel(selectCursorChannel, i, colour);
        }
    }
}

void SequenceMatrixView::renderPlayCursor() {
    if(showPlayCursor) {
        for(int channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
            CRGB colour = matrix.getPixel(channel, playCursorTick);
            colour += PLAY_CURSOR_PIXEL;
            matrix.setPixel(channel, playCursorTick, colour);
        }
    }
}

void SequenceMatrixView::setBar(int _bar) {
    bar = _bar;
}

void SequenceMatrixView::setPlayCursor(bool _showPlayCursor) {
    showPlayCursor =_showPlayCursor;
}

void SequenceMatrixView::cursorUp() {
    if(selectCursorChannel > 0) {
        selectCursorChannel--;
        render();
    }
}

void SequenceMatrixView::cursorDown() {
    if(selectCursorChannel < SEQUENCE_CHANNELS-1) {
        selectCursorChannel++;
        render();
    }
}

void SequenceMatrixView::cursorLeft() {
    if(selectCursorTick > 0) {
        selectCursorTick--;
        render();
    }
}

void SequenceMatrixView::cursorRight() {
    if(selectCursorTick < MATRIX_COLS-1) {
        selectCursorTick++;
        render();
    }
}
