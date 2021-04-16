#include "AppData.h"
#include "lib/util/debug.h"
#include "model/event/SequenceEventFactory.h"

#include <Arduino.h>

AppData AppData::data;

AppData::AppData() {
}

SequenceBar* AppData::getBar(int index) {
    while(index >= sequence.getBars().size()) {
        newBar(sequence.getBars().size());
    }
    return sequence.getBar(index);
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

uint16_t AppData::getAbsoluteSpeed(SequenceBar* bar) {
    return sequence.getSpeed() + bar->getSpeedDiff();
}

uint8_t AppData::getAbsoluteSpeedMult(SequenceBar* bar) {
    return sequence.getSpeedMult() * bar->getSpeedMult();
}

SequenceBar* AppData::newBar(int index) {
    SequenceBar* bar = new SequenceBar();
    sequence.getBars().add(index, bar);
    return bar;
}

SequencePattern* AppData::newPattern() {
    SequencePattern* pattern = new SequencePattern(getUnusedPatternId());
    patterns.add(pattern);
    return pattern;
}

SequencePattern* AppData::newPattern(uint16_t barIndex, uint8_t channelIndex) {
    SequencePattern* pattern = newPattern();
    SequenceBar* bar = getBar(barIndex);
    if(bar == NULL) {
        bar = newBar(barIndex);
    }
    bar->setPattern(channelIndex, pattern);
    return pattern;
}

SequencePattern* AppData::copyPattern(SequencePattern* sourcePattern) {
    DEBUGINFO
    SequencePattern* pattern = newPattern();
    pattern->copy(sourcePattern);
    return pattern;
}

SequenceBar* AppData::copyBar(SequenceBar* sourceBar, int newBarIndex) {
    SequenceBar* newBar = AppData::newBar(newBarIndex);
    newBar->copy(sourceBar);
    return newBar;
}

void AppData::setPattern(uint16_t barIndex, uint8_t channel, SequencePattern* pattern) {
    SequenceBar* bar = getBar(barIndex);
    if(bar != NULL) {
        bar->setPattern(channel, pattern);
    }
}

uint8_t AppData::getUnusedPatternId() {
    for(uint8_t id = 1; id < MAX_PATTERN_ID; id++) {
        if(getPatternById(id) == NULL) {
            return id;
        }
    }
    return 0;
}

SequenceEvent* AppData::newEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, EventType eventType) {
    SequenceBar* bar = getBar(barIndex);
    if(bar == NULL) {
        bar = newBar(barIndex);
    }
    SequencePattern* pattern = bar->getPattern(channelIndex);
    if(pattern == NULL) {
        pattern = newPattern(barIndex, channelIndex);
    }
    SequenceEvent* event = SequenceEventFactory::create(eventType);
    pattern->addEvent(tickIndex, event);
    return event;
}

SequenceTickEvents* AppData::newTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, SequenceTickEvents* copy) {
    SequenceBar* bar = getBar(barIndex);
    if(bar == NULL) {
        bar = newBar(barIndex);
    }
    SequencePattern* pattern = bar->getPattern(channelIndex);
    if(pattern == NULL) {
        pattern = newPattern(barIndex, channelIndex);
    }
    SequenceTickEvents* tickEvents = new SequenceTickEvents(copy);
    pattern->setTickEvents(tickIndex, tickEvents);
    return tickEvents;
}

void AppData::deleteTickEvents(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex) {
    SequenceBar* bar = getBar(barIndex);
    if(bar == NULL) {
        return;
    }
    SequencePattern* pattern = bar->getPattern(channelIndex);
    if(pattern == NULL) {
        return;
    }
    pattern->deleteTickEvents(tickIndex);
}

void AppData::deleteEvent(uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex, uint8_t eventIndex) {
    SequenceBar* bar = getBar(barIndex);
    if(bar == NULL) {
        return;
    }
    SequencePattern* pattern = bar->getPattern(channelIndex);
    if(pattern == NULL) {
        return;
    }
    pattern->deleteEvent(tickIndex, eventIndex);
}

SequenceChannel& AppData::getChannel(uint8_t index) {
    return sequence.getChannel(index);
}

void AppData::clear() {
    LinkedList<SequenceBar*>& bars = sequence.getBars();
    for(int i = 0; i < bars.size(); i++) {
        sequence.deleteBar(i);
    }
    bars.clear();

    for(int i = 0; i < patterns.size(); i++) {
        SequencePattern* pattern = patterns.get(i);
        delete pattern;
    }
    patterns.clear();
}

void AppData::serialize(JsonObject doc) {
    doc["version"] = DATA_VERSION;
    JsonArray docPatterns = doc.createNestedArray("patterns");
    for(int i = 0; i < patterns.size(); i++) {
        JsonObject docPattern = docPatterns.createNestedObject();
        patterns[i]->serialize(docPattern);
    }

    JsonObject docSequence = doc.createNestedObject("sequence");
    sequence.serialize(docSequence);
}

void AppData::deserialize(JsonObject doc) {
    AppData::clear();
    float version = doc["version"];
    Serial.println(version);

    JsonArray docPatterns = doc["patterns"];
    for(JsonObject docPattern : docPatterns) {
        SequencePattern* pattern = newPattern();
        pattern->deserialize(docPattern);
    }

    JsonObject docSequence = doc["sequence"];
    sequence.deserialize(docSequence);
}