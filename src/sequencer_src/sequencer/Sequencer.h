#ifndef Sequencer_h
#define Sequencer_h

#include <inttypes.h>

#include "Clock.h"
#include "SequencerEventListener.h"
#include "midi/EventOutputService.h"
#include "midi/EventCompiler.h"
#include "model/AppData.h"

enum SequencePlayMode {
    PLAY_SONG,
    PLAY_LOOP_BAR,
    PLAY_LOOP_SELECTION,
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
    SequencePlayMode getPlayMode() { return playMode; }
    uint16_t getLoopStart() { return loopStart; }
    uint16_t getLoopEnd() { return loopEnd; }

    void setPlayMode(SequencePlayMode playMode);
    void setLoopStart(uint16_t loopStart) { this->loopStart = loopStart; }
    void setLoopEnd(uint16_t loopEnd) { this->loopEnd = loopEnd; }

private:
    EventOutputService& eventOutputService;
    EventCompiler eventCompiler;
    Clock clock;
    LinkedList<SequencerEventListener*> eventListeners;

    bool playing;
    SequencePlayMode playMode;
    uint16_t loopStart;
    uint16_t loopEnd;

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
