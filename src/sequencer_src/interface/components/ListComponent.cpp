#include "ListComponent.h"

void ListComponent::render(GraphicsContext& g) {
    for(int i = 0; i < componentCount; i++) {
        components[i]->render(g);
        g.yPos += components[i]->getHeight();
    }
}

void ListComponent::addComponent(Component* component) {
    components[componentCount] = component;
    componentCount++;
}
