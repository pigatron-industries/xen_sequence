#include "TickEventsParameterView.h"
#include "model/event/NoteEvent.h"

TickEventsParameterView::TickEventsParameterView() {
    for(int i = 0; i < MAX_EVENTS; i++) {
        eventParametersViews[i].addFields(&fields);
    }
    setSelectedField(0);
}

// InterfaceEvent TickEventsParameterView::handleEvent(InterfaceEvent event) {
//     switch(event.eventType) {
//         case InterfaceEventType::DATA_PRESS:

//             EventParameterView* eventParameterView = getSelectedEventParameters();
//             if(selectedField == eventParameterView->)
//             break;
//     }
//     return AbstractParameterView::handleEvent(event);
// }

void TickEventsParameterView::setTickEvents(SequenceTickEvents* tickEvents) {
    this->tickEvents = tickEvents;
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(tickEvents, tickEvents->getEvent(i));
        }
    } else {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(NULL, NULL);
        }
    }
    if(selectedField != NULL && !selectedField->getVisibility() && fields.getComponent(0)->getVisibility()) {
        setSelectedField(0);
    }
}

int TickEventsParameterView::getSelectedEventIndex() {
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            if(eventParametersViews[i].containsField(selectedField)) {
                return i;
            }
        }
    }
    return -1;
}

EventParameterView* TickEventsParameterView::getSelectedEventParameters() {
    int index = getSelectedEventIndex();
    if(index != -1) {
        return &eventParametersViews[index];
    } else {
        return NULL;
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