#ifndef SequenceMatrixView_h
#define SequenceMatrixView_h

#include <inttypes.h>

#include "../../model/AppData.h"
#include "../../lib/drivers/Matrix.h"


class SequenceMatrixView {

public:
    SequenceMatrixView(AppData& _appData, Matrix& _matrix);
    void render();
    void setBar(int _bar);
    void setSelectCursor(bool _showSelectCursor);
    void setPlayCursor(bool _showPlayCursor);
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

private:
    AppData& appData;
    Matrix& matrix;
    SequencePattern* patterns[SEQUENCE_CHANNELS];

    uint16_t bar;
    bool showSelectCursor = false;
    bool showPlayCursor = false;
    uint8_t selectCursorChannel = 0;
    uint8_t selectCursorTick = 0;
    uint8_t playCursorTick = 0;

    void renderData();
    void renderSelectCursor();
    void renderPlayCursor();

};

#endif
