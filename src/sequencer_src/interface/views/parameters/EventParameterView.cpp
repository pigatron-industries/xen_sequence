#include "EventParameterView.h"
#include "model/event/NoteEvent.h"

const char* EventParameterView::EVENT_TYPE_NAMES[] = { "NOTE", "CONTROL" };

EventParameterView::EventParameterView() {
}

void EventParameterView::addFields(ListComponent* fields) {
    fields->addComponent(&eventTypeField);
    fields->addComponent(&noteOnOffField);
    fields->addComponent(&eventPitchField);
    fields->addComponent(&eventVelocityField);
    fields->addComponent(&lineComponent);
}

void EventParameterView::setEvent(SequenceEvent* event) {
    eventTypeField.setVisibility(false);
    noteOnOffField.setVisibility(false);
    eventPitchField.setVisibility(false);
    eventVelocityField.setVisibility(false);
    lineComponent.setVisibility(false);

    this->event = event;
    if(event != NULL) {
        eventTypeField.setVisibility(true);
        lineComponent.setVisibility(true);
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

bool EventParameterView::containsField(ParameterField* field) {
    return field == &eventTypeField || field == &noteOnOffField || field == &eventPitchField || field == &eventVelocityField;
}