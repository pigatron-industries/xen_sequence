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


    sequence.getChannel(0).getPatterns().add(pattern1);
    sequence.getChannel(0).getPatterns().add(NULL);
    sequence.getChannel(0).getPatterns().add(pattern1);

    sequence.getChannel(1).getPatterns().add(NULL);
    sequence.getChannel(1).getPatterns().add(pattern3);
    sequence.getChannel(1).getPatterns().add(pattern3);
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

SequencePattern* AppData::getPatternById(uint8_t id) {
    for(int i = 0; i < patterns.size(); i++) {
        SequencePattern* pattern = patterns.get(i);
        if(pattern->getId() == id) {
            return pattern;
        }
    }
    return NULL;
}
