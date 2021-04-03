#include "EventParameterView.h"
#include "model/event/NoteEvent.h"

EventParameterView::EventParameterView() {
}

void EventParameterView::addFields(ListComponent* fields) {
    fields->addComponent(&noteOnOffField);
    fields->addComponent(&eventPitchField);
    fields->addComponent(&eventVelocityField);
}

void EventParameterView::setEvent(SequenceEvent* event) {
    noteOnOffField.setVisibility(false);
    eventPitchField.setVisibility(false);
    eventVelocityField.setVisibility(false);

    this->event = event;
    if(event != NULL) {
        if(event->getEventType() == EventType::NOTE_EVENT) {
            NoteEvent* noteEvent = (NoteEvent*)event;
            noteOnOffField.setStartValue(noteEvent->getStart());
            noteOnOffField.setStopValue(noteEvent->getStop());
            eventPitchField.setValue(noteEvent->getPitch());
            eventVelocityField.setValue(noteEvent->getVelocity());
            noteOnOffField.setVisibility(true);
            eventPitchField.setVisibility(true);
            eventVelocityField.setVisibility(true);
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
    if(event != NULL) {
        if(event->getEventType() == EventType::NOTE_EVENT) {
            NoteEvent* noteEvent = (NoteEvent*)event;
            if(field == &noteOnOffField) {
                noteEvent->setStart(noteOnOffField.getStartValue());
                noteEvent->setStop(noteOnOffField.getStopValue());
            } else if(field == &eventPitchField) {
                noteEvent->setPitch(eventPitchField.getValue());
            } else if(field == &eventVelocityField) {
                noteEvent->setVelocity(eventVelocityField.getValue());
            }
        }
    }
}