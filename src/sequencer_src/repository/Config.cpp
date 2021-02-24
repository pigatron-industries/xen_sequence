#include "Config.h"

Config Config::config;

Config::Config() {
    lastFile[0] = "\0";
}

void Config::serialize(JsonObject doc) {
    doc["lastFile"] = lastFile;
}

void Config::deserialize(JsonObject doc) {
    strcpy(lastFile, doc["lastFile"]);
}
