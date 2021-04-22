#include "EventParameterView.h"
#include "model/event/NoteEvent.h"
#include "model/event/ControlEvent.h"
#include "model/event/SequenceEventFactory.h"

const char* EventParameterView::EVENT_TYPE_NAMES[] = { "NOTE", "CONTROL" };

EventParameterView::EventParameterView() {
    eventTypeField.setListener(this);
}

void EventParameterView::addFields(ListComponent* fields) {
    fields->addComponent(&eventTypeField);
    fields->addComponent(&noteOnOffField);
    fields->addComponent(&eventPitchField);
    fields->addComponent(&eventVelocityField);

    fields->addComponent(&eventControlField);
    fields->addComponent(&eventValueField);

    fields->addComponent(&lineComponent);
}

void EventParameterView::setEvent(SequenceTickEvents* tickEvents, SequenceEvent* event) {
    eventTypeField.setVisibility(false);
    noteOnOffField.setVisibility(false);
    eventPitchField.setVisibility(false);
    eventVelocityField.setVisibility(false);

    eventControlField.setVisibility(false);
    eventValueField.setVisibility(false);

    lineComponent.setVisibility(false);

    this->tickEvents = tickEvents;
    this->event = event;
    if(event != NULL) {
        eventTypeField.setVisibility(true);
        lineComponent.setVisibility(true);

        switch(event->getEventType()) {
            case EventType::NOTE_EVENT: {
                NoteEvent* noteEvent = (NoteEvent*)event;
                noteOnOffField.setStartValue(noteEvent->getStart());
                noteOnOffField.setStopValue(noteEvent->getStop());
                eventPitchField.setValue(noteEvent->getPitch());
                eventVelocityField.setValue(noteEvent->getVelocity());
                noteOnOffField.setVisibility(true);
                eventPitchField.setVisibility(true);
                eventVelocityField.setVisibility(true);
                break;
            }
            case EventType::CONTROL_EVENT: {
                ControlEvent* controlEvent = (ControlEvent*)event;
                eventControlField.setValue(controlEvent->getControl());
                eventValueField.setValue(controlEvent->getValue());
                eventControlField.setVisibility(true);
                eventValueField.setVisibility(true);
                break;
            }
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
        eventValueField.setValue(message.data2);
        updateDataFromField(&eventValueField);
    }
}

void EventParameterView::updateDataFromField(ParameterField* field) {
    if(event != NULL) {
        switch(event->getEventType()) {
            case EventType::NOTE_EVENT: {
                NoteEvent* noteEvent = (NoteEvent*)event;
                if(field == &noteOnOffField) {
                    noteEvent->setStart(noteOnOffField.getStartValue());
                    noteEvent->setStop(noteOnOffField.getStopValue());
                } else if(field == &eventPitchField) {
                    noteEvent->setPitch(eventPitchField.getValue());
                } else if(field == &eventVelocityField) {
                    noteEvent->setVelocity(eventVelocityField.getValue());
                }
                break;
            }
            case EventType::CONTROL_EVENT: {
                ControlEvent* controlEvent = (ControlEvent*)event;
                if(field == &eventControlField) {
                    controlEvent->setControl(eventControlField.getValue());
                } else if(field == &eventValueField) {
                    controlEvent->setValue(eventValueField.getValue());
                }
                break;
            }
        }
    }
}

bool EventParameterView::containsField(ParameterField* field) {
    return field == &eventTypeField || field == &noteOnOffField || field == &eventPitchField || field == &eventVelocityField;
}

void EventParameterView::onSelectModeChange(ParameterField* field) {
    if(field == &eventTypeField) {
        if(eventTypeField.getValue() != event->getEventType()) {
            int index = tickEvents->findEvent(event);
            SequenceEvent* newEvent = SequenceEventFactory::create(static_cast<EventType>(eventTypeField.getValue()));
            tickEvents->replaceEvent(index, newEvent);
            setEvent(tickEvents, newEvent);
            InterfaceEventQueue::q.doRender(true);
        }
    }
}

void EventParameterView::onValueChange(ParameterField* field) {

}
