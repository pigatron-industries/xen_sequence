#ifndef AbstractParameterView_h
#define AbstractParameterView_h

#include <inttypes.h>

#include "interface/views/View.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
#include "interface/components/ListComponent.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceEvent.h"


class AbstractParameterView : public View {

public:
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);

protected:
    ListComponent fields;

    int8_t selectedFieldIndex = 0;
    ParameterField* selectedField = NULL;

    void prevParameter();
    void nextParameter();
    void setSelectedField(int index);
    void fieldIncrement(int amount);
    void fieldDecrement(int amount);
};

#endif
