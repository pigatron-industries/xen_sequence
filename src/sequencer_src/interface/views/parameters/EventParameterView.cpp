#include "EventParameterView.h"

EventParameterView::EventParameterView() {
    fields.addComponent(&eventStartField);
    fields.addComponent(&eventStopField);
    fields.addComponent(&eventPitchField);
    fields.addComponent(&eventVelocityField);
    setSelectedField(0);
}

#include "model/event/NoteEvent.h"

void EventParameterView::setTickEvents(SequenceTickEvents* tickEvents) {
    this->tickEvents = tickEvents;
    if(tickEvents != NULL) {
        NoteEvent* event = (NoteEvent*)tickEvents->getEvent(0); // TODO temporarily only use first event on list

        eventStartField.setValue(event->getStart());
        eventStopField.setValue(event->getStop());
        eventPitchField.setValue(event->getPitch());
        eventVelocityField.setValue(event->getVelocity());
        
        for(int i = 0; i < fields.getSize(); i++) {
            fields.getComponent(i)->setVisibility(true);
        }
    } else {
        for(int i = 0; i < fields.getSize(); i++) {
            fields.getComponent(i)->setVisibility(false);
        }
    }
}

InterfaceEvent EventParameterView::handleEvent(InterfaceEvent event) {
    AbstractParameterView::handleEvent(event);
    switch(event.eventType) {
        case InterfaceEventType::DATA_DECREMENT:
        case InterfaceEventType::DATA_INCREMENT:
            updateDataFromField(selectedField);
            break;
        default:
            break;
    }
    return InterfaceEvent::NONE;
}

void EventParameterView::handleMidiEvent(MidiMessage message) {
    if(message.command == COMMAND_NOTEON) {
        eventPitchField.setValue(message.data1);
        eventVelocityField.setValue(message.data2);
        updateDataFromField(&eventPitchField);
        updateDataFromField(&eventVelocityField);
    } else if (message.command == COMMAND_CONTROL_CHANGE) {
        //TODO
    }
}

void EventParameterView::updateDataFromField(ParameterField* field) {
    // TODO temporarily only use first event on list
    NoteEvent* event = (NoteEvent*)tickEvents->getEvent(0); 
    if(event != NULL) {
        if(field == &eventStartField) {
            event->setStart(eventStartField.getValue());
        } else if(field == &eventStopField) {
            event->setStop(eventStopField.getValue());
        } else if(field == &eventPitchField) {
            event->setPitch(eventPitchField.getValue());
        } else if(field == &eventVelocityField) {
            event->setVelocity(eventVelocityField.getValue());
        }
        tickEvents->setCompiled(false);
    }
}