#ifndef SequenceView_h
#define SequenceView_h

#include <inttypes.h>

#include "interface/InterfaceEvent.h"
#include "View.h"
#include "matrix/SequenceMatrixView.h"

enum MoveMode {
    PATTERN_MOVE,
    PATTERN_COPY,
    BAR_MOVE,
    BAR_COPY
};

class SequenceView : public View {

public:
    SequenceView(SequenceMatrixView& _sequenceMatrixView);
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual void handleEvent(InterfaceEvent event);
    uint16_t getCursorBar() { return cursorBar; }

private:
    SequenceMatrixView& sequenceMatrixView;

    uint8_t cursorChannel;
    uint16_t cursorBar;
    uint16_t scrollBar;
    SequencePattern* selectedPattern = NULL;

    MoveMode moveMode;
    bool moving;
    uint8_t movingFromChannel;
    uint16_t movingFromBar;

    SequencePattern* copiedPattern = NULL;

    bool function = false;

    //rendering
    void renderStatusBar();
    void renderGrid();
    void renderSequence();
    void renderPattern(SequencePattern* pattern, short left, short top);
    void renderCursor();

    void renderKeyLeds();
    void renderKeyLedsPattern();
    void renderKeyLedsMoveMode();

    void loopStart();
    void loopEnd();

    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();
    void setSelectedPattern();

    void incrementPattern();
    void decrementPattern();

    void addPattern();
    void deletePattern();
    void copy();
    void paste();

    void cycleMoveMode();
    void setMoveMode(MoveMode moveMode);

    void moveStart();
    void patternMoveEnd();
    void patternCopyEnd();
    void barMoveEnd();
    void barCopyEnd();

};

#endif
