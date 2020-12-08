#include "SequenceChannel.h"

void SequenceChannel::serialize(JsonObject doc) {
    doc["mute"] = mute;
}