#include "SequenceView.h"

#include <Fonts/Org_01.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

#define CHANNEL_HEIGHT 14
#define BAR_WIDTH 19

#define VISIBLE_BARS DISPLAY_WIDTH / BAR_WIDTH + 1

#define GRID_COLOUR Colour(20, 20, 20)
#define DATA_COLOUR Colour(0, 40, 80)
#define CURSOR_COLOUR Colour(255, 0, 0)

SequenceView::SequenceView(AppData& _appData, Display& _display) :
    appData(_appData),
    display(_display) {
    cursorChannel = 0;
    cursorBar = 0;
}

void SequenceView::render() {
    renderStatusBar();
    renderGrid();
    renderSequence();
    renderCursor();
}

void SequenceView::renderStatusBar() {
    display.setTextSize(1);
    display.setTextColour(Colour(255, 255, 255));
    display.setFont(Org_01);
    display.setCursor(0, 12);
    display.print("SELECT");
}

void SequenceView::renderGrid() {
    int16_t top = 15;
    for(int16_t channel = 0; channel < SEQUENCE_CHANNELS+1; channel++) {
        display.drawLine(0, top, 128, top, GRID_COLOUR);
        top += CHANNEL_HEIGHT;
    }
    int16_t left = 0;
    for(int16_t channel = 0; channel < SEQUENCE_CHANNELS+1; channel++) {
        display.drawLine(left, 15, left, 128, GRID_COLOUR);
        left += BAR_WIDTH;
    }
}

void SequenceView::renderSequence() {
    short top = 15;
    for(short channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        short left = 0;
        for(short bar = 0; bar < VISIBLE_BARS; bar++) {
            SequencePattern* pattern = appData.sequence.channels[channel].patterns.get(bar);
            if(pattern != NULL) {
                display.fillRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, DATA_COLOUR);
                display.setCursor(left+5, top+9);
                display.print(pattern->id, HEX);
            }
            left += BAR_WIDTH;
        }
        top += CHANNEL_HEIGHT;
    }
}

void SequenceView::renderCursor() {
    short top = 15+(cursorChannel*CHANNEL_HEIGHT);
    short left = cursorBar*BAR_WIDTH;
    display.drawRect(left, top, BAR_WIDTH+1, CHANNEL_HEIGHT+1, CURSOR_COLOUR);
    display.drawRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, CURSOR_COLOUR);
    display.drawLine(left, 15, left, 128, CURSOR_COLOUR);
}
