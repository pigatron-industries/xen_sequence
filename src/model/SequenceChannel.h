#ifndef SequenceChannel_h
#define SequenceChannel_h

#include <inttypes.h>

class SequenceChannel {

public:
    bool getMute() { return mute; }
    void setMute(bool _mute) { mute = _mute; }

private:
    bool mute;

};

#endif
