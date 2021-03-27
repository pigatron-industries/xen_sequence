#ifndef MidiInputService_h
#define MidiInputService_h

#include <inttypes.h>
#include <Arduino.h>
#include "model/midi/MidiMessage.h"
#include "MidiEventHandler.h"

#define SYSEX_BUFFER_SIZE 100
#define MESSAGE_BUFFER_SIZE 10
#define MAX_EVENT_HANDLERS 10

class MidiInputService  {

public:
    MidiInputService(HardwareSerial& midiSerial);
    void init();
    void update();

    void addEventHandler(MidiEventHandler* eventHandler);

private:
    HardwareSerial& _midiSerial;

    MidiEventHandler* eventHandlers[MAX_EVENT_HANDLERS];
    size_t eventHandlerCount;

    uint8_t sysexBuffer[SYSEX_BUFFER_SIZE];
    uint8_t sysexBufferDecoded[SYSEX_BUFFER_SIZE];

    int8_t prevCCChannel;
    int8_t prevCCControl;
    int8_t prevCCValue;

    uint8_t getByte();
    void handleControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t msbValue, int8_t lsbValue);
    void handleSysex();
    void notify(MidiMessage midiMessage);

};

#endif
