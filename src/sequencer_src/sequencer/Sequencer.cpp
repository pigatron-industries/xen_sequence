#include "Sequencer.h"

#include <Arduino.h>
#include "lib/util/debug.h"

Sequencer Sequencer::sequencer;

Sequencer::Sequencer() {
    playing = false;
    playMode = PLAY_LOOP_BAR;
    loopStart = 0;
    loopEnd = 0;
}

void Sequencer::init(MidiOutputService* midiOutputService) {
    eventOutputService.init(midiOutputService);
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
            SequenceTickEvents* event = pattern->getTickEvents(tickIndex);
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
    DEBUG("Sequencer::play")
    tickIndex = 0;
    playing = true;
    clock.reset();
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
    setBar(loopStart);
    tickIndex = 0;
    clock.reset();
}

uint16_t Sequencer::setBar(uint16_t _barIndex) {
    DEBUG("Sequencer::setBar");
    barIndex = _barIndex;
    currentBar = AppData::data.getBar(barIndex);
    updateBarSpeed();
    if(playMode == PLAY_LOOP_BAR) {
        loopStart = barIndex;
        loopEnd = barIndex;
    }
    return barIndex;
}

void Sequencer::updateBarSpeed() {
    uint8_t multiplier = AppData::data.getAbsoluteSpeedMult(currentBar);
    clock.setTicksPerMinute(AppData::data.getAbsoluteSpeed(currentBar) * multiplier);
    //clock.setPulsesPerTick(MAX_PULSES_PER_TICK / multiplier);
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
        barIndex++;
        if(barIndex <= loopEnd) {
            setBar(barIndex);
        } else {
            reset();
            if(playMode == PLAY_SONG) {
                clock.stop();
            }
        }
    }
}

void Sequencer::setPlayMode(SequencePlayMode playMode) { 
    this->playMode = playMode;
    switch(playMode) {
        case SequencePlayMode::PLAY_SONG:
        case SequencePlayMode::PLAY_LOOP_SONG:
            loopStart = 0;
            loopEnd = AppData::data.getSequence().getLength();
            break;
        case SequencePlayMode::PLAY_LOOP_BAR:
            loopStart = barIndex;
            loopEnd = barIndex;
            break;
        default:
            break;
    }
}

void Sequencer::notifyTickEvent() {
    for(uint8_t i = 0; i < eventListeners.size(); i++) {
        eventListeners.get(i)->onTick();
    }
}
