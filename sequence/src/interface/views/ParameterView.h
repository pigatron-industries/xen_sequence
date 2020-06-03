#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "SequenceMatrixView.h"
#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"

class ParameterView {

public:
    ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView);
    void render();

private:
    AppData& appData;
    Display& display;
    SequenceMatrixView& sequenceMatrixView;

};

#endif
