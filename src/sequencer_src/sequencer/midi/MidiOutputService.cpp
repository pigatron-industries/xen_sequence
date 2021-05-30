#include "MidiOutputService.h"
#include "HardwareSerial.h"
#include "hwconfig.h"
#include "lib/util/debug.h"


MidiOutputService::MidiOutputService(HardwareSerial& _midiSerial) :
    midiSerial(_midiSerial) {
}

void MidiOutputService::init() {
    midiSerial.begin(MIDI_BAUD);
}

void MidiOutputService::sendMessage(MidiMessage& message) {
    if(message.command != COMMAND_SYSTEM) {
        // DEBUGINFO
        // DEBUG("channel=");
        // DEBUG(message.channel);
        // DEBUG("command=");
        // DEBUG(message.command);
        // DEBUG("data1=");
        // DEBUG(message.data1);
        // DEBUG("data2=");
        // DEBUG(message.data2);
        // DEBUGLN();
    }
    midiSerial.write(message.getBytes(), message.length);
}
