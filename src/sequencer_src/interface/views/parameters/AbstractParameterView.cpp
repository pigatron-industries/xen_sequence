#include "AbstractParameterView.h"
#include "lib/util/debug.h"

void AbstractParameterView::init() {

}

void AbstractParameterView::render(GraphicsContext& g) {
    DEBUG("AbstractParameterView::render");
    Serial.println(g.yPos);
    fields.render(g);
}

InterfaceEvent AbstractParameterView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::DATA_PRESS:
            nextParameter();
            break;

        case InterfaceEventType::DATA_INCREMENT:
            fieldIncrement(event.data);
            break;

        case InterfaceEventType::DATA_DECREMENT:
            fieldDecrement(event.data);
            break;

        default:
            break;
    }
    return InterfaceEvent::NONE;
}

void AbstractParameterView::prevParameter() {
    int8_t newFieldIndex = selectedFieldIndex-1;
    if(newFieldIndex < 0) {
        newFieldIndex = fields.getSize()-1;
    }
    setSelectedField(newFieldIndex);
}

void AbstractParameterView::nextParameter() {
    int8_t newFieldIndex = selectedFieldIndex+1;
    if(newFieldIndex >= fields.getSize()) {
        newFieldIndex = 0;
    }
    setSelectedField(newFieldIndex);
}

void AbstractParameterView::setSelectedField(int index) {
    selectedFieldIndex = index;
    if(selectedField != NULL) {
        selectedField->setSelected(false);
    }
        
    selectedField = (ParameterField*)fields.getComponent(index);
    selectedField->setSelected(true);
}

void AbstractParameterView::fieldIncrement(int amount) {
    if(selectedField != NULL) {
        selectedField->increment(amount);
        //updateDataFromField(field);
        //queueRender();
    }
}

void AbstractParameterView::fieldDecrement(int amount) {
    if(selectedField != NULL) {
        selectedField->decrement(amount);
        //updateDataFromField(field);
        //queueRender();
    }
}