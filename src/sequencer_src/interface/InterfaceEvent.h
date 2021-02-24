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
    KEY_LOOP_MODE,
    KEY_LOOP_START,
    KEY_LOOP_END,
    KEY_PLACE_1,
    //
    KEY_VIEW,
    KEY_SELECTION,
    KEY_FILE,
    KEY_HELP,
    //
    KEY_ADD_DEL,
    KEY_COPY,
    KEY_PASTE,
    KEY_PLACE_2,
    //
    KEY_PLACE_3,
    KEY_PLACE_4,
    KEY_PLACE_5,
    KEY_PLACE_6,
    //
    KEY_MOVE_MODE,
    KEY_MOVE,
    KEY_PLACE_7,
    KEY_PLACE_8,
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
