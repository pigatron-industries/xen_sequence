#include "SequenceBar.h"
#include "AppData.h"

void SequenceBar::copy(SequenceBar* sourceBar) {
    for(int channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        patterns[channel] = sourceBar->getPattern(channel);
    }
    length = sourceBar->getLength();
    speedDiff = sourceBar->getSpeedDiff();
    speedMult = sourceBar->getSpeedMult();
    empty = sourceBar->isEmpty();
}

void SequenceBar::serialize(JsonObject doc) {
    doc["length"] = length;
    doc["speedDiff"] = speedDiff;
    doc["speedMult"] = speedMult;

    JsonArray docPatterns = doc.createNestedArray("patterns");
    for(int i = 0; i < SEQUENCE_CHANNELS; i++) {
        JsonObject docPattern = docPatterns.createNestedObject();
        if(patterns[i] != NULL) {
            docPattern["id"] = patterns[i]->getId();
        }
    }
}

void SequenceBar::deserialize(JsonObject doc) {
    length = doc["length"];
    speedDiff = doc["speedDiff"];
    speedMult = doc["speedMult"];
    if(speedMult == 0) {
        speedMult = 1;
    }

    JsonArray docPatterns = doc["patterns"];
    int i = 0;
    for(JsonObject docPattern : docPatterns) {
        int id = docPattern["id"];
        SequencePattern* pattern = AppData::data.getPatternById(id);
        patterns[i] = pattern;
        empty = false;
        i++;
    }
}