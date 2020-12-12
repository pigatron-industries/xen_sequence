#include "SequenceChannel.h"

void SequenceChannel::serialize(JsonObject doc) {
    doc["mute"] = mute;
}

void SequenceChannel::deserialize(JsonObject doc) {
    mute = doc["mute"];
}