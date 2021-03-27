#ifndef MidiOutputService_h
#define MidiOutputService_h

#include <inttypes.h>
#include <Arduino.h>
#include "model/midi/MidiMessage.h"

class MidiOutputService {

public:
    MidiOutputService(HardwareSerial& _midiSerial);
    void init();
    void sendMessage(MidiMessage& message);

private:
    HardwareSerial& midiSerial;
};

#endif
