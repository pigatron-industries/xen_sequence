#ifndef View_h
#define View_h

#include "Events.h"
#include "../lib/drivers/Display.h"

class View {
    public:
        virtual void render() = 0;
        virtual void handleEvent(Event event) = 0;
};

#endif
