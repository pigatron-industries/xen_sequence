#include "Sequence.h"

int Sequence::getLength() {
    if(bars[bars.size()-1]->isEmpty()) {
        return bars.size()-1; 
    } else {
        return bars.size(); 
    }
}

void Sequence::deleteBar(uint16_t index) {
    SequenceBar* bar = bars.get(index);
    bars.remove(index);
    delete bar;
}

void Sequence::clear() {
    for(int i = 0; i < bars.size(); i++) {
        deleteBar(i);
    }
    bars.clear();
    for(int channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        channels[channel].setMidiChannel(channel);
    }
}

void Sequence::serialize(JsonObject doc) {
    doc["speed"] = speed;
    doc["speedMult"] = speedMult;

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
    speed = doc["speed"];
    if(speed == 0) {
        speed = 120;
    }
    speedMult = doc["speedMult"];
    if(speedMult == 0) {
        speedMult = 1;
    }

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

