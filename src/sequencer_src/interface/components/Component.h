#ifndef Component_h
#define Component_h

#include <inttypes.h>
#include "../graphics/GraphicsContext.h"

class Component {

public:
    Component() {}
    virtual void render(GraphicsContext& graphicsContext) = 0;
    void render() { GraphicsContext g = GraphicsContext(true); render(g); }

    uint8_t getHeight() { return height; }

protected:
    uint8_t height;

};


#endif
