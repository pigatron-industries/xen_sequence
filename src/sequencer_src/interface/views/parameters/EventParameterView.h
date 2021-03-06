#ifndef EventParameterView_h
#define EventParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/EnumParameterField.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/field/RangeParameterField.h"
#include "interface/components/field/ParameterFieldListener.h"
#include "interface/components/ListComponent.h"
#include "interface/components/LineComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceTickEvents.h"


class EventParameterView : public AbstractParameterView, ParameterFieldListener {

public:
    EventParameterView();
    void addFields(ListComponent* fields);
    void setEvent(SequenceTickEvents* tickEvents, SequenceEvent* event);
    SequenceEvent* getEvent() { return event; }
    void handleMidiEvent(MidiMessage message);
    void updateDataFromField(ParameterField* field);
    bool containsField(ParameterField* field);

    virtual void onSelectModeChange(ParameterField* field);
    virtual void onValueChange(ParameterField* field);

private:
    static const char* EVENT_TYPE_NAMES[];
    LineComponent lineComponent = LineComponent(Colour::YELLOW, 1);
    EnumParameterField eventTypeField = EnumParameterField("TYPE", EVENT_TYPE_NAMES, 2);

    RangeParameterField noteOnOffField = RangeParameterField("ON/OFF", 0, 24);
    PitchParameterField eventPitchField = PitchParameterField("PITCH");
    IntegerParameterField eventVelocityField = IntegerParameterField("VELOCITY", 0, 127);

    IntegerParameterField eventControlField = IntegerParameterField("CONTROL", 0, 31);
    IntegerParameterField eventValueField = IntegerParameterField("VALUE", 0, 127);

    SequenceTickEvents* tickEvents;
    SequenceEvent* event;

};

#endif
