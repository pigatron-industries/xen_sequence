#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "interface/InterfaceEvent.h"
#include "View.h"
#include "SequenceMatrixView.h"

class SequenceView : public View {

public:
    SequenceView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView);
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);
    uint16_t getCursorBar() { return cursorBar; }

private:
    Sequencer& sequencer;
    SequenceMatrixView& sequenceMatrixView;

    uint8_t cursorChannel;
    uint16_t cursorBar;
    uint16_t scrollBar;

    bool dragging;
    uint8_t draggingFromChannel;
    uint16_t draggingFromBar;

    SequencePattern* copiedPattern;

    void renderStatusBar();
    void renderGrid();
    void renderSequence();
    void renderCursor();

    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

    void updateSelectedPattern();

    void incrementPattern();
    void decrementPattern();

    void addPattern();
    void deletePattern();
    void copy();
    void paste();
    void drag();
    void drop();

};

#endif
