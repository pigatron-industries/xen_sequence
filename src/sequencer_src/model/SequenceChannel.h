#ifndef SequenceChannel_h
#define SequenceChannel_h

#include <inttypes.h>
#include <ArduinoJson.h>

class SequenceChannel {

public:
    bool getMute() { return mute; }
    uint8_t getMidiChannel() { return midiChannel; }

    void setMute(bool mute) { this->mute = mute; }
    void setMidiChannel(uint8_t midiChannel) { this->midiChannel = midiChannel; }

    void serialize(JsonObject doc);
    void deserialize(JsonObject doc);

private:
    uint8_t midiChannel;
    bool mute;

};

#endif
