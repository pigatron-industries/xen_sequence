#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "../model/AppData.h"
#include "../modules/Sequencer.h"
#include "Events.h"
#include "View.h"
#include "./views/SequenceView.h"
#include "./views/ParameterView.h"
#include "./views/SequenceMatrixView.h"

class InterfaceController {

public:
    InterfaceController(AppData& _appData, Sequencer& _sequencer, Display& _display, LedMatrix& _ledMatrix);
    void init();
    void render();
    void handleEvent(Event event);

private:
    AppData& appData;
    Sequencer& sequencer;

    Display& display;
    LedMatrix& ledMatrix;

    View* currentView;

    SequenceMatrixView sequenceMatrixView;
    SequenceView sequenceView;
    ParameterView parameterView;

    void switchToParameterView();
    void switchToSequenceView();

};

#endif
