#ifndef Component_h
#define Component_h

#include <inttypes.h>
#include "../graphics/GraphicsContext.h"

class Component : public Focusable {

public:
    Component() {}
    virtual void render(GraphicsContext& graphicsContext) = 0;
    void render() { GraphicsContext g = GraphicsContext(true); render(g); }

    uint8_t getHeight() { return height; }
    uint8_t getWidth() { return width; }

protected:
    uint8_t height;
    uint8_t width;

};


#endif
