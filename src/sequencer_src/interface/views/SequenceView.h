#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "../InterfaceEvent.h"
#include "../View.h"
#include "SequenceMatrixView.h"
#include "../../model/AppData.h"

class SequenceView : public View {

public:
    SequenceView(AppData& _appData, SequenceMatrixView& _sequenceMatrixView);
    virtual void render(bool full = false);
    virtual void handleEvent(InterfaceEvent event);
    uint16_t getCursorBar() { return cursorBar; }

private:
    AppData& appData;
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
