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

void Sequencer::interrupt() {
    Sequencer::sequencer.execute();
}

void Sequencer::execute() {
    clock.update();
    bool isTick = clock.tick();
    if(isTick) {
        tick();
    }
    pulse();
    if(isTick) {
        notifyTickEvent();
    }
}

void Sequencer::pulse() {
    pulseClockEvent();

    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequenceTickEvents* tickEvents = currentTickEvents[channel];
        if(tickEvents != NULL) {
            // Compile to midi event before sending if needed
            if(clock.getPulseCount() == 0 && !tickEvents->isCompiled()) {
                uint8_t midiChannel = AppData::data.getChannel(channel).getMidiChannel();
                eventCompiler.compileTickEvents(tickEvents, midiChannel);
            }
            
            eventOutputService.event(channel, clock.getPulseCount(), tickEvents);
        }
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

    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = currentBar->getPattern(channel);
        if(pattern != NULL) {
            currentTickEvents[channel] = pattern->getTickEvents(tickIndex);
        } else {
            currentTickEvents[channel] = NULL;
        }
    }
}

void Sequencer::pulseClockEvent() {
    eventOutputService.system(SYSTEM_CLOCK);
}

void Sequencer::play() {
    DEBUGINFO
    tickIndex = 0;
    playing = true;
    clock.reset();
    clock.start();
    eventOutputService.system(SYSTEM_START);
    pulse();
    interruptTimer.priority(0);
    interruptTimer.begin(Sequencer::interrupt, calculatePulseInterval());
}

void Sequencer::stop() {
    playing = false;
    clock.stop();
    eventOutputService.system(SYSTEM_STOP);
    reset();
    interruptTimer.end();
}

void Sequencer::reset() {
    setBar(loopStart);
    tickIndex = 0;
    clock.reset();
}

uint16_t Sequencer::setBar(uint16_t _barIndex) {
    DEBUGINFO
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
    interruptTimer.update(calculatePulseInterval());
}

int Sequencer::calculatePulseInterval() {
    int multiplier = AppData::data.getAbsoluteSpeedMult(currentBar);
    int ticksPerMinute = AppData::data.getAbsoluteSpeed(currentBar) * multiplier;
    return (60000000/PULSES_PER_TICK)/ticksPerMinute;
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
    //TODO put event on queue instead
    for(uint8_t i = 0; i < eventListeners.size(); i++) {
        eventListeners.get(i)->onTick();
    }
}