#ifndef Switch_h
#define Switch_h

#include <Bounce2.h>

class Switch {

public:
    Switch(uint8_t pin) {
        debouncer.attach(pin, INPUT_PULLUP);
        digitalWrite(pin, HIGH);
    }

    bool update() { return debouncer.update(); }
    bool rose() { return debouncer.rose(); }
    bool fell() { return debouncer.fell(); }
    bool read() { return debouncer.read(); }
    unsigned long duration() { return debouncer.duration(); }
    unsigned long previousDuration() { return debouncer.previousDuration(); }

private:
    Bounce debouncer;

};

#endif
