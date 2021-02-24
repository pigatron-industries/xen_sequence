#ifndef Config_h
#define Config_h

#include <ArduinoJson.h>

#define JSON_BUF_SIZE 16384
#define JSON_DOC_SIZE 16384

class Config {
    public:
        Config();
        static Config config;

        char lastFile[32];

        void serialize(JsonObject doc);
        void deserialize(JsonObject doc);

};

#endif