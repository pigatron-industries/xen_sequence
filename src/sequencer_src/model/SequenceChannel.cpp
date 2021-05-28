#include "SequenceChannel.h"

void SequenceChannel::serialize(JsonObject doc) {
    doc["mute"] = mute;
    doc["midi"] = midiChannel;
}

void SequenceChannel::deserialize(JsonObject doc) {
    mute = doc["mute"];
    midiChannel = doc["midi"];
}