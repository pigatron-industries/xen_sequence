#ifndef BarParameterView_h
#define BarParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceBar.h"


class BarParameterView : public AbstractParameterView {

public:
    BarParameterView();
    void setBar(SequenceBar* bar);

//private:
    IntegerParameterField barLengthField = IntegerParameterField("LENGTH", 1, 255);
    IntegerParameterField barSpeedField = IntegerParameterField("SPEED+", 0, 960, " BPM");
    IntegerParameterField barSpeedMultField = IntegerParameterField("SPEEDX", 0, 4, "");

    SequenceBar* bar;
};

#endif
