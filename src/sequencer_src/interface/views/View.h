#ifndef View_h
#define View_h

#include "../InterfaceEvent.h"
#include "../components/Component.h"
#include "../../lib/drivers/Display.h"

class View : public Component {
    public:
        virtual InterfaceEvent handleEvent(InterfaceEvent event) = 0;
        void queueRender(bool full = false) { rerender = true; rerenderFull = rerenderFull || full; }
        bool rerender;
        bool rerenderFull;

};

#endif
