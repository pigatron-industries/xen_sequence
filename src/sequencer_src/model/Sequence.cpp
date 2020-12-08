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
