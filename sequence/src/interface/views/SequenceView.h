#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"

class SequenceView {

public:
    SequenceView(AppData& _appData, Display& _display);
    void render();

private:
    AppData& appData;
    Display& display;
    uint8_t cursorChannel;
    uint8_t cursorBar;

    void renderStatusBar();
    void renderGrid();
    void renderSequence();
    void renderCursor();

};

#endif
