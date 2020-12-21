#ifndef MidiMessage_h
#define MidiMessage_h

#include <inttypes.h>
#include "MidiConstants.h"

class MidiMessage {
    public:
        MidiMessage(uint8_t _pulse, uint8_t _channel, uint8_t _command, uint8_t _data1, uint8_t _data2) {
            pulse = _pulse;
            channel = _channel;
            command = _command;
            data1 = _data1;
            data2 = _data2;
        }

        MidiMessage(uint8_t _channel, uint8_t _command, uint8_t _data1, uint8_t _data2) {
            pulse = 0;
            channel = _channel;
            command = _command;
            data1 = _data1;
            data2 = _data2;
        }

        MidiMessage() {
            command = COMMAND_NONE;
        }

        uint8_t pulse;
        uint8_t channel;
        uint8_t command;
        uint8_t data1;
        uint8_t data2;

        uint8_t bytes[3];
        uint8_t length = 3;

        uint8_t* getBytes() {
            bytes[0] = (command << 4) | channel;
            bytes[1] = data1;
            bytes[2] = data2;
            return bytes;
        }
        
    private:
};

#endif
