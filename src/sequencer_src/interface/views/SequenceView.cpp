#include "SequenceView.h"
#include "interface/Hardware.h"
#include "model/AppData.h"
#include "lib/util/debug.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

#define STATUS_HEIGHT 15
#define CHANNEL_HEIGHT 14
#define BAR_WIDTH 19

#define VISIBLE_BARS DISPLAY_WIDTH / BAR_WIDTH + 1

#define GRID_COLOUR Colour(20, 20, 20)
#define GRID_TEXT_COLOUR Colour(127, 127, 127)
#define DATA_COLOUR Colour(0, 40, 80)
#define DATA_TEXT_COLOUR Colour::WHITE
#define CURSOR_COLOUR Colour::RED
#define BACKGROUND_COLOUR Colour::BLACK

SequenceView::SequenceView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView) :
        sequencer(_sequencer),
        sequenceMatrixView(_sequenceMatrixView) {
    cursorChannel = 0;
    cursorBar = 0;
    scrollBar = 0;
    copiedPattern = NULL;
}

void SequenceView::init() {
    DEBUG("SequenceView::init");

    sequencer.setBar(cursorBar);
    updateSelectedPattern();
}

void SequenceView::render(GraphicsContext& g) {
    DEBUG("SequenceView::render");

    renderStatusBar();
    renderGrid();
    renderSequence();
    renderCursor();
    Hardware::display.updateScreen();

    sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
    sequenceMatrixView.setBar(cursorBar);
    sequenceMatrixView.render();
}


void SequenceView::renderStatusBar() {
    Hardware::display.setTextColour(Colour(255, 255, 255));
}

void SequenceView::renderGrid() {
    Hardware::display.setTextColour(GRID_TEXT_COLOUR);
    int16_t top = STATUS_HEIGHT;
    for(int16_t channel = 0; channel < SEQUENCE_CHANNELS+1; channel++) {
        Hardware::display.drawLine(0, top, DISPLAY_WIDTH, top, GRID_COLOUR);
        top += CHANNEL_HEIGHT;
    }
    int16_t left = 0;
    for(int16_t bar = scrollBar; bar < scrollBar+VISIBLE_BARS; bar++) {
        Hardware::display.drawLine(left, STATUS_HEIGHT, left, DISPLAY_HEIGHT, GRID_COLOUR);
        Hardware::display.setCursor(left, 12);
        Hardware::display.print(bar, HEX);
        left += BAR_WIDTH;
    }
}

void SequenceView::renderSequence() {
    Hardware::display.setTextColour(DATA_TEXT_COLOUR);
    short top = STATUS_HEIGHT;
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        short left = 0;
        for(int16_t bar = scrollBar; bar < scrollBar+VISIBLE_BARS; bar++) {
            SequencePattern* pattern = AppData::data.getPattern(bar, channel);
            if(pattern != NULL) {
                Hardware::display.fillRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, DATA_COLOUR);
                Hardware::display.setCursor(left+5, top+9);
                Hardware::display.print(pattern->getId(), HEX);
            } else {
                Hardware::display.fillRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, BACKGROUND_COLOUR);
            }
            left += BAR_WIDTH;
        }
        top += CHANNEL_HEIGHT;
    }
}

void SequenceView::renderCursor() {
    short top = STATUS_HEIGHT+(cursorChannel*CHANNEL_HEIGHT);
    short left = (cursorBar-scrollBar)*BAR_WIDTH;
    Hardware::display.drawRect(left, top, BAR_WIDTH+1, CHANNEL_HEIGHT+1, CURSOR_COLOUR);
    Hardware::display.drawRect(left+1, top+1, BAR_WIDTH-1, CHANNEL_HEIGHT-1, CURSOR_COLOUR);
    Hardware::display.drawLine(left, STATUS_HEIGHT, left, DISPLAY_HEIGHT, CURSOR_COLOUR);
    Hardware::display.drawLine(left+BAR_WIDTH, STATUS_HEIGHT, left+BAR_WIDTH, DISPLAY_HEIGHT, CURSOR_COLOUR);
}

InterfaceEvent SequenceView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::STICK_UP:
            cursorUp();
            break;

        case InterfaceEventType::STICK_DOWN:
            cursorDown();
            break;

        case InterfaceEventType::STICK_LEFT:
        case InterfaceEventType::KEY_PREV:
            if(event.data == EVENT_KEY_PRESSED) {
                cursorLeft();
            }
            break;

        case InterfaceEventType::STICK_RIGHT:
        case InterfaceEventType::KEY_NEXT:
            if(event.data == EVENT_KEY_PRESSED) {
                cursorRight();
            }
            break;

        case InterfaceEventType::DATA_INCREMENT:
            incrementPattern();
            break;

        case InterfaceEventType::DATA_DECREMENT:
            decrementPattern();
            break;
        
        case InterfaceEventType::KEY_ADD_DEL:
            if(event.data == EVENT_KEY_PRESSED) {
                SequencePattern* selectedPattern = AppData::data.getPattern(cursorBar, cursorChannel);
                if(selectedPattern != NULL) {
                    deletePattern();
                } else {
                    addPattern();
                }
            }
            break;

        case InterfaceEventType::KEY_COPY:
            if(event.data == EVENT_KEY_PRESSED) {
                copy();
            }
            break;

        case InterfaceEventType::KEY_PASTE:
            if(event.data == EVENT_KEY_PRESSED) {
                paste();
            }
            break;

        case InterfaceEventType::KEY_MOVE:
            if(event.data == EVENT_KEY_PRESSED) {
                drag();
            } else if(event.data == EVENT_KEY_RELEASED) {
                drop();
            }
            break;

        default:
            break;
    }

    return InterfaceEvent::NONE;
}

void SequenceView::cursorUp() {
    if(cursorChannel > 0) {
        cursorChannel--;
        queueRender();
        updateSelectedPattern();
    }
}

void SequenceView::cursorDown() {
    if(cursorChannel < SEQUENCE_CHANNELS-1) {
        cursorChannel++;
        queueRender();
        updateSelectedPattern();
    }
}

void SequenceView::cursorLeft() {
    uint16_t prevCursorBar = cursorBar;
    cursorBar = sequencer.prevBar();
    if(cursorBar != prevCursorBar) {
        if(cursorBar == scrollBar-1) {
            scrollBar--;
        }
        updateSelectedPattern();
        queueRender();
    }
}

void SequenceView::cursorRight() {
    uint16_t prevCursorBar = cursorBar;
    cursorBar = sequencer.nextBar();
    if(cursorBar != prevCursorBar) {
        if(cursorBar == scrollBar+VISIBLE_BARS-1) {
            scrollBar++;
        }
        updateSelectedPattern();
        queueRender();
    }
}

void SequenceView::updateSelectedPattern() {
    SequencePattern* pattern = AppData::data.getPattern(cursorBar, cursorChannel);
    if(pattern != NULL) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
    } else {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::BLUE);
    }
}

void SequenceView::incrementPattern() {
    SequencePattern* pattern = AppData::data.getPattern(cursorBar, cursorChannel);
    uint16_t patternId = pattern->getId();
    patternId++;
    pattern = AppData::data.getPatternById(patternId);
    if(pattern != NULL) {
        AppData::data.setPattern(cursorBar, cursorChannel, pattern);
        queueRender();
    }
}

void SequenceView::decrementPattern() {
    SequencePattern* pattern = AppData::data.getPattern(cursorBar, cursorChannel);
    int patternId = pattern->getId();
    patternId--;
    if(patternId > 0) {
        pattern = AppData::data.getPatternById(patternId);
        if(pattern != NULL) {
            AppData::data.setPattern(cursorBar, cursorChannel, pattern);
            queueRender();
        }
    }
}

void SequenceView::addPattern() {
    //TODO determine most sensible pattern id to add
    SequencePattern* pattern = AppData::data.getPatternById(1);
    if(pattern != NULL) {
        AppData::data.setPattern(cursorBar, cursorChannel, pattern);
    }
    updateSelectedPattern();
    queueRender();
}

void SequenceView::deletePattern() {
    AppData::data.setPattern(cursorBar, cursorChannel, NULL);
    updateSelectedPattern();
    queueRender();
}

void SequenceView::copy() {
    DEBUG("SequenceView::copy")
    SequencePattern* pattern = AppData::data.getPattern(cursorBar, cursorChannel);
    if(pattern != NULL) {
        copiedPattern = AppData::data.copyPattern(pattern);
        queueRender();
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PASTE, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
    }
}

void SequenceView::paste() {
    DEBUG("SequenceView::paste")
    if(copiedPattern != NULL) {
        AppData::data.setPattern(cursorBar, cursorChannel, copiedPattern);
        queueRender();
    }
}

void SequenceView::drag() {
    SequencePattern* pattern = AppData::data.getPattern(cursorBar, cursorChannel);
    if(pattern != NULL) {
        draggingFromChannel = cursorChannel;
        draggingFromBar = cursorBar;
        dragging = true;
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::BLUE);
    }
}

void SequenceView::drop() {
    if(dragging) {
        SequencePattern* pattern = AppData::data.getPattern(draggingFromBar, draggingFromChannel);
        AppData::data.setPattern(draggingFromBar, draggingFromChannel, NULL);
        AppData::data.setPattern(cursorBar, cursorChannel, pattern);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::OFF);
        queueRender();
    }
}