#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"
#include "../Events.h"

class SequenceView {

public:
    SequenceView(AppData& _appData, Display& _display);
    void render();
    void handleEvent(Event event);

private:
    AppData& appData;
    Display& display;
    uint8_t cursorChannel;
    uint8_t cursorBar;
    uint8_t scrollBar;

    void renderStatusBar();
    void renderGrid();
    void renderSequence();
    void renderCursor();

    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

};

#endif
