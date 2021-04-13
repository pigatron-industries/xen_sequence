#ifndef View_h
#define View_h

#include "interface/InterfaceEvent.h"
#include "interface/components/Component.h"
#include "lib/drivers/Display.h"

class View : public Component {
    public:
        virtual void init() = 0;
        virtual void handleEvent(InterfaceEvent event) = 0;
};

#endif
