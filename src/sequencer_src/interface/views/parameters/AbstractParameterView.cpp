#include "AbstractParameterView.h"
#include "lib/util/debug.h"

void AbstractParameterView::init() {
    fields.setScrollPosition(0);
}

void AbstractParameterView::render(GraphicsContext& g) {
    DEBUG("AbstractParameterView::render");
    Component::render(g);
    fields.render(g);
}

InterfaceEvent AbstractParameterView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::DATA_PRESS:
            selectedField->changeSelectMode();
            break;

        case InterfaceEventType::DATA_INCREMENT:
            if(ParameterField::selectMode == ParameterField::SelectMode::VALUE) {
                fieldIncrement(event.data);
            } else {
                nextParameter();
            }
            break;

        case InterfaceEventType::DATA_DECREMENT:
            if(ParameterField::selectMode == ParameterField::SelectMode::VALUE) {
                fieldDecrement(event.data);
            } else {
                prevParameter();
            }
            break;

        default:
            break;
    }
    return InterfaceEvent::NONE;
}

void AbstractParameterView::prevParameter() {
    int8_t newFieldIndex = selectedFieldIndex;
    boolean foundSelectableField = false;
    while(!foundSelectableField) {
        newFieldIndex--;
        if(newFieldIndex < 0) {
            newFieldIndex = fields.getSize()-1;
        }
        Component* field = fields.getComponent(newFieldIndex);
        foundSelectableField = field->getVisibility() & field->getFocusable();
    }

    setSelectedField(newFieldIndex);
}

void AbstractParameterView::nextParameter() {
    int8_t newFieldIndex = selectedFieldIndex;
    boolean foundSelectableField = false;
    while(!foundSelectableField) {
        newFieldIndex++;
        if(newFieldIndex >= fields.getSize()) {
            newFieldIndex = 0;
        }
        foundSelectableField = fields.getComponent(newFieldIndex)->getVisibility()
                             & fields.getComponent(newFieldIndex)->getFocusable();
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
    fields.scrollToComponent(index);
}

void AbstractParameterView::fieldIncrement(int amount) {
    if(selectedField != NULL) {
        selectedField->increment(amount);
        updateDataFromField(selectedField);
        //queueRender();
    }
}

void AbstractParameterView::fieldDecrement(int amount) {
    if(selectedField != NULL) {
        selectedField->decrement(amount);
        updateDataFromField(selectedField);
        //queueRender();
    }
}