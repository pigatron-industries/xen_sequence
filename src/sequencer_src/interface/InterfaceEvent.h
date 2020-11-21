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
    KEY_RECORD,
    KEY_PLAY_STOP,
    KEY_PREV,
    KEY_NEXT,
    //
    KEY_LOOP,
    KEY_PLACE_2,
    KEY_PLACE_3,
    KEY_PLACE_4,
    //
    KEY_BACK,
    KEY_ADD_DEL,
    KEY_COPY,
    KEY_PASTE,
    //
    KEY_PLACE_5,
    KEY_PLACE_6,
    KEY_PLACE_7,
    KEY_PLACE_8,
    //
    KEY_PLACE_9,
    KEY_PLACE_10,
    KEY_PLACE_11,
    KEY_PLACE_12,
    //
    KEY_PLACE_13,
    KEY_PLACE_14,
    KEY_PLACE_15,
    KEY_PLACE_16,
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
