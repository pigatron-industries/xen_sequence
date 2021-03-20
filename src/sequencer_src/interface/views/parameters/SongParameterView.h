#ifndef SongParameterView_h
#define SongParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceEvent.h"


class SongParameterView : public AbstractParameterView {

public:
    SongParameterView();
    virtual void init();
    virtual InterfaceEvent handleEvent(InterfaceEvent event);

//private:
    IntegerParameterField songSpeedField = IntegerParameterField("SPEED", 30, 960, " BPM");
    IntegerParameterField songSpeedMultField = IntegerParameterField("SPEEDX", 0, 4, "");

    void updateDataFromField(ParameterField* field);
};

#endif
