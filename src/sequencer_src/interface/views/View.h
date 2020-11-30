#ifndef View_h
#define View_h

#include "../InterfaceEvent.h"
#include "../components/Component.h"
#include "../../lib/drivers/Display.h"

class View : public Component {
    public:
        virtual void handleEvent(InterfaceEvent event) = 0;
};

#endif
