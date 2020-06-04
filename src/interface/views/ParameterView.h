#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "../View.h"
#include "SequenceMatrixView.h"
#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"

class ParameterView : public View {

public:
    ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView);
    virtual void render();
    virtual void handleEvent(Event event);

    void setBar(uint16_t _bar);

private:
    AppData& appData;
    Display& display;
    SequenceMatrixView& sequenceMatrixView;

    uint16_t bar;

};

#endif
