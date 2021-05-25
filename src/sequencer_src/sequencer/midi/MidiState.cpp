#include "MidiState.h"

MidiState MidiState::midiState = MidiState();

bool MidiChannelState::noteOn(uint8_t note) {
    if(noteOnCount >= MAX_POLYPHONY) {
        return false;
    } else {
        if(getNoteOnIndex(note) == -1) {
            noteOns[noteOnCount] = note;
            noteOnCount++;
        }
        return true;
    }
}

void MidiChannelState::noteOff(uint8_t note) {
    int removeIndex = getNoteOnIndex(note);
    if(removeIndex != -1) {
        for(int i = removeIndex+1; i < noteOnCount; i++) {
            noteOns[i-1] = noteOns[i];
        }
        noteOnCount--;
    }
}

int MidiChannelState::getNoteOnIndex(uint8_t note) {
    for(int i = 0 ; i < noteOnCount; i++) {
        if(noteOns[i] == note) {
            return i;
        }
    }
    return -1;
}
