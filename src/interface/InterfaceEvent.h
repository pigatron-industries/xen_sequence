#ifndef InterfaceEvent_h
#define InterfaceEvent_h

enum InterfaceEventType {
    STICK_LEFT,
    STICK_RIGHT,
    STICK_UP,
    STICK_DOWN,
    STICK_PRESS,
    //
    DATA_INCREMENT,
    DATA_DECREMENT,
    DATA_PRESS,
    //
    KEY_BACK,
    KEY_ADD_DEL,
    KEY_COPY,
    KEY_PASTE,
    //
    KEY_PLAY_STOP,
    KEY_RECORD,
    KEY_PREV,
    KEY_NEXT,
    //
    SEQUENCER_TICK
};

class InterfaceEvent {
    public:
        InterfaceEvent(InterfaceEventType _eventType) {
            eventType = _eventType;
        }
        InterfaceEvent(InterfaceEventType _eventType, int _data) {
            eventType = _eventType;
            data = _data;
        }

        InterfaceEventType eventType;
        int data;
};

#endif
