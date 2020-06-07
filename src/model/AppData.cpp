#include "AppData.h"

#include <Arduino.h>

void AppData::populateTestData() {
    SequencePattern* pattern1 = newPattern();
    SequencePattern* pattern3 = newPattern();

    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);
    pattern1->getEvents().add(new SequenceEvent());
    pattern1->getEvents().add(NULL);

    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());
    pattern3->getEvents().add(NULL);
    pattern3->getEvents().add(new SequenceEvent());

    SequenceBar* bar1 = newBar(0);
    SequenceBar* bar2 = newBar(0);
    SequenceBar* bar3 = newBar(0);

    bar1->setPattern(0, pattern1);
    bar2->setPattern(1, pattern3);
    bar3->setPattern(0, pattern1);
    bar3->setPattern(1, pattern3);
}

SequencePattern* AppData::newPattern() {
    SequencePattern* pattern = new SequencePattern(getUnusedPatternId());
    patterns.add(pattern);
    return pattern;
}

SequenceBar* AppData::newBar(int index) {
    SequenceBar* bar = new SequenceBar();
    sequence.getBars().add(index, bar);
    return bar;
}

uint8_t AppData::getUnusedPatternId() {
    for(uint8_t id = 1; id < MAX_PATTERN_ID; id++) {
        if(getPatternById(id) == NULL) {
            return id;
        }
    }
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

SequenceChannel& AppData::getChannel(uint8_t index) {
    return sequence.getChannel(index);
}

SequenceBar* AppData::getBar(int index) {
    return sequence.getBar(index);
}
