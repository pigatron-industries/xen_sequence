#ifndef ChannelParameterView_h
#define ChannelParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceChannel.h"


class ChannelParameterView : public AbstractParameterView {

public:
    ChannelParameterView();
    void setChannel(SequenceChannel* channel);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);

private:
    BooleanParameterField channelMuteField = BooleanParameterField("MUTE");

    SequenceChannel* channel;

    void updateDataFromField(ParameterField* field);
};

#endif
