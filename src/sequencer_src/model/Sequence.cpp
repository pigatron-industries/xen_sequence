#include "Sequence.h"

void Sequence::serialize(JsonObject doc) {
    JsonArray docChannels = doc.createNestedArray("channels");
    for(int i = 0; i < SEQUENCE_CHANNELS; i++) {
        JsonObject docChannel = docChannels.createNestedObject();
        channels[i].serialize(docChannel);
    }

    JsonArray docBars = doc.createNestedArray("bars");
    for(int i = 0; i < bars.size(); i++) {
        JsonObject docBar = docBars.createNestedObject();
        bars[i]->serialize(docBar);
    }
}

void Sequence::deserialize(JsonObject doc) {
    JsonArray docChannels = doc["channels"];
    int i = 0;
    for(JsonObject docChannel : docChannels) {
        channels[i].deserialize(docChannel);
        i++;
    }

    JsonArray docBars = doc["bars"];
    i = 0;
    for(JsonObject docBar : docBars) {
        SequenceBar* bar = new SequenceBar();
        bars.add(i, bar);
        bar->deserialize(docBar);
        i++;
    }
}

