#ifndef SequenceMatrixView_h
#define SequenceMatrixView_h

#include <inttypes.h>

#include "model/AppData.h"
#include "lib/drivers/LedMatrix.h"
#include "sequencer/Sequencer.h"

enum class SequenceMatrixSelectionMode {
    SELECT_NONE,
    SELECT_EVENT,
    SELECT_CHANNEL
};

class SequenceMatrixView {

public:
    SequenceMatrixView();
    void render();
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

    void setBar(int _barIndex);
    void setSelectionMode(SequenceMatrixSelectionMode _selectionMode) { selectionMode = _selectionMode; }
    void setPlayCursor(bool _showPlayCursor);
    void setSelectionActive(bool _selectionActive) { selectionActive = _selectionActive; }
    void setMarker(uint8_t channel, uint8_t tick);
    void clearMarker();

    uint8_t getSelectCursorChannel() { return selectCursorChannel; }
    uint8_t getSelectCursorTick() { return selectCursorTick; }

private:
    SequencePattern* patterns[SEQUENCE_CHANNELS];

    uint16_t barIndex;
    SequenceMatrixSelectionMode selectionMode = SequenceMatrixSelectionMode::SELECT_NONE;
    
    bool selectionActive = false;
    uint8_t selectCursorChannel = 0;
    uint8_t selectCursorTick = 0;

    bool showPlayCursor = false;
    uint8_t playCursorTick = 0;

    bool showMarker = false;
    uint8_t markerChannel = 0;
    uint8_t markerTick = 0;

    void renderData();
    void renderSelectCursor();
    void renderPlayCursor();
    void renderMarker();

};

#endif
