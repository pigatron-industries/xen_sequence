#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"

class ParameterView {

public:
    ParameterView(AppData& _appData, Display& _display);
    void render();

private:
    AppData& appData;
    Display& display;

};

#endif
