#include "SequenceEvent.h"

void SequenceEvent::serialize(JsonObject doc) {
    JsonArray jsonFlags = doc.createNestedArray("flags");
    if(getFlag(SequenceEventFlag::NOTE_ON)) {
        jsonFlags.add("NOTE_ON");
    }
    if(getFlag(SequenceEventFlag::NOTE_OFF)) {
        jsonFlags.add("NOTE_OFF");
    }
    doc["pitch"] = pitch;
    doc["velocity"] = velocity;
    doc["gate"] = gate;
    doc["delay"] = delay;
}
