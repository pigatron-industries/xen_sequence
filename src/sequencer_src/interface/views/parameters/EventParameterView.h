#ifndef EventParameterView_h
#define EventParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceEvent.h"


class EventParameterView : public AbstractParameterView {

public:
    EventParameterView();
    void setEvent(SequenceEvent* event);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);

//private:
    PitchParameterField eventPitchField = PitchParameterField("PITCH");
    IntegerParameterField eventVelocityField = IntegerParameterField("VELOCITY", 0, 128);
    IntegerParameterField eventGateField = IntegerParameterField("GATE", 0, 100, " %");
    IntegerParameterField eventDelayField = IntegerParameterField("DELAY", 0, 100, " %");

    SequenceEvent* event;

    void updateDataFromField(ParameterField* field);
};

#endif
