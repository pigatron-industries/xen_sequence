#include "SequenceBar.h"
#include "AppData.h"

void SequenceBar::serialize(JsonObject doc) {
    doc["length"] = length;
    doc["speed"] = speed;

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
    speed = doc["speed"];

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