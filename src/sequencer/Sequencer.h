#ifndef Sequencer_h
#define Sequencer_h

#include <inttypes.h>

#include "Clock.h"
#include "SequencerEventListener.h"
#include "EventOutputService.h"
#include "../model/AppData.h"

enum SequencePlayMode {
    PLAY_SONG,
    PLAY_LOOP_BAR,
    PLAY_LOOP_SONG
};


class Sequencer {

public:
    Sequencer(AppData& _appData, EventOutputService& _eventOutputService);
    void addEventListener(SequencerEventListener* eventListener);
    void execute();

    void play();
    void stop();
    void reset();

    bool isPlaying() { return playing; }

    void setBar(uint16_t _barIndex);
    uint16_t getBarIndex() { return barIndex; }
    uint8_t getTickIndex() { return tickIndex; }

private:
    AppData& appData;
    EventOutputService& eventOutputService;
    Clock clock;
    LinkedList<SequencerEventListener*> eventListeners;

    bool playing;
    SequencePlayMode playMode;

    SequenceBar* currentBar;
    uint16_t barIndex = 0;
    uint8_t tickIndex = 0;

    void tick();
    void executeTickEvents();
    void notifyTickEvent();

};


#endif
