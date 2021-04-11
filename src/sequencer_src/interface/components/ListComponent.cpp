#include "ListComponent.h"
#include "lib/util/debug.h"

void ListComponent::render(GraphicsContext& g) {
    Component::render(g);
    if(rerenderFull) {
        g.full = true;
        rerenderFull = false;
        Hardware::display.fillRect(0, g.yPos, width, height, Colour::BLACK);
    }

    g.yPos -= scrollPosition;
    for(int i = 0; i < componentCount; i++) {
        if(components[i]->getVisibility()) {
            components[i]->setTop(g.yPos);
            if(g.yPos >= top && g.yPos <= top+height) {
                components[i]->render(g);
            }
            g.yPos += components[i]->getHeight();
        }
    }
}

void ListComponent::addComponent(Component* component) {
    components[componentCount] = component;
    componentCount++;
}

void ListComponent::scrollToComponent(uint8_t index) {
    Component* component = getComponent(index);
    if(height > 0) {
        int absoluteFieldTop = component->getTop() - getTop();
        int absoluteFieldBottom = absoluteFieldTop + component->getHeight();
        int fieldPos = absoluteFieldTop + scrollPosition;
        if(absoluteFieldBottom >= height) {
            setScrollPosition(fieldPos - 11*9);
        } else if(absoluteFieldTop < 0) {
            setScrollPosition(fieldPos);
        }
    }
}