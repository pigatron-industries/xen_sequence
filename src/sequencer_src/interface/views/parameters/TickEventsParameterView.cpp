#include "TickEventsParameterView.h"
#include "model/event/NoteEvent.h"

TickEventsParameterView::TickEventsParameterView() {
    for(int i = 0; i < MAX_EVENTS; i++) {
        eventParametersViews[i].addFields(&fields);
    }
    setSelectedField(0);
}

void TickEventsParameterView::setTickEvents(SequenceTickEvents* tickEvents) {
    this->tickEvents = tickEvents;
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(tickEvents->getEvent(i));
        }
    } else {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(NULL);
        }
    }
}

void TickEventsParameterView::handleMidiEvent(MidiMessage message) {
    if(message.command == COMMAND_NOTEON) {
        eventParametersViews[0].handleMidiEvent(message); //TODO decide which event to send midi to
    } else if (message.command == COMMAND_CONTROL_CHANGE) {
        eventParametersViews[0].handleMidiEvent(message);
    }
}

void TickEventsParameterView::updateDataFromField(ParameterField* field) {
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].updateDataFromField(field);
        }
        tickEvents->setCompiled(false);
    }
}