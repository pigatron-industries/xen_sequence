#ifndef View_h
#define View_h

#include "interface/InterfaceEvent.h"
#include "interface/components/Component.h"
#include "lib/drivers/Display.h"

class View : public Component {
    public:
        virtual void init() = 0;
        virtual InterfaceEvent handleEvent(InterfaceEvent event) = 0;
        void queueRender(bool full = false) { rerender = true; rerenderFull = rerenderFull || full; }
        bool rerender;
        bool rerenderFull;

};

#endif
