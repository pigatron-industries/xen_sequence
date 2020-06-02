#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "../model/AppData.h"
#include "Events.h"
#include "./views/SequenceView.h"
#include "./views/ParameterView.h"

class InterfaceController {

public:
    InterfaceController(AppData& _appData, Display& _display);
    void init();
    void handleEvent(Event event);

private:
    AppData& appData;
    Display& display;

    SequenceView sequenceView;
    ParameterView parameterView;

};

#endif
