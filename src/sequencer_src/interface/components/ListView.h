#ifndef ListView_h
#define ListView_h

#include "Component.h"
#include "../../lib/drivers/Display.h"

#define MAX_COMPONENTS 255


class ListView : public Component {

public:
    ListView() {}
    virtual void render(GraphicsContext& g);

    void addComponent(Component* component);

private:
    Component* components[MAX_COMPONENTS];
    int componentCount = 0;

};


#endif
