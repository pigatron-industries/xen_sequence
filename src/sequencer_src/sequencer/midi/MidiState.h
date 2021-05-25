#ifndef MidiState_h
#define MidiState_h

#include <inttypes.h>

#define MIDI_CHANNELS 16
#define MAX_POLYPHONY 5

class MidiChannelState {
    public:
        bool noteOn(uint8_t note);
        void noteOff(uint8_t note);

        uint8_t getNoteOnCount() { return noteOnCount; }
        uint8_t* getNoteOns() { return noteOns; }

    private:
        uint8_t noteOnCount = 0;
        uint8_t noteOns[MAX_POLYPHONY];

        int getNoteOnIndex(uint8_t note);
};

class MidiState {
    public:
        static MidiState midiState;

        MidiChannelState& getChannelState(uint8_t channel) {
            return channels[channel];
        }
        
    private:
        MidiChannelState channels[MIDI_CHANNELS];
};

#endif
