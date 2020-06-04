#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "../Events.h"
#include "../View.h"
#include "SequenceMatrixView.h"
#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"

class SequenceView : public View {

public:
    SequenceView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView);
    virtual void render();
    virtual void handleEvent(Event event);
    uint16_t getCursorBar() { return cursorBar; }

private:
    AppData& appData;
    Display& display;
    SequenceMatrixView& sequenceMatrixView;

    uint8_t cursorChannel;
    uint16_t cursorBar;
    uint16_t scrollBar;

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
