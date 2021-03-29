#include "EventParameterView.h"

EventParameterView::EventParameterView() {
    fields.addComponent(&noteOnOffField);
    fields.addComponent(&eventPitchField);
    fields.addComponent(&eventVelocityField);
    setSelectedField(0);
}

#include "model/event/NoteEvent.h"

void EventParameterView::setTickEvents(SequenceTickEvents* tickEvents) {
    this->tickEvents = tickEvents;
    if(tickEvents != NULL) {
        NoteEvent* event = (NoteEvent*)tickEvents->getEvent(0); // TODO temporarily only use first event on list

        noteOnOffField.setStartValue(event->getStart());
        noteOnOffField.setStopValue(event->getStop());
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
        if(field == &noteOnOffField) {
            event->setStart(noteOnOffField.getStartValue());
            event->setStop(noteOnOffField.getStopValue());
        } else if(field == &eventPitchField) {
            event->setPitch(eventPitchField.getValue());
        } else if(field == &eventVelocityField) {
            event->setVelocity(eventVelocityField.getValue());
        }
        tickEvents->setCompiled(false);
    }
}