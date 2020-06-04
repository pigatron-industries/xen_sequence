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
    void setCursor(bool _showCursor);
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

private:
    AppData& appData;
    Matrix& matrix;
    SequencePattern* patterns[SEQUENCE_CHANNELS];

    bool showCursor = false;
    uint16_t bar;
    uint8_t cursorChannel = 0;
    uint8_t cursorTick = 0;

    void renderData();
    void renderCursor();

};

#endif
