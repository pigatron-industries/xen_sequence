#include "EventParameterView.h"

EventParameterView::EventParameterView() {
    fields.addComponent(&eventPitchField);
    fields.addComponent(&eventVelocityField);
    fields.addComponent(&eventGateField);
    fields.addComponent(&eventDelayField);
    setSelectedField(0);
}

void EventParameterView::setEvent(SequenceEvent* event) {
    this->event = event;
    if(event != NULL) {
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

void EventParameterView::updateDataFromField(ParameterField* field) {
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
    }
}