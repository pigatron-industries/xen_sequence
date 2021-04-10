#ifndef TickEventParameterView_h
#define TickEventParameterView_h

#include <inttypes.h>

#include "AbstractParameterView.h"
#include "EventParameterView.h"
#include "sequencer/midi/MidiEventHandler.h"
#include "model/SequenceTickEvents.h"

#define MAX_EVENTS 5

class TickEventsParameterView : public AbstractParameterView {

public:
    TickEventsParameterView();
    void setTickEvents(SequenceTickEvents* tickEvents);
    SequenceTickEvents* getTickEvents() { return tickEvents; }
    void handleMidiEvent(MidiMessage message);
    int getSelectedEventIndex();

protected:
    virtual void updateDataFromField(ParameterField* field);

private:
    EventParameterView eventParametersViews[MAX_EVENTS];

    SequenceTickEvents* tickEvents;

};

#endif
