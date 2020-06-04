#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "../model/AppData.h"
#include "Events.h"
#include "View.h"
#include "./views/SequenceView.h"
#include "./views/ParameterView.h"
#include "./views/SequenceMatrixView.h"

class InterfaceController {

public:
    InterfaceController(AppData& _appData, Display& _display, Matrix& _matrix);
    void init();
    void handleEvent(Event event);

private:
    AppData& appData;
    Display& display;
    Matrix& matrix;

    View* currentView;

    SequenceMatrixView sequenceMatrixView;
    SequenceView sequenceView;
    ParameterView parameterView;

    void switchToParameterView();
    void switchToSequenceView();

};

#endif
