#include "EventParameterView.h"

EventParameterView::EventParameterView() {
    fields.addComponent(&eventPitchField);
    fields.addComponent(&eventVelocityField);
    fields.addComponent(&eventGateField);
    fields.addComponent(&eventDelayField);
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