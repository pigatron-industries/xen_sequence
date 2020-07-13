#include "MidiOutputService.h"
#include "HardwareSerial.h"
#include "MidiConstants.h"
#include "../../hwconfig.h"




MidiOutputService::MidiOutputService(HardwareSerial& _midiSerial) :
    midiSerial(_midiSerial) {
}

void MidiOutputService::init() {
    midiSerial.begin(MIDI_BAUD);
}

void MidiOutputService::sendMessage(MidiMessage& message) {
    midiSerial.write(message.getBytes(), message.length);
}
