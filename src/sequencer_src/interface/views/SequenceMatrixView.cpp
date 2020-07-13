#include "SequenceMatrixView.h"

#define OFF_PIXEL CRGB::Black
#define DATA_PIXEL CRGB(0x000088)
#define SELECT_CURSOR_PIXEL CRGB(0x880000)
#define SELECT_CURSOR_ACTIVE_PIXEL CRGB(0x880000)
#define PLAY_CURSOR_PIXEL CRGB(0x008800)



SequenceMatrixView::SequenceMatrixView(AppData& _appData, Sequencer& _sequencer, LedMatrix& _ledMatrix):
    appData(_appData),
    sequencer(_sequencer),
    ledMatrix(_ledMatrix) {
}

void SequenceMatrixView::render() {
    renderData();
    renderSelectCursor();
    renderPlayCursor();
    ledMatrix.update();
}

void SequenceMatrixView::renderData() {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = appData.getPattern(barIndex, channel);
        if(pattern != NULL) {
            for(uint8_t tick = 0; tick < MATRIX_COLS; tick++) {
                if(pattern->getEvents().get(tick) != NULL) {
                    ledMatrix.setPixel(channel, tick, DATA_PIXEL);
                } else {
                    ledMatrix.setPixel(channel, tick, OFF_PIXEL);
                }
            }
        } else {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                ledMatrix.setPixel(channel, i, OFF_PIXEL);
            }
        }
    }
}

void SequenceMatrixView::renderSelectCursor() {
    if(selectionMode == SequenceMatrixSelectionMode::SELECT_EVENT) {
        CRGB colour = ledMatrix.getPixel(selectCursorChannel, selectCursorTick);
        colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
        ledMatrix.setPixel(selectCursorChannel, selectCursorTick, colour);
    } else if(selectionMode == SequenceMatrixSelectionMode::SELECT_CHANNEL) {
        for(int i = 0; i < MATRIX_COLS; i++) {
            CRGB colour = ledMatrix.getPixel(selectCursorChannel, i);
            colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
            ledMatrix.setPixel(selectCursorChannel, i, colour);
        }
    }
}

void SequenceMatrixView::renderPlayCursor() {
    uint8_t playCursorTick = sequencer.getTickIndex();
    if(sequencer.isPlaying() && sequencer.getBarIndex() == barIndex) {
        for(int channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
            CRGB colour = ledMatrix.getPixel(channel, playCursorTick);
            colour += PLAY_CURSOR_PIXEL;
            ledMatrix.setPixel(channel, playCursorTick, colour);
        }
    }
}

void SequenceMatrixView::setBar(int _barIndex) {
    barIndex = _barIndex;
}

void SequenceMatrixView::setPlayCursor(bool _showPlayCursor) {
    showPlayCursor =_showPlayCursor;
}

void SequenceMatrixView::cursorUp() {
    if(selectCursorChannel > 0) {
        selectCursorChannel--;
    }
}

void SequenceMatrixView::cursorDown() {
    if(selectCursorChannel < SEQUENCE_CHANNELS-1) {
        selectCursorChannel++;
    }
}

void SequenceMatrixView::cursorLeft() {
    if(selectCursorTick > 0) {
        selectCursorTick--;
    }
}

void SequenceMatrixView::cursorRight() {
    if(selectCursorTick < MATRIX_COLS-1) {
        selectCursorTick++;
    }
}
