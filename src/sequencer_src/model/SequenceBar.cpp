#include "SequenceBar.h"

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
