#include "Sequencer.h"

#include <Arduino.h>

Sequencer::Sequencer(AppData& _appData) :
    appData(_appData) {
    playing = false;
    playMode = PLAY_LOOP_BAR;
    setBar(0);
}

void Sequencer::execute() {
    if(clock.update()) {
        if(clock.tick()) {
            tick();
            executeTickEvents();
        }

        // TODO sub tick events
    }
}

void Sequencer::executeTickEvents() {
    Serial.println(tickIndex);
}

void Sequencer::play() {
    tickIndex = 0;
    playing = true;
    clock.start();
    executeTickEvents();
}

void Sequencer::stop() {
    playing = false;
    clock.stop();
    reset();
}

void Sequencer::reset() {
    if(playMode != PLAY_LOOP_BAR) {
        setBar(0);
    }
    tickIndex = 0;
    clock.reset();
}

void Sequencer::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    currentBar = appData.getBar(barIndex);
}

void Sequencer::tick() {
    tickIndex++;
    if(tickIndex == currentBar->getLength()) {
        tickIndex = 0;
        if(playMode != PLAY_LOOP_BAR) {
            barIndex++;
            if(barIndex < appData.getSequence().getLength()) {
                setBar(barIndex);
            } else {
                reset();
                if(playMode == PLAY_SONG) {
                    clock.stop();
                }
            }
        }
    }
}
