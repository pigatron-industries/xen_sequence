#ifndef EventParameterView_h
#define EventParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/field/RangeParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceTickEvents.h"


class EventParameterView : public AbstractParameterView {

public:
    EventParameterView();
    void addFields(ListComponent* fields);
    void setEvent(SequenceEvent* event);
    SequenceEvent* getEvent() { return event; }
    void handleMidiEvent(MidiMessage message);
    void updateDataFromField(ParameterField* field);

private:
    RangeParameterField noteOnOffField = RangeParameterField("ON/OFF", 0, 100);
    PitchParameterField eventPitchField = PitchParameterField("PITCH");
    IntegerParameterField eventVelocityField = IntegerParameterField("VELOCITY", 0, 128);

    SequenceEvent* event;

};

#endif
