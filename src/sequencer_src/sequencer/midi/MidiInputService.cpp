#include "MidiInputService.h"
#include "HardwareSerial.h"

#include "hwconfig.h"
#include "lib/util/debug.h"

#include <Arduino.h>



#define HI_NYBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NYBBLE(b) ((b) & 0x0F)


MidiInputService::MidiInputService(HardwareSerial& midiSerial) :
    _midiSerial(midiSerial) {
}

void MidiInputService::init() {
    _midiSerial.begin(MIDI_BAUD);
}

void MidiInputService::addEventHandler(MidiEventHandler* eventHandler) {
    eventHandlers[eventHandlerCount++] = eventHandler;
}

byte MidiInputService::getByte() {
    while(!_midiSerial.available()){}
    return _midiSerial.read();
}

void MidiInputService::notify(MidiMessage& midiMessage) {
    for(size_t i = 0; i < eventHandlerCount; i++) {
        eventHandlers[i]->handleMidiEvent(midiMessage);
    }
}

void MidiInputService::update() {
    while(_midiSerial.available()) {
        DEBUGINFO

        uint8_t messageBuffer[3];
        messageBuffer[0] = getByte();

        if(messageBuffer[0] >= 0x80) { // start of midi message
            uint8_t length = 0;

            byte command = HI_NYBBLE(messageBuffer[0]);
            byte channel = LO_NYBBLE(messageBuffer[0]);

            if(command != COMMAND_SYSTEM) {

                messageBuffer[1] = getByte();
                if(command != COMMAND_CHAN_PRESSURE && command != COMMAND_PROGRAM_CHANGE) {
                    messageBuffer[2] = getByte();
                    length = 3;
                } else {
                    messageBuffer[2] = 0;
                    length = 2;
                }

                DEBUG("command=");DEBUG(command);
                DEBUG("channel=");DEBUG(channel);
                DEBUG("data1=");DEBUG(messageBuffer[1]);
                DEBUG("data2=");DEBUGLN(messageBuffer[2]);

                MidiChannelState& channelState = MidiState::midiState.getChannelState(channel);
                if(command == COMMAND_NOTEON) {
                    channelState.noteOn(messageBuffer[1]);
                } else if (command == COMMAND_NOTEOFF) {
                    channelState.noteOff(messageBuffer[1]);
                }

                MidiMessage midiMessage = MidiMessage(channel, command, messageBuffer[1], messageBuffer[2]);
                notify(midiMessage);

            } else { // command == COMMAND_SYSTEM
                if(channel != SYSTEM_EXCLUSIVE) {
                    MidiMessage midiMessage = MidiMessage(channel, command, 0, 0);
                    notify(midiMessage);
                } else {
                    handleSysex();
                }
            }
        }
    }
}

void MidiInputService::handleSysex() {
    memset(sysexBuffer, 0, SYSEX_BUFFER_SIZE);
    size_t size = _midiSerial.readBytesUntil(SYSTEM_EXCLUSIVE_END, sysexBuffer, SYSEX_BUFFER_SIZE);

    INFO("System config message recieved:");
    for(unsigned int i = 0; i < size; i++) {
        INFO((char)sysexBuffer[i]);
    }
    INFO();
    INFO();

    // int decodedSize = base64_decode((char*)sysexBufferDecoded, (char*)sysexBuffer, size);
    // _midiEventProcessor.eventSystemConfig(sysexBufferDecoded, decodedSize);
}
