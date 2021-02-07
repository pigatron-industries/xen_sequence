#ifndef ListComponent_h
#define ListComponent_h

#include "Component.h"
#include "lib/drivers/Display.h"

#define MAX_COMPONENTS 255


class ListComponent : public Component {

public:
    ListComponent() {}
    virtual void render(GraphicsContext& g);

    void clear() { componentCount = 0; }
    void addComponent(Component* component);
    int getSize() { return componentCount; }
    Component* getComponent(int index) { return components[index]; }

private:
    Component* components[MAX_COMPONENTS];
    int componentCount = 0;

};


#endif
