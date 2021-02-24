#ifndef InterfaceEvent_h
#define InterfaceEvent_h

#define EVENT_KEY_RELEASED 0
#define EVENT_KEY_PRESSED 1

enum InterfaceEventType {
    NONE,
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
    KEY_LOOP_START,
    KEY_LOOP_END,
    KEY_PLACE_4,
    //
    KEY_VIEW,
    KEY_SELECTION,
    KEY_PLACE_5,
    KEY_PLACE_6,
    //
    KEY_ADD_DEL,
    KEY_COPY,
    KEY_PASTE,
    KEY_MOVE,
    //
    KEY_PLACE_9,
    KEY_PLACE_10,
    KEY_PLACE_11,
    KEY_PLACE_12,
    //
    KEY_PLACE_13,
    KEY_PLACE_14,
    KEY_FILE,
    KEY_HELP,
    //
    SEQUENCER_TICK
};

class InterfaceEvent {
    public:
        static const InterfaceEvent NONE;
        InterfaceEvent(InterfaceEventType _eventType) {
            eventType = _eventType;
            data = 1;
        }
        InterfaceEvent(InterfaceEventType _eventType, int _data) {
            eventType = _eventType;
            data = _data;
        }

        InterfaceEventType eventType;
        int data;
};

#endif
