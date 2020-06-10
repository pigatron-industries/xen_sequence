#ifndef Sequencer_h
#define Sequencer_h

#include <inttypes.h>

#include "Clock.h"
#include "../model/AppData.h"

enum SequencePlayMode {
    PLAY_SONG,
    PLAY_LOOP_BAR,
    PLAY_LOOP_SONG
};


class Sequencer {

public:
    Sequencer(AppData& _appData);
    void execute();

    void play();
    void stop();
    void reset();

    bool isPlaying() { return playing; }

    void setBar(uint16_t _barIndex);

private:
    AppData& appData;
    Clock clock;

    bool playing;
    SequencePlayMode playMode;

    SequenceBar* currentBar;
    uint16_t barIndex = 0;
    uint8_t tickIndex = 0;

    void tick();
    void executeTickEvents();

};


#endif
