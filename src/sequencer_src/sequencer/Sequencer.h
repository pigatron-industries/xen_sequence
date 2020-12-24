#ifndef Sequencer_h
#define Sequencer_h

#include <inttypes.h>

#include "Clock.h"
#include "SequencerEventListener.h"
#include "midi/EventOutputService.h"
#include "midi/EventCompiler.h"
#include "../model/AppData.h"

enum SequencePlayMode {
    PLAY_SONG,
    PLAY_LOOP_BAR,
    PLAY_LOOP_SONG
};


class Sequencer {

public:
    Sequencer(EventOutputService& _eventOutputService);
    void init();
    void addEventListener(SequencerEventListener* eventListener);
    void execute();

    void play();
    void stop();
    void reset();

    bool isPlaying() { return playing; }

    uint16_t setBar(uint16_t _barIndex);
    uint16_t nextBar();
    uint16_t prevBar();
    uint16_t getBarIndex() { return barIndex; }
    uint8_t getTickIndex() { return tickIndex; }

private:
    EventOutputService& eventOutputService;
    EventCompiler eventCompiler;
    Clock clock;
    LinkedList<SequencerEventListener*> eventListeners;

    bool playing;
    SequencePlayMode playMode;

    SequenceBar* currentBar;
    uint16_t barIndex = 0;
    uint8_t tickIndex = 0;

    uint8_t midiPulseDivider = 4; //convert 96ppm to 24ppm

    void tick();
    void pulse();
    void pulseClockEvent();
    void notifyTickEvent();

};


#endif
