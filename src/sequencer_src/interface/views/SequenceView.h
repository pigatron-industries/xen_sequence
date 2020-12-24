#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "../InterfaceEvent.h"
#include "View.h"
#include "SequenceMatrixView.h"

class SequenceView : public View {

public:
    SequenceView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView);
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);
    uint16_t getCursorBar() { return cursorBar; }

private:
    Sequencer& sequencer;
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
