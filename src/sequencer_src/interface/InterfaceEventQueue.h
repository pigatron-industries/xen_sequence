#ifndef InterfaceEventQueue_h
#define InterfaceEventQueue_h

#include "InterfaceEvent.h"

class InterfaceEventQueue {
    public:
        static InterfaceEventQueue q;

        InterfaceEventQueue() {}
        void doRender(bool full) { pushEvent(InterfaceEvent(InterfaceEventType::RENDER, full)); }
        void pushEvent(InterfaceEvent event);
        InterfaceEvent& popEvent();
        int getSize() { return size; }

    private:
        InterfaceEvent event = InterfaceEvent::NONE;
        int size = 0;

};

#endif
