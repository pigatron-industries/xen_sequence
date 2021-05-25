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
    //virtual InterfaceEvent handleEvent(InterfaceEvent event);
    void setTickEvents(SequenceTickEvents* tickEvents, uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex);
    SequenceTickEvents* getTickEvents() { return tickEvents; }
    bool handleMidiEvent(const MidiMessage& message);
    int getSelectedEventIndex();

protected:
    virtual void updateDataFromField(ParameterField* field);

private:
    EventParameterView eventParametersViews[MAX_EVENTS];

    SequenceTickEvents* tickEvents;
    uint16_t barIndex;
    uint8_t channelIndex;
    uint8_t tickIndex;

    EventParameterView* getSelectedEventParameters();
    bool handleMidiMessage(const MidiMessage& message, EventType eventType);
    int getMatchingEventIndex(const MidiMessage& message, int startIndex = 0);
    int createEvent(EventType eventType);
};

#endif
