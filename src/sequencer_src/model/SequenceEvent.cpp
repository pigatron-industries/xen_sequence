#include "SequenceEvent.h"

void SequenceEvent::serialize(JsonObject doc) {
    JsonArray docFlags = doc.createNestedArray("flags");
    if(getFlag(SequenceEventFlag::NOTE_ON)) {
        docFlags.add("NOTE_ON");
    }
    if(getFlag(SequenceEventFlag::NOTE_OFF)) {
        docFlags.add("NOTE_OFF");
    }
    doc["pitch"] = pitch;
    doc["velocity"] = velocity;
    doc["gate"] = gate;
    doc["delay"] = delay;
}

void SequenceEvent::deserialize(JsonObject doc) {
    JsonArray docFlags = doc["flags"];
    for(JsonVariant v : docFlags) {
        const char* docFlag = v.as<char*>();
        if(strcmp(docFlag, "NOTE_ON")) {
            setFlag(SequenceEventFlag::NOTE_ON, true);
        } else if(strcmp(docFlag, "NOTE_OFF")) {
            setFlag(SequenceEventFlag::NOTE_OFF, true);
        }
    }
    pitch = doc["pitch"];
    velocity = doc["velocity"];
    gate = doc["gate"];
    delay = doc["delay"];
}