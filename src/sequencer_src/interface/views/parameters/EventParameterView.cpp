#include "EventParameterView.h"

EventParameterView::EventParameterView() {
    fields.addComponent(&eventPitchField);
    fields.addComponent(&eventVelocityField);
    fields.addComponent(&eventGateField);
    fields.addComponent(&eventDelayField);
    setSelectedField(0);
}

void EventParameterView::setTickEvents(SequenceTickEvents* tickEvents) {
    this->tickEvents = tickEvents;
    if(tickEvents != NULL) {
        SequenceEvent* event = tickEvents->getEvent(0); // TODO temporarily only use first event on list
        eventPitchField.setValue(event->getPitch());
        eventVelocityField.setValue(event->getVelocity());
        eventGateField.setValue(event->getGate());
        eventDelayField.setValue(event->getDelay());
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
    SequenceEvent* event = tickEvents->getEvent(0); // TODO temporarily only use first event on list
    if(event != NULL) {
        if(field == &eventPitchField) {
            event->setPitch(eventPitchField.getValue());
        } else if(field == &eventVelocityField) {
            event->setVelocity(eventVelocityField.getValue());
        } else if(field == &eventGateField) {
            event->setGate(eventGateField.getValue());
        } else if(field == &eventDelayField) {
            event->setDelay(eventDelayField.getValue());
        }
        tickEvents->setCompiled(false);
    }
}