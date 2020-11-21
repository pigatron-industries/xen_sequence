#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "../View.h"
#include "../../lib/drivers/display.h"


class HelpView : public View {

public:
    HelpView();
    virtual void render(bool full = false);
    virtual void handleEvent(InterfaceEvent event);

private:
    
};

#endif
