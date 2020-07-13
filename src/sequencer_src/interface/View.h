#ifndef View_h
#define View_h

#include "InterfaceEvent.h"
#include "../lib/drivers/Display.h"

class View {
    public:
        virtual void render(bool full = false) = 0;
        virtual void handleEvent(InterfaceEvent event) = 0;
};

#endif
