#include "Sequencer.h"

#include <Arduino.h>

Sequencer::Sequencer(AppData& _appData, EventOutputService& _eventOutputService) :
    appData(_appData),
    eventOutputService(_eventOutputService) {
    playing = false;
    playMode = PLAY_LOOP_BAR;
    setBar(0);
}

void Sequencer::addEventListener(SequencerEventListener* eventListener) {
    eventListeners.add(eventListener);
}

void Sequencer::execute() {
    if(clock.update()) {
        bool isTick = clock.tick();
        if(isTick) {
            tick();
        }
        executeTickEvents();
        if(isTick) {
            notifyTickEvent();
        }
    }
}

void Sequencer::executeTickEvents() {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = currentBar->getPattern(channel);
        if(pattern != NULL) {
            SequenceEvent* event = pattern->getEvent(tickIndex);
            if(event != NULL) {
                eventOutputService.event(channel, clock.getPulseCount(), event);
            }
        }
    }
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
    clock.setTicksPerMinute(currentBar->getSpeed());
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

void Sequencer::notifyTickEvent() {
    for(uint8_t i = 0; i < eventListeners.size(); i++) {
        eventListeners.get(i)->onTick();
    }
}
