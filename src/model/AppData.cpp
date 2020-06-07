#include "AppData.h"

#include <Arduino.h>

void AppData::populateTestData() {
    SequencePattern* pattern1 = newPattern();
    SequencePattern* pattern3 = newPattern();

    //newEvent(0, pattern1);
    newEvent(2, pattern1)->pitch = 1;
    newEvent(4, pattern1)->pitch = 2;
    newEvent(6, pattern1)->pitch = 3;
    newEvent(8, pattern1)->pitch = 4;
    newEvent(10, pattern1)->pitch = 5;
    newEvent(12, pattern1)->pitch = 6;
    newEvent(14, pattern1)->pitch = 7;

    newEvent(1, pattern3);
    newEvent(3, pattern3);
    newEvent(5, pattern3);
    newEvent(7, pattern3);
    newEvent(9, pattern3);
    newEvent(11, pattern3);
    newEvent(13, pattern3);
    newEvent(15, pattern3);

    SequenceBar* bar1 = newBar(0);
    SequenceBar* bar2 = newBar(0);
    SequenceBar* bar3 = newBar(0);

    bar1->setPattern(0, pattern1);
    bar2->setPattern(1, pattern3);
    bar3->setPattern(0, pattern1);
    bar3->setPattern(1, pattern3);
}

SequenceBar* AppData::getBar(int index) {
    return sequence.getBar(index);
}

SequenceBar* AppData::newBar(int index) {
    SequenceBar* bar = new SequenceBar();
    sequence.getBars().add(index, bar);
    return bar;
}

SequencePattern* AppData::getPatternById(uint8_t id) {
    for(int i = 0; i < patterns.size(); i++) {
        SequencePattern* pattern = patterns.get(i);
        if(pattern->getId() == id) {
            return pattern;
        }
    }
    return NULL;
}

SequencePattern* AppData::getPattern(uint16_t barIndex, uint8_t channel) {
    SequenceBar* bar = sequence.getBar(barIndex);
    if(bar != NULL) {
        return bar->getPattern(channel);
    }
    return NULL;
}

SequencePattern* AppData::newPattern() {
    SequencePattern* pattern = new SequencePattern(getUnusedPatternId());
    patterns.add(pattern);
    return pattern;
}

uint8_t AppData::getUnusedPatternId() {
    for(uint8_t id = 1; id < MAX_PATTERN_ID; id++) {
        if(getPatternById(id) == NULL) {
            return id;
        }
    }
}

SequenceEvent* AppData::newEvent(uint8_t tick, SequencePattern* pattern) {
    SequenceEvent* event = new SequenceEvent();
    pattern->addEvent(tick, event);
    return event;
}

SequenceChannel& AppData::getChannel(uint8_t index) {
    return sequence.getChannel(index);
}
