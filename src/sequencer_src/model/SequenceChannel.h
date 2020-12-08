#ifndef SequenceChannel_h
#define SequenceChannel_h

#include <inttypes.h>
#include <ArduinoJson.h>

class SequenceChannel {

public:
    bool getMute() { return mute; }
    void setMute(bool _mute) { mute = _mute; }

    void serialize(JsonObject doc);

private:
    bool mute;

};

#endif
