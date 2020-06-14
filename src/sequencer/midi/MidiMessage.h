#ifndef MidiMessage_h
#define MidiMessage_h

#include <inttypes.h>

class MidiMessage {
    public:
        uint8_t channel;
        uint8_t type;
        uint8_t data1;
        uint8_t data2;
        
        uint8_t length = 3;

        uint8_t* getBytes() {
            bytes[0] = (channel << 4) | type;
            bytes[1] = data1;
            bytes[2] = data2;
            return bytes;
        }
    private:
        uint8_t bytes[3];
};

#endif
