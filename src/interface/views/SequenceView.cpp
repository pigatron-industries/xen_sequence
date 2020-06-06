#include "SequenceView.h"

#include <Fonts/Org_01.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

#define STATUS_HEIGHT 15
#define CHANNEL_HEIGHT 14
#define BAR_WIDTH 19

#define VISIBLE_BARS DISPLAY_WIDTH / BAR_WIDTH + 1

#define GRID_COLOUR Colour(20, 20, 20)
#define GRID_TEXT_COLOUR Colour(127, 127, 127)
#define DATA_COLOUR Colour(0, 40, 80)
#define DATA_TEXT_COLOUR Colour(255, 255, 255)
#define CURSOR_COLOUR Colour(255, 0, 0)

SequenceView::SequenceView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView) :
    appData(_appData),
    display(_display),
    sequenceMatrixView(_sequenceMatrixView) {
    cursorChannel = 0;
    cursorBar = 0;
    scrollBar = 0;
}

void SequenceView::render() {
    display.fillScreen(Colour(0, 0, 0));
    display.setFont(Org_01);
    display.setTextSize(1);
    renderStatusBar();
    renderGrid();
    renderSequence();
    renderCursor();
    display.updateScreen();

    sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
    sequenceMatrixView.setBar(cursorBar);
    sequenceMatrixView.render();
}

void SequenceView::handleEvent(Event event) {
    switch(event) {
        case STICK_UP:
            cursorUp();
            break;
        case STICK_DOWN:
            cursorDown();
            break;
        case STICK_LEFT:
            cursorLeft();
            break;
        case STICK_RIGHT:
            cursorRight();
            break;
        default:
            break;
    }
}

void SequenceView::cursorUp() {
    if(cursorChannel > 0) {
        cursorChannel--;
        render();
    }
}

void SequenceView::cursorDown() {
    if(cursorChannel < SEQUENCE_CHANNELS-1) {
        cursorChannel++;
        render();
    }
}

void SequenceView::cursorLeft() {
    if(cursorBar > 0) {
        cursorBar--;
        if(cursorBar == scrollBar-1) {
            scrollBar--;
        }
        render();
    }
}

void SequenceView::cursorRight() {
    // TODO find max sequence length
    if(cursorBar < 10) {
        cursorBar++;
        if(cursorBar == scrollBar+VISIBLE_BARS-1) {
            scrollBar++;
        }
        render();
    }
}

void SequenceView::renderStatusBar() {
    display.setTextColour(Colour(255, 255, 255));
    //display.setCursor(0, 12);
    //display.print("SELECT");
}

void SequenceView::renderGrid() {
    display.setTextColour(GRID_TEXT_COLOUR);
    int16_t top = STATUS_HEIGHT;
    for(int16_t channel = 0; channel < SEQUENCE_CHANNELS+1; channel++) {
        display.drawLine(0, top, DISPLAY_WIDTH, top, GRID_COLOUR);
        top += CHANNEL_HEIGHT;
    }
    int16_t left = 0;
    for(int16_t bar = scrollBar; bar < scrollBar+VISIBLE_BARS; bar++) {
        display.drawLine(left, STATUS_HEIGHT, left, DISPLAY_HEIGHT, GRID_COLOUR);
        display.setCursor(left, 12);
        display.print(bar, HEX);
        left += BAR_WIDTH;
    }
}

void SequenceView::renderSequence() {
    display.setTextColour(DATA_TEXT_COLOUR);
    short top = STATUS_HEIGHT;
    for(short channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        short left = 0;
        for(short bar = scrollBar; bar < scrollBar+VISIBLE_BARS; bar++) {
            SequencePattern* pattern = appData.getSequence().getChannel(channel).getPatterns().get(bar);
            if(pattern != NULL) {
                display.fillRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, DATA_COLOUR);
                display.setCursor(left+5, top+9);
                display.print(pattern->getId(), HEX);
            }
            left += BAR_WIDTH;
        }
        top += CHANNEL_HEIGHT;
    }
}

void SequenceView::renderCursor() {
    short top = STATUS_HEIGHT+(cursorChannel*CHANNEL_HEIGHT);
    short left = (cursorBar-scrollBar)*BAR_WIDTH;
    display.drawRect(left, top, BAR_WIDTH+1, CHANNEL_HEIGHT+1, CURSOR_COLOUR);
    display.drawRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, CURSOR_COLOUR);
    display.drawLine(left, STATUS_HEIGHT, left, DISPLAY_HEIGHT, CURSOR_COLOUR);
    display.drawLine(left+BAR_WIDTH, STATUS_HEIGHT, left+BAR_WIDTH, DISPLAY_HEIGHT, CURSOR_COLOUR);
}