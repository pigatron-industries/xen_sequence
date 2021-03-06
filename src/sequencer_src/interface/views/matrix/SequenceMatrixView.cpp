#include "SequenceMatrixView.h"
#include "interface/Hardware.h"
#include "lib/util/debug.h"

#define OFF_PIXEL CRGB::Black
#define DATA_PIXEL CRGB(0x000088)
#define SELECT_CURSOR_PIXEL CRGB(0x880000)
#define SELECT_CURSOR_ACTIVE_PIXEL CRGB(0x880000)
#define PLAY_CURSOR_PIXEL CRGB(0x008800)
#define MARKER_PIXEL CRGB(0x880000)



SequenceMatrixView::SequenceMatrixView() {
}

void SequenceMatrixView::render() {
    renderData();
    renderSelectCursor();
    renderMarker();
    renderPlayCursor();
    Hardware::ledMatrix.update();
}

void SequenceMatrixView::renderData() {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = AppData::data.getPattern(barIndex, channel);
        if(pattern != NULL) {
            for(uint8_t tick = 0; tick < MATRIX_COLS; tick++) {
                if(pattern->getEvents().get(tick) != NULL) {
                    Hardware::ledMatrix.setPixel(channel, tick, DATA_PIXEL);
                } else {
                    Hardware::ledMatrix.setPixel(channel, tick, OFF_PIXEL);
                }
            }
        } else {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                Hardware::ledMatrix.setPixel(channel, i, OFF_PIXEL);
            }
        }
    }
}

void SequenceMatrixView::renderSelectCursor() {
    if(selectionMode == SequenceMatrixSelectionMode::SELECT_EVENT) {
        CRGB colour = Hardware::ledMatrix.getPixel(selectCursorChannel, selectCursorTick);
        colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
        Hardware::ledMatrix.setPixel(selectCursorChannel, selectCursorTick, colour);
    } else if(selectionMode == SequenceMatrixSelectionMode::SELECT_CHANNEL) {
        for(int i = 0; i < MATRIX_COLS; i++) {
            CRGB colour = Hardware::ledMatrix.getPixel(selectCursorChannel, i);
            colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
            Hardware::ledMatrix.setPixel(selectCursorChannel, i, colour);
        }
    }
}

void SequenceMatrixView::renderPlayCursor() {
    uint8_t playCursorTick = Sequencer::sequencer.getTickIndex();
    if(Sequencer::sequencer.isPlaying() && Sequencer::sequencer.getBarIndex() == barIndex) {
        for(int channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
            CRGB colour = Hardware::ledMatrix.getPixel(channel, playCursorTick);
            colour += PLAY_CURSOR_PIXEL;
            Hardware::ledMatrix.setPixel(channel, playCursorTick, colour);
        }
    }
}

void SequenceMatrixView::renderMarker() {
    if(showMarker) {
        CRGB colour = Hardware::ledMatrix.getPixel(markerChannel, markerTick);
        colour += selectionActive ? SELECT_CURSOR_ACTIVE_PIXEL : SELECT_CURSOR_PIXEL;
        Hardware::ledMatrix.setPixel(markerChannel, markerTick, colour);
    }
}

void SequenceMatrixView::setBar(int _barIndex) {
    barIndex = _barIndex;
}

void SequenceMatrixView::setPlayCursor(bool _showPlayCursor) {
    showPlayCursor =_showPlayCursor;
}

void SequenceMatrixView::setMarker(uint8_t channel, uint8_t tick) {
    showMarker = true;
    markerChannel = channel;
    markerTick = tick;
}

void SequenceMatrixView::clearMarker() {
    showMarker = false;
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
    } else {
        selectCursorTick = MATRIX_COLS-1;
    }
}

void SequenceMatrixView::cursorRight() {
    if(selectCursorTick < MATRIX_COLS-1) {
        selectCursorTick++;
    } else {
        selectCursorTick = 0;
    }
}
