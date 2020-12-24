#include "Sequencer.h"

#include <Arduino.h>
#include "../lib/util/debug.h"

Sequencer::Sequencer(EventOutputService& _eventOutputService) :
    eventOutputService(_eventOutputService) {
    playing = false;
    playMode = PLAY_LOOP_BAR;
}

void Sequencer::init() {
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
        pulse();
        if(isTick) {
            notifyTickEvent();
        }
    }
}

void Sequencer::pulse() {
    pulseClockEvent();

    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = currentBar->getPattern(channel);
        if(pattern != NULL) {
            SequenceEvent* event = pattern->getEvent(tickIndex);
            if(event != NULL) {
                if(clock.getPulseCount() == 0 && event->isCompileNeeded()) {
                    eventCompiler.compileEvent(event, channel);
                }
                eventOutputService.event(channel, clock.getPulseCount(), event);
            }
        }
    }
}

void Sequencer::pulseClockEvent() {
    if(clock.getPulseCount() % midiPulseDivider == 0) {
        eventOutputService.system(SYSTEM_CLOCK);
    }
}

void Sequencer::play() {
    tickIndex = 0;
    playing = true;
    clock.start();
    eventOutputService.system(SYSTEM_START);
    pulse();
}

void Sequencer::stop() {
    playing = false;
    clock.stop();
    eventOutputService.system(SYSTEM_STOP);
    reset();
}

void Sequencer::reset() {
    if(playMode != PLAY_LOOP_BAR) {
        setBar(0);
    }
    tickIndex = 0;
    clock.reset();
}

uint16_t Sequencer::setBar(uint16_t _barIndex) {
    DEBUG("Sequencer::setBar");
    barIndex = _barIndex;
    currentBar = AppData::data.getBar(barIndex);
    clock.setTicksPerMinute(currentBar->getSpeed());
    return barIndex;
}

uint16_t Sequencer::nextBar() {
    if(currentBar->isEmpty()) {
        return barIndex;
    } else {
        return setBar(barIndex+1);
    }
}

uint16_t Sequencer::prevBar() {
    if(barIndex == 0) {
        return barIndex;
    } else {
        return setBar(barIndex-1);
    }
}

void Sequencer::tick() {
    tickIndex++;
    if(tickIndex == currentBar->getLength()) {
        tickIndex = 0;
        if(playMode != PLAY_LOOP_BAR) {
            barIndex++;
            if(barIndex < AppData::data.getSequence().getLength()) {
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
